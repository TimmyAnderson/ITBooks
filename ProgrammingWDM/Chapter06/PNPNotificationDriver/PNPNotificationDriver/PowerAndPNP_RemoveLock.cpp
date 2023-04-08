//-------------------------------------------------------------------------------------------------------
#include <wdm.h>
#include "PowerAndPNP_Structures.h"
//-------------------------------------------------------------------------------------------------------
GENERICAPI VOID GENERIC_EXPORT GenericInitializeRemoveLock(PGENERIC_REMOVE_LOCK Lock, ULONG, ULONG, ULONG)
{
	KeInitializeEvent(&Lock->MEventRemove,NotificationEvent,FALSE);
	Lock->MUsage=1;
	Lock->MRemoving=FALSE;
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
GENERICAPI NTSTATUS GENERIC_EXPORT GenericAcquireRemoveLock(PGENERIC_REMOVE_LOCK Lock, PVOID)
{
	InterlockedIncrement(&Lock->MUsage);

	if (Lock->MRemoving!=FALSE)
	{
		// Removal in progress.
		if (InterlockedDecrement(&Lock->MUsage)==0)
		{
			KeSetEvent(&Lock->MEventRemove,0,FALSE);
		}

		return(STATUS_DELETE_PENDING);
	}

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI VOID GENERIC_EXPORT GenericReleaseRemoveLock(PGENERIC_REMOVE_LOCK Lock, PVOID)
{
	if (InterlockedDecrement(&Lock->MUsage)==0)
	{
		KeSetEvent(&Lock->MEventRemove,0,FALSE);
	}
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI VOID GENERIC_EXPORT GenericReleaseRemoveLockAndWait(PGENERIC_REMOVE_LOCK Lock, PVOID Tag)
{
	Lock->MRemoving=TRUE;
	GenericReleaseRemoveLock(Lock,Tag);
	GenericReleaseRemoveLock(Lock,NULL);
	KeWaitForSingleObject(&Lock->MEventRemove,Executive,KernelMode,FALSE,NULL);
}
//-------------------------------------------------------------------------------------------------------