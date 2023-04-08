//-------------------------------------------------------------------------------------------------------
// !!! HEADER [Ntddk.h] MUSI BYT PRED HEADER [wdm.h].
#include <Ntddk.h>
#include <wdm.h>
#include <initguid.h>
#include <Ntstrsafe.h>
//-------------------------------------------------------------------------------------------------------
#include "Macros.h"
#include "Defines.h"
#include "Driver.h"
#include "GUIDS.h"
#include "FileLogger.h"
//-------------------------------------------------------------------------------------------------------
struct MY_THREAD_PARAMTERS
{
	PIRP														IRP;
	PDEVICE_EXTENSION											DeviceExtension;
};
//-------------------------------------------------------------------------------------------------------
CFileLogger*													LOG=NULL;
UCHAR															Component[]="MyDriver";
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_DPC_ROUTINE)
VOID DPCForISR(PKDPC DeferredProcedureCall, PDEVICE_OBJECT DeviceObject, PIRP, PVOID Context);
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
_Dispatch_type_(IRP_MJ_CREATE)
NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLOSE)
NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLEANUP)
NTSTATUS DispatchCleanup(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_POWER)
NTSTATUS DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_PNP)
NTSTATUS DispatchPNP(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SYSTEM_CONTROL)
NTSTATUS DispatchWMI(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SHUTDOWN)
NTSTATUS DispatchShutdown(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_READ)
NTSTATUS IRPQueueingLowerDriverDispatchRead(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_WRITE)
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_DEVICE_CONTROL)
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_STARTIO)
void IRPQueueingLowerDriverStartIo(PDEVICE_OBJECT DeviceObject, PIRP IRP);
_Function_class_(IO_WORKITEM_ROUTINE_EX)
VOID IRPQueueingLowerDriverWorkItemRoutineEx(PVOID IoObject, PVOID Context, PIO_WORKITEM IoWorkItem);
NTSTATUS ProcessIOControlIRPQueueingUpperDriverTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&);
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_SIMPLE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_QUEUE_IRP_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! Simuluje UKONCENIE IRP po nejakom case, ktory simuluje PROCESSING IRP.
// !!!!! Tento CODE NIE JE CELKOM KOREKTNY, pretoze v pripade, ze pocas behu THREADU dojde k odstraneniu DRIVER z MEMORY WINDOWS detekuje, ze THREAD vytvoreny DRIVER nebol odstraneny z MEMORY a sposobi BUG CHECK [0xCE] [DRIVER_UNLOADED_WITHOUT_CANCELLING_PENDING_OPERATIONS]. THREADS by sa mali vytvarat pri starte DRIVER a uvolnovat pri ukonceni DRIVER.
_Function_class_(KSTART_ROUTINE)
void IRPCompleteSimulator(PVOID Parameter)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n");

	MY_THREAD_PARAMTERS*										ThreadParameters=(MY_THREAD_PARAMTERS*) Parameter;
	PIRP														InterruptRequestPacket=ThreadParameters->IRP;
	PDEVICE_EXTENSION											DeviceExtension=ThreadParameters->DeviceExtension;

	ExFreePoolWithTag(ThreadParameters,'  PT');

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=2*1000*(-10*1000);

	// !!! POCKAM 2 SEKUNDY.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD DELAY FINISHED !\n");
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeDelayExecutionThread() FAILED [%X] !\n",Status);
	}

	InterruptRequestPacket->IoStatus.Status=STATUS_SUCCESS;
	InterruptRequestPacket->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(InterruptRequestPacket,NULL);

	// !!! Ukoncim IRP.
	// !!!!! Ak DRIVER dostal IRP z DRIVER VYSSIE v DRIVER STACK musi ho bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP was COMPLETED by DESTINATION DRIVER !\n");

	// !!! Kedze sa IRP SPRACOVAL, tak je NUTNE UVOLNIT REMOVE LOCK.
	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,InterruptRequestPacket);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n");

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlSimpleTest(PIRP InterruptRequestPacket, DEVICE_EXTENSION*, ULONG, ULONG InputBufferLength, ULONG OutputBufferLength, ULONG& Info)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n");

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// Alokujem aj miesto pre NULL TERMINATOR.
	SIZE_T														DataFromInputBufferLength=InputBufferLength+sizeof(CHAR);
	CHAR*														DataFromInputBuffer=(CHAR*) ExAllocatePoolWithTag(PagedPool,DataFromInputBufferLength,' FUB');

	if (DataFromInputBuffer!=NULL)
	{
		RtlZeroMemory(DataFromInputBuffer,DataFromInputBufferLength);

		// Do DataFromInputBuffer sa ulozia BYTES z INPUT BUFFER, pricom DataFromInputBuffer ma este o 1 BYTE navyse na ulozenie NULL TERMINATOR.
		// !!!!! FIELD InterruptRequestPacket->AssociatedIrp.SystemBuffer obsahuje INPUT aj OUTPUT BUFFER.
		RtlCopyMemory(DataFromInputBuffer,InterruptRequestPacket->AssociatedIrp.SystemBuffer,InputBufferLength);

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): InputBuffer [%s] !\n",DataFromInputBuffer);
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): MEMORY ALLOCATION FAILED !\n");
	}

	WCHAR												DataToSendToUserMode[]=L"My name is Timmy Anderson !";
	ULONG												DataToSendToUserModeLength=sizeof(DataToSendToUserMode);
			
	if (OutputBufferLength>=DataToSendToUserModeLength)
	{
		// Do OUTPUT BUFFER sa ulozi STRING.
		// !!!!! FIELD InterruptRequestPacket->AssociatedIrp.SystemBuffer obsahuje INPUT aj OUTPUT BUFFER.
		RtlCopyMemory(InterruptRequestPacket->AssociatedIrp.SystemBuffer,&DataToSendToUserMode,DataToSendToUserModeLength);
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
	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP]=DispatchCleanup;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchSystemControl;
	DriverObject->MajorFunction[IRP_MJ_POWER]=DispatchPower;
	DriverObject->MajorFunction[IRP_MJ_PNP]=DispatchPNP;
	DriverObject->MajorFunction[IRP_MJ_SHUTDOWN]=DispatchShutdown;

	DriverObject->MajorFunction[IRP_MJ_READ]=IRPQueueingLowerDriverDispatchRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE]=DispatchWrite;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL]=DispatchWMI;

	if ((LOG=new CFileLogger(LOGFILE))!=NULL)
	{
		return(STATUS_SUCCESS);
	}
	else
	{
		return(STATUS_UNSUCCESSFUL);
	}
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_UNLOAD)
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DriverObject [%p] !\n",DriverObject);

	if (LOG!=NULL)
	{
		delete(LOG);
		LOG=NULL;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(KSERVICE_ROUTINE)
BOOLEAN MyInterruptServiceRoutine(PKINTERRUPT, PVOID Context)
{
	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) Context;

	LONG														Value=InterlockedIncrement(&DeviceExtensionData->InterruptCounter);

	if ((Value % 100)==0)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): MyInterruptServiceRoutine() CALLED, VALUE [%d] !\n",Value);

		IoRequestDpc(DeviceExtensionData->DeviceObject,NULL,DeviceExtensionData);
	}

	// !!! Ak INTERRUPT NIE JE SPRACOVANY, tak sa MUSI vratit FALSE, aby INTERRUPT (ktory moze byt SHARED) mohol byt posunuty dalsim DRIVERS.
	return(FALSE);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_DPC_ROUTINE)
VOID DPCForISR(PKDPC, PDEVICE_OBJECT, PIRP, PVOID)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DPCForISR() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_ADD_DEVICE)
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PhysicalDeviceObject)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DriverObject [%p], PhysicalDeviceObject [%p] !\n",DriverObject,PhysicalDeviceObject);

	NTSTATUS													Status;
	PDEVICE_OBJECT												NewDeviceObject=NULL;
	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;
	bool														SymbolicLinkCreated=false;
	bool														IsGenericExtensionInitialized=false;

	RtlInitUnicodeString(&DeviceName, L"\\??\\" LDRIVERNAME);
	RtlInitUnicodeString(&SymbolicLink, L"\\Device\\My" LDRIVERNAME);

	// !!! Dlzku zvacsim na NASOBOK 8, aby POINTER ukazujuci ZA DEVICE_EXTENSION bol NASOBKOM 8. Je to dolezite, pretoze POINTER za DEVICE_EXTENSION bude odkazovat na PGENERIC_EXTENSION pouzivanu na POWER a PNP SUPPORT.
	ULONG														DeviceExtensionSize=(sizeof(DEVICE_EXTENSION)+7)&~7;
	ULONG														TotalDeviceExtensionSize=DeviceExtensionSize+GetSizeofGenericExtension();

	Status=IoCreateDevice(DriverObject,TotalDeviceExtensionSize,&DeviceName,FILE_DEVICE_UNKNOWN,FILE_DEVICE_SECURE_OPEN,FALSE,&NewDeviceObject);

	if (NT_SUCCESS(Status)==false)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCreateDevice() FAILED [%X] !\n",Status);
		return(Status);
	}
	
	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) NewDeviceObject->DeviceExtension;

	RtlInitUnicodeString(&DeviceExtensionData->InterfaceName,NULL);
	DeviceExtensionData->InterruptObject=NULL;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCreateSymbolicLink() FAILED [%X] !\n",Status);
			break;
		}

		SymbolicLinkCreated=true;

		NewDeviceObject->Flags|=DO_BUFFERED_IO;

		IoInitializeDpcRequest(NewDeviceObject,DPCForISR);

		DeviceExtensionData->DeviceObject=NewDeviceObject;
		DeviceExtensionData->PDO=PhysicalDeviceObject;
		DeviceExtensionData->LowerDeviceObject=IoAttachDeviceToDeviceStack(NewDeviceObject,PhysicalDeviceObject);
		DeviceExtensionData->Handles=0;

		if (DeviceExtensionData->LowerDeviceObject==NULL)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAttachDeviceToDeviceStack() FAILED !\n");
			Status=STATUS_DEVICE_REMOVED;
			break;
		}

		NewDeviceObject->Flags|=DO_POWER_PAGABLE;

		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_IRP_QUEUEING_DRIVER,NULL,&DeviceExtensionData->InterfaceName);
		
		if (NT_SUCCESS(Status)==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoRegisterDeviceInterface() FAILED [%X] !\n",Status);
			break;
		}

		Status=IoSetDeviceInterfaceState(&DeviceExtensionData->InterfaceName,TRUE);
		
		if (NT_SUCCESS(Status)==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetDeviceInterfaceState() FAILED [%X] !\n",Status);
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
		
		// !!!!! [DEVQUEUE] sa ulozi do [GENERIC_INIT_STRUCT], aby [DEVQUEUE] bol spravovany STRUCTURE [GENERIC_EXTENSION].
		GenericInitStructure.MQueues[0].MDeviceQueue=&DeviceExtensionData->DevQueue;
		GenericInitStructure.MQueues[0].MStartIO=IRPQueueingLowerDriverStartIo;
		GenericInitStructure.MNumberOfQueues=1;

		RtlInitUnicodeString(&GenericInitStructure.MDebugName,LDRIVERNAME);

		Status=InitializeGenericExtension(DeviceExtensionData->PowerAndPNP,&GenericInitStructure);

		if (NT_SUCCESS(Status)==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): InitializeGenericExtension() FAILED [%X] !\n",Status);
			break;
		}

		IsGenericExtensionInitialized=true;

		// !!! Zaregistrujem SHUTDOWN ROUTINE.
		IoRegisterShutdownNotification(NewDeviceObject);

		// !!! Po zruseni FLAG 'DO_DEVICE_INITIALIZING' je DEVICE_OBJECT pripraveny prijimat IRP.
		NewDeviceObject->Flags&=~DO_DEVICE_INITIALIZING;

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DEVICE_OBJECT INITIALIZED, Flags [%X], Characteristics [%X], AlignmentRequirement [%X], STACK SIZE [%d] !\n",NewDeviceObject->Flags,NewDeviceObject->Characteristics,NewDeviceObject->AlignmentRequirement,NewDeviceObject->StackSize);

		Status=STATUS_SUCCESS;
		break;
	}

	if (NT_SUCCESS(Status)==false)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): AddDevice() FAILED, STATUS [%X] !\n",Status);

		if (IsGenericExtensionInitialized==true)
		{
			DeregisterAllInterfaces(DeviceExtensionData->PowerAndPNP);
			CleanupGenericExtension(DeviceExtensionData->PowerAndPNP);
		}

		if (SymbolicLinkCreated==true)
		{
			IoDeleteSymbolicLink(&SymbolicLink);
		}

		// Odstrani INTERFACE NAME.
		if (DeviceExtensionData->InterfaceName.Buffer!=NULL)
		{
			// !!! Musim VYPNUT DEVICE INTERFACE NAME.
			NTSTATUS											LocalStatus=IoSetDeviceInterfaceState(&DeviceExtensionData->InterfaceName,FALSE);
		
			if (NT_SUCCESS(LocalStatus)==false)
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetDeviceInterfaceState() FAILED [%X] !\n",LocalStatus);
			}

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
// !!!!! FUNCTION je volana potom co IRP bol odoslany a spracovany DRIVERS NIZSIE v DRIVER STACK.
NTSTATUS __stdcall StartDevice(PDEVICE_OBJECT DeviceObject, PCM_PARTIAL_RESOURCE_LIST RawList, PCM_PARTIAL_RESOURCE_LIST TranslatedList)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], RawList [%p], TranslatedList [%p] !\n",DeviceObject,RawList,TranslatedList);

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	DeviceExtensionData->InterruptObject=NULL;

	ULONG														Vector=0;
	KIRQL														IRQL=0;
	KINTERRUPT_MODE												Mode=Latched;
	KAFFINITY													Affinity=0;
	BOOLEAN														IRQShare=FALSE;
	BOOLEAN														GotInterrupt=FALSE;
	
	if (TranslatedList==NULL)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): TRANSLATED LIST is NULL !\n");
		return(STATUS_DEVICE_CONFIGURATION_ERROR);
	}

	PCM_PARTIAL_RESOURCE_DESCRIPTOR								Resource=TranslatedList->PartialDescriptors;
	ULONG														NumberOfResources=TranslatedList->Count;

	for (ULONG Index=0;Index<NumberOfResources;++Index,++Resource)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RESOURCE TYPE [%d] !\n",Resource->Type);

		switch(Resource->Type)
		{
			case CmResourceTypeInterrupt:
			{
				IRQL=(KIRQL) Resource->u.Interrupt.Level;
				Vector=Resource->u.Interrupt.Vector;
				Affinity=Resource->u.Interrupt.Affinity;
				Mode=(Resource->Flags==CM_RESOURCE_INTERRUPT_LATCHED) ? Latched : LevelSensitive;
				IRQShare=(Resource->ShareDisposition==CmResourceShareShared);
				GotInterrupt=TRUE;
			}
			break;

			default:
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Unexpected I/O resource type [%d] !\n",Resource->Type);
			}
			break;
		}
	}

	if (GotInterrupt==FALSE)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Didn't get expected I/O resources !\n");
		return(STATUS_DEVICE_CONFIGURATION_ERROR);
	}

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CONNECTING INTERRUPT REQUEST - Vector [%X], IRQL [%X], Mode [%X], IRQShare [%X], Affinity [%I64X] !\n",Vector,IRQL,Mode,IRQShare,Affinity);

	// !!! REALNY DEVICE by tu mal prinutit DEVICE, aby zastavil generovanie INTERRUPTS. Generovanie INTERRUPTS by sa malo obnovit az po dokonceni FUNCTION IoConnectInterrupt().

	LOG->WriteToLog("TEST 1 !\n");

	NTSTATUS													Status;

	if (NT_SUCCESS(Status=IoConnectInterrupt(&DeviceExtensionData->InterruptObject,(PKSERVICE_ROUTINE) MyInterruptServiceRoutine,(PVOID) DeviceExtensionData,NULL,Vector,IRQL,IRQL,Mode,IRQShare,Affinity,FALSE))==false)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoConnectInterrupt() FAILED [%X] !\n",Status);
		return(Status);
	}

	LOG->WriteToLog("TEST 2 !\n");

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION je volana potom co IRP bol odoslany a spracovany DRIVERS NIZSIE v DRIVER STACK.
VOID __stdcall StopDevice(IN PDEVICE_OBJECT DeviceObject, BOOLEAN)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p] !\n",DeviceObject);

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	if (DeviceExtensionData->InterruptObject!=NULL)
	{
		// !!! REALNY DEVICE by tu mal prinutit DEVICE, aby zastavil generovanie INTERRUPTS.
		IoDisconnectInterrupt(DeviceExtensionData->InterruptObject);
		DeviceExtensionData->InterruptObject=NULL;
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION je volana potom co IRP bol odoslany a spracovany DRIVERS NIZSIE v DRIVER STACK.
VOID __stdcall RemoveDevice(IN PDEVICE_OBJECT DeviceObject)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p] !\n",DeviceObject);

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	if (DeviceExtensionData->InterruptObject!=NULL)
	{
		IoDisconnectInterrupt(DeviceExtensionData->InterruptObject);
		DeviceExtensionData->InterruptObject=NULL;
	}

	// !!! Odregistrujem SHUTDOWN ROUTINE.
	IoUnregisterShutdownNotification(DeviceObject);

	if (DeviceExtensionData->InterfaceName.Buffer!=NULL)
	{
		RtlFreeUnicodeString(&DeviceExtensionData->InterfaceName);
	}

	if (DeviceExtensionData->LowerDeviceObject!=NULL)
	{
		// !!! Odpaja DEVICE_OBJECT z DRIVER STACK.
		IoDetachDevice(DeviceExtensionData->LowerDeviceObject);
	}

	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&SymbolicLink, L"\\Device\\My" LDRIVERNAME);

	IoDeleteSymbolicLink(&SymbolicLink);

	// !!! Odstranuje DEVICE_OBJECT z MEMORY.
	IoDeleteDevice(DeviceObject);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION sa vola, ked USER MODE PROCESS vytvori HANDLE na DRIVER.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CREATE)
NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// Inkrementuje sa HANDLER COUNTER.
	InterlockedIncrement(&DeviceExtensionData->Handles);

	// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	NTSTATUS													Status=CompleteRequest(InterruptRequestPacket,STATUS_SUCCESS,0);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X], Handles [%d] !\n",DeviceObject,InterruptRequestPacket,Status,DeviceExtensionData->Handles);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION sa vola, ked USER MODE PROCESS uzatvori HANDLE na DRIVER.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLOSE)
NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// Dekrementuje sa HANDLER COUNTER.
	InterlockedDecrement(&DeviceExtensionData->Handles);

	// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	NTSTATUS													Status=CompleteRequest(InterruptRequestPacket,STATUS_SUCCESS,0);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X], Handles [%d] !\n",DeviceObject,InterruptRequestPacket,Status,DeviceExtensionData->Handles);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION vykonava CLEANUP IRP, ktore vytvoril konciaci PROCESS.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_CLEANUP)
NTSTATUS DispatchCleanup(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// !!!!! Ziskam IO_STACK_LOCATION zaslaneho IRP. Tento IRP vytvori IO MANAGER, ktory nastavi FileObject na FILE_OBJECT uzatvaraneho HANDLE.
	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(InterruptRequestPacket);

	// !!! Ziskam FILE_OBJECT reprezentujuci uzatvarany HANDLE.
	PFILE_OBJECT												FileObject=Stack->FileObject;

	// !!!!! Vykona sa CLEANUP IRP v DEVQUEUE, ktore vytvoril uzatvarany HANDLE.
	CleanupRequests(&DeviceExtensionData->DevQueue,FileObject,STATUS_CANCELLED);

	// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	NTSTATUS													Status=CompleteRequest(InterruptRequestPacket,STATUS_SUCCESS,0);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X], Handles [%d] !\n",DeviceObject,InterruptRequestPacket,Status,DeviceExtensionData->Handles);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_POWER)
NTSTATUS DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	return(GenericDispatchPower(DeviceExtensionData->PowerAndPNP,InterruptRequestPacket));
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_PNP)
NTSTATUS DispatchPNP(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	return(GenericDispatchPNP(DeviceExtensionData->PowerAndPNP,InterruptRequestPacket));
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SYSTEM_CONTROL)
NTSTATUS DispatchWMI(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	PDEVICE_EXTENSION											PDX=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	IoSkipCurrentIrpStackLocation(InterruptRequestPacket);

	return(IoCallDriver(PDX->LowerDeviceObject,InterruptRequestPacket));
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_SHUTDOWN)
NTSTATUS DispatchShutdown(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	return(CompleteRequest(InterruptRequestPacket,STATUS_SUCCESS));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_WRITE)
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);
	
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): InterruptRequestPacket->StackCount [%d] !\n",InterruptRequestPacket->StackCount);
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): InterruptRequestPacket->CurrentLocation [%d] !\n",InterruptRequestPacket->CurrentLocation);

	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// !!! Ziska sa REMOVE LOCK.
	NTSTATUS													Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,InterruptRequestPacket);

	if (NT_SUCCESS(Status)==false)
	{
		InterruptRequestPacket->IoStatus.Status=Status;
		InterruptRequestPacket->IoStatus.Information=0;

		IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

		return(Status);
	}

	InterruptRequestPacket->IoStatus.Status=STATUS_SUCCESS;
	InterruptRequestPacket->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(InterruptRequestPacket,NULL);

	// !!! Ukoncim IRP.
	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

	// !!! Kedze sa IRP SPRACOVAL, tak je NUTNE UVOLNIT REMOVE LOCK.
	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,InterruptRequestPacket);

	// !!!!! Ak DISPATCH ROUTINE ukoncuje IPR volanim FUNCTION IoCompleteRequest(), tak MUSI ako RETURN VALUE vratit TU ISTU HODNOTU, aku nastavil v MEMBER IRP.IoStatus.Status. Ak vrati INU VALUE, VERIFIER sposobi BUG CHECK.
	// !!!!! TENTO CODE uz NIE JE CHRANENY REMOVE LOCK a teda sa moze stat, ze ak by WINDOWS uvolnil DRIVER SKOR ako by sa zavolal INSTRUCTION [return(STATUS_SUCCESS)] doslo by k BUG CHECK. Nanestastie WDM NEPOSKYTUJE MOZNOST, ako tejto situacii ZABRANIT.
	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION spracovava IO CONTROL MESSAGES.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_DEVICE_CONTROL)
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	NTSTATUS													Status;
	ULONG														Info=0;

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK ACQUIRING - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);
	
	Status=IoAcquireRemoveLock(&DeviceExtensionData->RemoveLock,InterruptRequestPacket);

	if (NT_SUCCESS(Status)==false)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END 1 - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status);

		return(CompleteRequest(InterruptRequestPacket,Status,0));
	}

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK ACQUIRED - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status);

	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(InterruptRequestPacket);
	ULONG														Code=Stack->Parameters.DeviceIoControl.IoControlCode;
	ULONG														InputBufferLength=Stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG														OutputBufferLength=Stack->Parameters.DeviceIoControl.OutputBufferLength;

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Code [%d], InputBufferLength [%d], OutputBufferLength [%d] !\n",Code,InputBufferLength,OutputBufferLength);

	switch(Code)
	{
		case IOCTL_SIMPLE_TEST:
		{
			Status=ProcessIOControlSimpleTest(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_QUEUE_IRP_TEST:
		{
			Status=ProcessIOControlIRPQueueingUpperDriverTest(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		default:
		{
			Status=STATUS_INVALID_DEVICE_REQUEST;
		}
		break;
	}

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASING - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status);

	IoReleaseRemoveLock(&DeviceExtensionData->RemoveLock,InterruptRequestPacket);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status);

	// !!! Ukonci spracovanie IRP PACKET, ktory reprezentuje SYSTEM CONTROL.
	Status=CompleteRequest(InterruptRequestPacket,Status,Info);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END 2 - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Requires_lock_held_(_Global_cancel_spin_lock_)
_Function_class_(DRIVER_CANCEL)
_IRQL_raises_(DISPATCH_LEVEL)
void IRPQueueingLowerDriverCancellationRoutine(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	DbgPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) DeviceObject->DeviceExtension;

	// !!! Odstrani IRP z IRP QUEUE.
	CancelRequest(&DeviceExtension->DevQueue,IRP);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_WORKITEM_ROUTINE_EX)
VOID IRPQueueingLowerDriverWorkItemRoutineEx(PVOID IoObject, PVOID Context, PIO_WORKITEM IoWorkItem)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKITEM ROUTINE CALLED !\n");

	PDEVICE_OBJECT												DeviceObject=(PDEVICE_OBJECT) IoObject;
	PIRP														InterruptRequestPacket=(PIRP) Context;
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// !!! Sluzi na SPOMALENIE CODE, aby sa otestovalo ukladanie IRP do IRP QUEUE.
	// !!!!! Na VIRTUAL MACHINE s 2 CPU sa bezne stavalo, ze sa QUEUE zacinala zaplnat. Bez tohto CODE prakticky vzdy sa IRP spracovali rychlejsie aby sa stihli ulozit do IRP QUEUE.
	KeStallExecutionProcessor(1000);

	// !!! Uvolni sa WORK ITEM.
	IoFreeWorkItem(IoWorkItem);

	// !!!!! DPC ROUTINE spusti vykonavanie dalsieho IRP ak je QUEUE.
	StartNextPacket(&DeviceExtension->DevQueue,DeviceObject);

	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);

	// !!! DPC ROUTINE emuluje UKONCENIE IRP.
	InterruptRequestPacket->IoStatus.Status=STATUS_SUCCESS;
	InterruptRequestPacket->IoStatus.Information=NULL;

	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_STARTIO)
void IRPQueueingLowerDriverStartIo(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	PIO_WORKITEM												WorkItem=IoAllocateWorkItem(DeviceObject);

	if (WorkItem!=NULL)
	{
		// !!! IRP sa zasle na spracovanie do SYSTEM THREAD.
		IoQueueWorkItemEx(WorkItem,IRPQueueingLowerDriverWorkItemRoutineEx,DelayedWorkQueue,InterruptRequestPacket);
	}
	// !!! Ak sa WORK ITEM nepodarilo alokovat, tak sa spracovanie IRP OKAMZITE UKONCI a zaroven sa spusti spracovanie noveho IRP.
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IoAllocateWorkItem() FAILED to allocate WORK ITEM !\n"));

		PDEVICE_EXTENSION										DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

		// !!!!! DPC ROUTINE spusti vykonavanie dalsieho IRP ak je QUEUE.
		StartNextPacket(&DeviceExtension->DevQueue,DeviceObject);

		IoReleaseRemoveLock(&DeviceExtension->RemoveLock,NULL);

		// !!! DPC ROUTINE emuluje UKONCENIE IRP.
		InterruptRequestPacket->IoStatus.Status=STATUS_SUCCESS;
		InterruptRequestPacket->IoStatus.Information=NULL;

		IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! DISPATCH ROUTINE simuluje DRIVER spracujuci IRP cez IRP QUEUEING.
// !!! Kedze sa jedna o simulaciu IRP su v skutocnosti TAKTIEZ vytvarane v CURRENT DRIVER a nasledne ich DRIVER zasle SAM SEBE cez FUNCTION IoCallDriver().
// !!! DRIVERS okrem FILE SYSTEM DRIVERS toto IRP NEIMPLEMENTUJU, kedze ulohou IRP je vratit EXTENDED INFORMATION ATTRIBUTES FILE na DISKU.
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_READ)
NTSTATUS IRPQueueingLowerDriverDispatchRead(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// CURRENT DRIVER ziska REMOVE LOCK, aby sa zabranilo jeho predcasnemu odstraneniu z MEMORY IO MANAGER.
	if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==true)
	{
		// !!! Kedze IRP NEBUDE OKAMZITE spracovane, nastavi sa do PENDING STATE.
		IoMarkIrpPending(InterruptRequestPacket);

		// !!!!! IRP sa ulozi do QUEUE.
		// !!! FUNCTION zaroven nastavi CANCEL ROUTINE.
		StartPacket(&DeviceExtension->DevQueue,DeviceObject,InterruptRequestPacket,IRPQueueingLowerDriverCancellationRoutine);

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

		// !!! Kedze IRP NEBUDE OKAMZITE spracovane, ako RETURN VALUE sa vrati hodnota [STATUS_PENDING].
		return(STATUS_PENDING);
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));

		// !!!!! EMULUJE sa KONIEC IRP.
		InterruptRequestPacket->IoStatus.Status=STATUS_UNSUCCESSFUL;
		InterruptRequestPacket->IoStatus.Information=NULL;

		// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
		IoSetCancelRoutine(InterruptRequestPacket,NULL);

		// !!! Ukoncim IRP.
		IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

		return(InterruptRequestPacket->IoStatus.Status);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION simuluje COMPLETION ROUTINE DRIVER VYSSIE v DEVICE OBJECT STACK.
_Function_class_(IO_COMPLETION_ROUTINE)
NTSTATUS IRPQueueingUpperDriverCompletionRoutine(PDEVICE_OBJECT, PIRP InterruptRequestPacket, PVOID)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COMPLETING IRP, IRQL [%d] !\n",KeGetCurrentIrql());

	// Vypise STATUS skoncenej IO OPERATION.
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP FINISHED with STATUS [%X], PENDING RETURNED [%d] !\n",InterruptRequestPacket->IoStatus.Status,InterruptRequestPacket->PendingReturned);

	IoFreeIrp(InterruptRequestPacket);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n");

	// !!! COMPLETION ROUTINE vracia RETURN VALUE [STATUS_MORE_PROCESSING_REQUIRED], pretoze IRP uz bol uvolneny.
	return(STATUS_MORE_PROCESSING_REQUIRED);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Tato FUNCTION simuluje DRIVER VYSSIE v DEVICE OBJECT STACK, ktory zasiela do CURRENT DRIVER IRP.
// !!!!! Kedze IRP bolo vytvorene ako ASYNCHRONNE IRP, MUSI DRIVER zaregistrovat VLASTNU COMPLETION ROUTINE v ktorej IRP uvolni.
// !!! Kedze sa jedna o simulaciu FUNCTION NEPOUZIVA REMOVE LOCK, aby nenarusil beh CODE v DispatchQueryEA(), ktora simuluje DRIVER NIZSIE v DEVICE OBJECT STACK.
NTSTATUS ProcessIOControlIRPQueueingUpperDriverTest(PIRP, DEVICE_EXTENSION* DeviceExtension, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));
	
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for(int Index=0;Index<10;Index++)
	{
		PIRP													InterruptRequestPacket=NULL;
		CHAR													Buffer[100];
		LARGE_INTEGER											Offset;
		IO_STATUS_BLOCK											IRPStatus;

		RtlZeroMemory(Buffer,sizeof(Buffer));
		RtlZeroMemory(&IRPStatus,sizeof(IRPStatus));
		Offset.QuadPart=0;

		// !!!!! Emuluje sa IRP akokeby bol zaslany zo SOURCE DRIVER (DRIVER VYSSIE v DEVICE OBJECT STACK).
		// !!! Vytvori sa IRP, ktory SKONCI ASYNCHRONNE.
		if ((InterruptRequestPacket=IoBuildAsynchronousFsdRequest(IRP_MJ_READ,DeviceExtension->DeviceObject,Buffer,_countof(Buffer),&Offset,&IRPStatus))!=NULL)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): InterruptRequestPacket->StackCount [%d] !\n",InterruptRequestPacket->StackCount);
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): InterruptRequestPacket->CurrentLocation [%d] !\n",InterruptRequestPacket->CurrentLocation);

			// Ziskam IO_STACK_LOCATION na DRIVER NIZSIE v DEVICE OBJECT STACK.
			// !!! Pri vytvoreni IRP sa INDEX do IO_STACK_LOCATION ARRAY nastavi na hodnotu -1. Zavolanim FUNCTION IoGetNextIrpStackLocation() sa inkrementuje na hodnotu 0 co znamena, ze INDEX ukazuje na PRVY IO_STACK_LOCATION objekt.
			PIO_STACK_LOCATION									StackLocation=IoGetNextIrpStackLocation(InterruptRequestPacket);

			StackLocation->MajorFunction=IRP_MJ_READ;

			// !!! Zaregistruje sa COMPLETION ROUTINE.
			// !!!!! Skor ako je COMPLETION ROUTINE zaregistrovana pomocou FUNCTION IoSetCompletionRoutine(), alebo FUNCTION IoSetCompletionRoutineEx() je NUTNE pripravit [IO_STACK_LOCATION] pre DESTINATION DRIVER. Je to dosledok toho, ze volanie FUNCTIONS IoSetCompletionRoutine() a IoSetCompletionRoutineEx() MODIFIKUJE CURRENT [IO_STACK_LOCATION] a ak by sa napriklad [IO_STACK_LOCATION] pre DESTINATION DRIVER inicializoval volanim IoCopyCurrentIrpStackLocationToNext(), tak by sa skopirovali uz MODIFIKOVANE HODNOTY CURRENT [IO_STACK LOCATION].
			if (NT_SUCCESS(Status=IoSetCompletionRoutineEx(DeviceExtension->DeviceObject,InterruptRequestPacket,IRPQueueingUpperDriverCompletionRoutine,DeviceExtension,TRUE,TRUE,TRUE))==true)
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): InterruptRequestPacket->CurrentLocation [%p] !\n",StackLocation->CompletionRoutine);

				// !!!!! IRP sa zasle do CURRENT DRIVER (sam do seba).
				if (NT_SUCCESS(Status=IoCallDriver(DeviceExtension->DeviceObject,InterruptRequestPacket))==true)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP SENT do DESTINATION DRIVER with STATUS [%X] !\n",Status));
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCallDriver() FAILED [%X] !\n",Status));
				}

				continue;
			}
			else
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetCompletionRoutineEx() FAILED [%X] !\n",Status));
			}

			IoFreeIrp(InterruptRequestPacket);

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP RELEASED !\n"));
		}
		else
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoBuildAsynchronousFsdRequest() FAILED [%X] !\n",Status));
		}
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------