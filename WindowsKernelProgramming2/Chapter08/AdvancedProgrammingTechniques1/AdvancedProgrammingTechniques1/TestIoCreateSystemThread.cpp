//----------------------------------------------------------------------------------------------------------------------
#include "TestIoCreateSystemThread.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ThreadIoCreateSystemThread(PVOID StartContext)
{
	UNREFERENCED_PARAMETER(StartContext);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! THREAD ROUTINE [%s] - THREAD STARTED.\n",FunctionName));

	CHelpers::Sleep(1000);

	KdPrint(("!!!!!!!!!! THREAD ROUTINE [%s] - THREAD FINISHED.\n",FunctionName));

	// !!!!! Ak je SYSTEM THREAD vytvoreny pomocou FUNCTION [IoCreateSystemThread()] THREAD ROUTINE NESMIE volat NON RETURNABLE FUNCTION [PsTerminateSystemThread()], pretoze ta sa vola AUTOMATICKY.
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestIoCreateSystemThread(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	do
	{
		HANDLE													ThreadHandle=nullptr;
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes;
		PETHREAD												ThreadObject=nullptr;

		InitializeObjectAttributes(&ThreadHandleObjectAttributes,nullptr,OBJ_KERNEL_HANDLE,nullptr,nullptr);

		// !!!!! VYHODOU pouzitia FUNCTION [IoCreateSystemThread()] je to ze GARANTUJE, ze WINDOWS neodstrani DRIVER z MEMORY skor ako SYSTEM THREAD skonci.
		Status=IoCreateSystemThread(DeviceObject,&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,nullptr,nullptr,ThreadIoCreateSystemThread,nullptr);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to CREATE THREAD with ERROR CODE [%lX].\n",FunctionName,Status));
			break;
		}

		// !!!!! Z THREAD HANDLE sa ziska POINTER na STRUCTURE [ETHREAD], ktora definuje KERNEL THREAD.
		Status=ObReferenceObjectByHandle(ThreadHandle,GENERIC_ALL,*PsThreadType,MODE::KernelMode,(PVOID*) &ThreadObject,nullptr);

		// !!!!! THREAD HANDLE sa MUSI uvolnit, aby mohol byt THREAD korektne uvolneny z MEMORY.
		ZwClose(ThreadHandle);
		ThreadHandle=nullptr;

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to GET THREAD KERNEL OBJECT with ERROR CODE [%lX].\n",FunctionName,Status));
			break;
		}

		PLARGE_INTEGER											Timeout=nullptr;

		// !!! Caka sa na ukoncenie THREAD.
		Status=KeWaitForSingleObject(ThreadObject,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,Timeout);

		if (Status==STATUS_SUCCESS)
		{
			// !!!!! Vracia STATUS CODE, ktory bol zaslany do FUNCTION [PsTerminateSystemThread()]. Kedze FUNCTION [IoCreateSystemThread()] vola FUNCTION [PsTerminateSystemThread()] AUTOMATICKY s VALUE [STATUS_SUCCESS], tak sa VZDY vrati VALUE [STATUS_SUCCESS].
			NTSTATUS										ThreadStatusCode=PsGetThreadExitStatus(ThreadObject);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - THREAD FINISHED with THREAD STATUS CODE [%lX].\n",FunctionName,ThreadStatusCode));
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to WAIT for THREAD with ERROR CODE [%lX].\n",FunctionName,Status));
		}

		// !!! Dekrementuje sa COUNTER na THREAD OBJECT, aby sa THREAD mohol korektne uvolnit.
		ObDereferenceObject(ThreadObject);
	}
	while(false);

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------