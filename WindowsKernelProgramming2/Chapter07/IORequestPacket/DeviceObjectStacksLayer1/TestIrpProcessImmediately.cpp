//----------------------------------------------------------------------------------------------------------------------
#include "TestIrpProcessImmediately.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestIrpProcessImmediately(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;
	
	// !!! FUNCTION vrati CURRENT STACK LOCATION.
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
	ULONG														InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;
	ULONG														OutputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	
	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] UPPER DRIVER - CODE [%lu] INPUT BUFFER LENGTH [%lu] OUTPUT BUFFER LENGTH [%lu] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName,Code,InputBufferLength,OutputBufferLength));

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------