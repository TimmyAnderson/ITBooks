//----------------------------------------------------------------------------------------------------------------------
#include "TestManualResetEvents.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
KEVENT															ManualResetEventsLock;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ManualResetEventsThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 BEFORE WAIT 1.\n",FunctionName));

	Status=KeWaitForSingleObject(&ManualResetEventsLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED WAIT 1 with CODE [%lX].\n",FunctionName,Status));

	CHelpers::Sleep(300);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 BEFORE WAIT 2.\n",FunctionName));

	Status=KeWaitForSingleObject(&ManualResetEventsLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED WAIT 2 with CODE [%lX].\n",FunctionName,Status));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ManualResetEventsThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 BEFORE WAIT 1.\n",FunctionName));

	Status=KeWaitForSingleObject(&ManualResetEventsLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED WAIT 1 with CODE [%lX].\n",FunctionName,Status));

	CHelpers::Sleep(300);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 BEFORE WAIT 2.\n",FunctionName));

	Status=KeWaitForSingleObject(&ManualResetEventsLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED WAIT 2 with CODE [%lX].\n",FunctionName,Status));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ManualResetEventsThread3(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 STARTED.\n",FunctionName));

	CHelpers::Sleep(1000);

	LONG														EventState1=KeReadStateEvent(&ManualResetEventsLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 EVENT STATE [%ld].\n",FunctionName,EventState1));

	// !!! Po nastaveni EVENT sa rozbehnu THREAD 1 aj THREAD 2.
	KeSetEvent(&ManualResetEventsLock,1,FALSE);

	LONG														EventState2=KeReadStateEvent(&ManualResetEventsLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 EVENT STATE [%ld].\n",FunctionName,EventState2));

	// !!! EVENT sa nastavi do NON-SINGALED STATE.
	KeResetEvent(&ManualResetEventsLock);

	LONG														EventState3=KeReadStateEvent(&ManualResetEventsLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 EVENT STATE [%ld].\n",FunctionName,EventState3));

	CHelpers::Sleep(1000);

	// !!! Po nastaveni EVENT sa rozbehnu THREAD 1 aj THREAD 2.
	KeSetEvent(&ManualResetEventsLock,1,FALSE);

	LONG														EventState4=KeReadStateEvent(&ManualResetEventsLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 EVENT STATE [%ld].\n",FunctionName,EventState4));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestManualResetEvents(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa MANUAL RESET EVENT.
	KeInitializeEvent(&ManualResetEventsLock,EVENT_TYPE::NotificationEvent,FALSE);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;
	PETHREAD													ThreadObject3=NULL;

	Status=CHelpers::CreateThread("111",ManualResetEventsThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

	Status=CHelpers::CreateThread("222",ManualResetEventsThread2,nullptr,&ThreadObject2);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject1);

		return;
	}

	Status=CHelpers::CreateThread("333",ManualResetEventsThread3,nullptr,&ThreadObject3);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject2);
		ObDereferenceObject(ThreadObject1);

		return;
	}

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