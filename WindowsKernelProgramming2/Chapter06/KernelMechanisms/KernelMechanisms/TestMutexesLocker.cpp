//----------------------------------------------------------------------------------------------------------------------
#include "TestMutexesLocker.h"
#include <ntddk.h>
#include "CHelpers.h"
#include "CMutex.h"
#include "CLocker.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CMutex															MutexesLockerLock;
ULONG64															MutexesLockerSharedVariable=0;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MutexesLockerThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(1000*1000);Index++)
	{
		// !!! OBJECT v CONSTRUCTOR vykona LOCK a v DESTRUCTOR vykona UNLOCK;
		CLocker<CMutex>											Locker(MutexesLockerLock);

		MutexesLockerSharedVariable++;
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void MutexesLockerThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(1000*1000);Index++)
	{
		// !!! OBJECT v CONSTRUCTOR vykona LOCK a v DESTRUCTOR vykona UNLOCK;
		CLocker<CMutex>											Locker(MutexesLockerLock);

		MutexesLockerSharedVariable++;
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestMutexesLocker(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa MUTEX.
	MutexesLockerLock.Init();

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;

	Status=CHelpers::CreateThread("111",MutexesLockerThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

	Status=CHelpers::CreateThread("222",MutexesLockerThread2,nullptr,&ThreadObject2);

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

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - SHARED VARIABLE [%I64d].\n",FunctionName,MutexesLockerSharedVariable));

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------