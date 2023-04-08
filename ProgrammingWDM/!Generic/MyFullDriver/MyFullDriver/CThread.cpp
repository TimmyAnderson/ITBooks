//-------------------------------------------------------------------------------------------------------
#include "CThread.h"
#include "Macros.h"
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void CThread::ThreadFunction(PVOID Parameter)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n");

	NTSTATUS													Status=STATUS_SUCCESS;
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) Parameter;
	
	HANDLE														WaitObjects[]{&DeviceExtension->ThreadExitEvent,&DeviceExtension->ThreadIRPEvent};
	KWAIT_BLOCK													WaitBlocks[_countof(WaitObjects)];

	for(;;)
	{
		Status=KeWaitForMultipleObjects(_countof(WaitObjects),WaitObjects,WaitAny,Executive,KernelMode,FALSE,nullptr,WaitBlocks);

		if (Status==STATUS_WAIT_0)
		{
			break;
		}

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD is WORKING !\n");
	}

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n");

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
bool CThread::StartThread(PDEVICE_EXTENSION DeviceExtension)
{
	NTSTATUS													Status;

	KeInitializeEvent(&DeviceExtension->ThreadExitEvent,NotificationEvent,FALSE);
	KeInitializeEvent(&DeviceExtension->ThreadIRPEvent,SynchronizationEvent,FALSE);

	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,ThreadFunction,DeviceExtension))==true)
	{
		if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &DeviceExtension->Thread,NULL))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ObReferenceObjectByHandle() FAILED [%X] !\n",Status);
		}

		return(true);
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status);

		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------
void CThread::StopThread(PDEVICE_EXTENSION DeviceExtension)
{
	if (DeviceExtension->Thread!=nullptr)
	{
		KeSetEvent(&DeviceExtension->ThreadExitEvent,0,FALSE);

		KeWaitForSingleObject(DeviceExtension->Thread,Executive,KernelMode,FALSE,nullptr);

		ObDereferenceObject(DeviceExtension->Thread);
		DeviceExtension->Thread=nullptr;
	}
}
//-------------------------------------------------------------------------------------------------------