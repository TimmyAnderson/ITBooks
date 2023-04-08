//-------------------------------------------------------------------------------------------------------
// !!! HEADER [Ntddk.h] MUSI BYT PRED HEADER [wdm.h].
#include <Ntddk.h>
#include <wdm.h>
#include <initguid.h>
#include <Ntstrsafe.h>
//-------------------------------------------------------------------------------------------------------
#include "Defines.h"
#include "Driver.h"
#include "GUIDS.h"
#include "MyCSQIRPQueueing.h"
#include "Macros.h"
//-------------------------------------------------------------------------------------------------------
// !!! Nastavi SIMULACIU SOURCE DRIVER.
#define SIMULATION_SOURCE_DRIVER
//-------------------------------------------------------------------------------------------------------
#pragma warning(disable:4127)
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_UNLOAD)
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);
_Function_class_(DRIVER_ADD_DEVICE)
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PDO);
//-------------------------------------------------------------------------------------------------------
NTSTATUS __stdcall StartDevice(PDEVICE_OBJECT DeviceObject, PCM_PARTIAL_RESOURCE_LIST, PCM_PARTIAL_RESOURCE_LIST);
VOID __stdcall StopDevice(IN PDEVICE_OBJECT DeviceObject, BOOLEAN);
VOID __stdcall RemoveDevice(IN PDEVICE_OBJECT DeviceObject);
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_READ)
NTSTATUS DispatchRead(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_WRITE)
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SET_VOLUME_INFORMATION)
NTSTATUS DispatchSetVolumeInformation(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_QUERY_VOLUME_INFORMATION)
NTSTATUS DispatchQueryVolumeInformation(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_QUERY_EA)
NTSTATUS DispatchQueryEA(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SET_EA)
NTSTATUS DispatchSetEA(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CREATE)
NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLOSE)
NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLEANUP)
NTSTATUS DispatchCleanup(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_DEVICE_CONTROL)
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_POWER)
NTSTATUS DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_PNP)
NTSTATUS DispatchPNP(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SYSTEM_CONTROL)
NTSTATUS DispatchWMI(PDEVICE_OBJECT DeviceObject, PIRP IRP);
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_SIMPLE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_1_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_2_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x803,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_3_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x804,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_4_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x805,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_5_FINISHED_SYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x806,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_5_FINISHED_ASYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x807,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_6_FINISHED_SYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x808,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_6_FINISHED_ASYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x809,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_7_FINISHED_SYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x8010,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_7_FINISHED_ASYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x811,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_8_FINISHED_SYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x812,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_8_FINISHED_ASYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x813,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_IO_STACK_LOCATION_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x814,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_GET_DEVICE_OBJECT_POINTER_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x815,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_IRP_QUEUEING_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x816,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CANCEL_SAFE_IRP_QUEUE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x817,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CANCEL_SYNCHRONOUS_IRP_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x818,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CANCEL_ASYNCHRONOUS_IRP_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x819,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_REMOTE_CANCEL_ASYNCHRONOUS_IRP_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x820,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DOUBLE_COMPLETION_ROUTINES_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x821,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYNCHRONOUS_IRP_COMPLETION_ROUTINE_NO_CALL_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x822,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_ASYNCHRONOUS_IRP_COMPLETION_ROUTINE_NO_CALL_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x823,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! Simuluje UKONCENIE IRP po nejakom case, ktory simuluje PROCESSING IRP.
_Function_class_(KSTART_ROUTINE)
void IRPCompleteSimulator(PVOID Parameter)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n"));

	PIRP														IRP=(PIRP) Parameter;
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=2*1000*(-10*1000);

	// !!! POCKAM 2 SEKUNDY.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	IRP->IoStatus.Status=STATUS_SUCCESS;
	IRP->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(IRP,NULL);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!!!!!!! BEFORE IoCompleteRequest() CALLED !\n"));

	// !!! Ukoncim IRP.
	// !!!!! Ak DRIVER dostal IRP z DRIVER VYSSIE v DRIVER STACK musi ho bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
	// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
	IoCompleteRequest(IRP,IO_NO_INCREMENT);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!!!!!!! AFTER IoCompleteRequest() FINISHED !\n"));

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP was COMPLETED by DESTINATION DRIVER !\n"));

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlSimpleTest(PIRP IRP, DEVICE_EXTENSION*, ULONG, ULONG InputBufferLength, ULONG OutputBufferLength, ULONG& Info)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// Alokujem aj miesto pre NULL TERMINATOR.
	SIZE_T														DataFromInputBufferLength=InputBufferLength+sizeof(CHAR);
	CHAR*														DataFromInputBuffer=(CHAR*) ExAllocatePoolWithTag(PagedPool,DataFromInputBufferLength,' FUB');

	if (DataFromInputBuffer!=NULL)
	{
		RtlZeroMemory(DataFromInputBuffer,DataFromInputBufferLength);

		// Do DataFromInputBuffer sa ulozia BYTES z INPUT BUFFER, pricom DataFromInputBuffer ma este o 1 BYTE navyse na ulozenie NULL TERMINATOR.
		// !!!!! FIELD IRP->AssociatedIrp.SystemBuffer obsahuje INPUT aj OUTPUT BUFFER.
		RtlCopyMemory(DataFromInputBuffer,IRP->AssociatedIrp.SystemBuffer,InputBufferLength);

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): InputBuffer [%s] !\n",DataFromInputBuffer));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): MEMORY ALLOCATION FAILED !\n"));
	}

	WCHAR												DataToSendToUserMode[]=L"My name is Timmy Anderson !";
	ULONG												DataToSendToUserModeLength=sizeof(DataToSendToUserMode);
			
	if (OutputBufferLength>=DataToSendToUserModeLength)
	{
		// Do OUTPUT BUFFER sa ulozi STRING.
		// !!!!! FIELD IRP->AssociatedIrp.SystemBuffer obsahuje INPUT aj OUTPUT BUFFER.
		RtlCopyMemory(IRP->AssociatedIrp.SystemBuffer,&DataToSendToUserMode,DataToSendToUserModeLength);
		Info=DataToSendToUserModeLength;
		Status=STATUS_SUCCESS;
	}
	else
	{
		Status=STATUS_BUFFER_TOO_SMALL;
	}

	if (DataFromInputBuffer!=NULL)
	{
		ExFreePoolWithTag(DataFromInputBuffer,' FUB');
		DataFromInputBuffer=NULL;
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario1CompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;
	PIO_STACK_LOCATION											StackLocation=IoGetCurrentIrpStackLocation(InterruptRequestPacket);

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d], CONTROL [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned,StackLocation->Control));

#ifndef SIMULATION_SOURCE_DRIVER
	// !!! Ak OPERATION bola PENDING, tak nastavi EVENT.
	if (InterruptRequestPacket->PendingReturned!=FALSE)
	{
		// !!!!! FUNCTION IoMarkIrpPending() sa moze volat IBA ak DRIVER vracia INU HODNOTU ako 'STATUS_MORE_PROCESSING_REQUIRED'.

		// !!!!! IRP sa oznaci ako PENDING, aby v pripade, ze IRP prislo z IO MANAGER ho IO MANAGER korektne UVOLNIL.
		IoMarkIrpPending(InterruptRequestPacket);
	}
#endif

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], AFTER IoMarkIrpPending() CALLED - PENDING RETURNED [%d], CONTROL [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned,StackLocation->Control));

#ifdef SIMULATION_SOURCE_DRIVER
	// !!!!! Odstranenie IRP je IBA PRETO, ze som ho vytvoril v CURRENT DRIVER. Ak by bolo IRP vytvorene v SOURCE DRIVER, tak ho uvolnit SOURCE DRIVER, alebo IO MANAGER, ak by bol vytvoreny nim.
	// !!!!! Ak sa ODSTRANI IRP, tak je NUTNE vratit VALUE [STATUS_MORE_PROCESSING_REQUIRED], inak by sa WINDOWS pokusil volat COMPLETION ROUTINE PARENT DRIVER, ktory NEEXISTUJE pre IRP, ktore uz bolo UVOLNENE z MEMORY.
	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
#endif

	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP COMPLETED !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=2*1000*(-10*1000);

	// !!!!! POCKAM 2 SEKUND. Toto zdrzanie sluzi na ukazanie, ze je to FUNCTION IoCompletionRoutine(), ktora vyvolava vo svojom CODE COMPLETION ROUTINES.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

#ifdef SIMULATION_SOURCE_DRIVER
	// !!!!! NORMALNE by tu mal byt vrateny 'STATUS_SUCCESS', ale kedze IRP bolo vytvorene v CURRENT DRIVER, tak sa SIMULUJE ODSTRANENIE IRP a vracia sa [STATUS_MORE_PROCESSING_REQUIRED].
	// !!! Vratenie VALUE [STATUS_MORE_PROCESSING_REQUIRED] ZABRANI WINDOWS, aby sa pokusil vyvolat COMPLETION ROUTINE PARENT DRIVER, ktory NEEXISTUJE pre IRP, ktore uz bolo UVOLNENE z MEMORY.
	return(STATUS_MORE_PROCESSING_REQUIRED);
#else
	// !!!!! NORMALNE v SCENARIO 2 sa predpoklada vratenie [STATUS_CONTINUE_COMPLETION] a takisto plati, ze CURRENT DRIVER NESMIE volat IoFreeIrp(), ale toto ma vykonat az SOURCE DRIVER, ktory IRP vytvoril. Ak ho vytvoril IO MANAGER, tak je to IO MANAGER, ktory IRP AUTOMATICKY UKONCI.
	// !!!!! Ak sa vrati [STATUS_CONTINUE_COMPLETION] (je to ALIAS k [STATUS_SUCESS]), tak sa IoFreeIrp() NEVOLAL (inak by doslo k BUG CHECK) a to znamena, ze IRP sa NEUVOLNI. Uvolnil by sa v realnej situacii, keby IRP bol zaslany zo SOURCE DRIVER a nie vytvoreny pre simulaciu v CURRENT DRIVER. Ak by IRP bol vytvoreny v SOURCE DRIVER, potom by SOURCE DRIVER bol zodpovedny za uvolnenie IRP.
	return(STATUS_CONTINUE_COMPLETION);
#endif
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario1Test(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!!!! Emuluje sa IRP akokeby bol zaslany zo SOURCE DRIVER.
		// !!! Vytvori sa IRP, ktory SKONCI ASYNCHRONNE. (IRP_MJ_WRITE sa SIMULUJE ako ASYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));

			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// !!! Kedze po vytvoreni IRP sa IRP odkazuje na -1 poziciu v IO_STACK_LOCATION ARRAY, tak volanim FUNCTION IoGetNextIrpStackLocation() sa ziska POINTER na PRVY IO_STACK_LOCATION v IO_STACK_LOCATION ARRAY.
		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_WRITE;

		// !!!!! Kedze IRP je SIMULOVANY, ze prisiel zo SOURCE DRIVER, tak je nutne POSUNUT STACK LOCATION.
		IoSetNextIrpStackLocation(InterruptRequestPacket);

		// !!! Skopirujem THIS IO_STACK_LOCATION do STACK LOCATION na pozicii pre DRIVER NIZSIE v DRIVER STACK. V tomto pripade je to THIS DRIVER, kedze IRP DRIVER posiela sam do seba.
		IoCopyCurrentIrpStackLocationToNext(InterruptRequestPacket);

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario1CompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
			
			// !!!!! KEDZE uvolnenie LOCK a uvolnenie IRP sa robi v COMPLETION ROUTINE, ktoru vyvolava DRIVER NIZSIE v DRIVER STACK pomocou volania IoCompleteRequest(), tak IRP sa v tomto bloku NESMIE UVOLNIT a podobne sa NESMIE uvolnit ani LOCK, inak by doslo k BUG CHECK.
			/*
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			*/

			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario2CompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	// !!!!! Odstranenie IRP je IBA PRETO, ze som ho vytvoril v CURRENT DRIVER. Ak by bolo IRP vytvorene v SOURCE DRIVER, tak ho uvolnit SOURCE DRIVER, alebo IO MANAGER, ak by bol vytvoreny nim.
	// !!!!! Ak sa ODSTRANI IRP, tak je NUTNE vratit VALUE 'STATUS_MORE_PROCESSING_REQUIRED'.
	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	// !!!!! Uvolnenie LOCK IBA PRETO, ze som zaregistroval COMPLETION ROUTINE ako predpoklada SCENARIO 2. Ak by som COMPLETION ROUTINE NEZAREGISTROVAL, tak by sa LOCK MUSEL UVOLNOVAT uz v DISPATCH ROUTINE.
	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario2Test(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!!!! Emuluje sa IRP akokeby bol zaslany zo SOURCE DRIVER.
		// !!! Vytvori sa IRP, ktory SKONCI ASYNCHRONNE. (IRP_MJ_WRITE sa SIMULUJE ako ASYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));

			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_WRITE;

		// !!!!! Kedze IRP je SIMULOVANY, ze prisiel zo SOURCE DRIVER, tak je nutne POSUNUT IRP.
		IoSetNextIrpStackLocation(InterruptRequestPacket);

		// !!! DESTINATION IO_STACK_LOCATION bude obsahovat CURRENT IO_STACK_LOCATION.
		IoSkipCurrentIrpStackLocation(InterruptRequestPacket);

		// !!! Zaregistruje sa COMPLETION ROUTINE. COMPLETION ROUTINE sa registruje IBA PRETO, aby som v nej mohol UVOLNIT IRP.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario2CompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

			// !!!!! KEDZE uvolnenie LOCK a uvolnenie IRP sa robi v COMPLETION ROUTINE, ktoru vyvolava DRIVER NIZSIE v DRIVER STACK pomocou volania IoCompleteRequest(), tak IRP sa v tomto bloku NESMIE UVOLNIT a podobne sa NESMIE uvolnit ani LOCK, inak by doslo k BUG CHECK.
			/*
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			*/

			break;
		}

		// !!!!! SCENARION 2 predpoklada, ze DRIVER NEREGISTRUJE COMPLETION ROUTINE. V tom pripade TU MUSI BYT RELEASE LOCK volanim FUNCTION IoReleaseRemoveLock().
		// !!!!! Kedze vsak v tejto simulacii sa COMPLETION ROUTINE REGISTRUJE v nej sa RELEASE LOCK UVOLNUJE volanim FUNCTION IoReleaseRemoveLock(), tak nasledujuci CODE je ZAKOMENTOVANY.
		//IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
		//KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario3CompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	// !!!!! Odstranenie IRP je IBA PRETO, ze som ho vytvoril v CURRENT DRIVER. Ak by bolo IRP vytvorene v SOURCE DRIVER, tak ho uvolnit SOURCE DRIVER, alebo IO MANAGER, ak by bol vytvoreny nim.
	// !!!!! Ak sa ODSTRANI IRP, tak je NUTNE vratit VALUE 'STATUS_MORE_PROCESSING_REQUIRED'.
	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario3Test(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!!!! Emuluje sa IRP akokeby bol zaslany zo SOURCE DRIVER.
		// !!! Vytvori sa IRP, ktory SKONCI SYNCHRONNE. (IRP_MJ_READ sa SIMULUJE ako SYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_READ,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));

			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_READ;

		// !!! Zaregistruje sa COMPLETION ROUTINE. COMPLETION ROUTINE sa registruje IBA PRETO, aby som v nej mohol UVOLNIT IRP.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario3CompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

			// !!!!! KEDZE uvolnenie LOCK a uvolnenie IRP sa robi v COMPLETION ROUTINE, ktoru vyvolava DRIVER NIZSIE v DRIVER STACK pomocou volania IoCompleteRequest(), tak IRP sa v tomto bloku NESMIE UVOLNIT a podobne sa NESMIE uvolnit ani LOCK, inak by doslo k BUG CHECK.
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_STARTIO)
void StartIo_Scenario4(PDEVICE_OBJECT, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	// !!!!! EMULUJE sa KONIEC IRP.
	IRP->IoStatus.Status=STATUS_SUCCESS;
	IRP->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(IRP,NULL);

	// !!! Ukoncim IRP.
	// !!!!! Tento CODE by sa mal volat normalne v DPC, ak by som mal REALNY HW.
	// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
	// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
	IoCompleteRequest(IRP,IO_NO_INCREMENT);
}
//-------------------------------------------------------------------------------------------------------
_Requires_lock_held_(_Global_cancel_spin_lock_)
_Function_class_(DRIVER_CANCEL)
_IRQL_raises_(DISPATCH_LEVEL)
void Scenario4CancelRoutine(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) DeviceObject->DeviceExtension;

	// !!! Odstrani IRP z IRP QUEUE.
	CancelRequest(&DeviceExtension->DevQueue,IRP);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario4CompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	/*
	// !!!!! Pri DIRECT IO OPERATIONS je NUTNE odstranit aj MDL.
	PMDL														MDL;
  
	while ((MDL=InterruptRequestPacket->MdlAddress)!=NULL)
    {
		InterruptRequestPacket->MdlAddress=MDL->Next;

		// !!! Je NUTNA iba ak sa vykonal LOCK PAGES pomocou FUNCTION MmProbeAndLockPages().
		//MmUnlockPages(MDL);
		IoFreeMdl(MDL);
    }
	*/
	
	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	// !!!!! Tento CODE by sa mal volat normalne v DPC, ak by som mal REALNY HW.
	// !!!!! Spusti sa vykonavanie dalsieho IRP, ak je nejake v IRP QUEUE.
	StartNextPacket(&DeviceExtension->DevQueue,DeviceExtension->DeviceObject);

	// !!!!! IO MANAGER pri zavolani IoCompleteRequest() vola VSETKY ZAREGISTROVANE COMPLETION ROUTINES pre VSETKY DRIVERS v DRIVER STACK az kym nie su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES, alebo pokym niektora COMPLETION ROUTINE nevrati RETURN VALUE STATUS_MORE_PROCESSING_REQUIRED.
	// !!!!! Je NUTNE hodit hodnotu STATUS_MORE_PROCESSING_REQUIRED - pretoze IRP sa uz UVOLNILO volanim FUNCTION IoFreeIrp() a teda je NEPLATNE. Ak by sa vratila INA HODNOTA, tak IO MANAGER by mohol vyvolat dalsie COMPLETION ROUTINES, ktore pre dane IRP zaregistrovali INE DRIVERS, no kedze IRP je uz UVOLNENE, tak by doslo k BUG CHECK.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario4Test(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(int Index=0;Index<100;Index++)
	{
		for(;;)
		{
			if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
				break;
			}

			PIRP												InterruptRequestPacket=NULL;
			CHAR												Buffer[1024];
			LARGE_INTEGER										Offset;
			IO_STATUS_BLOCK										IRPStatus;

			RtlZeroMemory(Buffer,sizeof(Buffer));
			RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
			Offset.QuadPart=0;

			// !!!!! POZOR. IRP_MJ_QUERY_VOLUME_INFORMATION NIE JE medzi MAJOR FUNCTIONS, ktore FUNCTION IoBuildAsynchronousFsdRequest() podporuje.
			// !!!!! Emuluje sa IRP akokeby bol zaslany zo SOURCE DRIVER.
			// !!! Vytvori sa IRP, ktory SKONCI ASYNCHRONNE. (IRP_MJ_QUERY_VOLUME_INFORMATION sa SIMULUJE ako ASYNCHRONNE vykonavana operacia.)
			if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_QUERY_VOLUME_INFORMATION,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));

				IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
				break;
			}

			// Ziskam IO_STACK_LOCATION na DRIVER NIZSIE v DRIVER STACK.
			// !!! Pri vytvoreni IRP sa INDEX do IO_STACK_LOCATION ARRAY nastavi na hodnotu -1. Zavolanim FUNCTION IoGetNextIrpStackLocation() sa inkrementuje na hodnotu 0 co znamena, ze INDEX ukazuje na PRVY IO_STACK_LOCATION objekt.
			PIO_STACK_LOCATION									StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

			StackLocation->MajorFunction=IRP_MJ_QUERY_VOLUME_INFORMATION;

			// !!!!! EMULUJE sa COMPLETION ROUTINE, ktora bude vykonavat ten CODE, ktory by mala vykonavat DPC, ak by som mal k dispozicii realny HW.
			// !!! Zaregistruje sa COMPLETION ROUTINE.
			// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
			if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario4CompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

				IoFreeIrp(InterruptRequestPacket);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
				IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
				break;
			}

			// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
			if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
				break;
			}

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

			break;
		}
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario5FinishedSynchronouslyCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	/*
	// !!!!! Pri DIRECT IO OPERATIONS je NUTNE odstranit aj MDL.
	PMDL														MDL;
  
	while ((MDL=InterruptRequestPacket->MdlAddress)!=NULL)
    {
		InterruptRequestPacket->MdlAddress=MDL->Next;

		// !!! Je NUTNA iba ak sa vykonal LOCK PAGES pomocou FUNCTION MmProbeAndLockPages().
		//MmUnlockPages(MDL);
		IoFreeMdl(MDL);
    }
	*/
	
	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	// !!!!! IO MANAGER pri zavolani IoCompleteRequest() vola VSETKY ZAREGISTROVANE COMPLETION ROUTINES pre VSETKY DRIVERS v DRIVER STACK az kym nie su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES, alebo pokym niektora COMPLETION ROUTINE nevrati RETURN VALUE STATUS_MORE_PROCESSING_REQUIRED.
	// !!!!! Je NUTNE hodit hodnotu STATUS_MORE_PROCESSING_REQUIRED - pretoze IRP sa uz UVOLNILO volanim FUNCTION IoFreeIrp() a teda je NEPLATNE. Ak by sa vratila INA HODNOTA, tak IO MANAGER by mohol vyvolat dalsie COMPLETION ROUTINES, ktore pre dane IRP zaregistrovali INE DRIVERS, no kedze IRP je uz UVOLNENE, tak by doslo k BUG CHECK.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// !!! ASYNCHRONNE IRP sa mozu vytvarat aj na ARBITRARY THREADS a preto WORKER THREAD NIE JE NUTNE vytvarat, ako je to v SYNCHRONNYCH IRP.
NTSTATUS ProcessIOControlScenario5FinishedSynchronouslyTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!! Vytvori sa IRP, ktory SKONCI SYNCHRONNE. (IRP_MJ_READ sa SIMULUJE ako SYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_READ,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));

			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// Ziskam IO_STACK_LOCATION na DRIVER NIZSIE v DRIVER STACK.
		// !!! Pri vytvoreni IRP sa INDEX do IO_STACK_LOCATION ARRAY nastavi na hodnotu -1. Zavolanim FUNCTION IoGetNextIrpStackLocation() sa inkrementuje na hodnotu 0 co znamena, ze INDEX ukazuje na PRVY IO_STACK_LOCATION objekt.
		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_READ;

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		//IoSetCompletionRoutine(InterruptRequestPacket,Scenario5FinishedSynchronouslyCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE);

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario5FinishedSynchronouslyCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario5FinishedAsynchronouslyCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	/*
	// !!!!! Pri DIRECT IO OPERATIONS je NUTNE odstranit aj MDL.
	PMDL														MDL;
  
	while ((MDL=InterruptRequestPacket->MdlAddress)!=NULL)
    {
		InterruptRequestPacket->MdlAddress=MDL->Next;

		// !!! Je NUTNA iba ak sa vykonal LOCK PAGES pomocou FUNCTION MmProbeAndLockPages().
		//MmUnlockPages(MDL);
		IoFreeMdl(MDL);
    }
	*/

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	// !!!!! IO MANAGER pri zavolani IoCompleteRequest() vola VSETKY ZAREGISTROVANE COMPLETION ROUTINES pre VSETKY DRIVERS v DRIVER STACK az kym nie su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES, alebo pokym niektora COMPLETION ROUTINE nevrati RETURN VALUE STATUS_MORE_PROCESSING_REQUIRED.
	// !!!!! Je NUTNE hodit hodnotu STATUS_MORE_PROCESSING_REQUIRED - pretoze IRP sa uz UVOLNILO volanim FUNCTION IoFreeIrp() a teda je NEPLATNE. Ak by sa vratila INA HODNOTA, tak IO MANAGER by mohol vyvolat dalsie COMPLETION ROUTINES, ktore pre dane IRP zaregistrovali INE DRIVERS, no kedze IRP je uz UVOLNENE, tak by doslo k BUG CHECK.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// !!! ASYNCHRONNE IRP sa mozu vytvarat aj na ARBITRARY THREADS a preto WORKER THREAD NIE JE NUTNE vytvarat, ako je to v SYNCHRONNYCH IRP.
NTSTATUS ProcessIOControlScenario5FinishedAsynchronouslyTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!! Vytvori sa IRP, ktory SKONCI ASYNCHRONNE. (IRP_MJ_WRITE sa SIMULUJE ako ASYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));

			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// Ziskam IO_STACK_LOCATION na DRIVER NIZSIE v DRIVER STACK.
		// !!! Pri vytvoreni IRP sa INDEX do IO_STACK_LOCATION ARRAY nastavi na hodnotu -1. Zavolanim FUNCTION IoGetNextIrpStackLocation() sa inkrementuje na hodnotu 0 co znamena, ze INDEX ukazuje na PRVY IO_STACK_LOCATION objekt.
		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_WRITE;

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		//IoSetCompletionRoutine(InterruptRequestPacket,Scenario5FinishedAsynchronouslyCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE);

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario5FinishedAsynchronouslyCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! SYNCHRONNE IRP sa MUSIA vytvarat na NON-ARBITRARY THREADS.
_Function_class_(KSTART_ROUTINE)
void Scenario6FinishedSynchronouslyThreadFunction(PVOID Parameter)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Parameter;
	bool														RemoveLock=false;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		RemoveLock=true;

		PIRP													InterruptRequestPacket=NULL;
		KEVENT													Event;

		// KERNEL EVENT sluzi ako synchronizacny EVENT, ktory bude SIGNALIZED, ak je spracovavanie IRP je skoncene.
		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!! Vytvori sa IRP, ktory SKONCI SYNCHRONNE. (IRP_MJ_WRITE sa SIMULUJE ako SYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildSynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&Event,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildSynchronousFsdRequest() FAILED [%X] !\n",Status));
			// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM.
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

			// !!!!! IRP je uvolnene DESTINATION DRIVER. Ak by sa tu zavolala FUNCTION IoCompleteRequest(), dojde k BUG CHECK.
			// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
			// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
			//IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

			// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM.
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		// Vycka sa na SINGALIZACIU KEVENT.
		if (NT_SUCCESS(Status=KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));

			// !!!!! IRP je uvolnene DESTINATION DRIVER. Ak by sa tu zavolala FUNCTION IoCompleteRequest(), dojde k BUG CHECK.
			// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
			// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
			//IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

			// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM.
			break;
		}

		// Vypisem STATUS skoncenej IO OPERATION.
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X] !\n",IRPStatus.Status));

		break;
	}

	if (RemoveLock==true)
	{
		IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario6FinishedSynchronouslyTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,Scenario6FinishedSynchronouslyThreadFunction,DeviceExtension))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n"));

		PKTHREAD												Thread;

		if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread,NULL))==true)
		{
			// Cakam kym sa THREAD NESKONCI.
			KeWaitForSingleObject(Thread,Executive,KernelMode,FALSE,NULL);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

			ObDereferenceObject(Thread);
			Thread=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ObReferenceObjectByHandle() FAILED [%X] !\n",Status));
		}

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! SYNCHRONNE IRP sa MUSIA vytvarat na NON-ARBITRARY THREADS.
_Function_class_(KSTART_ROUTINE)
void Scenario6FinishedAsynchronouslyThreadFunction(PVOID Parameter)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Parameter;
	bool														RemoveLock=false;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		RemoveLock=true;

		PIRP													InterruptRequestPacket=NULL;
		KEVENT													Event;

		// KERNEL EVENT sluzi ako synchronizacny EVENT, ktory bude SIGNALIZED, ak je spracovavanie IRP je skoncene.
		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!! Vytvori sa IRP, ktory SKONCI SYNCHRONNE. (IRP_MJ_WRITE sa SIMULUJE ako ASYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildSynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&Event,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildSynchronousFsdRequest() FAILED [%X] !\n",Status));
			// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM.
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

			// !!!!! IRP je uvolnene DESTINATION DRIVER. Ak by sa tu zavolala FUNCTION IoCompleteRequest(), dojde k BUG CHECK.
			// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
			// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
			//IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		// Vycka sa na SINGALIZACIU KEVENT.
		if (NT_SUCCESS(Status=KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));

			// !!!!! IRP je uvolnene DESTINATION DRIVER. Ak by sa tu zavolala FUNCTION IoCompleteRequest(), dojde k BUG CHECK.
			// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
			// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
			//IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

			// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM.
			break;
		}

		// Vypisem STATUS skoncenej IO OPERATION.
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X] !\n",IRPStatus.Status));

		break;
	}

	if (RemoveLock==true)
	{
		IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario6FinishedAsynchronouslyTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,Scenario6FinishedAsynchronouslyThreadFunction,DeviceExtension))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n"));

		PKTHREAD												Thread;

		if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread,NULL))==true)
		{
			// Cakam kym sa THREAD NESKONCI.
			KeWaitForSingleObject(Thread,Executive,KernelMode,FALSE,NULL);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

			ObDereferenceObject(Thread);
			Thread=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ObReferenceObjectByHandle() FAILED [%X] !\n",Status));
		}

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario7FinishedSynchronouslyCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	PKEVENT														Event=(PKEVENT) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	// !!! Ak OPERATION bola PENDING, tak nastavi EVENT.
	if (InterruptRequestPacket->PendingReturned!=FALSE)
	{
		KeSetEvent(Event,IO_NO_INCREMENT,FALSE);
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP COMPLETED !\n"));

	// !!!!! IO MANAGER pri zavolani IoCompleteRequest() vola VSETKY ZAREGISTROVANE COMPLETION ROUTINES pre VSETKY DRIVERS v DRIVER STACK az kym nie su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES, alebo pokym niektora COMPLETION ROUTINE nevrati RETURN VALUE STATUS_MORE_PROCESSING_REQUIRED.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! SYNCHRONNY PASS DOWN IRP sa MUSI vytvarat na NON-ARBITRARY THREADS.
_Function_class_(KSTART_ROUTINE)
void Scenario7FinishedSynchronouslyThreadFunction(PVOID Parameter)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		DEVICE_EXTENSION*										DeviceExtension=(DEVICE_EXTENSION*) Parameter;

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!! Vytvori sa IRP, ktory SKONCI SYNCHRONNE. (IRP_MJ_READ sa SIMULUJE ako SYNCHRONNE vykonavana operacia.)
		// !!!!! Toto je iba SIMULOVANY IRP, ktory by normalne bol zaslany zo SOURCE DRIVER.
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_READ,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			break;
		}

		// !!!!! Kedze IRP je SIMULOVANY, ze prisiel zo SOURCE DRIVER, tak je nutne POSUNUT IRP.
		IoSetNextIrpStackLocation(InterruptRequestPacket);

		KEVENT													Event;

		// KERNEL EVENT sluzi ako synchronizacny EVENT, ktory bude SIGNALIZED, ak je spracovavanie IRP je skoncene.
		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		// !!! Skopirujem THIS IO_STACK_LOCATION do STACK LOCATION na pozicii pre DRIVER NIZSIE v DRIVER STACK. V tomto pripade je to THIS DRIVER, kedze IRP DRIVER posiela sam do seba.
		IoCopyCurrentIrpStackLocationToNext(InterruptRequestPacket);

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		//IoSetCompletionRoutine(InterruptRequestPacket,Scenario7FinishedSynchronouslyCompletionRoutine,&Event,TRUE,TRUE,TRUE);

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario7FinishedSynchronouslyCompletionRoutine,&Event,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		// !!!!! Kedze DESTINATION DRIVER je THIS DRIVER, tak sa IPR zasle do THIS DRIVER.
		// !!!!! IRP sa zasle do THIS DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
			// !!!!! IRP sa MUSI uvolnit, pretoze COMPLETION ROUTINE NEOBSAHUJE volanie FUNCTION IoFreeIrp().
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		// !!! Na EVENT sa caka IBA pri PENDING STAVE.
		if (Status==STATUS_PENDING)
		{
			// Vycka sa na SINGALIZACIU KEVENT.
			if (NT_SUCCESS(Status=KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));
				// !!!!! IRP sa MUSI uvolnit, pretoze COMPLETION ROUTINE NEOBSAHUJE volanie FUNCTION IoFreeIrp().
				IoFreeIrp(InterruptRequestPacket);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
				break;
			}
		}

		// !!!!! UVOLNIM IRP, kedze pre simulaciu bol vytvoreny v TOMTO DRIVER. Normalne by bol vytvoreny v SOURCE DRIVER a ten by ho aj UVOLNIL.
		IoFreeIrp(InterruptRequestPacket);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

		// Vypisem STATUS skoncenej IO OPERATION.
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X] !\n",IRPStatus.Status));

		break;
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario7FinishedSynchronouslyTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,Scenario7FinishedSynchronouslyThreadFunction,DeviceExtension))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n"));

		PKTHREAD												Thread;

		if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread,NULL))==true)
		{
			// Cakam kym sa THREAD NESKONCI.
			KeWaitForSingleObject(Thread,Executive,KernelMode,FALSE,NULL);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

			ObDereferenceObject(Thread);
			Thread=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ObReferenceObjectByHandle() FAILED [%X] !\n",Status));
		}

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario7FinishedAsynchronouslyCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	PKEVENT														Event=(PKEVENT) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	// !!! Ak OPERATION bola PENDING, tak nastavi EVENT.
	if (InterruptRequestPacket->PendingReturned!=FALSE)
	{
		KeSetEvent(Event,IO_NO_INCREMENT,FALSE);
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP COMPLETED !\n"));

	// !!!!! IO MANAGER pri zavolani IoCompleteRequest() vola VSETKY ZAREGISTROVANE COMPLETION ROUTINES pre VSETKY DRIVERS v DRIVER STACK az kym nie su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES, alebo pokym niektora COMPLETION ROUTINE nevrati RETURN VALUE STATUS_MORE_PROCESSING_REQUIRED.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! SYNCHRONNY PASS DOWN IRP sa MUSI vytvarat na NON-ARBITRARY THREADS.
_Function_class_(KSTART_ROUTINE)
void Scenario7FinishedAsynchronouslyThreadFunction(PVOID Parameter)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		DEVICE_EXTENSION*										DeviceExtension=(DEVICE_EXTENSION*) Parameter;

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!! Vytvori sa IRP, ktory SKONCI ASYNCHRONNE. (IRP_MJ_WRITE sa SIMULUJE ako ASYNCHRONNE vykonavana operacia.)
		// !!!!! Toto je iba SIMULOVANY IRP, ktory by normalne bol zaslany zo SOURCE DRIVER.
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			break;
		}

		// !!!!! Kedze IRP je SIMULOVANY, ze prisiel zo SOURCE DRIVER, tak je nutne POSUNUT IRP.
		IoSetNextIrpStackLocation(InterruptRequestPacket);

		KEVENT													Event;

		// KERNEL EVENT sluzi ako synchronizacny EVENT, ktory bude SIGNALIZED, ak je spracovavanie IRP je skoncene.
		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		// !!! Skopirujem THIS IO_STACK_LOCATION do STACK LOCATION na pozicii pre DRIVER NIZSIE v DRIVER STACK. V tomto pripade je to THIS DRIVER, kedze IRP DRIVER posiela sam do seba.
		IoCopyCurrentIrpStackLocationToNext(InterruptRequestPacket);

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		//IoSetCompletionRoutine(InterruptRequestPacket,Scenario7FinishedAsynchronouslyCompletionRoutine,&Event,TRUE,TRUE,TRUE);

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario7FinishedAsynchronouslyCompletionRoutine,&Event,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		// !!!!! Kedze DESTINATION DRIVER je THIS DRIVER, tak sa IPR zasle do THIS DRIVER.
		// !!!!! IRP sa zasle do THIS DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
			// !!!!! IRP sa MUSI uvolnit, pretoze COMPLETION ROUTINE NEOBSAHUJE volanie FUNCTION IoFreeIrp().
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		// !!! Na EVENT sa caka IBA pri PENDING STAVE.
		if (Status==STATUS_PENDING)
		{
			// Vycka sa na SINGALIZACIU KEVENT.
			if (NT_SUCCESS(Status=KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));
				// !!!!! IRP sa MUSI uvolnit, pretoze COMPLETION ROUTINE NEOBSAHUJE volanie FUNCTION IoFreeIrp().
				IoFreeIrp(InterruptRequestPacket);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
				break;
			}
		}

		// !!!!! UVOLNIM IRP, kedze pre simulaciu bol vytvoreny v TOMTO DRIVER. Normalne by bol vytvoreny v SOURCE DRIVER a ten by ho aj UVOLNIL.
		IoFreeIrp(InterruptRequestPacket);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

		// Vypisem STATUS skoncenej IO OPERATION.
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X] !\n",IRPStatus.Status));

		break;
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario7FinishedAsynchronouslyTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,Scenario7FinishedAsynchronouslyThreadFunction,DeviceExtension))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n"));

		PKTHREAD												Thread;

		if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread,NULL))==true)
		{
			// Cakam kym sa THREAD NESKONCI.
			KeWaitForSingleObject(Thread,Executive,KernelMode,FALSE,NULL);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

			ObDereferenceObject(Thread);
			Thread=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ObReferenceObjectByHandle() FAILED [%X] !\n",Status));
		}

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario8FinishedSynchronouslyCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	PKEVENT														Event=(PKEVENT) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	// !!! Ak OPERATION bola PENDING, tak nastavi EVENT.
	if (InterruptRequestPacket->PendingReturned!=FALSE)
	{
		KeSetEvent(Event,IO_NO_INCREMENT,FALSE);
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP COMPLETED !\n"));

	// !!!!! IO MANAGER pri zavolani IoCompleteRequest() vola VSETKY ZAREGISTROVANE COMPLETION ROUTINES pre VSETKY DRIVERS v DRIVER STACK az kym nie su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES, alebo pokym niektora COMPLETION ROUTINE nevrati RETURN VALUE STATUS_MORE_PROCESSING_REQUIRED.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void Scenario8FinishedSynchronouslyThreadFunction(PVOID Parameter)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Parameter;
	bool														RemoveLock=false;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		RemoveLock=true;

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!! Vytvori sa IRP, ktory SKONCI SYNCHRONNE. (IRP_MJ_READ sa SIMULUJE ako SYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_READ,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			break;
		}

		// Ziskam IO_STACK_LOCATION na DRIVER NIZSIE v DRIVER STACK.
		// !!! Pri vytvoreni IRP sa INDEX do IO_STACK_LOCATION ARRAY nastavi na hodnotu -1. Zavolanim FUNCTION IoGetNextIrpStackLocation() sa inkrementuje na hodnotu 0 co znamena, ze INDEX ukazuje na PRVY IO_STACK_LOCATION objekt.
		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_READ;

		KEVENT													Event;

		// KERNEL EVENT sluzi ako synchronizacny EVENT, ktory bude SIGNALIZED, ak je spracovavanie IRP je skoncene.
		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario8FinishedSynchronouslyCompletionRoutine,&Event,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
			// !!!!! IRP sa MUSI uvolnit, pretoze COMPLETION ROUTINE NEOBSAHUJE volanie FUNCTION IoFreeIrp().
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		// !!! Na EVENT sa caka IBA pri PENDING STAVE.
		if (Status==STATUS_PENDING)
		{
			// Vycka sa na SINGALIZACIU KEVENT.
			if (NT_SUCCESS(Status=KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));
				// !!!!! IRP sa MUSI uvolnit, pretoze COMPLETION ROUTINE NEOBSAHUJE volanie FUNCTION IoFreeIrp().
				IoFreeIrp(InterruptRequestPacket);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
				break;
			}
		}

		// !!!!! UVOLNIM IRP, kedze pre simulaciu bol vytvoreny v TOMTO DRIVER. Normalne by bol vytvoreny v SOURCE DRIVER a ten by ho aj UVOLNIL.
		IoFreeIrp(InterruptRequestPacket);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

		// Vypisem STATUS skoncenej IO OPERATION.
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X] !\n",IRPStatus.Status));

		break;
	}

	if (RemoveLock==true)
	{
		IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario8FinishedSynchronouslyTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,Scenario8FinishedSynchronouslyThreadFunction,DeviceExtension))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n"));

		PKTHREAD												Thread;

		if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread,NULL))==true)
		{
			// Cakam kym sa THREAD NESKONCI.
			KeWaitForSingleObject(Thread,Executive,KernelMode,FALSE,NULL);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

			ObDereferenceObject(Thread);
			Thread=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ObReferenceObjectByHandle() FAILED [%X] !\n",Status));
		}

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS Scenario8FinishedAsynchronouslyCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	PKEVENT														Event=(PKEVENT) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	// !!! Ak OPERATION bola PENDING, tak nastavi EVENT.
	if (InterruptRequestPacket->PendingReturned!=FALSE)
	{
		KeSetEvent(Event,IO_NO_INCREMENT,FALSE);
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP COMPLETED !\n"));

	// !!!!! IO MANAGER pri zavolani IoCompleteRequest() vola VSETKY ZAREGISTROVANE COMPLETION ROUTINES pre VSETKY DRIVERS v DRIVER STACK az kym nie su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES, alebo pokym niektora COMPLETION ROUTINE nevrati RETURN VALUE STATUS_MORE_PROCESSING_REQUIRED.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSTART_ROUTINE)
void Scenario8FinishedAsynchronouslyThreadFunction(PVOID Parameter)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Parameter;
	bool														RemoveLock=false;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		RemoveLock=true;

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!! Vytvori sa IRP, ktory SKONCI ASYNCHRONNE. (IRP_MJ_WRITE sa SIMULUJE ako ASYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			break;
		}

		// Ziskam IO_STACK_LOCATION na DRIVER NIZSIE v DRIVER STACK.
		// !!! Pri vytvoreni IRP sa INDEX do IO_STACK_LOCATION ARRAY nastavi na hodnotu -1. Zavolanim FUNCTION IoGetNextIrpStackLocation() sa inkrementuje na hodnotu 0 co znamena, ze INDEX ukazuje na PRVY IO_STACK_LOCATION objekt.
		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_WRITE;

		KEVENT													Event;

		// KERNEL EVENT sluzi ako synchronizacny EVENT, ktory bude SIGNALIZED, ak je spracovavanie IRP je skoncene.
		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,Scenario8FinishedAsynchronouslyCompletionRoutine,&Event,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
			// !!!!! IRP sa MUSI uvolnit, pretoze COMPLETION ROUTINE NEOBSAHUJE volanie FUNCTION IoFreeIrp().
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		// !!! Na EVENT sa caka IBA pri PENDING STAVE.
		if (Status==STATUS_PENDING)
		{
			// Vycka sa na SINGALIZACIU KEVENT.
			if (NT_SUCCESS(Status=KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));
				IoFreeIrp(InterruptRequestPacket);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
				break;
			}
		}

		// !!!!! UVOLNIM IRP, kedze pre simulaciu bol vytvoreny v TOMTO DRIVER. Normalne by bol vytvoreny v SOURCE DRIVER a ten by ho aj UVOLNIL.
		IoFreeIrp(InterruptRequestPacket);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

		// Vypisem STATUS skoncenej IO OPERATION.
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X] !\n",IRPStatus.Status));

		break;
	}

	if (RemoveLock==true)
	{
		IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlScenario8FinishedAsynchronouslyTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,Scenario8FinishedAsynchronouslyThreadFunction,DeviceExtension))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n"));

		PKTHREAD												Thread;

		if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread,NULL))==true)
		{
			// Cakam kym sa THREAD NESKONCI.
			KeWaitForSingleObject(Thread,Executive,KernelMode,FALSE,NULL);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

			ObDereferenceObject(Thread);
			Thread=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ObReferenceObjectByHandle() FAILED [%X] !\n",Status));
		}

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlIoStackLocationTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			break;
		}

		// !!! Velkost IO_STACK_LOCATION ARRAY je rovna DEVICE_OBJECT.StackSize.
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): StackSize [%d], IRP [%p], IPR SIZE [%I64d], IO_STACK_LOCATION SIZE [%I64d] !\n",DeviceExtension->DeviceObject->StackSize,InterruptRequestPacket,sizeof(IRP),sizeof(IO_STACK_LOCATION)));

		// !!!!! Na zaciatku ukazuje CURRENT IO_STACK_LOCATION na NEPLATNU POZICIU a preto je potrebne ho presunut na NASLEDUJUCU IO_STACK_LOCATION volanim FUNCTION IoSetNextIrpStackLocation().
		for (int Index=0;Index<DeviceExtension->DeviceObject->StackSize;Index++)
		{
			IoSetNextIrpStackLocation(InterruptRequestPacket);

			PIO_STACK_LOCATION									CurrentStackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

			CurrentStackLocation->MajorFunction=IRP_MJ_WRITE;

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CurrentStackLocation [%p] !\n",CurrentStackLocation));
		}

		IoFreeIrp(InterruptRequestPacket);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS GetDeviceObjectPointerCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	/*
	// !!!!! Pri DIRECT IO OPERATIONS je NUTNE odstranit aj MDL.
	PMDL														MDL;
  
	while ((MDL=InterruptRequestPacket->MdlAddress)!=NULL)
    {
		InterruptRequestPacket->MdlAddress=MDL->Next;

		// !!! Je NUTNA iba ak sa vykonal LOCK PAGES pomocou FUNCTION MmProbeAndLockPages().
		//MmUnlockPages(MDL);
		IoFreeMdl(MDL);
    }
	*/
	
	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	// !!!!! IO MANAGER pri zavolani IoCompleteRequest() vola VSETKY ZAREGISTROVANE COMPLETION ROUTINES pre VSETKY DRIVERS v DRIVER STACK az kym nie su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES, alebo pokym niektora COMPLETION ROUTINE nevrati RETURN VALUE STATUS_MORE_PROCESSING_REQUIRED.
	// !!!!! Je NUTNE hodit hodnotu STATUS_MORE_PROCESSING_REQUIRED - pretoze IRP sa uz UVOLNILO volanim FUNCTION IoFreeIrp() a teda je NEPLATNE. Ak by sa vratila INA HODNOTA, tak IO MANAGER by mohol vyvolat dalsie COMPLETION ROUTINES, ktore pre dane IRP zaregistrovali INE DRIVERS, no kedze IRP je uz UVOLNENE, tak by doslo k BUG CHECK.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// !!! ASYNCHRONNE IRP sa mozu vytvarat aj na ARBITRARY THREADS a preto WORKER THREAD NIE JE NUTNE vytvarat, ako je to v SYNCHRONNYCH IRP.
NTSTATUS ProcessIOControlGetDeviceObjectPointerTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		PDEVICE_OBJECT											DestinationDeviceObject;
		PFILE_OBJECT											DestinationFileObject;
		UNICODE_STRING											DeviceName;

		RtlInitUnicodeString(&DeviceName, L"\\DosDevices\\" LDRIVERNAME);

		// !!!!! ALTERNATIVNY SPOSOB ziskania DEVICE_OBJECT do ktoreho sa bude smerovat IRP.
		// !!!!! POINTERS DestinationFileObject a DestinationDeviceObject referuju na TEN ISTY KERNEL OBJECT a preto pri uvolnovani sa NESMU uvolnovat OBE, ale iba jeden z nich, inak dojde k BUG CHECK.
		if (NT_SUCCESS(Status=IoGetDeviceObjectPointer(&DeviceName,FILE_ALL_ACCESS,&DestinationFileObject,&DestinationDeviceObject))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoGetDeviceObjectPointer() FAILED [%X] !\n",Status));

			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!! Vytvori sa IRP, ktory SKONCI SYNCHRONNE. (IRP_MJ_READ sa SIMULUJE ako SYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE,DestinationDeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));

			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			// ????? Finalne uvolnenie FILE_OBJECT. FILE_OBJECT vrateny IoGetDeviceObjectPointer() by sa mal uvolnit, akurat si nie som isty, ci to robim na spravnom mieste.
			ObDereferenceObject(DestinationFileObject);
			break;
		}

		// Ziskam IO_STACK_LOCATION na DRIVER NIZSIE v DRIVER STACK.
		// !!! Pri vytvoreni IRP sa INDEX do IO_STACK_LOCATION ARRAY nastavi na hodnotu -1. Zavolanim FUNCTION IoGetNextIrpStackLocation() sa inkrementuje na hodnotu 0 co znamena, ze INDEX ukazuje na PRVY IO_STACK_LOCATION objekt.
		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_WRITE;
		
		// !!! Zvysi INTERNY COUNTER KERNEL OBJECT.
		// !!!!! Pri ziskani DEVICE_OBJECT cez IoGetDeviceObjectPointer() sa ODPORUCA INKREMENTOVAT FILE_OBJECT, aby ZABRANILO PREDCASNEMU odstraneniu DRIVER (napriklad cez PNP) a DISPATCH ROUTINE na tomto DRIVER sa vyvolat.
		ObReferenceObject(DestinationFileObject);

		// !!!!! Pri ziskani DEVICE_OBJECT cez IoGetDeviceObjectPointer() sa ODPORUCA nastavit FILE_OBJECT na IO_STACK_LOCATION, keby ho DRIVERS nizsie v DRIVER STACK potrebovali.
		StackLocation->FileObject=DestinationFileObject;

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DestinationDeviceObject,InterruptRequestPacket,GetDeviceObjectPointerCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

			// !!! Znizi INTERNY COUNTER KERNEL OBJECT.
			// !!!!! Pri ziskanie DEVICE_OBJECT cez IoGetDeviceObjectPointer() sa ODPORUCA INKREMENTOVAT FILE_OBJECT, aby ZABRANILO PREDCASNEMU odstraneniu DRIVER (napriklad cez PNP) a DISPATCH ROUTINE na tomto DRIVER sa vyvolat.
			ObDereferenceObject(DestinationFileObject);

			// ????? Finalne uvolnenie FILE_OBJECT. FILE_OBJECT vrateny IoGetDeviceObjectPointer() by sa mal uvolnit, akurat si nie som isty, ci to robim na spravnom mieste.
			ObDereferenceObject(DestinationFileObject);

			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DestinationDeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

			// !!! Znizi INTERNY COUNTER KERNEL OBJECT.
			// !!!!! Pri ziskanie DEVICE_OBJECT cez IoGetDeviceObjectPointer() sa ODPORUCA INKREMENTOVAT FILE_OBJECT, aby ZABRANILO PREDCASNEMU odstraneniu DRIVER (napriklad cez PNP) a DISPATCH ROUTINE na tomto DRIVER sa vyvolat.
			ObDereferenceObject(DestinationFileObject);

			// ????? Finalne uvolnenie FILE_OBJECT. FILE_OBJECT vrateny IoGetDeviceObjectPointer() by sa mal uvolnit, akurat si nie som isty, ci to robim na spravnom mieste.
			ObDereferenceObject(DestinationFileObject);
			break;
		}

		// !!! Znizi INTERNY COUNTER KERNEL OBJECT.
		// !!!!! Pri ziskanie DEVICE_OBJECT cez IoGetDeviceObjectPointer() sa ODPORUCA INKREMENTOVAT FILE_OBJECT, aby ZABRANILO PREDCASNEMU odstraneniu DRIVER (napriklad cez PNP) a DISPATCH ROUTINE na tomto DRIVER sa vyvolat.
		ObDereferenceObject(DestinationFileObject);

		// ????? Finalne uvolnenie FILE_OBJECT. FILE_OBJECT vrateny IoGetDeviceObjectPointer() by sa mal uvolnit, akurat si nie som isty, ci to robim na spravnom mieste.
		ObDereferenceObject(DestinationFileObject);

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void StartIo_Emulator(PDEVICE_OBJECT, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	// !!!!! EMULUJE sa KONIEC IRP.
	IRP->IoStatus.Status=STATUS_SUCCESS;
	IRP->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(IRP,NULL);

	// !!! Ukoncim IRP.
	// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
	// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
	IoCompleteRequest(IRP,IO_NO_INCREMENT);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION reprezentuje jednoduchu implementaciu IRP QUEUING.
// !!! FUNCTION je volana, ked sa ma IRP vlozit do QUEUE.
void SimpleStartPacket(PDEVICE_EXTENSION DeviceExtension, PIRP IRPToProcess)
{
	KIRQL														OriginalIRQL;

	// !!! Kedze IRP mozu byt zasielane PARALELNE, je NUTNE ziskat LOCK pre QUEUE, aby 2 THREADS nepristupovali PARALALNE ku QUEUE, ktora je SHARED.
	KeAcquireSpinLock(&DeviceExtension->IRPQueueLock,&OriginalIRQL);

	// Zisti sa ci QUEUE je prazdna.
	if (DeviceExtension->DeviceBusy!=FALSE)
    {
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP will be ADDED to QUEUE !\n"));

		// !!! Kedze QUEUE nie je PRAZDNA, tak sa IRP vlozi do QUEUE.
		InsertTailList(&DeviceExtension->IRPQueue,&IRPToProcess->Tail.Overlay.ListEntry);

		// Uvolni sa QUEUE LOCK a zaroven sa znizi IRQL na povodnu hodnotu.
		KeReleaseSpinLock(&DeviceExtension->IRPQueueLock,OriginalIRQL);
    }
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP will be IMMEDIATELY EXECUTED !\n"));

		// !!! DRIVER si poznaci, ze je BUSY, kedze sa spracovana novy IRP.
		DeviceExtension->DeviceBusy=TRUE;

		// !!!!! Uvolni sa QUEUE LOCK a zaroven sa PONECHA IRQL==DISPATCH_LEVEL, pretoze StartIo() sa MUSI vykonavat v IRQL==DISPATCH_LEVEL.
		KeReleaseSpinLock(&DeviceExtension->IRPQueueLock,DISPATCH_LEVEL);

		// !!! Tato FUNCTION je EMULACIA StartIo(), ktoru by mal DRIVER implementovat.
		// !!!!! Kedze v QUEUE nebol ziaden IRP, tak sa novy IRP OKAMZITE VYKONA.
		StartIo_Emulator(DeviceExtension->DeviceObject,IRPToProcess);

		// IRQL sa znizi na povodnu hodnotu.
		KeLowerIrql(OriginalIRQL);
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION reprezentuje jednoduchu implementaciu IRP QUEUING.
// !!! FUNCTION je volana, ked sa UKONCIL PREDCHADZAJUCI IRP a ma sa spracovat DALSI IRP z QUEUE.
void SimpleStartNextPacket(PDEVICE_EXTENSION DeviceExtension)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	KIRQL														OriginalIRQL;

	// !!! Kedze IRP mozu byt zasielane PARALELNE, je NUTNE ziskat LOCK pre QUEUE, aby 2 THREADS nepristupovali PARALALNE ku QUEUE, ktora je SHARED.
	KeAcquireSpinLock(&DeviceExtension->IRPQueueLock,&OriginalIRQL);

	// Zisti sa ci QUEUE je prazdna.
	if (IsListEmpty(&DeviceExtension->IRPQueue)!=FALSE)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP QUEUE is EMPTY !\n"));

		// !!! Kedze QUEUE je PRAZDNA, uvolni sa priznak o blokovani DRIVER.
		DeviceExtension->DeviceBusy=FALSE;

		// Uvolni sa QUEUE LOCK a zaroven sa znizi IRQL na povodnu hodnotu.
		KeReleaseSpinLock(&DeviceExtension->IRPQueueLock,OriginalIRQL);
	}
	else
    {
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): NEXT IRP from QUEUE will be IMMEDIATELY EXECUTED !\n"));

		// !!! Kedze QUEUE NIE JE PRAZDNA, vytiahne sa dalsia IRP z QUEUE.
		PLIST_ENTRY												EntryFromQueue=RemoveHeadList(&DeviceExtension->IRPQueue);

		// !!!!! Kedze s QUEUE sa dalej nepracuje je mozne UVOLNI QUEUE LOCK.
		KeReleaseSpinLock(&DeviceExtension->IRPQueueLock,DISPATCH_LEVEL);
    
		// !!! Z PLIST_ENTRY (obsahuje ho IRP) sa ziska POINTER na IRP.
		PIRP													IRPFromQueue=CONTAINING_RECORD(EntryFromQueue,IRP,Tail.Overlay.ListEntry);

		// !!! Tato FUNCTION je EMULACIA StartIo(), ktoru by mal DRIVER implementovat.
		// !!!!! Kedze v PRECHADZAJUCI IRP uz bol spracovany a v QUEUE je DALSIE IRP, tak sa tento novy IRP vybrany z QUEUE OKAMZITE VYKONA.
		StartIo_Emulator(DeviceExtension->DeviceObject,IRPFromQueue);

		// IRQL sa znizi na povodnu hodnotu.
		KeLowerIrql(OriginalIRQL);
    }
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS IRPQueueingCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	/*
	// !!!!! Pri DIRECT IO OPERATIONS je NUTNE odstranit aj MDL.
	PMDL														MDL;
  
	while ((MDL=InterruptRequestPacket->MdlAddress)!=NULL)
    {
		InterruptRequestPacket->MdlAddress=MDL->Next;

		// !!! Je NUTNA iba ak sa vykonal LOCK PAGES pomocou FUNCTION MmProbeAndLockPages().
		//MmUnlockPages(MDL);
		IoFreeMdl(MDL);
    }
	*/
	
	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	// !!!!! Spusti sa vykonavanie dalsieho IRP, ak je nejake v IRP QUEUE.
	SimpleStartNextPacket(DeviceExtension);

	// !!!!! IO MANAGER pri zavolani IoCompleteRequest() vola VSETKY ZAREGISTROVANE COMPLETION ROUTINES pre VSETKY DRIVERS v DRIVER STACK az kym nie su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES, alebo pokym niektora COMPLETION ROUTINE nevrati RETURN VALUE STATUS_MORE_PROCESSING_REQUIRED.
	// !!!!! Je NUTNE hodit hodnotu STATUS_MORE_PROCESSING_REQUIRED - pretoze IRP sa uz UVOLNILO volanim FUNCTION IoFreeIrp() a teda je NEPLATNE. Ak by sa vratila INA HODNOTA, tak IO MANAGER by mohol vyvolat dalsie COMPLETION ROUTINES, ktore pre dane IRP zaregistrovali INE DRIVERS, no kedze IRP je uz UVOLNENE, tak by doslo k BUG CHECK.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlIRPQueueingTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(int Index=0;Index<100;Index++)
	{
		for(;;)
		{
			if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
				break;
			}

			PIRP												InterruptRequestPacket=NULL;
			CHAR												Buffer[1024];
			LARGE_INTEGER										Offset;
			IO_STATUS_BLOCK										IRPStatus;

			RtlZeroMemory(Buffer,sizeof(Buffer));
			RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
			Offset.QuadPart=0;

			// !!!!! POZOR. IRP_MJ_SET_VOLUME_INFORMATION NIE JE medzi MAJOR FUNCTIONS, ktore FUNCTION IoBuildAsynchronousFsdRequest() podporuje.
			// !!! Vytvori sa IRP, ktory SKONCI SYNCHRONNE. (IRP_MJ_SET_VOLUME_INFORMATION sa SIMULUJE ako SYNCHRONNE vykonavana operacia.)
			if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_SET_VOLUME_INFORMATION,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));

				IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
				break;
			}

			// Ziskam IO_STACK_LOCATION na DRIVER NIZSIE v DRIVER STACK.
			// !!! Pri vytvoreni IRP sa INDEX do IO_STACK_LOCATION ARRAY nastavi na hodnotu -1. Zavolanim FUNCTION IoGetNextIrpStackLocation() sa inkrementuje na hodnotu 0 co znamena, ze INDEX ukazuje na PRVY IO_STACK_LOCATION objekt.
			PIO_STACK_LOCATION									StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

			StackLocation->MajorFunction=IRP_MJ_SET_VOLUME_INFORMATION;

			// !!! Zaregistruje sa COMPLETION ROUTINE.
			//IoSetCompletionRoutine(InterruptRequestPacket,Scenario5FinishedSynchronouslyCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE);

			// !!! Zaregistruje sa COMPLETION ROUTINE.
			// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
			if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,IRPQueueingCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

				IoFreeIrp(InterruptRequestPacket);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
				IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
				break;
			}

			// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
			if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

				// !!!!! KEDZE uvolnenie LOCK a uvolnenie IRP sa robi v COMPLETION ROUTINE, ktoru vyvolava DRIVER NIZSIE v DRIVER STACK pomocou volania IoCompleteRequest(), tak IRP sa v tomto bloku NESMIE UVOLNIT a podobne sa NESMIE uvolnit ani LOCK, inak by doslo k BUG CHECK.
				//IoFreeIrp(InterruptRequestPacket);
				//KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
				//IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
				//KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
				break;
			}

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

			break;
		}
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma code_seg()
NTSTATUS ProcessIOControlCancelSafeIRPQueueTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	const int													COUNT=3;
	CHAR														Buffer[COUNT][1024];
	IO_STATUS_BLOCK												IRPStatus[COUNT];

	RtlZeroMemory(Buffer,sizeof(Buffer));
	RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));

	PIRP														InterruptRequestPackets[COUNT];

	for(int Index=0;Index<COUNT;Index++)
	{
		KEVENT													Event;
		LARGE_INTEGER											Offset;

		Offset.QuadPart=0;

		// KERNEL EVENT sluzi ako synchronizacny EVENT, ktory bude SIGNALIZED, ak je spracovavanie IRP je skoncene.
		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		if ((InterruptRequestPackets[Index]=IoBuildAsynchronousFsdRequest(IRP_MJ_READ,DeviceExtension->DeviceObject,Buffer[Index],_countof(Buffer[Index]),&Offset,&IRPStatus[Index]))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			Index--;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() SUCCEEDED !\n"));
		}
	}

	for(int Index=0;Index<COUNT;Index++)
	{
		// Simuluje sa vlozenie IRP do CANCEL SAFE IRP QUEUE.
		IoCsqInsertIrpEx(&DeviceExtension->CancelSafeIRPQueue,InterruptRequestPackets[Index],NULL,NULL);
	}

	for(int Index=0;Index<COUNT;Index++)
	{
		// Simuluje sa vybratie IRP do CANCEL SAFE IRP QUEUE.
		IoCsqRemoveNextIrp(&DeviceExtension->CancelSafeIRPQueue,NULL);
	}

	for(int Index=0;Index<COUNT;Index++)
	{
		IoFreeIrp(InterruptRequestPackets[Index]);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoFreeIrp() SUCCEEDED !\n"));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS CancelSynchronousIRPCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	KEVENT*														Event=(KEVENT*) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	// !!! Ak OPERATION bola PENDING, tak nastavi EVENT.
	// !!!!! Je to preto, lebo ak IRP skonci OKAMZITE v DISPATCH ROUTINE, tak CODE v CancelSynchronousIRPThreadFunction() na EVENT NECAKA. Caka nan iba ak IoCompleteRequest() vrati STATUS_PENDING.
	if (InterruptRequestPacket->PendingReturned!=FALSE)
	{
		// !!!!! Signalizuje sa EVENT na ktory caka FUNCTION CancelSynchronousIRPThreadFunction().
		KeSetEvent(Event,IO_NO_INCREMENT,FALSE);
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP COMPLETED !\n"));

	// !!!!! KEDZE COMLETION ROUTINE vrati 'STATUS_MORE_PROCESSING_REQUIRED', tak DRIVER NIZSIE v DRIVER STACK NESPOSOBI UVOLNENIE IRP z MEMORY.
	// !!!!! Kvoli RACE-CONDITION je NUTNE vracat hodnotu 'STATUS_MORE_PROCESSING_REQUIRED'. Vtedy SYNCHRONNE IRP NEBUDE uvolnene z MEMORY az kym IoCompleteRequest() nie je volany ESTE RAZ.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! SYNCHRONNE IRP sa MUSIA vytvarat na NON-ARBITRARY THREADS.
_Function_class_(KSTART_ROUTINE)
void CancelSynchronousIRPThreadFunction(PVOID Parameter)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Parameter;
	bool														RemoveLock=false;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		RemoveLock=true;

		PIRP													InterruptRequestPacket=NULL;
		KEVENT													Event;

		// KERNEL EVENT sluzi ako synchronizacny EVENT, ktory bude SIGNALIZED, ak je spracovavanie IRP je skoncene.
		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;
		
		// !!! Vytvori sa IRP, ktory SKONCI SYNCHRONNE o 2 SEKUNDACH. (IRP_MJ_WRITE sa SIMULUJE ako SYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildSynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&Event,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildSynchronousFsdRequest() FAILED [%X] !\n",Status));
			// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM pri skonceni THREADU.
			break;
		}

		// !!! Zaregistruje sa COMPLETION ROUTINE, aby DRIVER NIZSIE v DRIVER STACK NEMOHOL PREDCASNE UVOLNIT IRP.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,CancelSynchronousIRPCompletionRoutine,&Event,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

			// !!!!! Pri ERROR je NUTNE UKONCIT IRP volanim FUNCTION IoCompleteRequest().
			// !!!!! COMPLETION ROUTINE sa vsak NEVYVOLA, pretoze ta sa vola IBA z DRIVERS NIZSIE v DRIVER STACK.
			// !!!!! Kedze sa COMPLETION ROUTINE NEVYVOLA a nevrati v RETURN VALUE 'STATUS_MORE_PROCESSING_REQUIRED' tak, IRP je OKAMZITE UVOLNENE z MEMORY cez IO MANAGER.
			// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
			// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
			IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

			// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM pri skonceni THREADU.
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

			// !!!!! Kedze IRP bol zaslany do DRIVER NIZSIE v DRIVER STACK, tak tento DRIVER musi zavolat IoCompleteRequest().
			// !!!!! Avsak, kedze COMPLETION ROUTINE v CURRENT DRIVER vracia 'STATUS_MORE_PROCESSING_REQUIRED', vyzera to, ze IoCompleteRequest() je treba volat este raz.
			// !!!!! Toto je SPECIALITA pre CANCELLATION SYNCHRONNYCH IRP. Pri ASYNCHRONNYCH IRP toto nie je potrebne a sposobi to BUG CHECK.
			// !!!!! COMPLETION ROUTINE sa vsak NEVYVOLA, pretoze ta sa vola IBA z DRIVERS NIZSIE v DRIVER STACK.
			// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
			// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
			IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

			// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM pri skonceni THREADU.
			break;
		}
		
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		LARGE_INTEGER												Timeout;

		Timeout.QuadPart=1*1000*(-10*1000);

		Status=KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,&Timeout);

		// !!!!! SIMULUJE sa cakanie 1 SEKUNDU na skoncenie IRP. Ak sa NESKONCI IRP, tak sa spusti IRP CANCELLATION.
		if (Status==STATUS_TIMEOUT)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP will be CANCELLED !\n"));

			// !!!!! Teraz je vykonanie IRP CANCELLATION BEZPECNE.
			BOOLEAN												CancelResult=IoCancelIrp(InterruptRequestPacket);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! Waiting for IRP COMPLETION, CancelResult [%d] !\n",CancelResult));

			// !!!!! Pocka sa na UKONCENIE IRP.
			if (NT_SUCCESS(Status=KeWaitForSingleObject(&Event,Executive,KernelMode,FALSE,NULL))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));

				// !!!!! Ked IRP nebol COMPLETED pri chybe, dochadzalo k DEADLOCK.
				// !!!!! Kedze COMPLETION ROUTINE ZABRANILA IRP v ukonceni (aby DRIVER NIZSIE v DRIVER STACK PREDCASNE NEUVOLNIL IRP), tak je IRP nutne ESTE RAZ UVOLNIT, aby IO MANAGER zavola IoFreeIrp().
				// !!!!! COMPLETION ROUTINE sa vsak NEVYVOLA, pretoze ta sa vola IBA z DRIVERS NIZSIE v DRIVER STACK.
				// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
				// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
				IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

				// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM pri skonceni THREADU.
				break;
			}
		}
		else if (NT_SUCCESS(Status)==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));

			// !!!!! Ked IRP nebol COMPLETED pri chybe, dochadzalo k DEADLOCK.
			// !!!!! Kedze COMPLETION ROUTINE ZABRANILA IRP v ukonceni (aby DRIVER NIZSIE v DRIVER STACK PREDCASNE NEUVOLNIL IRP), tak je IRP nutne ESTE RAZ UVOLNIT, aby IO MANAGER zavola IoFreeIrp().
			// !!!!! COMPLETION ROUTINE sa vsak NEVYVOLA, pretoze ta sa vola IBA z DRIVERS NIZSIE v DRIVER STACK.
			// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
			// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
			IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

			// !!! SYNCHRONNE IRP NIE JE POTREBNE UVOLNIT, lebo sa uvolnuje AUTOMATICKY IO MANAGEROM pri skonceni THREADU.
			break;
		}

		// !!!!! Kedze COMPLETION ROUTINE ZABRANILA IRP v ukonceni (aby DRIVER NIZSIE v DRIVER STACK PREDCASNE NEUVOLNIL IRP), tak je IRP nutne ESTE RAZ UVOLNIT, aby IO MANAGER zavola IoFreeIrp().
		// !!!!! COMPLETION ROUTINE sa vsak NEVYVOLA, pretoze ta sa vola IBA z DRIVERS NIZSIE v DRIVER STACK.
		// !!!!! Kedze tato COMPLETION ROUTINE sa vola na NAJVYSSOM IO_STACK_LOCATION, tak uz NEVYVOLA COMPLETION ROUTINE a kedze ta nemoze vratit 'STATUS_MORE_PROCESSING_REQUIRED', tak IRP sa UVOLNI.
		// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
		// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
		IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

		// Vypisem STATUS skoncenej IO OPERATION.
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X] !\n",IRPStatus.Status));

		break;
	}

	if (RemoveLock==true)
	{
		IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RELEASE LOCK REMOVED !\n"));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlCancelSynchronousIRPTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,CancelSynchronousIRPThreadFunction,DeviceExtension))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n"));

		PKTHREAD												Thread;

		if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandle,THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Thread,NULL))==true)
		{
			// Cakam kym sa THREAD NESKONCI.
			KeWaitForSingleObject(Thread,Executive,KernelMode,FALSE,NULL);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

			ObDereferenceObject(Thread);
			Thread=NULL;
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ObReferenceObjectByHandle() FAILED [%X] !\n",Status));
		}

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS CancelAsynchronousIRPCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	// !!!!! Staci ak ASPON 1 CONDITION je naplnena, aby sa uvolnil IRP a RELEASE LOCK.
	if (InterlockedExchangePointer(&DeviceExtension->CurrentIRP,NULL)!=NULL || InterlockedExchange(&DeviceExtension->CancelFlag,1)!=0)
	{
		IoFreeIrp(InterruptRequestPacket);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
		IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

		InterlockedExchangePointer(&DeviceExtension->CurrentIRP,NULL);
		DeviceExtension->CancelFlag=0;
		
		KeSetEvent(&DeviceExtension->SingleCallEvent,IO_NO_INCREMENT,FALSE);
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
	}

	// !!!!! Kedze sa IRP moze UVOLNIT je NUTNE vratit VALUE 'STATUS_MORE_PROCESSING_REQUIRED'.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
VOID CancelAsynchronousIRPCancelIRPAfter1Second(DEVICE_EXTENSION* DeviceExtension)
{
	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1*1000*(-10*1000);

	// !!! POCKAM SEKUNDU.
	KeDelayExecutionThread(KernelMode,FALSE,&Timeout);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Trying to CANCEL IRP !\n"));

	PIRP														InterruptRequestPacket=(PIRP) InterlockedExchangePointer(&DeviceExtension->CurrentIRP,NULL);

	// !!!!! OBE CONDITIONS MUSIA BYT NAPLNENE, aby sa uvolnil IRP a RELEASE LOCK.
	if (InterruptRequestPacket!=NULL)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CANCELLING IRP !\n"));

		// !!!!! Teraz je CANCELLATION IRP BEZPECNE.
		IoCancelIrp(InterruptRequestPacket);

		if (InterlockedExchange(&DeviceExtension->CancelFlag,1)!=0)
		{
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

			InterlockedExchangePointer(&DeviceExtension->CurrentIRP,NULL);
			DeviceExtension->CancelFlag=0;

			KeSetEvent(&DeviceExtension->SingleCallEvent,IO_NO_INCREMENT,FALSE);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
		}
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Kedze sa jedna iba o simulaciu, FUNCTION predpoklada, ze v danom case sa zavola IBA RAZ. To znaci, ze sa FUNCTION NEZAVOLA OPATOVNE SKOR, nez povodne volanie tejto FUNCTION SKONCILO.
// !!!!! Ak sa CODE spusti VIACKRAT PARALALNE, moze dojst k DEADLOCK ci BUG CHECK.
NTSTATUS ProcessIOControlCancelAsynchronousIRPTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		// !!!!! Sluzi na to, aby CODE NEBOL vyvolany VIAC ako 1 KRAT.
		if (NT_SUCCESS(Status=KeWaitForSingleObject(&DeviceExtension->SingleCallEvent,Executive,KernelMode,FALSE,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));
			break;
		}

		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X], REMOVE LOCK COUNT [%d] !\n",Status,DeviceExtension->RemoveLock.MUsage));
			KeSetEvent(&DeviceExtension->SingleCallEvent,IO_NO_INCREMENT,FALSE);
			break;
		}

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!!!! Emuluje sa IRP akokeby bol zaslany zo SOURCE DRIVER.
		// !!! Vytvori sa IRP, ktory SKONCI ASYNCHRONNE. (IRP_MJ_WRITE sa SIMULUJE ako ASYNCHRONNE vykonavana operacia.)
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			KeSetEvent(&DeviceExtension->SingleCallEvent,IO_NO_INCREMENT,FALSE);
			break;
		}

		// !!!!! Inicializuje sa DEVICE_EXTENSION.
		InterlockedExchangePointer(&DeviceExtension->CurrentIRP,InterruptRequestPacket);
		DeviceExtension->CancelFlag=0;

		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_WRITE;

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,CancelAsynchronousIRPCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			InterlockedExchangePointer(&DeviceExtension->CurrentIRP,NULL);
			DeviceExtension->CancelFlag=0;
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			KeSetEvent(&DeviceExtension->SingleCallEvent,IO_NO_INCREMENT,FALSE);
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X], REMOVE LOCK COUNT [%d] !\n",Status,DeviceExtension->RemoveLock.MUsage));
			return(Status);
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		CancelAsynchronousIRPCancelIRPAfter1Second(DeviceExtension);

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
VOID RemoteCancelAsynchronousIRPCancelIRPAfter1Second(DEVICE_EXTENSION* DeviceExtension)
{
	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1*1000*(-10*1000);

	// !!! POCKAM SEKUNDU.
	KeDelayExecutionThread(KernelMode,FALSE,&Timeout);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Trying to CANCEL IRP !\n"));

	PIRP														InterruptRequestPacket=(PIRP) InterlockedExchangePointer(&DeviceExtension->CurrentIRP,NULL);

	// !!!!! OBE CONDITIONS MUSIA BYT NAPLNENE, aby sa uvolnil IRP a RELEASE LOCK.
	if (InterruptRequestPacket!=NULL)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CANCELLING IRP !\n"));

		// !!!!! Teraz je CANCELLATION IRP BEZPECNE.
		IoCancelIrp(InterruptRequestPacket);

		if (InterlockedExchange(&DeviceExtension->CancelFlag,1)!=0)
		{
			// !!!!! IRP sa NEUVOLNUJE v CURRENT DRIVER ale v SOURCE DRIVER. CURRENT DRIVER iba sposobi ukoncenie IRP.
			// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
			// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
			IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP COMPLETED !\n"));
		}
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS QueryEACompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	// !!! Ak OPERATION bola PENDING, tak nastavi EVENT.
	if (InterruptRequestPacket->PendingReturned!=FALSE)
	{
		// !!!!! IRP sa oznaci ako PENDING, aby v pripade, ze IRP prislo z IO MANAGER ho IO MANAGER korektne UVOLNIL.
		// !!!!! Ak za v COMPLETION ROUTINE zavola FUNCTION IoMarkIrpPending(), potom COMPLETION ROUTINE MUSI vracat hodnotu [STATUS_CONTINUE_COMPLETION], resp. jej ALIAS [STATUS_SUCCESS].
		IoMarkIrpPending(InterruptRequestPacket);
	}

	// !!!!! Staci ak ASPON 1 CONDITION je naplnena, aby sa uvolnil IRP a RELEASE LOCK.
	if (InterlockedExchangePointer(&DeviceExtension->CurrentIRP,NULL)!=NULL || InterlockedExchange(&DeviceExtension->CancelFlag,1)!=0)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP will be RELEASED !\n"));

		// !!!!! Umozni sa UKONCENIE IRP v SOURCE DRIVER.
		return(STATUS_CONTINUE_COMPLETION);
	}

	return(STATUS_CONTINUE_COMPLETION);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_QUERY_EA)
NTSTATUS DispatchQueryEA(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,InterruptRequestPacket));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	for(;;)
	{
		// !!!!! Inicializuje sa DEVICE_EXTENSION.
		InterlockedExchangePointer(&DeviceExtension->CurrentIRP,InterruptRequestPacket);
		DeviceExtension->CancelFlag=0;

		IoCopyCurrentIrpStackLocationToNext(InterruptRequestPacket);

		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_WRITE;

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,QueryEACompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

			InterlockedExchangePointer(&DeviceExtension->CurrentIRP,NULL);

			return(CompleteRequest(InterruptRequestPacket,Status));
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

			InterlockedExchangePointer(&DeviceExtension->CurrentIRP,NULL);

			// !!!!! Aj ked pri ERROR MUSI DRIVER VZDY IRP UKONCIT volanim FUNCTION IoCompleteRequest(), tak tu sa UZ NESMIE VYKONAT, pretoze sa volal iny DRIVER a TENTO DRIVER je zodpovedny za volanie IoCompleteRequest().
			return(Status);
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		RemoteCancelAsynchronousIRPCancelIRPAfter1Second(DeviceExtension);

		Status=STATUS_PENDING;

		break;
	}

	// !!!!! IRP je NUTNE nastavit na PENDING.
	IoMarkIrpPending(InterruptRequestPacket);

	return(STATUS_PENDING);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS CompleteRemoteCancelAsynchronousIRPCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned));

	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	KeSetEvent(&DeviceExtension->SingleCallEvent,IO_NO_INCREMENT,FALSE);

	// !!!!! Kedze sa IRP moze UVOLNIT je NUTNE vratit VALUE 'STATUS_MORE_PROCESSING_REQUIRED'.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Kedze sa jedna iba o simulaciu, FUNCTION predpoklada, ze v danom case sa zavola IBA RAZ. To znaci, ze sa FUNCTION NEZAVOLA OPATOVNE SKOR, nez povodne volanie tejto FUNCTION SKONCILO.
NTSTATUS ProcessIOControlRemoteCancelAsynchronousIRPTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		// !!!!! Sluzi na to, aby CODE NEBOL vyvolany VIAC ako 1 KRAT.
		if (NT_SUCCESS(Status=KeWaitForSingleObject(&DeviceExtension->SingleCallEvent,Executive,KernelMode,FALSE,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));
			break;
		}

		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			KeSetEvent(&DeviceExtension->SingleCallEvent,IO_NO_INCREMENT,FALSE);
			break;
		}

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!!!! POZOR. IRP_MJ_QUERY_EA NIE JE medzi MAJOR FUNCTIONS, ktore FUNCTION IoBuildAsynchronousFsdRequest() podporuje.
		// !!!!! Emuluje sa IRP akokeby bol zaslany zo SOURCE DRIVER.
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_QUERY_EA,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			KeSetEvent(&DeviceExtension->SingleCallEvent,IO_NO_INCREMENT,FALSE);
			break;
		}

		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

		StackLocation->MajorFunction=IRP_MJ_QUERY_EA;

		// !!! Zaregistruje sa COMPLETION ROUTINE.
		// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit IO_STACK_LOCATION pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT IO_STACK_LOCATION a ak by sa napriklad IO_STACK_LOCATION pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT IO_STACK LOCATION.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,CompleteRemoteCancelAsynchronousIRPCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			KeSetEvent(&DeviceExtension->SingleCallEvent,IO_NO_INCREMENT,FALSE);
			break;
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
			return(Status);
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINES MUSIA predpokladat, ze MOZU byt vyvolane aj na DISPATCH_LEVEL a preto NESMU sposobit PAGE FAULT, ani volat FUNCTIONS, ktore na DISPATCH_LEVEL NEMOZE byt vyvolane.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS SecondaryDoubleCompletionRoutineCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	// !!!!! EXTREMNE DOLEZITE je PROPAGOVAT FLAG 'SL_PENDING_RETURNED' do PARENT DRIVER v DRIVER STACK.
	if (InterruptRequestPacket->PendingReturned!=FALSE)
	{
		// !!!!! V CURRENT IO_STACK_LOCATION sa nastavi FLAG IO_STACK_LOCATION.Control|=SL_PENDING_RETURNED.
		// !!!!! Ak za v COMPLETION ROUTINE zavola FUNCTION IoMarkIrpPending(), potom COMPLETION ROUTINE MUSI vracat hodnotu [STATUS_CONTINUE_COMPLETION], resp. jej ALIAS [STATUS_SUCCESS].
		IoMarkIrpPending(InterruptRequestPacket);
	}

	// !!! Ziskam IO_STACK_LOCATION DRIVER NIZSIE v DRIVER STACK, ktory ukoncil svoju cinnost a zavolal tuto COMPLETION ROUTINE.
	PIO_STACK_LOCATION											StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);
	
	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] and MAJOR FUNCTION [%X] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned,StackLocation->MajorFunction));

	return(STATUS_CONTINUE_COMPLETION);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SET_EA)
NTSTATUS DispatchSetEA(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,InterruptRequestPacket));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	for(;;)
	{
		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);
		UCHAR													MajorFunction=IRP_MJ_WRITE;

		StackLocation->MajorFunction=MajorFunction;

		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,SecondaryDoubleCompletionRoutineCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));

			// !!!!! Pri ERROR MUSI DRIVER VZDY IRP UKONCIT volanim FUNCTION IoCompleteRequest().
			return(CompleteRequest(InterruptRequestPacket,Status));
		}

		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		// !!!!! FUNCTION IoCallDriver() ako RETURN VALUE vracia bud RETURN VALUE DISPATCH ROUTINE, alebo STATUS_PENDING. VALUE STATUS_PENDING MOZE byt vratena AJ KED DISPATCH ROUTINE vratila ERROR VALUE, pokial sa este SCHEDULED COMPLETION ROUTINES nestihli vyvolat.
		// !!!!! Ak by DISPATCH ROUTINE pre IRP_MJ_WRITE vrati ERROR CODE, tak ESTE STALE moze IoCallDriver() vratit STATUS_PENDING. K tomu dojde vtedy, ked IRP malo zaregistrovane COMPLETION ROUTINES a tieto sa este NESTIHLI VYKONAT.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

			// !!!!! Aj ked pri ERROR MUSI DRIVER VZDY IRP UKONCIT volanim FUNCTION IoCompleteRequest(), tak tu sa UZ NESMIE VYKONAT, pretoze sa volal iny DRIVER a TENTO DRIVER je zodpovedny za volanie IoCompleteRequest().
			return(Status);
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] and MAJOR FUNCTION [%X] !\n",Status,MajorFunction));

			return(Status);
		}
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINE pre PRIMARNY DRIVER, ktory musi uvolnit ASYNCHRONNE IRP.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS PrimaryDoubleCompletionRoutineCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID Context)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) Context;

	// !!! Ziskam IO_STACK_LOCATION DRIVER NIZSIE v DRIVER STACK, ktory ukoncil svoju cinnost a zavolal tuto COMPLETION ROUTINE.
	PIO_STACK_LOCATION											StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);
	
	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] and MAJOR FUNCTION [%X] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned,StackLocation->MajorFunction));

	// Uvolni IRP.
	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	// Uvolni REMOVE LOCK.
	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));

	// !!!!! Kedze sa IRP UVOLNIL je NUTNE vratit VALUE 'STATUS_MORE_PROCESSING_REQUIRED', inak by doslo k BUG CHECK.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// Simuluje sa vytvorenie IRP, ktore bude zaslane do 2 NIZSICH DRIVERS. Demonstruje ako korektne zaregistrovat a implementovat COMPLETION ROUTINES.
// !!! IO CONTROL ROUTINE, ktory vytvara IRP.
NTSTATUS ProcessIOControlDoubleCompletionRoutineTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		// Ziska sa REMOVE LOCK, aby zabranilo predcasnemu uvolneniu DRIVER.
		if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
			break;
		}

		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!!!! POZOR. IRP_MJ_SET_EA NIE JE medzi MAJOR FUNCTIONS, ktore FUNCTION IoBuildAsynchronousFsdRequest() podporuje.
		// !!!!! Vytvori IRP, simulujuc akokeby bol zaslany zo SOURCE DRIVER.
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_SET_EA,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			// Uvolni REMOVE LOCK.
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);
		UCHAR													MajorFunction=IRP_MJ_SET_EA;

		StackLocation->MajorFunction=MajorFunction;

		// !!!!! Ak sa COMPLETION ROUTINE USPESNE ZAREGISTRUJE DISPATCH ROUTINE MUSI zavolat IoCallDriver(), inak dojde k MEMORY LEAK.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,PrimaryDoubleCompletionRoutineCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			// Uvolni IRP.
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			// Uvolni REMOVE LOCK.
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		// !!!!! Ak sa COMPLETION ROUTINE USPESNE ZAREGISTRUJE DISPATCH ROUTINE MUSI zavolat IoCallDriver(), inak dojde k MEMORY LEAK.
		// !!!!! IRP sa zasle do CURRENT DRIVER - teda sam do seba.
		if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));

			// !!!!! KEDZE uvolnenie LOCK a uvolnenie IRP sa robi v COMPLETION ROUTINE, ktoru vyvolava DRIVER NIZSIE v DRIVER STACK pomocou volania IoCompleteRequest(), tak IRP sa v tomto bloku NESMIE UVOLNIT a podobne sa NESMIE uvolnit ani LOCK, inak by doslo k BUG CHECK.
			//IoFreeIrp(InterruptRequestPacket);
			//KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			//IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);
			//KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED, REMOVE LOCK COUNT [%d] !\n",DeviceExtension->RemoveLock.MUsage));
			break;
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] and MAJOR FUNCTION [%X] !\n",Status,MajorFunction));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINE pre PRIMARNY DRIVER, ktory musi uvolnit ASYNCHRONNE IRP.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS SynchronousIRPCompletionRoutineNoCallCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	// !!! Ziskam IO_STACK_LOCATION DRIVER NIZSIE v DRIVER STACK, ktory ukoncil svoju cinnost a zavolal tuto COMPLETION ROUTINE.
	PIO_STACK_LOCATION											StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);
	
	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] and MAJOR FUNCTION [%X] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned,StackLocation->MajorFunction));

	// !!!!! Kedze IRP je SYNCHRONNE a NEBOLO UVOLNENE volanim IoFreeIrp(), je NUTNE vratit STATUS_SUCCESS, inak by sa IRP NEUKONCILO.
	// !!!!! Ak by sa vratila RETURN VALUE 'STATUS_MORE_PROCESSING_REQUIRED', tak by IO MANAGER NEUVOLNIL IRP, az pokym by sa ZNOVA nevolala FUNCTION IoCompleteReqeust().
	return(STATUS_CONTINUE_COMPLETION);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlSynchronousIRPCompletionRoutineNoCallTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		KEVENT													Event;

		KeInitializeEvent(&Event,NotificationEvent,FALSE);

		if ((InterruptRequestPacket=IoBuildSynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&Event,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildSynchronousFsdRequest() FAILED [%X] !\n",Status));
			break;
		}

		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);
		UCHAR													MajorFunction=IRP_MJ_WRITE;

		StackLocation->MajorFunction=MajorFunction;

		// !!!!! Ak sa COMPLETION ROUTINE USPESNE ZAREGISTRUJE DISPATCH ROUTINE MUSI zavolat IoCallDriver(), inak dojde k MEMORY LEAK.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,SynchronousIRPCompletionRoutineNoCallCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			// Uvolni IRP.
			// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
			// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
			IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		// !!!!! Ak sa tato FUNCTION ZAVOLA, tak sa zavola aj COMPLETION ROUTINE pri volani IoCompleteRequest().
		IoSetNextIrpStackLocation(InterruptRequestPacket);

		// !!!!! Kedze sa IoCallDriver() NEVOLA, tak FUNCTION sposobi MEMORY LEAK, pretoze po zaregistrovani COMPLETION ROUTINE je NUTNE volat FUNCTION IoCallDriver().

		// !!!!! Ak sa ZAKOMENTOVALO volanie FUNCTION IoSetNextIrpStackLocation(), tak sa COMPLETION ROUTINE NEZAVOLA, pretoze vyssie registrovana COMPLETION ROUTINE bola zaregistrovana pre IO_STACK_LOCATION zodpovedajuci DRIVER NIZSIE v DRIVER STACK a ted kedze sa NEVYVOLAL, tak sa ani COMPLETION ROUTINE NEZAVOLA.
		// !!!!! POZOR. Ked sa COMPLETION ROUTINE NEZAVOLA v ktorej sa uvolnuje IRP tak, pri odinstalacii DRIVER hodi VERIFIER BUG CHECK, pretoze sa nie vsetky MEMORY POOLS odstranili.
		// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
		// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
		IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP was COMPLETED by DESTINATION DRIVER !\n"));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS AsynchronousIRPCompletionRoutineNoCallCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql()));

	// !!! Ziskam IO_STACK_LOCATION DRIVER NIZSIE v DRIVER STACK, ktory ukoncil svoju cinnost a zavolal tuto COMPLETION ROUTINE.
	PIO_STACK_LOCATION											StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);
	
	// Vypisem STATUS skoncenej IO OPERATION.
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] and MAJOR FUNCTION [%X] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned,StackLocation->MajorFunction));

	// Uvolni IRP.
	IoFreeIrp(InterruptRequestPacket);
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));

	// !!!!! Kedze sa IRP UVOLNIL je NUTNE vratit VALUE 'STATUS_MORE_PROCESSING_REQUIRED', inak by doslo k BUG CHECK.
	// !!! Kedze COMPLETION ROUTINE vratila RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED] NESMIE volat FUNCTION IoMarkIrpRequest().
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlAsynchronousIRPCompletionRoutineNoCallTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[1024];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_WRITE,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
			break;
		}

		PIO_STACK_LOCATION										StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);
		UCHAR													MajorFunction=IRP_MJ_WRITE;

		StackLocation->MajorFunction=MajorFunction;

		// !!!!! Ak sa COMPLETION ROUTINE USPESNE ZAREGISTRUJE DISPATCH ROUTINE MUSI zavolat IoCallDriver(), inak dojde k MEMORY LEAK.
		if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,AsynchronousIRPCompletionRoutineNoCallCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			// Uvolni IRP.
			IoFreeIrp(InterruptRequestPacket);
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
			break;
		}

		// !!!!! Ak sa tato FUNCTION ZAVOLA, tak sa zavola aj COMPLETION ROUTINE pri volani IoCompleteRequest().
		IoSetNextIrpStackLocation(InterruptRequestPacket);

		// !!!!! Kedze sa IoCallDriver() NEVOLA, tak FUNCTION sposobi MEMORY LEAK, pretoze po zaregistrovani COMPLETION ROUTINE je NUTNE volat FUNCTION IoCallDriver().

		// !!!!! Ak sa ZAKOMENTOVALO volanie FUNCTION IoSetNextIrpStackLocation(), tak sa COMPLETION ROUTINE NEZAVOLA, pretoze vyssie registrovana COMPLETION ROUTINE bola zaregistrovana pre IO_STACK_LOCATION zodpovedajuci DRIVER NIZSIE v DRIVER STACK a ted kedze sa NEVYVOLAL, tak sa ani COMPLETION ROUTINE NEZAVOLA.
		// !!!!! POZOR. Ked sa COMPLETION ROUTINE NEZAVOLA v ktorej sa uvolnuje IRP , tak pri odinstalacii DRIVER hodi VERIFIER BUG CHECK, pretoze sa nie vsetky MEMORY POOLS odstranili.
		// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
		// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
		IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP was COMPLETED by DESTINATION DRIVER !\n"));

		break;
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_INITIALIZE)
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryKey)
{
	NTSTATUS													Status;
	ANSI_STRING													RegistryKeyANSI;

	if (NT_SUCCESS(Status=RtlUnicodeStringToAnsiString(&RegistryKeyANSI,RegistryKey,TRUE))==true)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DriverObject [%p], RegistryKey [%s] !\n",DriverObject,RegistryKeyANSI.Buffer);
	
		RtlFreeAnsiString(&RegistryKeyANSI);
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RtlUnicodeStringToAnsiString() FAILED [%X] !\n",Status);
	}

	DriverObject->DriverUnload=DriverUnload;
	DriverObject->DriverExtension->AddDevice=AddDevice;

	DriverObject->MajorFunction[IRP_MJ_READ]=DispatchRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE]=DispatchWrite;
	// Nie je zasielana z USER MODE, ale iba na simulaciu IRP QUEUEING.
	DriverObject->MajorFunction[IRP_MJ_SET_VOLUME_INFORMATION]=DispatchSetVolumeInformation;
	// Nie je zasielana z USER MODE, ale iba na simulaciu IRP QUEUEING cez DEVQUEUE.
	DriverObject->MajorFunction[IRP_MJ_QUERY_VOLUME_INFORMATION]=DispatchQueryVolumeInformation;
	// Nie je zasielana z USER MODE, ale iba na simulaciu IRP CANCELLATION.
	DriverObject->MajorFunction[IRP_MJ_QUERY_EA]=DispatchQueryEA;
	// Nie je zasielana z USER MODE, ale iba na simulaciu IRP COMPLETION ROUTINES.
	DriverObject->MajorFunction[IRP_MJ_SET_EA]=DispatchSetEA;

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP]=DispatchCleanup;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchSystemControl;
	DriverObject->MajorFunction[IRP_MJ_POWER]=DispatchPower;
	DriverObject->MajorFunction[IRP_MJ_PNP]=DispatchPNP;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL]=DispatchWMI;

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_UNLOAD)
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DriverObject [%p] !\n",DriverObject));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_ADD_DEVICE)
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PhysicalDeviceObject)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DriverObject [%p], PhysicalDeviceObject [%p] !\n",DriverObject,PhysicalDeviceObject));

	NTSTATUS													Status;
	PDEVICE_OBJECT												NewDeviceObject=NULL;
	UNICODE_STRING												DeviceName;

	RtlInitUnicodeString(&DeviceName, L"\\DosDevices\\" LDRIVERNAME);

	// !!! Dlzku zvacsim na NASOBOK 8, aby POINTER ukazujuci ZA DEVICE_EXTENSION bol NASOBKOM 8. Je to dolezite, pretoze POINTER za DEVICE_EXTENSION bude odkazovat na PGENERIC_EXTENSION pouzivanu na POWER a PNP SUPPORT.
	ULONG														DeviceExtensionSize=(sizeof(DEVICE_EXTENSION)+7)&~7;
	ULONG														TotalDeviceExtensionSize=DeviceExtensionSize+GetSizeofGenericExtension();

	Status=IoCreateDevice(DriverObject,TotalDeviceExtensionSize,&DeviceName,FILE_DEVICE_UNKNOWN,FILE_DEVICE_SECURE_OPEN,FALSE,&NewDeviceObject);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCreateDevice() FAILED [%X] !\n",Status));
		return(Status);
	}
	
	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) NewDeviceObject->DeviceExtension;

	do
	{
		DeviceExtensionData->DeviceObject=NewDeviceObject;
		DeviceExtensionData->PDO=PhysicalDeviceObject;
		DeviceExtensionData->LowerDeviceObject=IoAttachDeviceToDeviceStack(NewDeviceObject,PhysicalDeviceObject);
		DeviceExtensionData->Handles=0;

		if (DeviceExtensionData->LowerDeviceObject==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAttachDeviceToDeviceStack() FAILED !\n"));
			Status=STATUS_DEVICE_REMOVED;
			break;
		}

		NewDeviceObject->Flags|=DO_POWER_PAGABLE;

		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_IO_REQUEST_PACKET_DRIVER,NULL,&DeviceExtensionData->InterfaceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoRegisterDeviceInterface() FAILED [%X] !\n",Status));
			break;
		}

		IoInitializeRemoveLock(&DeviceExtensionData->RemoveLock,0,0,0);

		// !!! Inicializujem POINTER na PGENERIC_EXTENSION, tak aby ukazoval do ALOKOVANEJ MEMORY na KONCI DEVICE_EXTENSION STRUCTURE.
		DeviceExtensionData->PowerAndPNP=PGENERIC_EXTENSION((PUCHAR(DeviceExtensionData)+DeviceExtensionSize));

		// !!! STRUCTURE sa pouziva na inicializaciu PGENERIC_EXTENSION.
		GENERIC_INIT_STRUCT										GenericInitStructure={sizeof(GENERIC_INIT_STRUCT)};

		GenericInitStructure.MDeviceObject=NewDeviceObject;
		GenericInitStructure.MPDO=PhysicalDeviceObject;
		GenericInitStructure.MLDO=DeviceExtensionData->LowerDeviceObject;
		GenericInitStructure.MRemoveLock=&DeviceExtensionData->RemoveLock;
		GenericInitStructure.MStartDevice=StartDevice;
		GenericInitStructure.MStopDevice=StopDevice;
		GenericInitStructure.MRemoveDevice=RemoveDevice;
		RtlInitUnicodeString(&GenericInitStructure.MDebugName,LDRIVERNAME);

		Status=InitializeGenericExtension(DeviceExtensionData->PowerAndPNP,&GenericInitStructure);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): InitializeGenericExtension() FAILED [%X] !\n",Status));
			break;
		}

		// !!! Inicializuje sa IRP QUEUE.
		InitializeListHead(&DeviceExtensionData->IRPQueue);
		KeInitializeSpinLock(&DeviceExtensionData->IRPQueueLock);

		// !!! Inicializuje sa DEVQUEUE.
		InitializeQueue(&DeviceExtensionData->DevQueue,StartIo_Scenario4);

		KeInitializeEvent(&DeviceExtensionData->SingleCallEvent,SynchronizationEvent,TRUE);

		// !!! Inicializuje sa CANCEL SAFE IRP QUEUE.
		KeInitializeSpinLock(&DeviceExtensionData->CancelSafeIRPQueueLock);
		InitializeListHead(&DeviceExtensionData->CancelSafeIRPQueueList);
		IoCsqInitializeEx(&DeviceExtensionData->CancelSafeIRPQueue,MyCSQInsertIRPEx,MyCSQRemoveIRP,MyCSQPeekNextIRP,MyCSQAcquireLock,MyCSQReleaseLock,MyCSQCompleteCanceledIRP);

		NewDeviceObject->Flags&=~DO_DEVICE_INITIALIZING;
		
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DEVICE_OBJECT INITIALIZED, Flags [%X], Characteristics [%X], AlignmentRequirement [%X], STACK SIZE [%d] !\n",NewDeviceObject->Flags,NewDeviceObject->Characteristics,NewDeviceObject->AlignmentRequirement,NewDeviceObject->StackSize));

		Status=STATUS_SUCCESS;
	}
	while(FALSE);

	if (NT_SUCCESS(Status)==false)
	{
		if (DeviceExtensionData->InterfaceName.Buffer!=NULL)
		{
			RtlFreeUnicodeString(&DeviceExtensionData->InterfaceName);
		}

		if (DeviceExtensionData->LowerDeviceObject!=NULL)
		{
			IoDetachDevice(DeviceExtensionData->LowerDeviceObject);
		}

		if (NewDeviceObject!=NULL)
		{
			IoDeleteDevice(NewDeviceObject);
			NewDeviceObject=NULL;
		}
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS __stdcall StartDevice(PDEVICE_OBJECT DeviceObject, PCM_PARTIAL_RESOURCE_LIST, PCM_PARTIAL_RESOURCE_LIST)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p] !\n",DeviceObject));

	NTSTATUS													Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
VOID __stdcall StopDevice(IN PDEVICE_OBJECT DeviceObject, BOOLEAN)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p] !\n",DeviceObject));
}
//-------------------------------------------------------------------------------------------------------
VOID __stdcall RemoveDevice(IN PDEVICE_OBJECT DeviceObject)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p] !\n",DeviceObject));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	if (DeviceExtensionData->LowerDeviceObject!=NULL)
	{
		IoDetachDevice(DeviceExtensionData->LowerDeviceObject);
	}

	IoDeleteDevice(DeviceObject);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_READ)
NTSTATUS DispatchRead(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	// !!!!! EMULUJEM SYNCHRONNY KONIEC IRP.

	IRP->IoStatus.Status=STATUS_SUCCESS;
	IRP->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(IRP,NULL);

	// !!! Ukoncim IRP.
	// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
	// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
	IoCompleteRequest(IRP,IO_NO_INCREMENT);

	// !!!!! Ak DISPATCH ROUTINE ukoncuje IPR volanim FUNCTION IoCompleteRequest(), tak MUSI ako RETURN VALUE vratit TU ISTU HODNOTU, aku nastavil v MEMBER IRP.IoStatus.Status. Ak vrati INU VALUE, VERIFIER sposobi BUG CHECK.
	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_WRITE)
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	// !!!!! V THREADE sa SIMULUJE PROCESSING IRP.
	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,IRPCompleteSimulator,IRP))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n"));

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;
		
		PIO_STACK_LOCATION										CurrentStackLocation=IoGetCurrentIrpStackLocation(IRP);

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() BEFORE CALL IoMarkIrpPending() ! IRP->PendingReturned [%d], CurrentStackLocation->Control [%X] !\n",IRP->PendingReturned,CurrentStackLocation->Control));
		
		IoMarkIrpPending(IRP);

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() AFTER CALL IoMarkIrpPending() ! IRP->PendingReturned [%d], CurrentStackLocation->Control [%X] !\n",IRP->PendingReturned,CurrentStackLocation->Control));

		// !!!!! Kedze IRP NEBOL SKONCENY, tak sa vracia hodnota STATUS_PENDING.
		return(STATUS_PENDING);
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));

		// !!!!! Pri ERROR MUSI DRIVER VZDY IRP UKONCIT volanim FUNCTION IoCompleteRequest().

		IRP->IoStatus.Status=STATUS_UNSUCCESSFUL;
		IRP->IoStatus.Information=NULL;

		// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
		IoSetCancelRoutine(IRP,NULL);

		// !!! Ukoncim IRP.
		// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
		// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
		IoCompleteRequest(IRP,IO_NO_INCREMENT);

		// !!!!! Ak DISPATCH ROUTINE ukoncuje IPR volanim FUNCTION IoCompleteRequest(), tak MUSI ako RETURN VALUE vratit TU ISTU HODNOTU, aku nastavil v MEMBER IRP.IoStatus.Status. Ak vrati INU VALUE, VERIFIER sposobi BUG CHECK.
		return(STATUS_UNSUCCESSFUL);
	}
}
//-------------------------------------------------------------------------------------------------------
/*
// !!! SIMULACIA ERROR.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_WRITE)
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));

	// !!!!! Pri ERROR MUSI DRIVER VZDY IRP UKONCIT volanim FUNCTION IoCompleteRequest().

	IRP->IoStatus.Status=STATUS_UNSUCCESSFUL;
	IRP->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(IRP,NULL);

	// !!! Ukoncim IRP.
	// !!!!! FUNCTION IoCompleteRequest() zavola VSETKY ZAREGISTROVANE COMPLETION ROUTINES. FUNCTION IoCompleteRequest(), az ked su zavolane VSETKY ZAREGISTROVANE COMPLETION ROUTINES.
	// !!!!! Kedze COMPLETION ROUTINES, ktore FUNCTION IoCompleteRequest() vola mozu (a spravidla aj robia) uvolnit IRP z MEMORY, po NAVRATE z volania FUNCTION IoCompleteRequest() uz CODE NESMIE PRISTUPOVAT k IRP, inak by mohlo dojst k BUG CHECK.
	IoCompleteRequest(IRP,IO_NO_INCREMENT);

	// !!!!! Ak DISPATCH ROUTINE ukoncuje IPR volanim FUNCTION IoCompleteRequest(), tak MUSI ako RETURN VALUE vratit TU ISTU HODNOTU, aku nastavil v MEMBER IRP.IoStatus.Status. Ak vrati INU VALUE, VERIFIER sposobi BUG CHECK.
	return(STATUS_UNSUCCESSFUL);
}
*/
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SET_VOLUME_INFORMATION)
NTSTATUS DispatchSetVolumeInformation(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// !!!!! IRP je NUTNE nastavit na PENDING.
	IoMarkIrpPending(IRP);

	SimpleStartPacket(DeviceExtensionData,IRP);

	return(STATUS_PENDING);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_QUERY_VOLUME_INFORMATION)
NTSTATUS DispatchQueryVolumeInformation(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// !!!!! IRP je NUTNE nastavit na PENDING.
	IoMarkIrpPending(IRP);
	
	StartPacket(&DeviceExtensionData->DevQueue,DeviceObject,IRP,Scenario4CancelRoutine);

	return(STATUS_PENDING);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION sa vola, ked USER MODE PROCESS vytvori HANDLE na DRIVER.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CREATE)
NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// Inkrementuje sa HANDLER COUNTER.
	InterlockedIncrement(&DeviceExtensionData->Handles);

	// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	NTSTATUS													Status=CompleteRequest(IRP,STATUS_SUCCESS,0);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], IRP [%p], Status [%X], Handles [%d] !\n",DeviceObject,IRP,Status,DeviceExtensionData->Handles));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION sa vola, ked USER MODE PROCESS uzatvori HANDLE na DRIVER.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLOSE)
NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// Dekrementuje sa HANDLER COUNTER.
	InterlockedDecrement(&DeviceExtensionData->Handles);

	// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	NTSTATUS													Status=CompleteRequest(IRP,STATUS_SUCCESS,0);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], IRP [%p], Status [%X], Handles [%d] !\n",DeviceObject,IRP,Status,DeviceExtensionData->Handles));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLEANUP)
// !!!!! FUNCTION vykonava CLEANUP IRP, ktore vytvoril konciaci PROCESS.
NTSTATUS DispatchCleanup(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// !!!!! Ziskam IO_STACK_LOCATION zaslaneho IRP. Tento IRP vytvori IO MANAGER, ktory nastavi FileObject na FILE_OBJECT uzatvaraneho HANDLE.
	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);

	// !!! Ziskam FILE_OBJECT reprezentujuci uzatvarany HANDLE.
	PFILE_OBJECT												FileObject=Stack->FileObject;

	// !!!!! Vykona sa CLEANUP IRP v DEVQUEUE, ktore vytvoril uzatvarany HANDLE.
	CleanupRequests(&DeviceExtensionData->DevQueue,FileObject,STATUS_CANCELLED);
	
	PIRP														IRPToRemove;

	// !!!!! Odstrania sa IRP ulozene v CANCEL-SAFE IRP QUEUE.
	while((IRPToRemove=IoCsqRemoveNextIrp(&DeviceExtensionData->CancelSafeIRPQueue,FileObject))!=NULL)
	{
		// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
		CompleteRequest(IRPToRemove,STATUS_CANCELLED);
	}

	// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	NTSTATUS													Status=CompleteRequest(IRP,STATUS_SUCCESS,0);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], IRP [%p], Status [%X], Handles [%d] !\n",DeviceObject,IRP,Status,DeviceExtensionData->Handles));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_POWER)
NTSTATUS DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	return(GenericDispatchPower(DeviceExtensionData->PowerAndPNP,IRP));
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_PNP)
NTSTATUS DispatchPNP(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	PIO_STACK_LOCATION											CurrentStackLocation=IoGetCurrentIrpStackLocation(IRP);
	
	if (CurrentStackLocation->MinorFunction==IRP_MN_START_DEVICE)
	{
		// !!!!! POVINNY CODE, bez ktoreho by STALLCOUNT v DEVQUEUE ostal na 1 a DEVQUEUE by NEPRACOVALA SPRAVNE.
		RestartRequests(&DeviceExtensionData->DevQueue,DeviceExtensionData->DeviceObject);
	}

	return(GenericDispatchPNP(DeviceExtensionData->PowerAndPNP,IRP));
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SYSTEM_CONTROL)
NTSTATUS DispatchWMI(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											PDX=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	IoSkipCurrentIrpStackLocation(IRP);

	return(IoCallDriver(PDX->LowerDeviceObject,IRP));
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION spracovava IO CONTROL MESSAGES.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_DEVICE_CONTROL)
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	NTSTATUS													Status;
	ULONG														Info=0;

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK ACQUIRING - DeviceObject [%p], IRP [%p] !\n",DeviceObject,IRP));
	
	Status=IoAcquireRemoveLock(&DeviceExtensionData->RemoveLock,IRP);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END 1 - DeviceObject [%p], IRP [%p], Status [%X] !\n",DeviceObject,IRP,Status));

		return(CompleteRequest(IRP,Status,0));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK ACQUIRED - DeviceObject [%p], IRP [%p], Status [%X] !\n",DeviceObject,IRP,Status));

	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(IRP);
	ULONG														Code=Stack->Parameters.DeviceIoControl.IoControlCode;
	ULONG														InputBufferLength=Stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG														OutputBufferLength=Stack->Parameters.DeviceIoControl.OutputBufferLength;

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Code [%d], InputBufferLength [%d], OutputBufferLength [%d] !\n",Code,InputBufferLength,OutputBufferLength));

	switch(Code)
	{
		case IOCTL_SIMPLE_TEST:
		{
			Status=ProcessIOControlSimpleTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_1_TEST:
		{
			Status=ProcessIOControlScenario1Test(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_2_TEST:
		{
			Status=ProcessIOControlScenario2Test(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_3_TEST:
		{
			Status=ProcessIOControlScenario3Test(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_4_TEST:
		{
			Status=ProcessIOControlScenario4Test(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_5_FINISHED_SYNCHRONOUSLY_TEST:
		{
			Status=ProcessIOControlScenario5FinishedSynchronouslyTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_5_FINISHED_ASYNCHRONOUSLY_TEST:
		{
			Status=ProcessIOControlScenario5FinishedAsynchronouslyTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_6_FINISHED_SYNCHRONOUSLY_TEST:
		{
			Status=ProcessIOControlScenario6FinishedSynchronouslyTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_6_FINISHED_ASYNCHRONOUSLY_TEST:
		{
			Status=ProcessIOControlScenario6FinishedAsynchronouslyTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_7_FINISHED_SYNCHRONOUSLY_TEST:
		{
			Status=ProcessIOControlScenario7FinishedSynchronouslyTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_7_FINISHED_ASYNCHRONOUSLY_TEST:
		{
			Status=ProcessIOControlScenario7FinishedAsynchronouslyTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_8_FINISHED_SYNCHRONOUSLY_TEST:
		{
			Status=ProcessIOControlScenario8FinishedSynchronouslyTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SCENARIO_8_FINISHED_ASYNCHRONOUSLY_TEST:
		{
			Status=ProcessIOControlScenario8FinishedAsynchronouslyTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_IO_STACK_LOCATION_TEST:
		{
			Status=ProcessIOControlIoStackLocationTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_GET_DEVICE_OBJECT_POINTER_TEST:
		{
			Status=ProcessIOControlGetDeviceObjectPointerTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_IRP_QUEUEING_TEST:
		{
			Status=ProcessIOControlIRPQueueingTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_CANCEL_SAFE_IRP_QUEUE_TEST:
		{
			Status=ProcessIOControlCancelSafeIRPQueueTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_CANCEL_SYNCHRONOUS_IRP_TEST:
		{
			Status=ProcessIOControlCancelSynchronousIRPTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_CANCEL_ASYNCHRONOUS_IRP_TEST:
		{
			Status=ProcessIOControlCancelAsynchronousIRPTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_REMOTE_CANCEL_ASYNCHRONOUS_IRP_TEST:
		{
			Status=ProcessIOControlRemoteCancelAsynchronousIRPTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_DOUBLE_COMPLETION_ROUTINES_TEST:
		{
			Status=ProcessIOControlDoubleCompletionRoutineTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_SYNCHRONOUS_IRP_COMPLETION_ROUTINE_NO_CALL_TEST:
		{
			Status=ProcessIOControlSynchronousIRPCompletionRoutineNoCallTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_ASYNCHRONOUS_IRP_COMPLETION_ROUTINE_NO_CALL_TEST:
		{
			Status=ProcessIOControlAsynchronousIRPCompletionRoutineNoCallTest(IRP,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		default:
		{
			Status=STATUS_INVALID_DEVICE_REQUEST;
		}
		break;
	}

	// !!! Ukonci spracovanie IRP PACKET, ktory reprezentuje SYSTEM CONTROL.
	Status=CompleteRequest(IRP,Status,Info);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASING - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,IRP,Status);

	// !!!!!! Z MSDN. For I/O operations (including power and PnP IRPs) that set an IoCompletion() routine, a driver should call IoReleaseRemoveLock() in the IoCompletion() routine, after calling IoCompleteRequest().
	IoReleaseRemoveLock(&DeviceExtensionData->RemoveLock,IRP);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,IRP,Status);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END 2 - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,IRP,Status);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------