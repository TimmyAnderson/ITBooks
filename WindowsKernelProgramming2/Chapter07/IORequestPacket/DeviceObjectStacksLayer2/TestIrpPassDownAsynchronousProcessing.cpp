//----------------------------------------------------------------------------------------------------------------------
#include "TestIrpPassDownAsynchronousProcessing.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void IrpPassDownAsynchronousProcessingWorkItemRoutine(PVOID IoObject, PVOID Context, PIO_WORKITEM IoWorkItem)
{
	UNREFERENCED_PARAMETER(IoObject);

	// !!!!! Po vybrati WORK ITEM z QUEUE je ho mozne uvolnit.
	IoFreeWorkItem(IoWorkItem);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! WORK ITEM ROUTINE [%s] LOWER DRIVER - COMPLETING IRP.\n",FunctionName));

	CHelpers::Sleep(1000);

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;
	IRP*														Irp=static_cast<IRP*>(Context);

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	KdPrint(("!!!!!!!!!! WORK ITEM ROUTINE [%s] LOWER DRIVER - COMPLETED IRP.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestIrpPassDownAsynchronousProcessing(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	PIO_WORKITEM												WorkItem=IoAllocateWorkItem(DeviceObject);

	if (WorkItem!=nullptr)
	{
		// !!!!! Pri ASYNCHRONNOM spracovani sa MUSI nastavit STATUS [STATUS_PENDING].
		NTSTATUS												Status=STATUS_PENDING;
	
		// !!! FUNCTION vrati CURRENT STACK LOCATION.
		IO_STACK_LOCATION*										CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
		ULONG													Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
		ULONG													InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;
		ULONG													OutputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	
		KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] LOWER DRIVER - CODE [%lu] INPUT BUFFER LENGTH [%lu] OUTPUT BUFFER LENGTH [%lu] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName,Code,InputBufferLength,OutputBufferLength));

		// !!!!! IRP sa nastavi, ze bude spracovane ASYNCHRONNE.
		IoMarkIrpPending(Irp);

		// !!!!! IRP sa zaradi do WORK ITEM QUEUE, aby sa simulovalo ASYNCRHONNE spracovanie.
		IoQueueWorkItemEx(WorkItem,IrpPassDownAsynchronousProcessingWorkItemRoutine,WORK_QUEUE_TYPE::DelayedWorkQueue,Irp);

		// !!!!! Pri ASYNCHRONNOM spracovani sa MUSI nastavit STATUS [STATUS_PENDING].
		return(Status);
	}
	else
	{
		KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] LOWER DRIVER - CAN NOT ALLOCATE WORK ITEM.\n",DeviceObject->DriverObject->DriverName,FunctionName));

		NTSTATUS												Status=STATUS_SUCCESS;
		ULONG_PTR												Information=0;

		Irp->IoStatus.Status=Status;
		Irp->IoStatus.Information=Information;

		// !!! FUNCTION ukonci IRP.
		IofCompleteRequest(Irp,IO_NO_INCREMENT);

		return(Status);
	}
}
//----------------------------------------------------------------------------------------------------------------------