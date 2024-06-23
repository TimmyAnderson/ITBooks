//----------------------------------------------------------------------------------------------------------------------
#include "TestInterlockedLockFree.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! INTERLOCKED VARIABLES MUSIA byt VOLATILE a MALI byt byt zarovnane na SIZEOF BITS.
alignas(64) volatile LONG64										LockFreeVariable=TRUE;
alignas(64) volatile LONG64										LockFreeCounter=0;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void InterlockedLockFreeThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(100*1000*1000);Index++)
	{
		// !!!!! IRQL MUSI byt pred ziskanim LOCK nastavene na MAXIMAL VALUE zo vsetkych IRQLs v ktorych bezi CODE chraneny LOCK. Inak hrozi vznik DEADLOCK, aby CODE ktory ma LOCK bol preruseny inym CODE s vyssim IRQL, ktory by sa pokusil ziskat ten isty LOCK.
		// !!!!! Kedze tu OBA THREADS pristupujuce k SHARED RESOURCE su v IRQL [PASSIVE_LEVEL], tak IRQL NIE JE NUTNE MENIT.

		// !!!!! Ak [LockFreeVariable=TRUE] tak nastavi [LockFreeVariable=FALSE] a zaroven vrati RETURN VALUE [TRUE].
		// !!!!! Ak [LockFreeVariable=FALSE] tak FUNCTION NIC NEROBI a zaroven vrati RETURN VALUE [FALSE].
		// !!!!! THREAD robi SPINNING a kym sa SHARED VARIABLE neuvolni.
		while(InterlockedCompareExchange64(&LockFreeVariable,FALSE,TRUE)==FALSE)
		{
		}

		LockFreeCounter++;

		// !!!!! THREAD uvolni LOCK nastavenim [LockFreeVariable=TRUE].
		InterlockedExchange64(&LockFreeVariable,TRUE);
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void InterlockedLockFreeThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(100*1000*1000);Index++)
	{
		// !!!!! IRQL MUSI byt pred ziskanim LOCK nastavene na MAXIMAL VALUE zo vsetkych IRQLs v ktorych bezi CODE chraneny LOCK. Inak hrozi vznik DEADLOCK, aby CODE ktory ma LOCK bol preruseny inym CODE s vyssim IRQL, ktory by sa pokusil ziskat ten isty LOCK.
		// !!!!! Kedze tu OBA THREADS pristupujuce k SHARED RESOURCE su v IRQL [PASSIVE_LEVEL], tak IRQL NIE JE NUTNE MENIT.

		// !!!!! Ak [LockFreeVariable=TRUE] tak nastavi [LockFreeVariable=FALSE] a zaroven vrati RETURN VALUE [TRUE].
		// !!!!! Ak [LockFreeVariable=FALSE] tak FUNCTION NIC NEROBI a zaroven vrati RETURN VALUE [FALSE].
		// !!!!! THREAD robi SPINNING a kym sa SHARED VARIABLE neuvolni.
		while(InterlockedCompareExchange64(&LockFreeVariable,FALSE,TRUE)==FALSE)
		{
		}

		LockFreeCounter++;

		// !!!!! THREAD uvolni LOCK nastavenim [LockFreeVariable=TRUE].
		InterlockedExchange64(&LockFreeVariable,TRUE);
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestInterlockedLockFree(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;

	Status=CHelpers::CreateThread("111",InterlockedLockFreeThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

	Status=CHelpers::CreateThread("222",InterlockedLockFreeThread2,nullptr,&ThreadObject2);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject1);

		return;
	}

	PVOID														Object[]{ThreadObject1,ThreadObject2};
    ULONG														Count=(sizeof(Object)/sizeof(Object[0]));
    PLARGE_INTEGER												Timeout=nullptr;

	ASSERT(Count<=THREAD_WAIT_OBJECTS);

	Status=KeWaitForMultipleObjects(Count,Object,WAIT_TYPE::WaitAll,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,Timeout,nullptr);

	if (Status==STATUS_SUCCESS)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREADS FINISHED.\n",FunctionName));
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to WAIT for THREADS with ERROR CODE [%lX].\n",FunctionName,Status));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - INTERLOCKED VARIABLE [%I64d].\n",FunctionName,LockFreeCounter));

	ObDereferenceObject(ThreadObject2);
	ObDereferenceObject(ThreadObject1);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------