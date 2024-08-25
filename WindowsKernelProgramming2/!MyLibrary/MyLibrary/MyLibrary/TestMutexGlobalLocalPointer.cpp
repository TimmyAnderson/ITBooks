//----------------------------------------------------------------------------------------------------------------------
#include "TestMutexGlobalLocalPointer.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CMutexGlobal.h"
#include "Helpers\CLocker.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
ULONG64															MutexGlobalLocalPointerSharedVariable=0;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ThreadMutexGlobalLocalPointer1(PVOID StartContext)
{
	const char*													FunctionName=__FUNCTION__;

	CMutexGlobal*												Mutex=static_cast<CMutexGlobal*>(StartContext);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(1000*1000);Index++)
	{
		CLocker													Locker(*Mutex);

		{
			MutexGlobalLocalPointerSharedVariable++;
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 1 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ThreadMutexGlobalLocalPointer2(PVOID StartContext)
{
	const char*													FunctionName=__FUNCTION__;

	CMutexGlobal*												Mutex=static_cast<CMutexGlobal*>(StartContext);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 STARTED.\n",FunctionName));

	for(LONG64 Index=0;Index<LONG64(1000*1000);Index++)
	{
		CLocker													Locker(*Mutex);

		{
			MutexGlobalLocalPointerSharedVariable++;
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD 2 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestMutexGlobalLocalPointer(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		CMutexGlobal*											MutexGlobalLocalPointer=new (EPoolFlags::E_POOL_FLAG_PAGED) CMutexGlobal();

		if (MutexGlobalLocalPointer!=nullptr)
		{
			MutexGlobalLocalPointer->Init();

			{
				PETHREAD										ThreadObject1=nullptr;
				PETHREAD										ThreadObject2=nullptr;

				do
				{
					Status=CHelpers::CreateThread(DeviceObject,"111",ThreadMutexGlobalLocalPointer1,MutexGlobalLocalPointer,&ThreadObject1);

					if (NT_SUCCESS(Status)==false)
					{
						KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 1 with ERROR CODE [%lX].\n",FunctionName,Status));
						break;
					}

					Status=CHelpers::CreateThread(DeviceObject,"222",ThreadMutexGlobalLocalPointer2,MutexGlobalLocalPointer,&ThreadObject2);

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

					KdPrint(("!!!!!!!!!! ROUTINE [%s] - SHARED VARIABLE [%I64d].\n",FunctionName,MutexGlobalLocalPointerSharedVariable));
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

			delete(MutexGlobalLocalPointer);
			MutexGlobalLocalPointer=nullptr;
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