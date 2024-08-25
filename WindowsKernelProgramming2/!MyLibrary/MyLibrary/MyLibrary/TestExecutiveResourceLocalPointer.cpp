//----------------------------------------------------------------------------------------------------------------------
#include "TestExecutiveResourceLocalPointer.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CExecutiveResource.h"
#include "Helpers\CLocker.h"
#include "Helpers\CSharedLocker.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourceLocalPointerThread1(PVOID StartContext)
{
	CExecutiveResource*											ExecutiveResourceLocalPointer=static_cast<CExecutiveResource*>(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 STARTED.\n",FunctionName));

	CHelpers::Sleep(200);

	{
		// !!! LOCKER ziskava SHARED ACCESS.
		CSharedLocker<CExecutiveResource>						Locker(*ExecutiveResourceLocalPointer);

		{
			ULONG												NumberOfReaders1=ExecutiveResourceLocalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters1=ExecutiveResourceLocalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

			CHelpers::Sleep(1000);

			ULONG												NumberOfReaders2=ExecutiveResourceLocalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters2=ExecutiveResourceLocalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourceLocalPointerThread2(PVOID StartContext)
{
	CExecutiveResource*											ExecutiveResourceLocalPointer=static_cast<CExecutiveResource*>(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 STARTED.\n",FunctionName));

	CHelpers::Sleep(200);

	{
		// !!! LOCKER ziskava SHARED ACCESS.
		CSharedLocker<CExecutiveResource>						Locker(*ExecutiveResourceLocalPointer);

		{
			ULONG												NumberOfReaders1=ExecutiveResourceLocalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters1=ExecutiveResourceLocalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

			CHelpers::Sleep(1000);

			ULONG												NumberOfReaders2=ExecutiveResourceLocalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters2=ExecutiveResourceLocalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourceLocalPointerThread3(PVOID StartContext)
{
	CExecutiveResource*											ExecutiveResourceLocalPointer=static_cast<CExecutiveResource*>(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 STARTED.\n",FunctionName));

	{
		// !!! LOCKER ziskava EXCLUSIVE ACCESS.
		CLocker<CExecutiveResource>								Locker(*ExecutiveResourceLocalPointer);

		{
			ULONG												NumberOfReaders1=ExecutiveResourceLocalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters1=ExecutiveResourceLocalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

			CHelpers::Sleep(1000);

			ULONG												NumberOfReaders2=ExecutiveResourceLocalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters2=ExecutiveResourceLocalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourceLocalPointerThread4(PVOID StartContext)
{
	CExecutiveResource*											ExecutiveResourceLocalPointer=static_cast<CExecutiveResource*>(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 STARTED.\n",FunctionName));

	{
		// !!! LOCKER ziskava EXCLUSIVE ACCESS.
		CLocker<CExecutiveResource>								Locker(*ExecutiveResourceLocalPointer);

		{
			ULONG												NumberOfReaders1=ExecutiveResourceLocalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters1=ExecutiveResourceLocalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

			CHelpers::Sleep(1000);

			ULONG												NumberOfReaders2=ExecutiveResourceLocalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters2=ExecutiveResourceLocalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestExecutiveResourceLocalPointer(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		CExecutiveResource*										ExecutiveResourceLocalPointer=new (EPoolFlags::E_POOL_FLAG_PAGED) CExecutiveResource();

		if (ExecutiveResourceLocalPointer!=nullptr)
		{
			PETHREAD											ThreadObject1=nullptr;
			PETHREAD											ThreadObject2=nullptr;
			PETHREAD											ThreadObject3=nullptr;
			PETHREAD											ThreadObject4=nullptr;

			do
			{
				Status=CHelpers::CreateThread(DeviceObject,"111",ExecutiveResourceLocalPointerThread1,ExecutiveResourceLocalPointer,&ThreadObject1);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 1 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				Status=CHelpers::CreateThread(DeviceObject,"222",ExecutiveResourceLocalPointerThread2,ExecutiveResourceLocalPointer,&ThreadObject2);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 2 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				Status=CHelpers::CreateThread(DeviceObject,"333",ExecutiveResourceLocalPointerThread3,ExecutiveResourceLocalPointer,&ThreadObject3);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 3 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				Status=CHelpers::CreateThread(DeviceObject,"444",ExecutiveResourceLocalPointerThread4,ExecutiveResourceLocalPointer,&ThreadObject4);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 4 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				PVOID											Object[]{ThreadObject1,ThreadObject2,ThreadObject3,ThreadObject4};
				constexpr ULONG									Count=(sizeof(Object)/sizeof(Object[0]));
				PLARGE_INTEGER									Timeout=nullptr;
				KWAIT_BLOCK										WaitBlockArray[Count];

				// !!!!! FUNCTION VZDY vracia STATUS VALUE pre ktoru MACRO [NT_SUCCESS()] vracia TRUE.
				Status=KeWaitForMultipleObjects(Count,Object,WAIT_TYPE::WaitAll,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,Timeout,WaitBlockArray);

				if (Status==STATUS_SUCCESS)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREADS FINISHED.\n",FunctionName));
				}
				else
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to WAIT for THREADS with ERROR CODE [%lX].\n",FunctionName,Status));
				}
			}
			while(false);

			if (ThreadObject4!=nullptr)
			{
				ObDereferenceObject(ThreadObject4);
				ThreadObject4=nullptr;
			}

			if (ThreadObject3!=nullptr)
			{
				ObDereferenceObject(ThreadObject3);
				ThreadObject3=nullptr;
			}

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

			delete(ExecutiveResourceLocalPointer);
			ExecutiveResourceLocalPointer=nullptr;
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to ALLOCATE MEMORY.\n",FunctionName));
			Status=STATUS_INSUFFICIENT_RESOURCES;
		}

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------