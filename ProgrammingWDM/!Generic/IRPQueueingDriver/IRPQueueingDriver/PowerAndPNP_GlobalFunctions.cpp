//-------------------------------------------------------------------------------------------------------
#include <wdm.h>
#include <initguid.h>
#include "PowerAndPNP_Structures.h"
//-------------------------------------------------------------------------------------------------------
#define VERMAJOR 2
#define VERMINOR 0
#define BUILD 0
#define PRODVER "2, 0, 0, 0\0"
//-------------------------------------------------------------------------------------------------------
DEFINE_GUID(GUID_AUTOLAUNCH_NOTIFY, 0xba4ec740, 0xda8b, 0x11d2, 0x81, 0xb5, 0x0, 0xc0, 0x4f, 0xa3, 0x30, 0xa6);
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS OnRequestComplete(PDEVICE_OBJECT Junk, PIRP IRP, PKEVENT PEvent);
//-------------------------------------------------------------------------------------------------------
GENERICAPI VOID GENERIC_EXPORT CleanupGenericExtension(PGENERIC_EXTENSION PDX)
{
	if (PDX->MQueues!=NULL)
	{
		ExFreePoolWithTag(PDX->MQueues,' EUQ');
	}

	PDX->MQueues=NULL;
	PDX->MNumberQueues=0;
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
NTSTATUS CompleteRequest(PIRP IRP, NTSTATUS Status, ULONG_PTR Info)
{
	IRP->IoStatus.Status=Status;
	IRP->IoStatus.Information=Info;
	IoCompleteRequest(IRP,IO_NO_INCREMENT);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Overloaded variant that doesn't change IoStatus.Information -- use this for most PnP requests.
NTSTATUS CompleteRequest(PIRP IRP, NTSTATUS Status)
{
	IRP->IoStatus.Status=Status;
	IoCompleteRequest(IRP,IO_NO_INCREMENT);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION ForwardAndWait() zasle IRP NIZSIE do DEVICE OBJECT STACK a caka na skoncenie spracovania IRP cakanim na EVENT, ktory sa nastavuje v COMPLETION ROUTINE OnRequestComplete().
NTSTATUS ForwardAndWait(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	KEVENT														Event;

	KeInitializeEvent(&Event,NotificationEvent,FALSE);

	IoCopyCurrentIrpStackLocationToNext(IRP);
	IoSetCompletionRoutine(IRP,(PIO_COMPLETION_ROUTINE) OnRequestComplete,(PVOID) &Event,TRUE,TRUE,TRUE);

	IoCallDriver(PDX->MLowerDeviceObject,IRP);
	KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL);

	return(IRP->IoStatus.Status);
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
GENERICAPI ULONG GENERIC_EXPORT GenericGetVersion(void)
{
	return((VERMAJOR<<16) | VERMINOR);
}
//-------------------------------------------------------------------------------------------------------
// Portable implementation of MmGetSystemAddressForMDLSafe().
#pragma LOCKEDCODE
GENERICAPI PVOID GENERIC_EXPORT GenericGetSystemAddressForMDL(PMDL MDL)
{
	if (MDL==NULL)
	{
		return(NULL);
	}

	PVOID														Address=MmGetSystemAddressForMdlSafe(MDL,KernelMode);

	return(Address);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI ULONG GENERIC_EXPORT GetSizeofGenericExtension(void)
{
	ULONG														Size=(sizeof(GENERIC_EXTENSION)+7)&~7;

	return(Size);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI NTSTATUS GENERIC_EXPORT InitializeGenericExtension(PGENERIC_EXTENSION PDX, PGENERIC_INIT_STRUCT ISP)
{
	// ????? Neviem ci podmienka (ISP->MDeviceQueue!=NULL) je KOREKTNA.
	if (ISP->MSize<FIELD_OFFSET(GENERIC_INIT_STRUCT,MFlags) || ISP->MDeviceObject==NULL || ISP->MLDO==NULL || ISP->MPDO==NULL || ISP->MStartDevice==NULL || ISP->MStopDevice==NULL || ISP->MRemoveDevice==NULL || ISP->MDeviceQueue!=NULL && ISP->MStartIO==NULL)
	{
		return(STATUS_INVALID_PARAMETER);
	}

	RtlZeroMemory(PDX,sizeof(GENERIC_EXTENSION));

	PDX->MDeviceObject=ISP->MDeviceObject;
	PDX->MLowerDeviceObject=ISP->MLDO;
	PDX->MPDO=ISP->MPDO;
	PDX->MStartDevice=ISP->MStartDevice;
	PDX->MStopDevice=ISP->MStopDevice;
	PDX->MRemoveDevice=ISP->MRemoveDevice;
	PDX->MModifyResources=ISP->MModifyResources;

	if (ISP->MSize>=(FIELD_OFFSET(GENERIC_INIT_STRUCT,MOkayToRemove)+sizeof(PQUERYFUNCTION)))
	{
		PDX->MOkayToStop=ISP->MOkayToStop;
		PDX->MOkayToRemove=ISP->MOkayToRemove;
	}

	if ((PDX->MRemoveLock=ISP->MRemoveLock)!=NULL)
	{
		IoInitializeRemoveLock(PDX->MRemoveLock,0,0,0);
	}

	PDX->MState=STOPPED;
	PDX->MDevicePower=PowerDeviceD0;
	PDX->MSystemPower=PowerSystemWorking;

	POWER_STATE													State;

	State.DeviceState=PowerDeviceD0;
	PoSetPowerState(PDX->MDeviceObject,DevicePowerState,State);

	// In version 1.3, I added support for multiple IRP queues.
	if (ISP->MSize>=(FIELD_OFFSET(GENERIC_INIT_STRUCT,MNumberOfQueues)+sizeof(ULONG)) && ISP->MNumberOfQueues!=0)
	{
		// Multiple queues.
		if (ISP->MDeviceQueue!=NULL || ISP->MStartIO!=NULL)
		{
			// Can't mix new and old ways of identifying queues.
			return(STATUS_INVALID_PARAMETER);
		}

		if (ISP->MSize<(FIELD_OFFSET(GENERIC_INIT_STRUCT,MQueues)+ISP->MNumberOfQueues*2*sizeof(PVOID)))
		{
			// Init structure not big enough.
			return(STATUS_INVALID_PARAMETER);
		}

		for (ULONG Index=0;Index<ISP->MNumberOfQueues;++Index)
		{
			if (ISP->MQueues[Index].MDeviceQueue==NULL || ISP->MQueues[Index].MStartIO==NULL)
			{
				// None of the entries can be NULL.
				return(STATUS_INVALID_PARAMETER);
			}
		}

		PDX->MNumberQueues=ISP->MNumberOfQueues;
		PDX->MQueues=(PDEVQUEUE*) ExAllocatePoolWithTag(NonPagedPool,ISP->MNumberOfQueues*sizeof(PDEVQUEUE),' EUQ');

		if (PDX->MQueues==NULL)
		{
			return(STATUS_INSUFFICIENT_RESOURCES);
		}

		for (ULONG Index=0;Index<ISP->MNumberOfQueues;++Index)
		{
			// For each queue.
			PDX->MQueues[Index]=ISP->MQueues[Index].MDeviceQueue;
			InitializeQueue(PDX->MQueues[Index],ISP->MQueues[Index].MStartIO);
		}
	}
	else if (ISP->MDeviceQueue!=NULL)
	{
		// Single queue.
		PDX->MNumberQueues=1;
		PDX->MQueues=(PDEVQUEUE*) ExAllocatePoolWithTag(NonPagedPool,sizeof(PDEVQUEUE),' EUQ');

		if (PDX->MQueues==NULL)
		{
			return(STATUS_INSUFFICIENT_RESOURCES);
		}

		PDX->MQueues[0]=ISP->MDeviceQueue;
		InitializeQueue(PDX->MQueues[0],ISP->MStartIO);
	}

	// In version 1.9, I added support for FlushPendingIo. In version 1.10, GetDevicePowerState.
	if (ISP->MSize>=FIELD_OFFSET(GENERIC_INIT_STRUCT,MQueues))
	{
		// Additional reserved fields.
		PDX->MFlushPendingIO=ISP->MFlushPendingIO;
		PDX->MGetDevicePowerState=ISP->MGetDevicePowerState;
	}

	// Capture the mini-driver name for messages. This needs to be in ANSI because unicode conversions at or above DISPATCH_LEVEL are not allowed. In retrospect, I should have made the field in the INIT struct be in ANSI to start with.
	if (ISP->MDebugName.Length==0)
	{
		strcpy_s(PDX->MDebugName,"GENERIC");
	}
	else
	{
		// Convert debug name.
		ANSI_STRING												ASName={0,sizeof(PDX->MDebugName)-1,PDX->MDebugName};

		RtlUnicodeStringToAnsiString(&ASName,&ISP->MDebugName,FALSE);
		PDX->MDebugName[ASName.Length]=0;
	}

	if (ISP->MSize>=(FIELD_OFFSET(GENERIC_INIT_STRUCT,MFlags)+sizeof(ULONG)))
	{
		PDX->MFlags=(ISP->MFlags&GENERIC_CLIENT_FLAGS);
	}

	if (ISP->MSize>=(FIELD_OFFSET(GENERIC_INIT_STRUCT,MRestoreDeviceContext)+sizeof(PCONTEXTFUNCTION)))
	{
		// Get power helper functions.
		PDX->MQueryPower=ISP->MQueryPower;
		PDX->MSaveDeviceContext=ISP->MSaveDeviceContext;
		PDX->MRestoreDeviceContext=ISP->MRestoreDeviceContext;
	}

	if (ISP->MSize>=(FIELD_OFFSET(GENERIC_INIT_STRUCT,MPerfBoundary)+sizeof(DEVICE_POWER_STATE)))
	{
		PDX->MPerfBoundary=ISP->MPerfBoundary;
	}
	else
	{
		PDX->MPerfBoundary=PowerDeviceUnspecified;
	}

	if (PDX->MPerfBoundary==PowerDeviceUnspecified)
	{
		// Inhibit POWER_SEQUENCE optimization.
		PDX->MPerfBoundary=PowerDeviceMaximum;
	}

	// Initialize variables related to asynchrounous IOCTL management. In version 2.0, this is now always done rather than depending on a flag in the init struct.
	InitializeListHead(&PDX->MPendingIoctlList);
	PDX->MIoctlAbortStatus=0;
	KeInitializeSpinLock(&PDX->MIoctlListLock);

	// Initialize to manage registered device interfaces.
	KeInitializeEvent(&PDX->MIfLock,SynchronizationEvent,TRUE);
	InitializeListHead(&PDX->MIfList);

	// Indicate we handle power IRPs at PASSIVE_LEVEL.
	PDX->MDeviceObject->Flags|=DO_POWER_PAGABLE;

	DbgPrint((DRIVERLOGNAME " - Initializing for [%s] !\n",PDX->MDebugName));

	// If device honors paging-path notifications, initialize a synchronization event in the signalled state to act as a simple mutex (SP-7).
	if ((PDX->MFlags & GENERIC_USAGE_PAGING)!=0)
	{
		KeInitializeEvent(&PDX->MEventPagingPath,SynchronizationEvent,TRUE);
	}

	// If requested to do so, register an AutoLaunch interface.
	if ((PDX->MFlags & GENERIC_AUTOLAUNCH)!=0)
	{
		GenericRegisterInterface(PDX,&GUID_AUTOLAUNCH_NOTIFY);
	}

	// Register a power management interface.
	GenericRegisterInterface(PDX,&GUID_GENERIC_POWER);

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
// !!! COMPLETION ROUTINE pouzivana FUNCTION CompleteRequest().
#pragma LOCKEDCODE
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS OnRequestComplete(PDEVICE_OBJECT, PIRP, PKEVENT PEvent)
{
	KeSetEvent(PEvent,0,FALSE);

	// !!!!! COMPLETION ROUTINE MUSI vracat hodnotu [STATUS_MORE_PROCESSING_REQUIRED], aby ZABRANILA volaniu dalsich COMPLETION ROUTINES. Je to NUTNE, pretoze IRP vo FUNCTION CompleteRequest() (resp. jej CALLERS) je dalej spracovavane. Ak by COMPLETION ROUTINE vratila hodnotu [STATUS_SUCCES], IO MANAGER by pokracoval vo volani COMPLETION ROUTINES vysledkom coho by bolo UVOLNENIE IRP z MEMORY. V tomto pripade by FUNCTION CompleteRequest() pristupila v NEPLATNEJ MEMORY a doslo by k vzniku BUG CHECK.
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// Force inline functions into locked code.
#pragma LOCKEDCODE
//-------------------------------------------------------------------------------------------------------