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
#include "FileLogger.h"
#include "CThread.h"
//-------------------------------------------------------------------------------------------------------
struct MY_WORK_QUEUE_ITEM
{
//-------------------------------------------------------------------------------------------------------
	PIO_WORKITEM												WorkQueueItem;
	PIRP														InterruptRequestPacket;
//-------------------------------------------------------------------------------------------------------
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
PIO_RESOURCE_REQUIREMENTS_LIST __stdcall ModifyResources(IN PIO_RESOURCE_REQUIREMENTS_LIST ResourceRequirementList);
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
NTSTATUS DispatchRead(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_WRITE)
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_DEVICE_CONTROL)
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_STARTIO)
void StartIO(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_SIMPLE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS CopyString(LPTSTR Destination, size_t DestinationLength, LPCTSTR Source)
{
	for(size_t Index=0;Index<DestinationLength;Index++)
	{
		Destination[Index]=Source[Index];

		if (Source[Index]=='\0')
		{
			break;
		}
	}

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS PrintfInteger(LPTSTR Destination, size_t DestinationLength, int Value)
{
	_snprintf(Destination,DestinationLength,"%d",Value);

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS LengthString(LPTSTR String, size_t MaximumStringLength, size_t* Length)
{
	*Length=0;

	for(size_t Index=0;Index<MaximumStringLength;Index++)
	{
		if (String[Index]=='\0')
		{
			return(STATUS_SUCCESS);
		}

		*Length=*Length+1;
	}

	return(STATUS_INVALID_PARAMETER);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void PrintReadBuffer(PCSTR UserModeBuffer, ULONG UserModeBufferLength)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!!!!!!! DATA LENGTH [%d] !\n",UserModeBufferLength);

	const ULONG													FRAGMENT_SIZE=200;
	ULONG														NumberOfFragments=((UserModeBufferLength % FRAGMENT_SIZE)==0) ? (UserModeBufferLength/FRAGMENT_SIZE) : ((UserModeBufferLength/FRAGMENT_SIZE)+1);

	for(ULONG Index=0;Index<NumberOfFragments;Index++)
	{
		CHAR													DataToPrint[FRAGMENT_SIZE+1];
		ULONG													FragmentSize;

		if (Index<(NumberOfFragments-1))
		{
			FragmentSize=FRAGMENT_SIZE;
		}
		else
		{
			FragmentSize=UserModeBufferLength-(Index * FRAGMENT_SIZE);
		}

		PCSTR													StartIndex=&UserModeBuffer[Index*FRAGMENT_SIZE];

		for(ULONG LocalIndex=0;LocalIndex<FragmentSize;LocalIndex++)
		{
			DataToPrint[LocalIndex]=StartIndex[LocalIndex];
		}

		DataToPrint[FragmentSize]='\0';

		// FUNCTION DbgPrint() moze naraz vypisat iba 512 CHARACTERS.
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!!!!!!! DATA to READ [%s] !\n",DataToPrint);
	}
}
//-------------------------------------------------------------------------------------------------------
void PrintWriteBuffer(PCSTR UserModeBuffer, ULONG UserModeBufferLength)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!!!!!!! DATA LENGTH [%d] !\n",UserModeBufferLength);

	const ULONG													FRAGMENT_SIZE=200;
	ULONG														NumberOfFragments=((UserModeBufferLength % FRAGMENT_SIZE)==0) ? (UserModeBufferLength/FRAGMENT_SIZE) : ((UserModeBufferLength/FRAGMENT_SIZE)+1);

	for(ULONG Index=0;Index<NumberOfFragments;Index++)
	{
		CHAR													DataToPrint[FRAGMENT_SIZE+1];
		ULONG													FragmentSize;

		if (Index<(NumberOfFragments-1))
		{
			FragmentSize=FRAGMENT_SIZE;
		}
		else
		{
			FragmentSize=UserModeBufferLength-(Index * FRAGMENT_SIZE);
		}

		PCSTR													StartIndex=&UserModeBuffer[Index*FRAGMENT_SIZE];

		for(ULONG LocalIndex=0;LocalIndex<FragmentSize;LocalIndex++)
		{
			DataToPrint[LocalIndex]=StartIndex[LocalIndex];
		}

		DataToPrint[FragmentSize]='\0';

		// FUNCTION DbgPrint() moze naraz vypisat iba 512 CHARACTERS.
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!!!!!!! DATA to WRITE [%s] !\n",DataToPrint);
	}
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

	WCHAR														DataToSendToUserMode[]=L"My name is Timmy Anderson !";
	ULONG														DataToSendToUserModeLength=sizeof(DataToSendToUserMode);
			
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
/*
VOID DoBugCheck(void)
{
	ULONG														ErrorCode=ERROR_SEVERITY_ERROR | APPLICATION_ERROR_MASK | 400;

	// !!!!! SPOSOBI PAD SYSTEMU.
	KeBugCheckEx(ErrorCode,100,200,300,400);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Pomocou MAP FILES sa mi SKUTOCNE podarilo zistit FUNCTION v ktorej doslo k BUG CHECK. Sacilo len odcitat hodnoty BASE ADDRESS a ADDRESS na ktorej doslo k BUG CHECK a nasledne pozriet do MAP FILE a najst, ktora FUNCTION ma tento OFFSET (hodnota [Rva+Base]-[Preferred load address]). Takto sa POLAHKY da najst ADDRESS FUNCTION, ktora sposobila BUG CHECK.
VOID DoAccessViolation(void)
{
	int*														Pointer=(int*) 100;

	// !!!!! SPOSOBI PAD SYSTEMU.
	*Pointer=200;
}
*/
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

	DriverObject->MajorFunction[IRP_MJ_READ]=DispatchRead;
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

	/*
	ULONG														ErrorCode=ERROR_SEVERITY_ERROR | APPLICATION_ERROR_MASK | 400;

	KeBugCheckEx(ErrorCode,100,200,300,400);
	*/
		
	// !!! Ak INTERRUPT NIE JE SPRACOVANY, tak sa MUSI vratit FALSE, aby INTERRUPT (ktory moze byt SHARED) mohol byt posunuty dalsim DRIVERS.
	return(FALSE);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_DPC_ROUTINE)
VOID DPCForISR(PKDPC, PDEVICE_OBJECT, PIRP, PVOID)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DPCForISR() CALLED !\n");

	/*
	ULONG														ErrorCode=ERROR_SEVERITY_ERROR | APPLICATION_ERROR_MASK | 400;

	KeBugCheckEx(ErrorCode,100,200,300,400);
	*/
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

		// !!!!! DRIVER definuje, ze sa bude pouzivat DIRECT MODE.
		NewDeviceObject->Flags|=DO_DIRECT_IO;

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

		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_MY_FULL_DRIVER,NULL,&DeviceExtensionData->InterfaceName);
		
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
		GenericInitStructure.MModifyResources=ModifyResources;

		// !!!!! [DEVQUEUE] sa ulozi do [GENERIC_INIT_STRUCT], aby [DEVQUEUE] bol spravovany STRUCTURE [GENERIC_EXTENSION].
		GenericInitStructure.MQueues[0].MDeviceQueue=&DeviceExtensionData->DevQueue;
		GenericInitStructure.MQueues[0].MStartIO=StartIO;
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
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RESOURCE TYPE [%d], FLAGS [%d], SHARE DISPOSITION [%d] !\n",Resource->Type,Resource->Flags,Resource->ShareDisposition);

		switch(Resource->Type)
		{
			case CmResourceTypeInterrupt:
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): LEVEL [%d], VECTOR [%d], AFFINITY [%I64X] !\n",Resource->u.Interrupt.Level,Resource->u.Interrupt.Vector,Resource->u.Interrupt.Affinity);

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

	/*
	// !!! Demonstruje vytvorenie SYSTEM THREAD.
	// !!!!! SYSTEM THREAD sa NEPOUZIVA v CODE. Iba CODE demonstruje vytvorenie THREAD a jeho nasledne uvolnenie.
	if (CThread::StartThread(DeviceExtensionData)==false)
	{
		return(STATUS_UNSUCCESSFUL);
	}
	*/

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

	// !!! Demonstruje uvolnenie SYSTEM THREAD.
	//CThread::StopThread(DeviceExtensionData);

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
// !!!!! FUNCTION je volana v momente, ked DEVICE MANAGER prideluje RESOURCES aktualneho DRIVER.
// !!!!! Ak CALLBACK ROUTINE NEPOTREBUJE modifikovat RESOURCES, tak MUSI vratit VSTUPNY PARAMETER.
// !!!!! Ak CALLBACK ROUTINE POTREBUJE modifikovat RESOURCES, tak MUSI UVOLNIT POINTER na ktory odkazuje VSTUPNY PARAMETER a ALOKOVAT NOVY MEMORY BLOCK v ktorom budu MODIFIKOVANE RESOURCES.
PIO_RESOURCE_REQUIREMENTS_LIST __stdcall ModifyResources(IN PIO_RESOURCE_REQUIREMENTS_LIST ResourceRequirementList)
{
	if (ResourceRequirementList!=NULL)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! NUMBER of LISTS [%d], LIST SIZE [%d] !\n",ResourceRequirementList->AlternativeLists,ResourceRequirementList->ListSize));

		if (ResourceRequirementList->AlternativeLists>0)
		{
			IO_RESOURCE_LIST									ResourceList=ResourceRequirementList->List[0];

			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! NUMBER of RESOURCES [%d] !\n",ResourceList.Count));

			for(ULONG Index=0;Index<ResourceList.Count;Index++)
			{
				IO_RESOURCE_DESCRIPTOR							ResourceDescriptor=ResourceList.Descriptors[Index];

				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RESOURCE TYPE [%d] !\n",ResourceDescriptor.Type);
			}
		}
	}

	return(ResourceRequirementList);
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
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	return(GenericDispatchPNP(DeviceExtension->PowerAndPNP,InterruptRequestPacket));
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
void ProcessReadIRP(PDEVICE_EXTENSION DeviceExtension, PIRP InterruptRequestPacket)
{
	const ULONG													DATA_LENGTH=12000;
	const ULONG													NUMBER_OF_ITERATIONS=2000;

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! V DIRECT MODE FIELD [IRP.MdlAddress] obsahuje POINTER na STRUCTURE [MDL].
	PMDL														CurrentMDL=InterruptRequestPacket->MdlAddress;

	// !!! V DIRECT MODE FUNCTION MmGetSystemAddressForMdlSafe() vracia POINTER na BUFFER v SYSTEM ADDRESS SPACE.
	PSTR														DataToRead=(PSTR) MmGetSystemAddressForMdlSafe(CurrentMDL,NormalPagePriority);
	size_t														NumberOfBytesWritten=0;

	if (DataToRead!=NULL)
	{
		ULONG													DataLengthToRead=MmGetMdlByteCount(CurrentMDL);
		bool													HasError=false;

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!!!!!!! DATA to READ [%d] !\n",DataLengthToRead);

		if (DataLengthToRead>=DATA_LENGTH)
		{
			for(;;)
			{
				CHAR											Prefix[]="HUGE TEXT READ [";

				if (NT_SUCCESS(Status=CopyString(&DataToRead[NumberOfBytesWritten],DATA_LENGTH-NumberOfBytesWritten,Prefix))==false)
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyString() FAILED [%X] !\n",Status);
					HasError=true;
					break;
				}

				NumberOfBytesWritten+=(sizeof(Prefix)-sizeof(CHAR));

				for(int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
				{
					CHAR										LocalBuffer[20];
					size_t										LocalBufferSize;

					if (NT_SUCCESS(Status=PrintfInteger(LocalBuffer,sizeof(LocalBuffer),Index+1))==false)
					{
						DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RtlStringCbPrintfA() FAILED [%X] !\n",Status);
						HasError=true;
						break;
					}

					if (NT_SUCCESS(Status=LengthString(LocalBuffer,sizeof(LocalBuffer),&LocalBufferSize))==false)
					{
						DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RtlStringCbLengthA() FAILED [%X] !\n",Status);
						HasError=true;
						break;
					}

					if (Index>0)
					{
						CHAR									Separator[]=",";

						if (NT_SUCCESS(Status=CopyString(&DataToRead[NumberOfBytesWritten],DATA_LENGTH-NumberOfBytesWritten,Separator))==false)
						{
							DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyString() FAILED [%X] !\n",Status);
							HasError=true;
							break;
						}

						NumberOfBytesWritten+=(sizeof(Separator)-sizeof(CHAR));
					}

					if (NT_SUCCESS(Status=CopyString(&DataToRead[NumberOfBytesWritten],DATA_LENGTH-NumberOfBytesWritten,LocalBuffer))==false)
					{
						DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyString() FAILED [%X] !\n",Status);
						HasError=true;
						break;
					}

					NumberOfBytesWritten+=LocalBufferSize;
				}

				if (HasError==false)
				{
					CHAR										Postfix[]="] !";

					if (NT_SUCCESS(Status=CopyString(&DataToRead[NumberOfBytesWritten],DATA_LENGTH-NumberOfBytesWritten,Postfix))==false)
					{
						DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyString() FAILED [%X] !\n",Status);
						HasError=true;
						break;
					}

					// !!! Vlozi sa aj znak '\0'.
					NumberOfBytesWritten+=sizeof(Postfix);
				}

				break;
			}

			if (HasError==false)
			{
				PrintReadBuffer(DataToRead,DataLengthToRead);
			}
			else
			{
				NumberOfBytesWritten=0;
			}
		}
		else
		{
			NumberOfBytesWritten=0;
		}
	}
	else
	{
		NumberOfBytesWritten=0;
	}

	/*
	// !!! Simulacia spomalenia spracovania IRP.
	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=30*1000*(-10*1000);

	// !!! POCKAM 30 SEKUND.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD DELAY FINISHED !\n");
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeDelayExecutionThread() FAILED [%X] !\n",Status);
	}
	*/

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!!!!!!! DEVICE READ [%I64X] BYTES !\n",NumberOfBytesWritten);

	// !!!!! Spusti sa vykonavanie dalsieho IRP ak je QUEUE.
	StartNextPacket(&DeviceExtension->DevQueue,DeviceExtension->DeviceObject);

	InterruptRequestPacket->IoStatus.Status=STATUS_SUCCESS;
	InterruptRequestPacket->IoStatus.Information=NumberOfBytesWritten;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(InterruptRequestPacket,NULL);

	// !!! Ukoncim IRP.
	// !!!!! Ak DRIVER dostal IRP z DRIVER VYSSIE v DRIVER STACK musi ho bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP was COMPLETED by DESTINATION DRIVER !\n");

	// !!! Kedze sa IRP SPRACOVAL, tak je NUTNE UVOLNIT REMOVE LOCK.
	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,InterruptRequestPacket);
}
//-------------------------------------------------------------------------------------------------------
void ProcessWriteIRP(PDEVICE_EXTENSION DeviceExtension, PIRP InterruptRequestPacket)
{
	const ULONG													FRAGMENT_SIZE=200;

	// !!! V DIRECT MODE FIELD [IRP.MdlAddress] obsahuje POINTER na STRUCTURE [MDL].
	PMDL														CurrentMDL=InterruptRequestPacket->MdlAddress;
	// !!! V DIRECT MODE FUNCTION MmGetSystemAddressForMdlSafe() vracia POINTER na BUFFER v SYSTEM ADDRESS SPACE.
	PCSTR														DataToWrite=(PCSTR) MmGetSystemAddressForMdlSafe(CurrentMDL,NormalPagePriority);
	ULONG														DataLengthToWrite=MmGetMdlByteCount(CurrentMDL);

	if (DataToWrite!=NULL)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!!!!!!! DATA LENGTH [%d] !\n",DataLengthToWrite);

		PrintWriteBuffer(DataToWrite,DataLengthToWrite);
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): MmGetSystemAddressForMdlSafe() FAILED !\n");

		DataLengthToWrite=0;
	}

	// !!!!! Spusti sa vykonavanie dalsieho IRP ak je QUEUE.
	StartNextPacket(&DeviceExtension->DevQueue,DeviceExtension->DeviceObject);

	InterruptRequestPacket->IoStatus.Status=STATUS_SUCCESS;
	InterruptRequestPacket->IoStatus.Information=DataLengthToWrite;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(InterruptRequestPacket,NULL);

	// !!! Ukoncim IRP.
	// !!!!! Ak DRIVER dostal IRP z DRIVER VYSSIE v DRIVER STACK musi ho bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP was COMPLETED by DESTINATION DRIVER !\n");

	// !!! Kedze sa IRP SPRACOVAL, tak je NUTNE UVOLNIT REMOVE LOCK.
	IoReleaseRemoveLock(&DeviceExtension->RemoveLock,InterruptRequestPacket);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
VOID MyWorkItemCallbackRead(PDEVICE_OBJECT DeviceObject, PVOID Parameter)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING WORK ITEM - READ !\n");

	MY_WORK_QUEUE_ITEM*											MyWorkQueueItem=(MY_WORK_QUEUE_ITEM*) Parameter;
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	PIRP														InterruptRequestPacket=MyWorkQueueItem->InterruptRequestPacket;

	// !!!!! WORK ITEM moze byt uvolneny v CALLBACK FUNCTION.
	IoFreeWorkItem(MyWorkQueueItem->WorkQueueItem);

	ExFreePoolWithTag(MyWorkQueueItem,' IQW');

	ProcessReadIRP(DeviceExtension,InterruptRequestPacket);
}
//-------------------------------------------------------------------------------------------------------
VOID MyWorkItemCallbackWrite(PDEVICE_OBJECT DeviceObject, PVOID Parameter)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING WORK ITEM - WRITE !\n");

	MY_WORK_QUEUE_ITEM*											MyWorkQueueItem=(MY_WORK_QUEUE_ITEM*) Parameter;
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	PIRP														InterruptRequestPacket=MyWorkQueueItem->InterruptRequestPacket;

	// !!!!! WORK ITEM moze byt uvolneny v CALLBACK FUNCTION.
	IoFreeWorkItem(MyWorkQueueItem->WorkQueueItem);

	ExFreePoolWithTag(MyWorkQueueItem,' IQW');

	ProcessWriteIRP(DeviceExtension,InterruptRequestPacket);
}
//-------------------------------------------------------------------------------------------------------
_Requires_lock_held_(_Global_cancel_spin_lock_)
_Function_class_(DRIVER_CANCEL)
_IRQL_raises_(DISPATCH_LEVEL)
void IRPQueueingCancellationRoutine(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	DbgPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	DEVICE_EXTENSION*											DeviceExtension=(DEVICE_EXTENSION*) DeviceObject->DeviceExtension;

	// !!! Odstrani IRP z IRP QUEUE.
	CancelRequest(&DeviceExtension->DevQueue,IRP);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_STARTIO)
void StartIO(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION CALLED !\n"));

	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	NTSTATUS													Status;
	bool														RemoveLockAcquired=false;

	// CURRENT DRIVER ziska REMOVE LOCK, aby sa zabranilo jeho predcasnemu odstraneniu z MEMORY IO MANAGER.
	if (NT_SUCCESS(Status=IoAcquireRemoveLock(&DeviceExtension->RemoveLock,NULL))==true)
	{
		RemoveLockAcquired=true;

		PIO_STACK_LOCATION										Stack=IoGetCurrentIrpStackLocation(InterruptRequestPacket);

		if (Stack->MajorFunction==IRP_MJ_READ)
		{
			// !!! WORK ITEM QUEUE sa alokuje a inicializuje.
			MY_WORK_QUEUE_ITEM*									MyWorkQueueItemStructure=(MY_WORK_QUEUE_ITEM*) ExAllocatePoolWithTag(NonPagedPool,sizeof(MY_WORK_QUEUE_ITEM),' IQW');
		
			if (MyWorkQueueItemStructure!=NULL)
			{
				PIO_WORKITEM									MyWorkQueueItem=IoAllocateWorkItem(DeviceObject);

				if (MyWorkQueueItem!=NULL)
				{
					MyWorkQueueItemStructure->WorkQueueItem=MyWorkQueueItem;
					MyWorkQueueItemStructure->InterruptRequestPacket=InterruptRequestPacket;

					// !!! WORK ITEM sa ulozi do QUEUE.
					// !!!!! Ked sa namiesto VALUE [DelayedWorkQueue] pouzila VALUE [NormalWorkQueue] DRIVER hodil BUG CHECK. Pri hodnote [DelayedWorkQueue] vsetko fungovalo OK.
					IoQueueWorkItem(MyWorkQueueItem,MyWorkItemCallbackRead,DelayedWorkQueue,MyWorkQueueItemStructure);

					return;
				}
				else
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAllocateWorkItem() FAILED !\n");

					ExFreePoolWithTag(MyWorkQueueItemStructure,' IQW');
				}
			}
			else
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExAllocatePoolWithTag() FAILED !\n");
			}
		}
		else if (Stack->MajorFunction==IRP_MJ_WRITE)
		{
			// !!! WORK ITEM QUEUE sa alokuje a inicializuje.
			MY_WORK_QUEUE_ITEM*									MyWorkQueueItemStructure=(MY_WORK_QUEUE_ITEM*) ExAllocatePoolWithTag(NonPagedPool,sizeof(MY_WORK_QUEUE_ITEM),' IQW');
		
			if (MyWorkQueueItemStructure!=NULL)
			{
				PIO_WORKITEM									MyWorkQueueItem=IoAllocateWorkItem(DeviceObject);

				if (MyWorkQueueItem!=NULL)
				{
					MyWorkQueueItemStructure->WorkQueueItem=MyWorkQueueItem;
					MyWorkQueueItemStructure->InterruptRequestPacket=InterruptRequestPacket;

					// !!! WORK ITEM sa ulozi do QUEUE.
					// !!!!! Ked sa namiesto VALUE [DelayedWorkQueue] pouzila VALUE [NormalWorkQueue] DRIVER hodil BUG CHECK. Pri hodnote [DelayedWorkQueue] vsetko fungovalo OK.
					IoQueueWorkItem(MyWorkQueueItem,MyWorkItemCallbackWrite,DelayedWorkQueue,MyWorkQueueItemStructure);

					return;
				}
				else
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAllocateWorkItem() FAILED !\n");

					ExFreePoolWithTag(MyWorkQueueItemStructure,' IQW');
				}
			}
			else
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExAllocatePoolWithTag() FAILED !\n");
			}
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): UNSUPPORTED MAJOR FUNCTION [%d] !\n",Stack->MajorFunction);
		}
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
	}

	// !!!!! Spusti sa vykonavanie dalsieho IRP ak je QUEUE.
	StartNextPacket(&DeviceExtension->DevQueue,DeviceObject);

	// !!!!! Pri ERROR MUSI DRIVER VZDY IRP UKONCIT volanim FUNCTION IoCompleteRequest().

	InterruptRequestPacket->IoStatus.Status=STATUS_UNSUCCESSFUL;
	InterruptRequestPacket->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(InterruptRequestPacket,NULL);

	// !!! Ukoncim IRP.
	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

	if (RemoveLockAcquired==true)
	{
		// !!! Kedze sa IRP SPRACOVAL, tak je NUTNE UVOLNIT REMOVE LOCK.
		IoReleaseRemoveLock(&DeviceExtension->RemoveLock,InterruptRequestPacket);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_READ)
NTSTATUS DispatchRead(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);
	
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - MdlAddress [%p], UserBuffer [%p], AssociatedIrp.SystemBuffer [%p] !\n",InterruptRequestPacket->MdlAddress,InterruptRequestPacket->UserBuffer,InterruptRequestPacket->AssociatedIrp.SystemBuffer);

	// !!!!! FUNCTION IoAcquireRemoveLock() sa NESMIE volat v tejto FUNCTION, ale az vo FUNCTION StartIO(). Je to NEVYHNUTNE, pretoze ak som tu zavolal FUNCTION IoAcquireRemoveLock(), tak pri IRP CANCELLATION (ked som cez CTRL-C uzatvoril beziaci TEST PROGRAM) a v DEVQUEUE boli nejake IRP, tieto sa sice UVOLNILI (boli CANCELLED), ale LOCK NEBOL DEKREMENTOVANY. Vysledok bol taky, ze sice REBOOT VIRTUAL MACHINE isiel korektne, ale pri pokuse odstranit DRIVER doslo k LOCK a WINDOWS do nekonecna cakal na uvolnenie LOCK.
	// !!!!! Ak sa FUNCTION IoAcquireRemoveLock() zavola az vo FUNCTION StartIO() k tomuto problemu nedochadza, pretoze FUNCTION StartIO() sa vola pri SPUSTENI SPRACOVANI IRP a teda ak su este IRP v DEVQUEUE, tak sa FUNCTION IoAcquireRemoveLock() pre ne nezavolala. Tym padom je LOCK vzdy iba na maximalnej hodnote 1, ktora klesne na 0, ked sa prace spracovany IRP ukonci. Tym padom NEDOCHADZA k VIACNASOBNEMU zamknutiu REMOVE LOCK.

	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// !!! Kedze IRP NEBUDE OKAMZITE spracovane, nastavi sa do PENDING STATE.
	IoMarkIrpPending(InterruptRequestPacket);

	// !!!!! IRP sa ulozi do QUEUE.
	// !!! FUNCTION zaroven nastavi CANCEL ROUTINE.
	StartPacket(&DeviceExtension->DevQueue,DeviceObject,InterruptRequestPacket,IRPQueueingCancellationRoutine);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	// !!! Kedze IRP NEBUDE OKAMZITE spracovane, ako RETURN VALUE sa vrati hodnota [STATUS_PENDING].
	return(STATUS_PENDING);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_WRITE)
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);
	
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - MdlAddress [%p], UserBuffer [%p], AssociatedIrp.SystemBuffer [%p] !\n",InterruptRequestPacket->MdlAddress,InterruptRequestPacket->UserBuffer,InterruptRequestPacket->AssociatedIrp.SystemBuffer);

	// !!!!! FUNCTION IoAcquireRemoveLock() sa NESMIE volat v tejto FUNCTION, ale az vo FUNCTION StartIO(). Je to NEVYHNUTNE, pretoze ak som tu zavolal FUNCTION IoAcquireRemoveLock(), tak pri IRP CANCELLATION (ked som cez CTRL-C uzatvoril beziaci TEST PROGRAM) a v DEVQUEUE boli nejake IRP, tieto sa sice UVOLNILI (boli CANCELLED), ale LOCK NEBOL DEKREMENTOVANY. Vysledok bol taky, ze sice REBOOT VIRTUAL MACHINE isiel korektne, ale pri pokuse odstranit DRIVER doslo k LOCK a WINDOWS do nekonecna cakal na uvolnenie LOCK.
	// !!!!! Ak sa FUNCTION IoAcquireRemoveLock() zavola az vo FUNCTION StartIO() k tomuto problemu nedochadza, pretoze FUNCTION StartIO() sa vola pri SPUSTENI SPRACOVANI IRP a teda ak su este IRP v DEVQUEUE, tak sa FUNCTION IoAcquireRemoveLock() pre ne nezavolala. Tym padom je LOCK vzdy iba na maximalnej hodnote 1, ktora klesne na 0, ked sa prace spracovany IRP ukonci. Tym padom NEDOCHADZA k VIACNASOBNEMU zamknutiu REMOVE LOCK.

	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// !!! Kedze IRP NEBUDE OKAMZITE spracovane, nastavi sa do PENDING STATE.
	IoMarkIrpPending(InterruptRequestPacket);

	// !!!!! IRP sa ulozi do QUEUE.
	// !!! FUNCTION zaroven nastavi CANCEL ROUTINE.
	StartPacket(&DeviceExtension->DevQueue,DeviceObject,InterruptRequestPacket,IRPQueueingCancellationRoutine);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

	// !!! Kedze IRP NEBUDE OKAMZITE spracovane, ako RETURN VALUE sa vrati hodnota [STATUS_PENDING].
	return(STATUS_PENDING);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
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

		default:
		{
			Status=STATUS_INVALID_DEVICE_REQUEST;
		}
		break;
	}

	// !!! Ukonci spracovanie IRP PACKET, ktory reprezentuje SYSTEM CONTROL.
	Status=CompleteRequest(InterruptRequestPacket,Status,Info);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASING - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status);

	// !!!!!! Z MSDN. For I/O operations (including power and PnP IRPs) that set an IoCompletion() routine, a driver should call IoReleaseRemoveLock() in the IoCompletion() routine, after calling IoCompleteRequest().
	IoReleaseRemoveLock(&DeviceExtensionData->RemoveLock,InterruptRequestPacket);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END 2 - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status);

	return(Status);
}
//-------------------------------------------------------------------------------------------------------