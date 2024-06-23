//----------------------------------------------------------------------------------------------------------------------
#include "TestMutexesRecursive.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
KMUTEX															MutexesRecursiveLock;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MutexesRecursiveThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	KeWaitForSingleObject(&MutexesRecursiveLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	__try
	{
		CHelpers::Sleep(500);

		KeWaitForSingleObject(&MutexesRecursiveLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		__try
		{
			CHelpers::Sleep(500);

			KeWaitForSingleObject(&MutexesRecursiveLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

			__try
			{
				CHelpers::Sleep(500);
			}
			__finally
			{
				LONG											Counter1=KeReleaseMutex(&MutexesRecursiveLock,FALSE);

				KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 - COUNTER [%ld].\n",FunctionName,Counter1));
			}

		}
		__finally
		{
			LONG												Counter2=KeReleaseMutex(&MutexesRecursiveLock,FALSE);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 - COUNTER [%ld].\n",FunctionName,Counter2));
		}
	}
	__finally
	{
		LONG													Counter3=KeReleaseMutex(&MutexesRecursiveLock,FALSE);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 - COUNTER [%ld].\n",FunctionName,Counter3));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void MutexesRecursiveThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	KeWaitForSingleObject(&MutexesRecursiveLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

	__try
	{
		CHelpers::Sleep(500);

		KeWaitForSingleObject(&MutexesRecursiveLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		__try
		{
			CHelpers::Sleep(500);

			KeWaitForSingleObject(&MutexesRecursiveLock,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

			__try
			{
				CHelpers::Sleep(500);
			}
			__finally
			{
				LONG											Counter1=KeReleaseMutex(&MutexesRecursiveLock,FALSE);

				KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 - COUNTER [%ld].\n",FunctionName,Counter1));
			}

		}
		__finally
		{
			LONG												Counter2=KeReleaseMutex(&MutexesRecursiveLock,FALSE);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 - COUNTER [%ld].\n",FunctionName,Counter2));
		}
	}
	__finally
	{
		LONG													Counter3=KeReleaseMutex(&MutexesRecursiveLock,FALSE);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 - COUNTER [%ld].\n",FunctionName,Counter3));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestMutexesRecursive(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa MUTEX.
	KeInitializeMutex(&MutexesRecursiveLock,0);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;

	Status=CHelpers::CreateThread("111",MutexesRecursiveThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

	Status=CHelpers::CreateThread("222",MutexesRecursiveThread2,nullptr,&ThreadObject2);

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