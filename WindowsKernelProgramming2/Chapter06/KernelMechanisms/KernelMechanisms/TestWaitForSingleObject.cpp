//----------------------------------------------------------------------------------------------------------------------
#include "TestWaitForSingleObject.h"
#include <ntddk.h>
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void WaitForSingleObjectThread(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD STARTED.\n",FunctionName));

	CHelpers::Sleep(1000);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD FINISHED.\n",FunctionName));

	PsTerminateSystemThread(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestWaitForSingleObject(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	NTSTATUS													Status;
	PETHREAD													ThreadObject=NULL;

	Status=CHelpers::CreateThread("THREAD",WaitForSingleObjectThread,nullptr,&ThreadObject);

	if (NT_SUCCESS(Status)==false)
	{
		return;
	}

    PLARGE_INTEGER												Timeout=nullptr;

	// !!!!! FUNCTION VZDY vracia STATUS VALUE pre ktoru MACRO [NT_SUCCESS()] vracia TRUE.
	Status=KeWaitForSingleObject(ThreadObject,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,Timeout);

	if (Status==STATUS_SUCCESS)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD FINISHED.\n",FunctionName));
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to WAIT for THREAD with ERROR CODE [%lX].\n",FunctionName,Status));
	}

	ObDereferenceObject(ThreadObject);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------