//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CExecutiveResourceGlobal.h"
#include "Helpers\CFastMutexGlobal.h"
#include "Helpers\CLookasideListGlobal.h"
#include "Helpers\CLocker.h"
#include "Helpers\CSharedLocker.h"
#include "SharedHeader.h"
#include "SRemoteThreadItem.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PREPROCESSOR DEFINITION [IS_KERNEL] must be defined.
// !!!!! DRIVER, ktory pouziva PROCESS NOTIFICATION MUSI mat v PE FILE povoleny FLAG [IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY]. To sa robi pridanim COMMAND [/integritycheck] do LINKER COMMAND LINE.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
constexpr size_t												MAX_PROCESSES=32;
//----------------------------------------------------------------------------------------------------------------------
ULONG															NewProcesses[MAX_PROCESSES];
size_t															NewProcessesCount;
CExecutiveResourceGlobal										ProcessesLock;
LIST_ENTRY														RemoteThreadsHead;
CFastMutexGlobal												RemoteThreadsLock;
CLookasideListGlobal<SRemoteThreadItem>							Lookaside;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool FindProcess(HANDLE PID)
{
	ULONG														ID=HandleToUlong(PID);
	CSharedLocker												Locker(ProcessesLock);

	{
		for (size_t Index=0;Index<MAX_PROCESSES;Index++)
		{
			if (NewProcesses[Index]==ID)
			{
				return(true);
			}
		}

		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
bool AddNewProcess(HANDLE PID)
{
	CSharedLocker												Locker(ProcessesLock);

	{
		if (NewProcessesCount==MAX_PROCESSES)
		{
			return(false);
		}

		for (size_t Index=0;Index<MAX_PROCESSES;Index++)
		{
			if (NewProcesses[Index]==0)
			{
				NewProcesses[Index]=HandleToUlong(PID);
				break;
			}
		}

		NewProcessesCount++;
	}

	return(true);
}
//----------------------------------------------------------------------------------------------------------------------
bool RemoveProcess(HANDLE PID)
{
	ULONG														ID=HandleToUlong(PID);
	CSharedLocker												Locker(ProcessesLock);

	{
		for (size_t Index=0;Index<MAX_PROCESSES;Index++)
		{
			if (NewProcesses[Index]==ID)
			{
				NewProcesses[Index]=0;
				NewProcessesCount--;

				return(true);
			}
		}

		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void OnProcessNotify(PEPROCESS Process, HANDLE ProcessID, PPS_CREATE_NOTIFY_INFO CreateInfo)
{
	UNREFERENCED_PARAMETER(Process);

	if (CreateInfo!=nullptr)
	{
		bool													Result=AddNewProcess(ProcessID);

		if (Result==true)
		{
			ULONG												ProcessIDAsULONG=HandleToULong(ProcessID);

			KdPrint(("!!!!! NEW PROCESS ADDED [%u].\n",ProcessIDAsULONG));
		}
		else
		{
			KdPrint(("!!!!! NEW PROCES CREATED, but no ROOM to STORE.\n"));
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
void OnThreadNotify(HANDLE ProcessID, HANDLE ThreadID, BOOLEAN Create)
{
	if (Create==TRUE)
	{
		bool													Remote=(PsGetCurrentProcessId()!=ProcessID && PsInitialSystemProcess!=PsGetCurrentProcess() && PsGetProcessId(PsInitialSystemProcess)!=ProcessID);

		if (Remote==true)
		{
			bool												Found=FindProcess(ProcessID);

			if (Found==true)
			{
				// !!!!! FIRST THREAD in PROCESS.
				bool											Result(ProcessID);

				if (Result==true)
				{
					ULONG										ProcessIDAsULONG=HandleToULong(ProcessID);
					ULONG										ThreadIDAsULONG=HandleToULong(ThreadID);

					KdPrint(("!!!!! PROCESS [%u] REMOVED because FIRST THREAD [%u] DETECTED.\n",ProcessIDAsULONG,ThreadIDAsULONG));
				}
				else
				{
					KdPrint(("!!!!! PROCESS FAILED to REMOVE.\n"));
				}
			}
			else
			{
				SRemoteThreadItem*								Item=Lookaside.Alloc();
				SRemoteThread&									Data=Item->MRemote;

				KeQuerySystemTimePrecise(&Data.MTime);

				Data.MCreatorProcessID=HandleToULong(PsGetCurrentProcessId());
				Data.MCreatorThreadID=HandleToULong(PsGetCurrentThreadId());
				Data.MProcessID=HandleToULong(ProcessID);
				Data.MThreadID=HandleToULong(ThreadID);
				
				KdPrint(("!!!!! REMOTE THREAD DETECTED. CREATOR PROCESS ID [%u] CREATOR THREAD [%u] PROCESS ID [%u] THREAD [%u].\n",Data.MCreatorProcessID,Data.MCreatorThreadID,Data.MProcessID,Data.MThreadID));

				CLocker											Locker(RemoteThreadsLock);
				{
					InsertTailList(&RemoteThreadsHead,&Item->MLink);
				}
			}
		}
	}
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
NTSTATUS DispatchRoutineRead(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													NumberOfBytesRead=0;

	PIO_STACK_LOCATION											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

	ULONG														ReadBufferSize=CurrentStackLocation->Parameters.Read.Length;
	PUCHAR														ReadBuffer=(PUCHAR)MmGetSystemAddressForMdlSafe(Irp->MdlAddress,NormalPagePriority);

	if (ReadBuffer!=nullptr)
	{
		CLocker													Locker(RemoteThreadsLock);

		while(true)
		{
			if (IsListEmpty(&RemoteThreadsHead)!=FALSE)
			{
				break;
			}

			if (ReadBufferSize<sizeof(SRemoteThread))
			{
				break;
			}

			PLIST_ENTRY											Entry=RemoveHeadList(&RemoteThreadsHead);
			SRemoteThreadItem*									Info=CONTAINING_RECORD(Entry,SRemoteThreadItem,MLink);
			ULONG												Size=sizeof(SRemoteThread);

			memcpy(ReadBuffer,&Info->MRemote,Size);

			ReadBufferSize-=Size;
			ReadBuffer+=Size;
			NumberOfBytesRead+=Size;

			Lookaside.Free(Info);
		}
	}
	else
	{
		KdPrint(("Can't MAP MDL ADDRESS.\n"));

		Status=STATUS_INSUFFICIENT_RESOURCES;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,NumberOfBytesRead);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	UNICODE_STRING												SymbolicLink;
	NTSTATUS													Status;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	Status=PsRemoveCreateThreadNotifyRoutine(OnThreadNotify);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER THREAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
	}

	Status=PsSetCreateProcessNotifyRoutineEx(OnProcessNotify,TRUE);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER PROCESS NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
	}

	Lookaside.Delete();

	ProcessesLock.Delete();

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(DriverObject->DeviceObject);

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING)
{
	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	NTSTATUS													Status=STATUS_SUCCESS;
	PDEVICE_OBJECT												DeviceObject=nullptr;
	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	bool														SymbolicLinkCreated=false;
	bool														ProcessCallbacksCreated=false;

	do
	{
		Status=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,TRUE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		DeviceObject->Flags|=DO_DIRECT_IO;

		Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK [%wZ] with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,SymbolicLink,Status));
			break;
		}

		SymbolicLinkCreated=true;

		Status=PsSetCreateProcessNotifyRoutineEx(OnProcessNotify,FALSE);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER PROCESS NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		ProcessCallbacksCreated=true;

		Status=PsSetCreateThreadNotifyRoutine(OnThreadNotify);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER THREAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
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

		if (ProcessCallbacksCreated==true)
		{
			PsSetCreateProcessNotifyRoutineEx(OnProcessNotify,TRUE);
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

		return(Status);
	}

	ProcessesLock.Init();
	Lookaside.Init(PagedPool,MY_TAG);
	InitializeListHead(&RemoteThreadsHead);
	RemoteThreadsLock.Init();

	DriverObject->DriverUnload=FunctionDriverUnload;
	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_READ]=DispatchRoutineRead;

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------