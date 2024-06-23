//----------------------------------------------------------------------------------------------------------------------
#include "TestNamedAutoResetEvents.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void NamedAutoResetEventsThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	UNICODE_STRING												EventName;
	HANDLE														EventHandle;
	PKEVENT														Event;
	NTSTATUS													Status;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	// !!! EVENT NAME musi obsahovat FULL PATH v OBJECT MANAGER.
	RtlInitUnicodeString(&EventName,L"\\BaseNamedObjects\\KernelMechanismsAutoEvent");

	// !!! Inicializuje sa NAMED AUTO RESET EVENT.
	Event=IoCreateSynchronizationEvent(&EventName,&EventHandle);

	if (Event!=nullptr)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 BEFORE WAIT 1.\n",FunctionName));

		Status=KeWaitForSingleObject(Event,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED WAIT 1 with CODE [%lX].\n",FunctionName,Status));

		CHelpers::Sleep(300);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 BEFORE WAIT 2.\n",FunctionName));

		Status=KeWaitForSingleObject(Event,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED WAIT 2 with CODE [%lX].\n",FunctionName,Status));

		// !!!!! HANDLE na EVENT sa MUSI uvolnit, ked uz sa viac nepouziva.
		ZwClose(EventHandle);
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FAILED to CREATE NAMED AUTO RESET EVENT.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void NamedAutoResetEventsThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	UNICODE_STRING												EventName;
	HANDLE														EventHandle;
	PKEVENT														Event;
	NTSTATUS													Status;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	// !!! EVENT NAME musi obsahovat FULL PATH v OBJECT MANAGER.
	RtlInitUnicodeString(&EventName,L"\\BaseNamedObjects\\KernelMechanismsAutoEvent");

	// !!! Inicializuje sa NAMED AUTO RESET EVENT.
	Event=IoCreateSynchronizationEvent(&EventName,&EventHandle);

	if (Event!=nullptr)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 BEFORE WAIT 1.\n",FunctionName));

		Status=KeWaitForSingleObject(Event,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED WAIT 1 with CODE [%lX].\n",FunctionName,Status));

		CHelpers::Sleep(300);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 BEFORE WAIT 2.\n",FunctionName));

		Status=KeWaitForSingleObject(Event,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED WAIT 2 with CODE [%lX].\n",FunctionName,Status));

		// !!!!! HANDLE na EVENT sa MUSI uvolnit, ked uz sa viac nepouziva.
		ZwClose(EventHandle);
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FAILED to CREATE NAMED AUTO RESET EVENT.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void NamedAutoResetEventsThread3(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	UNICODE_STRING												EventName;
	HANDLE														EventHandle;
	PKEVENT														Event;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 STARTED.\n",FunctionName));

	// !!! EVENT NAME musi obsahovat FULL PATH v OBJECT MANAGER.
	RtlInitUnicodeString(&EventName,L"\\BaseNamedObjects\\KernelMechanismsAutoEvent");

	// !!! Inicializuje sa NAMED AUTO RESET EVENT.
	Event=IoCreateSynchronizationEvent(&EventName,&EventHandle);

	if (Event!=nullptr)
	{
		CHelpers::Sleep(500);

		KeSetEvent(Event,1,FALSE);

		LONG													EventState1=KeReadStateEvent(Event);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 EVENT STATE [%ld].\n",FunctionName,EventState1));

		CHelpers::Sleep(500);

		KeSetEvent(Event,1,FALSE);

		LONG													EventState2=KeReadStateEvent(Event);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 EVENT STATE [%ld].\n",FunctionName,EventState2));

		CHelpers::Sleep(500);

		KeSetEvent(Event,1,FALSE);

		LONG													EventState3=KeReadStateEvent(Event);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 EVENT STATE [%ld].\n",FunctionName,EventState3));

		CHelpers::Sleep(500);

		KeSetEvent(Event,1,FALSE);

		LONG													EventState4=KeReadStateEvent(Event);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 EVENT STATE [%ld].\n",FunctionName,EventState4));

		// !!!!! HANDLE na EVENT sa MUSI uvolnit, ked uz sa viac nepouziva.
		ZwClose(EventHandle);
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 FAILED to CREATE NAMED AUTO RESET EVENT.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestNamedAutoResetEvents(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	UNICODE_STRING												EventName;
	HANDLE														EventHandle;
	PKEVENT														Event;
		
	// !!! EVENT NAME musi obsahovat FULL PATH v OBJECT MANAGER.
	RtlInitUnicodeString(&EventName,L"\\BaseNamedObjects\\KernelMechanismsAutoEvent");

	// !!! Inicializuje sa NAMED AUTO RESET EVENT.
	Event=IoCreateSynchronizationEvent(&EventName,&EventHandle);

	if (Event==nullptr)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE NAMED AUTO RESET EVENT.\n",FunctionName));
		return;
	}

	// !!!!! EVENT sa nastavi do NON-SINAGLED STATE.
	KeResetEvent(Event);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;
	PETHREAD													ThreadObject3=NULL;

	Status=CHelpers::CreateThread("111",NamedAutoResetEventsThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		ZwClose(EventHandle);

		return;
	}

	Status=CHelpers::CreateThread("222",NamedAutoResetEventsThread2,nullptr,&ThreadObject2);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject1);
		ZwClose(EventHandle);

		return;
	}

	Status=CHelpers::CreateThread("333",NamedAutoResetEventsThread3,nullptr,&ThreadObject3);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject2);
		ObDereferenceObject(ThreadObject1);
		ZwClose(EventHandle);

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

	// !!!!! HANDLE na EVENT sa MUSI uvolnit, ked uz sa viac nepouziva.
	ZwClose(EventHandle);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------