//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <fltKernel.h>
#include "SharedHeader.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CFilterFileNameInformation.h"
#include "Helpers\CMiniFilterRegistryHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE SYSTEM MINI FILTERS MUSIA mat vlozenu LIBRARY [FltMgr.lib].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//#define														DUMP_FUNCTIONS
//#define														DUMP_ERRORS
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PDRIVER_OBJECT													GlobalDriverObject;
PFLT_FILTER														Filter=nullptr;
CMiniFilterRegistryHelpers										MiniFilterRegistryHelpers;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS FileSytemMiniFilterPreCreate(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

#ifdef DUMP_FUNCTIONS
	const char*													FunctionNameFunctions=__FUNCTION__;

	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionNameFunctions));
#endif

#ifdef DUMP_ERRORS
	const char*													FunctionNameErrors=__FUNCTION__;
#endif

	FLT_PREOP_CALLBACK_STATUS									CallbackStatus=FLT_PREOP_SUCCESS_NO_CALLBACK;

	if (Data->RequestorMode==UserMode)
	{
		NTSTATUS												Status;

		// !!! NORMALIZED NAME obsahuje FULL PATH.
		CFilterFileNameInformation								FileNameInformation(Status,Data,EFileNameOptions::E_NORMALIZED | EFileNameOptions::E_QUERY_DEFAULT);

		if (NT_SUCCESS(Status)==true)
		{
			// !!! Naplni ostatne FIELDS STRUCTURE [FLT_FILE_NAME_INFORMATION].
			Status=FileNameInformation.Parse();

			if (NT_SUCCESS(Status)==true)
			{
				if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_FILTER_FILE_NAME_INFORMATION)==true)
				{
					const char*									FunctionName=__FUNCTION__;

					KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));
				}
			}
			else
			{
#ifdef DUMP_ERRORS
				KdPrint(("!!!!! FUNCTION [%s] FAILED to PARSE FILE/DIRECTORY NAME INFORMATION with ERROR CODE [%lX] !!!\n",FunctionNameErrors,Status));
#endif
			}
		}
		else
		{
#ifdef DUMP_ERRORS
			KdPrint(("!!!!! FUNCTION [%s] FAILED to GET FILE/DIRECTORY NAME INFORMATION with ERROR CODE [%lX] !!!\n",FunctionNameErrors,Status));
#endif
		}
	}

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS FileSytemMiniFilterPreSetInformation(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID*)
{
	UNREFERENCED_PARAMETER(Data);
	UNREFERENCED_PARAMETER(FltObjects);

#ifdef DUMP_FUNCTIONS
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionName));
#endif

	return(FLT_PREOP_SUCCESS_NO_CALLBACK);
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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

	FltUnregisterFilter(Filter);

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(GlobalDriverObject->DeviceObject);

	NTSTATUS													Status=MiniFilterRegistryHelpers.DeleteRegistryKeys(Instance);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER KEYS from REGISTRY with ERROR CODE [%lX] !!!\n",GlobalDriverObject->DriverName,Status));
	}

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

		if (Filter!=nullptr)
		{
			FltUnregisterFilter(Filter);
		}

		if (SymbolicLinkCreated==true)
		{
			IoDeleteSymbolicLink(&SymbolicLink);
		}

		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}

		if (RegistryKeyCreated==true)
		{
			NTSTATUS											LocalStatus=MiniFilterRegistryHelpers.DeleteRegistryKeys(Instance);

			if (NT_SUCCESS(LocalStatus)==false)
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER KEYS from REGISTRY with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,LocalStatus));
			}
		}
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------