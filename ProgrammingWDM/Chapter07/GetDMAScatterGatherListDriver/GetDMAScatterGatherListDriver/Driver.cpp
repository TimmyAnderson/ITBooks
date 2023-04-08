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
// !!! Testovanie DRIVER by malo byt vykonane pre [MAX_SIZE_OF_SCATTER_GATHER_LIST=1] aj [MAX_SIZE_OF_SCATTER_GATHER_LIST=2].
//const int														MAX_ELEMENTS_TO_PROCEED_BY_HW=1;
const int														MAX_ELEMENTS_TO_PROCEED_BY_HW=2;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void PrintReadBuffer(PSTR UserModeBuffer, ULONG UserModeBufferLength)
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
void PrintWriteBuffer(PSTR UserModeBuffer, ULONG UserModeBufferLength)
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
// 2. PARAMETER sa NEPOUZIVA, pretoze IRP sa vybera z DEVQUEUE.
void ReadIRPDMAExecutionRoutine(PDEVICE_OBJECT, PIRP, PSCATTER_GATHER_LIST ScatterGatherList, PVOID Context)
{
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) Context;

	DeviceExtension->DMAScatterGatherList=ScatterGatherList;
	DeviceExtension->DMAActualIndexOfSGLElement=0;
	DeviceExtension->DMANumberOfProcessedSGLElementsForCurrentStage=0;

	// !!! Pocet ELEMENTS, ktore je este treba preniest.
	ULONG														NumberOfElementsToProceed=DeviceExtension->DMAScatterGatherList->NumberOfElements-DeviceExtension->DMAActualIndexOfSGLElement;

	if (NumberOfElementsToProceed>MAX_ELEMENTS_TO_PROCEED_BY_HW)
	{
		NumberOfElementsToProceed=MAX_ELEMENTS_TO_PROCEED_BY_HW;
	}

	DeviceExtension->DMANumberOfProcessedSGLElementsForCurrentStage=NumberOfElementsToProceed;

	// !!!!! Teraz by sa mal spustit prenos dat ho HW DEVICE pomocou HW DEVICE CUSTOM OPERATIONS.

	// !!! Vypisu sa PHYSICAL ADDRESS do LOGU.
	for(ULONG Index=0;Index<NumberOfElementsToProceed;Index++)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! [%I64X], SIZE [%d] !\n",DeviceExtension->DMAScatterGatherList->Elements[DeviceExtension->DMAActualIndexOfSGLElement].Address.QuadPart,DeviceExtension->DMAScatterGatherList->Elements[DeviceExtension->DMAActualIndexOfSGLElement].Length);
	}

	// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
	DeviceExtension->ReadyForDMAInterrupt=true;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Tento CODE sluziaci iba na EMULALCIU DMA NIE JE CELKOM BEZPECNY. Ak by totizto tento CODE trval prilis dlho a INTERRUPT, ktorym sa posuva spracovanie medzi STAGES v DEFFERED PROCEDURE CALL by sa spustil v jeho priebehu, mohlo by dojst k BUG CHECK.
void ProcessReadIRP(PDEVICE_EXTENSION DeviceExtension, PIRP InterruptRequestPacket)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	// !!! V DIRECT MODE FIELD [IRP.MdlAddress] obsahuje POINTER na STRUCTURE [MDL].
	PMDL														CurrentMDL=InterruptRequestPacket->MdlAddress;

	// !!!!! Vyzera to, ze POINTER vrateny ako RETURN VALUE NESMIE byt NIJAKO UVOLNENY. Uvolnovanie robi IO MANAGER, ktory IRP a s nim asociovany MDL vytvoril.
	DeviceExtension->UserModeBufferForCurrentDMATransfer=PCHAR(MmGetSystemAddressForMdlSafe(CurrentMDL,NormalPagePriority));

	if (DeviceExtension->UserModeBufferForCurrentDMATransfer!=nullptr)
	{
		// Ulozi sa pocet BYTES, ktore sa pocas TRANSFER maju preniest.
		DeviceExtension->DMANumberOfBytesRemainingToTransfer=MmGetMdlByteCount(CurrentMDL);

		PVOID													VirtualAddress=MmGetMdlVirtualAddress(CurrentMDL);

		if (NT_SUCCESS(Status=(*DeviceExtension->DMAAddapter->DmaOperations->GetScatterGatherList)(DeviceExtension->DMAAddapter,DeviceExtension->DeviceObject,CurrentMDL,VirtualAddress,DeviceExtension->DMANumberOfBytesRemainingToTransfer,(PDRIVER_LIST_CONTROL) ReadIRPDMAExecutionRoutine,DeviceExtension,FALSE))==true)
		{
			return;
		}
		// !!!!! Ak je pocet BYTES, ktore maju byt prenesene prilis VELKY, tak GetScatterGatherList() hodi ERROR [STATUS_INSUFFICIENT_RESOURCES].
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA::GetScatterGatherList() FAILED [%X] !\n",Status);
		}
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): MmGetSystemAddressForMdlSafe() FAILED !\n");
	}

	// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
	DeviceExtension->ReadyForDMAInterrupt=false;

	// !!!!! Spusti sa vykonavanie dalsieho IRP ak je QUEUE.
	StartNextPacket(&DeviceExtension->DevQueue,DeviceExtension->DeviceObject);

	InterruptRequestPacket->IoStatus.Status=Status;
	InterruptRequestPacket->IoStatus.Information=0;

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
// 2. PARAMETER sa NEPOUZIVA, pretoze IRP sa vybera z DEVQUEUE.
void WriteIRPDMAExecutionRoutine(PDEVICE_OBJECT, PIRP, PSCATTER_GATHER_LIST ScatterGatherList, PVOID Context)
{
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) Context;

	DeviceExtension->DMAScatterGatherList=ScatterGatherList;
	DeviceExtension->DMAActualIndexOfSGLElement=0;
	DeviceExtension->DMANumberOfProcessedSGLElementsForCurrentStage=0;

	// !!! Pocet ELEMENTS, ktore je este treba preniest.
	ULONG														NumberOfElementsToProceed=DeviceExtension->DMAScatterGatherList->NumberOfElements-DeviceExtension->DMAActualIndexOfSGLElement;

	if (NumberOfElementsToProceed>MAX_ELEMENTS_TO_PROCEED_BY_HW)
	{
		NumberOfElementsToProceed=MAX_ELEMENTS_TO_PROCEED_BY_HW;
	}

	DeviceExtension->DMANumberOfProcessedSGLElementsForCurrentStage=NumberOfElementsToProceed;

	// !!!!! Teraz by sa mal spustit prenos dat ho HW DEVICE pomocou HW DEVICE CUSTOM OPERATIONS.

	// !!! Vypisu sa PHYSICAL ADDRESS do LOGU.
	for(ULONG Index=0;Index<NumberOfElementsToProceed;Index++)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! [%I64X], SIZE [%d] !\n",DeviceExtension->DMAScatterGatherList->Elements[DeviceExtension->DMAActualIndexOfSGLElement].Address.QuadPart,DeviceExtension->DMAScatterGatherList->Elements[DeviceExtension->DMAActualIndexOfSGLElement].Length);
	}

	// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
	DeviceExtension->ReadyForDMAInterrupt=true;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Tento CODE sluziaci iba na EMULALCIU DMA NIE JE CELKOM BEZPECNY. Ak by totizto tento CODE trval prilis dlho a INTERRUPT, ktorym sa posuva spracovanie medzi STAGES v DEFFERED PROCEDURE CALL by sa spustil v jeho priebehu, mohlo by dojst k BUG CHECK.
void ProcessWriteIRP(PDEVICE_EXTENSION DeviceExtension, PIRP InterruptRequestPacket)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	// !!! V DIRECT MODE FIELD [IRP.MdlAddress] obsahuje POINTER na STRUCTURE [MDL].
	PMDL														CurrentMDL=InterruptRequestPacket->MdlAddress;

	// !!!!! Vyzera to, ze POINTER vrateny ako RETURN VALUE NESMIE byt NIJAKO UVOLNENY. Uvolnovanie robi IO MANAGER, ktory IRP a s nim asociovany MDL vytvoril.
	DeviceExtension->UserModeBufferForCurrentDMATransfer=PCHAR(MmGetSystemAddressForMdlSafe(CurrentMDL,NormalPagePriority));

	if (DeviceExtension->UserModeBufferForCurrentDMATransfer!=nullptr)
	{
		// Ulozi sa pocet BYTES, ktore sa pocas TRANSFER maju preniest.
		DeviceExtension->DMANumberOfBytesRemainingToTransfer=MmGetMdlByteCount(CurrentMDL);

		PVOID													VirtualAddress=MmGetMdlVirtualAddress(CurrentMDL);

		if (NT_SUCCESS(Status=(*DeviceExtension->DMAAddapter->DmaOperations->GetScatterGatherList)(DeviceExtension->DMAAddapter,DeviceExtension->DeviceObject,CurrentMDL,VirtualAddress,DeviceExtension->DMANumberOfBytesRemainingToTransfer,(PDRIVER_LIST_CONTROL) WriteIRPDMAExecutionRoutine,DeviceExtension,TRUE))==true)
		{
			return;
		}
		// !!!!! Ak je pocet BYTES, ktore maju byt prenesene prilis VELKY, tak GetScatterGatherList() hodi ERROR [STATUS_INSUFFICIENT_RESOURCES].
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA::GetScatterGatherList() FAILED [%X] !\n",Status);
		}
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): MmGetSystemAddressForMdlSafe() FAILED !\n");
	}

	// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
	DeviceExtension->ReadyForDMAInterrupt=false;

	// !!!!! Spusti sa vykonavanie dalsieho IRP ak je QUEUE.
	StartNextPacket(&DeviceExtension->DevQueue,DeviceExtension->DeviceObject);

	InterruptRequestPacket->IoStatus.Status=Status;
	InterruptRequestPacket->IoStatus.Information=0;

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

	if ((Value % 20)==0)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): MyInterruptServiceRoutine() CALLED, VALUE [%d] !\n",Value);

		IoRequestDpc(DeviceExtensionData->DeviceObject,NULL,DeviceExtensionData);
	}

	// !!! Ak INTERRUPT NIE JE SPRACOVANY, tak sa MUSI vratit FALSE, aby INTERRUPT (ktory moze byt SHARED) mohol byt posunuty dalsim DRIVERS.
	return(FALSE);
}
//-------------------------------------------------------------------------------------------------------
_Function_class_(IO_DPC_ROUTINE)
VOID DPCForISR(PKDPC, PDEVICE_OBJECT DeviceObject, PIRP, PVOID Context)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DPCForISR() CALLED !\n");

	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) Context;
	// !!! Pomocou FUNCTION GetCurrentIRP() sa ziska CURRENT IRP, ktore je prave spracovavane.
	PIRP														InterruptRequestPacket=GetCurrentIRP(&DeviceExtension->DevQueue);

	if (InterruptRequestPacket!=nullptr && DeviceExtension->ReadyForDMAInterrupt==true)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP in PROGRESS !\n");

		// Z CURRENT IRP sa ziska MDL.
		PMDL													CurrentMDL=InterruptRequestPacket->MdlAddress;

		// !!! Z CURRENT IRP sa ziska [IO_STACK_LOCATION].
		PIO_STACK_LOCATION										Stack=IoGetCurrentIrpStackLocation(InterruptRequestPacket);
		bool													IsRead=(Stack->MajorFunction==IRP_MJ_READ);

		NTSTATUS												Status=STATUS_SUCCESS;

		// !!!!! Tu je mozne vykonat detekciu ci DMA prenos nezlyhal. Zvycajne sa to robi citanim STATUS PORT na HW DEIVCE. Je to HW DEVICE SPECIFIC OPERATION.

		// !!!!! Vykona sa LOCK na USER MODE BUFFER, ktory vrati jeho POINTER z ktoreho je mozne citat pri WRITE OPERATION a zapisovat pri READ OPERATION.
		// !!!!! Vyzera to, ze POINTER vrateny ako RETURN VALUE NESMIE byt NIJAKO UVOLNENY. Uvolnovanie robi IO MANAGER, ktory IRP a s nim asociovany MDL vytvoril.
		PSTR													UserModeBuffer=(PSTR) MmGetSystemAddressForMdlSafe(CurrentMDL,NormalPagePriority);

		// !!!!! Simulacia ERROR. Ak sa nepodaril vykonat LOCK, povazujem to za ERROR a IO OPERATION sa okamzite UKONCI.
		if (UserModeBuffer==nullptr)
		{
			Status=STATUS_NO_MEMORY;

			// !!! DMA TRANSFER sa skoncil hodenim ERROR.
			// !!! Toto je len SIMULACIA ERROR. Ta vznikne, ak WINDOWS nedokazal uspesne zavolat FUNCTION MmGetSystemAddressForMdlSafe().
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): MmGetSystemAddressForMdlSafe() FAILED !\n");
		}

		// !!! Zisti sa ci DMA prenos nezlyhal.
		if (NT_SUCCESS(Status)==true)
		{
			// !!! DMA TRANSFER pokracuje vykonanim dalsej STAGE.
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA TRANSFER STARTING NEXT STAGE !\n");

			DeviceExtension->DMAActualIndexOfSGLElement+=DeviceExtension->DMANumberOfProcessedSGLElementsForCurrentStage;

			// !!! Pocet ELEMENTS, ktore je este treba preniest.
			ULONG												NumberOfElementsToProceed=DeviceExtension->DMAScatterGatherList->NumberOfElements-DeviceExtension->DMAActualIndexOfSGLElement;

			if (NumberOfElementsToProceed>0)
			{
				if (NumberOfElementsToProceed>MAX_ELEMENTS_TO_PROCEED_BY_HW)
				{
					NumberOfElementsToProceed=MAX_ELEMENTS_TO_PROCEED_BY_HW;
				}

				DeviceExtension->DMANumberOfProcessedSGLElementsForCurrentStage=NumberOfElementsToProceed;

				// !!!!! Teraz by sa mal spustit prenos dat ho HW DEVICE pomocou HW DEVICE CUSTOM OPERATIONS.

				// !!! Vypisu sa PHYSICAL ADDRESS do LOGU.
				for(ULONG Index=0;Index<NumberOfElementsToProceed;Index++)
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): !!!!! [%I64X], SIZE [%d] !\n",DeviceExtension->DMAScatterGatherList->Elements[DeviceExtension->DMAActualIndexOfSGLElement].Address.QuadPart,DeviceExtension->DMAScatterGatherList->Elements[DeviceExtension->DMAActualIndexOfSGLElement].Length);
				}
			}
			else
			{
				// !!! DMA TRANSFER sa skoncil.
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA TRANSFER COMPLETED !\n");

				// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
				DeviceExtension->ReadyForDMAInterrupt=false;

				// !!! FUNCTION vo FIELD [DMA_OPERATIONS.PutScatterGatherList] uvolnuje alokovany SCATTER GATHER LIST.
				// !!!!! FUNCTION vo FIELD [DMA_OPERATIONS.PutScatterGatherList] MUSI byt volana predtym ako sa zacne pracovat s BUFFER, pretoze tato FUNCTION vykonava BUFFER FLUSH.
				(*DeviceExtension->DMAAddapter->DmaOperations->PutScatterGatherList)(DeviceExtension->DMAAddapter,DeviceExtension->DMAScatterGatherList,!IsRead);

				DeviceExtension->DMAActualIndexOfSGLElement=0;
				DeviceExtension->DMANumberOfProcessedSGLElementsForCurrentStage=0;

				ULONG											NumberOfTransferedBytes=0;

				for(ULONG Index=0;Index<DeviceExtension->DMAScatterGatherList->NumberOfElements;Index++)
				{
					NumberOfTransferedBytes+=DeviceExtension->DMAScatterGatherList->Elements[Index].Length;
				}

				if (IsRead==true)
				{
					if (NumberOfTransferedBytes>=DeviceExtension->ReadBufferSize1 && NumberOfTransferedBytes<DeviceExtension->ReadBufferSize2)
					{
						RtlCopyMemory(PCHAR(UserModeBuffer),DeviceExtension->ReadBuffer1,DeviceExtension->ReadBufferSize1);
					}
					else if (NumberOfTransferedBytes>=DeviceExtension->ReadBufferSize2 && NumberOfTransferedBytes<DeviceExtension->ReadBufferSize3)
					{
						RtlCopyMemory(PCHAR(UserModeBuffer),DeviceExtension->ReadBuffer2,DeviceExtension->ReadBufferSize2);
					}
					else
					{
						RtlCopyMemory(PCHAR(UserModeBuffer),DeviceExtension->ReadBuffer3,DeviceExtension->ReadBufferSize3);
					}

					PrintReadBuffer(PCHAR(UserModeBuffer),NumberOfTransferedBytes);
				}
				else
				{
					PrintWriteBuffer(PCHAR(UserModeBuffer),NumberOfTransferedBytes);
				}

				// !!! CUSTOM FUNCTION CompleteRequest() ukonci spracovanie CURRENT IRP.
				CompleteRequest(InterruptRequestPacket,Status,NumberOfTransferedBytes);

				// !!! Spusti sa spracovanie noveho IRP.
				StartNextPacket(&DeviceExtension->DevQueue,DeviceObject);

				// !!! Kedze sa IRP SPRACOVAL, tak je NUTNE UVOLNIT REMOVE LOCK.
				IoReleaseRemoveLock(&DeviceExtension->RemoveLock,InterruptRequestPacket);
			}
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA TRANSFER FAILED [%X] !\n",Status);

			// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
			DeviceExtension->ReadyForDMAInterrupt=false;

			// !!! FUNCTION vo FIELD [DMA_OPERATIONS.PutScatterGatherList] uvolnuje alokovany SCATTER GATHER LIST.
			// !!!!! FUNCTION vo FIELD [DMA_OPERATIONS.PutScatterGatherList] MUSI byt volana predtym ako sa zacne pracovat s BUFFER, pretoze tato FUNCTION vykonava BUFFER FLUSH.
			(*DeviceExtension->DMAAddapter->DmaOperations->PutScatterGatherList)(DeviceExtension->DMAAddapter,DeviceExtension->DMAScatterGatherList,!IsRead);

			DeviceExtension->DMAActualIndexOfSGLElement=0;
			DeviceExtension->DMANumberOfProcessedSGLElementsForCurrentStage=0;

			// !!! Pri ERROR sa ukonci CURRENT IRP volanim CUSTOM FUNCTION CompleteRequest(), ktora vola FUNCTION IoCompleteRequest().
			CompleteRequest(InterruptRequestPacket,Status,0);

			// !!! Spusti sa spracovanie noveho IRP.
			StartNextPacket(&DeviceExtension->DevQueue,DeviceObject);

			// !!! Kedze sa IRP SPRACOVAL, tak je NUTNE UVOLNIT REMOVE LOCK.
			IoReleaseRemoveLock(&DeviceExtension->RemoveLock,InterruptRequestPacket);
		}
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS GetReadStringSize(const ULONG NUMBER_OF_ITERATIONS, size_t& NumberOfBytes)
{
	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	NumberOfBytes=(sizeof("HUGE TEXT READ [")-sizeof(CHAR));

	for(ULONG Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
	{
		CHAR													LocalBuffer[20];
		size_t													LocalBufferSize;

		if (NT_SUCCESS(Status=PrintfInteger(LocalBuffer,sizeof(LocalBuffer),Index+1))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RtlStringCbPrintfA() FAILED [%X] !\n",Status);

			return(Status);
		}

		if (NT_SUCCESS(Status=LengthString(LocalBuffer,sizeof(LocalBuffer),&LocalBufferSize))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RtlStringCbLengthA() FAILED [%X] !\n",Status);

			return(Status);
		}

		if (Index>0)
		{
			NumberOfBytes+=(sizeof(",")-sizeof(CHAR));
		}

		NumberOfBytes+=LocalBufferSize;
	}

	// !!! Vlozi sa aj znak '\0'.
	NumberOfBytes+=sizeof("] !");

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
NTSTATUS CopyReadString(const ULONG NUMBER_OF_ITERATIONS, PSTR Buffer, size_t BufferSize)
{
	NTSTATUS													Status;
	CHAR														Prefix[]="HUGE TEXT READ [";
	size_t														NumberOfBytesWritten=0;

	if (NT_SUCCESS(Status=CopyString(&Buffer[NumberOfBytesWritten],BufferSize-NumberOfBytesWritten,Prefix))==false)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyString() FAILED [%X] !\n",Status);

		return(Status);
	}

	NumberOfBytesWritten+=(sizeof(Prefix)-sizeof(CHAR));

	for(ULONG Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
	{
		CHAR													LocalBuffer[20];
		size_t													LocalBufferSize;

		if (NT_SUCCESS(Status=PrintfInteger(LocalBuffer,sizeof(LocalBuffer),Index+1))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RtlStringCbPrintfA() FAILED [%X] !\n",Status);

			return(Status);
		}

		if (NT_SUCCESS(Status=LengthString(LocalBuffer,sizeof(LocalBuffer),&LocalBufferSize))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RtlStringCbLengthA() FAILED [%X] !\n",Status);

			return(Status);
		}

		if (Index>0)
		{
			CHAR												Separator[]=",";

			if (NT_SUCCESS(Status=CopyString(&Buffer[NumberOfBytesWritten],BufferSize-NumberOfBytesWritten,Separator))==false)
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyString() FAILED [%X] !\n",Status);

				return(Status);
			}

			NumberOfBytesWritten+=(sizeof(Separator)-sizeof(CHAR));
		}

		if (NT_SUCCESS(Status=CopyString(&Buffer[NumberOfBytesWritten],BufferSize-NumberOfBytesWritten,LocalBuffer))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyString() FAILED [%X] !\n",Status);

			return(Status);
		}

		NumberOfBytesWritten+=LocalBufferSize;
	}

	CHAR														Postfix[]="] !";

	if (NT_SUCCESS(Status=CopyString(&Buffer[NumberOfBytesWritten],BufferSize-NumberOfBytesWritten,Postfix))==false)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyString() FAILED [%X] !\n",Status);

		return(Status);
	}

	// !!! Vlozi sa aj znak '\0'.
	NumberOfBytesWritten+=sizeof(Postfix);

	return(Status);
}
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
		DeviceExtensionData->ReadBufferSize1=0;
		DeviceExtensionData->ReadBuffer1=nullptr;
		DeviceExtensionData->ReadBufferSize2=0;
		DeviceExtensionData->ReadBuffer2=nullptr;
		DeviceExtensionData->ReadBufferSize3=0;
		DeviceExtensionData->ReadBuffer3=nullptr;

		const ULONG												NUMBER_OF_ITERATIONS_1=400;
		const ULONG												NUMBER_OF_ITERATIONS_2=1200;
		const ULONG												NUMBER_OF_ITERATIONS_3=4000;

		if (DeviceExtensionData->LowerDeviceObject==NULL)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAttachDeviceToDeviceStack() FAILED !\n");
			Status=STATUS_DEVICE_REMOVED;
			break;
		}

		if (NT_SUCCESS(Status=GetReadStringSize(NUMBER_OF_ITERATIONS_1,DeviceExtensionData->ReadBufferSize1))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): GetReadStringSize() FAILED !\n");
			break;
		}

		if (NT_SUCCESS(Status=GetReadStringSize(NUMBER_OF_ITERATIONS_2,DeviceExtensionData->ReadBufferSize2))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): GetReadStringSize() FAILED !\n");
			break;
		}

		if (NT_SUCCESS(Status=GetReadStringSize(NUMBER_OF_ITERATIONS_3,DeviceExtensionData->ReadBufferSize3))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): GetReadStringSize() FAILED !\n");
			break;
		}

		if ((DeviceExtensionData->ReadBuffer1=PCHAR(ExAllocatePoolWithTag(NonPagedPool,DeviceExtensionData->ReadBufferSize1,'FUBR')))==nullptr)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExAllocatePoolWithTag() FAILED !\n");
			Status=STATUS_NO_MEMORY;
			break;
		}

		if ((DeviceExtensionData->ReadBuffer2=PCHAR(ExAllocatePoolWithTag(NonPagedPool,DeviceExtensionData->ReadBufferSize2,'FUBR')))==nullptr)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExAllocatePoolWithTag() FAILED !\n");
			Status=STATUS_NO_MEMORY;
			break;
		}

		if ((DeviceExtensionData->ReadBuffer3=PCHAR(ExAllocatePoolWithTag(NonPagedPool,DeviceExtensionData->ReadBufferSize3,'FUBR')))==nullptr)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExAllocatePoolWithTag() FAILED !\n");
			Status=STATUS_NO_MEMORY;
			break;
		}

		if (NT_SUCCESS(Status=CopyReadString(NUMBER_OF_ITERATIONS_1,DeviceExtensionData->ReadBuffer1,DeviceExtensionData->ReadBufferSize1))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyReadString() FAILED !\n");
			break;
		}

		if (NT_SUCCESS(Status=CopyReadString(NUMBER_OF_ITERATIONS_2,DeviceExtensionData->ReadBuffer2,DeviceExtensionData->ReadBufferSize2))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyReadString() FAILED !\n");
			break;
		}

		if (NT_SUCCESS(Status=CopyReadString(NUMBER_OF_ITERATIONS_3,DeviceExtensionData->ReadBuffer3,DeviceExtensionData->ReadBufferSize3))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyReadString() FAILED !\n");
			break;
		}

		NewDeviceObject->Flags|=DO_POWER_PAGABLE;

		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_GET_DMA_SCATTER_GATHER_LIST_DRIVER,NULL,&DeviceExtensionData->InterfaceName);
		
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

		if (DeviceExtensionData->ReadBuffer1!=nullptr)
		{
			ExFreePoolWithTag(DeviceExtensionData->ReadBuffer1,'FUBR');
			DeviceExtensionData->ReadBuffer1=nullptr;
		}

		if (DeviceExtensionData->ReadBuffer2!=nullptr)
		{
			ExFreePoolWithTag(DeviceExtensionData->ReadBuffer2,'FUBR');
			DeviceExtensionData->ReadBuffer2=nullptr;
		}

		if (DeviceExtensionData->ReadBuffer3!=nullptr)
		{
			ExFreePoolWithTag(DeviceExtensionData->ReadBuffer3,'FUBR');
			DeviceExtensionData->ReadBuffer3=nullptr;
		}

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

	// !!! REALNY DEVICE by tu mal prinutit DEVICE, aby zastavil generovanie INTERRUPTS. Generovanie INTERRUPTS by sa malo obnovit az po dokonceni FUNCTION IoConnectInterrupt().

	LOG->WriteToLog("TEST 1 !\n");

	NTSTATUS													Status;

	for(;;)
	{
		if (NT_SUCCESS(Status=IoConnectInterrupt(&DeviceExtensionData->InterruptObject,(PKSERVICE_ROUTINE) MyInterruptServiceRoutine,(PVOID) DeviceExtensionData,NULL,Vector,IRQL,IRQL,Mode,IRQShare,Affinity,FALSE))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoConnectInterrupt() FAILED [%X] !\n",Status);

			Status=STATUS_NO_MEMORY;
			break;
		}

		DEVICE_DESCRIPTION										DeviceDesciption;

		RtlZeroMemory(&DeviceDesciption,sizeof(DeviceDesciption));

		DeviceDesciption.Version=DEVICE_DESCRIPTION_VERSION;
		DeviceDesciption.Master=TRUE;
		DeviceDesciption.InterfaceType=InterfaceTypeUndefined;
		DeviceDesciption.MaximumLength=PAGE_SIZE;
		DeviceDesciption.Dma32BitAddresses=TRUE;

		// !!! Pri DMA typu SCATTER-GATHER je NUTNE nastavit FLAG [DEVICE_DESCRIPTION.ScatterGather] na TRUE.
		DeviceDesciption.ScatterGather=TRUE;

		LOG->WriteToLog("TEST 2 !\n");

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEFORE IoGetDmaAdapter() CALLING !\n");

		/*
		// !!! Alokuje sa DMA ADAPTER OBJECT.
		if ((DeviceExtensionData->DMAAddapter=IoGetDmaAdapter(DeviceExtensionData->PDO,&DeviceDesciption,&DeviceExtensionData->DMANumberOfMapRegisters))==NULL)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoGetDmaAdapter() FAILED !\n");

			Status=STATUS_NO_MEMORY;
			break;
		}
		*/

		// !!! Alokuje sa DMA ADAPTER OBJECT.
		// !!!!! Je to OBSOLETE FUNCTION. Na rozdiel od FUNCTION IoGetDmaAdapter(), ktora vracala NULL, tato vratila POINTER na DMA ADAPTER OBJECT.
		if ((DeviceExtensionData->DMAAddapter=HalGetAdapter(&DeviceDesciption,&DeviceExtensionData->DMANumberOfMapRegisters))==NULL)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): HalGetAdapter() FAILED !\n");

			Status=STATUS_NO_MEMORY;
			break;
		}

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): AFTER IoGetDmaAdapter() CALLED !\n");

		LOG->WriteToLog("TEST 3 !\n");

		Status=STATUS_SUCCESS;
		break;
	}

	if (NT_SUCCESS(Status)==false)
	{
		if (DeviceExtensionData->DMAAddapter!=NULL)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEFORE PutDmaAdapter() CALLING !\n");

			// !!! Zavola CUSTOM DMA FUNCTION vo FIELD [DMA_OPERATIONS.PutDmaAdapter] na uvolnenie DMA ADAPTER OBJECT.
			(*DeviceExtensionData->DMAAddapter->DmaOperations->PutDmaAdapter)(DeviceExtensionData->DMAAddapter);
			DeviceExtensionData->DMAAddapter=NULL;

			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): AFTER PutDmaAdapter() CALLED !\n");
		}

		if (DeviceExtensionData->InterruptObject!=NULL)
		{
			// !!! REALNY DEVICE by tu mal prinutit DEVICE, aby zastavil generovanie INTERRUPTS.
			IoDisconnectInterrupt(DeviceExtensionData->InterruptObject);
			DeviceExtensionData->InterruptObject=NULL;
		}

		return(Status);
	}
	else
	{
		return(Status);
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION je volana potom co IRP bol odoslany a spracovany DRIVERS NIZSIE v DRIVER STACK.
VOID __stdcall StopDevice(IN PDEVICE_OBJECT DeviceObject, BOOLEAN)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DeviceObject [%p] !\n",DeviceObject);

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;

	if (DeviceExtensionData->DMAAddapter!=NULL)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEFORE PutDmaAdapter() CALLING !\n");

		// !!! Zavola CUSTOM DMA FUNCTION vo FIELD [DMA_OPERATIONS.PutDmaAdapter] na uvolnenie DMA ADAPTER OBJECT.
		(*DeviceExtensionData->DMAAddapter->DmaOperations->PutDmaAdapter)(DeviceExtensionData->DMAAddapter);
		DeviceExtensionData->DMAAddapter=NULL;

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): AFTER PutDmaAdapter() CALLED !\n");
	}

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

	if (DeviceExtensionData->ReadBuffer1!=nullptr)
	{
		ExFreePoolWithTag(DeviceExtensionData->ReadBuffer1,'FUBR');
		DeviceExtensionData->ReadBuffer1=nullptr;
	}

	if (DeviceExtensionData->ReadBuffer2!=nullptr)
	{
		ExFreePoolWithTag(DeviceExtensionData->ReadBuffer2,'FUBR');
		DeviceExtensionData->ReadBuffer2=nullptr;
	}

	if (DeviceExtensionData->ReadBuffer3!=nullptr)
	{
		ExFreePoolWithTag(DeviceExtensionData->ReadBuffer3,'FUBR');
		DeviceExtensionData->ReadBuffer3=nullptr;
	}

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
//-------------------------------------------------------------------------------------------------------
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
			ProcessReadIRP(DeviceExtension,InterruptRequestPacket);
			return;
		}
		else if (Stack->MajorFunction==IRP_MJ_WRITE)
		{
			ProcessWriteIRP(DeviceExtension,InterruptRequestPacket);
			return;
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): UNSUPPORTED MAJOR FUNCTION [%d] !\n",Stack->MajorFunction);
		}
	}

	// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
	DeviceExtension->ReadyForDMAInterrupt=false;

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

	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	PMDL														CurrentMDL=InterruptRequestPacket->MdlAddress;
	ULONG														NumberOfBytesToTransfer=MmGetMdlByteCount(CurrentMDL);

	if (NumberOfBytesToTransfer<DeviceExtension->ReadBufferSize1)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BUFFER is too SMALL !\n"));

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