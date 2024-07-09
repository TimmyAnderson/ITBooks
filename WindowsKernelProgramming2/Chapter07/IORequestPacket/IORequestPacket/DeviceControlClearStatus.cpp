//----------------------------------------------------------------------------------------------------------------------
#include "DeviceControlClearStatus.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DeviceControlClearStatus(DEVICE_OBJECT* DeviceObject, IRP* Irp, volatile LONG64& TotalReadBytes, volatile LONG64& TotalWriteBytes)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;
	
	// !!! FUNCTION vrati CURRENT STACK LOCATION.
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
	ULONG														InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;
	ULONG														OutputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	
	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] IRP [%p] CODE [%lu] INPUT BUFFER LENGTH [%lu] OUTPUT BUFFER LENGTH [%lu] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName,Irp,Code,InputBufferLength,OutputBufferLength));

	// !!! Vykona sa RESET oboch COUNTERS.
	InterlockedExchange64(&TotalReadBytes,0);
	InterlockedExchange64(&TotalWriteBytes,0);

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------