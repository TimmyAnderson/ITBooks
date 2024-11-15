//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <fltKernel.h>
#include "SharedHeader.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CFilterFileNameInformation.h"
#include "Helpers\CMiniFilterRegistryHelpers.h"
#include "TestCallbacksNoPostOperation.h"
#include "TestCallbacksWithPostOperation.h"
#include "TestCallbacksPendingPreOperation.h"
#include "TestCallbacksPendingSafePostOperation.h"
#include "TestCallbacksPendingWorkItemPostOperation.h"
#include "TestCallbacksSendNoReplyMessage.h"
#include "TestCallbacksSendRequestReplyMessage.h"
#include "TestFileOperations.h"
#include "SPortClientToDriverNoReplyRequest.h"
#include "SPortClientToDriverRequestReplyRequest.h"
#include "SPortClientToDriverRequestReplyReply.h"
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
PFLT_PORT														Port=nullptr;
PFLT_PORT														ClientPort=nullptr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS PortConnectNotify(PFLT_PORT LocalClientPort, PVOID ServerPortCookie, PVOID ConnectionContext, ULONG SizeOfContext, PVOID* ConnectionPortCookie)
{
	UNREFERENCED_PARAMETER(ServerPortCookie);
	UNREFERENCED_PARAMETER(ConnectionContext);
	UNREFERENCED_PARAMETER(SizeOfContext);
	UNREFERENCED_PARAMETER(ConnectionPortCookie);

	const char*													FunctionName=__FUNCTION__;

	// !!! Ulozi sa CLIENT PORT HANDLE do VARIABLE.
	ClientPort=LocalClientPort;

	KdPrint(("!!!!! FUNCTION [%s] REGISTERED FILTER COMMUNICATION PORT CLIENT !!!\n",FunctionName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void PortDisconnectNotify(PVOID ConnectionCookie)
{
	UNREFERENCED_PARAMETER(ConnectionCookie);

	const char*													FunctionName=__FUNCTION__;

	// !!! Uvolni sa CLIENT PORT HANDLE.
	FltCloseClientPort(Filter,&ClientPort);
	ClientPort=nullptr;

	KdPrint(("!!!!! FUNCTION [%s] UNREGISTERED FILTER COMMUNICATION PORT CLIENT !!!\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS PortMessageNotify(PVOID PortCookie, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength, PULONG ReturnOutputBufferLength)
{
	UNREFERENCED_PARAMETER(PortCookie);

	const char*													FunctionName=__FUNCTION__;

	// !!! Spracovanie USER MODE BUFFER MUSI byt v TRY CATCH BLOCK.
	__try
	{
		if (InputBufferLength>=sizeof(SPortClientToDriverBase))
		{
			// !!!!! FUNCTION hodi EXCEPTION, ak je BUFFER nevalidny.
			ProbeForRead(InputBuffer,InputBufferLength,1);

			SPortClientToDriverBase*							TypedInputBuffer=(SPortClientToDriverBase*) InputBuffer;
			EPortClientToDriverMessageType						MessageType=TypedInputBuffer->MMessageType;

			if (MessageType==EPortClientToDriverMessageType::E_NO_REPLY)
			{
				if (InputBufferLength>=sizeof(SPortClientToDriverNoReplyRequest))
				{
					SPortClientToDriverNoReplyRequest*			Request=(SPortClientToDriverNoReplyRequest*) TypedInputBuffer;
					ULONG										Value=Request->MValue;

					KdPrint(("!!!!!!!!!! ROUTINE [%s] - NO REPLY REQUEST MESSAGE with VALUE [%lu] ARRIVED.\n",FunctionName,Value));
				}
			}
			else if (MessageType==EPortClientToDriverMessageType::E_REQUEST_REPLY)
			{
				if (InputBufferLength>=sizeof(SPortClientToDriverRequestReplyRequest))
				{
					SPortClientToDriverRequestReplyRequest*		Request=(SPortClientToDriverRequestReplyRequest*) TypedInputBuffer;
					ULONG										Value=Request->MValue;

					KdPrint(("!!!!!!!!!! ROUTINE [%s] - REQUEST REPLY REQUEST MESSAGE with VALUE [%lu] ARRIVED.\n",FunctionName,Value));

					if (OutputBufferLength>=sizeof(SPortClientToDriverRequestReplyReply))
					{
						// !!!!! FUNCTION hodi EXCEPTION, ak je BUFFER nevalidny.
						ProbeForWrite(OutputBuffer,OutputBufferLength,1);

						SPortClientToDriverRequestReplyReply*	Reply=(SPortClientToDriverRequestReplyReply*) OutputBuffer;

						Reply->MValue1=Value;
						Reply->MValue2=(Value*2);

						*ReturnOutputBufferLength=sizeof(SPortClientToDriverRequestReplyReply);

						KdPrint(("!!!!!!!!!! ROUTINE [%s] - REQUEST REPLY REPLY MESSAGE with VALUE 1 [%lu] VALUE 2 [%lu] is SENT to CLIENT.\n",FunctionName,Reply->MValue1,Reply->MValue2));
					}
				}
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
	}

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS FileSytemMiniFilterPreCreate(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

#ifdef DUMP_FUNCTIONS
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionName));
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
				if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_NO_POST_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksNoPostOperationPreOperation(FileNameInformation);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_WITH_POST_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksWithPostOperationPreOperation(FileNameInformation);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_PENDING_PRE_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksPendingPreOperationPreOperation(FileNameInformation,Data,GlobalDriverObject->DeviceObject);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_PENDING_SAFE_POST_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksPendingSafePostOperationPreOperation(FileNameInformation);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_PENDING_WORK_ITEM_POST_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksPendingWorkItemPostOperationPreOperation(FileNameInformation);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_SEND_NO_REPLY_MESSAGE)==true)
				{
					CallbackStatus=TestCallbacksSendNoReplyMessagePreOperation(FileNameInformation,Filter,ClientPort);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_SEND_REQUEST_REPLY_MESSAGE)==true)
				{
					CallbackStatus=TestCallbacksSendRequestReplyMessagePreOperation(FileNameInformation,Filter,ClientPort);
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
FLT_POSTOP_CALLBACK_STATUS FileSytemMiniFilterPostCreate(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID CompletionContext, FLT_POST_OPERATION_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

#ifdef DUMP_FUNCTIONS
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionName));
#endif

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
				if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_NO_POST_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksNoPostOperationPostOperation(FileNameInformation);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_WITH_POST_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksWithPostOperationPostOperation(FileNameInformation);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_PENDING_PRE_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksPendingPreOperationPostOperation(FileNameInformation);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_PENDING_SAFE_POST_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksPendingSafePostOperationPostOperation(FileNameInformation,Data,FltObjects,Flags);
				}
				else if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_CALLBACKS_PENDING_WORK_ITEM_POST_OPERATION)==true)
				{
					CallbackStatus=TestCallbacksPendingWorkItemPostOperationPostOperation(FileNameInformation,Data,CompletionContext,Flags);
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
FLT_PREOP_CALLBACK_STATUS FileSytemMiniFilterPreSetInformation(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext)
{
	UNREFERENCED_PARAMETER(Data);
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

#ifdef DUMP_FUNCTIONS
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionName));
#endif

	return(FLT_PREOP_SUCCESS_NO_CALLBACK);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS FileSytemMiniFilterPreRead(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

#ifdef DUMP_FUNCTIONS
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! FUNCTION [%s] CALLED !!!\n",FunctionName));
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
				if (CHelpers::FindFirstString(FileNameInformation->Name,TEST_FILE_NAME_FILE_OPERATIONS)==true)
				{
					CallbackStatus=TestFileOperationsPreReadOperation(FltObjects,FileNameInformation);
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

	if (Port!=nullptr)
	{
		FltCloseCommunicationPort(Port);
		Port=nullptr;
	}

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
			{ IRP_MJ_CREATE, 0, FileSytemMiniFilterPreCreate, FileSytemMiniFilterPostCreate },
			{ IRP_MJ_SET_INFORMATION, 0, FileSytemMiniFilterPreSetInformation, nullptr },
			{ IRP_MJ_READ, 0, FileSytemMiniFilterPreRead, nullptr },
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

		UNICODE_STRING											Name=RTL_CONSTANT_STRING(L"\\" COMMUNICATION_PORT_NAME);
		PSECURITY_DESCRIPTOR									SecurityDesciptor;

		Status=FltBuildDefaultSecurityDescriptor(&SecurityDesciptor,FLT_PORT_ALL_ACCESS);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to BUILD SECURITY DESCRIPTOR with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		OBJECT_ATTRIBUTES										Attributes;

		InitializeObjectAttributes(&Attributes,&Name,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,nullptr,SecurityDesciptor);

		Status=FltCreateCommunicationPort(Filter,&Port,&Attributes,nullptr,PortConnectNotify,PortDisconnectNotify,PortMessageNotify,1);

		FltFreeSecurityDescriptor(SecurityDesciptor);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE COMMUNICATION PORT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

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

		if (Port!=nullptr)
		{
			FltCloseCommunicationPort(Port);
			Port=nullptr;
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