//----------------------------------------------------------------------------------------------------------------------
#include "TestSpinLocksIRQL.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
KSPIN_LOCK														SpinLocksIRQLLock;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void SpinLocksIRQLThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	KIRQL														OldIRQL;

	// !!!!! IRQL je zvysene na IRQL [DISPATCH_LEVEL].
	KeAcquireSpinLock(&SpinLocksIRQLLock,&OldIRQL);

	KIRQL														NewIRQL=KeGetCurrentIrql();

	// !!!!! IRQL je znizene na povodne IRQL.
	// !!! Ako IRQL sa musi pouzit to, ktore vratilo MACRO [KeAcquireSpinLock()].
	KeReleaseSpinLock(&SpinLocksIRQLLock,OldIRQL);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 OLD IRQL [%hhu] NEW IRQL [%hhu].\n",FunctionName,OldIRQL,NewIRQL));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void SpinLocksIRQLThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	KIRQL														OldIRQL;

	// !!!!! IRQL je zvysene na IRQL [DISPATCH_LEVEL].
	KeAcquireSpinLock(&SpinLocksIRQLLock,&OldIRQL);

	KIRQL														NewIRQL=KeGetCurrentIrql();

	// !!!!! IRQL je znizene na povodne IRQL.
	// !!! Ako IRQL sa musi pouzit to, ktore vratilo MACRO [KeAcquireSpinLock()].
	KeReleaseSpinLock(&SpinLocksIRQLLock,OldIRQL);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 OLD IRQL [%hhu] NEW IRQL [%hhu].\n",FunctionName,OldIRQL,NewIRQL));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSpinLocksIRQL(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa SPIN LOCK.
	KeInitializeSpinLock(&SpinLocksIRQLLock);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;

	Status=CHelpers::CreateThread("111",SpinLocksIRQLThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

	Status=CHelpers::CreateThread("222",SpinLocksIRQLThread2,nullptr,&ThreadObject2);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject1);

		return;
	}

	PVOID														Object[]{ThreadObject1,ThreadObject2};
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

	ObDereferenceObject(ThreadObject2);
	ObDereferenceObject(ThreadObject1);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------