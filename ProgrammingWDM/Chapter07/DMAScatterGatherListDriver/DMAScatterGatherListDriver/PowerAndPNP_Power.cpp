//-------------------------------------------------------------------------------------------------------
#include <wdm.h>
#include "Macros.h"
#include "Defines.h"
#include "PowerAndPNP_Structures.h"
//-------------------------------------------------------------------------------------------------------
NTSTATUS DefaultPowerHandler(PGENERIC_EXTENSION PDX, PIRP IRP);
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS WaitWakeCompletionRoutine(PDEVICE_OBJECT Junk, PIRP IRP, PGENERIC_EXTENSION PDX);
_Function_class_(REQUEST_POWER_COMPLETE)
VOID WaitWakeCallback(PDEVICE_OBJECT Junk, UCHAR MinorFunction, POWER_STATE State, PGENERIC_EXTENSION PDX, PIO_STATUS_BLOCK PStatus);
//-------------------------------------------------------------------------------------------------------
enum POWSTATE
{
	// Initial state of FSM.
	InitialState=0,
	// System power-up IRP forwarded.
	SysPowerUpPending,
	// Waiting for nested device power up to finish.
	SubPowerUpPending,
	// Waiting from device to power down before forwarding system power-down IRP.
	SubPowerDownPending,
	// Waiting for system power-down IRP to finish.
	SysPowerDownPending,
	// Waiting for device power-up IRP.
	DevPowerUpPending,
	// Waiting for device power-down IRP.
	DevPowerDownPending,
	// Context save is underway.
	ContextSavePending,
	// Context restore is underway.
	ContextRestorePending,
	// Device query for power-up pending.
	DevQueryUpPending,
	// Device query for power-down pending.
	DevQueryDownPending,
	// Waiting for device to be idle.
	QueueStallPending,
	// Waiting to get sequence numbers after context save.
	SaveSeqPending,
	// Waiting to get sequence numbers before context restore.
	RestoreSeqPending,
	// Waiting for PASSIVE_LEVEL callback to complete IRP.
	PassiveCompletePending,
	// Final state of FSM.
	FinalState,
	NUMPOWSTATES,
};
//-------------------------------------------------------------------------------------------------------
enum POWEVENT
{
	// New query/set IRP.
	NewIRP=0,
	// The main IRP has finished.
	MainIRPComplete,
	// Some other event has occurred.
	AsyncNotify,
	NUMPOWEVENTS,
};
//-------------------------------------------------------------------------------------------------------
typedef struct _POWCONTEXT
{
	// Unique sequence number for this IRP.
	LONG														MID;
	// Number of events generated for this IRP.
	LONG														MEventCount;
	// Our own device extension.
	PGENERIC_EXTENSION											MPDX;
	// The IRP we're processing.
	PIRP														MIRP;
	// Current state of FSM.
	enum POWSTATE												MState;
	// Completion status for main IRP.
	NTSTATUS													MStatus;
	// Device power state to use.
	DEVICE_POWER_STATE											MDeviceState;
	// Sequence numbers retrieved by ditto.
	POWER_SEQUENCE												MSequence;
	// Previous device power state.
	DEVICE_POWER_STATE											MOldPower;
	// Minor function to use in requested power IRP.
	UCHAR														MMinorFunction;
	// Unstall queue when main IRP finishes.
	BOOLEAN														MUnstallQueue;
}POWCONTEXT, *PPOWCONTEXT;
//-------------------------------------------------------------------------------------------------------
struct SDSP_CONTEXT
{
	// Event to signal when request complete.
	PKEVENT														MPEvent;
	// Ending status.
	NTSTATUS													MStatus;
};
//-------------------------------------------------------------------------------------------------------
NTSTATUS HandlePowerEvent(PPOWCONTEXT Context, enum POWEVENT Event);
//-------------------------------------------------------------------------------------------------------
// Counter for POWCONTEXT structures.
static LONG														ContextCount=0;
//-------------------------------------------------------------------------------------------------------
static char* FunctionName[]=
{
	"IRP_MN_WAIT_WAKE",
	"IRP_MN_POWER_SEQUENCE",
	"IRP_MN_SET_POWER",
	"IRP_MN_QUERY_POWER",
};
//-------------------------------------------------------------------------------------------------------
static char* SystemState[]=
{
	"PowerSystemUnspecified",
	"PowerSystemWorking",
	"PowerSystemSleeping1",
	"PowerSystemSleeping2",
	"PowerSystemSleeping3",
	"PowerSystemHibernate",
	"PowerSystemShutdown",
	"PowerSystemMaximum",
};
//-------------------------------------------------------------------------------------------------------
static char* DeviceState[]=
{
	"PowerDeviceUnspecified",
	"PowerDeviceD0",
	"PowerDeviceD1",
	"PowerDeviceD2",
	"PowerDeviceD3",
	"PowerDeviceMaximum",
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
GENERICAPI NTSTATUS GENERIC_EXPORT GenericDispatchPower(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	if (PDX->MRemoveLock!=NULL)
	{
		Status=IoAcquireRemoveLock(PDX->MRemoveLock,IRP);

		if (NT_SUCCESS(Status)==false)
		{
			PoStartNextPowerIrp(IRP);
			return(CompleteRequest(IRP,Status));
		}
	}

	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);

	ASSERT(Stack->MajorFunction==IRP_MJ_POWER);

	ULONG														Function=Stack->MinorFunction;

	if (Function==IRP_MN_SET_POWER || Function==IRP_MN_QUERY_POWER)
	{
		// Handle set/query.
		if (Stack->Parameters.Power.Type==SystemPowerState)
		{
			DbgPrint("%s - POWER Request [%s], S-state=[%s] !\n",PDX->MDebugName,FunctionName[Function],DeviceState[Stack->Parameters.Power.State.SystemState]);
		}
		else
		{
			DbgPrint("%s - POWER Request [%s], D-state=[%s] !\n",PDX->MDebugName,FunctionName[Function],DeviceState[Stack->Parameters.Power.State.DeviceState]);
		}

		// Create a context structure and launch the finite state machine that will process this IRP asynchronously. The initial call to HandlePowerEvent() should return STATUS_PENDING. The FSM will eventually complete the IRP.
		PPOWCONTEXT												Context=(PPOWCONTEXT) ExAllocatePoolWithTag(NonPagedPool,sizeof(POWCONTEXT),'  CP');

		if (Context==NULL)
		{
			DbgPrint("%s - Can't allocate power context structure !\n",PDX->MDebugName);

			PoStartNextPowerIrp(IRP);
			Status=CompleteRequest(IRP,STATUS_INSUFFICIENT_RESOURCES);
		}
		else
		{
			// Process this IRP.
			RtlZeroMemory(Context,sizeof(POWCONTEXT));

			Context->MPDX=PDX;
			Context->MIRP=IRP;
			Context->MID=InterlockedIncrement(&ContextCount);
			Status=HandlePowerEvent(Context,NewIRP);
		}
	}
	else
	{
		// Handle other power request.
		if (Function<_countof(FunctionName))
		{
			DbgPrint("%s - POWER Request [%s] !\n",PDX->MDebugName,FunctionName[Function]);
		}
		else
		{
			DbgPrint("%s - POWER Request ?? [0x%X] !\n",PDX->MDebugName,Function);
		}

		// Install a completion routine for a WAIT_WAKE so we're sure to nullify our cached pointer before the IRP disappears.
		if (Function==IRP_MN_WAIT_WAKE)
		{
			// Wait-wake IRP.
			PoStartNextPowerIrp(IRP);
			IoCopyCurrentIrpStackLocationToNext(IRP);
			IoSetCompletionRoutine(IRP,(PIO_COMPLETION_ROUTINE) WaitWakeCompletionRoutine,PDX,TRUE,TRUE,TRUE);
			Status=IoCallDriver(PDX->MLowerDeviceObject,IRP);
		}
		else
		{
			// Simply forward any other power IRP. At the present time, the only kind it could be is IRP_MN_POWER_SEQUENCE, which probably no-one actually uses.
			Status=DefaultPowerHandler(PDX,IRP);
		}
	}
	
	if (PDX->MRemoveLock!=NULL)
	{
		IoReleaseRemoveLock(PDX->MRemoveLock,IRP);
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI NTSTATUS GENERIC_EXPORT GenericHandlePowerIoctl(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(KeGetCurrentIrql()==PASSIVE_LEVEL);

	ULONG														Info=0;
	NTSTATUS													Status=STATUS_SUCCESS;
	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);

	if (Stack->MajorFunction!=IRP_MJ_DEVICE_CONTROL)
	{
		return(STATUS_INVALID_DEVICE_REQUEST);
	}

	ULONG														CBIn=Stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG														CBOut=Stack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG														Code=Stack->Parameters.DeviceIoControl.IoControlCode;

	// Process request.
	switch(Code)
	{
		case IOCTL_GET_POWERINFO:
		{
			if (CBOut<sizeof(POWERINFO))
			{
				Status=STATUS_INVALID_PARAMETER;
				break;
			}
		
			PPOWERINFO											PIP=(PPOWERINFO) IRP->AssociatedIrp.SystemBuffer;

			// Get timeout constants from the registry.
			Status=GetPowerInfoFromRegistry(PDX,PIP);

			if (NT_SUCCESS(Status)==false)
			{
				// Initialize parameters.
				PIP->MConservation=0;
				PIP->MPerformance=0;
				Status=STATUS_SUCCESS;
			}

			// Determine current device state.
			PIP->MCanIdle=((PDX->MFlags & GENERIC_IDLE_DETECT)!=0);
			PIP->MCanWake=(PDX->MDeviceCaps.SystemWake!=PowerSystemUnspecified && PDX->MDeviceCaps.DeviceWake!=PowerDeviceUnspecified);
			PIP->MWakeup=PDX->MWakeupEnabled;
			PIP->MIdle=(PDX->MDevicePower>PowerDeviceD0);
		
			Info=sizeof(POWERINFO);
			break;
		}

		case IOCTL_SET_POWERINFO:
		{
			if (CBIn<sizeof(POWERINFO))
			{
				Status=STATUS_INVALID_PARAMETER;
				break;
			}

			// If we're currently idle, restore power. This is in case we've just been told to never idle in the power mode the machine is currently in (which we can't easily determine).
			GenericWakeupFromIdle(PDX,TRUE);

			PPOWERINFO											PIP=(PPOWERINFO) IRP->AssociatedIrp.SystemBuffer;

			Status=WritePowerInfoToRegistry(PDX,PIP);

			if (NT_SUCCESS(Status)==true)
			{
				Status=ImplementPowerPolicy(PDX,PIP);
			}

			break;
		}

		case IOCTL_IDLENOW:
		{
			Status=GenericIdleDevice(PDX,PowerDeviceD3);
			break;
		}

		default:
		{
			Status=STATUS_INVALID_DEVICE_REQUEST;
		}
		break;
	}

	IRP->IoStatus.Information=Info;
	IRP->IoStatus.Status=Status;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI NTSTATUS GENERIC_EXPORT GenericIdleDevice(PGENERIC_EXTENSION PDX, DEVICE_POWER_STATE State, BOOLEAN Wait/*=FALSE*/)
{
	if (PDX->MState!=WORKING && PDX->MState!=STOPPED)
	{
		return(STATUS_SUCCESS);
	}

	NTSTATUS													Status=SendDeviceSetPower(PDX,State,Wait);

	if (Status==STATUS_PENDING)
	{
		Status=STATUS_SUCCESS;
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI VOID GENERIC_EXPORT GenericMarkDeviceBusy(PGENERIC_EXTENSION PDX)
{
	if (PDX->MIdleCount!=0)
	{
		PoSetDeviceBusy(PDX->MIdleCount);
	}
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI VOID GENERIC_EXPORT GenericRegisterForIdleDetection(PGENERIC_EXTENSION PDX, ULONG ConservationTimeout, ULONG PerformanceTimeout, DEVICE_POWER_STATE State)
{
	// Required by PoRegisterDeviceForIdleDetection.
	ASSERT(KeGetCurrentIrql()<DISPATCH_LEVEL);

	PDX->MCTO=ConservationTimeout;
	PDX->MPTO=PerformanceTimeout;
	PDX->MIdleState=State;
	PDX->MIdleCount=PoRegisterDeviceForIdleDetection(PDX->MPDO,ConservationTimeout,PerformanceTimeout,State);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI VOID GENERIC_EXPORT GenericSaveRestoreComplete(PVOID Context)
{
	HandlePowerEvent((PPOWCONTEXT) Context,AsyncNotify);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI NTSTATUS GENERIC_EXPORT GenericWakeupControl(PGENERIC_EXTENSION PDX, enum WAKEFUNCTION WF)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	// Perform requested function.
	switch(WF)
	{
		case EnableWakeup:
		{
			PDX->MWakeupEnabled=TRUE;
			goto Manage;
		}

		case DisableWakeup:
		{
			PDX->MWakeupEnabled=FALSE;
			goto Manage;
		}

		case ManageWaitWake:
		Manage:
		{
			if (PDX->MWakeupEnabled!=FALSE)
			{
				// Wakeup is enabled.
				// If capabilities don't provide for wakeup, don't do anything. This often happens the first time we get called because the capabilities query hasn't happened yet. Also, we mustn't issue a WAIT_WAKE if the device is not in D0.
				if (PDX->MDevicePower>PDX->MDeviceCaps.DeviceWake || PDX->MSystemPower>PDX->MDeviceCaps.SystemWake || PDX->MDevicePower!=PowerDeviceD0)
				{
					DbgPrint("%s - Deferring WAIT_WAKE due to state or capabilities !\n",PDX->MDebugName);
					return(STATUS_INVALID_DEVICE_REQUEST);
				}

				if (InterlockedExchange(&PDX->MWWOutstanding,1)!=0)
				{
					// IRP already pending.
					break;
				}

				PDX->MWWCancelled=0;

				POWER_STATE										Junk;

				// Lowest state from which this IRP will wake system.
				Junk.SystemState=PDX->MDeviceCaps.SystemWake;

				// I have seen systems where SystemState has a ridiculous value, such that we have to ask for S0 or else it doesn't work.
				if (Junk.SystemState>PowerSystemHibernate)
				{
					// Correct bogus value.
					DbgPrint("%s - Requesting WAIT_WAKE with S0 instead of bogus S%d from capabilities !\n",PDX->MDebugName,Junk.SystemState-1);
					Junk.SystemState=PowerSystemWorking;
				}
			
				DbgPrint("%s - Issuing WAIT_WAKE !\n",PDX->MDebugName);
			
				Status=PoRequestPowerIrp(PDX->MPDO,IRP_MN_WAIT_WAKE,Junk,(PREQUEST_POWER_COMPLETE) WaitWakeCallback,PDX,&PDX->MWaitWakeIRP);

				if (NT_SUCCESS(Status)==false)
				{
					// Error starting wakeup IRP.
					DbgPrint("%s - PoRequestPowerIrp(IRP_MN_WAIT_WAIT) failed - [%X] !\n",PDX->MDebugName,Status);
					PDX->MWakeupEnabled=FALSE;
					PDX->MWWOutstanding=0;
					break;
				}

				// Especially *not* STATUS_PENDING.
				Status=STATUS_SUCCESS;
				break;
			}

			// Note fall-through to CanceWaitWake here.
		}

		case CancelWaitWake:
		{
			// If the following exchange operation returns NULL, WaitWakeComplete has run and the IRP may no longer exist.
			PIRP												IRP=(PIRP) InterlockedExchangePointer((PVOID*)&PDX->MWaitWakeIRP,NULL);

			if (IRP!=NULL)
			{
				// Cancel pending IRP.
				// We need to be sure that IoCancelIrp and any cancel routine it may call finish before the Power Manager calls IoFreeIrp to get rid of the WAIT_WAKE IRP. The call to IoFreeIrp can't happen sooner than the IRP gets all the way through IoCompleteRequest, however, so we establish an interlock such that whichever of us and our completion routine sees the IRP last allows it to complete.
				IoCancelIrp(IRP);
				DbgPrint("%s - IRP_MN_WAIT_WAKE cancelled !\n",PDX->MDebugName);

				if (InterlockedExchange(&PDX->MWWCancelled,1)!=0)
				{
					// Pickup with aborted completion.
					IoCompleteRequest(IRP,IO_NO_INCREMENT);
				}
			}

			break;
		}

		default:
		{
			ASSERT(FALSE);
			Status=STATUS_INVALID_DEVICE_REQUEST;
		}
		break;
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI NTSTATUS GENERIC_EXPORT GenericWakeupFromIdle(PGENERIC_EXTENSION PDX, BOOLEAN Wait/*=FALSE*/)
{
	if (PDX->MDevicePower==PowerDeviceD0)
	{
		return(STATUS_SUCCESS);
	}

	NTSTATUS													Status=SendDeviceSetPower(PDX,PowerDeviceD0,Wait);

	if (Status==STATUS_PENDING)
	{
		Status=STATUS_SUCCESS;
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
VOID AdjustSpecialFileCounter(PGENERIC_EXTENSION PDX, BOOLEAN InPath, PLONG Counter)
{
	// Increment or decrement the appopriate special-file usage counter. Note that IoAdjustPagingPathCount (recommended for this use in the DDK doc) is just a macro that does exactly this.
	if (InPath!=FALSE)
	{
		InterlockedIncrement(Counter);
	}
	else
	{
		InterlockedDecrement(Counter);
	}

	// Enable or disable idle detection, as appropriate. Alter the not-disableable status flag as well (SP-7, ver 1.6).
	LONG														TotalCount=PDX->MNumberDumpFiles+PDX->MNumberHibernateFiles+PDX->MNumberPageFiles;

	if (TotalCount==0)
	{
		// Resume idle detection.
		if (PDX->MCTO!=0 && PDX->MPTO!=0)
		{
			PDX->MIdleCount=PoRegisterDeviceForIdleDetection(PDX->MPDO,PDX->MCTO,PDX->MPTO,PDX->MIdleState);
		}

		GenericSetDeviceState(PDX,0);
	}
	else if (InPath!=FALSE && TotalCount==1)
	{
		// Disable idle detection.
		PDX->MIdleCount=PoRegisterDeviceForIdleDetection(PDX->MPDO,0,0,PowerDeviceD0);
		GenericSetDeviceState(PDX,PNP_DEVICE_NOT_DISABLEABLE);
	}
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS DefaultPowerHandler(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	// Must be done while we own the IRP.
	PoStartNextPowerIrp(IRP);
	IoSkipCurrentIrpStackLocation(IRP);

	return(IoCallDriver(PDX->MLowerDeviceObject,IRP));
}
//-------------------------------------------------------------------------------------------------------
// GetLowestDevicePowerState returns the lowest device power state that is consistent with a given system power state and the current wakeup state of the device.
DEVICE_POWER_STATE GetLowestDevicePowerState(PGENERIC_EXTENSION PDX, SYSTEM_POWER_STATE CurrentSystemState)
{
	DEVICE_POWER_STATE											MaxState=PDX->MDeviceCaps.DeviceState[CurrentSystemState];
	DEVICE_POWER_STATE											MinState=PowerDeviceD3;

	if (PDX->MWakeupEnabled!=FALSE && CurrentSystemState<=PDX->MDeviceCaps.SystemWake)
	{
		// Select state that will preserve wakeup ability.
		MinState=PDX->MDeviceCaps.DeviceWake;
	}

	DEVICE_POWER_STATE											CurrentDeviceState=(MinState>MaxState) ? MinState : MaxState;

	// Allow minidriver to pick the new state, subject to the minimum and maximum already established.
	if (PDX->MGetDevicePowerState!=NULL)
	{
		// Let minidriver pick state.
		CurrentDeviceState=(*PDX->MGetDevicePowerState)(PDX->MDeviceObject,CurrentSystemState,CurrentDeviceState);

		if (CurrentDeviceState<MaxState)
		{
			CurrentDeviceState=MaxState;
		}
		else if (CurrentDeviceState>MinState)
		{
			CurrentDeviceState=MinState;
		}
	}

	return(CurrentDeviceState);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS GetPowerInfoFromRegistry(PGENERIC_EXTENSION PDX, PPOWERINFO PIP)
{
	HANDLE														HKey;
	NTSTATUS													Status=IoOpenDeviceRegistryKey(PDX->MPDO,PLUGPLAY_REGKEY_DEVICE,KEY_ALL_ACCESS,&HKey);

	if (NT_SUCCESS(Status)==false)
	{
		DbgPrint(DRIVERLOGNAME " - Error [%X] trying to open registry key !\n",Status);
		return(Status);
	}

	UNICODE_STRING												ValueName;

	RtlInitUnicodeString(&ValueName,L"PowerSettings");

	ULONG														Size=0;
	UCHAR														Junk;

	Status=ZwQueryValueKey(HKey,&ValueName,KeyValuePartialInformation,&Junk,0,&Size);

	if ((Status==STATUS_BUFFER_OVERFLOW || Status==STATUS_BUFFER_TOO_SMALL))
	{
		// Value exists.
		#pragma warning(suppress: 6102)
		PKEY_VALUE_PARTIAL_INFORMATION							VPIP=(PKEY_VALUE_PARTIAL_INFORMATION) ExAllocatePoolWithTag(PagedPool,Size,'IPVK');

		if (VPIP!=NULL)
		{
			Status=ZwQueryValueKey(HKey,&ValueName,KeyValuePartialInformation,VPIP,Size,&Size);

			if (NT_SUCCESS(Status)==true)
			{
				// Copy value.
				if (VPIP->DataLength<(2*sizeof(ULONG)))
				{
					DbgPrint("%s - Ignoring PowerSettings value with strange size [%d] !\n",PDX->MDebugName,VPIP->DataLength);
					Status=STATUS_UNSUCCESSFUL;
				}
				else
				{
					RtlCopyBytes(PIP,VPIP->Data,2*sizeof(ULONG));
				}
			}
			else
			{
				DbgPrint("ZwQueryValueKey failed - [%X] !\n",Status);
			}

			ExFreePoolWithTag(VPIP,'IPVK');
		}
		else
		{
			Status=STATUS_NO_MEMORY;
		}
	}

	ZwClose(HKey);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ImplementPowerPolicy(PGENERIC_EXTENSION PDX, PPOWERINFO PIP)
{
	if ((PDX->MFlags & GENERIC_IDLE_DETECT)!=0)
	{
		GenericRegisterForIdleDetection(PDX,PIP->MConservation,PIP->MPerformance,PowerDeviceD3);
	}

	GenericWakeupControl(PDX,(PIP->MWakeup) ? EnableWakeup : DisableWakeup);

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
BOOLEAN OkayToRemove(PGENERIC_EXTENSION PDX)
{
	if (PDX->MNumberDumpFiles!=0 || PDX->MNumberHibernateFiles!=0 || PDX->MNumberPageFiles!=0)
	{
		return(FALSE);
	}

	if (PDX->MOkayToRemove==NULL)
	{
		return(TRUE);
	}

	return((*PDX->MOkayToRemove)(PDX->MDeviceObject));
}
//-------------------------------------------------------------------------------------------------------
BOOLEAN OkayToStop(PGENERIC_EXTENSION PDX)
{
	if (PDX->MNumberDumpFiles!=0 || PDX->MNumberHibernateFiles!=0 || PDX->MNumberPageFiles!=0)
	{
		return(FALSE);
	}

	if (PDX->MOkayToStop==NULL)
	{
		return(TRUE);
	}

	return((*PDX->MOkayToStop)(PDX->MDeviceObject));
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
_Function_class_(REQUEST_POWER_COMPLETE)
VOID SendDeviceSetPowerComplete(PDEVICE_OBJECT, UCHAR, POWER_STATE, SDSP_CONTEXT* Context, PIO_STATUS_BLOCK PStatus)
{
	Context->MStatus=PStatus->Status;
	KeSetEvent(Context->MPEvent,EVENT_INCREMENT,FALSE);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS SendDeviceSetPower(PGENERIC_EXTENSION PDX, DEVICE_POWER_STATE DevicePower, BOOLEAN Wait/*=FALSE*/)
{
	POWER_STATE													State;

	State.DeviceState=DevicePower;

	NTSTATUS													Status;

	// Synchronous operation.
	if (Wait!=FALSE)
	{
		KEVENT													Event;

		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		SDSP_CONTEXT											Context={&Event};

		Status=PoRequestPowerIrp(PDX->MPDO,IRP_MN_SET_POWER,State,(PREQUEST_POWER_COMPLETE)SendDeviceSetPowerComplete,&Context,NULL);

		if (Status==STATUS_PENDING)
		{
			KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL);
			Status=Context.MStatus;
		}
	}
	else
	{
		Status=PoRequestPowerIrp(PDX->MPDO,IRP_MN_SET_POWER,State,NULL,NULL,NULL);
	}
	
	return(Status);
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
_Function_class_(REQUEST_POWER_COMPLETE)
VOID WaitWakeCallback(PDEVICE_OBJECT, UCHAR, POWER_STATE, PGENERIC_EXTENSION PDX, PIO_STATUS_BLOCK PStatus)
{
	// Indicate that wait-wake is no longer outstanding.
	PDX->MWWOutstanding=0;

	if (NT_SUCCESS(PStatus->Status)==false)
	{
		// IRP failed.
		DbgPrint("%s - IRP_MN_WAIT_WAKE failed - [%X] !\n",PDX->MDebugName,PStatus->Status);
		return;
	}

	// Wakeup our own device. This is necessary if the device signalled a wakeup while the system was already in S0 because, in this case, we won't otherwise get an IRP to power ourselves on.
	SendDeviceSetPower(PDX,PowerDeviceD0,FALSE);
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS WaitWakeCompletionRoutine(PDEVICE_OBJECT, PIRP IRP, PGENERIC_EXTENSION PDX)
{
	if (IRP->PendingReturned!=FALSE)
	{
		IoMarkIrpPending(IRP);
	}

	// Nullify our WaitWakeIrp pointer to prevent anyone from dereferncing the pointer once the IRP gets released as part of the completion process. If it's already NULL, someone has gotten into CancelWaitWake in GenericWakeupControl, meaning we have to avoid a race with IoCancelIRP.
	if (InterlockedExchangePointer((PVOID*) &PDX->MWaitWakeIRP,NULL)!=0)
	{
		// We got here before anyone tried to cancel the IRP.
		return(STATUS_SUCCESS);
	}

	// CancelWaitWake has run. If wwcancelled is nonzero, so has the call to IoCancelIRP and we can allow the IRP to complete. If wwcancelled is still zero (left over from when we launched the IRP), IoCancelIRP hasn't been called yet and we want to interrupt the completion process.
	if (InterlockedExchange(&PDX->MWWCancelled,1)!=0)
	{
		// Allow it to complete.
		return(STATUS_SUCCESS);
	}

	// Let CancelWakeWait complete it.
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS WritePowerInfoToRegistry(PGENERIC_EXTENSION PDX, PPOWERINFO PIP)
{
	HANDLE														HKey;
	NTSTATUS													Status=IoOpenDeviceRegistryKey(PDX->MPDO,PLUGPLAY_REGKEY_DEVICE,KEY_ALL_ACCESS,&HKey);

	if (NT_SUCCESS(Status)==false)
	{
		DbgPrint(DRIVERLOGNAME " - Error [%X] trying to open registry key !\n",Status);

		return(Status);
	}

	UNICODE_STRING												ValueName;

	RtlInitUnicodeString(&ValueName,L"PowerSettings");

	Status=ZwSetValueKey(HKey,&ValueName,0,REG_BINARY,PIP,2*sizeof(ULONG));

	if (NT_SUCCESS(Status)==false)
	{
		DbgPrint(DRIVERLOGNAME " - ZwSetValueKey failed - [%X] !\n",Status);
	}

	ZwClose(HKey);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS MainCompletionRoutine(PDEVICE_OBJECT Junk, PIRP IRP, PPOWCONTEXT Context);
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS SequenceCompletionRoutine(PDEVICE_OBJECT Junk, PIRP IRP, PPOWCONTEXT Context);
_Function_class_(REQUEST_POWER_COMPLETE)
VOID PoCompletionRoutine(PDEVICE_OBJECT Junk, UCHAR Function, POWER_STATE State, PPOWCONTEXT Context, PIO_STATUS_BLOCK PStatus);
//-------------------------------------------------------------------------------------------------------
VOID PassivePowerComplete(PPOWCONTEXT Context)
{
	HandlePowerEvent(Context,AsyncNotify);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS HandlePowerEvent(PPOWCONTEXT Context, enum POWEVENT Event)
{
	// An invalid value.
	NTSTATUS													Status=-1;

	ASSERT(Context);
	ASSERT((ULONG) Event<NUMPOWEVENTS);

	// Could be null if we did an early S0 completion.
	PIRP														IRP=Context->MIRP;
	PIO_STACK_LOCATION											Stack=(IRP!=NULL) ? IoGetCurrentIrpStackLocation(IRP) : NULL;
	PGENERIC_EXTENSION											PDX=Context->MPDX;

	enum POWACTION
	{
		// Code for invalid state/event combinations.
		InvalidAction,
		// Decide what to do with new IRP.
		TriageNewIRP,
		// Device queue has been stalled.
		QueueStallComplete,
		// Begin system or device IRP for more power.
		ForwardMainIRP,
		// System power-up IRP completed.
		SystemPowerUpComplete,
		// System power-down IRP completed.
		SystemPowerDownComplete,
		// Choose D-state corresponding to main IRP's S-state.
		SelectDState,
		// Send device IRP.
		SendDeviceIRP,
		// Complete the main IRP.
		CompleteMainIRP,
		// Terminate FSM.
		DestroyContext,
		// Nested power-up IRP finished or failed.
		SubPowerUpComplete,
		// Nested power-down IRP finished or failed.
		SubPowerDownComplete,
		// Device power-up IRP has completed.
		DevicePowerUpComplete,
		// Save context in preparation for powering down.
		SaveContext,
		// Device context has been saved.
		ContextSaveComplete,
		// Device context has been restored.
		ContextRestoreComplete,
		// Device query for power-up complete.
		DeviceQueryUpComplete,
		// See if device can power down.
		DeviceQueryDown,
		// Device query for power-down complete.
		DeviceQueryDownComplete,
		// Create and send POWER_SEQUENCE request.
		SendPowerSequence,
		// Sequence fetch after context save complete.
		SaveSequenceComplete,
		// Forward device set-power down IRP.
		ForwardDeviceDown,
		// Sequence fetch before context save complete.
		RestoreSequenceComplete,
		// Restore device context.
		RestoreContext,
	};

	static char*												PowerStateNames[]=
	{
		"InitialState",
		"SysPowerUpPending",
		"SubPowerUpPending",
		"SubPowerDownPending",
		"SystemPowerDownPending",
		"DevicePowerUpPending",
		"DevicePowerDownPending",
		"ContextSavePending",
		"ContextRestorePending",
		"DeviceQueryUpPending",
		"DeviceQueryDownPending",
		"QueueStallPending",
		"SaveSequencePending",
		"RestoreSequencePending",
		"PassiveCompletePending",
		"FinalState",
	};

	static char*												EventNames[]=
	{
		"NewIRP",
		"MainIRPComplete",
		"AsyncNotify",
	};

	static char*												ActionNames[]=
	{
		"InvalidAction",
		"TriageNewIRP",
		"QueueStallComplete",
		"ForwardMainIRP",
		"SystemPowerUpComplete",
		"SystemPowerDownComplete",
		"SelectDState",
		"SendDeviceIRP",
		"CompleteMainIRP",
		"DestroyContext",
		"SubPowerUpComplete",
		"SubPowerDownComplete",
		"DevicePowerUpComplete",
		"SaveContext",
		"ContextSaveComplete",
		"ContextRestoreComplete",
		"DeviceQueryUpComplete",
		"DeviceQueryDown",
		"DeviceQueryDownComplete",
		"SendPowerSequence",
		"SaveSequenceComplete",
		"ForwardDeviceDown",
		"RestoreSequenceComplete",
		"RestoreContext",
	};

	static enum POWACTION										ActionTable[NUMPOWSTATES][NUMPOWEVENTS]=
	{
		//							NewIRP.				MainIRPComplete.			AsyncNotify.
		/*InitialState.*/			{TriageNewIRP,		InvalidAction,				InvalidAction},
		/*SysPowerUpPending.*/		{InvalidAction,		SystemPowerUpComplete,		InvalidAction},
		/*SubPowerUpPending.*/		{InvalidAction,		InvalidAction,				SubPowerUpComplete},
		/*SubPowerDownPending.*/	{InvalidAction,		InvalidAction,				SubPowerDownComplete},
		/*SysPowerDownPending.*/	{InvalidAction,		SystemPowerDownComplete,	InvalidAction},
		/*DevicePowerUpPending.*/	{InvalidAction,		DevicePowerUpComplete,		InvalidAction},
		/*DevicePowerDownPending.*/	{InvalidAction,		CompleteMainIRP,			InvalidAction},
		/*ContextSavePending.*/		{InvalidAction,		InvalidAction,				ContextSaveComplete},
		/*ContextRestorePending.*/	{InvalidAction,		InvalidAction,				ContextRestoreComplete},
		/*DeviceQueryUpPending.*/	{InvalidAction,		DeviceQueryUpComplete,		InvalidAction},
		/*DeviceQueryDownPending.*/	{InvalidAction,		DeviceQueryDownComplete,	InvalidAction},
		/*QueueStallPending.*/		{InvalidAction,		InvalidAction,				QueueStallComplete},
		/*SaveSequencePending.*/	{InvalidAction,		InvalidAction,				SaveSequenceComplete},
		/*RestoreSequencePending.*/	{InvalidAction,		InvalidAction,				RestoreSequenceComplete},
		/*PassiveCompletePending.*/	{InvalidAction,		InvalidAction,				CompleteMainIRP},
		/*FinalState.*/				{InvalidAction,		InvalidAction,				InvalidAction},
	};

	// Determine the first action to take based on the current state of the FSM and the event that occurred. Note that this isn't as complicated as the use of 2-D array might suggest: all states except the initial state lead to a single action for the one-and-only event that's possible to get in that state.
	enum POWACTION												Action=ActionTable[Context->MState][Event];

	// Structurally, the following code is a switch on "action" imbedded within an infinite loop. A case that does a "break" from the switch executes a "break" from the loop, whereupon we return whatever value is left in "status". A case that does a "continue" from the switch repeats the loop -- this is how actions can be strung together during one call to this routine. I coded it this way to avoid return statements in the middle that make it harder to prove that the routine behaves in a predictable way. Note that any "break" should be preceded by a change to the state recorded in the context structure and to the initially invalid valid of "status". There are ASSERTs at the end to check this.
	// Concerning the required change to "Context->MState": there are many cases where we call PoRequestPowerIRP or PoCallDriver, whereupon the context structure gets released before those routines return. We use a SETSTATE macro so we don't have to dereference a possibly invalid "Context" pointer at the end of the loop. Any action that calls a routine that might result in completing the current IRP should also take care not to touch "Context" afterwards. (These are always cases that "break" from the switch, so you can just verify that the break always immediately follows the PoXxx call.)
	// Concerning the required change to "status": only TriageNewIRP will arrange to return STATUS_PENDING. Many of the other initial actions are entered from a standard I/O completion routine and will need to return STATUS_MORE_PROCESSING_REQUIRED to hold off final completion. Any action for MainIRPComplete that goes out through CompleteMainIRP will end up returning Context->MStatus, which gets set in MainCompletionRoutine() to whatever's in the IRP -- this allows the IRP to complete normally. Any action off of AsyncNotify should be changing "status" explicitly (and they do -- I checked).
	// Note: Avoid doing ASSERTs in this code because they're basically impossible to debug. (Usually, the display is turned off before anything else, and then the serial port. So the debugger is usually deaf and dumb when something goes wrong here.)

	enum POWSTATE												OriginalState=Context->MState;
	enum POWSTATE												NextState=OriginalState;

	#define SETSTATE(S) Context->MState=NextState=S

	LONG														EventID=InterlockedIncrement(&Context->MEventCount);
	LONG														ContextID=Context->MID;

	DbgPrint("%s - [%d.%d] is [%s] in state [%s] !\n",PDX->MDebugName,ContextID,EventID,EventNames[Event],PowerStateNames[OriginalState]);

	for(;;)
	{
		// Handle this event.
		DbgPrint("%s -  [%d.%d] [%s] !\n",PDX->MDebugName,ContextID,EventID,ActionNames[Action]);

		switch(Action)
		{
			// Perform next action.
			// TriageNewIRP is the first action for a newly receive query or set IRP.
			case TriageNewIRP:
			{
				// We want the power dispatch routine to return STATUS_PENDING unless something goes wrong right away. If we do return STATUS_PENDING, we need to be sure we mark the IRP pending.
				Status=STATUS_PENDING;

				if (IRP!=NULL)
				{
					IoMarkIrpPending(IRP);
				}

				// Acquire remove lock an extra time. We'll release it when we eventually complete this IRP.
				if (PDX->MRemoveLock!=NULL)
				{
					IoAcquireRemoveLock(PDX->MRemoveLock,IRP);
				}

				if (Stack!=NULL)
				{
					// For a system IRP, we'll request the corresponding device IRP. If system power is being restored, we wait until the lower level drivers finish the system IRP. If system power is being removed, we do it now and forward the system IRP when the device IRP finishes.
					if (Stack->Parameters.Power.Type==SystemPowerState)
					{
						// System IRP.
						if (Stack->Parameters.Power.State.SystemState<PDX->MSystemPower)
						{
							Action=ForwardMainIRP;
							SETSTATE(SysPowerUpPending);
						}
						else
						{
							Action=SelectDState;
							SETSTATE(SubPowerDownPending);
						}
					}
					else
					{
						// For a device set-power IRP, we have a variety of tasks to carry out. If device power is being restored, we do those tasks when the lower level drivers complete the IRP. If device power is being removed or staying the same, we do those tasks before passing this IRP down. In either case, we ensure that the device isn't busy with any substantive IRPs first.
						SETSTATE(QueueStallPending);

						DEVICE_POWER_STATE						NewState=Stack->Parameters.Power.State.DeviceState;

						// Conceivably, we could cancel any outstanding wait-wake when going to a D-state that doesn't support wakeup. In practice, the bus driver will do this for us.
						// According to the DDK, we're supposed to call PoSetPowerState any time we change the power state, *before* calling PoStartNextPowerIrp and at IRQL<DISPATCH_LEVEL (except=DISPATCH_LEVEL is okay for D0). In fact, it seems to make no difference whether we do this or not, and bus drivers seem to make all the necessary calls. Therefore, don't bother.
						// If the device is currently sleeping or off, the queue should already be stalled. If the device is in D0, however, it might be servicing a request right now, and there might be requests queued up behind the active one. StallRequestsAndNotify will stall the queue and establish a callback for when the client driver calls StartNextPacket.
						if (PDX->MNumberQueues!=0 && PDX->MStalledForPower==FALSE)
						{
							// Stall request queue.
							// We mustn't touch the context structure after calling a function that might recursively invoke this routine.
							Context->MUnstallQueue=TRUE;
							PDX->MStalledForPower=TRUE;

							UCHAR								Minor=Stack->MinorFunction;
							DEVICE_POWER_STATE					OldState=PDX->MDevicePower;
							NTSTATUS							QStatus=StallAllRequestsAndNotify(PDX->MQueues,PDX->MNumberQueues,GenericSaveRestoreComplete,Context);

							if (NT_SUCCESS(QStatus)==false)
							{
								// Can't stall queue.
								Context->MStatus=QStatus;
								Action=CompleteMainIRP;
								Context->MUnstallQueue=FALSE;
								PDX->MStalledForPower=FALSE;
								continue;
							}

							// The UnstallQueue flag tells CompleteMainIRP to unstall the queue as part of the cleanup process. We may clear this flag somewhere along the way in order to keep the queue stalled during a period of low power.
							DbgPrint("%s -  [%d.%d] stalling queue !\n",PDX->MDebugName,ContextID,EventID);

							if (QStatus==STATUS_PENDING)
							{
								// Wait for notification that device is idle.
								if (PDX->MFlushPendingIO!=NULL)
								{
									(*PDX->MFlushPendingIO)(PDX->MDeviceObject,IRP_MJ_POWER,Minor,OldState,NewState);
								}

								break;
							}
						}

						Action=QueueStallComplete;
					}
				}

				continue;
			}
			
			// QueueStallComplete is the action for an AsyncNotify event in the QueueStallPending state. It's reached when StartNextPacket calls GenericSaveRestoreComplete, which we specified as the current-IRP complete notification routine in our earlier call to StallRequestsAndNotify. This action can also be reached directly from TriageNewIRP if the device was idle to begin with or if we were already in a low-power state (so that the queue should have been stalled).
			case QueueStallComplete:
			{
				if (Stack!=NULL)
				{
					if (Stack->MinorFunction==IRP_MN_SET_POWER)
					{
						// Device set-power IRP.
						if (Stack->Parameters.Power.State.DeviceState<PDX->MDevicePower)
						{
							Action=ForwardMainIRP;
							SETSTATE(DevPowerUpPending);
						}
						else
						{
							Action=SaveContext;
						}
					}
					else
					{
						// Device query-power IRP.
						if (Stack->Parameters.Power.State.DeviceState<PDX->MDevicePower)
						{
							Action=ForwardMainIRP;
							SETSTATE(DevQueryUpPending);
						}
						else
						{
							Action=DeviceQueryDown;
						}
					}
				}

				continue;
			}
			
			// ForwardMainIRP sends the current power IRP to the next driver in the stack. We regain control in MainCompletionRoutine.
			case ForwardMainIRP:
			{
				if (IRP!=NULL)
				{
					IoCopyCurrentIrpStackLocationToNext(IRP);

					IoSetCompletionRoutine(IRP,(PIO_COMPLETION_ROUTINE) MainCompletionRoutine,(PVOID) Context,TRUE,TRUE,TRUE);
				
					IoCallDriver(PDX->MLowerDeviceObject,IRP);
				}

				break;
			}

			// SysPowerUpComplete is the action for a MainIRPComplete event in the SysPowerUpPending state. If the IRP succeeded, request the corresponding D-state IRP. When the subsidiary IRP finishes, we'll complete this S-state IRP as well.
			// The DDK doesn't explicitly say you need to send a D-state query when you get an S-state query. It simplifies our own logic a good deal to do this, however.
			case SystemPowerUpComplete:
			{
				if (NT_SUCCESS(Context->MStatus)==false)
				{
					Action=CompleteMainIRP;
				}
				else
				{
					// S-IRP succeeded.
					Action=SelectDState;
					SETSTATE(SubPowerUpPending);

					// Defer completion of S-IRP.
					Status=STATUS_MORE_PROCESSING_REQUIRED;

					if (Stack!=NULL)
					{
						if (Stack->MinorFunction==IRP_MN_SET_POWER)
						{
							// S-set.
							PDX->MSystemPower=Stack->Parameters.Power.State.SystemState;
					
							// Except in 98/Me, complete an S0 IRP right away to allow faster restart after suspend.
							if (PDX->MSystemPower==PowerSystemWorking)
							{
								// S0.
								DbgPrint("%s - [%d.%d] Completing S0 IRP early !\n",PDX->MDebugName,ContextID,EventID);

								if (IRP!=NULL)
								{
									PoStartNextPowerIrp(IRP);
								}

								// Allows S-IRP to complete.
								Status=STATUS_SUCCESS;

								if (PDX->MRemoveLock!=NULL)
								{
									IoReleaseRemoveLock(PDX->MRemoveLock,IRP);
								}

								// Flag for eventual CompleteMainIRP step.
								Context->MIRP=NULL;
							}
						}
					}
				}

				continue;
			}

			// SystemPowerDownComplete is the action for a MainIrpComplete event in the SysPowerDownPending state.
			case SystemPowerDownComplete:
			{
				if (NT_SUCCESS(Context->MStatus)==false)
				{
					DbgPrint("%s - System power-down IRP failed - [%X] !\n",PDX->MDebugName,Context->MStatus);
				}

				if (Stack!=NULL)
				{
					if (Stack->MinorFunction==IRP_MN_SET_POWER)
					{
						// Note that this IRP could not legally have been failed.
						PDX->MSystemPower=Stack->Parameters.Power.State.SystemState;
					}
				}

				Action=CompleteMainIRP;
				continue;
			}

			// SelectDState is used to establish the power state and minor function code for a D-state IRP that corresponds to the S-state IRP we're processing. After doing that, we do the SendDeviceIRP action.
			case SelectDState:
			{
				if (Stack!=NULL)
				{
					SYSTEM_POWER_STATE							SState=Stack->Parameters.Power.State.SystemState;

					Context->MDeviceState=GetLowestDevicePowerState(PDX,SState);
					Context->MMinorFunction=Stack->MinorFunction;
					Action=SendDeviceIRP;
				}

				continue;
			}

			// SendDeviceIRP requests a device set- or query-power IRP using the power state and minor function code currently in the context block. SelectDState put them there.
			case SendDeviceIRP:
			{
				// If we want the device in the same state it's already in, bypass sending the D-state IRP. This is necessary in Win98 due to a bug that causes PoRequestPowerIRP to report success in a situation where CONFIGMG won't generate the configuration event. This has also turned out to be necessary when bringing Win2K/Xp out of standby or hibernate, although I don't exactly understand why.
				if (Context->MDeviceState==PDX->MDevicePower)
				{
					// Pretend success.
					DbgPrint("%s - [%d.%d] pretending to succeed D-state IRP for same state !\n",PDX->MDebugName,ContextID,EventID);
					Context->MStatus=STATUS_SUCCESS;
					Action=ActionTable[Context->MState][AsyncNotify];
					continue;
				}

				// Ask the power manager to send us an IRP. In Win98, we need to supply the PDO as the device object address because NTKERN needs to go directly from there to the devnode address.
				POWER_STATE										PowerState;

				PowerState.DeviceState=Context->MDeviceState;

				NTSTATUS										PoStatus=PoRequestPowerIrp(PDX->MPDO,Context->MMinorFunction,PowerState,(PREQUEST_POWER_COMPLETE) PoCompletionRoutine,Context,NULL);

				// If PoRequestPowerIRP fails, it never actually sent an IRP down the stack, so we can certain that PoCompletionRoutine never ran.
				if (NT_SUCCESS(PoStatus)==true)
				{
					// Started device IRP okay.
					break;
				}

				DbgPrint("PoRequestPowerIRP failed - [%X] !\n",PoStatus);
				Action=CompleteMainIRP;
				Context->MStatus=PoStatus;
				continue;
			}

			// CompleteMainIRP is the penultimate action of the finite state machine. This is where we actually complete the power IRP we've been handling.
			case CompleteMainIRP:
			{
				// Skip completion processing if we've already completed an S0 SET_POWER. Otherwise, complete (or allow to complete) the main IRP.
				if (IRP!=NULL)
				{
					// Not previously completed.
					// Tell the power manager to release the next IRP of the same flavor as we're currently processing.
					PoStartNextPowerIrp(IRP);

					// If called from MainCompletionRoutine, just allow the completion process to take its course. Otherwise, explicitly complete the main IRP.
					if (Event==MainIRPComplete)
					{
						// Might have been STATUS_MORE_PROCESSING_REQUIRED until now.
						Status=Context->MStatus;
					}
					else
					{
						IRP->IoStatus.Status=Context->MStatus;
						IoCompleteRequest(IRP,IO_NO_INCREMENT);
					
						if (Status==-1)
						{
							Status=STATUS_SUCCESS;
						}
					}

					// Release the remove lock to balance the extra acquisition in TriageNewIRP.
					if (PDX->MRemoveLock!=NULL)
					{
						IoReleaseRemoveLock(PDX->MRemoveLock,IRP);
					}
				}

				// If we stalled the request queue for the pendency of this IRP, unstall it now. Sometimes, we will have cleared the flag in order to leave the queue stalled after completing a power-down.
				if (Context->MUnstallQueue!=FALSE)
				{
					PDX->MStalledForPower=FALSE;
					DbgPrint("%s - [%d.%d] unstalling queue !\n",PDX->MDebugName,ContextID,EventID);
					RestartAllRequests(PDX->MQueues,PDX->MNumberQueues,PDX->MDeviceObject);
				}
			
				Action=DestroyContext;
				continue;
			}

			// DestroyContext is the last action for an IRP.
			case DestroyContext:
			{
				SETSTATE(FinalState);
				ExFreePool(Context);
				break;
			}

			// SubPowerUpComplete is the action for a AsyncNotify event in the SubPowerUpPending state. This should be called from PoCompletionRoutine. We can also get here from SendDeviceIRP to avoid the Win98 no-D-IRP bug, in which case we don't want to alter "status" from its current value.
			case SubPowerUpComplete:
			{
				if (Status==-1)
				{
					// Don't actually care, since called from PoCompletionRoutine.
					Status=STATUS_SUCCESS;
				}
			
				Action=CompleteMainIRP;
				continue;
			}

			// SubPowerDownComplete is the action for a AsyncNotify event in the SubPowerDownPending state. This should be called from PoCompletionRoutine. We can also get here from SendDeviceIRP to avoid the Win98 no-D-IRP bug, in which case we don't want to alter "status" from its current value.
			case SubPowerDownComplete:
			{
				if (Status==-1)
				{
					// Don't actually care, since called from PoCompletionRoutine.
					Status=STATUS_SUCCESS;
				}

				if (NT_SUCCESS(Context->MStatus)==true)
				{
					SETSTATE(SysPowerDownPending);
					Action=ForwardMainIRP;
				}
				else
				{
					// D-state IRP failed, so fail S-state IRP too.
					Action=CompleteMainIRP;
				}
			
				continue;
			}

			// DevPowerUpComplete is the action for a MainIrpComplete event in the DevPowerUpPending state. This should be called from MainCompletionRoutine when a device power-up IRP finishes in the lower layers.
			case DevicePowerUpComplete:
			{
				if (Stack!=NULL)
				{
					// If this IRP failed, or if we're just dealing with a query, we're done.
					if (NT_SUCCESS(Context->MStatus)==false || Stack->MinorFunction!=IRP_MN_SET_POWER)
					{
						Action=CompleteMainIRP;
						continue;
					}

					// Defer completion of the main IRP while we restore context.
					Status=STATUS_MORE_PROCESSING_REQUIRED;

					Context->MOldPower=PDX->MDevicePower;
					PDX->MDevicePower=Stack->Parameters.Power.State.DeviceState;

					DbgPrint("%s - Now in [%s] !\n",PDX->MDebugName,DeviceState[PDX->MDevicePower]);

					// Since no bus driver currently implements IRP_MN_POWER_SEQUENCE, you don't really need to bother with it. But doing it correctly is enough of a pain in the neck that it's worthwhile showing you how to do it just in case it ever becomes relevant. I thought this was marginal enough that I didn't discuss the extra states in the book, though. In the book, I showed this action as including the stuff that's in RestoreContext, too. [SP-10: don't do this unless PerfBoundary is nonzero. The comment in Generic.h says that leaving it zero will suppress the IRP, and a reader reported a problem with PCMCIA.SYS barfing on one of them.]
					if (PDX->MPerfBoundary!=0 && Context->MOldPower>=PDX->MPerfBoundary)
					{
						// Context restore will be expensive.
						SETSTATE(RestoreSeqPending);
						Action=SendPowerSequence;
						continue;
					}

					Action=RestoreContext;
				}

				continue;
			}

			// ContextRestoreComplete is the last action for a device set power up operation. It's ordinarily reached when GenericSaveRestoreComplete signals a MainIRPComplete event from the ContextRestorePending state. It can also be reached directly from DevPowerUpComplete when there is no context restore function.
			case ContextRestoreComplete:
			{
				if (Event==AsyncNotify)
				{
					// Doesn't actually matter.
					Status=STATUS_SUCCESS;
				}

				Action=CompleteMainIRP;

				// If the device IRP failed, just go ahead and let it complete. If we've successfully resumed to a sleeping state (> D0), skip restarting the substantive IRP queue and complete the IRP as well.
				if (NT_SUCCESS(Context->MStatus)==false || PDX->MDevicePower!=PowerDeviceD0)
				{
					continue;
				}

				// We've just gone to D0, unstall the request queue by setting the flag that will cause CompleteMainIRP to do so. It's very important in our scheme that we stall the queue for any device IRP that arrives while we're in D0 and omit to unstall it when we complete a SET for a lower power state. We thereby arrange to stall the queue just once across an entire period of low power.
				if (PDX->MNumberQueues!=0)
				{
					Context->MUnstallQueue=TRUE;
				}

				continue;
			}

			// SaveContext initiates a context save operation if necessary. This will be the second action for a new device set-power IRP.
			case SaveContext:
			{
				if (Stack!=NULL)
				{
					DEVICE_POWER_STATE							DevicePower=Stack->Parameters.Power.State.DeviceState;

					// If we're actually changing to a lower power state, give the client driver a chance to save any device context information asynchronously. It will call GenericSaveRestoreComplete when it finishes.
					if (PDX->MSaveDeviceContext!=NULL && DevicePower>PDX->MDevicePower)
					{
						// Save context.
						SETSTATE(ContextSavePending);
						(*PDX->MSaveDeviceContext)(PDX->MDeviceObject,PDX->MDevicePower,DevicePower,Context);
						break;
					}

					Action=ContextSaveComplete;
				}

				continue;
			}

			// ContextSaveComplete is the action for an AsyncNotify event in the ContextSavePending state. It should be entered from GenericSaveRestoreComplete, which in turn should have been called by the client driver when its context save operation finished. It can also be entered directly from SaveContext when there is no context save routine.
			case ContextSaveComplete:
			{
				if (Event==AsyncNotify)
				{
					// Doesn't actually matter in this case.
					Status=STATUS_SUCCESS;
				}

				if (Stack!=NULL)
				{
					// Obtain a set of power-state sequence numbers to optimize state restoration later. In the book, I didn't include this bit of nonsense. The code in ForwardDevDown appears right here in the book. [SP-10: See note elsewhere.]
					if (PDX->MPerfBoundary!=0 && Stack->Parameters.Power.State.DeviceState>=PDX->MPerfBoundary)
					{
						// Context restore will be expensive.
						SETSTATE(SaveSeqPending);
						Action=SendPowerSequence;
						continue;
					}

					Action=ForwardDeviceDown;
				}

				continue;
			}

			// DevQueryUpComplete is the action for a MainIrpComplete event in the DevQueryUpPending state. This should be called by MainCompletionRoutine when a device query-power-up IRP completes. We don't expect to ever get this kind of a query, by the way, but we should handle it nontheless.
			case DeviceQueryUpComplete:
			{
				if (Stack!=NULL)
				{
					if (NT_SUCCESS(Context->MStatus)==true && PDX->MQueryPower!=NULL)
					{
						// Ask client if change okay.
						// Everybody belows us has acquiesced in restoring power. Ask the client driver if it's cool by this too.
						if (((*PDX->MQueryPower)(PDX->MDeviceObject,PDX->MDevicePower,Stack->Parameters.Power.State.DeviceState))==FALSE)
						{
							// Fail the query.
							Context->MStatus=STATUS_UNSUCCESSFUL;
						}
					}

					Action=CompleteMainIRP;
				}

				continue;
			}

			// DevQueryDown is the second action (after TriageNewIRP) for a device query-power that specifies less than or equal to the current device power state.
			case DeviceQueryDown:
			{
				if (Stack!=NULL)
				{
					DEVICE_POWER_STATE							DevicePower=Stack->Parameters.Power.State.DeviceState;

					// If the proposed power state is less than the current state, ask the client driver if it's okay to change.
					if (DevicePower>PDX->MDevicePower && PDX->MQueryPower!=NULL && ((*PDX->MQueryPower)(PDX->MDeviceObject,PDX->MDevicePower,DevicePower))==FALSE)
					{
						// Fail the query.
						Context->MStatus=STATUS_UNSUCCESSFUL;
						Action=DeviceQueryDownComplete;
						continue;
					}

					SETSTATE(DevQueryDownPending);
					Action=ForwardMainIRP;
				}

				continue;
			}

			// DevQueryDownComplete is the action for a MainIrpComplete event in the DevQueryDownPending state. It can be reached from MainCompletionRoutine or directly from DevQueryDown.
			case DeviceQueryDownComplete:
			{
				// The Windows 98 version of the USB hub driver fails device power query operations, which is incorrect.
				if (Context->MStatus==STATUS_INVALID_PARAMETER)
				{
					Context->MStatus=STATUS_SUCCESS;
				}

				// If the query is succeeding, leave the request queue stalled.
				if (NT_SUCCESS(Context->MStatus)==true)
				{
					Context->MUnstallQueue=FALSE;
				}

				Action=CompleteMainIRP;
				continue;
			}

			// SendPowerSequence creates an IRP_MN_POWER_SEQUENCE request. It can be entered from DevPowerUpComplete or ContextSaveComplete
			case SendPowerSequence:
			{
				PIRP											SequenceIRP=IoAllocateIrp(PDX->MLowerDeviceObject->StackSize,FALSE);

				if (SequenceIRP!=NULL)
				{
					// Sequence IRP created.
					PIO_STACK_LOCATION							SequenceStack=IoGetNextIrpStackLocation(SequenceIRP);
				
					SequenceStack->MajorFunction=IRP_MJ_POWER;
					SequenceStack->MinorFunction=IRP_MN_POWER_SEQUENCE;
					SequenceStack->Parameters.PowerSequence.PowerSequence=&Context->MSequence;

					IoSetCompletionRoutine(SequenceIRP,(PIO_COMPLETION_ROUTINE) SequenceCompletionRoutine,(PVOID) Context,TRUE,TRUE,TRUE);

					IoCallDriver(PDX->MLowerDeviceObject,SequenceIRP);
					break;
				}
				else
				{
					// Couldn't create IRP.
					if (Context->MState==SaveSeqPending)
					{
						Action=ForwardDeviceDown;
					}
					else
					{
						Action=RestoreContext;
					}

					continue;
				}
			}

			// SaveSequenceComplete is the action for an AsyncNotify event in the SaveSequencePending state. It should be entered from SequenceCompletionRoutine when an IRP_MN_POWER_SEQUENCE request completes.
			case SaveSequenceComplete:
			{
				if (NT_SUCCESS(Context->MStatus)==true)
				{
					DbgPrint("%s - Someone actually succeeded a POWER_SEQUENCE request !\n",PDX->MDebugName);

					// Save sequence numbers for power-up.
					PDX->MOldSequence=Context->MSequence;
				}
				else
				{
					RtlZeroMemory(&PDX->MOldSequence,sizeof(PDX->MOldSequence));
				}

				// Won't actually be used.
				Status=STATUS_MORE_PROCESSING_REQUIRED;

				// Status from POWER_SEQUENCE not actually relevant.
				Context->MStatus=STATUS_SUCCESS;

				Action=ForwardDeviceDown;
				continue;
			}

			// ForwardDeviceDown forwards a device set-power down IRP. It can be reached from SaveSequenceComplete or from ContextSaveComplete.
			case ForwardDeviceDown:
			{
				SETSTATE(DevPowerDownPending);
				Action=ForwardMainIRP;

				if (Stack!=NULL)
				{
					DEVICE_POWER_STATE							DevicePower=Stack->Parameters.Power.State.DeviceState;

					if (DevicePower<=PDX->MDevicePower)
					{
						// No actual change in device power.
						continue;
					}

					PDX->MDevicePower=DevicePower;

					DbgPrint("%s - Now in [%s] !\n",PDX->MDebugName,DeviceState[PDX->MDevicePower]);

					// If power has now been removed, leave the queue stalled.
					if (DevicePower>PowerDeviceD0)
					{
						Context->MUnstallQueue=FALSE;
					}
				}

				continue;
			}

			// RestoreSequenceComplete is the action for an AsyncNotify event in the RestoreSequencePending state. It should be entered from SequenceCompletionRoutine when an IRP_MN_POWER_SEQUENCE request completes.
			case RestoreSequenceComplete:
			{
				// Now decide if we really need to restore the device context by comparing the sequence numbers for the performance boundary state.
				// Assume we'll want to restore context.
				Action=RestoreContext;

				if (NT_SUCCESS(Context->MStatus)==true)
				{
					switch (PDX->MPerfBoundary)
					{
						// Check relevant sequence numbers.
						case PowerDeviceD1:
						{
							if (Context->MSequence.SequenceD1<=PDX->MOldSequence.SequenceD1)
							{
								Action=ContextRestoreComplete;
							}
						}
						break;
					
						case PowerDeviceD2:
						{
							if (Context->MSequence.SequenceD2<=PDX->MOldSequence.SequenceD2)
							{
								Action=ContextRestoreComplete;
							}
						}
						break;
					
						case PowerDeviceD3:
						{
							if (Context->MSequence.SequenceD3<=PDX->MOldSequence.SequenceD3)
							{
								Action=ContextRestoreComplete;
							}
						}
						break;
					}
				}

				if (Action!=RestoreContext)
				{
					DbgPrint("%s - Bypassing context restore due to sequence number optimization !\n",PDX->MDebugName);
				}

				// Ignore status from POWER_SEQUENCE.
				Context->MStatus=STATUS_SUCCESS;
				Status=STATUS_MORE_PROCESSING_REQUIRED;
				continue;
			}

			// RestoreContext restores device context if necessary. It can be entered from RestoreSequenceComplete or from DevicePowerUpComplete.
			case RestoreContext:
			{
				// Allow the client driver to restore any device context. This occurs asynchronously. The client notifies us when the the restore operation finishes by calling GenericSaveRestoreComplete.
				if (PDX->MRestoreDeviceContext!=NULL)
				{
					// Restore context.
					SETSTATE(ContextRestorePending);
					(*PDX->MRestoreDeviceContext)(PDX->MDeviceObject,Context->MOldPower,PDX->MDevicePower,Context);
					break;
				}

				Action=ContextRestoreComplete;
				continue;
			}

			// InvalidAction is the action for any unexpected event. It should never occur.
			case InvalidAction:
			default:
			{
				Status=STATUS_UNSUCCESSFUL;
				break;
			}
		}

		break;
	}

	// Check to make sure the state got changed before we exit.
	if (NextState==OriginalState)
	{
		DbgPrint("%s - State didn't change from [%d] in HandlePowerEvent !\n",PDX->MDebugName,OriginalState);
	}

	// Check to make sure a valid status will be returned.
	if (Status==-1)
	{
		DbgPrint("%s - returned status didn't change in HandlePowerEvent !\n",PDX->MDebugName);
	}

	DbgPrint("%s - [%d.%d] returning [%X], state is [%s] !\n",PDX->MDebugName,ContextID,EventID,Status,PowerStateNames[NextState]);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS MainCompletionRoutine(PDEVICE_OBJECT, PIRP IRP, PPOWCONTEXT Context)
{
	Context->MStatus=IRP->IoStatus.Status;

	return(HandlePowerEvent(Context,MainIRPComplete));
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS SequenceCompletionRoutine(PDEVICE_OBJECT, PIRP IRP, PPOWCONTEXT Context)
{
	Context->MStatus=IRP->IoStatus.Status;
	HandlePowerEvent(Context,AsyncNotify);
	IoFreeIrp(IRP);

	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(REQUEST_POWER_COMPLETE)
VOID PoCompletionRoutine(PDEVICE_OBJECT, UCHAR, POWER_STATE, PPOWCONTEXT Context, PIO_STATUS_BLOCK PStatus)
{
	Context->MStatus=PStatus->Status;
	HandlePowerEvent(Context,AsyncNotify);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(WORKER_THREAD_ROUTINE)
VOID PassivePowerCall(PIRP IRP)
{
	IoCallDriver(IoGetNextIrpStackLocation(IRP)->DeviceObject,IRP);
}
//-------------------------------------------------------------------------------------------------------