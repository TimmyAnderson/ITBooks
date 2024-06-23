//----------------------------------------------------------------------------------------------------------------------
#include "TestMutexesAbandoned.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CODE NEDOKAZE nasimulovat ABANDONED MUTEX, pretoze pri pokuse ukoncit THREAD, ktory neuvolni MUTEX vykona WINDOWS BUG CHECK.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
KMUTEX															MutexesAbandonedLock;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MutexesAbandonedThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	KeWaitForSingleObject(&MutexesAbandonedLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	__try
	{
	}
	__finally
	{
		// !!!!! Ak by nasledujuce FUNCTION NEBOLA VOLANA, MUTEX ostane v NON-SIGALED STATE a po ukonceni THREADU sa dostane do ABANDONED STATE.
		// !!!!! FUNCTION vsak NIE JE MOZNE NEZAVOLAT, pretoze WINDOWS spravi SYSTEM CRASH.
		KeReleaseMutex(&MutexesAbandonedLock,FALSE);
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void MutexesAbandonedThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	CHelpers::Sleep(1000);

	// !!!!! Ak by sa v THREAD 1 MUTEX stal ABANDONED, tak RETURN VALUE bude VALUE [STATUS_ABANDONED].
	NTSTATUS													Status1=KeWaitForSingleObject(&MutexesAbandonedLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 - WAIT FUNCTION RETURNS STATUS [%lX].\n",FunctionName,Status1));

	__try
	{
		// !!!!! Kedze WAIT FUNCTION uz vratila STATE ABANDONED, tak RETURN VALUE bude VALUE [STATUS_SUCCESS].
		NTSTATUS												Status2=KeWaitForSingleObject(&MutexesAbandonedLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 - WAIT FUNCTION RETURNS STATUS [%lX].\n",FunctionName,Status2));

		__try
		{

		}
		__finally
		{
			KeReleaseMutex(&MutexesAbandonedLock,FALSE);
		}
	}
	__finally
	{
		KeReleaseMutex(&MutexesAbandonedLock,FALSE);
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestMutexesAbandoned(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa MUTEX.
	KeInitializeMutex(&MutexesAbandonedLock,0);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;

	Status=CHelpers::CreateThread("111",MutexesAbandonedThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

	Status=CHelpers::CreateThread("222",MutexesAbandonedThread2,nullptr,&ThreadObject2);

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