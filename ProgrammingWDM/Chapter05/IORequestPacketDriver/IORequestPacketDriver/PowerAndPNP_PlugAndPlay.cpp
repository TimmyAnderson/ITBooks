//-------------------------------------------------------------------------------------------------------
#include <wdm.h>
#include "Macros.h"
#include "PowerAndPNP_Structures.h"
//-------------------------------------------------------------------------------------------------------
NTSTATUS DefaultPnpHandler(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleCancelRemove(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleCancelStop(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleQueryCapabilities(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleQueryRemove(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleQueryState(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleQueryStop(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleRemoveDevice(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleStartDevice(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleStopDevice(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleSurpriseRemoval(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleUsageNotification(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS HandleFilterResourceRequirements(PGENERIC_EXTENSION PDX, PIRP IRP);
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS OnNotificationComplete(PDEVICE_OBJECT FDO, PIRP IRP, PGENERIC_EXTENSION PDX);
VOID AdjustDeviceCapabilities(PDEVICE_CAPABILITIES PDC);
VOID AdjustWakeCapabilities(PGENERIC_EXTENSION PDX, PDEVICE_CAPABILITIES PDC, DEVICE_POWER_STATE DeviceState);
VOID DeregisterInterface(PGENERIC_EXTENSION PDX, PINTERFACE_RECORD IFP);
VOID DeregisterAllInterfaces(PGENERIC_EXTENSION PDX);
VOID EnableAllInterfaces(PGENERIC_EXTENSION PDX, BOOLEAN Enable);
PINTERFACE_RECORD FindInterfaceRecord(PGENERIC_EXTENSION PDX, const GUID* GUID);
VOID CallStopDevice(PGENERIC_EXTENSION PDX);
VOID CallRemoveDevice(PGENERIC_EXTENSION PDX);
//-------------------------------------------------------------------------------------------------------
VOID ShowResources(IN PCM_PARTIAL_RESOURCE_LIST List);
//-------------------------------------------------------------------------------------------------------
static char*													StateNames[]=
{
	"STOPPED",
	"WORKING",
	"PENDINGSTOP",
	"PENDINGREMOVE",
	"SURPRISEREMOVED",
	"REMOVED",
};
//-------------------------------------------------------------------------------------------------------
static char*													SName[]=
{
	"PowerSystemUnspecified",
	"PowerSystemWorking",
	"PowerSystemSleeping1",
	"PowerSystemSleeping2",
	"PowerSystemSleeping3",
	"PowerSystemHibernate",
	"PowerSystemShutdown",
};
//-------------------------------------------------------------------------------------------------------
static char*													DName[]=
{
	"PowerDeviceUnspecified",
	"PowerDeviceD0",
	"PowerDeviceD1",
	"PowerDeviceD2",
	"PowerDeviceD3",
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION reprezentuje implementaciu DISPATCH ROUTINE pre IRP typu IRP_MJ_PNP.
GENERICAPI NTSTATUS GENERIC_EXPORT GenericDispatchPNP(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	// !!!!! Ziska sa REMOVE LOCK, aby nedoslo k predcasnemu uvolneniu DEVICE OBJECT pre CURRENT DRIVER z MEMORY.
	// !!!!! Volanie FUNCTION IoAcquireRemoveLock() je NUTNE, pretoze IRP typu [IRP_MJ_PNP] sa posiela na spracovanie do DRIVERS NIZSIE v DEVICE OBJECT STACK.
	if (PDX->MRemoveLock!=NULL && NT_SUCCESS(Status=IoAcquireRemoveLock(PDX->MRemoveLock,IRP))==false)
	{
		// !!! Ak REMOVE LOCK NEBOL PRIDELENY, tak IRP musi byt OKAMZITE UKONCENE s ERROR CODE.
		return(CompleteRequest(IRP,Status));
	}

	// FUNCTION IoGetCurrentIrpStackLocation() ziska POINTER na STRUCTURE [IO_STACK_LOCATION] pre CURRENT DRIVER v DEVICE OBJECT STACK.
	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);

	ASSERT(Stack->MajorFunction==IRP_MJ_PNP);

	// !!! ARRAY obsahuje HANDLER ROUTINES, ktore vykonavaju spracovanie jednotlivych MINOR FUNCTIONS.
	// !!!!! Pozicie jednotlivych HANDLER ROUTINES MUSIA zodpovedat cislam MINOR FUNCTIONS, inak sa zavola NESPRAVNA HANDLER ROUTINE.
	static NTSTATUS (*FunctionTable[])(PGENERIC_EXTENSION PDX, PIRP IRP)=
	{
		HandleStartDevice,					// IRP_MN_START_DEVICE.
		HandleQueryRemove,					// IRP_MN_QUERY_REMOVE_DEVICE.
		HandleRemoveDevice,					// IRP_MN_REMOVE_DEVICE.
		HandleCancelRemove,					// IRP_MN_CANCEL_REMOVE_DEVICE.
		HandleStopDevice,					// IRP_MN_STOP_DEVICE.
		HandleQueryStop,					// IRP_MN_QUERY_STOP_DEVICE.
		HandleCancelStop,					// IRP_MN_CANCEL_STOP_DEVICE.
		DefaultPnpHandler,					// IRP_MN_QUERY_DEVICE_RELATIONS.
		DefaultPnpHandler,					// IRP_MN_QUERY_INTERFACE.
		HandleQueryCapabilities,			// IRP_MN_QUERY_CAPABILITIES.
		DefaultPnpHandler,					// IRP_MN_QUERY_RESOURCES.
		DefaultPnpHandler,					// IRP_MN_QUERY_RESOURCE_REQUIREMENTS.
		DefaultPnpHandler,					// IRP_MN_QUERY_DEVICE_TEXT.
		HandleFilterResourceRequirements,	// IRP_MN_FILTER_RESOURCE_REQUIREMENTS.
		// MINOR FUNCTION pre hodnotu 0x0E NIE JE DEFINOVANA.
		DefaultPnpHandler,
		DefaultPnpHandler,					// IRP_MN_READ_CONFIG.
		DefaultPnpHandler,					// IRP_MN_WRITE_CONFIG.
		DefaultPnpHandler,					// IRP_MN_EJECT.
		DefaultPnpHandler,					// IRP_MN_SET_LOCK.
		DefaultPnpHandler,					// IRP_MN_QUERY_ID.
		HandleQueryState,					// IRP_MN_QUERY_PNP_DEVICE_STATE.
		DefaultPnpHandler,					// IRP_MN_QUERY_BUS_INFORMATION.
		HandleUsageNotification,			// IRP_MN_DEVICE_USAGE_NOTIFICATION.
		HandleSurpriseRemoval,				// IRP_MN_SURPRISE_REMOVAL.
		// !!! Novsie verzie WINDOWS definuju aj MINOR FUNCTION [IRP_MN_DEVICE_ENUMERATED] s hodnotou 0x19.
	};

	// !!! Hodnota MINOR FUNCTION sluzi ako INDEX do ARRAY.
	ULONG														Function=Stack->MinorFunction;

	// !!! Ak HANDLER ROUTINE pre danu MINOR FUNCTION nebol najdeny (napriklad preto, lebo novsie verzie WINDOWS pridali nove MINOR FUNCTIONS), tak sa zavola STANDARDNY HANDLER, ktory posunie spracovanie danej MINOR FUNCTION do DRIVER NIZSIE v DEVICE OBJECT STACK.
	if (Function>=_countof(FunctionTable))
	{
		// Unknown function.
		// Some function we don't know about.
		// !!! FUNCTION posle spracovanie MINOR FUNCTION do DRIVER NIZSIE v DEVICE OBJECT STACK.
		Status=DefaultPnpHandler(PDX,IRP);

		if (PDX->MRemoveLock!=NULL)
		{
			// !!!!! Po spracovani IRP sa uvolni REMOVE LOCK.
			IoReleaseRemoveLock(PDX->MRemoveLock,IRP);
		}
		
		return(Status);
	}

	static char*												FunctionName[]=
	{
		"IRP_MN_START_DEVICE",
		"IRP_MN_QUERY_REMOVE_DEVICE",
		"IRP_MN_REMOVE_DEVICE",
		"IRP_MN_CANCEL_REMOVE_DEVICE",
		"IRP_MN_STOP_DEVICE",
		"IRP_MN_QUERY_STOP_DEVICE",
		"IRP_MN_CANCEL_STOP_DEVICE",
		"IRP_MN_QUERY_DEVICE_RELATIONS",
		"IRP_MN_QUERY_INTERFACE",
		"IRP_MN_QUERY_CAPABILITIES",
		"IRP_MN_QUERY_RESOURCES",
		"IRP_MN_QUERY_RESOURCE_REQUIREMENTS",
		"IRP_MN_QUERY_DEVICE_TEXT",
		"IRP_MN_FILTER_RESOURCE_REQUIREMENTS",
		"",
		"IRP_MN_READ_CONFIG",
		"IRP_MN_WRITE_CONFIG",
		"IRP_MN_EJECT",
		"IRP_MN_SET_LOCK",
		"IRP_MN_QUERY_ID",
		"IRP_MN_QUERY_PNP_DEVICE_STATE",
		"IRP_MN_QUERY_BUS_INFORMATION",
		"IRP_MN_DEVICE_USAGE_NOTIFICATION",
		"IRP_MN_SURPRISE_REMOVAL",
	};

	DbgPrint(("%s - PNP Request [%s] !\n",PDX->MDebugName,FunctionName[Function]));

	// !!! Zavola sa HANDLER ROUTINE, ktorej ulohou je spracovat danu MINOR FUNCTION a vratit RETURN VALUE typu [NTSTATUS].
	Status=(*FunctionTable[Function])(PDX,IRP);

	if (Function!=IRP_MN_REMOVE_DEVICE && PDX->MRemoveLock!=NULL)
	{
		// !!!!! Po spracovani IRP sa uvolni REMOVE LOCK.
		IoReleaseRemoveLock(PDX->MRemoveLock,IRP);
	}

	// !!! Ako RETURN VALUE sa vrati VALUE [NTSTATUS], ktoru vratil HANDLER ROUTINE pre danu MINOR FUNCTION.
	return(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS HandleFilterResoureRequirementsCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	PGENERIC_EXTENSION											PDX=(PGENERIC_EXTENSION) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d], INFORMATION [%I64X] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned,InterruptRequestPacket->IoStatus.Information));

	if (InterruptRequestPacket->PendingReturned!=FALSE)
	{
		IoMarkIrpPending(InterruptRequestPacket);
	}

	if (PDX->MModifyResources!=NULL)
	{
		InterruptRequestPacket->IoStatus.Information=(ULONG_PTR) PDX->MModifyResources((PIO_RESOURCE_REQUIREMENTS_LIST) InterruptRequestPacket->IoStatus.Information);
	}

	return(STATUS_CONTINUE_COMPLETION);
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION reprezentuje HANDLER ROUTINE pre MINOR FUNCTION [IRP_MN_FILTER_RESOURCE_REQUIREMENTS].
NTSTATUS HandleFilterResourceRequirements(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	IoCopyCurrentIrpStackLocationToNext(IRP);

	IoSetCompletionRoutine(IRP,HandleFilterResoureRequirementsCompletionRoutine,PDX,TRUE,TRUE,TRUE);

	return(IoCallDriver(PDX->MLowerDeviceObject,IRP));
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION reprezentuje DEFAULT HANDLER ROUTINE, ktora je volana pre tie MINOR FUNCTIONS IRP typu [IRP_MJ_PNP], ktore CURRENT DRIVER NESPRACOVAVA.
NTSTATUS DefaultPnpHandler(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	// INDEX v [IO_STACK_LOCATION] ARRAY sa DEKREMENTUJE.
	// !!! Pri VIRTUAL DRIVERS (ktore nemaju pripojenie na fyzicky BUS) je NESMIERNE DOLEZITE pouzit FUNCTION IoSkipCurrentIrpStackLocation() a NIE FUNCTION IoCopyCurrentIrpStackLocationToNext(), pretoze v DEVICE OBJECT STACK moze byt CURRENT DRIVER POSLEDNY a NIZSIE v STRUCTURE [IRP] uz NEMUSI BYT miesto pre dalsi [IO_STACK_LOCATION].
	IoSkipCurrentIrpStackLocation(IRP);

	// !!! FUNCTION IoCallDriver() spatne INKREMENTUJE INDEX v [IO_STACK_LOCATION] ARRAY a zavola DRIVER NIZSIE v DEVICE OBJECT STACK.
	return(IoCallDriver(PDX->MLowerDeviceObject,IRP));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION je zodpovedna za spracovanie MINOR FUNCTION [IRP_MN_START_DEVICE].
// !!! Ulohou FUNCTION je INICIALIZOVAT HW DEVICE.
NTSTATUS HandleStartDevice(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_START_DEVICE);

	// Flag that we handled this IRP.
	// !!! Kedze MINOR FUNCTION [IRP_MN_START_DEVICE] VYZADUJE, aby IRP bolo spracovane NAJPRV DRIVERS NIZSIE v DEVICE STACK, je NUTNE nastavit hodnotu FIELD [IRP.IoStatus.Status] na VALUE [STATUS_SUCCESS]. Tym sa indikuje DRIVERS NIZSIE v DEVICE OBJECT STACK, ze IRP bola spracovana CURRENT DRIVER a CURRENT DRIVER je pripraveny na nastartovanie HW DEVICE.
	IRP->IoStatus.Status=STATUS_SUCCESS;

	// !!!!! FUNCTION zasle IRP na spracovanie do DRIVERS NIZSIE v DEVICE OBJECT STACK. FUNCTION vykonava nasledujuce kroky.
	// 1. Vytvori KERNEL EVENT.
	// 2. Pomocou FUNCTION IoSetCompletionRoutine() zaregistruje COMPLETION ROUTINE.
	// 3. Pomocou FUNCTION KeWaitForSingleObject() vykona THREAD BLOCKING, ktory caka na SIGNALIZACIU KERNEL EVENT vytvorenom v bode 1.
	// 4. COMPLETION ROUTINE nastavi KERNEL EVENT vytvoreny v bode 1.
	// 5. COMPLETION ROUTINE vrati ako RETURN VALUE hodnotu [STATUS_MORE_PROCESSING_REQUIRED], ktora ZABRANI volaniu COMPLETION ROUTINES DRIVERS VYSSIE v DEVICE OBJECT STACK.
	// !!! 6. Ako RETURN VALUE FUNCTION ForwardAndWait() vrati hodnotu FIELD [IRP.IoStatus.Status].
	NTSTATUS													Status=ForwardAndWait(PDX,IRP);

	if (NT_SUCCESS(Status)==false)
	{
		// !!! Ak DRIVERS NIZSIE v DEVICE OBJECT STACK ZLYHALI pri spracovavani MINOR FUNCTION [IRP_MN_START_DEVICE], DRIVER MUSI UKONCIT IRP volanim FUNCTION IoCompleteRequest(), ktora spusti volanie COMPLETION ROUTINES pre DRIVERS VYSSIE v DEVICE OBJECT STACK.
		return(CompleteRequest(IRP,Status));
	}

	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);
	PCM_PARTIAL_RESOURCE_LIST									Raw;

	// FIELD obsahuje [IO_STACK_LOCATION.Parameters.StartDevice.AllocatedResources] obsahuje zoznam IO RESOURCES alokovanych pre dany DRIVER, ktore maju BUS SPECIFIC cislovanie.
	if (Stack->Parameters.StartDevice.AllocatedResources!=NULL)
	{
		Raw=&Stack->Parameters.StartDevice.AllocatedResources->List[0].PartialResourceList;
	}
	else
	{
		Raw=NULL;
	}

	PCM_PARTIAL_RESOURCE_LIST									Translated;

	// FIELD obsahuje [IO_STACK_LOCATION.Parameters.StartDevice.AllocatedResourcesTranslated] obsahuje zoznam IO RESOURCES alokovanych pre dany DRIVER, ktore maju SYSTEM SPECIFIC cislovanie.
	if (Stack->Parameters.StartDevice.AllocatedResourcesTranslated!=NULL)
	{
		Translated=&Stack->Parameters.StartDevice.AllocatedResourcesTranslated->List[0].PartialResourceList;
	}
	else
	{
		Translated=NULL;
	}

	if (Raw!=NULL)
	{
		DbgPrint(("%s - Resources:\n",PDX->MDebugName));
		ShowResources(Raw);
	}

	if (Translated!=NULL)
	{
		DbgPrint(("%s - Translated Resources:\n",PDX->MDebugName));
		ShowResources(Translated);
	}

	// Assume we are initially in the D0 state.
	PDX->MDevicePower=PowerDeviceD0;
	PDX->MSystemPower=PowerSystemWorking;

	POWER_STATE													Foo;

	Foo.DeviceState=PowerDeviceD0;
	PoSetPowerState(PDX->MPDO,DevicePowerState,Foo);

	// Call client driver's StartDevice function to initialize the device for I/O.
	// !!!!! Zavola sa CUSTOM ROUTINE StartDevice(), ktora obsahuje CUSTOM DRIVER CODE, ktoreho ulohou je nastartovat HW DEVICE.
	Status=(*PDX->MStartDevice)(PDX->MDeviceObject,Raw,Translated); 

	if (NT_SUCCESS(Status)==true)
	{
		// Started okay.
		DbgPrint("%s - To WORKING from [%s] !\n",PDX->MDebugName,StateNames[PDX->MState]);

		PDX->MHardwareWorking=TRUE;

		// If idle detection constants were saved in the registry, register this device for idle detection.
		POWERINFO												PI;

		if (NT_SUCCESS(GetPowerInfoFromRegistry(PDX,&PI))==true)
		{
			ImplementPowerPolicy(PDX,&PI);
		}

		// Enable all registered device interfaces.
		// !!! Povolia sa DEVICE INTERFACES, ktore boli zaregistrovane v CUSTOM ROUTINE AddDevice().
		EnableAllInterfaces(PDX,TRUE);

		// Release any stalled IRPs.
		// !!! PNP STATE sa zmeni na STATE [WORKING].
		PDX->MState=WORKING;

		// In case we got a bogus STOP.
		AllowAllRequests(PDX->MQueues,PDX->MNumberQueues);

		// !!!!! Kedze DEVICE QUEUES su na zaciatku v STATE [STALLED], po nastartovani DEVICE OBJECT je NUTNE umoznit DEVICE QUEUES, aby mohli spracovavat IRP a volanie FUNCTION RestartAllRequests() to zabezpeci zmenou IRP QUEUE STATE na STATE [READY].
		RestartAllRequests(PDX->MQueues,PDX->MNumberQueues,PDX->MDeviceObject);

		// If system wakeup is enabled, start a wait-wake IRP.
		GenericWakeupControl(PDX,ManageWaitWake);
	}

	// !!! DRIVER ukonci IRP volanim FUNCTION IoCompleteRequest(), ktora spusti volanie COMPLETION ROUTINES pre DRIVERS VYSSIE v DEVICE OBJECT STACK.
	// !!!!! Kedze COMPLETION ROUTINE zaregistrovana vo FUNCTION ForwardAndWait() vratila ako RETURN VALUE hodnotu [STATUS_MORE_PROCESSING_REQUIRED] MUSI sa volanim FUNCTION IoCompleteIrp() (je volana v CUSTOM FUNCTION CompleteRequest()) obnovit vyvolavanie COMPLETION ROUTINES, aby mohlo byt spracovanie IRP ukoncene.
	return(CompleteRequest(IRP,Status));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION je zodpovedna za spracovanie MINOR FUNCTION [IRP_MN_STOP_DEVICE].
// 1. FUNCTION vykonava CUSTOM IO OPERATIONS, ktore ZASTAVIA HW DEVICE.
// !!! 2. FUNCTION NEODSTRANUJE DEVICE OBJECT z MEMORY.
// !!!!! 3. FUNCTION NEZASTAVUJE IRP QUEUES. To robi uz DISPATCH ROUTINE, ktora spracovava IRP s MINOR FUNCTION [IRP_MN_QUERY_STOP_DEVICE].
// !!! 4. FUNCTION musi mat osetrenu moznost, ze pre jedno volanie FUNCTION HandleStartDevice() bude zavolana 'N' KRAT.
NTSTATUS HandleStopDevice(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_STOP_DEVICE);

	// Flag that we handled this IRP.
	// !!! FUNCTION nastavi FIELD [IRP.IoStatus.Status] na VALUE [STATUS_SUCCESS] cim sa indikuje, ze DRIVER IRP uspesne spracoval.
	IRP->IoStatus.Status=STATUS_SUCCESS;

	// We're supposed to always get a query before we're stopped, so we should already be in the PENDINGSTOP state. There's a Win98 bug that can sometimes cause us to get a STOP instead of a REMOVE, in which case we should start rejecting IRPs.
	// !!!!! Tento CODE je primarne kvoli CHYBE vo WINDOWS 98. V neskorsich verziach by uz tento stav NEMAL NASTAT.
	// !!! Ak DRIVER STATE je rozny od STATE [PENDINGSTOP], VSETKY IRP vo vsetkych DEVQUEUES sa UKONCIA s ERROR volanim FUNCTION IoCompleteIrp().
	if (PDX->MState!=PENDINGSTOP)
	{
		// No previous query.
		DbgPrint(("%s - STOP with no previous QUERY_STOP !\n",PDX->MDebugName));
		// !!!!! Zmeni sa STATE IRP QUEUES na STATE [REJECTING]. Od tejto chvile budu IRP QUEUES OKAMZITE UKONCOVAT IRP s ERROR.
		AbortAllRequests(PDX->MQueues,PDX->MNumberQueues,STATUS_DELETE_PENDING);
		AbortPendingIoctls(PDX,STATUS_DELETE_PENDING);
	}

	// Cancel any outstanding wait-wake IRP.
	GenericWakeupControl(PDX,CancelWaitWake);

	// !!! FUNCTION CallStopDevice() zavola CUSTOM ROUTINE StopDevice(), ktora obsahuje CUSTOM DRIVER CODE, ktoreho ulohou je pozastavit HW DEVICE.
	CallStopDevice(PDX);

	DbgPrint("%s - To STOPPED from [%s] !\n",PDX->MDebugName,StateNames[PDX->MState]);

	// !!! PNP STATE sa zmeni na STATE [STOPPED].
	PDX->MState=STOPPED;

	// !!!!! DRIVER MUSI zavolat DRIVERS NIZSIE v DEVICE OBJECT STACK, ktore dokoncia spracovanie IRP.
	return(DefaultPnpHandler(PDX,IRP));
}
//-------------------------------------------------------------------------------------------------------
// Pomocna FUNCTION, ktora sluzi na zavolanie CUSTOM ROUTINE StopDevice(), ktora obsahuje CUSTOM DRIVER CODE, ktoreho ulohou je pozastavit HW DEVICE.
VOID CallStopDevice(PGENERIC_EXTENSION PDX)
{
	GenericWakeupControl(PDX,CancelWaitWake);

	BOOLEAN														Touch=PDX->MHardwareWorking;

	PDX->MHardwareWorking=FALSE;

	// !!! Zavola sa CUSTOM ROUTINE StopDevice(), ktora obsahuje CUSTOM DRIVER CODE, ktoreho ulohou je pozastavit HW DEVICE.
	(*PDX->MStopDevice)(PDX->MDeviceObject,Touch);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION je zodpovedna za spracovanie MINOR FUNCTION [IRP_MN_QUERY_STOP_DEVICE].
// 1. FUNCTION zistuje ci HW DEVICE je pripravene byt STOPPED.
// !!! 2. Ak FUNCTION zisti, ze HW DEVICE moze byt STOPPED MUSI zmenit STATE DEVQUEUES do STATE [STALLED], aby sa ZABRANILO DEVQUEUES v odosielani dalsich IRP do HW DEVICE.
// !!!!! 3. FUNCTION zaroven MUSI SYNCHRONNE POCKAT na UKONCENIE SPRACOVANIE VSETKYCH IRP, ktore HW DEVICE aktualne spracovava.
// !!!!! 4. FUNCTION NEZASTAVUJE HW DEVICE. To robi az IRP s MINOR FUNCTION [IRP_MN_STOP_DEVICE]. FUNCTION iba ZASTAVI DEVQUEUES a SYNCHRONNE pocka na skoncenie aktualne vykonavanych IRP.
NTSTATUS HandleQueryStop(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_QUERY_STOP_DEVICE);

	// Flag that we handled this IRP.
	// !!! FUNCTION nastavi FIELD [IRP.IoStatus.Status] na VALUE [STATUS_SUCCESS] cim sa indikuje, ze DRIVER IRP uspesne spracoval.
	IRP->IoStatus.Status=STATUS_SUCCESS;
	
	// Boot devices may get this query before they even start, so check to see if we're in the WORKING state before doing anything.
	// !!! Vykona sa kontrola ci HW DEVICE uz bolo spustene. Ak nebolo, znamena to, ze IRP s MINOR FUNCTION [IRP_MN_QUERY_STOP_DEVICE] dorazil SKOR ako bolo HW DEVICE spustene.
	if (PDX->MState!=WORKING)
	{
		// !!! Ak STATE tohto DRIVER NIE JE [WORKING], potom sa IRP posle na spracovanie do DRIVERS NIZSIE v DEVICE OBJECT STACK a nasledne sa spracovanie IRP UKONCI.
		return(DefaultPnpHandler(PDX,IRP));
	}

	// See if it will be okay to stop the device right now. This test includes asking the client driver via a callback routine.
	// !!!!! DRIVER vykona kontrolu ci HW DEVICE MOZE BYT STOPPED. To aka kontrola sa vykona je DRIVER SPECIFIC.
	if (OkayToStop(PDX)==FALSE)
	{
		// !!! Ak HW DEVICE NEMOZE byt STOPPED, IRP s MINOR FUNCTION [IRP_MN_QUERY_STOP_DEVICE] je UKONCENE s ERROR VALUE [STATUS_UNSUCCESSFUL].
		return(CompleteRequest(IRP,STATUS_UNSUCCESSFUL));
	}

	// Stall the request queue and wait for the current IRP (if any) to finish.
	// !!!!! Ak HW DEVICE MOZE byt STOPPED, DRIVER MUSI pre VSETKY DEVQUEUES, ktore DRIVER pouziva zmenit STATE na STATE [STALLED], aby DEVQUEUES uz NEPUSTILI ZIADNE DALSIE IRP do HW DEVICE a iba ich ukladali do QUEUE, pre pripadne pozdejsie spracovanie.
	StallAllRequests(PDX->MQueues,PDX->MNumberQueues);

	if (PDX->MFlushPendingIO!=NULL)
	{
		(*PDX->MFlushPendingIO)(PDX->MDeviceObject,IRP_MJ_PNP,IRP_MN_QUERY_STOP_DEVICE,PowerDeviceUnspecified,PowerDeviceUnspecified);
	}

	// !!!!! DRIVER MUSI VYCKAT kym HW DEVICE NEUKONCI spracovanie VSETKYCH IRP, ktore uz DEVQUEUES odoslali na HW DEVICE. Az POTOM moze USPESNE ukoncit IRP s MINOR FUNCTION [IRP_MN_QUERY_STOP_DEVICE].
	WaitForCurrentIRPS(PDX->MQueues,PDX->MNumberQueues);

	GenericWakeupControl(PDX,DisableWakeup);
 	
	// !!! PNP STATE sa zmeni na STATE [PENDINGSTOP].
	PDX->MState=PENDINGSTOP;

	// !!! IRP sa zasle na spracovanie do DRIVER NIZSIE v DEVICE OBJECT STACK.
	return(DefaultPnpHandler(PDX,IRP));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION je zodpovedna za spracovanie MINOR FUNCTION [IRP_MN_CANCEL_STOP_DEVICE].
// 1. FUNCTION SPUSTA DEVQUEUES zmenou ich STATE do STATE [READY], aby DEVQUEUES mohli odosielat IRP vo svojich QUEUES na HW DEVICE.
// !!!!! 2. FUNCTION NESTARTUJE HW DEVICE. Je to preto, lebo IRP s MINOR FUNCTION [IRP_MN_QUERY_STOP_DEVICE] NEVYKONAL zastavenie HW DEVICE, ale iba zastavil DEVQUEUES. Zastavenie HW DEVICE je az ulohou IRP s MINOR FUNCTION [IRP_MN_STOP_DEVICE].
NTSTATUS HandleCancelStop(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_CANCEL_STOP_DEVICE);

	// Flag that we handled this IRP.
	// !!! FUNCTION nastavi FIELD [IRP.IoStatus.Status] na VALUE [STATUS_SUCCESS] cim sa indikuje, ze DRIVER IRP uspesne spracoval.
	IRP->IoStatus.Status=STATUS_SUCCESS;

	// !!! Zisti sa ci DRIVER je v PNP STATE [PENDINGSTOP]. Ak nie je tak sa IRP IGNORUJE zaslanim na spracovanie do DRIVERS NIZSIE v DEVICE OBJECT STACK.
	if (PDX->MState==PENDINGSTOP)
	{
		// We succeeded earlier query.
		// Lower level drivers are presumably in the pending-stop state as well, so we need to tell them that the stop has been cancelled before we start sending IRPs down to them.
		// Wait for lower layers.
		// !!!!! IRP sa SYNCHRONNE zasle na spracovanie do DRIVER NIZSIE v DEVICE OBJECT STACK. Blokacia CURRENT THREAD je realizovana pomocou EVENT, ktory je nastaveny v COMPLETION ROUTINE, ktoru CUSTOM FUNCTION ForwardAndWait() registruje.
		NTSTATUS												Status=ForwardAndWait(PDX,IRP);

		if (NT_SUCCESS(Status)==true)
		{
			// Completed successfully.
			DbgPrint(("%s - To WORKING from PENDINGSTOP !\n",PDX->MDebugName));

			// !!! PNP STATE sa zmeni na STATE [WORKING].
			PDX->MState=WORKING;

			// !!!!! VSETKY DEVQUEUES sa opatovne SPUSTIA zmenenim DEVQUEUE STATE na STATE [READY]. IRP, ktore sa pocas casu, kedy boli DEVQUEUES v STATE [STALLED] zaslane do DEVQUEUES sa mozu vykonat.
			RestartAllRequests(PDX->MQueues,PDX->MNumberQueues,PDX->MDeviceObject);

			// Reissue wait-wake if necessary.
			GenericWakeupControl(PDX,ManageWaitWake);
		}
		else
		{
			DbgPrint("%s - Status [%8.8lX] returned by PDO for IRP_MN_CANCEL_STOP_DEVICE !",PDX->MDebugName,Status);
		}
		
		// !!!!! Kedze COMPLETION ROUTINE zaregistrovana vo FUNCTION ForwardAndWait() vratila ako RETURN VALUE hodnotu [STATUS_MORE_PROCESSING_REQUIRED] MUSI sa volanim FUNCTION IoCompleteIrp() (je volana v CUSTOM FUNCTION CompleteRequest()) obnovit vyvolavanie COMPLETION ROUTINES, aby mohlo byt spracovanie IRP ukoncene.
		return(CompleteRequest(IRP,Status));
	}

	// Unexpected cancel.
	// !!! Ak DRIVER DRIVER NEBOL v PNP STATE [PENDINGSTOP], tak sa IRP IGNORUJE zaslanim na spracovanie do DRIVERS NIZSIE v DEVICE OBJECT STACK.
	return(DefaultPnpHandler(PDX,IRP));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION je zodpovedna za spracovanie MINOR FUNCTION [IRP_MN_REMOVE_DEVICE].
// !!! 1. FUNCTION vyprazdni DEVQUEUES odstranenim vsetkych IRP z DEVQUEUES ich ukocenim volanim FUNCTION IoCompleteRequest() s ERROR VALUE.
// !!! 2. FUNCTION zmenou STATE DEVQUEUES na STATE [REJECTING] zaroven prinuti DEVQUEUES, aby akekolvek IRP, ktore do DEVQUEUES dorazia boli OKAMZITE UKONCENE volanim FUNCTION IoCompleteRequest() s ERROR VALUE.
// !!! 3. FUNCTION nasledne vykonava CUSTOM IO OPERATIONS, ktore ZASTAVIA HW DEVICE.
// !!! 4. FUNCTION nasledne ODSTRANUJE DEVICE OBJECT z MEMORY.
// !!!!! 5. FUNCTION NEZASTAVUJE IRP QUEUES iba VYPRAZDNUJE UZ ZASTAVENE IRP QUEUES. Zastavenie IRP QUEUES robi uz DISPATCH ROUTINE, ktora spracovava IRP s MINOR FUNCTION [IRP_MN_QUERY_REMOVE_DEVICE].
// !!! 6. FUNCTION musi mat osetrenu moznost, ze pre jedno volanie FUNCTION HandleStartDevice() bude zavolana 'N' KRAT.
NTSTATUS HandleRemoveDevice(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_REMOVE_DEVICE);

	// Flag that we handled this IRP.
	// !!! FUNCTION nastavi FIELD [IRP.IoStatus.Status] na VALUE [STATUS_SUCCESS] cim sa indikuje, ze DRIVER IRP uspesne spracoval.
	IRP->IoStatus.Status=STATUS_SUCCESS;

	// Cancel any queued requests and start rejecting new ones.
	// !!!!! IRP QUEUES uz BOLI v STATE [STALLED] a volanie FUNCTION AbortAllRequests() zmeni STATE [STALLED] na STATE [REJECTING].
	// !!!!! Volanie FUNCTION AbortAllRequests() OKAMZITE UKONCI VSETKY IRP, ktore boli ulozene v IRP QUEUES volanim FUNCTION IoCompleteRequest() s ERROR CODE a zaroven VSETKY NOVE IRP budu OKAMZITE UKONCENE volanim IoCompleteRequest() s ERROR CODE.
	AbortAllRequests(PDX->MQueues,PDX->MNumberQueues,STATUS_DELETE_PENDING);

	AbortPendingIoctls(PDX,STATUS_DELETE_PENDING);
	GenericWakeupControl(PDX,DisableWakeup);

	// Disable all device interfaces that were registered through us. This triggers PnP notifications that will allow apps to close their handles.
	// !!! FUNCTION odregistruje DEVICE INTERFACES, ktore boli zaregistrovane v CUSTOM ROUTINE AddDevice().
	DeregisterAllInterfaces(PDX);

	// Release I/O resources.
	// !!! FUNCTION CallStopDevice() zavola CUSTOM ROUTINE StopDevice(), ktora obsahuje CUSTOM IO OPERATIONS, ktorych ulohou je pozastavit HW DEVICE.
	CallStopDevice(PDX);

	DbgPrint("%s - To REMOVED from [%s] !\n",PDX->MDebugName,StateNames[PDX->MState]);

	// !!! PNP STATE sa zmeni na STATE [REMOVED].
	PDX->MState=REMOVED;

	// Let lower-level drivers handle this request. Ignore whatever result eventuates.
	// !!!!! DRIVER MUSI zavolat DRIVERS NIZSIE v DEVICE OBJECT STACK, ktore dokoncia spracovanie IRP.
	NTSTATUS													Status=DefaultPnpHandler(PDX,IRP);

	// Wait for all claims against this device to vanish before removing the device object.
	if (PDX->MRemoveLock!=NULL)
	{
		// !!!!! FUNCTION UVOLNI LOCK a ZAROVEN vykona BLOCKING CURRENT THREAD, az kym VSETKY IPR DISPATCH ROUTINES, ktore vykonali LOCKING nad REMOVE LOCK tento LOCKING neuvolnia.
		// !!!!! Po zavolani FUNCTION IoReleaseRemoveLockAndWait() budu VSETKY NASLEDNE VOLANIA FUNCTION IoAcquireRemoveLock() vraciat ERROR CODE [STATUS_DELETE_PENDING], cim indikuju, ze DRIVER caka na UVOLNENIE REMOVE LOCK a teda ZIADNE DALSIE IRP by nemalo byt SPRACOVANE.
		IoReleaseRemoveLockAndWait(PDX->MRemoveLock,IRP);
	}

	// Remove the device object.
	// !!!!! FUNCTION CallRemoveDevice() zavola CUSTOM ROUTINE RemoveDevice(), ktora obsahuje CUSTOM DRIVER CODE, ktoreho ulohou je UVOLNIT DEVICE OBJECT z MEMORY.
	CallRemoveDevice(PDX);

	// Cleanup our device extension.
	CleanupGenericExtension(PDX);

	// Lower-level completed IoStatus already.
	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Pomocna FUNCTION, ktora sluzi na zavolanie CUSTOM ROUTINE RemoveDevice(), ktora obsahuje CUSTOM DRIVER CODE, ktoreho ulohou je zastavit HW DEVICE a uvolnit DEVICE OBJECT.
VOID CallRemoveDevice(PGENERIC_EXTENSION PDX)
{
	// !!! CUSTOM ROUTINE RemoveDevice() obsahuje CUSTOM DRIVER CODE, ktoreho ulohou je zastavit HW DEVICE a UVOLNIT DEVICE OBJECT.
	(*PDX->MRemoveDevice)(PDX->MDeviceObject);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION je zodpovedna za spracovanie MINOR FUNCTION [IRP_MN_QUERY_REMOVE_DEVICE].
// 1. Ulohou FUNCTION je ZISTIT ci HW DEVICE moze byt REMOVE (HW DEVICE STOPPED a DEVICE OBJECT vymazany z MEMORY).
// !!!!! 2. Ak FUNCTION zisti, ze HW DEVICE moze byt REMOVED MUSI zmenit STATE DEVQUEUES do STATE [STALLED], aby sa ZABRANILO DEVQUEUES v odosielani dalsich IRP do HW DEVICE.
// !!!!! 3. FUNCTION zaroven MUSI POCKAT na UKONCENIE SPRACOVANIE VSETKYCH IRP, ktore HW DEVICE aktualne spracovava.
NTSTATUS HandleQueryRemove(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_QUERY_REMOVE_DEVICE);

	// Flag that we handled this IRP.
	// !!! FUNCTION nastavi FIELD [IRP.IoStatus.Status] na VALUE [STATUS_SUCCESS] cim sa indikuje, ze DRIVER IRP uspesne spracoval.
	IRP->IoStatus.Status=STATUS_SUCCESS;

	// !!! Vykona sa kontrola ci HW DEVICE uz bolo spustene. Ak nebolo, znamena to, ze IRP s MINOR FUNCTION [IRP_MN_QUERY_STOP_DEVICE] dorazil SKOR ako bolo HW DEVICE spustene.
	if (PDX->MState==WORKING)
	{
		// Currently working.
		// See if it's okay to remove this device. The test includes asking the client driver. Then stall the queue for the duration of the query. The TOASTER sample in the DDK drains the queue here instead of stalling it, by the way.
		// !!!!! DRIVER vykona kontrolu ci HW DEVICE MOZE BYT REMOVED. To aka kontrola sa vykona je DRIVER SPECIFIC.
		// !!!!! Kontrola spravidla zahrna detekciu ci pre DEVICE OBJECT obsahuje otvorene HANDLES. Ak ano, potom FUNCTION OkayToRemove() by mala vratit FALSE.
		if (OkayToRemove(PDX)==FALSE)
		{
			// Can't remove because busy.
			// !!! Ak HW DEVICE NEMOZE byt REMOVED, IRP s MINOR FUNCTION [IRP_MN_QUERY_REMOVE_DEVICE] je UKONCENE s ERROR VALUE [STATUS_UNSUCCESSFUL].
			return(CompleteRequest(IRP,STATUS_UNSUCCESSFUL));
		}

		// !!!!! Ak HW DEVICE MOZE byt REMOVED, DRIVER MUSI pre VSETKY DEVQUEUES, ktore DRIVER pouziva zmenit STATE na STATE [STALLED], aby DEVQUEUES uz NEPUSTILI ZIADNE DALSIE IRP do HW DEVICE a iba ich ukladali do QUEUE, pre pripadne pozdejsie spracovanie.
		StallAllRequests(PDX->MQueues,PDX->MNumberQueues);

		if (PDX->MFlushPendingIO!=NULL)
		{
			(*PDX->MFlushPendingIO)(PDX->MDeviceObject,IRP_MJ_PNP,IRP_MN_QUERY_REMOVE_DEVICE,PowerDeviceUnspecified,PowerDeviceUnspecified);
		}

		// !!!!! DRIVER MUSI VYCKAT kym HW DEVICE NEUKONCI spracovanie VSETKYCH IRP, ktore uz DEVQUEUES odoslali na HW DEVICE. Az POTOM moze USPESNE ukoncit IRP s MINOR FUNCTION [IRP_MN_QUERY_REMOVE_DEVICE].
		WaitForCurrentIRPS(PDX->MQueues,PDX->MNumberQueues);

		// Cancel any pending wait-wake.
		GenericWakeupControl(PDX,CancelWaitWake);

		DbgPrint("%s - To PENDINGREMOVE from [%s] !\n",PDX->MDebugName,StateNames[PDX->MState]);
	}

	// Save current state for restoration if the query gets cancelled. (We can now be stopped or working.)
	// !!!!! DRIVER si ULOZI AKTUALNY STATE. Je to NUTNE preto, lebo IPR s MINOR FUNCTION [IRP_MN_QUERY_REMOVE_DEVICE] moze byt volany pri ROZNYCH DRIVER STATES. V pripade, ze IPR s MINOR FUNCTION [IRP_MN_QUERY_REMOVE_DEVICE] bude NESKOR ZRUSENE IRP s MINOR FUNCTION [IRP_MN_CANCEL_REMOVE_DEVICE], tak DRIVER STATE sa nastavi na POVODNU HODNOTU.
	PDX->MPrevState=PDX->MState;

	// !!! PNP STATE sa zmeni na STATE [PENDINGREMOVE].
	PDX->MState=PENDINGREMOVE;

	// !!! IRP sa zasle na spracovanie do DRIVER NIZSIE v DEVICE OBJECT STACK.
	return(DefaultPnpHandler(PDX,IRP));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION je zodpovedna za spracovanie MINOR FUNCTION [IRP_MN_CANCEL_REMOVE_DEVICE].
// 1. FUNCTION SPUSTA DEVQUEUES zmenou ich STATE do STATE [READY], aby DEVQUEUES mohli odosielat IRP vo svojich QUEUES na HW DEVICE.
// !!!!! 2. FUNCTION NESTARTUJE HW DEVICE ani NEVYTVARA DEVICE OBJECT. Je to preto, lebo IRP s MINOR FUNCTION [IRP_MN_QUERY_REMOVE_DEVICE] NEVYKONAL zastavenie HW DEVICE, ani neodstranil DEVICE OBJECT, ale iba zastavil DEVQUEUES. Zastavenie HW DEVICE a odstranenie DEVICE OBJECT je az ulohou IRP s MINOR FUNCTION [IRP_MN_REMOVE_DEVICE].
NTSTATUS HandleCancelRemove(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_CANCEL_REMOVE_DEVICE);
	
	// Flag that we handled this IRP.
	// !!! FUNCTION nastavi FIELD [IRP.IoStatus.Status] na VALUE [STATUS_SUCCESS] cim sa indikuje, ze DRIVER IRP uspesne spracoval.
	IRP->IoStatus.Status=STATUS_SUCCESS;

	// !!! Zisti sa ci DRIVER je v PNP STATE [PENDINGREMOVE]. Ak nie je tak sa IRP IGNORUJE zaslanim na spracovanie do DRIVERS NIZSIE v DEVICE OBJECT STACK.
	if (PDX->MState==PENDINGREMOVE)
	{
		// We succeeded earlier query.
		// Lower-level drivers are presumably in the pending-remove state as well, so we need to tell them that the remove has been cancelled before we start sending IRPs down to them.
		// Wait for lower layers.
		// !!!!! IRP sa SYNCHRONNE zasle na spracovanie do DRIVER NIZSIE v DEVICE OBJECT STACK. Blokacia CURRENT THREAD je realizovana pomocou EVENT, ktory je nastaveny v COMPLETION ROUTINE, ktoru CUSTOM FUNCTION ForwardAndWait() registruje.
		NTSTATUS												Status=ForwardAndWait(PDX,IRP);

		if (NT_SUCCESS(Status)==true)
		{
			// Completed successfully.
			DbgPrint("%s - To [%s] from PENDINGREMOVE !\n",PDX->MDebugName,StateNames[PDX->MPrevState]);

			// !!!!! DRIVER vrati STATE na POVODNY STATE v ktorom bol DRIVER PRED spracovanim IRP s MINOR FUNCTION [IRP_MN_QUERY_REMOVE_DEVICE].
			PDX->MState=PDX->MPrevState;

			// !!!!! VSETKY DEVQUEUES sa opatovne SPUSTIA zmenenim DEVQUEUE STATE na STATE [READY]. IRP, ktore sa pocas casu, kedy boli DEVQUEUES v STATE [STALLED] zaslane do DEVQUEUES sa mozu vykonat.
			RestartAllRequests(PDX->MQueues,PDX->MNumberQueues,PDX->MDeviceObject);

			// Reissue wait-wake if necessary.
			GenericWakeupControl(PDX,ManageWaitWake);
		}
		else
		{
			DbgPrint("%s - Status [%8.8lX] returned by PDO for IRP_MN_CANCEL_REMOVE_DEVICE !",PDX->MDebugName,Status);
		}

		// !!!!! Kedze COMPLETION ROUTINE zaregistrovana vo FUNCTION ForwardAndWait() vratila ako RETURN VALUE hodnotu [STATUS_MORE_PROCESSING_REQUIRED] MUSI sa volanim FUNCTION IoCompleteIrp() (je volana v CUSTOM FUNCTION CompleteRequest()) obnovit vyvolavanie COMPLETION ROUTINES, aby mohlo byt spracovanie IRP ukoncene.
		return(CompleteRequest(IRP,Status));
	}
	
	// Unexpected cancel.
	// !!! Ak DRIVER DRIVER NEBOL v PNP STATE [PENDINGREMOVE], tak sa IRP IGNORUJE zaslanim na spracovanie do DRIVERS NIZSIE v DEVICE OBJECT STACK.
	return(DefaultPnpHandler(PDX,IRP));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION je zodpovedna za spracovanie MINOR FUNCTION [IRP_MN_SURPRISE_REMOVAL].
// !!! 1. FUNCTION vyprazdni DEVQUEUES odstranenim vsetkych IRP z DEVQUEUES ich ukocenim volanim FUNCTION IoCompleteRequest() s ERROR VALUE.
// !!! 2. FUNCTION zmenou STATE DEVQUEUES na STATE [REJECTING] zaroven prinuti DEVQUEUES, aby akekolvek IRP, ktore do DEVQUEUES dorazia boli OKAMZITE UKONCENE volanim FUNCTION IoCompleteRequest() s ERROR VALUE.
// !!! 3. FUNCTION nasledne vykonava CUSTOM IO OPERATIONS, ktore ZASTAVIA HW DEVICE.
NTSTATUS HandleSurpriseRemoval(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_SURPRISE_REMOVAL);

	// Flag that we handled this IRP.
	// !!! FUNCTION nastavi FIELD [IRP.IoStatus.Status] na VALUE [STATUS_SUCCESS] cim sa indikuje, ze DRIVER IRP uspesne spracoval.
	IRP->IoStatus.Status=STATUS_SUCCESS;

	// !!!!! Zmeni sa STATE IRP QUEUES na STATE [REJECTING]. Od tejto chvile budu IRP QUEUES OKAMZITE UKONCOVAT IRP s ERROR.
	// !!!!! Volanie FUNCTION AbortAllRequests() OKAMZITE UKONCI VSETKY IRP, ktore boli ulozene v IRP QUEUES volanim FUNCTION IoCompleteRequest() s ERROR CODE a zaroven VSETKY NOVE IRP budu OKAMZITE UKONCENE volanim IoCompleteRequest() s ERROR CODE.
	AbortAllRequests(PDX->MQueues,PDX->MNumberQueues,STATUS_DELETE_PENDING);

	AbortPendingIoctls(PDX,STATUS_DELETE_PENDING);
	GenericWakeupControl(PDX,DisableWakeup);

	DbgPrint("%s - To SURPRISEREMOVED from [%s] !\n",PDX->MDebugName,StateNames[PDX->MState]);

	// !!! PNP STATE sa zmeni na STATE [SURPRISEREMOVED].
	PDX->MState=SURPRISEREMOVED;

	// This triggers notifications so apps can close their handles.
	// !!! DRIVER vykona DISABLE vsetkych zaregistrovanych DEVICE INTERFACES.
	EnableAllInterfaces(PDX,FALSE);

	// !!! FUNCTION CallStopDevice() zavola CUSTOM ROUTINE StopDevice(), ktora obsahuje CUSTOM IO OPERATIONS, ktorych ulohou je pozastavit HW DEVICE. DEVICE OBJECT sa vsak NEUVOLNUJE z MEMORY.
	CallStopDevice(PDX);

	// !!!!! DRIVER MUSI zavolat DRIVERS NIZSIE v DEVICE OBJECT STACK, ktore dokoncia spracovanie IRP.
	return(DefaultPnpHandler(PDX,IRP));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
GENERICAPI NTSTATUS GENERIC_EXPORT GenericDeregisterInterface(PGENERIC_EXTENSION PDX, const GUID* GUID)
{
	ASSERT(KeGetCurrentIrql()==PASSIVE_LEVEL);

	NTSTATUS													Status;
	
	KeEnterCriticalRegion();
	KeWaitForSingleObject(&PDX->MIfLock,Executive,KernelMode,FALSE,NULL);

	PINTERFACE_RECORD											IFP=FindInterfaceRecord(PDX,GUID);

	if (IFP!=NULL)
	{
		DeregisterInterface(PDX,IFP);
		Status=STATUS_SUCCESS;
	}
	else
	{
		Status=STATUS_INVALID_PARAMETER;
	}

	KeSetEvent(&PDX->MIfLock,EVENT_INCREMENT,FALSE);
	KeLeaveCriticalRegion();

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI NTSTATUS GENERIC_EXPORT GenericEnableInterface(PGENERIC_EXTENSION PDX, const GUID* GUID, BOOLEAN Enable)
{
	ASSERT(KeGetCurrentIrql()==PASSIVE_LEVEL);

	NTSTATUS													Status;
	
	KeEnterCriticalRegion();
	KeWaitForSingleObject(&PDX->MIfLock,Executive,KernelMode,FALSE,NULL);

	PINTERFACE_RECORD											IFP=FindInterfaceRecord(PDX,GUID);

	if (IFP!=NULL)
	{
		// Enable/disable this interface.
		if (IFP->MEnabled!=Enable)
		{
			(void)IoSetDeviceInterfaceState(&IFP->MLinkName,Enable);
		}

		IFP->MEnabled=Enable;
		Status=STATUS_SUCCESS;
	}
	else
	{
		Status=STATUS_INVALID_PARAMETER;
	}

	KeSetEvent(&PDX->MIfLock,EVENT_INCREMENT,FALSE);
	KeLeaveCriticalRegion();

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// GenericGetDeviceCapabilities (added 2.0) returns the device capabilties. If necessary, it retrieves them.
#pragma LOCKEDCODE
GENERICAPI PDEVICE_CAPABILITIES GENERIC_EXPORT GenericGetDeviceCapabilities(PGENERIC_EXTENSION PDX)
{
	// If necessary, ask the bus driver for this device's capabilities. We must be at PASSIVE_LEVEL to do this (requirement for sending the IRP).
	if (PDX->MGotCapabilities==FALSE)
	{
		// Fetch capabilities.
		if (KeGetCurrentIrql()!=PASSIVE_LEVEL)
		{
			return(NULL);
		}

		PDEVICE_CAPABILITIES									PDC=(PDEVICE_CAPABILITIES) ExAllocatePoolWithTag(PagedPool,sizeof(DEVICE_CAPABILITIES),'  CD');

		if (PDC==NULL)
		{
			return(NULL);
		}

		RtlZeroMemory(PDC,sizeof(*PDC));

		PDC->Size=sizeof(*PDC);
		PDC->Version=1;
		// Tu to hodilo WARNING.
		PDC->Address=(ULONG)-1;
		// Tu to hodilo WARNING.
		PDC->UINumber=(ULONG)-1;

		KEVENT													Event;
		
		KeInitializeEvent(&Event,NotificationEvent,FALSE);
		IO_STATUS_BLOCK											IOStatusBlock;

		PDEVICE_OBJECT											TDO=IoGetAttachedDeviceReference(PDX->MPDO);
		PIRP													IRP=IoBuildSynchronousFsdRequest(IRP_MJ_PNP,TDO,NULL,0,NULL,&Event,&IOStatusBlock);

		if (IRP==NULL)
		{
			return(NULL);
		}

		PIO_STACK_LOCATION										Stack=IoGetNextIrpStackLocation(IRP);

		Stack->MinorFunction=IRP_MN_QUERY_CAPABILITIES;
		Stack->Parameters.DeviceCapabilities.Capabilities=PDC;

		NTSTATUS												Status=IoCallDriver(TDO,IRP);

		if (Status==STATUS_PENDING)
		{
			KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL);
		}

		ExFreePoolWithTag(PDC,'  CD');
		ObDereferenceObject(TDO);
	}

	return(&PDX->MDeviceCaps);
}
//-------------------------------------------------------------------------------------------------------
GENERICAPI NTSTATUS GENERIC_EXPORT GenericRegisterInterface(PGENERIC_EXTENSION PDX, const GUID* GUID)
{
	ASSERT(KeGetCurrentIrql()==PASSIVE_LEVEL);

	NTSTATUS													Status;
	
	KeEnterCriticalRegion();
	KeWaitForSingleObject(&PDX->MIfLock,Executive,KernelMode,FALSE,NULL);

	PINTERFACE_RECORD											IFP=FindInterfaceRecord(PDX,GUID);

	if (IFP!=NULL)
	{
		Status=STATUS_INVALID_PARAMETER;
	}
	else
	{
		// Register new interface.
		IFP=(PINTERFACE_RECORD) ExAllocatePoolWithTag(NonPagedPool,sizeof(INTERFACE_RECORD),' PFI');

		if (IFP!=NULL)
		{
			// Initialize new interface record.
			Status=IoRegisterDeviceInterface(PDX->MPDO,GUID,NULL,&IFP->MLinkName);

			if (NT_SUCCESS(Status)==true)
			{
				// Interface registered.
				IFP->MGUID=*GUID;
				IFP->MEnabled=FALSE;
				InsertHeadList(&PDX->MIfList,&IFP->MList);
			}
			else
			{
				ExFreePoolWithTag(IFP,' PFI');
			}
		}
		else
		{
			Status=STATUS_INSUFFICIENT_RESOURCES;
		}
	}

	KeSetEvent(&PDX->MIfLock,EVENT_INCREMENT,FALSE);
	KeLeaveCriticalRegion();

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
GENERICAPI VOID GENERIC_EXPORT GenericSetDeviceState(PGENERIC_EXTENSION PDX, PNP_DEVICE_STATE PNPState)
{
	// Mask for things that changed.
	PDX->MPNPStateMask=(PNPState^PDX->MPNPState);
	PDX->MPNPState|=PNPState;

	// Inform PnP manager that our state has changed.
	IoInvalidateDeviceState(PDX->MPDO);
}
//-------------------------------------------------------------------------------------------------------
// AdjustDeviceCapabilities corrects the reported device capabilities to workaround the fact that many back-level bus drivers simply don't report them correctly. Cf. toaster.sys sample in the DDK and talk given by Adrian Oney (no relation) at WinHEC 2002.
__inline SYSTEM_POWER_STATE& operator++(SYSTEM_POWER_STATE& SystemState)
{
	SystemState=(SYSTEM_POWER_STATE) (SystemState+1);
	
	return(SystemState);
}
//-------------------------------------------------------------------------------------------------------
__inline SYSTEM_POWER_STATE& operator--(SYSTEM_POWER_STATE& SystemState)
{
	SystemState=(SYSTEM_POWER_STATE) (SystemState-1);
	
	return(SystemState);
}
//-------------------------------------------------------------------------------------------------------
VOID AdjustDeviceCapabilities(PGENERIC_EXTENSION PDX, PDEVICE_CAPABILITIES PDC)
{
	// Make sure that the device state for S0 is D0
	if (PDC->DeviceState[PowerSystemWorking]!=PowerDeviceD0)
	{
		DbgPrint("%s - DeviceState[PowerSystemWorking] is D%d instead of D0 !\n",PDX->MDebugName,PDC->DeviceState[PowerSystemWorking]-1);
		PDC->DeviceState[PowerSystemWorking]=PowerDeviceD0;
	}

	// Check for silly value of SystemWake.
	if (PDC->SystemWake>PowerSystemHibernate)
	{
		DbgPrint("%s - SystemWake has the silly value [%s] !\n",PDX->MDebugName,SName[PDC->SystemWake]);
	}

	// Adjust power capabilities to compensate for bus driver written to WDM 1.0 spec. First infer D1 and D2 capabilities from S->D state map.
	for (SYSTEM_POWER_STATE SystemState=PowerSystemSleeping1;SystemState<=PowerSystemHibernate;++SystemState)
	{
		// For each S-state.
		if (PDC->DeviceState[SystemState]==PowerDeviceD1 && PDC->DeviceD1==0)
		{
			DbgPrint(("%s - Inferring DeviceD1 from DeviceState[%s] !\n",PDX->MDebugName,SName[SystemState]));
			PDC->DeviceD1=TRUE;
		}

		if (PDC->DeviceState[SystemState]==PowerDeviceD2 && PDC->DeviceD2==0)
		{
			DbgPrint("%s - Inferring DeviceD2 from DeviceState[%s] !\n",PDX->MDebugName,SName[SystemState]);
			PDC->DeviceD2=TRUE;
		}
	}

	// Set the WakeFromDx flags based on the reported DeviceWake state and on the D-state corresponding to the reported SystemWake state.
	AdjustWakeCapabilities(PDX,PDC,PDC->DeviceWake);

	if (PDC->SystemWake!=PowerSystemUnspecified)
	{
		AdjustWakeCapabilities(PDX,PDC,PDC->DeviceState[PDC->SystemWake]);
	}

	// Make sure the device state for S5 is D3. Do this after adjusting wakeup capabilities because USBHUB uncritically assumes that a device can be in D2 from S1 through SystemWakeup. So if SystemWakeup happens to be S5 because of some ACPI mistake, changing the device state entry too soon would cause us to pick D3 as the DeviceWake value, which is more wrong than what we were starting with.
	if (PDC->DeviceState[PowerSystemShutdown]!=PowerDeviceD3)
	{
		DbgPrint("%s - DeviceState[PowerSystemShutdown] is D%d instead of D3 !\n",PDX->MDebugName,PDC->DeviceState[PowerSystemShutdown]-1);
		PDC->DeviceState[PowerSystemShutdown]=PowerDeviceD3;
	}

	// Find the deepest D-state from which this device can wake the system.
	// Assume no wakeup capability.
	DEVICE_POWER_STATE											WakeState=PowerDeviceUnspecified;

	if (PDC->WakeFromD3!=0)
	{
		WakeState=PowerDeviceD3;
	}
	else if (PDC->WakeFromD2!=0)
	{
		WakeState=PowerDeviceD2;
	}
	else if (PDC->WakeFromD1!=0)
	{
		WakeState=PowerDeviceD1;
	}
	else if (PDC->WakeFromD0!=0)
	{
		WakeState=PowerDeviceD0;
	}

	if (PDC->DeviceWake!=WakeState)
	{
		DbgPrint("%s - DeviceWake is [%s], but should be [%s] !\n",PDX->MDebugName,DName[PDC->DeviceWake],DName[WakeState]);
		PDC->DeviceWake=WakeState;
	}

	// If SystemWake is specified, the corresponding D-state had better be at least as powered as the state we just discovered, or else there's a bug in our bus driver. It may just be that we got a bogus SystemWake value, so don't do anything about it.
	if (PDC->SystemWake!=PowerSystemUnspecified)
	{
		if (PDC->DeviceState[PDC->SystemWake]>WakeState)
		{
			DbgPrint("%s - DeviceState[SystemWake] is less powered than minimum wake state [%s] !\n",PDX->MDebugName,DName[WakeState]);
		}
	}
	// If SystemWake wasn't specified, infer it from the S->D state map by finding the lowest S-state whose D-state is at least as powered as the lowest D-state from which wakeup is possible. (I think I got that right.)
	else if (WakeState!=PowerDeviceD0 && WakeState!=PowerDeviceUnspecified)
	{
		// Infer system wake state.
		for (SYSTEM_POWER_STATE SystemState=PowerSystemSleeping3;SystemState>=PowerSystemWorking;--SystemState)
		{
			// For each S-state.
			if (PDC->DeviceState[SystemState]!=PowerDeviceUnspecified && PDC->DeviceState[SystemState]<=WakeState)
			{
				// Found the S-state.
				DbgPrint("%s - Inferring that wakeup from S%d state possible !\n",PDX->MDebugName,SystemState-1);
				PDC->SystemWake=SystemState;
				break;
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------
// AdjustWakeCapabilities adjusts the wakeup capabilities for a device.	
VOID AdjustWakeCapabilities(PGENERIC_EXTENSION PDX, PDEVICE_CAPABILITIES PDC, DEVICE_POWER_STATE DeviceState)
{
	switch (DeviceState)
	{
		// Select on D-state.
		case PowerDeviceUnspecified:
		{
		}
		break;

		case PowerDeviceD0:
		{
			if (PDC->WakeFromD0==0)
			{
				DbgPrint("%s - AdjustWakeCapabilities Inferring WakeFromD0 !\n",PDX->MDebugName);
			}

			PDC->WakeFromD0=TRUE;
		}
		break;

		case PowerDeviceD1:
		{
			if (PDC->WakeFromD1==0)
			{
				DbgPrint(("%s - AdjustWakeCapabilities Inferring WakeFromD1 !\n",PDX->MDebugName));
			}
		
			if (PDC->DeviceD1==0)
			{
				DbgPrint(("%s - AdjustWakeCapabilities Inferring DeviceD1 !\n",PDX->MDebugName));
			}
		
			PDC->DeviceD1=TRUE;
			PDC->WakeFromD1=TRUE;
		}
		break;

		case PowerDeviceD2:
		{
			if (PDC->WakeFromD2==0)
			{
				DbgPrint(("%s - AdjustWakeCapabilities Inferring WakeFromD2 !\n",PDX->MDebugName));
			}

			if (PDC->DeviceD2==0)
			{
				DbgPrint(("%s - AdjustWakeCapabilities Inferring DeviceD2 !\n",PDX->MDebugName));
			}

			PDC->DeviceD2=TRUE;
			PDC->WakeFromD2=TRUE;
		}
		break;

		case PowerDeviceD3:
		{
			if (PDC->WakeFromD3==0)
			{
				DbgPrint(("%s - AdjustWakeCapabilities Inferring WakeFromD3 !\n",PDX->MDebugName));
			}
		
			PDC->WakeFromD3=TRUE;
		}
		break;
	
		default:
		{
			ASSERT(FALSE);
		}
		break;
	}
}
//-------------------------------------------------------------------------------------------------------
VOID DeregisterAllInterfaces(PGENERIC_EXTENSION PDX)
{
	ASSERT(KeGetCurrentIrql()==PASSIVE_LEVEL);
	
	KeEnterCriticalRegion();
	KeWaitForSingleObject(&PDX->MIfLock,Executive,KernelMode,FALSE,NULL);

	while (IsListEmpty(&PDX->MIfList)==FALSE)
	{
		// For each interface.
		PLIST_ENTRY												List=RemoveHeadList(&PDX->MIfList);
		PINTERFACE_RECORD										IFP=CONTAINING_RECORD(List,INTERFACE_RECORD,MList);

		// !!!!! TENTO CODE som VYHODIL.
		//DeregisterInterface(PDX,IFP);

		// !!!!! Tento CODE az do konca WHILE je jeho nahrada.
		if (IFP->MEnabled!=FALSE)
		{
			(void)IoSetDeviceInterfaceState(&IFP->MLinkName,FALSE);
		}

		RtlFreeUnicodeString(&IFP->MLinkName);
		ExFreePool(IFP);
	}

	KeSetEvent(&PDX->MIfLock,EVENT_INCREMENT,FALSE);
	KeLeaveCriticalRegion();
}
//-------------------------------------------------------------------------------------------------------
VOID DeregisterInterface(PGENERIC_EXTENSION, PINTERFACE_RECORD IFP)
{
	if (IFP->MEnabled!=FALSE)
	{
		(void)IoSetDeviceInterfaceState(&IFP->MLinkName,FALSE);
	}

	RtlFreeUnicodeString(&IFP->MLinkName);
	RemoveEntryList(&IFP->MList);
	ExFreePool(IFP);
}
//-------------------------------------------------------------------------------------------------------
#pragma LOCKEDCODE
VOID EnableAllInterfaces(PGENERIC_EXTENSION PDX, BOOLEAN Enable)
{
	for (PLIST_ENTRY List=PDX->MIfList.Flink;List!=&PDX->MIfList;List=List->Flink)
	{
		// Search for specified interface record.
		PINTERFACE_RECORD										IFP=CONTAINING_RECORD(List,INTERFACE_RECORD,MList);

		if (IFP->MEnabled!=Enable)
		{
			(void)IoSetDeviceInterfaceState(&IFP->MLinkName,Enable);
		}
		
		IFP->MEnabled=Enable;
	}
}
//-------------------------------------------------------------------------------------------------------
PINTERFACE_RECORD FindInterfaceRecord(PGENERIC_EXTENSION PDX, const GUID* GUID)
{
	for (PLIST_ENTRY List=PDX->MIfList.Flink;List!=&PDX->MIfList;List=List->Flink)
	{
		// Search for specified interface record.
		PINTERFACE_RECORD										IFP=CONTAINING_RECORD(List,INTERFACE_RECORD,MList);

		if (IFP->MGUID==*GUID)
		{
			return(IFP);
		}
	}

	return(NULL);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS HandleQueryCapabilities(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_QUERY_CAPABILITIES);

	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);
	PDEVICE_CAPABILITIES										PDC=Stack->Parameters.DeviceCapabilities.Capabilities;

	// Check to be sure we know how to handle this version of the capabilities structure.
	if (PDC->Version<1)
	{
		return(DefaultPnpHandler(PDX,IRP));
	}

	NTSTATUS													Status=ForwardAndWait(PDX,IRP);

	if (NT_SUCCESS(Status)==true)
	{
		// IRP succeeded.
		Stack=IoGetCurrentIrpStackLocation(IRP);
		PDC=Stack->Parameters.DeviceCapabilities.Capabilities;

		if ((PDX->MFlags & GENERIC_SURPRISE_REMOVAL_OK)!=0)
		{
			PDC->SurpriseRemovalOK=TRUE;
		}

		// Compensate for bus driver shortcoming.
		AdjustDeviceCapabilities(PDX,PDC);
		// Save capabilities for whoever needs to see them.
		PDX->MDeviceCaps=*PDC;
		// Flag for GenericGetDeviceCapabilities.
		PDX->MGotCapabilities=TRUE;
		// In case capabilities now allow WAIT_WAKE.
		GenericWakeupControl(PDX,ManageWaitWake);
	}

	return(CompleteRequest(IRP,Status));
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS HandleQueryState(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_QUERY_PNP_DEVICE_STATE);

	// Note that you can't use sizeof in a #if expression, so it's not possible to use conditional compilation to choose between 32 and 64-bit exchanges in the following statement. If the size of a PNP_DEVICE_STATE changes to be bigger than 32 bits, therefore, you have to change this by hand. The ASSERT will alert you to the problem.
	PNP_DEVICE_STATE											Mask=InterlockedExchange((PLONG) &PDX->MPNPStateMask,0);

	ASSERT(sizeof(PNP_DEVICE_STATE)==sizeof(LONG));

	if (Mask!=0)
	{
		// Some status flags have changed.
		// Indicate we've handled this IRP.
		IRP->IoStatus.Status=STATUS_SUCCESS;
		// Clear all changed flags.
		IRP->IoStatus.Information&=~(ULONG_PTR) Mask;
		// Set all flags that were changed to "1".
		IRP->IoStatus.Information|=(PDX->MPNPState & Mask);
	}

	// DDK doc says you handle this IRP on the way down, but TOASTER handles it on the way up. It shouldn't matter, because you're not supposed to overstore the result you find already in IoStatus.Information.
	return(DefaultPnpHandler(PDX,IRP));
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION je zodpovedna za spracovanie MINOR FUNCTION [IRP_MN_DEVICE_USAGE_NOTIFICATION].
// !!! Spracovava NOTIFICATIONS, ktore WINDOWS zasiela do DRIVER. Na zaklade tychto NOTIFICATIONS moze DRIVER menit svoju cinnost.
// !!! Spravidla iba DRIVER obsluhujuce HW DEVICES typu HDD spracovavaju tieto NOTIFICATIONS.
NTSTATUS HandleUsageNotification(PGENERIC_EXTENSION PDX, PIRP IRP)
{
	ASSERT(IoGetCurrentIrpStackLocation(IRP)->MinorFunction==IRP_MN_DEVICE_USAGE_NOTIFICATION);

	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);
	DEVICE_USAGE_NOTIFICATION_TYPE								Type=Stack->Parameters.UsageNotification.Type;
	BOOLEAN														InPath=Stack->Parameters.UsageNotification.InPath;

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): NOTIFICATION_TYPE [%d], IN PATH [%d] !\n",Type,InPath);

	switch(Type)
	{
		// Switch on usage type.
		case DeviceUsageTypeHibernation:
		{
			if ((PDX->MFlags & GENERIC_USAGE_HIBERNATE)==0)
			{
				return(CompleteRequest(IRP,STATUS_UNSUCCESSFUL));
			}

			AdjustSpecialFileCounter(PDX,InPath,&PDX->MNumberHibernateFiles);
			IRP->IoStatus.Status=STATUS_SUCCESS;
		}
		break;

		case DeviceUsageTypePaging:
		{
			if ((PDX->MFlags & GENERIC_USAGE_PAGING)==0)
			{
				return(CompleteRequest(IRP,STATUS_UNSUCCESSFUL));
			}

			if (InPath!=FALSE && PDX->MState!=WORKING)
			{
				// SP-7, per DDK doc.
				return(CompleteRequest(IRP,STATUS_DEVICE_NOT_READY));
			}

			// Guard against reentrance by waiting on evPagingPath, which is a synchronization event that was initialized to the signalled state. Therefore, it will be reset once we get past the wait (SP-7, ver 1.6).
			KeWaitForSingleObject(&PDX->MEventPagingPath,Executive,KernelMode,FALSE,NULL);

			// Add or substract one from the paging path counter. AdjustSpecialFileCounter will also take care of enabling or disabling idle detection.
			AdjustSpecialFileCounter(PDX,InPath,&PDX->MNumberPageFiles);

			// Adjust the power-pagable flag too. (Per AdrianO) we must be careful not to have a non-paged power handler sitting on top of a paged handler, so we only clear DO_POWER_PAGABLE in our completion routine.
			PDEVICE_OBJECT										FDO=PDX->MDeviceObject;

			if (PDX->MNumberPageFiles==0)
			{
				// Resume paging.
				if ((FDO->Flags & DO_POWER_INRUSH)==0)
				{
					FDO->Flags|=DO_POWER_PAGABLE;
				}
			}

			// TODO: Deal with paging of Read, Write, Control requests in minidriver.
			IRP->IoStatus.Status=STATUS_SUCCESS;
		}
		break;

		case DeviceUsageTypeDumpFile:
		{
			if ((PDX->MFlags & GENERIC_USAGE_DUMP)==0)
			{
				return(CompleteRequest(IRP,STATUS_UNSUCCESSFUL));
			}

			AdjustSpecialFileCounter(PDX,InPath,&PDX->MNumberDumpFiles);
			IRP->IoStatus.Status=STATUS_SUCCESS;
		}
		break;
	}

	// Install completion routine so we can recover from a failure and so we can clear DO_POWER_PAGABLE at the right time.
	IoSetCompletionRoutine(IRP,(PIO_COMPLETION_ROUTINE) OnNotificationComplete,PDX,TRUE,TRUE,TRUE);
	IoCopyCurrentIrpStackLocationToNext(IRP);

	return(IoCallDriver(PDX->MLowerDeviceObject,IRP));
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS OnNotificationComplete(PDEVICE_OBJECT FDO, PIRP IRP, PGENERIC_EXTENSION PDX)
{
	if (IRP->PendingReturned!=FALSE)
	{
		IoMarkIrpPending(IRP);
	}

	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);
	DEVICE_USAGE_NOTIFICATION_TYPE								Type=Stack->Parameters.UsageNotification.Type;
	BOOLEAN														InPath=Stack->Parameters.UsageNotification.InPath;

	// If the notification succeeded, and if we're on the path for paging files, be sure we start getting power IRPs at DISPATCH_LEVEL.
	if (NT_SUCCESS(IRP->IoStatus.Status)==true)
	{
		// Notification succeeded.
		if (PDX->MNumberPageFiles!=0)
		{
			FDO->Flags&=~DO_POWER_PAGABLE;
		}
		if (Type==DeviceUsageTypePaging)
		{
			// SP-7.
			KeSetEvent(&PDX->MEventPagingPath,IO_NO_INCREMENT,FALSE);
		}

		return(STATUS_SUCCESS);
	}

	// Somebody underneath us failed this usage notification, so undo the steps we took in the dispatch routine. Notice how we reverse the sense of "inpath" in the following calls to AdjustSpecialFileCounter.
	switch (Type)
	{
		// Switch on usage type.
		case DeviceUsageTypeHibernation:
		{
			AdjustSpecialFileCounter(PDX,!InPath,&PDX->MNumberHibernateFiles);
		}
		break;

		case DeviceUsageTypePaging:
		{
			AdjustSpecialFileCounter(PDX,!InPath,&PDX->MNumberPageFiles);

			if (PDX->MNumberPageFiles==0)
			{
				// Resume paging.
				if ((FDO->Flags & DO_POWER_INRUSH)==0)
				{
					FDO->Flags|=DO_POWER_PAGABLE;
				}
			}
			else
			{
				FDO->Flags&=~DO_POWER_PAGABLE;
			}

			// SP-7.
			KeSetEvent(&PDX->MEventPagingPath,IO_NO_INCREMENT,FALSE);
		}
		break;

		case DeviceUsageTypeDumpFile:
		{
			AdjustSpecialFileCounter(PDX,!InPath,&PDX->MNumberDumpFiles);
		}
		break;
	}

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
VOID ShowResources(IN PCM_PARTIAL_RESOURCE_LIST List)
{
	PCM_PARTIAL_RESOURCE_DESCRIPTOR								Resource=List->PartialDescriptors;
	ULONG														NumberOfResources=List->Count;

	for (ULONG Index=0;Index<NumberOfResources;++Index,++Resource)
	{
		// For each resource.
		ULONG													Type=Resource->Type;
		static char*											Name[]=
		{
			"CmResourceTypeNull",
			"CmResourceTypePort",
			"CmResourceTypeInterrupt",
			"CmResourceTypeMemory",
			"CmResourceTypeDma",
			"CmResourceTypeDeviceSpecific",
			"CmResourceTypeBusNumber",
			"CmResourceTypeDevicePrivate",
			"CmResourceTypeAssignedResource",
			"CmResourceTypeSubAllocateFrom",
		};

		DbgPrint("    Type [%s] !",Type<_countof(Name) ? Name[Type] : "UNKNOWN");

		switch(Type)
		{
			// Select on resource type.
			case CmResourceTypePort:
			case CmResourceTypeMemory:
			{
				DbgPrint(" Start [%8X%8.8lX] Length [%X] !\n",Resource->u.Port.Start.HighPart,Resource->u.Port.Start.LowPart,Resource->u.Port.Length);
			}
			break;
		
			case CmResourceTypeInterrupt:
			{
				DbgPrint("  Level [%X], Vector [%X], Affinity [%I64X] !\n",Resource->u.Interrupt.Level,Resource->u.Interrupt.Vector,Resource->u.Interrupt.Affinity);
			}
			break;
	
			case CmResourceTypeDma:
			{
				DbgPrint("  Channel [%d], Port [%X] !\n",Resource->u.Dma.Channel,Resource->u.Dma.Port);
			}
			break;
		}
	}
}
//-------------------------------------------------------------------------------------------------------