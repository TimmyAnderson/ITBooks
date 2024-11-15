//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <fltKernel.h>
#include "SharedHeader.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CMiniFilterRegistryHelpers.h"
#include "Helpers\CLocker.h"
#include "Helpers\CSharedLocker.h"
#include "CVector.h"
#include "CFilterState.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE SYSTEM MINI FILTERS MUSIA mat vlozenu LIBRARY [FltMgr.lib].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace KTL;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define ENABLE_PRE_OPERATION_CALLBACK
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_HIDE_PATH CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_HIDE_PATH,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SHOW_ALL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SHOW_ALL,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CMiniFilterRegistryHelpers										MiniFilterRegistryHelpers;
CFilterState*													State;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Implementacia sposobi, ze DIRECTORY sice bude viditelny, ale pri pokuse o vstup do PROTECTED DIRECTORY sa NEVYPISE jeho CONTENT.
FLT_PREOP_CALLBACK_STATUS OnPreDirectoryControl(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext)
{
	UNREFERENCED_PARAMETER(CompletionContext);

	// !!!!! FILTERING sa robi IBA pre MINOR FUNCTION [IRP_MN_QUERY_DIRECTORY].
	if (Data->RequestorMode==KernelMode || Data->Iopb->MinorFunction!=IRP_MN_QUERY_DIRECTORY)
	{
		return(FLT_PREOP_SUCCESS_NO_CALLBACK);
	}

	NTSTATUS													Status;
	POBJECT_NAME_INFORMATION									NameInfo;

	Status=IoQueryFileDosDeviceName(FltObjects->FileObject,&NameInfo);

	if (NT_SUCCESS(Status)==true)
	{
		FLT_PREOP_CALLBACK_STATUS								Result=FLT_PREOP_SUCCESS_WITH_CALLBACK;
		
#ifdef ENABLE_PRE_OPERATION_CALLBACK
		UNICODE_STRING											Path;
		CSharedLocker											Locker(State->MLock);

		{
			for(const CFilterState::TString& Name : State->MFiles)
			{
				Name.GetUnicodeString(Path);

				//KdPrint(("DOS PATH [%wZ] PATH [%wZ] !!!\n",NameInfo->Name,Path));

				if (RtlEqualUnicodeString(&Path,&NameInfo->Name,TRUE)==TRUE)
				{
					KdPrint(("PRE OPERATION hid PATH [%wZ] !!!\n",Path));

					Data->IoStatus.Status=STATUS_NOT_FOUND;
					Data->IoStatus.Information=0;

					Result=FLT_PREOP_COMPLETE;

					break;
				}
			}
		}
#endif

		ExFreePool(NameInfo);

		return(Result);
	}
	else
	{
		KdPrint(("PRE OPERATION FAILED to get DOS DEVICE NAME with ERROR CODE [%lX] !!!\n",Status));

		return(FLT_PREOP_SUCCESS_NO_CALLBACK);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Implementacia sposobi, ze DIRECTORY nebude vobec viditelny.
// !!!!! CODE je implementovany tak, ze v pripade, ze sa v PARENT DIRECTORY nachadza PROTECTED DIRECTORY, tak tento vysledok sa vyhodi z RESULT SET vsetkych DIRECTORIES a FILES, ktore IRP [IRP_MJ_DIRECTORY_CONTROL] v POST OPERATION vracia.
FLT_POSTOP_CALLBACK_STATUS OnPostDirectoryControl(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID CompletionContext, FLT_POST_OPERATION_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

	// !!!!! Pre kazdy CLASS definuje KERNEL inu STRUCTURE, ktora ma na inej POSITION definovane FIELD [NextEntryOffset], FIELD [FileName] a FIELD [FileNameLength].
	// !!!!! Aby bolo mozne k tymto FIELDS jednoducho pristupovat, KERNEL definuje pre kazdu STRUCTURE MACRO, ktore naplni pozicie FIELD [NextEntryOffset], FIELD [FileName] a FIELD [FileNameLength].
	const static FILE_INFORMATION_DEFINITION					Definitions[]=
	{
		FileFullDirectoryInformationDefinition,
		FileBothDirectoryInformationDefinition,
		FileDirectoryInformationDefinition,
		FileNamesInformationDefinition,
		FileIdFullDirectoryInformationDefinition,
		FileIdBothDirectoryInformationDefinition,
		FileIdExtdDirectoryInformationDefinition,
		FileIdGlobalTxDirectoryInformationDefinition
	};

	// !!!!! FILTERING sa robi IBA pre MINOR FUNCTION [IRP_MN_QUERY_DIRECTORY].
	if (Data->RequestorMode==KernelMode || Data->Iopb->MinorFunction!=IRP_MN_QUERY_DIRECTORY || (Flags&FLTFL_POST_OPERATION_DRAINING)!=0)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	// !!!!! Tuto CONDITION som musel pridat, lebo DRIVER NIZSIE v DRIVER STACK mohol vratit aj VALUE [STATUS_NO_MORE_FILES], kedy BUFFER [Parameters.MdlAddress] eventualne BUFFER [Parameters.DirectoryBuffer] NEOBSAHOVALI platne data a doslo k BUG CHECK.
	if (Data->IoStatus.Status!=STATUS_SUCCESS)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	auto&														Parameters=Data->Iopb->Parameters.DirectoryControl.QueryDirectory;

	const FILE_INFORMATION_DEFINITION*							ActualDefinition=nullptr;

	for(const FILE_INFORMATION_DEFINITION& Definition : Definitions)
	{
		if (Parameters.FileInformationClass==Definition.Class)
		{
			ActualDefinition=&Definition;
			break;
		}
	}

	if (ActualDefinition==nullptr)
	{
		KdPrint(("POST OPERATION IGNORED INFO CLASS [%u] !!!\n",Parameters.FileInformationClass));

		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	POBJECT_NAME_INFORMATION									DosPath=nullptr;
	NTSTATUS													Status;

	Status=IoQueryFileDosDeviceName(FltObjects->FileObject,&DosPath);

	if (NT_SUCCESS(Status)==true)
	{
		PUCHAR													Base=nullptr;

		if (Parameters.MdlAddress!=nullptr)
		{
			Base=((PUCHAR)MmGetSystemAddressForMdlSafe(Parameters.MdlAddress,NormalPagePriority));
		}

		if (Base==nullptr)
		{
			Base=((PUCHAR)Parameters.DirectoryBuffer);
		}

		if (Base==nullptr)
		{
			return(FLT_POSTOP_FINISHED_PROCESSING);
		}

		KdPrint(("DOS PATH [%wZ] !!!\n",DosPath));

		// !!! FILE SYSTEM DRIVER vracia pre MAJOR FUNCTION [IRP_MJ_DIRECTORY_CONTROL] a MINOR FUNCTION [IRP_MN_QUERY_DIRECTORY] zoznam vsetkych DIRECTORIES a vsetkych FILES.
		// !!!!! Zoznam vsetkych FILES je ulozeny v BUFFER [Parameters.MdlAddress], alebo BUFFER [Parameters.DirectoryBuffer], pricom pozicie jednotlivych DIRECTORIES a FILES v BUFFER je urceny ako ADDRESS [BUFFER_ADDRESS+FILE_INFORMATION_DEFINITION::NextEntryOffset].
		// !!! Ak sa v DIRECTORY nachadzaju DIRECTORY [DIRECTORY_1], DIRECTORY [DIRECTORY_2], FILE [FILE_1] a FILE [FILE_2] tak BUFFER je nasledovne usporiadany.
		// 1. ADDRESS [Address1=Base] obsahuje informacie o DIRECTORY [DIRECTORY_1].
		// 2. ADDRESS [Address2=*(Address1+FILE_INFORMATION_DEFINITION::NextEntryOffset)] obsahuje informacie o DIRECTORY [DIRECTORY_1].
		// 3. ADDRESS [Address3=*(Address2+FILE_INFORMATION_DEFINITION::NextEntryOffset)] obsahuje informacie o DIRECTORY [DIRECTORY_2].
		// 4. ADDRESS [Address4=*(Address3+FILE_INFORMATION_DEFINITION::NextEntryOffset)] obsahuje informacie o DIRECTORY [FILE_1].
		// 5. ADDRESS [Address5=*(Address4+FILE_INFORMATION_DEFINITION::NextEntryOffset)] obsahuje informacie o DIRECTORY [FILE_2].

		{
			ULONG												NextOffset=0;
			PUCHAR												Previous=nullptr;

			do
			{
				// !!! STRUCTURE [FILE_INFORMATION_DEFINITION] uz NEMA ERROR, ako sa o nej pise v BOOK. Uz bola odstranena.
				PWSTR											Filename=((PWSTR)(Base+ActualDefinition->FileNameOffset));
				ULONG											FilenameLength=(*(PULONG)(Base+ActualDefinition->FileNameLengthOffset));

				NextOffset=(*(PULONG)(Base+ActualDefinition->NextEntryOffset));

				UNICODE_STRING									UnicodeName{};

				UnicodeName.Buffer=Filename;
				UnicodeName.Length=USHORT(FilenameLength);
				UnicodeName.MaximumLength=UnicodeName.Length;

				KdPrint(("!!!!! NAME [%wZ] LENGTH [%lu] NEXT OFFSET [%lu] !!!\n",UnicodeName,FilenameLength,NextOffset));

				bool											DirectoryWasHidden=false;

				{
					CSharedLocker								Locker(State->MLock);

					{
						for(const CFilterState::TString& Name : State->MFiles)
						{
							wchar_t*							LastBackslashPosition=wcsrchr(Name,L'\\');

							if (LastBackslashPosition==nullptr)
							{
								continue;
							}

							UNICODE_STRING						Copy;

							Copy.Buffer=((PWCH)Name.Data());

							// !!! Vola sa CONVERSION OPERATOR pre TYPE [CFilterState::TString].
							Copy.Length=(USHORT(LastBackslashPosition-Name)*sizeof(WCHAR));

							// !!! Ak sa jedna o PATH [C:].
							if (Copy.Length==(sizeof(WCHAR)*2))
							{
								Copy.Length+=sizeof(WCHAR);
							}

							Copy.MaximumLength=Copy.Length;

							//KdPrint(("!!!!!!!!!! DOS PATH [%wZ] NAME [%ws] COPY [%wZ] !!!\n",DosPath->Name,Name.operator const wchar_t*(),Copy));

							if (RtlEqualUnicodeString(&Copy,&DosPath->Name,TRUE)==TRUE)
							{
								wchar_t*						String=(LastBackslashPosition+1);
								size_t							StringLength=wcslen(String);
								size_t							FilenameLengthInChars=(FilenameLength/sizeof(WCHAR));

								if (StringLength==FilenameLengthInChars)
								{
									int							CompareResult=_wcsnicmp(String,Filename,FilenameLengthInChars);

									if (FilenameLength!=0 && CompareResult==0)
									{
										if (Previous==nullptr)
										{
											// !!!!! Tato cast NEFUNGUJE. Aj ked dojde k zmene ADDRESS, nesposobi to, ze DIRECTORY je HIDDEN.
											Parameters.DirectoryBuffer=(Base+NextOffset);

											FltSetCallbackDataDirty(Data);

											KdPrint(("!!!!!!!!!! FIRST DIRECTORY [%ws] is HIDDEN !!!\n",String));
										}
										else
										{
											if (NextOffset!=0)
											{
												// !!!!! Ak sa NEJEDNA o posledny DIRECTORY v PARENT DIRECTORY, musi sa OFFSET nastavit na nasledujuci DIRECTORY RECORD, aby CURRENT DIRECTORY RECORDS nezobrazil a bol HIDDEN.
												*(PULONG)(Previous+ActualDefinition->NextEntryOffset)+=NextOffset;
											}
											else
											{
												// !!!!! Ak sa jedna o posledny DIRECTORY v PARENT DIRECTORY, musi sa OFFSET nastavit na VALUE [0].
												*(PULONG)(Previous+ActualDefinition->NextEntryOffset)=0;
											}

											KdPrint(("!!!!!!!!!! NEXT DIRECTORY [%ws] is HIDDEN !!!\n",String));
										}

										DirectoryWasHidden=true;

										break;
									}
								}
							}
						}
					}
				}

				if (DirectoryWasHidden==false)
				{
					Previous=Base;
				}

				Base+=NextOffset;
			}
			while(NextOffset!=0);
		}

		ExFreePool(DosPath);
	}
	else
	{
		KdPrint(("POST OPERATION FAILED to get DOS DEVICE NAME with ERROR CODE [%lX] !!!\n",Status));
	}

	return(FLT_POSTOP_FINISHED_PROCESSING);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineCreate(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineClose(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineDeviceControl(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	NTSTATUS													Status=STATUS_INVALID_DEVICE_REQUEST;
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	auto&														Parameters=CurrentStackLocation->Parameters.DeviceIoControl;
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
	ULONG_PTR													Information=0;

	if (Code==IOCTL_HIDE_PATH)
	{
		do
		{
			if (Parameters.InputBufferLength<(sizeof(WCHAR)*4))
			{
				Status=STATUS_BUFFER_TOO_SMALL;
				break;
			}

			PWSTR												Path=(PWSTR)Irp->AssociatedIrp.SystemBuffer;

			if (Path==nullptr || Path[1]!=L':')
			{
				Status=STATUS_INVALID_PARAMETER;
				break;
			}

			Path[(Parameters.InputBufferLength/sizeof(WCHAR))-1]=L'\0';

			{
				CLocker											Locker(State->MLock);

				{
					State->MFiles.Add(Path);
				}
			}

			size_t												PathLength=wcslen(Path);

			Information=(ULONG((1+PathLength)*sizeof(WCHAR)));
			Status=STATUS_SUCCESS;
		}
		while(false);
	}
	else if (Code==IOCTL_SHOW_ALL)
	{
		CLocker													Locker(State->MLock);

		{
			State->MFiles.Clear();
		}

		Information=0;
		Status=STATUS_SUCCESS;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! CALLBACK FUNCTION urcuje ku ktorym VOLUMES sa ma FILE SYSTEM MINI FILTER pripojit.
NTSTATUS FileSytemMiniFilterInstanceSetup(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_SETUP_FLAGS Flags, DEVICE_TYPE VolumeDeviceType, FLT_FILESYSTEM_TYPE VolumeFilesystemType)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);
	UNREFERENCED_PARAMETER(VolumeDeviceType);

	const char*													FunctionName=__FUNCTION__;

#ifdef DUMP_FUNCTIONS
	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionName));
#endif

	if (VolumeFilesystemType==FLT_FSTYPE_NTFS)
	{
		if (FltObjects->Volume!=nullptr)
		{
			NTSTATUS											Status;
			ULONG												BufferSize;

			Status=FltGetVolumeName(FltObjects->Volume,nullptr,&BufferSize);

			if (NT_SUCCESS(Status)!=false || Status==STATUS_BUFFER_TOO_SMALL)
			{
				PWCH											Buffer=(PWCH)ExAllocatePool2(POOL_FLAG_PAGED,BufferSize,MY_TAG);

				if (Buffer!=nullptr)
				{
					UNICODE_STRING								VolumeName;

					VolumeName.Length=(USHORT)BufferSize;
					VolumeName.MaximumLength=(USHORT)BufferSize;
					VolumeName.Buffer=Buffer;

					Status=FltGetVolumeName(FltObjects->Volume,&VolumeName,nullptr);

					if (NT_SUCCESS(Status)!=false)
					{
						KdPrint(("!!!!! FUNCTION [%s] ATTACHING to VOLUE [%wZ] !!!\n",FunctionName,VolumeName));
					}
					else
					{
						KdPrint(("!!!!! FUNCTION [%s] FAILED to GET VOLUME NAME with ERROR CODE [%lX] !!!\n",FunctionName,Status));
					}

					ExFreePoolWithTag(Buffer,MY_TAG);
				}
				else
				{
					KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE BUFFER for VOLUME NAME !!!\n",FunctionName));
				}
			}
			else
			{
				KdPrint(("!!!!! FUNCTION [%s] FAILED to GET VOLUME NAME SIZE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
			}
		}

		return(STATUS_SUCCESS);
	}
	else
	{
		return(STATUS_FLT_DO_NOT_ATTACH);
	}
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS FileSytemMiniFilterInstanceQueryTeardown(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);

#ifdef DUMP_FUNCTIONS
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionName));
#endif

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
VOID FileSytemMiniFilterInstanceTeardownStart(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_TEARDOWN_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);

#ifdef DUMP_FUNCTIONS
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionName));
#endif
}
//----------------------------------------------------------------------------------------------------------------------
VOID FileSytemMiniFilterInstanceTeardownComplete(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_TEARDOWN_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);

#ifdef DUMP_FUNCTIONS
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionName));
#endif
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS FileSytemMiniFilterUnload(FLT_FILTER_UNLOAD_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(Flags);

	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",State->MDriverObject->DriverName));

	UNICODE_STRING												SymbolicLink;

	WCHAR														Instance[]=MY_DRIVER_NAME L"DefaultInstance";

	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(State->MDriverObject->DeviceObject);

	FltUnregisterFilter(State->MFilter);
	State->MFilter=nullptr;

	NTSTATUS													Status=MiniFilterRegistryHelpers.DeleteRegistryKeys(Instance);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER KEYS from REGISTRY with ERROR CODE [%lX] !!!\n",State->MDriverObject->DriverName,Status));
	}

	UNICODE_STRING&												DriverName=State->MDriverObject->DriverName;

	if (State!=nullptr)
	{
		delete(State);
		State=nullptr;
	}

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",DriverName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchRoutineDeviceControl;

	WCHAR														Instance[]=MY_DRIVER_NAME L"DefaultInstance";
	WCHAR														Altitude[]=L"425342";

	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	NTSTATUS													Status;
	PDEVICE_OBJECT												DeviceObject=nullptr;
	bool														RegistryKeyCreated=false;
	bool														SymbolicLinkCreated=false;

	do
	{
		State=new(EPoolType::NonPaged,MY_TAG) CFilterState(DriverObject);

		if (State==nullptr)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to ALLOCATE MEMORY for STATE OBJECT !!!\n",DriverObject->DriverName));

			Status=STATUS_NO_MEMORY;
			break;
		}

		Status=MiniFilterRegistryHelpers.CreateRegistryKeys(RegistryPath,Instance,sizeof(Instance),Altitude,sizeof(Altitude),0);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER KEYS into REGISTRY with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		RegistryKeyCreated=true;

		const FLT_OPERATION_REGISTRATION						Callbacks[]=
		{
			{ IRP_MJ_DIRECTORY_CONTROL, 0, OnPreDirectoryControl, OnPostDirectoryControl },
			{IRP_MJ_OPERATION_END}
		};

		const FLT_REGISTRATION									Registration=
		{
			sizeof(FLT_REGISTRATION),
			FLT_REGISTRATION_VERSION,
			0,
			nullptr,
			Callbacks,
			FileSytemMiniFilterUnload,
			FileSytemMiniFilterInstanceSetup,
			FileSytemMiniFilterInstanceQueryTeardown,
			FileSytemMiniFilterInstanceTeardownStart,
			FileSytemMiniFilterInstanceTeardownComplete,
		};

		Status=FltRegisterFilter(DriverObject,&Registration,&State->MFilter);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER FILE SYSTEM MINI FILTER with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		Status=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK [%wZ] with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,SymbolicLink,Status));
			break;
		}

		SymbolicLinkCreated=true;

		Status=FltStartFiltering(State->MFilter);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to START FILTERING with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to START !!!\n",DriverObject->DriverName));

		if (SymbolicLinkCreated==true)
		{
			IoDeleteSymbolicLink(&SymbolicLink);
		}

		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}

		if (State->MFilter!=nullptr)
		{
			FltUnregisterFilter(State->MFilter);
			State->MFilter=nullptr;
		}

		if (RegistryKeyCreated==true)
		{
			NTSTATUS											LocalStatus=MiniFilterRegistryHelpers.DeleteRegistryKeys(Instance);

			if (NT_SUCCESS(LocalStatus)==false)
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER KEYS from REGISTRY with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,LocalStatus));
			}
		}

		if (State!=nullptr)
		{
			delete(State);
			State=nullptr;
		}
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------