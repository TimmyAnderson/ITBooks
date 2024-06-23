//----------------------------------------------------------------------------------------------------------------------
#include "TestSemaphores.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
KSEMAPHORE														SemaphoresLock;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void SemaphoresThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	LONG														SemaphoreState1=KeReadStateSemaphore(&SemaphoresLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 SEMAPHORE STATE [%ld].\n",FunctionName,SemaphoreState1));

	// !!! FUNCTION dekrementuje interny COUNTER. Ak COUNTER klesne na VALUE [0], tak SEMAPHORE je v NON SIGNALED STATE.
	KeWaitForSingleObject(&SemaphoresLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	CHelpers::Sleep(1000);

	LONG														SemaphoreState2=KeReadStateSemaphore(&SemaphoresLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 SEMAPHORE STATE [%ld].\n",FunctionName,SemaphoreState2));

	// !!! FUNCTION inkrementuje interny COUNTER.
	KeReleaseSemaphore(&SemaphoresLock,1,1,FALSE);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void SemaphoresThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	LONG														SemaphoreState1=KeReadStateSemaphore(&SemaphoresLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 SEMAPHORE STATE [%ld].\n",FunctionName,SemaphoreState1));

	// !!! FUNCTION dekrementuje interny COUNTER. Ak COUNTER klesne na VALUE [0], tak SEMAPHORE je v NON SIGNALED STATE.
	KeWaitForSingleObject(&SemaphoresLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	CHelpers::Sleep(1000);

	LONG														SemaphoreState2=KeReadStateSemaphore(&SemaphoresLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 SEMAPHORE STATE [%ld].\n",FunctionName,SemaphoreState2));

	// !!! FUNCTION inkrementuje interny COUNTER.
	KeReleaseSemaphore(&SemaphoresLock,1,1,FALSE);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void SemaphoresThread3(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 STARTED.\n",FunctionName));

	LONG														SemaphoreState1=KeReadStateSemaphore(&SemaphoresLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 SEMAPHORE STATE [%ld].\n",FunctionName,SemaphoreState1));

	// !!! FUNCTION dekrementuje interny COUNTER. Ak COUNTER klesne na VALUE [0], tak SEMAPHORE je v NON SIGNALED STATE.
	KeWaitForSingleObject(&SemaphoresLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	CHelpers::Sleep(1000);

	LONG														SemaphoreState2=KeReadStateSemaphore(&SemaphoresLock);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 SEMAPHORE STATE [%ld].\n",FunctionName,SemaphoreState2));

	// !!! FUNCTION inkrementuje interny COUNTER.
	KeReleaseSemaphore(&SemaphoresLock,1,1,FALSE);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 3 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSemaphores(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa SEMAPHORE.
	KeInitializeSemaphore(&SemaphoresLock,2,2);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;
	PETHREAD													ThreadObject3=NULL;

	Status=CHelpers::CreateThread("111",SemaphoresThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

	Status=CHelpers::CreateThread("222",SemaphoresThread2,nullptr,&ThreadObject2);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject1);

		return;
	}

	Status=CHelpers::CreateThread("333",SemaphoresThread3,nullptr,&ThreadObject3);

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