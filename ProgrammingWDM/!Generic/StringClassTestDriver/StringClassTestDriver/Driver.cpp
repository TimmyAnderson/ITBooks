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
#include "Log.h"
#include "UnicodeString.h"
//-------------------------------------------------------------------------------------------------------
CLog*															LOG=NULL;
UCHAR															Component[]="MyDriver";
//-------------------------------------------------------------------------------------------------------
VOID DPCForISR(PKDPC DeferredProcedureCall, PDEVICE_OBJECT DeviceObject, PIRP, PVOID Context);
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PDO);
//-------------------------------------------------------------------------------------------------------
NTSTATUS __stdcall StartDevice(PDEVICE_OBJECT DeviceObject, PCM_PARTIAL_RESOURCE_LIST, PCM_PARTIAL_RESOURCE_LIST);
VOID __stdcall StopDevice(IN PDEVICE_OBJECT DeviceObject, BOOLEAN);
VOID __stdcall RemoveDevice(IN PDEVICE_OBJECT DeviceObject);
//-------------------------------------------------------------------------------------------------------
NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
NTSTATUS DispatchCleanup(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
NTSTATUS DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
NTSTATUS DispatchPNP(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
NTSTATUS DispatchWMI(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
NTSTATUS DispatchShutdown(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
//-------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRead(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket);
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_SIMPLE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_STRING_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! Simuluje UKONCENIE IRP po nejakom case, ktory simuluje PROCESSING IRP.
void IRPCompleteSimulator(PVOID Parameter)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n"));

	PIRP														InterruptRequestPacket=(PIRP) Parameter;
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=2*1000*(-10*1000);

	// !!! POCKAM 2 SEKUNDY.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): THREAD DELAY FINISHED !\n",Status));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	InterruptRequestPacket->IoStatus.Status=STATUS_SUCCESS;
	InterruptRequestPacket->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(InterruptRequestPacket,NULL);

	// !!! Ukoncim IRP.
	// !!!!! Ak DRIVER dostal IRP z DRIVER VYSSIE v DRIVER STACK musi ho bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! IRP was COMPLETED by DESTINATION DRIVER !\n"));

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n"));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlSimpleTest(PIRP InterruptRequestPacket, DEVICE_EXTENSION*, ULONG, ULONG InputBufferLength, ULONG OutputBufferLength, ULONG& Info)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// Alokujem aj miesto pre NULL TERMINATOR.
	SIZE_T														DataFromInputBufferLength=InputBufferLength+sizeof(CHAR);
	CHAR*														DataFromInputBuffer=(CHAR*) ExAllocatePool(PagedPool,DataFromInputBufferLength);

	if (DataFromInputBuffer!=NULL)
	{
		RtlZeroMemory(DataFromInputBuffer,DataFromInputBufferLength);

		// Do DataFromInputBuffer sa ulozia BYTES z INPUT BUFFER, pricom DataFromInputBuffer ma este o 1 BYTE navyse na ulozenie NULL TERMINATOR.
		// !!!!! FIELD InterruptRequestPacket->AssociatedIrp.SystemBuffer obsahuje INPUT aj OUTPUT BUFFER.
		RtlCopyMemory(DataFromInputBuffer,InterruptRequestPacket->AssociatedIrp.SystemBuffer,InputBufferLength);

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
		ExFreePool(DataFromInputBuffer);
		DataFromInputBuffer=NULL;
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void PrintString(const CUnicodeString& UnicodeString)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): STRING has VALUE [%wZ], LengthInBytes() [%d], LengthInChars() [%d], MaximumLengthInBytes [%d] !\n",UnicodeString.operator const UNICODE_STRING &(),UnicodeString.LengthInBytes(false),UnicodeString.LengthInChars(false),UnicodeString.GetUNICODE_STRING().MaximumLength);
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): STRING has VALUE [%wZ], LengthInBytes() [%d], LengthInChars() [%d], MaximumLengthInBytes [%d] !\n",UnicodeString.GetUNICODE_STRING(),UnicodeString.LengthInBytes(false),UnicodeString.LengthInChars(false),UnicodeString.GetUNICODE_STRING().MaximumLength);
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): STRING has VALUE [%S], LengthInBytes() [%d], LengthInChars() [%d], MaximumLengthInBytes [%d] !\n",UnicodeString.operator PWSTR(),UnicodeString.LengthInBytes(false),UnicodeString.LengthInChars(false),UnicodeString.GetUNICODE_STRING().MaximumLength);
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): STRING has VALUE [%S], LengthInBytes() [%d], LengthInChars() [%d], MaximumLengthInBytes [%d] !\n",UnicodeString.GetUnicodeString(),UnicodeString.LengthInBytes(false),UnicodeString.LengthInChars(false),UnicodeString.GetUNICODE_STRING().MaximumLength);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS ProcessIOControlStringTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): STRING TEST STARTED !\n"));

	{
		CUnicodeString											String1("Timmy Anderson");

		String1.DumpState();
		String1=CUnicodeString("My name is Jenny Thompson !");
		String1.DumpState();
		String1=CUnicodeString("Atreyu");
		String1.DumpState();

		CUnicodeString*											String2=new CUnicodeString("Timmy Anderson");

		if (String2!=NULL)
		{
			String2->DumpState();
			*String2=CUnicodeString("My name is Jenny Thompson !");
			String2->DumpState();
			*String2=CUnicodeString("Atreyu");
			String2->DumpState();

			delete(String2);
		}
	}

	{
		CUnicodeString											String1(L"Timmy");
		CUnicodeString											String2(L"Anderson");

		String1+=CUnicodeString(" ");

		CUnicodeString											String3=String1+String2;

		PrintString(String3);
	}

	{
		CUnicodeString											String1(L"Timmy");
		CUnicodeString											String2(12);

		String1+=CUnicodeString(" ");

		CUnicodeString											String3=String1+String2;

		PrintString(String1);
		PrintString(String2);
		PrintString(String3);
		
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): STRING [%S] - ULONG [%d] !\n",String1.GetUnicodeString(),String1.operator ULONG()));
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): STRING [%S] - ULONG [%d] !\n",String2.GetUnicodeString(),String2.operator ULONG()));
	}

	{
		CUnicodeString											String(L"Timmy Anderson");
		wchar_t													Buffer[100];

		RtlZeroMemory(Buffer,sizeof(Buffer));

		for(int Index=0;Index<String.LengthInChars(true);Index++)
		{
			Buffer[Index]=String[Index];
		}

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BUFFER [%S] !\n",Buffer));
	}

	{
		CUnicodeString												String(L"Timmy");
		CUnicodeString												StringCompare1(L"Timmy");
		CUnicodeString												StringCompare2(L"TIMMY");
		CUnicodeString												StringCompare3(L"XXX");
		
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): [%S]==[%S] -> [%d] !\n",String.GetUnicodeString(),StringCompare1.GetUnicodeString(),String==StringCompare1));
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): [%S]==[%S] -> [%d] !\n",String.GetUnicodeString(),StringCompare2.GetUnicodeString(),String==StringCompare2));
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): [%S]==[%S] -> [%d] !\n",String.GetUnicodeString(),StringCompare3.GetUnicodeString(),String==StringCompare3));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): STRING TEST FINISHED !\n"));

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryKey)
{
	ANSI_STRING													RegistryKeyANSI;

	RtlUnicodeStringToAnsiString(&RegistryKeyANSI,RegistryKey,TRUE);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DriverObject [%p], RegistryKey [%s] !\n",DriverObject,RegistryKeyANSI.Buffer));
	
	RtlFreeAnsiString(&RegistryKeyANSI);

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

	if ((LOG=new CLog(LOGFILE))!=NULL)
	{
		return(STATUS_SUCCESS);
	}
	else
	{
		return(STATUS_UNSUCCESSFUL);
	}
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DriverObject [%p] !\n",DriverObject));
	
	if (LOG!=NULL)
	{
		delete(LOG);
		LOG=NULL;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
BOOLEAN MyInterruptServiceRoutine(PKINTERRUPT, PVOID Context)
{
	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) Context;

	LONG														Value=InterlockedIncrement(&DeviceExtensionData->InterruptCounter);

	if ((Value % 100)==0)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): MyInterruptServiceRoutine() CALLED, VALUE [%d] !\n",Value));

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
VOID DPCForISR(PKDPC, PDEVICE_OBJECT, PIRP, PVOID)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DPCForISR() CALLED !\n"));

	/*
	ULONG														ErrorCode=ERROR_SEVERITY_ERROR | APPLICATION_ERROR_MASK | 400;

	KeBugCheckEx(ErrorCode,100,200,300,400);
	*/
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PhysicalDeviceObject)
{
	PAGED_CODE();
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DriverObject [%p], PhysicalDeviceObject [%p] !\n",DriverObject,PhysicalDeviceObject));

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
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCreateDevice() FAILED [%X] !\n",Status));
		return(Status);
	}
	
	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) NewDeviceObject->DeviceExtension;

	DeviceExtensionData->InterruptObject=NULL;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoCreateSymbolicLink() FAILED [%X] !\n",Status));
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
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAttachDeviceToDeviceStack() FAILED !\n"));
			Status=STATUS_DEVICE_REMOVED;
			break;
		}

		NewDeviceObject->Flags|=DO_POWER_PAGABLE;

		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_STRING_CLASS_TEST_DRIVER,NULL,&DeviceExtensionData->InterfaceName);
		
		if (NT_SUCCESS(Status)==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoRegisterDeviceInterface() FAILED [%X] !\n",Status));
			break;
		}

		Status=IoSetDeviceInterfaceState(&DeviceExtensionData->InterfaceName,TRUE);
		
		if (NT_SUCCESS(Status)==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoSetDeviceInterfaceState() FAILED [%X] !\n",Status));
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

		IsGenericExtensionInitialized=true;

		// !!! Zaregistrujem SHUTDOWN ROUTINE.
		IoRegisterShutdownNotification(NewDeviceObject);

		// !!! Po zruseni FLAG 'DO_DEVICE_INITIALIZING' je DEVICE_OBJECT pripraveny prijimat IRP.
		NewDeviceObject->Flags&=~DO_DEVICE_INITIALIZING;

		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DEVICE_OBJECT INITIALIZED, Flags [%X], Characteristics [%X], AlignmentRequirement [%X], STACK SIZE [%d] !\n",NewDeviceObject->Flags,NewDeviceObject->Characteristics,NewDeviceObject->AlignmentRequirement,NewDeviceObject->StackSize));

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
#pragma PAGEDCODE
// !!!!! FUNCTION je volana potom co IRP bol odoslany a spracovany DRIVERS NIZSIE v DRIVER STACK.
NTSTATUS __stdcall StartDevice(PDEVICE_OBJECT DeviceObject, PCM_PARTIAL_RESOURCE_LIST RawList, PCM_PARTIAL_RESOURCE_LIST TranslatedList)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], RawList [%p], TranslatedList [%p] !\n",DeviceObject,RawList,TranslatedList));

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
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): TRANSLATED LIST is NULL !\n"));
		return(STATUS_DEVICE_CONFIGURATION_ERROR);
	}

	PCM_PARTIAL_RESOURCE_DESCRIPTOR								Resource=TranslatedList->PartialDescriptors;
	ULONG														NumberOfResources=TranslatedList->Count;

	for (ULONG Index=0;Index<NumberOfResources;++Index,++Resource)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RESOURCE TYPE [%d] !\n",Resource->Type));

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
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Unexpected I/O resource type [%d] !\n",Resource->Type));
			}
			break;
		}
	}

	if (GotInterrupt==FALSE)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Didn't get expected I/O resources !\n"));
		return(STATUS_DEVICE_CONFIGURATION_ERROR);
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CONNECTING INTERRUPT REQUEST - Vector [%X], IRQL [%X], Mode [%X], IRQShare [%X], Affinity [%X] !\n",Vector,IRQL,Mode,IRQShare,Affinity));

	// !!! REALNY DEVICE by tu mal prinutit DEVICE, aby zastavil generovanie INTERRUPTS. Generovanie INTERRUPTS by sa malo obnovit az po dokonceni FUNCTION IoConnectInterrupt().

	LOG->WriteToLog("TEST 1 !\n");

	NTSTATUS													Status;

	if (NT_SUCCESS(Status=IoConnectInterrupt(&DeviceExtensionData->InterruptObject,(PKSERVICE_ROUTINE) MyInterruptServiceRoutine,(PVOID) DeviceExtensionData,NULL,Vector,IRQL,IRQL,Mode,IRQShare,Affinity,FALSE))==false)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoConnectInterrupt() FAILED [%X] !\n",Status));
		return(Status);
	}

	LOG->WriteToLog("TEST 2 !\n");

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
// !!!!! FUNCTION je volana potom co IRP bol odoslany a spracovany DRIVERS NIZSIE v DRIVER STACK.
VOID __stdcall StopDevice(IN PDEVICE_OBJECT DeviceObject, BOOLEAN)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p] !\n",DeviceObject));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	if (DeviceExtensionData->InterruptObject!=NULL)
	{
		// !!! REALNY DEVICE by tu mal prinutit DEVICE, aby zastavil generovanie INTERRUPTS.
		IoDisconnectInterrupt(DeviceExtensionData->InterruptObject);
		DeviceExtensionData->InterruptObject=NULL;
	}
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
// !!!!! FUNCTION je volana potom co IRP bol odoslany a spracovany DRIVERS NIZSIE v DRIVER STACK.
VOID __stdcall RemoveDevice(IN PDEVICE_OBJECT DeviceObject)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p] !\n",DeviceObject));

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
#pragma PAGEDCODE
NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// Inkrementuje sa HANDLER COUNTER.
	InterlockedIncrement(&DeviceExtensionData->Handles);

	// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	NTSTATUS													Status=CompleteRequest(InterruptRequestPacket,STATUS_SUCCESS,0);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X], Handles [%d] !\n",DeviceObject,InterruptRequestPacket,Status,DeviceExtensionData->Handles));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION sa vola, ked USER MODE PROCESS uzatvori HANDLE na DRIVER.
#pragma PAGEDCODE
NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// Dekrementuje sa HANDLER COUNTER.
	InterlockedDecrement(&DeviceExtensionData->Handles);

	// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	NTSTATUS													Status=CompleteRequest(InterruptRequestPacket,STATUS_SUCCESS,0);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X], Handles [%d] !\n",DeviceObject,InterruptRequestPacket,Status,DeviceExtensionData->Handles));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
// !!!!! FUNCTION vykonava CLEANUP IRP, ktore vytvoril konciaci PROCESS.
NTSTATUS DispatchCleanup(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	// !!!!! IRP z DRIVER VYSSIE v DRIVER STACK musi DRIVER bud UKONCIT volanim FUNCTION IoCompleteRequest(), alebo ho preposlat do DRIVER NIZSIE v DRIVER STACK, ktory ho ukonci volanim FUNCTION IoCompleteRequest().
	NTSTATUS													Status=CompleteRequest(InterruptRequestPacket,STATUS_SUCCESS,0);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X], Handles [%d] !\n",DeviceObject,InterruptRequestPacket,Status,DeviceExtensionData->Handles));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	return(GenericDispatchPower(DeviceExtensionData->PowerAndPNP,InterruptRequestPacket));
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchPNP(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();
	
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	return(GenericDispatchPNP(DeviceExtension->PowerAndPNP,InterruptRequestPacket));
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchWMI(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	PDEVICE_EXTENSION											PDX=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	IoSkipCurrentIrpStackLocation(InterruptRequestPacket);

	return(IoCallDriver(PDX->LowerDeviceObject,InterruptRequestPacket));
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchShutdown(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	return(CompleteRequest(InterruptRequestPacket,STATUS_SUCCESS));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRead(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	// !!!!! EMULUJEM SYNCHRONNY KONIEC IRP.

	InterruptRequestPacket->IoStatus.Status=STATUS_SUCCESS;
	InterruptRequestPacket->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(InterruptRequestPacket,NULL);

	// !!! Ukoncim InterruptRequestPacket.
	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

	// !!!!! Ak DISPATCH ROUTINE ukoncuje IPR volanim FUNCTION IoCompleteRequest(), tak MUSI ako RETURN VALUE vratit TU ISTU HODNOTU, aku nastavil v MEMBER IRP.IoStatus.Status. Ak vrati INU VALUE, VERIFIER sposobi BUG CHECK.
	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));
	
	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - MdlAddress [%p], UserBuffer [%p], AssociatedIrp.SystemBuffer [%p] !\n",InterruptRequestPacket->MdlAddress,InterruptRequestPacket->UserBuffer,InterruptRequestPacket->AssociatedIrp.SystemBuffer));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	// !!!!! V THREADE sa SIMULUJE PROCESSING IRP.
	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,IRPCompleteSimulator,InterruptRequestPacket))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n"));

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;

		// !!!!! IRP je NUTNE nastavit na PENDING.
		IoMarkIrpPending(InterruptRequestPacket);

		// !!!!! Kedze IRP NEBOL SKONCENY, tak sa vracia hodnota STATUS_PENDING.
		return(STATUS_PENDING);
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));

		// !!!!! Pri ERROR MUSI DRIVER VZDY IRP UKONCIT volanim FUNCTION IoCompleteRequest().

		InterruptRequestPacket->IoStatus.Status=STATUS_UNSUCCESSFUL;
		InterruptRequestPacket->IoStatus.Information=NULL;

		// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
		IoSetCancelRoutine(InterruptRequestPacket,NULL);

		// !!! Ukoncim IRP.
		IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

		// !!!!! Ak DISPATCH ROUTINE ukoncuje IPR volanim FUNCTION IoCompleteRequest(), tak MUSI ako RETURN VALUE vratit TU ISTU HODNOTU, aku nastavil v MEMBER IRP.IoStatus.Status. Ak vrati INU VALUE, VERIFIER sposobi BUG CHECK.
		return(STATUS_UNSUCCESSFUL);
	}
}
//-------------------------------------------------------------------------------------------------------
/*
// !!! SIMULACIA ERROR.
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));

	// !!!!! Pri ERROR MUSI DRIVER VZDY IRP UKONCIT volanim FUNCTION IoCompleteRequest().

	InterruptRequestPacket->IoStatus.Status=STATUS_UNSUCCESSFUL;
	InterruptRequestPacket->IoStatus.Information=NULL;

	// !!! Odstranim CANCELLATION ROUTINE, kedze IRP bude ukonceny.
	IoSetCancelRoutine(InterruptRequestPacket,NULL);

	// !!! Ukoncim IRP.
	IoCompleteRequest(InterruptRequestPacket,IO_NO_INCREMENT);

	// !!!!! Ak DISPATCH ROUTINE ukoncuje IPR volanim FUNCTION IoCompleteRequest(), tak MUSI ako RETURN VALUE vratit TU ISTU HODNOTU, aku nastavil v MEMBER IRP.IoStatus.Status. Ak vrati INU VALUE, VERIFIER sposobi BUG CHECK.
	return(STATUS_UNSUCCESSFUL);
}
*/
//-------------------------------------------------------------------------------------------------------
// FUNCTION spracovava IO CONTROL MESSAGES.
#pragma PAGEDCODE
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	PAGED_CODE();

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	NTSTATUS													Status;
	ULONG														Info=0;

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK ACQUIRING - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));
	
	Status=IoAcquireRemoveLock(&DeviceExtensionData->RemoveLock,InterruptRequestPacket);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END 1 - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status));

		return(CompleteRequest(InterruptRequestPacket,Status,0));
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK ACQUIRED - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status));

	PIO_STACK_LOCATION											Stack=IoGetCurrentIrpStackLocation(InterruptRequestPacket);
	ULONG														Code=Stack->Parameters.DeviceIoControl.IoControlCode;
	ULONG														InputBufferLength=Stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG														OutputBufferLength=Stack->Parameters.DeviceIoControl.OutputBufferLength;

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Code [%d], InputBufferLength [%d], OutputBufferLength [%d] !\n",Code,InputBufferLength,OutputBufferLength));

	switch(Code)
	{
		case IOCTL_SIMPLE_TEST:
		{
			Status=ProcessIOControlSimpleTest(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_STRING_TEST:
		{
			Status=ProcessIOControlStringTest(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		default:
		{
			Status=STATUS_INVALID_DEVICE_REQUEST;
		}
		break;
	}

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASING - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status));

	IoReleaseRemoveLock(&DeviceExtensionData->RemoveLock,InterruptRequestPacket);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): REMOVE LOCK RELEASED - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status));

	// !!! Ukonci spracovanie IRP PACKET, ktory reprezentuje SYSTEM CONTROL.
	Status=CompleteRequest(InterruptRequestPacket,Status,Info);

	KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): END 2 - DeviceObject [%p], InterruptRequestPacket [%p], Status [%X] !\n",DeviceObject,InterruptRequestPacket,Status));

	return(Status);
}
//-------------------------------------------------------------------------------------------------------