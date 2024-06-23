//----------------------------------------------------------------------------------------------------------------------
#include "TestFastMutexes.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FAST_MUTEX														FastMutexesLock;
ULONG64															FastMutexesSharedVariable=0;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FastMutexesThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(10*1000*1000);Index++)
	{
		// !!! Caka sa kym FAST MUTEX nebude v SIGNALED STATE. FUNCTION ho nastavi do NON-SIGNALED STATE.
		ExAcquireFastMutex(&FastMutexesLock);

		__try
		{
			// !!!!! CODE v CRITICAL SECTION by mal byt v TRY-FINALLY BLOCK, aby pri vzniku EXCEPTION sa VZDY zavolala FUNCTION [ExReleaseFastMutex()].

			FastMutexesSharedVariable++;
		}
		__finally
		{
			// !!! FAST MUTEX sa nastavi do SIGNALED STATE.
			ExReleaseFastMutex(&FastMutexesLock);
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void FastMutexesThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(10*1000*1000);Index++)
	{
		// !!! Caka sa kym FAST MUTEX nebude v SIGNALED STATE. FUNCTION ho nastavi do NON-SIGNALED STATE.
		ExAcquireFastMutex(&FastMutexesLock);

		__try
		{
			// !!!!! CODE v CRITICAL SECTION by mal byt v TRY-FINALLY BLOCK, aby pri vzniku EXCEPTION sa VZDY zavolala FUNCTION [ExReleaseFastMutex()].

			FastMutexesSharedVariable++;
		}
		__finally
		{
			// !!! FAST MUTEX sa nastavi do SIGNALED STATE.
			ExReleaseFastMutex(&FastMutexesLock);
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFastMutexes(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa FAST MUTEX.
	ExInitializeFastMutex(&FastMutexesLock);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;

	Status=CHelpers::CreateThread("111",FastMutexesThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

	Status=CHelpers::CreateThread("222",FastMutexesThread2,nullptr,&ThreadObject2);

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

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - SHARED VARIABLE [%I64d].\n",FunctionName,FastMutexesSharedVariable));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------