//----------------------------------------------------------------------------------------------------------------------
#include "DeviceControlGetStatus.h"
#include "SharedHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DeviceControlGetStatus(DEVICE_OBJECT* DeviceObject, IRP* Irp, volatile LONG64& TotalReadBytes, volatile LONG64& TotalWriteBytes)
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

	do
	{
		if (OutputBufferLength<sizeof(SReadWriteStatistics))
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			break;
		}

		SReadWriteStatistics*									ReadWriteStatistics=(SReadWriteStatistics*) Irp->AssociatedIrp.SystemBuffer;

		if (ReadWriteStatistics==nullptr)
		{
			Status=STATUS_INVALID_PARAMETER;
			break;
		}

		// !!!!! Nacita SHARED VARIABLES INTERLOCKED sposobom. Alternativou je pouzitie FUNCTION [ReadAcquire64()].
		LONG64													LocalTotalReadBytes=InterlockedOr64(&TotalReadBytes,0);
		LONG64													LocalTotalWriteBytes=InterlockedOr64(&TotalWriteBytes,0);

		ReadWriteStatistics->SetTotalReadBytes(LocalTotalReadBytes);
		ReadWriteStatistics->SetTotalWriteBytes(LocalTotalWriteBytes);

		Information=sizeof(SReadWriteStatistics);
		Status=STATUS_SUCCESS;
	}
	while(false);

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------