//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <fltKernel.h>
#include "SharedHeader.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CFilterFileNameInformation.h"
#include "Helpers\CMiniFilterRegistryHelpers.h"
#include "TestFixedSizedContext.h"
#include "TestVariableSizedContext.h"
#include "SFixedContext.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE SYSTEM MINI FILTERS MUSIA mat vlozenu LIBRARY [FltMgr.lib].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PDRIVER_OBJECT													GlobalDriverObject;
PFLT_FILTER														Filter=nullptr;
CMiniFilterRegistryHelpers										MiniFilterRegistryHelpers;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//#define														DUMP_ERRORS
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PVOID MyContextAllocateCallback(POOL_TYPE PoolType, SIZE_T Size, FLT_CONTEXT_TYPE ContextType)
{
	POOL_FLAGS													Flags=0;

	if (PoolType==POOL_TYPE::PagedPool)
	{
		Flags=POOL_FLAG_PAGED;
	}
	else if (PoolType==POOL_TYPE::NonPagedPool)
	{
		Flags=POOL_FLAG_NON_PAGED;
	}

	void*														Buffer=ExAllocatePool2(Flags,Size,MY_TAG);

	KdPrint(("!!!!!!!!!! CONTEXT MEMORY ALLOCATED - SIZE [%I64u] POOL TYPE [%I64u] BUFFER [%p] CONTEXT TYPE [%hu] !!!\n",Size,Flags,Buffer,ContextType));

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
void MyContextFreeCallback(PVOID Pool, FLT_CONTEXT_TYPE ContextType)
{
	KdPrint(("!!!!!!!!!! CONTEXT MEMORY FREED - BUFFER [%p] CONTEXT TYPE [%hu] !!!\n",Pool,ContextType));

	ExFreePoolWithTag(Pool,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
void MyContextCleanupCallback(PFLT_CONTEXT Context, FLT_CONTEXT_TYPE ContextType)
{
	KdPrint(("!!!!!!!!!! CONTEXT MEMORY CLEANUP - CONTEXT [%p] CONTEXT TYPE [%hu] !!!\n",Context,ContextType));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS ContextPostCreate(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID CompletionContext, FLT_POST_OPERATION_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(CompletionContext);
	UNREFERENCED_PARAMETER(Flags);

#ifdef DUMP_ERRORS
	const char*													FunctionNameErrors=__FUNCTION__;
#endif

	FLT_POSTOP_CALLBACK_STATUS									CallbackStatus=FLT_POSTOP_FINISHED_PROCESSING;

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
				if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_FIXED_SIZED_CONTEXT)==true)
				{
					CallbackStatus=TestFixedSizedContextPostCreate(FileNameInformation,FltObjects);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_VARIABLE_SIZED_CONTEXT)==true)
				{
					CallbackStatus=TestVariableSizedContextPostCreate(FileNameInformation,FltObjects);
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
FLT_PREOP_CALLBACK_STATUS ContextPreRead(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext)
{
	UNREFERENCED_PARAMETER(CompletionContext);

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
				if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_FIXED_SIZED_CONTEXT)==true)
				{
					CallbackStatus=TestFixedSizedContextPreRead(FileNameInformation,FltObjects);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_VARIABLE_SIZED_CONTEXT)==true)
				{
					CallbackStatus=TestVariableSizedContextPreRead(FileNameInformation,FltObjects);
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
FLT_POSTOP_CALLBACK_STATUS ContextPostRead(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID CompletionContext, FLT_POST_OPERATION_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(CompletionContext);
	UNREFERENCED_PARAMETER(Flags);

#ifdef DUMP_ERRORS
	const char*													FunctionNameErrors=__FUNCTION__;
#endif

	FLT_POSTOP_CALLBACK_STATUS									CallbackStatus=FLT_POSTOP_FINISHED_PROCESSING;

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
				if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_FIXED_SIZED_CONTEXT)==true)
				{
					CallbackStatus=TestFixedSizedContextPostRead(FileNameInformation,FltObjects);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_VARIABLE_SIZED_CONTEXT)==true)
				{
					CallbackStatus=TestVariableSizedContextPostRead(FileNameInformation,FltObjects);
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

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
VOID FileSytemMiniFilterInstanceTeardownStart(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_TEARDOWN_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);
}
//----------------------------------------------------------------------------------------------------------------------
VOID FileSytemMiniFilterInstanceTeardownComplete(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_TEARDOWN_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);
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
			{ IRP_MJ_CREATE, 0, nullptr, ContextPostCreate },
			{ IRP_MJ_READ, 0, ContextPreRead, ContextPostRead},
			{IRP_MJ_OPERATION_END}
		};

		// !!!!! Kazda STRUCTURE [FLT_CONTEXT_REGISTRATION] musi ma INU VALUE FIELD [FLT_CONTEXT_REGISTRATION::ContextType].
		const FLT_CONTEXT_REGISTRATION							Context[]=
		{
			// !!!!! Zaregistruje sa FIXED SIZED CONTEXT.
			{ FLT_STREAM_CONTEXT, 0, MyContextCleanupCallback, sizeof(SFixedContext), MY_TAG},
			// !!!!! Zaregistruje sa VARIABLE SIZED CONTEXT.
			{ FLT_FILE_CONTEXT, 0, MyContextCleanupCallback, FLT_VARIABLE_SIZED_CONTEXTS, 0, MyContextAllocateCallback, MyContextFreeCallback},
			{ FLT_CONTEXT_END }
		};

		const FLT_REGISTRATION									Registration=
		{
			sizeof(FLT_REGISTRATION),
			FLT_REGISTRATION_VERSION,
			0,
			Context,
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
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------