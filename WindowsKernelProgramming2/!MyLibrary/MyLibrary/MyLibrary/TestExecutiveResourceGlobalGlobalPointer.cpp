//----------------------------------------------------------------------------------------------------------------------
#include "TestExecutiveResourceGlobalGlobalPointer.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CExecutiveResourceGlobal.h"
#include "Helpers\CLocker.h"
#include "Helpers\CSharedLocker.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CExecutiveResourceGlobal*										ExecutiveResourceGlobalGlobalPointer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourceGlobalGlobalPointerThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 STARTED.\n",FunctionName));

	CHelpers::Sleep(200);

	{
		// !!! LOCKER ziskava SHARED ACCESS.
		CSharedLocker<CExecutiveResourceGlobal>					Locker(*ExecutiveResourceGlobalGlobalPointer);

		{
			ULONG												NumberOfReaders1=ExecutiveResourceGlobalGlobalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters1=ExecutiveResourceGlobalGlobalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

			CHelpers::Sleep(1000);

			ULONG												NumberOfReaders2=ExecutiveResourceGlobalGlobalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters2=ExecutiveResourceGlobalGlobalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourceGlobalGlobalPointerThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 STARTED.\n",FunctionName));

	CHelpers::Sleep(200);

	{
		// !!! LOCKER ziskava SHARED ACCESS.
		CSharedLocker<CExecutiveResourceGlobal>					Locker(*ExecutiveResourceGlobalGlobalPointer);

		{
			ULONG												NumberOfReaders1=ExecutiveResourceGlobalGlobalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters1=ExecutiveResourceGlobalGlobalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

			CHelpers::Sleep(1000);

			ULONG												NumberOfReaders2=ExecutiveResourceGlobalGlobalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters2=ExecutiveResourceGlobalGlobalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourceGlobalGlobalPointerThread3(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 STARTED.\n",FunctionName));

	{
		// !!! LOCKER ziskava EXCLUSIVE ACCESS.
		CLocker<CExecutiveResourceGlobal>						Locker(*ExecutiveResourceGlobalGlobalPointer);

		{
			ULONG												NumberOfReaders1=ExecutiveResourceGlobalGlobalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters1=ExecutiveResourceGlobalGlobalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

			CHelpers::Sleep(1000);

			ULONG												NumberOfReaders2=ExecutiveResourceGlobalGlobalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters2=ExecutiveResourceGlobalGlobalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourceGlobalGlobalPointerThread4(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 STARTED.\n",FunctionName));

	{
		// !!! LOCKER ziskava EXCLUSIVE ACCESS.
		CLocker<CExecutiveResourceGlobal>						Locker(*ExecutiveResourceGlobalGlobalPointer);

		{
			ULONG												NumberOfReaders1=ExecutiveResourceGlobalGlobalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters1=ExecutiveResourceGlobalGlobalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

			CHelpers::Sleep(1000);

			ULONG												NumberOfReaders2=ExecutiveResourceGlobalGlobalPointer->GetSharedWaiterCount();
			ULONG												NumberOfWriters2=ExecutiveResourceGlobalGlobalPointer->GetExclusiveWaiterCount();

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));
		}
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestExecutiveResourceGlobalGlobalPointer(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		ExecutiveResourceGlobalGlobalPointer=new (EPoolFlags::E_POOL_FLAG_PAGED) CExecutiveResourceGlobal();

		if (ExecutiveResourceGlobalGlobalPointer!=nullptr)
		{
			// !!! Inicializuje sa EXECUTIVE RESOURCE.
			ExecutiveResourceGlobalGlobalPointer->Init();

			PETHREAD											ThreadObject1=nullptr;
			PETHREAD											ThreadObject2=nullptr;
			PETHREAD											ThreadObject3=nullptr;
			PETHREAD											ThreadObject4=nullptr;

			do
			{
				Status=CHelpers::CreateThread(DeviceObject,"111",ExecutiveResourceGlobalGlobalPointerThread1,nullptr,&ThreadObject1);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 1 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				Status=CHelpers::CreateThread(DeviceObject,"222",ExecutiveResourceGlobalGlobalPointerThread2,nullptr,&ThreadObject2);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 2 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				Status=CHelpers::CreateThread(DeviceObject,"333",ExecutiveResourceGlobalGlobalPointerThread3,nullptr,&ThreadObject3);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD 3 with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}

				Status=CHelpers::CreateThread(DeviceObject,"444",ExecutiveResourceGlobalGlobalPointerThread4,nullptr,&ThreadObject4);

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

			// !!! Uvolnuje sa EXECUTIVE RESOURCE.
			ExecutiveResourceGlobalGlobalPointer->Delete();

			delete(ExecutiveResourceGlobalGlobalPointer);
			ExecutiveResourceGlobalGlobalPointer=nullptr;
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