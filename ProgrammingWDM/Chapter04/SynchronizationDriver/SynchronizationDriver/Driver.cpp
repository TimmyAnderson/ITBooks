//-------------------------------------------------------------------------------------------------------
// !!! HEADER [Ntddk.h] MUSI BYT PRED HEADER [wdm.h].
#include <Ntddk.h>
#include <wdm.h>
#include <initguid.h>
#include <Ntstrsafe.h>
//-------------------------------------------------------------------------------------------------------
#include "Defines.h"
#include "Driver.h"
#include "GUIDS.h"
#include "Macros.h"
//-------------------------------------------------------------------------------------------------------
#pragma warning(disable:4127)
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_UNLOAD)
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);
_Function_class_(DRIVER_ADD_DEVICE)
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PDO);
//-------------------------------------------------------------------------------------------------------
NTSTATUS __stdcall StartDevice(PDEVICE_OBJECT DeviceObject, PCM_PARTIAL_RESOURCE_LIST, PCM_PARTIAL_RESOURCE_LIST);
VOID __stdcall StopDevice(IN PDEVICE_OBJECT DeviceObject, BOOLEAN);
VOID __stdcall RemoveDevice(IN PDEVICE_OBJECT DeviceObject);
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CREATE)
NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLOSE)
NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_DEVICE_CONTROL)
NTSTATUS DispatchDeviceControl(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_POWER)
NTSTATUS DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_PNP)
NTSTATUS DispatchPNP(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SYSTEM_CONTROL)
NTSTATUS DispatchWMI(PDEVICE_OBJECT DeviceObject, PIRP IRP);
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_READ_FILE CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_THREAD_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_IRQL_CHANGE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x803,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SPIN_LOCK_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x804,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SPIN_LOCK_WITH_THREADS_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x805,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_QUEUED_SPIN_LOCK_WITH_THREADS_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x806,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_WAIT_FOR_MULTIPLE_OBJECTS_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x807,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_MANUAL_RESET_EVENT_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x808,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_AUTO_RESET_EVENT_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x809,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SEMAPHORE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x810,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_MUTEX_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x811,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_MANUAL_RESET_TIMER_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x812,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_AUTO_RESET_TIMER_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x813,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DPC_TIMER_1_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x814,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DPC_TIMER_2_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x815,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DPC_TIMER_3_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x816,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_APC_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x817,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_FAST_MUTEX_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x818,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_EXECUTIVE_RESOURCE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x819,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_INTERLOCKED_DOUBLY_LINKED_LIST CTL_CODE(FILE_DEVICE_UNKNOWN,0x820,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_INTERLOCKED_SINGLY_LINKED_LIST CTL_CODE(FILE_DEVICE_UNKNOWN,0x821,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_INTERLOCKED_ARITHMETIC_1 CTL_CODE(FILE_DEVICE_UNKNOWN,0x822,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_INTERLOCKED_ARITHMETIC_2 CTL_CODE(FILE_DEVICE_UNKNOWN,0x823,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
struct STestLockThreadParam
{
	PKSPIN_LOCK													MSpinLock;
	INT32														MCounter;
};
//-------------------------------------------------------------------------------------------------------
struct STestPeriodicTimerParam
{
	KTIMER														MTimer;
	KDPC														MDPC;
	INT32														MCounter;
	bool														MIsInitialized;
};
//-------------------------------------------------------------------------------------------------------
// !!! VARIABLE TestPeriodicTimerParam MUSI byt v NON-PAGED MEMORY.
#pragma data_seg()
STestPeriodicTimerParam*										TestPeriodicTimerParam=NULL;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// DPC FUNCTIONS MUSIA byt v NON-PAGED MEMORY.
#pragma code_seg()
_Function_class_(KDEFERRED_ROUTINE)
VOID DPCCallback1(PKDPC, PVOID, PVOID, PVOID)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION DPCCallback1(): DPC STARTED !\n"));

	KdPrint((DRIVERLOGNAME " - FUNCTION DPCCallback1(): DPC FINISHED !\n"));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// DPC FUNCTIONS MUSIA byt v NON-PAGED MEMORY.
// !!! DPC FUNCTIONS su vykonavane SERIALIZOVANE.
#pragma code_seg()
_Function_class_(KDEFERRED_ROUTINE)
VOID DPCCallback2(PKDPC, PVOID Context, PVOID, PVOID)
{
	STestPeriodicTimerParam*									DPCContext=(STestPeriodicTimerParam*) Context;

	KdPrint((DRIVERLOGNAME " - FUNCTION DPCCallback2(): DPC STARTED - IRQL [%d] !\n",KeGetCurrentIrql()));

	KdPrint((DRIVERLOGNAME " - FUNCTION DPCCallback2(): DPC STARTED - IRQL [%d], COUNTER [%d] !\n",KeGetCurrentIrql(),DPCContext->MCounter));

	if (++DPCContext->MCounter>10)
	{
		// !!! Vykonam CANCEL daneho KERNEL TIME.
		KeCancelTimer(&DPCContext->MTimer);

		KdPrint((DRIVERLOGNAME " - FUNCTION DPCCallback2(): DPC CANCELLED TIMER !\n"));

		// !!!!! OPERATION by mal pouzivat LOCK, ale kedze sa nastavuje iba 1 INT32, tak OPERATION JE ATOMICKA.
		TestPeriodicTimerParam->MCounter=0;

		// !!!!! OPERATION by mal pouzivat LOCK, ale kedze sa nastavuje iba 1 BYTE, tak OPERATION JE ATOMICKA.
		TestPeriodicTimerParam->MIsInitialized=false;

		// !!!!! PERIODIC KERNEL TIMERS sa NESMU UVOLNIT v DPC (cez ExFreePool()) inak dojde k BUG CHECK.
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION DPCCallback2(): DPC FINISHED !\n"));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void WorkerThreadFunction(PVOID)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadFunction(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_SUCCESS;
	LARGE_INTEGER												Timeout;
	
	Timeout.QuadPart=1000*(-10*1000);

	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadFunction(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadFunction(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadFunction(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void WorkerThreadTestLockFunction(PVOID Param)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestLockFunction(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_SUCCESS;
	KIRQL														OriginalIRQL;
	STestLockThreadParam*										TypedParam=(STestLockThreadParam*) Param;

	for (INT32 Index=0;Index<10*1000;Index++)
	{
		// !!! ZISKAM LOCK a zaroven sa zmeni IRQL na DISPATCH_LEVEL.
		KeAcquireSpinLock(TypedParam->MSpinLock,&OriginalIRQL);

		TypedParam->MCounter++;

		// !!! UVOLNIM LOCK a zaroven sa zmeni IRQL na povodnu hodnotu.
		KeReleaseSpinLock(TypedParam->MSpinLock,OriginalIRQL);
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestLockFunction(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void WorkerThreadTestQueuedSpinLockFunction(PVOID Param)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestQueuedSpinLockFunction(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_SUCCESS;
	KLOCK_QUEUE_HANDLE											LockHandle;
	STestLockThreadParam*										TypedParam=(STestLockThreadParam*) Param;

	for (INT32 Index=0;Index<10*1000;Index++)
	{
		// !!! ZISKAM LOCK a zaroven sa zmeni IRQL na DISPATCH_LEVEL.
		KeAcquireInStackQueuedSpinLock(TypedParam->MSpinLock,&LockHandle);

		TypedParam->MCounter++;

		// !!! UVOLNIM LOCK a zaroven sa zmeni IRQL na povodnu hodnotu.
		KeReleaseInStackQueuedSpinLock(&LockHandle);
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestQueuedSpinLockFunction(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void WorkerThreadTestAutoAndManualResetEvent(PVOID Param)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoAndManualResetEvent(): WORKER THREAD STARTED [%p] !\n",PsGetCurrentThreadId()));

	NTSTATUS													Status=STATUS_SUCCESS;
	PRKEVENT													TypedParam=(PRKEVENT) Param;

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoAndManualResetEvent(): WORKER THREAD [%p] KERNEL EVENT STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateEvent(TypedParam)));

	KeWaitForSingleObject(TypedParam,Executive,KernelMode,FALSE,NULL);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoAndManualResetEvent(): WORKER THREAD [%p] KERNEL EVENT STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateEvent(TypedParam)));

	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1000*(-10*1000);

	// !!! POCKAM 1 SEKUNDU.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoAndManualResetEvent(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoAndManualResetEvent(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoAndManualResetEvent(): WORKER THREAD [%p] KERNEL EVENT STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateEvent(TypedParam)));

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoAndManualResetEvent(): WORKER THREAD FINISHED [%p] !\n",PsGetCurrentThreadId()));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void WorkerThreadTestSemaphore(PVOID Param)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestSemaphore(): WORKER THREAD STARTED [%p] !\n",PsGetCurrentThreadId()));

	NTSTATUS													Status=STATUS_SUCCESS;
	PKSEMAPHORE													TypedParam=(PKSEMAPHORE) Param;

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestSemaphore(): WORKER THREAD [%p] - BEFORE WAIT - KERNEL SEMAPHORE STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateSemaphore(TypedParam)));

	KeWaitForSingleObject(TypedParam,Executive,KernelMode,FALSE,NULL);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestSemaphore(): WORKER THREAD [%p] - AFTER WAIT - KERNEL SEMAPHORE STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateSemaphore(TypedParam)));

	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1000*(-10*1000);

	// !!! POCKAM 1 SEKUNDU.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestSemaphore(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestSemaphore(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	// !!! UVOLNI sa SEMAPHORE ZVYSENIM HODNOTY COUNTER.
	KeReleaseSemaphore(TypedParam,SEMAPHORE_INCREMENT,1,FALSE);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestSemaphore(): WORKER THREAD [%p] - AFTER RELEASE - KERNEL SEMAPHORE STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateSemaphore(TypedParam)));

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestSemaphore(): WORKER THREAD FINISHED [%p] !\n",PsGetCurrentThreadId()));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void WorkerThreadTestMutex(PVOID Param)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD STARTED [%p] !\n",PsGetCurrentThreadId()));

	NTSTATUS													Status=STATUS_SUCCESS;
	PKMUTEX														TypedParam=(PKMUTEX) Param;

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD [%p] - BEFORE WAIT - KERNEL MUTEX STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateMutex(TypedParam)));

	KeWaitForSingleObject(TypedParam,Executive,KernelMode,FALSE,NULL);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD [%p] - AFTER WAIT - KERNEL MUTEX STATE [%d], IRQL [%d] !\n",PsGetCurrentThreadId(),KeReadStateMutex(TypedParam),KeGetCurrentIrql()));

	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1000*(-10*1000);

	// !!! POCKAM 1 SEKUNDU.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	// !!! UVOLNI sa MUTEX.
	KeReleaseMutex(TypedParam,FALSE);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD [%p] - AFTER RELEASE - KERNEL MUTEX STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateMutex(TypedParam)));

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD FINISHED [%p] !\n",PsGetCurrentThreadId()));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void WorkerThreadTestManualResetTimer(PVOID Param)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestManualResetTimer(): WORKER THREAD STARTED [%p] !\n",PsGetCurrentThreadId()));

	NTSTATUS													Status=STATUS_SUCCESS;
	PKTIMER														TypedParam=(PKTIMER) Param;

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestManualResetTimer(): WORKER THREAD [%p] - BEFORE WAIT - KERNEL TIMER STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateTimer(TypedParam)));

	KeWaitForSingleObject(TypedParam,Executive,KernelMode,FALSE,NULL);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestManualResetTimer(): WORKER THREAD [%p] - AFTER WAIT - KERNEL TIMER STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateTimer(TypedParam)));

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestManualResetTimer(): WORKER THREAD FINISHED [%p] !\n",PsGetCurrentThreadId()));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void WorkerThreadTestAutoResetTimer(PVOID Param)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoResetTimer(): WORKER THREAD STARTED [%p] !\n",PsGetCurrentThreadId()));

	NTSTATUS													Status=STATUS_SUCCESS;
	PKTIMER														TypedParam=(PKTIMER) Param;

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoResetTimer(): WORKER THREAD [%p] - BEFORE WAIT - KERNEL TIMER STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateTimer(TypedParam)));

	KeWaitForSingleObject(TypedParam,Executive,KernelMode,FALSE,NULL);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoResetTimer(): WORKER THREAD [%p] - AFTER WAIT - KERNEL TIMER STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateTimer(TypedParam)));

	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1000*(-10*1000);

	// !!!!! Kedze KERNEL TIMER bol nastaveny ako AUTO RESET TIMER, tak aby sa uvolnil DALSI THREAD tak znova nastavim KERNEL TIMER na spustenie odcitavania TIMEOUT.
	KeSetTimerEx(TypedParam,Timeout,0,NULL);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoResetTimer(): WORKER THREAD [%p] - AFTER TIMER RESET - KERNEL TIMER STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateTimer(TypedParam)));

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestAutoResetTimer(): WORKER THREAD FINISHED [%p] !\n",PsGetCurrentThreadId()));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void WorkerThreadTestFastMutex(PVOID Param)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestFastMutex(): WORKER THREAD STARTED [%p] !\n",PsGetCurrentThreadId()));

	NTSTATUS													Status=STATUS_SUCCESS;
	PFAST_MUTEX													TypedParam=(PFAST_MUTEX) Param;

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestFastMutex(): WORKER THREAD [%p] - BEFORE WAIT !\n",PsGetCurrentThreadId()));

	// !!! Ziska FAST MUTEX.
	ExAcquireFastMutex(TypedParam);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestFastMutex(): WORKER THREAD [%p] - AFTER WAIT - IRQL [%d] !\n",PsGetCurrentThreadId(),KeGetCurrentIrql()));

	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1000*(-10*1000);

	// !!! POCKAM 1 SEKUNDU.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestFastMutex(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestFastMutex(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	// !!! UVOLNI sa FAST MUTEX.
	ExReleaseFastMutex(TypedParam);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestFastMutex(): WORKER THREAD [%p] - AFTER RELEASE - IRQL [%d] !\n",PsGetCurrentThreadId(),KeGetCurrentIrql()));

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestFastMutex(): WORKER THREAD FINISHED [%p] !\n",PsGetCurrentThreadId()));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlReadFile(PIRP IRP, DEVICE_EXTENSION*, ULONG, ULONG InputBufferLength, ULONG OutputBufferLength, ULONG& Info)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlReadFile(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// Alokujem aj miesto pre NULL TERMINATOR.
	SIZE_T														DataFromInputBufferLength=InputBufferLength+sizeof(CHAR);
	CHAR*														DataFromInputBuffer=(CHAR*) ExAllocatePoolWithTag(PagedPool,DataFromInputBufferLength,' FUB');

	if (DataFromInputBuffer!=NULL)
	{
		RtlZeroMemory(DataFromInputBuffer,DataFromInputBufferLength);

		// Do DataFromInputBuffer sa ulozia BYTES z INPUT BUFFER, pricom DataFromInputBuffer ma este o 1 BYTE navyse na ulozenie NULL TERMINATOR.
		// !!!!! FIELD IRP->AssociatedIrp.SystemBuffer obsahuje INPUT aj OUTPUT BUFFER.
		RtlCopyMemory(DataFromInputBuffer,IRP->AssociatedIrp.SystemBuffer,InputBufferLength);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlReadFile(): InputBuffer [%s] !\n",DataFromInputBuffer));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlReadFile(): MEMORY ALLOCATION FAILED !\n"));
	}

	WCHAR												DataToSendToUserMode[]=L"My name is Timmy Anderson !";
	ULONG												DataToSendToUserModeLength=sizeof(DataToSendToUserMode);
			
	if (OutputBufferLength>=DataToSendToUserModeLength)
	{
		// Do OUTPUT BUFFER sa ulozi STRING.
		// !!!!! FIELD IRP->AssociatedIrp.SystemBuffer obsahuje INPUT aj OUTPUT BUFFER.
		RtlCopyMemory(IRP->AssociatedIrp.SystemBuffer,&DataToSendToUserMode,DataToSendToUserModeLength);
		Info=DataToSendToUserModeLength;
		Status=STATUS_SUCCESS;
	}
	else
	{
		Status=STATUS_BUFFER_TOO_SMALL;
	}

	if (DataFromInputBuffer!=NULL)
	{
		ExFreePoolWithTag(DataFromInputBuffer,' FUB');
		DataFromInputBuffer=NULL;
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlThreadTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlThreadTest(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,WorkerThreadFunction,NULL))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlThreadTest(): SYSTEM THREAD CREATED !\n"));

		PKTHREAD												Thread;

		if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread,NULL))==true)
		{
			// Cakam kym sa THREAD NESKONCI.
			KeWaitForSingleObject(Thread,Executive,KernelMode,FALSE,NULL);

			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlThreadTest(): WORKER THREAD FINISHED !\n"));

			ObDereferenceObject(Thread);
			Thread=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlThreadTest(): ObReferenceObjectByHandle() FAILED [%X] !\n",Status));
		}

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlThreadTest(): PsCreateSystemThread() FAILED [%X] !\n",Status));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlThreadTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlIRQLChangeTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlIRQLChangeTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	KIRQL														OriginalIRQL;

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlIRQLChangeTest(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlIRQLChangeTest(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	KeLowerIrql(OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlIRQLChangeTest(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlSpinLockTest() bude v NON-PAGED MEMORY, kedze cast z nej pouziva SPIN LOCKS, ktore bezia v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlSpinLockTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	KIRQL														OriginalIRQL;
	PKSPIN_LOCK													SpinLock=(PKSPIN_LOCK) ExAllocatePoolWithTag(NonPagedPool,sizeof(KSPIN_LOCK),'KCOL');

	if (SpinLock!=NULL)
	{
		KeInitializeSpinLock(SpinLock);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockTest(): BEFORE LOCK ACQUIRE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		// !!! ZISKAM LOCK a zaroven sa zmeni IRQL na DISPATCH_LEVEL.
		KeAcquireSpinLock(SpinLock,&OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockTest(): INSIDE LOCK - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		// !!! UVOLNIM LOCK a zaroven sa zmeni IRQL na povodnu hodnotu.
		KeReleaseSpinLock(SpinLock,OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockTest(): AFTER LOCK RELEASE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		ExFreePoolWithTag(SpinLock,'KCOL');
		SpinLock=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlSpinLockWithThreadsTest() bude v NON-PAGED MEMORY, kedze cast z nej pouziva SPIN LOCKS, ktore bezia v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlSpinLockWithThreadsTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockWithThreadsTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	PKSPIN_LOCK													SpinLock=(PKSPIN_LOCK) ExAllocatePoolWithTag(NonPagedPool,sizeof(KSPIN_LOCK),'KCOL');
	STestLockThreadParam										ThreadParam;

	ThreadParam.MCounter=0;

	if (SpinLock!=NULL)
	{
		KeInitializeSpinLock(SpinLock);

		ThreadParam.MSpinLock=SpinLock;

		HANDLE													ThreadHandle1=NULL;
		HANDLE													ThreadHandle2=NULL;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes1;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes2;

		InitializeObjectAttributes(&ThreadHandleObjectAttributes1,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		InitializeObjectAttributes(&ThreadHandleObjectAttributes2,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

		if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle1,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes1,NULL,NULL,WorkerThreadTestLockFunction,&ThreadParam))==true)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle2,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes2,NULL,NULL,WorkerThreadTestLockFunction,&ThreadParam))==true)
			{
				PKTHREAD										Thread1=NULL;
				PKTHREAD										Thread2=NULL;

				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle1,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread1,NULL))==true)
				{
					if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle2,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread2,NULL))==true)
					{
						// Cakam kym sa THREADS NESKONCIA.
						KeWaitForSingleObject(Thread1,Executive,KernelMode,FALSE,NULL);
						KeWaitForSingleObject(Thread2,Executive,KernelMode,FALSE,NULL);

						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockWithThreadsTest(): WORKER THREADS FINISHED !\n"));
					}
					else
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockWithThreadsTest(): ObReferenceObjectByHandle() for THREAD 2 FAILED [%X] !\n",Status));
					}
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockWithThreadsTest(): ObReferenceObjectByHandle() for THREAD 1 FAILED [%X] !\n",Status));
				}

				if (Thread1!=NULL)
				{
					ObDereferenceObject(Thread1);
					Thread1=NULL;
				}

				if (Thread2!=NULL)
				{
					ObDereferenceObject(Thread2);
					Thread2=NULL;
				}
			}
			else
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockWithThreadsTest(): CAN'T CREATE THREAD 2 !\n"));
			}
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockWithThreadsTest(): CAN'T CREATE THREAD 1 !\n"));
		}

		if (ThreadHandle1!=NULL)
		{
			ZwClose(ThreadHandle1);
			ThreadHandle1=NULL;
		}

		if (ThreadHandle2!=NULL)
		{
			ZwClose(ThreadHandle2);
			ThreadHandle2=NULL;
		}

		ExFreePoolWithTag(SpinLock,'KCOL');
		SpinLock=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockWithThreadsTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockWithThreadsTest(): !!!!!!!!!! LOCK TEST RESULT [%d] !\n",ThreadParam.MCounter));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlSpinLockWithThreadsTest() bude v NON-PAGED MEMORY, kedze cast z nej pouziva SPIN LOCKS, ktore bezia v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlQueuedSpinLockWithThreadsTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlQueuedSpinLockWithThreadsTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	PKSPIN_LOCK													SpinLock=(PKSPIN_LOCK) ExAllocatePoolWithTag(NonPagedPool,sizeof(KSPIN_LOCK),'KCOL');
	STestLockThreadParam										ThreadParam;

	ThreadParam.MCounter=0;

	if (SpinLock!=NULL)
	{
		KeInitializeSpinLock(SpinLock);

		ThreadParam.MSpinLock=SpinLock;

		HANDLE													ThreadHandle1=NULL;
		HANDLE													ThreadHandle2=NULL;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes1;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes2;

		InitializeObjectAttributes(&ThreadHandleObjectAttributes1,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		InitializeObjectAttributes(&ThreadHandleObjectAttributes2,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

		if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle1,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes1,NULL,NULL,WorkerThreadTestQueuedSpinLockFunction,&ThreadParam))==true)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle2,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes2,NULL,NULL,WorkerThreadTestQueuedSpinLockFunction,&ThreadParam))==true)
			{
				PKTHREAD										Thread1=NULL;
				PKTHREAD										Thread2=NULL;

				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle1,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread1,NULL))==true)
				{
					if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle2,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread2,NULL))==true)
					{
						// Cakam kym sa THREADS NESKONCIA.
						KeWaitForSingleObject(Thread1,Executive,KernelMode,FALSE,NULL);
						KeWaitForSingleObject(Thread2,Executive,KernelMode,FALSE,NULL);

						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlQueuedSpinLockWithThreadsTest(): WORKER THREADS FINISHED !\n"));
					}
					else
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlQueuedSpinLockWithThreadsTest(): ObReferenceObjectByHandle() for THREAD 2 FAILED [%X] !\n",Status));
					}
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSpinLockWithThreadsTest(): ObReferenceObjectByHandle() for THREAD 1 FAILED [%X] !\n",Status));
				}

				if (Thread1!=NULL)
				{
					ObDereferenceObject(Thread1);
					Thread1=NULL;
				}

				if (Thread2!=NULL)
				{
					ObDereferenceObject(Thread2);
					Thread2=NULL;
				}
			}
			else
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlQueuedSpinLockWithThreadsTest(): CAN'T CREATE THREAD 2 !\n"));
			}
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlQueuedSpinLockWithThreadsTest(): CAN'T CREATE THREAD 1 !\n"));
		}

		if (ThreadHandle1!=NULL)
		{
			ZwClose(ThreadHandle1);
			ThreadHandle1=NULL;
		}

		if (ThreadHandle2!=NULL)
		{
			ZwClose(ThreadHandle2);
			ThreadHandle2=NULL;
		}

		ExFreePoolWithTag(SpinLock,'KCOL');
		SpinLock=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlQueuedSpinLockWithThreadsTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlQueuedSpinLockWithThreadsTest(): !!!!!!!!!! LOCK TEST RESULT [%d] !\n",ThreadParam.MCounter));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlThreadTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlWaitForMultipleObjectsTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	PKSPIN_LOCK													SpinLock=(PKSPIN_LOCK) ExAllocatePoolWithTag(NonPagedPool,sizeof(KSPIN_LOCK),'KCOL');
	STestLockThreadParam										ThreadParam;

	ThreadParam.MCounter=0;

	if (SpinLock!=NULL)
	{
		KeInitializeSpinLock(SpinLock);

		ThreadParam.MSpinLock=SpinLock;

		HANDLE													ThreadHandle1=NULL;
		HANDLE													ThreadHandle2=NULL;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes1;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes2;

		InitializeObjectAttributes(&ThreadHandleObjectAttributes1,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		InitializeObjectAttributes(&ThreadHandleObjectAttributes2,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

		if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle1,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes1,NULL,NULL,WorkerThreadTestLockFunction,&ThreadParam))==true)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle2,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes2,NULL,NULL,WorkerThreadTestLockFunction,&ThreadParam))==true)
			{
				PKTHREAD										Thread1=NULL;
				PKTHREAD										Thread2=NULL;

				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle1,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread1,NULL))==true)
				{
					if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle2,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread2,NULL))==true)
					{
						PKTHREAD								Threads[]={Thread1,Thread2};

						// !!! POSLEDNY PARAMETER moze byt NULL IBA ak pocet WAIT OBJECTS je MENSI ako THREAD_WAIT_OBJECTS (3).
						// Cakam kym sa THREADS NESKONCIA.
						//Status=KeWaitForMultipleObjects(_countof(Threads),(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,NULL);

						// !!! Sluzi IBA pre INTERNE POTREBY KeWaitForMultipleObjects() a NEMUSI BYT NIJAKO INICIALIZOVANA.
						// !!! WaitBlocks MUSI byt v NON-PAGED MEMORY.
						KWAIT_BLOCK								WaitBlocks[_countof(Threads)];

						Status=KeWaitForMultipleObjects(_countof(Threads),(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

						if (Status==STATUS_SUCCESS)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
						}
						else if (Status==STATUS_TIMEOUT)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
						}
						else
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
						}
					}
					else
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): ObReferenceObjectByHandle() for THREAD 2 FAILED [%X] !\n",Status));
					}
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): ObReferenceObjectByHandle() for THREAD 1 FAILED [%X] !\n",Status));
				}

				if (Thread1!=NULL)
				{
					ObDereferenceObject(Thread1);
					Thread1=NULL;
				}

				if (Thread2!=NULL)
				{
					ObDereferenceObject(Thread2);
					Thread2=NULL;
				}
			}
			else
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): CAN'T CREATE THREAD 2 !\n"));
			}
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): CAN'T CREATE THREAD 1 !\n"));
		}

		if (ThreadHandle1!=NULL)
		{
			ZwClose(ThreadHandle1);
			ThreadHandle1=NULL;
		}

		if (ThreadHandle2!=NULL)
		{
			ZwClose(ThreadHandle2);
			ThreadHandle2=NULL;
		}

		ExFreePoolWithTag(SpinLock,'KCOL');
		SpinLock=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlWaitForMultipleObjectsTest(): !!!!!!!!!! LOCK TEST RESULT [%d] !\n",ThreadParam.MCounter));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlManualResetEventTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlManualResetEventTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL EVENT MUSI byt v NON-PAGED MEMORY.
	PKEVENT														Event=(PKEVENT) ExAllocatePoolWithTag(NonPagedPool,sizeof(KEVENT),' EVE');

	if (Event!=NULL)
	{
		// !!! VYTVORI sa MANUAL RESET EVENT v NON-SIGNALIZED STATE.
		KeInitializeEvent(Event,NotificationEvent,FALSE);

		HANDLE													ThreadHandle1=NULL;
		HANDLE													ThreadHandle2=NULL;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes1;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes2;

		InitializeObjectAttributes(&ThreadHandleObjectAttributes1,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		InitializeObjectAttributes(&ThreadHandleObjectAttributes2,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

		if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle1,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes1,NULL,NULL,WorkerThreadTestAutoAndManualResetEvent,Event))==true)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle2,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes2,NULL,NULL,WorkerThreadTestAutoAndManualResetEvent,Event))==true)
			{
				PKTHREAD										Thread1=NULL;
				PKTHREAD										Thread2=NULL;

				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle1,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread1,NULL))==true)
				{
					if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle2,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread2,NULL))==true)
					{
						LARGE_INTEGER												Timeout;

						// !!! POCKAM 1 SEKUNDU a vykonam SET EVENTU.
						Timeout.QuadPart=1000*(-10*1000);

						if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): THREAD DELAY FINISHED !\n"));
						}
						else
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
						}

						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): EVENT will be SET !\n"));

						// !!! Vykona sa SET EVENTU.
						KeSetEvent(Event,EVENT_INCREMENT,FALSE);

						// !!! POCKAM 1 SEKUNDU a vykonam SET EVENTU.
						Timeout.QuadPart=1000*(-10*1000);

						if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): THREAD DELAY FINISHED !\n"));
						}
						else
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
						}

						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): EVENT will be SET !\n"));

						// !!! Vykona sa SET EVENTU.
						KeSetEvent(Event,EVENT_INCREMENT,FALSE);

						PKTHREAD								Threads[]={Thread1,Thread2};
						// !!! Sluzi IBA pre INTERNE POTREBY KeWaitForMultipleObjects() a NEMUSI BYT NIJAKO INICIALIZOVANA.
						// !!! WaitBlocks MUSI byt v NON-PAGED MEMORY.
						KWAIT_BLOCK								WaitBlocks[_countof(Threads)];

						Status=KeWaitForMultipleObjects(_countof(Threads),(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

						if (Status==STATUS_SUCCESS)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
						}
						else if (Status==STATUS_TIMEOUT)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
						}
						else
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
						}
					}
					else
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): ObReferenceObjectByHandle() for THREAD 2 FAILED [%X] !\n",Status));
					}
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): ObReferenceObjectByHandle() for THREAD 1 FAILED [%X] !\n",Status));
				}

				if (Thread1!=NULL)
				{
					ObDereferenceObject(Thread1);
					Thread1=NULL;
				}

				if (Thread2!=NULL)
				{
					ObDereferenceObject(Thread2);
					Thread2=NULL;
				}
			}
			else
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): CAN'T CREATE THREAD 2 !\n"));
			}
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): CAN'T CREATE THREAD 1 !\n"));
		}

		if (ThreadHandle1!=NULL)
		{
			ZwClose(ThreadHandle1);
			ThreadHandle1=NULL;
		}

		if (ThreadHandle2!=NULL)
		{
			ZwClose(ThreadHandle2);
			ThreadHandle2=NULL;
		}

		ExFreePoolWithTag(Event,' EVE');
		Event=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetEventTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlAutoResetEventTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlAutoResetEventTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL EVENT MUSI byt v NON-PAGED MEMORY.
	PKEVENT														Event=(PKEVENT) ExAllocatePoolWithTag(NonPagedPool,sizeof(KEVENT),' EVE');

	if (Event!=NULL)
	{
		// !!! VYTVORI sa AUTO RESET EVENT v NON-SIGNALIZED STATE.
		KeInitializeEvent(Event,SynchronizationEvent,FALSE);

		HANDLE													ThreadHandle1=NULL;
		HANDLE													ThreadHandle2=NULL;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes1;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes2;

		InitializeObjectAttributes(&ThreadHandleObjectAttributes1,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		InitializeObjectAttributes(&ThreadHandleObjectAttributes2,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

		if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle1,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes1,NULL,NULL,WorkerThreadTestAutoAndManualResetEvent,Event))==true)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle2,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes2,NULL,NULL,WorkerThreadTestAutoAndManualResetEvent,Event))==true)
			{
				PKTHREAD										Thread1=NULL;
				PKTHREAD										Thread2=NULL;

				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle1,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread1,NULL))==true)
				{
					if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle2,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread2,NULL))==true)
					{
						LARGE_INTEGER												Timeout;

						// !!! POCKAM 1 SEKUNDU a vykonam SET EVENTU.
						Timeout.QuadPart=1000*(-10*1000);

						if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): THREAD DELAY FINISHED !\n"));
						}
						else
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
						}

						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): EVENT will be SET !\n"));

						// !!! Vykona sa SET EVENTU.
						KeSetEvent(Event,EVENT_INCREMENT,FALSE);

						// !!! POCKAM 1 SEKUNDU a vykonam SET EVENTU.
						Timeout.QuadPart=1000*(-10*1000);

						if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): THREAD DELAY FINISHED !\n"));
						}
						else
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
						}

						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): EVENT will be SET !\n"));

						// !!! Vykona sa SET EVENTU.
						KeSetEvent(Event,EVENT_INCREMENT,FALSE);

						PKTHREAD								Threads[]={Thread1,Thread2};
						// !!! Sluzi IBA pre INTERNE POTREBY KeWaitForMultipleObjects() a NEMUSI BYT NIJAKO INICIALIZOVANA.
						// !!! WaitBlocks MUSI byt v NON-PAGED MEMORY.
						KWAIT_BLOCK								WaitBlocks[_countof(Threads)];

						Status=KeWaitForMultipleObjects(_countof(Threads),(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

						if (Status==STATUS_SUCCESS)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
						}
						else if (Status==STATUS_TIMEOUT)
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
						}
						else
						{
							KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
						}
					}
					else
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): ObReferenceObjectByHandle() for THREAD 2 FAILED [%X] !\n",Status));
					}
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): ObReferenceObjectByHandle() for THREAD 1 FAILED [%X] !\n",Status));
				}

				if (Thread1!=NULL)
				{
					ObDereferenceObject(Thread1);
					Thread1=NULL;
				}

				if (Thread2!=NULL)
				{
					ObDereferenceObject(Thread2);
					Thread2=NULL;
				}
			}
			else
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): CAN'T CREATE THREAD 2 !\n"));
			}
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): CAN'T CREATE THREAD 1 !\n"));
		}

		if (ThreadHandle1!=NULL)
		{
			ZwClose(ThreadHandle1);
			ThreadHandle1=NULL;
		}

		if (ThreadHandle2!=NULL)
		{
			ZwClose(ThreadHandle2);
			ThreadHandle2=NULL;
		}

		ExFreePoolWithTag(Event,' EVE');
		Event=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetEventTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlSemaphoreTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlSemaphoreTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSemaphoreTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL SEMPAHORE MUSI byt v NON-PAGED MEMORY.
	PKSEMAPHORE													Semaphore=(PKSEMAPHORE) ExAllocatePoolWithTag(NonPagedPool,sizeof(KSEMAPHORE),' MES');

	if (Semaphore!=NULL)
	{
		// !!! VYTVORI sa SEMAPHORE.
		KeInitializeSemaphore(Semaphore,4,4);

		const int												THREAD_COUNT=10;

		HANDLE													ThreadHandles[THREAD_COUNT];
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes[THREAD_COUNT];
		PKTHREAD												Threads[THREAD_COUNT];

		RtlZeroMemory(ThreadHandles,sizeof(ThreadHandles));
		RtlZeroMemory(ThreadHandleObjectAttributes,sizeof(ThreadHandleObjectAttributes));
		RtlZeroMemory(Threads,sizeof(Threads));

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			InitializeObjectAttributes(&ThreadHandleObjectAttributes[Index],NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		}

		bool													HasError=false;

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandles[Index],THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes[Index],NULL,NULL,WorkerThreadTestSemaphore,Semaphore))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSemaphoreTest(): CAN'T CREATE THREAD !\n"));
				HasError=true;
				break;
			}
		}

		if (HasError==false)
		{
			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandles[Index],THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Threads[Index],NULL))==false)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSemaphoreTest(): ObReferenceObjectByHandle() for THREAD FAILED [%X] !\n",Status));
					HasError=true;
					break;
				}
			}

			if (HasError==false)
			{
				KWAIT_BLOCK										WaitBlocks[THREAD_COUNT];

				Status=KeWaitForMultipleObjects(THREAD_COUNT,(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

				if (Status==STATUS_SUCCESS)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSemaphoreTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
				}
				else if (Status==STATUS_TIMEOUT)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSemaphoreTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSemaphoreTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
				}
			}

			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (Threads[Index]!=NULL)
				{
					ObDereferenceObject(Threads[Index]);
					Threads[Index]=NULL;
				}
			}
		}

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (ThreadHandles[Index]!=NULL)
			{
				ZwClose(ThreadHandles[Index]);
				ThreadHandles[Index]=NULL;
			}
		}

		ExFreePoolWithTag(Semaphore,' MES');
		Semaphore=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlSemaphoreTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlMutexTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlMutexTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL MUTEX MUSI byt v NON-PAGED MEMORY.
	PKMUTEX														Mutex=(PKMUTEX) ExAllocatePoolWithTag(NonPagedPool,sizeof(KMUTEX),' TUM');

	if (Mutex!=NULL)
	{
		// !!! VYTVORI sa MUTEX. Je v SIGNALIZED STATE.
		KeInitializeMutex(Mutex,0);

		const int												THREAD_COUNT=10;

		HANDLE													ThreadHandles[THREAD_COUNT];
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes[THREAD_COUNT];
		PKTHREAD												Threads[THREAD_COUNT];

		RtlZeroMemory(ThreadHandles,sizeof(ThreadHandles));
		RtlZeroMemory(ThreadHandleObjectAttributes,sizeof(ThreadHandleObjectAttributes));
		RtlZeroMemory(Threads,sizeof(Threads));

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			InitializeObjectAttributes(&ThreadHandleObjectAttributes[Index],NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		}

		bool													HasError=false;

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandles[Index],THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes[Index],NULL,NULL,WorkerThreadTestMutex,Mutex))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): CAN'T CREATE THREAD !\n"));
				HasError=true;
				break;
			}
		}

		if (HasError==false)
		{
			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandles[Index],THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Threads[Index],NULL))==false)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): ObReferenceObjectByHandle() for THREAD FAILED [%X] !\n",Status));
					HasError=true;
					break;
				}
			}

			if (HasError==false)
			{
				KWAIT_BLOCK										WaitBlocks[THREAD_COUNT];

				Status=KeWaitForMultipleObjects(THREAD_COUNT,(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

				if (Status==STATUS_SUCCESS)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
				}
				else if (Status==STATUS_TIMEOUT)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
				}
			}

			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (Threads[Index]!=NULL)
				{
					ObDereferenceObject(Threads[Index]);
					Threads[Index]=NULL;
				}
			}
		}

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (ThreadHandles[Index]!=NULL)
			{
				ZwClose(ThreadHandles[Index]);
				ThreadHandles[Index]=NULL;
			}
		}

		ExFreePoolWithTag(Mutex,' TUM');
		Mutex=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlManualResetTimerTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlManualResetTimerTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetTimerTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL TIMER MUSI byt v NON-PAGED MEMORY.
	PKTIMER														Timer=(PKTIMER) ExAllocatePoolWithTag(NonPagedPool,sizeof(KTIMER),' MIT');

	if (Timer!=NULL)
	{
		// !!! VYTVORI sa MANUAL RESET TIMER. Je v NON-SIGNALIZED STATE, az kym NEEXPIRUJE TIMEOUT.
		KeInitializeTimerEx(Timer,NotificationTimer);

		LARGE_INTEGER											Timeout;
	
		Timeout.QuadPart=3*1000*(-10*1000);

		// !!!!! Nastavi sa TIMEOUT a ZAROVEN sa SPUSTI COUNTDOWN na 3 SEKUNDY.
		KeSetTimerEx(Timer,Timeout,0,NULL);

		const int												THREAD_COUNT=3;

		HANDLE													ThreadHandles[THREAD_COUNT];
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes[THREAD_COUNT];
		PKTHREAD												Threads[THREAD_COUNT];

		RtlZeroMemory(ThreadHandles,sizeof(ThreadHandles));
		RtlZeroMemory(ThreadHandleObjectAttributes,sizeof(ThreadHandleObjectAttributes));
		RtlZeroMemory(Threads,sizeof(Threads));

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			InitializeObjectAttributes(&ThreadHandleObjectAttributes[Index],NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		}

		bool													HasError=false;

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandles[Index],THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes[Index],NULL,NULL,WorkerThreadTestManualResetTimer,Timer))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetTimerTest(): CAN'T CREATE THREAD !\n"));
				HasError=true;
				break;
			}
		}

		if (HasError==false)
		{
			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandles[Index],THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Threads[Index],NULL))==false)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetTimerTest(): ObReferenceObjectByHandle() for THREAD FAILED [%X] !\n",Status));
					HasError=true;
					break;
				}
			}

			if (HasError==false)
			{
				KWAIT_BLOCK										WaitBlocks[THREAD_COUNT];

				Status=KeWaitForMultipleObjects(THREAD_COUNT,(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

				if (Status==STATUS_SUCCESS)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetTimerTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
				}
				else if (Status==STATUS_TIMEOUT)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetTimerTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetTimerTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
				}
			}

			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (Threads[Index]!=NULL)
				{
					ObDereferenceObject(Threads[Index]);
					Threads[Index]=NULL;
				}
			}
		}

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (ThreadHandles[Index]!=NULL)
			{
				ZwClose(ThreadHandles[Index]);
				ThreadHandles[Index]=NULL;
			}
		}

		BOOLEAN													ScheduledActionCancelled=KeCancelTimer(Timer);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetTimerTest(): KeCancelTimer() CALLED with RESULT [%d] !\n",ScheduledActionCancelled));

		ExFreePoolWithTag(Timer,' MIT');
		Timer=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlManualResetTimerTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlAutoResetTimerTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlAutoResetTimerTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetTimerTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL TIMER MUSI byt v NON-PAGED MEMORY.
	PKTIMER														Timer=(PKTIMER) ExAllocatePoolWithTag(NonPagedPool,sizeof(KTIMER),' MIT');

	if (Timer!=NULL)
	{
		// !!! VYTVORI sa AUTO RESET TIMER. Je v NON-SIGNALIZED STATE, az kym NEEXPIRUJE TIMEOUT.
		KeInitializeTimerEx(Timer,SynchronizationTimer);

		LARGE_INTEGER											Timeout;
	
		Timeout.QuadPart=3*1000*(-10*1000);

		// !!!!! Nastavi sa TIMEOUT a ZAROVEN sa SPUSTI COUNTDOWN na 3 SEKUNDY.
		KeSetTimerEx(Timer,Timeout,0,NULL);

		const int												THREAD_COUNT=3;

		HANDLE													ThreadHandles[THREAD_COUNT];
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes[THREAD_COUNT];
		PKTHREAD												Threads[THREAD_COUNT];

		RtlZeroMemory(ThreadHandles,sizeof(ThreadHandles));
		RtlZeroMemory(ThreadHandleObjectAttributes,sizeof(ThreadHandleObjectAttributes));
		RtlZeroMemory(Threads,sizeof(Threads));

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			InitializeObjectAttributes(&ThreadHandleObjectAttributes[Index],NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		}

		bool													HasError=false;

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandles[Index],THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes[Index],NULL,NULL,WorkerThreadTestAutoResetTimer,Timer))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetTimerTest(): CAN'T CREATE THREAD !\n"));
				HasError=true;
				break;
			}
		}

		if (HasError==false)
		{
			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandles[Index],THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Threads[Index],NULL))==false)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetTimerTest(): ObReferenceObjectByHandle() for THREAD FAILED [%X] !\n",Status));
					HasError=true;
					break;
				}
			}

			if (HasError==false)
			{
				KWAIT_BLOCK										WaitBlocks[THREAD_COUNT];

				Status=KeWaitForMultipleObjects(THREAD_COUNT,(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

				if (Status==STATUS_SUCCESS)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetTimerTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
				}
				else if (Status==STATUS_TIMEOUT)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetTimerTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetTimerTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
				}
			}

			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (Threads[Index]!=NULL)
				{
					ObDereferenceObject(Threads[Index]);
					Threads[Index]=NULL;
				}
			}
		}

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (ThreadHandles[Index]!=NULL)
			{
				ZwClose(ThreadHandles[Index]);
				ThreadHandles[Index]=NULL;
			}
		}

		BOOLEAN													ScheduledActionCancelled=KeCancelTimer(Timer);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetTimerTest(): KeCancelTimer() CALLED with RESULT [%d] !\n",ScheduledActionCancelled));

		ExFreePoolWithTag(Timer,' MIT');
		Timer=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAutoResetTimerTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlDPCTimerTest1() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlDPCTimerTest1(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest1(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL TIMER MUSI byt v NON-PAGED MEMORY.
	PKTIMER														Timer=(PKTIMER) ExAllocatePoolWithTag(NonPagedPool,sizeof(KTIMER),' MIT');

	if (Timer!=NULL)
	{
		// !!! DPC MUSI byt v NON-PAGED MEMORY.
		PKDPC													DPC=(PKDPC) ExAllocatePoolWithTag(NonPagedPool,sizeof(KDPC),' CPD');

		if (DPC!=NULL)
		{
			// !!! VYTVORI sa AUTO RESET TIMER. Je v NON-SIGNALIZED STATE, az kym NEEXPIRUJE TIMEOUT.
			KeInitializeTimerEx(Timer,SynchronizationTimer);

			// !!! Vytvori sa DPC.
			KeInitializeDpc(DPC,DPCCallback1,NULL);

			LARGE_INTEGER										Timeout;
	
			Timeout.QuadPart=3*1000*(-10*1000);

			// !!!!! Nastavi sa TIMEOUT a ZAROVEN sa SPUSTI COUNTDOWN na 3 SEKUNDY a takisto sa nastavi DPC CALLBACK.
			KeSetTimerEx(Timer,Timeout,0,DPC);

			Status=KeWaitForSingleObject(Timer,Executive,KernelMode,FALSE,NULL);

			if (Status==STATUS_SUCCESS)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest1(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
			}
			else if (Status==STATUS_TIMEOUT)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest1(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
			}
			else
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest1(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
			}

			BOOLEAN												ScheduledActionCancelled=KeCancelTimer(Timer);

			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest1(): KeCancelTimer() CALLED with RESULT [%d] !\n",ScheduledActionCancelled));

			ExFreePoolWithTag(DPC,' TUM');
			DPC=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest1(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
		}

		ExFreePoolWithTag(Timer,' MIT');
		Timer=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest1(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlDPCTimerTest2() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlDPCTimerTest2(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest2(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL TIMER MUSI byt v NON-PAGED MEMORY.
	PKTIMER														Timer=(PKTIMER) ExAllocatePoolWithTag(NonPagedPool,sizeof(KTIMER),' MIT');

	if (Timer!=NULL)
	{
		// !!! DPC MUSI byt v NON-PAGED MEMORY.
		PKDPC													DPC=(PKDPC) ExAllocatePoolWithTag(NonPagedPool,sizeof(KDPC),' CPD');

		if (DPC!=NULL)
		{
			// !!! VYTVORI sa AUTO RESET TIMER. Je v NON-SIGNALIZED STATE, az kym NEEXPIRUJE TIMEOUT.
			KeInitializeTimerEx(Timer,SynchronizationTimer);

			// !!! Vytvori sa DPC.
			KeInitializeDpc(DPC,DPCCallback1,NULL);

			LARGE_INTEGER										Timeout;
	
			Timeout.QuadPart=3*1000*(-10*1000);

			// !!!!! Nastavi sa TIMEOUT a ZAROVEN sa SPUSTI COUNTDOWN na 3 SEKUNDY a takisto sa nastavi DPC CALLBACK.
			KeSetTimerEx(Timer,Timeout,0,DPC);

			Status=KeWaitForSingleObject(Timer,Executive,KernelMode,FALSE,NULL);

			if (Status==STATUS_SUCCESS)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest2(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
			}
			else if (Status==STATUS_TIMEOUT)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest2(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
			}
			else
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest2(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
			}

			BOOLEAN												ScheduledActionCancelled=KeCancelTimer(Timer);

			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest2(): KeCancelTimer() CALLED with RESULT [%d] !\n",ScheduledActionCancelled));

			ExFreePoolWithTag(DPC,' CPD');
			DPC=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest2(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
		}

		ExFreePoolWithTag(Timer,' MIT');
		Timer=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest2(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlDPCTimerTest3() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlDPCTimerTest3(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest3(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	if (TestPeriodicTimerParam->MIsInitialized==false)
	{
		// !!! VYTVORI sa AUTO RESET TIMER. Je v NON-SIGNALIZED STATE, az kym NEEXPIRUJE TIMEOUT.
		KeInitializeTimerEx(&TestPeriodicTimerParam->MTimer,SynchronizationTimer);

		// !!! Vytvori sa DPC.
		KeInitializeDpc(&TestPeriodicTimerParam->MDPC,DPCCallback2,TestPeriodicTimerParam);

		LARGE_INTEGER											Timeout;
	
		Timeout.QuadPart=3*1000*(-10*1000);

		// !!!!! Nastavi sa TIMEOUT a ZAROVEN sa SPUSTI COUNTDOWN na 3 SEKUNDY a takisto sa nastavi DPC CALLBACK.
		KeSetTimerEx(&TestPeriodicTimerParam->MTimer,Timeout,3*1000,&TestPeriodicTimerParam->MDPC);

		TestPeriodicTimerParam->MIsInitialized=true;

		// !!!!! PERIODIC KERNEL TIMERS sa KERNEL TIMERS NESMU UVOLNIT v DPC.
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDPCTimerTest3(): KERNEL TIMER was ALREADY INITIALIZED !\n"));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlAPCTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlAPCTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAPCTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL TIMER MUSI byt v NON-PAGED MEMORY.
	PKTIMER														Timer=(PKTIMER) ExAllocatePoolWithTag(NonPagedPool,sizeof(KTIMER),' MIT');

	if (Timer!=NULL)
	{
		// !!! VYTVORI sa AUTO RESET TIMER. Je v NON-SIGNALIZED STATE, az kym NEEXPIRUJE TIMEOUT.
		KeInitializeTimerEx(Timer,SynchronizationTimer);

		LARGE_INTEGER										Timeout;
	
		Timeout.QuadPart=30*1000*(-10*1000);

		// !!!!! Nastavi sa TIMEOUT a ZAROVEN sa SPUSTI COUNTDOWN na 30 SEKUND.
		KeSetTimerEx(Timer,Timeout,0,NULL);

		// !!!!! Ak THREAD ma byt preruseny vykonanim USER MODE APC REQUEST, tak MUSI BYT v ALERTABLE WAIT (WaitMode==KernelMode,Alertable==TRUE).
		Status=KeWaitForSingleObject(Timer,Executive,UserMode,TRUE,NULL);

		if (Status==STATUS_SUCCESS)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAPCTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
		}
		else if (Status==STATUS_TIMEOUT)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAPCTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
		}
		else if (Status==STATUS_USER_APC)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAPCTest(): !!!!!!!!!! WAIT for WORKER THREADS to FINISH COMPLETED after USER MODE APC EXECUTION - STATUS [%X] !\n",Status));
		}
		else if (Status==STATUS_ALERTED)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAPCTest(): !!!!!!!!!! WAIT for WORKER THREADS to FINISH COMPLETED after ALERT EXECUTION - STATUS [%X] !\n",Status));
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAPCTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
		}

		BOOLEAN												ScheduledActionCancelled=KeCancelTimer(Timer);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAPCTest(): KeCancelTimer() CALLED with RESULT [%d] !\n",ScheduledActionCancelled));

		ExFreePoolWithTag(Timer,' MIT');
		Timer=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlAPCTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlFastMutexTest() bude v NON-PAGED MEMORY, kedze cast z nej bezi v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlFastMutexTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlFastMutexTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL MUTEX MUSI byt v NON-PAGED MEMORY.
	PFAST_MUTEX													Mutex=(PFAST_MUTEX) ExAllocatePoolWithTag(NonPagedPool,sizeof(FAST_MUTEX),' TUM');

	if (Mutex!=NULL)
	{
		// !!! VYTVORI sa MUTEX. Je v NON-SIGNALIZED STATE.
		ExInitializeFastMutex(Mutex);

		const int												THREAD_COUNT=10;

		HANDLE													ThreadHandles[THREAD_COUNT];
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes[THREAD_COUNT];
		PKTHREAD												Threads[THREAD_COUNT];

		RtlZeroMemory(ThreadHandles,sizeof(ThreadHandles));
		RtlZeroMemory(ThreadHandleObjectAttributes,sizeof(ThreadHandleObjectAttributes));
		RtlZeroMemory(Threads,sizeof(Threads));

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			InitializeObjectAttributes(&ThreadHandleObjectAttributes[Index],NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		}

		bool													HasError=false;

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandles[Index],THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes[Index],NULL,NULL,WorkerThreadTestFastMutex,Mutex))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlFastMutexTest(): CAN'T CREATE THREAD !\n"));
				HasError=true;
				break;
			}
		}

		if (HasError==false)
		{
			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandles[Index],THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Threads[Index],NULL))==false)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlFastMutexTest(): ObReferenceObjectByHandle() for THREAD FAILED [%X] !\n",Status));
					HasError=true;
					break;
				}
			}

			if (HasError==false)
			{
				KWAIT_BLOCK										WaitBlocks[THREAD_COUNT];

				Status=KeWaitForMultipleObjects(THREAD_COUNT,(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

				if (Status==STATUS_SUCCESS)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlFastMutexTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
				}
				else if (Status==STATUS_TIMEOUT)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlFastMutexTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlFastMutexTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
				}
			}

			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (Threads[Index]!=NULL)
				{
					ObDereferenceObject(Threads[Index]);
					Threads[Index]=NULL;
				}
			}
		}

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (ThreadHandles[Index]!=NULL)
			{
				ZwClose(ThreadHandles[Index]);
				ThreadHandles[Index]=NULL;
			}
		}

		ExFreePoolWithTag(Mutex,' TUM');
		Mutex=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlFastMutexTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void ExecutiveResourceReadThread(PVOID Parameter)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n");

	PERESOURCE													ExecutiveResource=(PERESOURCE) Parameter;
	NTSTATUS													Status;
	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1000*(-10*1000);

	// !!! POCKAM 1 SEKUNDU.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	if (NT_SUCCESS(Status=ExAcquireResourceSharedLite(ExecutiveResource,TRUE))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD [%p] acquired SHARED LOCK !\n",KeGetCurrentThread()));

		Timeout.QuadPart=1000*(-10*1000);

		// !!! POCKAM 1 SEKUNDU.
		if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD DELAY FINISHED !\n"));
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
		}

		ExReleaseResourceLite(ExecutiveResource);
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExAcquireResourceSharedLite() FAILED [%X] !\n",Status);
	}

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n");

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void ExecutiveResourceWriteThread(PVOID Parameter)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n");

	PERESOURCE													ExecutiveResource=(PERESOURCE) Parameter;
	NTSTATUS													Status;
	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1000*(-10*1000);

	// !!! POCKAM 1 SEKUNDU.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	if (NT_SUCCESS(Status=ExAcquireResourceExclusiveLite(ExecutiveResource,TRUE))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD [%p] acquired EXCLUSIVE LOCK !\n",KeGetCurrentThread()));

		Timeout.QuadPart=1000*(-10*1000);

		// !!! POCKAM 1 SEKUNDU.
		if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD DELAY FINISHED !\n"));
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
		}

		ExReleaseResourceLite(ExecutiveResource);
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExAcquireResourceExclusiveLite() FAILED [%X] !\n",Status);
	}

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n");

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlExecutiveResourceTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! EXECUTIVE RESOURCE MUSI byt v NON-PAGED MEMORY.
	PERESOURCE													ExecutiveResource=(PERESOURCE) ExAllocatePoolWithTag(NonPagedPool,sizeof(ERESOURCE),'  RE');

	if (ExecutiveResource!=NULL)
	{
		if (NT_SUCCESS(Status=ExInitializeResourceLite(ExecutiveResource))==true)
		{
			const int											THREAD_COUNT=10;
			const int											NUMBER_OF_READERS=5;

			HANDLE												ThreadHandles[THREAD_COUNT];
			OBJECT_ATTRIBUTES									ThreadHandleObjectAttributes[THREAD_COUNT];
			PKTHREAD											Threads[THREAD_COUNT];

			RtlZeroMemory(ThreadHandles,sizeof(ThreadHandles));
			RtlZeroMemory(ThreadHandleObjectAttributes,sizeof(ThreadHandleObjectAttributes));
			RtlZeroMemory(Threads,sizeof(Threads));

			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				InitializeObjectAttributes(&ThreadHandleObjectAttributes[Index],NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
			}

			bool												HasError=false;

			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (Index<NUMBER_OF_READERS)
				{
					if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandles[Index],THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes[Index],NULL,NULL,ExecutiveResourceReadThread,ExecutiveResource))==false)
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CAN'T CREATE THREAD !\n"));
						HasError=true;
						break;
					}
				}
				else
				{
					if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandles[Index],THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes[Index],NULL,NULL,ExecutiveResourceWriteThread,ExecutiveResource))==false)
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CAN'T CREATE THREAD !\n"));
						HasError=true;
						break;
					}
				}
			}

			if (HasError==false)
			{
				for (int Index=0;Index<THREAD_COUNT;Index++)
				{
					if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandles[Index],THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Threads[Index],NULL))==false)
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ObReferenceObjectByHandle() for THREAD FAILED [%X] !\n",Status));
						HasError=true;
						break;
					}
				}

				if (HasError==false)
				{
					KWAIT_BLOCK									WaitBlocks[THREAD_COUNT];

					Status=KeWaitForMultipleObjects(THREAD_COUNT,(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

					if (Status==STATUS_SUCCESS)
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
					}
					else if (Status==STATUS_TIMEOUT)
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
					}
					else
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
					}
				}

				for (int Index=0;Index<THREAD_COUNT;Index++)
				{
					if (Threads[Index]!=NULL)
					{
						ObDereferenceObject(Threads[Index]);
						Threads[Index]=NULL;
					}
				}
			}

			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (ThreadHandles[Index]!=NULL)
				{
					ZwClose(ThreadHandles[Index]);
					ThreadHandles[Index]=NULL;
				}
			}

			if (NT_SUCCESS(Status=ExDeleteResourceLite(ExecutiveResource))==false)
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExDeleteResourceLite() FAILED [%X] !\n",Status);
			}
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExInitializeResourceLite() FAILED [%X] !\n",Status);
		}

		ExFreePoolWithTag(ExecutiveResource,'  RE');
		ExecutiveResource=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! STRUCTURE reprezentuje LIST ITEM, ktory sa bude vkladat do LIST.
struct SMyDoubleListItem
{
	// CUSTOM FIELDS.
	INT32														MValue1;

	// !!! POVINNY FIELD reprezentujuci LINK na dalsie LIST ITEMS.
	LIST_ENTRY													MLink;

	// CUSTOM FIELDS.
	INT32														MValue2;
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! STRUCTURE reprezentuje LIST ITEM, ktory sa bude vkladat do LIST.
struct SMySingleListItem
{
	// CUSTOM FIELDS.
	INT32														MValue1;

	// !!! POVINNY FIELD reprezentujuci LINK na dalsi LIST ITEM.
	SINGLE_LIST_ENTRY											MLink;

	// CUSTOM FIELDS.
	INT32														MValue2;
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
SMyDoubleListItem* AllocateDoubleListItem(INT32 Value1, INT32 Value2)
{
	// !!!!! INTERLOCKED LISTS MUSIA mat ITEMS v NON-PAGED MEMORY.
	SMyDoubleListItem*											MyDoubleListItem=(SMyDoubleListItem*) ExAllocatePoolWithTag(NonPagedPool,sizeof(SMyDoubleListItem),'TSIL');

	if (MyDoubleListItem==NULL)
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateDoubleListItem(): Can't ALLOCATE DOUBLE LIST ITEM !\n"));
	}
	else
	{
		MyDoubleListItem->MValue1=Value1;
		MyDoubleListItem->MValue2=Value2;
	}

	return(MyDoubleListItem);
}
//-------------------------------------------------------------------------------------------------------
SMySingleListItem* AllocateSingleListItem(INT32 Value1, INT32 Value2)
{
	// !!!!! INTERLOCKED LISTS MUSIA mat ITEMS v NON-PAGED MEMORY.
	SMySingleListItem*											MySingleListItem=(SMySingleListItem*) ExAllocatePoolWithTag(NonPagedPool,sizeof(SMySingleListItem),'TSIL');

	if (MySingleListItem==NULL)
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateSingleListItem(): Can't ALLOCATE SINGLY LIST ITEM !\n"));
	}
	else
	{
		MySingleListItem->MValue1=Value1;
		MySingleListItem->MValue2=Value2;
	}

	return(MySingleListItem);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void DumpDoubleListForward(LIST_ENTRY* List)
{
	KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListForward(): BEGIN !\n"));

	if (IsListEmpty(List)==false)
	{
		// !!!!! MUSIM sa presunut na Flink, lebo HEAD NIKDY NEOBSAHUJE LIST ITEM.
		LIST_ENTRY*												Iterator=List->Flink;

		for(;;)
		{
			SMyDoubleListItem*									ListItem=CONTAINING_RECORD(Iterator,SMyDoubleListItem,MLink);

			KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListForward(): ITEM [%d, %d] !\n",ListItem->MValue1,ListItem->MValue2));

			Iterator=Iterator->Flink;

			if (Iterator==List)
			{
				break;
			}
		}
	}

	KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListForward(): END !\n"));
}
//-------------------------------------------------------------------------------------------------------
void DumpDoubleListBackward(LIST_ENTRY* List)
{
	KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListBackward(): BEGIN !\n"));

	if (IsListEmpty(List)==false)
	{
		// !!!!! MUSIM sa presunut na Blink, lebo HEAD NIKDY NEOBSAHUJE LIST ITEM.
		LIST_ENTRY*												Iterator=List->Blink;

		for(;;)
		{
			SMyDoubleListItem*									ListItem=CONTAINING_RECORD(Iterator,SMyDoubleListItem,MLink);

			KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListBackward(): ITEM [%d, %d] !\n",ListItem->MValue1,ListItem->MValue2));

			Iterator=Iterator->Blink;

			if (Iterator==List)
			{
				break;
			}
		}
	}

	KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListBackward(): END !\n"));
}
//-------------------------------------------------------------------------------------------------------
void DumpSinglyList(SINGLE_LIST_ENTRY* List)
{
	KdPrint((DRIVERNAME " - FUNCTION DumpSinglyList(): BEGIN !\n"));

	if (List->Next!=NULL)
	{
		// !!!!! MUSIM sa presunut na Next, lebo HEAD NIKDY NEOBSAHUJE LIST ITEM.
		SINGLE_LIST_ENTRY*										Iterator=List->Next;

		for(;;)
		{
			SMySingleListItem*									ListItem=CONTAINING_RECORD(Iterator,SMySingleListItem,MLink);

			KdPrint((DRIVERNAME " - FUNCTION DumpSinglyList(): ITEM [%d, %d] !\n",ListItem->MValue1,ListItem->MValue2));

			Iterator=Iterator->Next;

			if (Iterator==NULL)
			{
				break;
			}
		}
	}

	KdPrint((DRIVERNAME " - FUNCTION DumpSinglyList(): END !\n"));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest() bude v NON-PAGED MEMORY, kedze cast z nej pouziva SPIN LOCKS, ktore bezia v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlInterlockedDoublyLinkedListTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	// !!! SPIN LOCK sa pouziva v INTERLOCKED LISTS.
	PKSPIN_LOCK													SpinLock=(PKSPIN_LOCK) ExAllocatePoolWithTag(NonPagedPool,sizeof(KSPIN_LOCK),'KCOL');

	if (SpinLock!=NULL)
	{
		KeInitializeSpinLock(SpinLock);

		// !!! Reprezentuje HEAD, ktory NEOBSAHUJE LIST ITEM.
		LIST_ENTRY												List;

		// Nainicailizuje sa LIST.
		InitializeListHead(&List);

		KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): AFTER INITIALIZATION - IS LIST EMPTY [%d] !\n",IsListEmpty(&List)));

		for(;;)
		{
			SMyDoubleListItem*									MyDoubleListItem;
	
			// Alokuje sa ITEM.
			if ((MyDoubleListItem=AllocateDoubleListItem(1,101))==NULL)
			{
				break;
			}

			// ITEM sa prida ako POSLEDNY ITEM.
			ExInterlockedInsertTailList(&List,&MyDoubleListItem->MLink,SpinLock);
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): AFTER INSERT - IS LIST EMPTY [%d] !\n",IsListEmpty(&List)));
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
			DumpDoubleListForward(&List);

			// Alokuje sa ITEM.
			if ((MyDoubleListItem=AllocateDoubleListItem(2,102))==NULL)
			{
				break;
			}

			// ITEM sa prida ako POSLEDNY ITEM.
			ExInterlockedInsertTailList(&List,&MyDoubleListItem->MLink,SpinLock);
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
			DumpDoubleListForward(&List);

			// Alokuje sa ITEM.
			if ((MyDoubleListItem=AllocateDoubleListItem(3,103))==NULL)
			{
				break;
			}

			// ITEM sa prida ako PRVY ITEM.
			ExInterlockedInsertHeadList(&List,&MyDoubleListItem->MLink,SpinLock);
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
			DumpDoubleListForward(&List);

			// Alokuje sa ITEM.
			if ((MyDoubleListItem=AllocateDoubleListItem(4,104))==NULL)
			{
				break;
			}

			// ITEM sa prida ako PRVY ITEM.
			ExInterlockedInsertHeadList(&List,&MyDoubleListItem->MLink,SpinLock);
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
			DumpDoubleListForward(&List);

			// Alokuje sa ITEM.
			if ((MyDoubleListItem=AllocateDoubleListItem(5,105))==NULL)
			{
				break;
			}

			// ITEM sa prida ako POSLEDNY ITEM.
			ExInterlockedInsertTailList(&List,&MyDoubleListItem->MLink,SpinLock);
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
			DumpDoubleListForward(&List);

			DumpDoubleListBackward(&List);

			// Odstrani sa PRVY ITEM z LIST.
			LIST_ENTRY*											RemovedListEntry1=ExInterlockedRemoveHeadList(&List,SpinLock);
			SMyDoubleListItem*									RemovedListItem1=CONTAINING_RECORD(RemovedListEntry1,SMyDoubleListItem,MLink);
		
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): REMOVING ITEM [%d, %d] !\n",RemovedListItem1->MValue1,RemovedListItem1->MValue2));
			ExFreePoolWithTag(RemovedListItem1,'TSIL');
			RemovedListItem1=NULL;
			DumpDoubleListForward(&List);

			// Odstrani sa DRUHY ITEM z LIST.
			LIST_ENTRY*											RemovedListEntry2=List.Flink->Flink;

			RemoveEntryList(RemovedListEntry2);

			SMyDoubleListItem*									RemovedListItem2=CONTAINING_RECORD(RemovedListEntry2,SMyDoubleListItem,MLink);
		
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): REMOVING ITEM [%d, %d] !\n",RemovedListItem2->MValue1,RemovedListItem2->MValue2));
			ExFreePoolWithTag(RemovedListItem2,'TSIL');
			RemovedListItem2=NULL;
			DumpDoubleListForward(&List);

			DumpDoubleListBackward(&List);

			break;
		}

		// Odstrania sa VSETKY ITEMS z LIST.
		while(IsListEmpty(&List)==false)
		{
			LIST_ENTRY*											RemovedListEntry=ExInterlockedRemoveHeadList(&List,SpinLock);
			SMyDoubleListItem*									RemovedListItem=CONTAINING_RECORD(RemovedListEntry,SMyDoubleListItem,MLink);
		
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): REMOVING ITEM [%d, %d] !\n",RemovedListItem->MValue1,RemovedListItem->MValue2));

			ExFreePoolWithTag(RemovedListItem,'TSIL');
			RemovedListItem=NULL;
		}

		ExFreePoolWithTag(SpinLock,'KCOL');

		KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): AFTER CLEAR - IS LIST EMPTY [%d] !\n",IsListEmpty(&List)));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedDoublyLinkedListTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest() bude v NON-PAGED MEMORY, kedze cast z nej pouziva SPIN LOCKS, ktore bezia v DISPATCH_LEVEL.
#pragma code_seg()
NTSTATUS ProcessIOControlInterlockedSinglyLinkedListTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	// !!! SPIN LOCK sa pouziva v INTERLOCKED LISTS.
	PKSPIN_LOCK													SpinLock=(PKSPIN_LOCK) ExAllocatePoolWithTag(NonPagedPool,sizeof(KSPIN_LOCK),'KCOL');

	if (SpinLock!=NULL)
	{
		KeInitializeSpinLock(SpinLock);

		// !!! Reprezentuje HEAD, ktory NEOBSAHUJE LIST ITEM.
		SINGLE_LIST_ENTRY										List;

		// Nainicailizuje sa LIST.
		List.Next=NULL;

		KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): AFTER INITIALIZATION - IS LIST EMPTY [%d] !\n",(List.Next==NULL)));

		for(;;)
		{
			SMySingleListItem*									MySingleListItem;
	
			// Alokuje sa ITEM.
			if ((MySingleListItem=AllocateSingleListItem(1,101))==NULL)
			{
				break;
			}

			// Prida ITEM na VRCHOL STACKU.
			ExInterlockedPushEntryList(&List,&MySingleListItem->MLink,SpinLock);
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): AFTER INSERT - IS LIST EMPTY [%d] !\n",(List.Next==NULL)));
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): INSERTING ITEM [%d, %d] !\n",MySingleListItem->MValue1,MySingleListItem->MValue2));
			DumpSinglyList(&List);

			// Alokuje sa ITEM.
			if ((MySingleListItem=AllocateSingleListItem(2,102))==NULL)
			{
				break;
			}

			// Prida ITEM na VRCHOL STACKU.
			ExInterlockedPushEntryList(&List,&MySingleListItem->MLink,SpinLock);
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): INSERTING ITEM [%d, %d] !\n",MySingleListItem->MValue1,MySingleListItem->MValue2));
			DumpSinglyList(&List);

			// Alokuje sa ITEM.
			if ((MySingleListItem=AllocateSingleListItem(3,103))==NULL)
			{
				break;
			}

			// Prida ITEM na VRCHOL STACKU.
			ExInterlockedPushEntryList(&List,&MySingleListItem->MLink,SpinLock);
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): INSERTING ITEM [%d, %d] !\n",MySingleListItem->MValue1,MySingleListItem->MValue2));
			DumpSinglyList(&List);

			// Alokuje sa ITEM.
			if ((MySingleListItem=AllocateSingleListItem(4,104))==NULL)
			{
				break;
			}

			// Prida ITEM na VRCHOL STACKU.
			ExInterlockedPushEntryList(&List,&MySingleListItem->MLink,SpinLock);
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): INSERTING ITEM [%d, %d] !\n",MySingleListItem->MValue1,MySingleListItem->MValue2));
			DumpSinglyList(&List);

			// Odstrani sa ITEM z VRCHOLA LIST.
			SINGLE_LIST_ENTRY*									RemovedListEntry1=ExInterlockedPopEntryList(&List,SpinLock);
			SMySingleListItem*									RemovedListItem1=CONTAINING_RECORD(RemovedListEntry1,SMySingleListItem,MLink);
		
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): REMOVING ITEM [%d, %d] !\n",RemovedListItem1->MValue1,RemovedListItem1->MValue2));
			ExFreePoolWithTag(RemovedListItem1,'TSIL');
			RemovedListItem1=NULL;
			DumpSinglyList(&List);

			// Odstrani sa ITEM z VRCHOLA LIST.
			SINGLE_LIST_ENTRY*									RemovedListEntry2=ExInterlockedPopEntryList(&List,SpinLock);
			SMySingleListItem*									RemovedListItem2=CONTAINING_RECORD(RemovedListEntry2,SMySingleListItem,MLink);
		
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): REMOVING ITEM [%d, %d] !\n",RemovedListItem2->MValue1,RemovedListItem2->MValue2));
			ExFreePoolWithTag(RemovedListItem2,'TSIL');
			RemovedListItem2=NULL;
			DumpSinglyList(&List);

			break;
		}

		// Odstrania sa VSETKY ITEMS z LIST.
		while((List.Next!=NULL))
		{
			SINGLE_LIST_ENTRY*									RemovedListEntry=ExInterlockedPopEntryList(&List,SpinLock);
			SMySingleListItem*									RemovedListItem=CONTAINING_RECORD(RemovedListEntry,SMySingleListItem,MLink);
		
			KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): REMOVING ITEM [%d, %d] !\n",RemovedListItem->MValue1,RemovedListItem->MValue2));

			ExFreePoolWithTag(RemovedListItem,'TSIL');
			RemovedListItem=NULL;
		}

		ExFreePoolWithTag(SpinLock,'KCOL');

		KdPrint((DRIVERNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): AFTER CLEAR - IS LIST EMPTY [%d] !\n",(List.Next==NULL)));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedSinglyLinkedListTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlInterlockedArithmetic1Test() bude v NON-PAGED MEMORY, kedze cast z nej pouziva SPIN LOCKS, ktore bezia v DISPATCH_LEVEL.
#pragma code_seg()
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlInterlockedArithmetic1Test(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	PKSPIN_LOCK													SpinLock=(PKSPIN_LOCK) ExAllocatePoolWithTag(NonPagedPool,sizeof(KSPIN_LOCK),'KCOL');

	if (SpinLock!=NULL)
	{
		KeInitializeSpinLock(SpinLock);

		// !!!!! KEDZE INTERLOCKED FUNCTIONS pouzivaju SPIN LOCK, ktory DVIHNE IRQL na DISPATCH_LEVEL, tak VSETKY PARAMETERS MUSIA byt v NON-PAGED MEMORY.
		// !!!!! KEDZE KERNEL STACK je v NON-PAGED MEMORY, tak je ho mozne pouzit na ulozenie PARAMETERS pre INTERLOCKED FUNCTIONS.
		LARGE_INTEGER											LeftOperand1;
		LARGE_INTEGER											RightOperand1;
		LARGE_INTEGER											Result1;

		LeftOperand1.QuadPart=100;
		RightOperand1.QuadPart=60;
		Result1.QuadPart=0;
		
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic1Test(): BEFORE - LEFT [%I64d], RIGHT [%I64d], RESULT [%I64d] !\n",LeftOperand1.QuadPart,RightOperand1.QuadPart,Result1.QuadPart));

		Result1=ExInterlockedAddLargeInteger(&LeftOperand1,RightOperand1,SpinLock);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic1Test(): AFTER - LEFT [%I64d], RIGHT [%I64d], RESULT [%I64d] !\n",LeftOperand1.QuadPart,RightOperand1.QuadPart,Result1.QuadPart));

		ULONG													LeftOperand2;
		ULONG													RightOperand2;
		ULONG													Result2;

		LeftOperand2=10;
		RightOperand2=6;
		Result2=0;

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic1Test(): BEFORE - LEFT [%d], RIGHT [%d], RESULT [%d] !\n",LeftOperand2,RightOperand2,Result2));

		Result2=ExInterlockedAddUlong(&LeftOperand2,RightOperand2,SpinLock);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic1Test(): AFTER - LEFT [%d], RIGHT [%d], RESULT [%d] !\n",LeftOperand2,RightOperand2,Result2));

		LONGLONG												Destination;
		LONGLONG												NewValue;
		LONGLONG												Compared1;
		LONGLONG												Compared2;
		LONGLONG												ExchangeResult1;
		LONGLONG												ExchangeResult2;

		Destination=30;
		NewValue=60;
		Compared1=40;
		Compared2=30;
		ExchangeResult1=0;
		ExchangeResult2=0;

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic1Test(): BEFORE - DESTINATION [%I64d], NEW VALUE [%I64d], COMPARED1 [%I64d], COMPARED2 [%I64d], RESULT 1 [%I64d], RESULT 2 [%I64d] !\n",Destination,NewValue,Compared1,Compared2,ExchangeResult1,ExchangeResult2));

		ExchangeResult1=ExInterlockedCompareExchange64(&Destination,&NewValue,&Compared1,SpinLock);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic1Test(): AFTER COMPARE 1 - DESTINATION [%I64d], NEW VALUE [%I64d], COMPARED1 [%I64d], COMPARED2 [%I64d], RESULT 1 [%I64d], RESULT 2 [%I64d] !\n",Destination,NewValue,Compared1,Compared2,ExchangeResult1,ExchangeResult2));

		ExchangeResult2=ExInterlockedCompareExchange64(&Destination,&NewValue,&Compared2,SpinLock);

		ExFreePoolWithTag(SpinLock,'KCOL');

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic1Test(): AFTER COMPARE 2 - DESTINATION [%I64d], NEW VALUE [%I64d], COMPARED1 [%I64d], COMPARED2 [%I64d], RESULT 1 [%I64d], RESULT 2 [%I64d] !\n",Destination,NewValue,Compared1,Compared2,ExchangeResult1,ExchangeResult2));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic1Test(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION ProcessIOControlInterlockedArithmetic2Test() bude v NON-PAGED MEMORY, kedze cast z nej pouziva SPIN LOCKS, ktore bezia v DISPATCH_LEVEL.
#pragma code_seg()
NTSTATUS ProcessIOControlInterlockedArithmetic2Test(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	// !!!!! KEDZE INTERLOCKED FUNCTIONS nepouzivaju SPIN LOCK, tak PARAMETERS mozu byt aj v PAGED MEMORY.
	LONG														LeftOperand;
	LONG														RightOperand;
	LONG														Result;

	LeftOperand=10;
	RightOperand=6;
	Result=0;

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic2Test(): BEFORE - LEFT [%d], RIGHT [%d], RESULT [%d] !\n",LeftOperand,RightOperand,Result));

	Result=InterlockedExchangeAdd(&LeftOperand,RightOperand);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic2Test(): AFTER - LEFT [%d], RIGHT [%d], RESULT [%d] !\n",LeftOperand,RightOperand,Result));

	LONG														Destination;
	LONG														NewValue;
	LONG														Compared1;
	LONG														Compared2;
	LONG														ExchangeResult1;
	LONG														ExchangeResult2;

	Destination=30;
	NewValue=60;
	Compared1=40;
	Compared2=30;
	ExchangeResult1=0;
	ExchangeResult2=0;

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic2Test(): BEFORE - DESTINATION [%d], NEW VALUE [%d], COMPARED1 [%d], COMPARED2 [%d], RESULT 1 [%d], RESULT 2 [%d] !\n",Destination,NewValue,Compared1,Compared2,ExchangeResult1,ExchangeResult2));

	ExchangeResult1=InterlockedCompareExchange(&Destination,NewValue,Compared1);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic2Test(): AFTER COMPARE 1 - DESTINATION [%d], NEW VALUE [%d], COMPARED1 [%d], COMPARED2 [%d], RESULT 1 [%d], RESULT 2 [%d] !\n",Destination,NewValue,Compared1,Compared2,ExchangeResult1,ExchangeResult2));

	ExchangeResult2=InterlockedCompareExchange(&Destination,NewValue,Compared2);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic2Test(): AFTER COMPARE 2 - DESTINATION [%d], NEW VALUE [%d], COMPARED1 [%d], COMPARED2 [%d], RESULT 1 [%d], RESULT 2 [%d] !\n",Destination,NewValue,Compared1,Compared2,ExchangeResult1,ExchangeResult2));

	LONG														Increment=30;
	LONG														Decrement=40;
	LONG														Result1=0;
	LONG														Result2=0;

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic2Test(): BEFORE - INCREMENT [%d], RESULT [%d] !\n",Increment,Result1));

	Result1=InterlockedIncrement(&Increment);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic2Test(): AFTER - INCREMENT [%d], RESULT [%d] !\n",Increment,Result1));

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic2Test(): BEFORE - DECREMENT [%d], RESULT [%d] !\n",Decrement,Result2));

	Result2=InterlockedDecrement(&Decrement);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlInterlockedArithmetic2Test(): AFTER - DECREMENT [%d], RESULT [%d] !\n",Decrement,Result2));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_INITIALIZE)
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryKey)
{
	ANSI_STRING													RegistryKeyANSI;

	RtlUnicodeStringToAnsiString(&RegistryKeyANSI,RegistryKey,TRUE);

	KdPrint((DRIVERLOGNAME " - FUNCTION DriverEntry(): DriverObject [%p], RegistryKey [%s] !\n",DriverObject,RegistryKeyANSI.Buffer));
	
	RtlFreeAnsiString(&RegistryKeyANSI);

	DriverObject->DriverUnload=DriverUnload;
	DriverObject->DriverExtension->AddDevice=AddDevice;

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchDeviceControl;
	DriverObject->MajorFunction[IRP_MJ_POWER]=DispatchPower;
	DriverObject->MajorFunction[IRP_MJ_PNP]=DispatchPNP;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL]=DispatchWMI;

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_UNLOAD)
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION DriverUnload(): DriverObject [%p] !\n",DriverObject));

	if (TestPeriodicTimerParam!=NULL)
	{
		// !!!!! Ak by sa PERIODIC KERNEL TIMER NEZASTAVIL pri DriverUnload(), tak by to sposobilo BUG CHECK.
		KeCancelTimer(&TestPeriodicTimerParam->MTimer);

		ExFreePoolWithTag(TestPeriodicTimerParam,' MIT');
		TestPeriodicTimerParam=NULL;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_ADD_DEVICE)
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PhysicalDeviceObject)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION AddDevice(): DriverObject [%p], PhysicalDeviceObject [%p] !\n",DriverObject,PhysicalDeviceObject));

	NTSTATUS													Status;
	PDEVICE_OBJECT												NewDeviceObject=NULL;
	UNICODE_STRING												DeviceName;

	RtlInitUnicodeString(&DeviceName, L"\\DosDevices\\" LDRIVERNAME);

	// !!! Dlzku zvacsim na NASOBOK 8, aby POINTER ukazujuci ZA DEVICE_EXTENSION bol NASOBKOM 8. Je to dolezite, pretoze POINTER za DEVICE_EXTENSION bude odkazovat na PGENERIC_EXTENSION pouzivanu na POWER a PNP SUPPORT.
	ULONG														DeviceExtensionSize=(sizeof(DEVICE_EXTENSION)+7)&~7;
	ULONG														TotalDeviceExtensionSize=DeviceExtensionSize+GetSizeofGenericExtension();

	Status=IoCreateDevice(DriverObject,TotalDeviceExtensionSize,&DeviceName,FILE_DEVICE_UNKNOWN,FILE_DEVICE_SECURE_OPEN,FALSE,&NewDeviceObject);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION AddDevice(): IoCreateDevice() FAILED [%X] !\n",Status));
		return(Status);
	}
	
	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) NewDeviceObject->DeviceExtension;

	do
	{
		DeviceExtensionData->DeviceObject=NewDeviceObject;
		DeviceExtensionData->PDO=PhysicalDeviceObject;
		DeviceExtensionData->LowerDeviceObject=IoAttachDeviceToDeviceStack(NewDeviceObject,PhysicalDeviceObject);
		DeviceExtensionData->Handles=0;

		if (DeviceExtensionData->LowerDeviceObject==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION AddDevice(): IoAttachDeviceToDeviceStack() FAILED !\n"));
			Status=STATUS_DEVICE_REMOVED;
			break;
		}

		NewDeviceObject->Flags|=DO_POWER_PAGABLE;

		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_SYNCHRONIZATION_DRIVER,NULL,&DeviceExtensionData->InterfaceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION AddDevice(): IoRegisterDeviceInterface() FAILED [%X] !\n",Status));
			break;
		}

		IoInitializeRemoveLock(&DeviceExtensionData->RemoveLock,0,0,0);

		// !!! Inicializujem POINTER na PGENERIC_EXTENSION, tak aby ukazoval do ALOKOVANEJ MEMORY na KONCI DEVICE_EXTENSION STRUCTURE.
		DeviceExtensionData->PowerAndPNP=PGENERIC_EXTENSION((PUCHAR(DeviceExtensionData)+DeviceExtensionSize));

		// !!! STRUCTURE sa pouziva na inicializaciu PGENERIC_EXTENSION.
		GENERIC_INIT_STRUCT										GenericInitStructure={sizeof(GENERIC_INIT_STRUCT)};

		GenericInitStructure.MDeviceObject=NewDeviceObject;
		GenericInitStructure.MPDO=PhysicalDeviceObject;
		GenericInitStructure.MLDO=DeviceExtensionData->LowerDeviceObject;
		GenericInitStructure.MRemoveLock=&DeviceExtensionData->RemoveLock;
		GenericInitStructure.MStartDevice=StartDevice;
		GenericInitStructure.MStopDevice=StopDevice;
		GenericInitStructure.MRemoveDevice=RemoveDevice;
		RtlInitUnicodeString(&GenericInitStructure.MDebugName,LDRIVERNAME);

		Status=InitializeGenericExtension(DeviceExtensionData->PowerAndPNP,&GenericInitStructure);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION AddDevice(): InitializeGenericExtension() FAILED [%X] !\n",Status));
			break;
		}

		TestPeriodicTimerParam=(STestPeriodicTimerParam*) ExAllocatePoolWithTag(NonPagedPool,sizeof(STestPeriodicTimerParam),' MIT');

		if (TestPeriodicTimerParam!=NULL)
		{
			// !!! KERNEL TIMER a DPC MUSI byt v NON-PAGED MEMORY.
			RtlZeroMemory(TestPeriodicTimerParam,sizeof(STestPeriodicTimerParam));

			NewDeviceObject->Flags&=~DO_DEVICE_INITIALIZING;

			KdPrint((DRIVERLOGNAME " - FUNCTION AddDevice(): DEVICE_OBJECT INITIALIZED, Flags [%X], Characteristics [%X], AlignmentRequirement [%X] !\n",NewDeviceObject->Flags,NewDeviceObject->Characteristics,NewDeviceObject->AlignmentRequirement));

			Status=STATUS_SUCCESS;
		}
		else
		{
			Status=STATUS_NO_MEMORY;
		}
	}
	while(FALSE);

	if (NT_SUCCESS(Status)==false)
	{
		if (DeviceExtensionData->InterfaceName.Buffer!=NULL)
		{
			RtlFreeUnicodeString(&DeviceExtensionData->InterfaceName);
		}

		if (DeviceExtensionData->LowerDeviceObject!=NULL)
		{
			IoDetachDevice(DeviceExtensionData->LowerDeviceObject);
		}

		if (NewDeviceObject!=NULL)
		{
			IoDeleteDevice(NewDeviceObject);
			NewDeviceObject=NULL;
		}
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS __stdcall StartDevice(PDEVICE_OBJECT DeviceObject, PCM_PARTIAL_RESOURCE_LIST, PCM_PARTIAL_RESOURCE_LIST)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION StartDevice(): DeviceObject [%p] !\n",DeviceObject));

	NTSTATUS													Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
VOID __stdcall StopDevice(IN PDEVICE_OBJECT DeviceObject, BOOLEAN)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION StopDevice(): DeviceObject [%p] !\n",DeviceObject));
}
//-------------------------------------------------------------------------------------------------------
VOID __stdcall RemoveDevice(IN PDEVICE_OBJECT DeviceObject)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION RemoveDevice(): DeviceObject [%p] !\n",DeviceObject));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	if (DeviceExtensionData->LowerDeviceObject!=NULL)
	{
		IoDetachDevice(DeviceExtensionData->LowerDeviceObject);
	}

	IoDeleteDevice(DeviceObject);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION sa vola, ked USER MODE PROCESS vytvori HANDLE na DRIVER.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CREATE)
NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchCreate(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// Inkrementuje sa HANDLER COUNTER.
	InterlockedIncrement(&DeviceExtensionData->Handles);

	NTSTATUS													Status=CompleteRequest(IRP,STATUS_SUCCESS,0);

	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchCreate(): END - DeviceObject [%p], IRP [%p], Status [%X], Handles [%d] !\n",DeviceObject,IRP,Status,DeviceExtensionData->Handles));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION sa vola, ked USER MODE PROCESS uzatvori HANDLE na DRIVER.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLOSE)
NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchClose(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// Dekrementuje sa HANDLER COUNTER.
	InterlockedDecrement(&DeviceExtensionData->Handles);

	NTSTATUS													Status=CompleteRequest(IRP,STATUS_SUCCESS,0);

	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchClose(): END - DeviceObject [%p], IRP [%p], Status [%X], Handles [%d] !\n",DeviceObject,IRP,Status,DeviceExtensionData->Handles));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION spracovava IO CONTROL MESSAGES.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_DEVICE_CONTROL)
NTSTATUS DispatchDeviceControl(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchSystemControl(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	NTSTATUS													Status;
	ULONG														Info=0;
	
	Status=IoAcquireRemoveLock(&DeviceExtensionData->RemoveLock,IRP);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION DispatchSystemControl(): END 1 - DeviceObject [%p], IRP [%p], Status [%X] !\n",DeviceObject,IRP,Status));

		return(CompleteRequest(IRP,Status,0));
	}

	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);
	ULONG														Code=Stack->Parameters.DeviceIoControl.IoControlCode;
	ULONG														InputBufferLength=Stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG														OutputBufferLength=Stack->Parameters.DeviceIoControl.OutputBufferLength;

	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchSystemControl(): Code [%d], InputBufferLength [%d], OutputBufferLength [%d] !\n",Code,InputBufferLength,OutputBufferLength));

	switch(Code)
	{
		case IOCTL_READ_FILE:
		{
			Status=ProcessIOControlReadFile(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_THREAD_TEST:
		{
			Status=ProcessIOControlThreadTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_IRQL_CHANGE_TEST:
		{
			Status=ProcessIOControlIRQLChangeTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SPIN_LOCK_TEST:
		{
			Status=ProcessIOControlSpinLockTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SPIN_LOCK_WITH_THREADS_TEST:
		{
			Status=ProcessIOControlSpinLockWithThreadsTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_QUEUED_SPIN_LOCK_WITH_THREADS_TEST:
		{
			Status=ProcessIOControlQueuedSpinLockWithThreadsTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_WAIT_FOR_MULTIPLE_OBJECTS_TEST:
		{
			Status=ProcessIOControlWaitForMultipleObjectsTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_MANUAL_RESET_EVENT_TEST:
		{
			Status=ProcessIOControlManualResetEventTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_AUTO_RESET_EVENT_TEST:
		{
			Status=ProcessIOControlAutoResetEventTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SEMAPHORE_TEST:
		{
			Status=ProcessIOControlSemaphoreTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_MUTEX_TEST:
		{
			Status=ProcessIOControlMutexTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_MANUAL_RESET_TIMER_TEST:
		{
			Status=ProcessIOControlManualResetTimerTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_AUTO_RESET_TIMER_TEST:
		{
			Status=ProcessIOControlAutoResetTimerTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_DPC_TIMER_1_TEST:
		{
			Status=ProcessIOControlDPCTimerTest1(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_DPC_TIMER_2_TEST:
		{
			Status=ProcessIOControlDPCTimerTest2(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_DPC_TIMER_3_TEST:
		{
			Status=ProcessIOControlDPCTimerTest3(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_APC_TEST:
		{
			Status=ProcessIOControlAPCTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_FAST_MUTEX_TEST:
		{
			Status=ProcessIOControlFastMutexTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_EXECUTIVE_RESOURCE_TEST:
		{
			Status=ProcessIOControlExecutiveResourceTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_INTERLOCKED_DOUBLY_LINKED_LIST:
		{
			Status=ProcessIOControlInterlockedDoublyLinkedListTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_INTERLOCKED_SINGLY_LINKED_LIST:
		{
			Status=ProcessIOControlInterlockedSinglyLinkedListTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_INTERLOCKED_ARITHMETIC_1:
		{
			Status=ProcessIOControlInterlockedArithmetic1Test(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_INTERLOCKED_ARITHMETIC_2:
		{
			Status=ProcessIOControlInterlockedArithmetic2Test(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		default:
		{
			Status=STATUS_INVALID_DEVICE_REQUEST;
		}
		break;
	}

	Status=CompleteRequest(IRP,Status,Info);

	IoReleaseRemoveLock(&DeviceExtensionData->RemoveLock,IRP);

	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchSystemControl(): END 2 - DeviceObject [%p], IRP [%p], Status [%X] !\n",DeviceObject,IRP,Status));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_POWER)
NTSTATUS DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchPower(): DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	return(GenericDispatchPower(DeviceExtensionData->PowerAndPNP,IRP));
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_PNP)
NTSTATUS DispatchPNP(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchPNP(): DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	
	return(GenericDispatchPNP(DeviceExtensionData->PowerAndPNP,IRP));
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SYSTEM_CONTROL)
NTSTATUS DispatchWMI(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION DispatchWMI(): DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											PDX=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	IoSkipCurrentIrpStackLocation(IRP);

	return(IoCallDriver(PDX->LowerDeviceObject,IRP));
}
//-------------------------------------------------------------------------------------------------------