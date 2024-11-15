//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <fltKernel.h>
#include "SharedHeader.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CFilterFileNameInformation.h"
#include "Helpers\CMiniFilterRegistryHelpers.h"
#include "Helpers\CLocker.h"
#include "Helpers\CSharedLocker.h"
#include "SFilterState.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE SYSTEM MINI FILTERS MUSIA mat vlozenu LIBRARY [FltMgr.lib].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_SET_EXTENSIONS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SET_EXTENSIONS,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PDRIVER_OBJECT													GlobalDriverObject;
PFLT_FILTER														Filter=nullptr;
CMiniFilterRegistryHelpers										MiniFilterRegistryHelpers;
SFilterState													FilterState;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool IsDeleteAllowed(PCUNICODE_STRING Filename)
{
	CSharedLocker												Locker(FilterState.MLock);

	{
		NTSTATUS												Status;
		UNICODE_STRING											Extension{};

		Status=FltParseFileName(Filename,&Extension,nullptr,nullptr);

		if (NT_SUCCESS(Status)==true)
		{
			WCHAR												UpperCaseExtensionBuffer[16]={0};
			UNICODE_STRING										UpperCaseExtension;

			UpperCaseExtension.Buffer=UpperCaseExtensionBuffer;
			UpperCaseExtension.MaximumLength=(sizeof(UpperCaseExtensionBuffer)-(2*sizeof(WCHAR)));

			RtlUpcaseUnicodeString(&UpperCaseExtension,&Extension,FALSE);

			RtlAppendUnicodeToString(&UpperCaseExtension,L";");

			wchar_t*											Found=wcsstr(FilterState.MExtentions.Buffer,UpperCaseExtensionBuffer);

			if (Found==nullptr)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		else
		{
			KdPrint(("!!!!! FILENAME FAILED to PARSE with ERROR CODE [%lX] !!!\n",Status));

			return(true);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILES su spravidla DELETED tak, ze pri otvoreni HANDLE je nastaveny FLAG [FILE_DELETE_ON_CLOSE]. Tento FLAG urcuje, ze sa FILE po uzatvoreni HANDLE ma automaticky vymazat.
// !!!!! Tento sposob DELETE FILE pouziva FUNCTION [DeleteFile()].
FLT_PREOP_CALLBACK_STATUS FileSytemMiniFilterPreCreate(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext)
{
	UNREFERENCED_PARAMETER(CompletionContext);
	
	if (Data->RequestorMode==KernelMode)
	{
		return(FLT_PREOP_SUCCESS_NO_CALLBACK);
	}

	const auto&													Parameters=Data->Iopb->Parameters.Create;
	FLT_PREOP_CALLBACK_STATUS									Result=FLT_PREOP_SUCCESS_NO_CALLBACK;

	// !!! Overi sa ze IRP obsahuje FLAG [FILE_DELETE_ON_CLOSE].
	if ((Parameters.Options & FILE_DELETE_ON_CLOSE)!=0)
	{
		UNICODE_STRING&											Filename=FltObjects->FileObject->FileName;

		KdPrint(("DELETE of FILE [%wZ] on CLOSE.\n",Filename));

		if (IsDeleteAllowed(&Filename)==false)
		{
			KdPrint(("FILE [%wZ] was PREVENTED from DELETION on CLOSE.\n",Filename));

			// !!!!! Nastavi sa vysledky STATUS IO OPERATION.
			Data->IoStatus.Status=STATUS_ACCESS_DENIED;

			// !!!!! Ak FILE NEMA byt DELETED, tak sa zabrani pokracovaniu IO OPERATION vratenim RETURN VALUE [FLT_PREOP_COMPLETE].
			Result=FLT_PREOP_COMPLETE;
		}
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILES mozu byt DELETED aj pomocou FUNCTION [SetFileInformationByHandle()], ktora odosle IRP [IRP_MJ_SET_INFORMATION] do FILE SYSTEM MINI FILTER.
FLT_PREOP_CALLBACK_STATUS FileSytemMiniFilterPreSetInformation(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

	if (Data->RequestorMode==KernelMode)
	{
		return(FLT_PREOP_SUCCESS_NO_CALLBACK);
	}

	FLT_PREOP_CALLBACK_STATUS									Result=FLT_PREOP_SUCCESS_NO_CALLBACK;
	auto&														Parameters=Data->Iopb->Parameters.SetFileInformation;

	// !!! Vykona sa kontrola ci sa pozaduje IO OPERATION DELETE FILE.
	if (Parameters.FileInformationClass==FileDispositionInformation || Parameters.FileInformationClass==FileDispositionInformationEx)
	{
		// !!! Pri IO OPERATION DELETE FILE FIELD [Parameters.InfoBuffer] je TYPE [FILE_DISPOSITION_INFORMATION*].
		FILE_DISPOSITION_INFORMATION*							Information=((FILE_DISPOSITION_INFORMATION*)Parameters.InfoBuffer);

		// !!! Overi sa ze IRP obsahuje poziadavku na DELETE FILE.
		if (Information->DeleteFile!=FALSE)
		{	
			PFLT_FILE_NAME_INFORMATION							FileNameInformation;
			NTSTATUS											Status=FltGetFileNameInformation(Data,FLT_FILE_NAME_QUERY_DEFAULT | FLT_FILE_NAME_NORMALIZED,&FileNameInformation);

			if (NT_SUCCESS(Status)==true)
			{
				if (IsDeleteAllowed(&FileNameInformation->Name)==false)
				{
					KdPrint(("FILE [%wZ] was PREVENTED from DELETION.\n",FileNameInformation->Name));

					// !!!!! Nastavi sa vysledky STATUS IO OPERATION.
					Data->IoStatus.Status=STATUS_ACCESS_DENIED;

					// !!!!! Ak FILE NEMA byt DELETED, tak sa zabrani pokracovaniu IO OPERATION vratenim RETURN VALUE [FLT_PREOP_COMPLETE].
					Result=FLT_PREOP_COMPLETE;
				}

				FltReleaseFileNameInformation(FileNameInformation);
			}
		}
	}

	return(Result);
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

	if (Code==IOCTL_SET_EXTENSIONS)
	{
		WCHAR*													Extensions=((WCHAR*)Irp->AssociatedIrp.SystemBuffer);
		ULONG													ExtensionsLength=Parameters.InputBufferLength;

		do
		{
			if (Extensions==nullptr || ExtensionsLength<sizeof(WCHAR) * 2 || Extensions[(ExtensionsLength/sizeof(WCHAR))-1]!=0)
			{
				Status=STATUS_INVALID_PARAMETER;
				break;
			}

			CLocker												Locker(FilterState.MLock);

			{
				if (FilterState.MExtentions.MaximumLength<(ExtensionsLength-sizeof(WCHAR)))
				{
					PVOID										Buffer=ExAllocatePool2(POOL_FLAG_PAGED,ExtensionsLength,MY_TAG);

					if (Buffer==nullptr)
					{
						KdPrint(("!!!!! DRIVER FAILED to ALLOCATE MEMORY for LIST of EXTENSIONS !!!\n"));

						Status=STATUS_INSUFFICIENT_RESOURCES;
						break;
					}

					FilterState.MExtentions.MaximumLength=((USHORT)ExtensionsLength);

					ExFreePool(FilterState.MExtentions.Buffer);

					FilterState.MExtentions.Buffer=((PWSTR)Buffer);
				}

				UNICODE_STRING									UpperCaseExtensions;

				RtlInitUnicodeString(&UpperCaseExtensions,Extensions);

				RtlUpcaseUnicodeString(&UpperCaseExtensions,&UpperCaseExtensions,FALSE);

				memcpy(FilterState.MExtentions.Buffer,Extensions,ExtensionsLength);

				Information=ExtensionsLength;

				FilterState.MExtentions.Length=((USHORT)ExtensionsLength);
			}

			Status=STATUS_SUCCESS;
		}
		while(false);
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

	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",GlobalDriverObject->DriverName));

	UNICODE_STRING												SymbolicLink;

	WCHAR														Instance[]=MY_DRIVER_NAME L"DefaultInstance";

	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(GlobalDriverObject->DeviceObject);

	FltUnregisterFilter(Filter);
	Filter=nullptr;

	NTSTATUS													Status=MiniFilterRegistryHelpers.DeleteRegistryKeys(Instance);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER KEYS from REGISTRY with ERROR CODE [%lX] !!!\n",GlobalDriverObject->DriverName,Status));
	}

	if (FilterState.MExtentions.Buffer!=nullptr)
	{
		ExFreePoolWithTag(FilterState.MExtentions.Buffer,MY_TAG);
		FilterState.MExtentions.Buffer=nullptr;
		FilterState.MExtentions.Length=0;
		FilterState.MExtentions.MaximumLength=0;
	}

	FilterState.MLock.Delete();

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",GlobalDriverObject->DriverName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	GlobalDriverObject=DriverObject;

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
		FilterState.MLock.Init();

		WCHAR													Extensions[]=L";";

		FilterState.MExtentions.Buffer=(PWSTR)ExAllocatePool2(POOL_FLAG_PAGED,sizeof(Extensions),MY_TAG);

		if (FilterState.MExtentions.Buffer==nullptr)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to ALLOCATE MEMORY for LIST of EXTENSIONS !!!\n",DriverObject->DriverName));

			Status=STATUS_NO_MEMORY;
			break;
		}

		memcpy(FilterState.MExtentions.Buffer,Extensions,sizeof(Extensions));

		FilterState.MExtentions.Length=sizeof(Extensions);
		FilterState.MExtentions.MaximumLength=sizeof(Extensions);

		Status=MiniFilterRegistryHelpers.CreateRegistryKeys(RegistryPath,Instance,sizeof(Instance),Altitude,sizeof(Altitude),0);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER KEYS into REGISTRY with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		RegistryKeyCreated=true;

		const FLT_OPERATION_REGISTRATION						Callbacks[]=
		{
			{ IRP_MJ_CREATE, 0, FileSytemMiniFilterPreCreate, nullptr },
			{ IRP_MJ_SET_INFORMATION, 0, FileSytemMiniFilterPreSetInformation, nullptr },
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

		Status=FltRegisterFilter(DriverObject,&Registration,&Filter);

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

		Status=FltStartFiltering(Filter);

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

		if (Filter!=nullptr)
		{
			FltUnregisterFilter(Filter);
			Filter=nullptr;
		}

		if (RegistryKeyCreated==true)
		{
			NTSTATUS											LocalStatus=MiniFilterRegistryHelpers.DeleteRegistryKeys(Instance);

			if (NT_SUCCESS(LocalStatus)==false)
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER KEYS from REGISTRY with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,LocalStatus));
			}
		}

		if (FilterState.MExtentions.Buffer!=nullptr)
		{
			ExFreePoolWithTag(FilterState.MExtentions.Buffer,MY_TAG);
			FilterState.MExtentions.Buffer=nullptr;
			FilterState.MExtentions.Length=0;
			FilterState.MExtentions.MaximumLength=0;
		}

		FilterState.MLock.Delete();
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------