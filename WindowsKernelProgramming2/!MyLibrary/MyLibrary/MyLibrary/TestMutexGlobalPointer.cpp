//----------------------------------------------------------------------------------------------------------------------
#include "TestMutexGlobalPointer.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CMutex.h"
#include "Helpers\CLocker.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
ULONG64															MutexGlobalPointerSharedVariable=0;
CMutex*															MutexGlobalPointer=nullptr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ThreadMutexGlobalPointer1(PVOID StartContext)
{
	const char*													FunctionName=__FUNCTION__;

	CMutex*														Mutex=static_cast<CMutex*>(StartContext);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(1000*1000);Index++)
	{
		CLocker													Locker(*Mutex);

		{
			MutexGlobalPointerSharedVariable++;
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ThreadMutexGlobalPointer2(PVOID StartContext)
{
	const char*													FunctionName=__FUNCTION__;

	CMutex*														Mutex=static_cast<CMutex*>(StartContext);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(1000*1000);Index++)
	{
		CLocker													Locker(*Mutex);

		{
			MutexGlobalPointerSharedVariable++;
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestMutexGlobalPointer(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		MutexGlobalPointer=new (EPoolFlags::E_POOL_FLAG_PAGED) CMutex();

		if (MutexGlobalPointer!=nullptr)
		{
			{
				PETHREAD										ThreadObject1=nullptr;
				PETHREAD										ThreadObject2=nullptr;

				do
				{
					Status=CHelpers::CreateThread(DeviceObject,"111",ThreadMutexGlobalPointer1,MutexGlobalPointer,&ThreadObject1);

					if (NT_SUCCESS(Status)==false)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 1 with ERROR CODE [%lX].\n",FunctionName,Status));
						break;
					}

					Status=CHelpers::CreateThread(DeviceObject,"222",ThreadMutexGlobalPointer2,MutexGlobalPointer,&ThreadObject2);

					if (NT_SUCCESS(Status)==false)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 2 with ERROR CODE [%lX].\n",FunctionName,Status));
						break;
					}

					PVOID										Object[]{ThreadObject1,ThreadObject2};
					ULONG										Count=(sizeof(Object)/sizeof(Object[0]));
					PLARGE_INTEGER								Timeout=nullptr;

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

					KdPrint(("!!!!!!!!!! ROUTINE [%s] - SHARED VARIABLE [%I64d].\n",FunctionName,MutexGlobalPointerSharedVariable));
				}
				while(false);

				if (ThreadObject2!=nullptr)
				{
					ObDereferenceObject(ThreadObject2);
					ThreadObject2=nullptr;
				}

				if (ThreadObject1!=nullptr)
				{
					ObDereferenceObject(ThreadObject1);
					ThreadObject1=nullptr;
				}
			}

			delete(MutexGlobalPointer);
			MutexGlobalPointer=nullptr;
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to ALLOCATE MEMORY.\n",FunctionName));
			Status=STATUS_INSUFFICIENT_RESOURCES;
		}
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------