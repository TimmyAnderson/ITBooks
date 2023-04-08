//-------------------------------------------------------------------------------------------------------
#include "MyCSQIRPQueueing.h"
//-------------------------------------------------------------------------------------------------------
#pragma code_seg()
PDEVICE_EXTENSION GetDeviceExtension(PIO_CSQ Queue)
{
	PDEVICE_EXTENSION											DeviceExtension=CONTAINING_RECORD(Queue,DEVICE_EXTENSION,CancelSafeIRPQueue);

	return(DeviceExtension);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma code_seg()
NTSTATUS MyCSQInsertIRPEx(PIO_CSQ Queue, PIRP InterruptRequestPacket, PVOID)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	PDEVICE_EXTENSION											DeviceExtension=GetDeviceExtension(Queue);

	InsertTailList(&DeviceExtension->CancelSafeIRPQueueList,&InterruptRequestPacket->Tail.Overlay.ListEntry);

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
#pragma code_seg()
VOID MyCSQRemoveIRP(PIO_CSQ, PIRP InterruptRequestPacket)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	RemoveEntryList(&InterruptRequestPacket->Tail.Overlay.ListEntry);
}
//-------------------------------------------------------------------------------------------------------
#pragma code_seg()
// !!! PeekContext sa bude IGNOROVAT.
// !!! InterruptRequestPacket urcuje od ktoreho IRP v IRP QUEUE sa ma najst NEXT IRP. Ak InterruptRequestPacket==NULL, tak sa hlada od ZACIATKU IRP QUEUE.
PIRP MyCSQPeekNextIRP(PIO_CSQ Queue, PIRP InterruptRequestPacket, PVOID PeekContext)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	PDEVICE_EXTENSION											DeviceExtension=CONTAINING_RECORD(Queue,DEVICE_EXTENSION,CancelSafeIRPQueue);
	// !!! Ak InterruptRequestPacket!=NULL, tak zacne hladat nasledujuce IRP od InterruptRequestPacket.
	// !!!!! Ak InterruptRequestPacket!=NULL, tak zacne hladat od PRVEHO IRP v IRP QUEUE. PRVE IRP v IRP QUEUE je ulozene v POINTER DeviceExtension->CancelSafeIRPQueueList.Flink, kedze CancelSafeIRPQueueList reprezentuje CYKLICKY LIST.
	PLIST_ENTRY													Next=(InterruptRequestPacket!=NULL) ? InterruptRequestPacket->Tail.Overlay.ListEntry.Flink : DeviceExtension->CancelSafeIRPQueueList.Flink;

	while (Next!=&DeviceExtension->CancelSafeIRPQueueList)
    {
		PIRP													NextInterruptRequestPacket=CONTAINING_RECORD(Next,IRP,Tail.Overlay.ListEntry);

		// !!! Tu je podmienka vyhodnocujuca PeekContext.
		// !!!!! Predpoklada sa, ze PeekContext je typu FILE_OBJECT, pretoze IRP_MJ_CLEANUP musi DRIVER odstranit VSETKY IRP patriace uzatvaranemu FILE_OBJECT.
		if (PeekContext!=NULL)
		{
			PFILE_OBJECT										FileObject=(PFILE_OBJECT) PeekContext;
			PIO_STACK_LOCATION									StackLocation=IoGetCurrentIrpStackLocation(NextInterruptRequestPacket);

			// !!!!! Ak IRP ma rovnaky FILE_OBJECT ako zaslany FILE_OBJECT, IRP bol NAJDENY.
			if (StackLocation->FileObject==FileObject)
			{
				return(NextInterruptRequestPacket);
			}
		}
		// !!!!! Ak je CONTEXT NULL, tak sa vrati prvy IRP.
		else if (PeekContext==NULL)
		{
			return(NextInterruptRequestPacket);
		}

		Next=Next->Flink;
    }

	return(NULL);
}
//-------------------------------------------------------------------------------------------------------
#pragma code_seg()
VOID MyCSQCompleteCanceledIRP(PIO_CSQ, PIRP InterruptRequestPacket)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	InterruptRequestPacket->IoStatus.Status=STATUS_CANCELLED;
	InterruptRequestPacket->IoStatus.Information=0;

	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);
}
//-------------------------------------------------------------------------------------------------------
_IRQL_raises_(DISPATCH_LEVEL)
#pragma code_seg()
VOID MyCSQAcquireLock(PIO_CSQ Queue, PKIRQL IRQL)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	PDEVICE_EXTENSION											DeviceExtension=CONTAINING_RECORD(Queue,DEVICE_EXTENSION,CancelSafeIRPQueue);

	KeAcquireSpinLock(&DeviceExtension->CancelSafeIRPQueueLock,IRQL);
}
//-------------------------------------------------------------------------------------------------------
_IRQL_raises_(DISPATCH_LEVEL)
#pragma code_seg()
VOID MyCSQReleaseLock(PIO_CSQ Queue, KIRQL IRQL)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	PDEVICE_EXTENSION											DeviceExtension=CONTAINING_RECORD(Queue,DEVICE_EXTENSION,CancelSafeIRPQueue);

	KeReleaseSpinLock(&DeviceExtension->CancelSafeIRPQueueLock,IRQL);
}
//-------------------------------------------------------------------------------------------------------