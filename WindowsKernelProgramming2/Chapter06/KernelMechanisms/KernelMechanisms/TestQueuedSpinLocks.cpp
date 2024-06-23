//----------------------------------------------------------------------------------------------------------------------
#include "TestQueuedSpinLocks.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
KSPIN_LOCK														QueuedSpinLocksLock;
KEVENT															QueuedSpinLocksManualResetEventsLock;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void QueuedSpinLocksThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	// !!! Caka sa na spustenie THREAD.
	KeWaitForSingleObject(&QueuedSpinLocksManualResetEventsLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	CHelpers::Sleep(100);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	ULONG64														Variable=0;
	KLOCK_QUEUE_HANDLE											LockHandle;

	// !!!!! IRQL je zvysene na IRQL [DISPATCH_LEVEL].
	KeAcquireInStackQueuedSpinLock(&QueuedSpinLocksLock,&LockHandle);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 has SHARED RESOURCE.\n",FunctionName));

	KIRQL														NewIRQL=KeGetCurrentIrql();

	for(LONG64 Index=0;Index<LONG64(1000*1000*1000);Index++)
	{
		Variable++;
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 NEW IRQL [%hhu] VALUE [%I64d].\n",FunctionName,NewIRQL,Variable));

	// !!!!! IRQL je znizene na povodne IRQL.
	KeReleaseInStackQueuedSpinLock(&LockHandle);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void QueuedSpinLocksThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	// !!! Caka sa na spustenie THREAD.
	KeWaitForSingleObject(&QueuedSpinLocksManualResetEventsLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	CHelpers::Sleep(300);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	ULONG64														Variable=0;
	KLOCK_QUEUE_HANDLE											LockHandle;

	// !!!!! IRQL je zvysene na IRQL [DISPATCH_LEVEL].
	KeAcquireInStackQueuedSpinLock(&QueuedSpinLocksLock,&LockHandle);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 has SHARED RESOURCE.\n",FunctionName));

	KIRQL														NewIRQL=KeGetCurrentIrql();

	for(LONG64 Index=0;Index<LONG64(1000*1000*1000);Index++)
	{
		Variable++;
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 NEW IRQL [%hhu] VALUE [%I64d].\n",FunctionName,NewIRQL,Variable));

	// !!!!! IRQL je znizene na povodne IRQL.
	KeReleaseInStackQueuedSpinLock(&LockHandle);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void QueuedSpinLocksThread3(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	// !!! Caka sa na spustenie THREAD.
	KeWaitForSingleObject(&QueuedSpinLocksManualResetEventsLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	CHelpers::Sleep(500);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 STARTED.\n",FunctionName));

	ULONG64														Variable=0;
	KLOCK_QUEUE_HANDLE											LockHandle;

	// !!!!! IRQL je zvysene na IRQL [DISPATCH_LEVEL].
	KeAcquireInStackQueuedSpinLock(&QueuedSpinLocksLock,&LockHandle);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 has SHARED RESOURCE.\n",FunctionName));

	KIRQL														NewIRQL=KeGetCurrentIrql();

	for(LONG64 Index=0;Index<LONG64(1000*1000*1000);Index++)
	{
		Variable++;
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 NEW IRQL [%hhu] VALUE [%I64d].\n",FunctionName,NewIRQL,Variable));

	// !!!!! IRQL je znizene na povodne IRQL.
	KeReleaseInStackQueuedSpinLock(&LockHandle);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestQueuedSpinLocks(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa SPIN LOCK.
	KeInitializeSpinLock(&QueuedSpinLocksLock);

	// !!! Inicializuje sa MANUAL RESET EVENT.
	KeInitializeEvent(&QueuedSpinLocksManualResetEventsLock,EVENT_TYPE::NotificationEvent,FALSE);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;
	PETHREAD													ThreadObject3=NULL;

	Status=CHelpers::CreateThread("111",QueuedSpinLocksThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

	Status=CHelpers::CreateThread("222",QueuedSpinLocksThread2,nullptr,&ThreadObject2);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject1);

		return;
	}

	Status=CHelpers::CreateThread("333",QueuedSpinLocksThread3,nullptr,&ThreadObject3);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject2);
		ObDereferenceObject(ThreadObject1);

		return;
	}

	CHelpers::Sleep(1000);

	// !!! Po nastaveni EVENT sa rozbehnu THREAD 1, THREAD 2 aj THREAD 3.
	KeSetEvent(&QueuedSpinLocksManualResetEventsLock,1,FALSE);

	PVOID														Object[]{ThreadObject1,ThreadObject2,ThreadObject3};
    ULONG														Count=(sizeof(Object)/sizeof(Object[0]));
    PLARGE_INTEGER												Timeout=nullptr;

	ASSERT(Count<=THREAD_WAIT_OBJECTS);

	// !!!!! FUNCTION VZDY vracia STATUS VALUE pre ktoru MACRO [NT_SUCCESS()] vracia TRUE.
	Status=KeWaitForMultipleObjects(Count,Object,WAIT_TYPE::WaitAll,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,Timeout,nullptr);

	if (Status==STATUS_SUCCESS)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREADS FINISHED.\n",FunctionName));
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to WAIT for THREADS with ERROR CODE [%lX].\n",FunctionName,Status));
	}

	ObDereferenceObject(ThreadObject3);
	ObDereferenceObject(ThreadObject2);
	ObDereferenceObject(ThreadObject1);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------