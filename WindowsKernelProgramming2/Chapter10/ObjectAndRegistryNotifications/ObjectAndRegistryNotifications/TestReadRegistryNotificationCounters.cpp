//----------------------------------------------------------------------------------------------------------------------
#include "TestReadRegistryNotificationCounters.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestReadRegistryNotificationCounters(DEVICE_OBJECT* DeviceObject, IRP* Irp, const SRegistryNotificationStatistics& Statistics)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	PVOID														OutputBuffer=Irp->AssociatedIrp.SystemBuffer;
	ULONG														OutputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG														DataSize=sizeof(SRegistryNotificationStatistics);

	do
	{
		if (OutputBufferLength<DataSize)
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			break;
		}

		if (OutputBuffer==nullptr)
		{
			Status=STATUS_INVALID_PARAMETER;
			break;
		}

		SRegistryNotificationStatistics*						TypedOutputBuffer=static_cast<SRegistryNotificationStatistics*>(Irp->AssociatedIrp.SystemBuffer);

		RtlCopyMemory(TypedOutputBuffer,&Statistics,DataSize);

		Information=DataSize;
		Status=STATUS_SUCCESS;
	}
	while(false);

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------