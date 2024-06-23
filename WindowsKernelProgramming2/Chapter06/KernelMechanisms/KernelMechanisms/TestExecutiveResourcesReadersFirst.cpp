//----------------------------------------------------------------------------------------------------------------------
#include "TestExecutiveResourcesReadersFirst.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
alignas(sizeof(void*)) ERESOURCE								ExecutiveResourcesReadersFirstExecutiveResource;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourcesReadersFirstThread1(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 STARTED.\n",FunctionName));

	{
		// !!!!! Pred ziskanim ACCESS k EXECUTIVE RESOURCE je NUTNE vstupit do CRITICAL REGION.
		KeEnterCriticalRegion();

		ExAcquireResourceSharedLite(&ExecutiveResourcesReadersFirstExecutiveResource,TRUE);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 is ENTERING ACCESS to SHARED RESOUCE.\n",FunctionName));

		CHelpers::Sleep(1000);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 is LEAVING ACCESS to SHARED RESOUCE.\n",FunctionName));

		ExReleaseResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

		// !!!!! Po uvolneni ACCESS k EXECUTIVE RESOURCE je NUTNE vystupit z CRITICAL REGION.
		KeLeaveCriticalRegion();
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourcesReadersFirstThread2(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 STARTED.\n",FunctionName));

	{
		// !!!!! Pred ziskanim ACCESS k EXECUTIVE RESOURCE je NUTNE vstupit do CRITICAL REGION.
		KeEnterCriticalRegion();

		ExAcquireResourceSharedLite(&ExecutiveResourcesReadersFirstExecutiveResource,TRUE);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 is ENTERING ACCESS to SHARED RESOUCE.\n",FunctionName));

		CHelpers::Sleep(1000);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 is LEAVING ACCESS to SHARED RESOUCE.\n",FunctionName));

		ExReleaseResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

		// !!!!! Po uvolneni ACCESS k EXECUTIVE RESOURCE je NUTNE vystupit z CRITICAL REGION.
		KeLeaveCriticalRegion();
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD READER 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourcesReadersFirstThread3(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 STARTED.\n",FunctionName));

	CHelpers::Sleep(200);

	{
		// !!!!! Pred ziskanim ACCESS k EXECUTIVE RESOURCE je NUTNE vstupit do CRITICAL REGION.
		KeEnterCriticalRegion();

		ExAcquireResourceExclusiveLite(&ExecutiveResourcesReadersFirstExecutiveResource,TRUE);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 is ENTERING ACCESS to SHARED RESOUCE.\n",FunctionName));

		CHelpers::Sleep(1000);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 is LEAVING ACCESS to SHARED RESOUCE.\n",FunctionName));

		ExReleaseResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

		// !!!!! Po uvolneni ACCESS k EXECUTIVE RESOURCE je NUTNE vystupit z CRITICAL REGION.
		KeLeaveCriticalRegion();
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 1 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ExecutiveResourcesReadersFirstThread4(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 STARTED.\n",FunctionName));

	CHelpers::Sleep(200);

	{
		// !!!!! Pred ziskanim ACCESS k EXECUTIVE RESOURCE je NUTNE vstupit do CRITICAL REGION.
		KeEnterCriticalRegion();

		ExAcquireResourceExclusiveLite(&ExecutiveResourcesReadersFirstExecutiveResource,TRUE);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 is ENTERING ACCESS to SHARED RESOUCE.\n",FunctionName));

		CHelpers::Sleep(1000);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 is LEAVING ACCESS to SHARED RESOUCE.\n",FunctionName));

		ExReleaseResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

		// !!!!! Po uvolneni ACCESS k EXECUTIVE RESOURCE je NUTNE vystupit z CRITICAL REGION.
		KeLeaveCriticalRegion();
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD WRITER 2 FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestExecutiveResourcesReadersFirst(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Inicializuje sa EXECUTIVE RESOURCE.
	ExInitializeResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

	NTSTATUS													Status;
	PETHREAD													ThreadObject1=NULL;
	PETHREAD													ThreadObject2=NULL;
	PETHREAD													ThreadObject3=NULL;
	PETHREAD													ThreadObject4=NULL;

	Status=CHelpers::CreateThread("111",ExecutiveResourcesReadersFirstThread1,nullptr,&ThreadObject1);

	if (NT_SUCCESS(Status)==false)
	{
		ExDeleteResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

		return;
	}

	Status=CHelpers::CreateThread("222",ExecutiveResourcesReadersFirstThread2,nullptr,&ThreadObject2);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject1);
		ExDeleteResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

		return;
	}

	Status=CHelpers::CreateThread("333",ExecutiveResourcesReadersFirstThread3,nullptr,&ThreadObject3);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject2);
		ObDereferenceObject(ThreadObject1);
		ExDeleteResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

		return;
	}

	Status=CHelpers::CreateThread("444",ExecutiveResourcesReadersFirstThread4,nullptr,&ThreadObject4);

	if (NT_SUCCESS(Status)==false)
	{
		ObDereferenceObject(ThreadObject3);
		ObDereferenceObject(ThreadObject2);
		ObDereferenceObject(ThreadObject1);
		ExDeleteResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

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
	ExDeleteResourceLite(&ExecutiveResourcesReadersFirstExecutiveResource);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------