//----------------------------------------------------------------------------------------------------------------------
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CHelpers::CreateThread(const char* ThreadName, PKSTART_ROUTINE StartRoutine, PVOID StartContext, PETHREAD* Object)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;
	HANDLE														ThreadHandle=NULL;
	PETHREAD													ThreadObject=NULL;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,nullptr,OBJ_KERNEL_HANDLE,nullptr,nullptr);

	Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,nullptr,nullptr,StartRoutine,StartContext);

	if (NT_SUCCESS(Status)==true)
	{
		// !!!!! THREAD HANDLE je iba HANDLE na KERNEL OBJECT, ale NIE samotny KERNEL OBJECT a tym padom ho nemozno pouzit vo WAIT FUNCTIONS. Na to je nutne ziskat KERNEL OBJECT [KTHREAD] volanim KERNEL FUNCTION [ObReferenceObjectByHandle()]. OBJECT TYPE [KTHREAD] uz je mozne pouzit vo WAIT FUNCTIONS.
		Status=ObReferenceObjectByHandle(ThreadHandle,GENERIC_ALL,*PsThreadType,MODE::KernelMode,(PVOID*) &ThreadObject,nullptr);

		if (NT_SUCCESS(Status)==true)
		{
			*Object=ThreadObject;
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to GET THREAD [%s] KERNEL OBJECT with ERROR CODE [%lX].\n",FunctionName,ThreadName,Status));
		}

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD [%s] with ERROR CODE [%lX].\n",FunctionName,ThreadName,Status));
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CHelpers::Sleep(LONGLONG TimeoutInMS)
{
	LARGE_INTEGER												Interval;

	Interval.QuadPart=(-10000LL*TimeoutInMS);

	NTSTATUS													Status=KeDelayExecutionThread(MODE::KernelMode,FALSE,&Interval);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CHelpers::CompleteIRP(PIRP Irp, NTSTATUS Status, ULONG_PTR Information)
{
	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	IoCompleteRequest(Irp,IO_NO_INCREMENT);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------