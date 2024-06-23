//----------------------------------------------------------------------------------------------------------------------
#include "TestExecutiveResourcesAutoReadersFirst.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
alignas(sizeof(void*)) ERESOURCE								ExecutiveResourcesAutoReadersFirstExecutiveResource;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourcesAutoReadersFirstThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 STARTED.\n",FunctionName));

	{
		// !!!!! Pred ziskanim ACCESS k EXECUTIVE RESOURCE je NUTNE vstupit do CRITICAL REGION.
		ExEnterCriticalRegionAndAcquireResourceShared(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		ULONG													NumberOfReaders1=ExGetSharedWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
		ULONG													NumberOfWriters1=ExGetExclusiveWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

		CHelpers::Sleep(1000);

		ULONG													NumberOfReaders2=ExGetSharedWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
		ULONG													NumberOfWriters2=ExGetExclusiveWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));

		// !!!!! Po uvolneni ACCESS k EXECUTIVE RESOURCE je NUTNE vystupit z CRITICAL REGION.
		ExReleaseResourceAndLeaveCriticalRegion(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourcesAutoReadersFirstThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 STARTED.\n",FunctionName));

	{
		// !!!!! Pred ziskanim ACCESS k EXECUTIVE RESOURCE je NUTNE vstupit do CRITICAL REGION.
		ExEnterCriticalRegionAndAcquireResourceShared(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		ULONG													NumberOfReaders1=ExGetSharedWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
		ULONG													NumberOfWriters1=ExGetExclusiveWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

		CHelpers::Sleep(1000);

		ULONG													NumberOfReaders2=ExGetSharedWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
		ULONG													NumberOfWriters2=ExGetExclusiveWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));

		// !!!!! Po uvolneni ACCESS k EXECUTIVE RESOURCE je NUTNE vystupit z CRITICAL REGION.
		ExReleaseResourceAndLeaveCriticalRegion(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourcesAutoReadersFirstThread3(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 STARTED.\n",FunctionName));

	CHelpers::Sleep(200);

	{
		// !!!!! Pred ziskanim ACCESS k EXECUTIVE RESOURCE je NUTNE vstupit do CRITICAL REGION.
		ExEnterCriticalRegionAndAcquireResourceExclusive(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		ULONG													NumberOfReaders1=ExGetSharedWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
		ULONG													NumberOfWriters1=ExGetExclusiveWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

		CHelpers::Sleep(1000);

		ULONG													NumberOfReaders2=ExGetSharedWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
		ULONG													NumberOfWriters2=ExGetExclusiveWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));

		// !!!!! Po uvolneni ACCESS k EXECUTIVE RESOURCE je NUTNE vystupit z CRITICAL REGION.
		ExReleaseResourceAndLeaveCriticalRegion(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourcesAutoReadersFirstThread4(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 STARTED.\n",FunctionName));

	CHelpers::Sleep(200);

	{
		// !!!!! Pred ziskanim ACCESS k EXECUTIVE RESOURCE je NUTNE vstupit do CRITICAL REGION.
		ExEnterCriticalRegionAndAcquireResourceExclusive(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		ULONG													NumberOfReaders1=ExGetSharedWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
		ULONG													NumberOfWriters1=ExGetExclusiveWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 is ENTERING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders1,NumberOfWriters1));

		CHelpers::Sleep(1000);

		ULONG													NumberOfReaders2=ExGetSharedWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
		ULONG													NumberOfWriters2=ExGetExclusiveWaiterCount(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 is LEAVING ACCESS to SHARED RESOUCE. READERS [%lu] WRITERS [%lu].\n",FunctionName,NumberOfReaders2,NumberOfWriters2));

		// !!!!! Po uvolneni ACCESS k EXECUTIVE RESOURCE je NUTNE vystupit z CRITICAL REGION.
		ExReleaseResourceAndLeaveCriticalRegion(&ExecutiveResourcesAutoReadersFirstExecutiveResource);
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestExecutiveResourcesAutoReadersFirst(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa EXECUTIVE RESOURCE.
	ExInitializeResourceLite(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;
	PETHREAD													ThreadObject3=NULL;
	PETHREAD													ThreadObject4=NULL;

	Status=CHelpers::CreateThread("111",ExecutiveResourcesAutoReadersFirstThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		ExDeleteResourceLite(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		return;
	}

	Status=CHelpers::CreateThread("222",ExecutiveResourcesAutoReadersFirstThread2,nullptr,&ThreadObject2);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject1);
		ExDeleteResourceLite(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		return;
	}

	Status=CHelpers::CreateThread("333",ExecutiveResourcesAutoReadersFirstThread3,nullptr,&ThreadObject3);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject2);
		ObDereferenceObject(ThreadObject1);
		ExDeleteResourceLite(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		return;
	}

	Status=CHelpers::CreateThread("444",ExecutiveResourcesAutoReadersFirstThread4,nullptr,&ThreadObject4);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject3);
		ObDereferenceObject(ThreadObject2);
		ObDereferenceObject(ThreadObject1);
		ExDeleteResourceLite(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

		return;
	}

	PVOID														Object[]{ThreadObject1,ThreadObject2,ThreadObject3,ThreadObject4};
    constexpr ULONG												Count=(sizeof(Object)/sizeof(Object[0]));
    PLARGE_INTEGER												Timeout=nullptr;
	KWAIT_BLOCK													WaitBlockArray[Count];

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

	ObDereferenceObject(ThreadObject4);
	ObDereferenceObject(ThreadObject3);
	ObDereferenceObject(ThreadObject2);
	ObDereferenceObject(ThreadObject1);

	// !!! Uvolnuje sa EXECUTIVE RESOURCE.
	ExDeleteResourceLite(&ExecutiveResourcesAutoReadersFirstExecutiveResource);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------