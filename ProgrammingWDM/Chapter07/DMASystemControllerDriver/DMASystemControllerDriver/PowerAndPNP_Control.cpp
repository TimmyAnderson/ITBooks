//-------------------------------------------------------------------------------------------------------
#include <wdm.h>
#include "PowerAndPNP_Structures.h"
//-------------------------------------------------------------------------------------------------------
_IRQL_raises_(DISPATCH_LEVEL)
_Function_class_(DRIVER_CANCEL)
_Requires_lock_held_(_Global_cancel_spin_lock_)
VOID OnCancelPendingIoctl(PDEVICE_OBJECT Junk, PIRP IRP);
//-------------------------------------------------------------------------------------------------------
VOID AbortPendingIoctls(PGENERIC_EXTENSION PDX, NTSTATUS Status)
{
	if ((PDX->MFlags & GENERIC_PENDING_IOCTLS)==0)
	{
		// Can't be anything to do.
		return;
	}

	InterlockedExchange(&PDX->MIoctlAbortStatus,Status);
	GenericCleanupControlRequests(PDX,Status,NULL);
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
GENERICAPI NTSTATUS GENERIC_EXPORT GenericCacheControlRequest(PGENERIC_EXTENSION PDX, PIRP IRP, PIRP* PIRP)
{
	ASSERT(KeGetCurrentIrql()<=DISPATCH_LEVEL);

	// Acquire the lock that guards pending IOCTL operations for this client.
	KIRQL														OldIRQL;

	KeAcquireSpinLock(&PDX->MIoctlListLock,&OldIRQL);

	NTSTATUS													Status;

	if ((*PIRP)!=NULL)
	{
		// Something already cached here.
		Status=STATUS_UNSUCCESSFUL;
	}
	else if (PDX->MIoctlAbortStatus!=STATUS_SUCCESS)
	{
		// Rejecting new IRPs for some reason.
		Status=PDX->MIoctlAbortStatus;
	}
	else
	{
		// Try to cache IRP.
		// Remember the IRP pointer cell and device extension pointers in DriverContext fields within the IRP. This is how our cancel routine knows which lock to claim and which pointer cell to nullify. It's important to set these fields *before* installing the cancel pointer.
		IRP->Tail.Overlay.DriverContext[0]=(PVOID) PIRP;
		IRP->Tail.Overlay.DriverContext[1]=(PVOID) PDX;
		*PIRP=IRP;

		// Install a cancel routine and check for this IRP having already been cancelled.
		IoSetCancelRoutine(IRP,OnCancelPendingIoctl);
		
		if (IRP->Cancel!=FALSE && IoSetCancelRoutine(IRP,NULL)!=NULL)
		{
			// Already cancelled.
			Status=STATUS_CANCELLED;
		}
		// Put this IRP on our list of pending IOCTLs. Note that our cancel routine, if running, will be waiting for the spin lock before completing the IRP.
		else
		{					
			// Cache it.
			IoMarkIrpPending(IRP);
			Status=STATUS_PENDING;
			InsertTailList(&PDX->MPendingIoctlList,&IRP->Tail.Overlay.ListEntry);
		}
	}

	KeReleaseSpinLock(&PDX->MIoctlListLock,OldIRQL);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI VOID GENERIC_EXPORT GenericCleanupAllRequests(PGENERIC_EXTENSION PDX, PFILE_OBJECT FOP, NTSTATUS Status)
{
	CleanupAllRequests(PDX->MQueues,PDX->MNumberQueues,FOP,Status);
	GenericCleanupControlRequests(PDX,Status,FOP);
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
GENERICAPI VOID GENERIC_EXPORT GenericCleanupControlRequests(PGENERIC_EXTENSION PDX, NTSTATUS, PFILE_OBJECT FOP)
{
	if ((PDX->MFlags & GENERIC_PENDING_IOCTLS)==0)
	{
		// Didn't signup for pending ioctl service !
		return;
	}

	LIST_ENTRY													CancelList;

	InitializeListHead(&CancelList);

	// Create a list of IRPs that belong to the same file object.
	KIRQL														OldIRQL;

	KeAcquireSpinLock(&PDX->MIoctlListLock,&OldIRQL);

	PLIST_ENTRY													First=&PDX->MPendingIoctlList;
	PLIST_ENTRY													Next;

	for (Next=First->Flink;Next!=First;)
	{
		// For each queued IRP.
		PIRP													IRPRecord=CONTAINING_RECORD(Next,IRP,Tail.Overlay.ListEntry);
		PIO_STACK_LOCATION										Stack=IoGetCurrentIrpStackLocation(IRPRecord);

		// Follow the chain to the next IRP now (so that the next iteration of the loop is properly setup whether we dequeue this IRP or not).

		PLIST_ENTRY												Current=Next;

		Next=Next->Flink;

		// Skip this IRP if it's not for the same file object as the current IRP_MJ_CLEANUP.
		if (FOP!=NULL && Stack->FileObject!=FOP)
		{
			// Not for same file object.
			continue;
		}

		// Set the CancelRoutine pointer to NULL and remove the IRP from the queue.
		if (IoSetCancelRoutine(IRPRecord,NULL)==NULL)
		{
			// Being cancelled right this instant.
			continue;
		}

		PIRP*													PointerIRP=(PIRP*) IRPRecord->Tail.Overlay.DriverContext[0];

		*PointerIRP=NULL;
		RemoveEntryList(Current);
		InsertTailList(&CancelList,Current);
	}

	// Release the spin lock. We're about to undertake a potentially time-consuming operation that might conceivably result in a deadlock if we keep the lock.
	KeReleaseSpinLock(&PDX->MIoctlListLock,OldIRQL);

	// Complete the selected requests.
	while(IsListEmpty(&CancelList)==FALSE)
	{
		// Cancel selected requests.
		Next=RemoveHeadList(&CancelList);

		PIRP													PointerIRP=CONTAINING_RECORD(Next,IRP,Tail.Overlay.ListEntry);

		PointerIRP->IoStatus.Status=STATUS_CANCELLED;
		IoCompleteRequest(PointerIRP,IO_NO_INCREMENT);
	}
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
GENERICAPI PIRP GENERIC_EXPORT GenericUncacheControlRequest(PGENERIC_EXTENSION PDX, PIRP* PointerPIRP)
{
	ASSERT(KeGetCurrentIrql()<=DISPATCH_LEVEL);

	if ((PDX->MFlags & GENERIC_PENDING_IOCTLS)==0)
	{
		return(NULL);
	}
	
	KIRQL														OldIRQL;

	KeAcquireSpinLock(&PDX->MIoctlListLock,&OldIRQL);

	// Uncache the request. Once we claim the spin lock, it's not necessary to further synchronize access to the pointer cell.
	PIRP														PointerIRP=*PointerPIRP;

	*PointerPIRP=NULL;

	if (PointerIRP!=NULL)
	{
		// An IRP was cached.
		// Clear the cancel pointer for this IRP. Since both we and the completion routine use a spin lock, it cannot happen that this IRP pointer is suddenly invalid but the cache pointer cell wasn't already NULL.
		if (IoSetCancelRoutine(PointerIRP,NULL)!=NULL)
		{
			// Uncache the IRP.
			RemoveEntryList(&PointerIRP->Tail.Overlay.ListEntry);
		}
		else
		{
			// Currently being cancelled.
			PointerIRP=NULL;
		}
	}

	KeReleaseSpinLock(&PDX->MIoctlListLock,OldIRQL);
	
	return(PointerIRP);
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
_IRQL_raises_(DISPATCH_LEVEL)
_Function_class_(DRIVER_CANCEL)
_Requires_lock_held_(_Global_cancel_spin_lock_)
VOID OnCancelPendingIoctl(PDEVICE_OBJECT, PIRP IRP)
{
	KIRQL														OldIRQL=IRP->CancelIrql;

	IoReleaseCancelSpinLock(DISPATCH_LEVEL);

	// Remove the IRP from the pending IOCTL list. Also nullify the pointer cell that points to this IRP. The following weird possibility exists:
	//	1.	Someone calls IoCancelIrp for this IRP.
	//	2.	Someone calls UncacheControlRequest for this pointer cell, and it gets to the point of calling IoSetCancelRoutine, whereupon it sees that IoCancelIrp has already nulled the cancel pointer. It releases the spin lock and returns NULL to its caller.
	//	3.	Someone calls CacheControlRequest for this pointer cell. It acquires the spin lock and sees that the pointer cell is NULL (from step 2), so it caches a new IRP and releases the spin lock.
	//	4.	We acquire the spin lock.
	// At this point, we need to be careful how we nullify the pointer cell to avoid wiping out what happened in step 3. The hypothetical other IRP cannot be at the same address as this one because we haven't completed this one yet.
	PIRP*														PointerIRP=(PIRP*) IRP->Tail.Overlay.DriverContext[0];
	PGENERIC_EXTENSION											PDX=(PGENERIC_EXTENSION) IRP->Tail.Overlay.DriverContext[1];

	KeAcquireSpinLockAtDpcLevel(&PDX->MIoctlListLock);
	RemoveEntryList(&IRP->Tail.Overlay.ListEntry);

	if ((*PointerIRP)==IRP)
	{
		// No need for interlocked operation here.
		*PointerIRP=NULL;
	}

	KeReleaseSpinLock(&PDX->MIoctlListLock,OldIRQL);

	// Complete the IRP.
	IRP->IoStatus.Status=STATUS_CANCELLED;
	IoCompleteRequest(IRP,IO_NO_INCREMENT);
}
//-------------------------------------------------------------------------------------------------------