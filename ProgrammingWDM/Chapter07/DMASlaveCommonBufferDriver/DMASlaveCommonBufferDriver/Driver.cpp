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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
const int														COMMON_BUFFER_SIZE=PAGE_SIZE*3;
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
IO_ALLOCATION_ACTION ReadIRPAdapterControl(PDEVICE_OBJECT, PIRP, PVOID MapRegisterBase, PVOID Context)
{
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) Context;

	// !!! MUSI sa pouzit MDL referujuci na COMMON BUFFER.
	PMDL														CurrentMDL=DeviceExtension->CommonBufferMDL;

	DeviceExtension->DMAMapRegisterAddressBaseForCurrentStage=MapRegisterBase;

	// !!! Pre dany MDL sa data z CPU CACHES, ak tam nejake su ulozene sa prenesu do MAIN MEMORY.
	// 2. PARAMETER urcuje, ze sa jedna o READ OPERATION.
	KeFlushIoBuffers(CurrentMDL,TRUE,TRUE);

	// !!! RETURN VALUE FUNCTION vo FIELD [DMA_OPERATIONS.MapTransfer] urcuje PHYSICAL ADDRESS, odkial sa maju data cez DMA prenos citat, aby boli zapisane do HW DEVICE.
	PHYSICAL_ADDRESS											Address=(*DeviceExtension->DMAAddapter->DmaOperations->MapTransfer)(DeviceExtension->DMAAddapter,CurrentMDL,MapRegisterBase,DeviceExtension->DMAVirtualAddressForCurrentStage,&DeviceExtension->DMANumberOfBytesToTransferForCurrentStage,FALSE);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PHYSICAL ADDRESS [%I64X] !\n",Address.QuadPart);

	// !!!!! ADDRESS ulozena v [PHYSICAL_ADDRESS] by sa teraz mala zaslat pomocou HAL FUNCTIONS do HW DEVICE, ktore by na tuto ADDRESS malo zapisovat/citat data.

	// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
	DeviceExtension->ReadyForDMAInterrupt=true;

	// !!!!! Kedze v SLAVE DMA TRANSFER je SYSTEM DMA CONTROLLER a jeho DMA CHANNELS SHARED medzi viacerymi HW DEVICES je NUTNE aby HW DEVICE, ktory ho prave pouziva ho rezervoval pre seba. To sa zabezpeci vratenim RETURN VALUE [KeepObject], ktora prinuti DMA CHANNEL, aby ostal priradeny CURRENT DRIVER, tak ako MAP REGISTERS.
	return(KeepObject);
}
//-------------------------------------------------------------------------------------------------------
void ProcessReadIRP(PDEVICE_EXTENSION DeviceExtension, PIRP InterruptRequestPacket)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	// !!! V DIRECT MODE FIELD [IRP.MdlAddress] obsahuje POINTER na STRUCTURE [MDL].
	PMDL														CurrentMDL=InterruptRequestPacket->MdlAddress;

	// !!!!! Vyzera to, ze POINTER vrateny ako RETURN VALUE NESMIE byt NIJAKO UVOLNENY. Uvolnovanie robi IO MANAGER, ktory IRP a s nim asociovany MDL vytvoril.
	DeviceExtension->UserModeBufferForCurrentDMATransfer=PCHAR(MmGetSystemAddressForMdlSafe(CurrentMDL,NormalPagePriority));

	if (DeviceExtension->UserModeBufferForCurrentDMATransfer!=nullptr)
	{
		ULONG													DataLength=MmGetMdlByteCount(CurrentMDL);

		// Doteraz sa nepreniesol ziaden BYTE.
		DeviceExtension->DMANumberOfAlreadyTransferedBytes=0;

		// Ulozi sa pocet BYTES, ktore sa pocas TRANSFER maju preniest.
		DeviceExtension->DMANumberOfBytesRemainingToTransfer=DataLength;

		// Na zaciatku sa predpoklada, ze vsetky BYTES aktualneho TRANSFER je mozne preniest v 1 STAGE.
		DeviceExtension->DMANumberOfBytesToTransferForCurrentStage=DeviceExtension->DMANumberOfBytesRemainingToTransfer;

		// Pre CURRENT STAGE sa nastavi VIRTUAL ADDRESS kam sa budu data cez DMA prenos ukladat.
		// !!!!! MUSI sa pouzit MDL z COMMON BUFFER.
		DeviceExtension->DMAVirtualAddressForCurrentStage=MmGetMdlVirtualAddress(DeviceExtension->CommonBufferMDL);

		// Pomocou MACRO ADDRESS_AND_SIZE_TO_SPAN_PAGES() sa urci pocet MEMORY PAGES, ktore su potrebne na prenos zadaneho poctu BYTES pre dany BUFFER. Pocet MEMORY PAGES zavisi od pozicie BUFFER v MEMORY ako aj poctu BYTES, ktore maju byt prenesene.
		ULONG													NumberOfMemoryPages=ADDRESS_AND_SIZE_TO_SPAN_PAGES(DeviceExtension->DMAVirtualAddressForCurrentStage,DeviceExtension->DMANumberOfBytesRemainingToTransfer);

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BUFFER ADDRESS [%p], NUMBER of BYTES to TRANSFER [%d], NUMBER of PAGES to TRANSFER [%d], NUMBER of MAP REGISTERS [%d] !\n",DeviceExtension->DMAVirtualAddressForCurrentStage,DeviceExtension->DMANumberOfBytesRemainingToTransfer,NumberOfMemoryPages,DeviceExtension->DMANumberOfMapRegisters);

		// !!!!! 1 MAP REGISTER obsahuje ADDRESS 1 MEMORY PAGE.
		// !!! Ak SYSTEM pridelil DRIVER MENSI pocet MAP REGISTERS ako pocet PAGES, ktore su potrebne na prenos celeho BUFFER, je prenos nutne rozdelit do viacerych STAGES.
		if (NumberOfMemoryPages>DeviceExtension->DMANumberOfMapRegisters)
		{
			NumberOfMemoryPages=DeviceExtension->DMANumberOfMapRegisters;

			// !!! MACRO MmGetMdlByteOffset() vracia BYTE OFFSET BUFFER voci zaciatku MEMORY PAGE.
			// !!! CODE vypocita pocet BYTES, ktore budu prenesene pocas CURRENT STAGE.
			DeviceExtension->DMANumberOfBytesToTransferForCurrentStage=(NumberOfMemoryPages*PAGE_SIZE)-MmGetMdlByteOffset(DeviceExtension->CommonBufferMDL);
		}

		// !!! Ulozi sa pocet MAP REGISTERS, ktore budu pouzite pocas aktualnej STAGE. Tato hodnota je potrebna pri uvolnovani MAP REGISTERS.
		DeviceExtension->DMANumberOfAllocatedMapRegisters=NumberOfMemoryPages;
	
		if (NT_SUCCESS(Status=(*DeviceExtension->DMAAddapter->DmaOperations->AllocateAdapterChannel)(DeviceExtension->DMAAddapter,DeviceExtension->DeviceObject,NumberOfMemoryPages,(PDRIVER_CONTROL) ReadIRPAdapterControl,DeviceExtension))==true)
		{
			return;
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA::AllocateAdapterChannel() FAILED [%X] !\n",Status);
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
IO_ALLOCATION_ACTION WriteIRPAdapterControl(PDEVICE_OBJECT, PIRP, PVOID MapRegisterBase, PVOID Context)
{
	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) Context;

	// !!! MUSI sa pouzit MDL referujuci na COMMON BUFFER.
	PMDL														CurrentMDL=DeviceExtension->CommonBufferMDL;

	DeviceExtension->DMAMapRegisterAddressBaseForCurrentStage=MapRegisterBase;

	// !!! Pre dany MDL sa data z CPU CACHES, ak tam nejake su ulozene sa prenesu do MAIN MEMORY.
	// 2. PARAMETER urcuje, ze sa jedna o WRITE OPERATION.
	KeFlushIoBuffers(CurrentMDL,FALSE,TRUE);

	// !!! RETURN VALUE FUNCTION vo FIELD [DMA_OPERATIONS.MapTransfer] urcuje PHYSICAL ADDRESS, odkial sa maju data cez DMA prenos citat, aby boli zapisane do HW DEVICE.
	PHYSICAL_ADDRESS											Address=(*DeviceExtension->DMAAddapter->DmaOperations->MapTransfer)(DeviceExtension->DMAAddapter,CurrentMDL,MapRegisterBase,DeviceExtension->DMAVirtualAddressForCurrentStage,&DeviceExtension->DMANumberOfBytesToTransferForCurrentStage,TRUE);

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PHYSICAL ADDRESS [%I64X] !\n",Address.QuadPart);

	// !!!!! ADDRESS ulozena v [PHYSICAL_ADDRESS] by sa teraz mala zaslat pomocou HAL FUNCTIONS do HW DEVICE, ktore by na tuto ADDRESS malo zapisovat/citat data.

	// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
	DeviceExtension->ReadyForDMAInterrupt=true;

	// !!!!! Kedze v SLAVE DMA TRANSFER je SYSTEM DMA CONTROLLER a jeho DMA CHANNELS SHARED medzi viacerymi HW DEVICES je NUTNE aby HW DEVICE, ktory ho prave pouziva ho rezervoval pre seba. To sa zabezpeci vratenim RETURN VALUE [KeepObject], ktora prinuti DMA CHANNEL, aby ostal priradeny CURRENT DRIVER, tak ako MAP REGISTERS.
	return(KeepObject);
}
//-------------------------------------------------------------------------------------------------------
void ProcessWriteIRP(PDEVICE_EXTENSION DeviceExtension, PIRP InterruptRequestPacket)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	// !!! V DIRECT MODE FIELD [IRP.MdlAddress] obsahuje POINTER na STRUCTURE [MDL].
	PMDL														CurrentMDL=InterruptRequestPacket->MdlAddress;

	// !!!!! Vyzera to, ze POINTER vrateny ako RETURN VALUE NESMIE byt NIJAKO UVOLNENY. Uvolnovanie robi IO MANAGER, ktory IRP a s nim asociovany MDL vytvoril.
	DeviceExtension->UserModeBufferForCurrentDMATransfer=PCHAR(MmGetSystemAddressForMdlSafe(CurrentMDL,NormalPagePriority));

	if (DeviceExtension->UserModeBufferForCurrentDMATransfer!=nullptr)
	{
		ULONG													DataLength=MmGetMdlByteCount(CurrentMDL);

		// Doteraz sa nepreniesol ziaden BYTE.
		DeviceExtension->DMANumberOfAlreadyTransferedBytes=0;

		// Ulozi sa pocet BYTES, ktore sa pocas TRANSFER maju preniest.
		DeviceExtension->DMANumberOfBytesRemainingToTransfer=DataLength;

		// Na zaciatku sa predpoklada, ze vsetky BYTES aktualneho TRANSFER je mozne preniest v 1 STAGE.
		DeviceExtension->DMANumberOfBytesToTransferForCurrentStage=DeviceExtension->DMANumberOfBytesRemainingToTransfer;

		// Pre CURRENT STAGE sa nastavi VIRTUAL ADDRESS kam sa budu data cez DMA prenos ukladat.
		// !!!!! MUSI sa pouzit MDL z COMMON BUFFER.
		DeviceExtension->DMAVirtualAddressForCurrentStage=MmGetMdlVirtualAddress(DeviceExtension->CommonBufferMDL);

		// Pomocou MACRO ADDRESS_AND_SIZE_TO_SPAN_PAGES() sa urci pocet MEMORY PAGES, ktore su potrebne na prenos zadaneho poctu BYTES pre dany BUFFER. Pocet MEMORY PAGES zavisi od pozicie BUFFER v MEMORY ako aj poctu BYTES, ktore maju byt prenesene.
		ULONG													NumberOfMemoryPages=ADDRESS_AND_SIZE_TO_SPAN_PAGES(DeviceExtension->DMAVirtualAddressForCurrentStage,DeviceExtension->DMANumberOfBytesRemainingToTransfer);

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BUFFER ADDRESS [%p], NUMBER of BYTES to TRANSFER [%d], NUMBER of PAGES to TRANSFER [%d], NUMBER of MAP REGISTERS [%d] !\n",DeviceExtension->DMAVirtualAddressForCurrentStage,DeviceExtension->DMANumberOfBytesRemainingToTransfer,NumberOfMemoryPages,DeviceExtension->DMANumberOfMapRegisters);

		// !!!!! 1 MAP REGISTER obsahuje ADDRESS 1 MEMORY PAGE.
		// !!! Ak SYSTEM pridelil DRIVER MENSI pocet MAP REGISTERS ako pocet PAGES, ktore su potrebne na prenos celeho BUFFER, je prenos nutne rozdelit do viacerych STAGES.
		if (NumberOfMemoryPages>DeviceExtension->DMANumberOfMapRegisters)
		{
			NumberOfMemoryPages=DeviceExtension->DMANumberOfMapRegisters;

			// !!! MACRO MmGetMdlByteOffset() vracia BYTE OFFSET BUFFER voci zaciatku MEMORY PAGE.
			// !!! CODE vypocita pocet BYTES, ktore budu prenesene pocas CURRENT PAGE.
			DeviceExtension->DMANumberOfBytesToTransferForCurrentStage=(NumberOfMemoryPages*PAGE_SIZE)-MmGetMdlByteOffset(DeviceExtension->CommonBufferMDL);
		}

		// !!! Ulozi sa pocet MAP REGISTERS, ktore budu pouzite pocas aktualnej STAGE. Tato hodnota je potrebna pri uvolnovani MAP REGISTERS.
		DeviceExtension->DMANumberOfAllocatedMapRegisters=NumberOfMemoryPages;

		// !!!!! Pri WRITE sa data z IRP MDL sa prekopiruju do COMMON BUFFER.
		RtlCopyMemory(DeviceExtension->CommonBufferVirtualMemory,DeviceExtension->UserModeBufferForCurrentDMATransfer,DeviceExtension->DMANumberOfBytesToTransferForCurrentStage);

		if (NT_SUCCESS(Status=(*DeviceExtension->DMAAddapter->DmaOperations->AllocateAdapterChannel)(DeviceExtension->DMAAddapter,DeviceExtension->DeviceObject,NumberOfMemoryPages,(PDRIVER_CONTROL) WriteIRPAdapterControl,DeviceExtension))==true)
		{
			return;
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA::AllocateAdapterChannel() FAILED [%X] !\n",Status);
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

	if ((Value % 30)==0)
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

	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) Context;
	// !!! Pomocou FUNCTION GetCurrentIRP() sa ziska CURRENT IRP, ktore je prave spracovavane.
	PIRP														InterruptRequestPacket=GetCurrentIRP(&DeviceExtensionData->DevQueue);

	if (InterruptRequestPacket!=nullptr && DeviceExtensionData->ReadyForDMAInterrupt==true)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IRP in PROGRESS !\n");

		// !!!!! Zoberie sa MDL s COMMON BUFFER.
		PMDL													CurrentMDL=DeviceExtensionData->CommonBufferMDL;

		// !!! Z CURRENT IRP sa ziska [IO_STACK_LOCATION].
		PIO_STACK_LOCATION										Stack=IoGetCurrentIrpStackLocation(InterruptRequestPacket);
		bool													IsRead=(Stack->MajorFunction==IRP_MJ_READ);

		// !!! FUNCTION vo FIELD [DMA_OPERATIONS.FlushAdapterBuffers] presunie INTERMEDIATE BUFFERS pouzivane DMA do USER MODE BUFFER.
		(*DeviceExtensionData->DMAAddapter->DmaOperations->FlushAdapterBuffers)(DeviceExtensionData->DMAAddapter,CurrentMDL,DeviceExtensionData->DMAMapRegisterAddressBaseForCurrentStage,DeviceExtensionData->DMAVirtualAddressForCurrentStage,DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage,!IsRead);

		NTSTATUS												Status=STATUS_SUCCESS;

		// !!!!! Tu je mozne vykonat detekciu ci DMA prenos nezlyhal. Zvycajne sa to robi citanim STATUS PORT na HW DEIVCE. Je to HW DEVICE SPECIFIC OPERATION.

		ULONG													NumberOfBytesTransmitted=(*DeviceExtensionData->DMAAddapter->DmaOperations->ReadDmaCounter)(DeviceExtensionData->DMAAddapter);

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): NUMBER OF BYTES TRANSMITTED [%d] !\n",NumberOfBytesTransmitted);

		// !!!!! Vykona sa LOCK na USER MODE BUFFER, ktory vrati jeho POINTER z ktoreho je mozne citat pri WRITE OPERATION a zapisovat pri READ OPERATION.
		// !!!!! POINTER vrateny ako RETURN VALUE NESMIE byt NIJAKO UVOLNENY. Uvolnovanie robi IO MANAGER, ktory IRP a s nim asociovany MDL vytvoril.
		// !!!!! Kedze sa za MDL dosadzuje hodnota z IRP a NIE CUSTOM MDL vytvoreny v CUSTOM FUNCTION StartDevice(), vrateny POINTER je POINTER na USER MODE BUFFER.
		PSTR													UserModeBuffer=(PSTR) MmGetSystemAddressForMdlSafe(InterruptRequestPacket->MdlAddress,NormalPagePriority);

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
			// !!! Teraz je mozne pristupit k USER MODE BUFFER a citat, alebo zapisovat DATA.
			// !!!!! Pristup k USER MODE BUFFER je mozny AZ PO VOLANI FUNCTION vo FIELD [DMA_OPERATIONS.FlushAdapterBuffers], pretoze iba vtedy je USER MODE BUFFER platny. Pri pokuse o pristup k casti USER MODE BUFFER, pre ktoru nebola zavolana FUNCTION vo FIELD [DMA_OPERATIONS.FlushAdapterBuffers] sa stavalo, ze sa BUFFER nenaplnal spravne a neulozili sa do vsetky DATA.
			if (IsRead==true)
			{
				// !!! Hodnota 'BytesToTransfer' sa MUSI rovnat hodnote 'NumberOfBytesTransmitted' ak tomu spravne rozumiem.
				ULONG											BytesToTransfer=DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage;

				if (BytesToTransfer!=NumberOfBytesTransmitted)
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ?????????? VALUES are DIFFERENT [%d,%d] !\n",BytesToTransfer,NumberOfBytesTransmitted);
				}

				// !!!!! Tu sa emuluje, ze DMA transfer uspesne preniesol BYTES do COMMON BUFFER tym, ze tieto BYTES manualne nakopirujem do COMMON BUFFER.
				RtlCopyMemory(DeviceExtensionData->CommonBufferVirtualMemory,DeviceExtensionData->ReadBuffer+DeviceExtensionData->DMANumberOfAlreadyTransferedBytes,BytesToTransfer);

				// !!!!! VALUE [DeviceExtensionData->DMANumberOfAlreadyTransferedBytes] can be HIGHER than VALUE [DeviceExtensionData->ReadBufferSize]. So there must be this CHECK, otherwise BUGCHECK can arise.
				if (DeviceExtensionData->DMANumberOfAlreadyTransferedBytes<DeviceExtensionData->ReadBufferSize)
				{
					if ((DeviceExtensionData->DMANumberOfAlreadyTransferedBytes+DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage)>DeviceExtensionData->ReadBufferSize)
					{
						BytesToTransfer=ULONG(max(0,LONG32(DeviceExtensionData->ReadBufferSize)-LONG32(DeviceExtensionData->DMANumberOfAlreadyTransferedBytes)));
					}

					// !!!!! Simuluje sa vykonanie operacie READ, ktora by za normalne bola vykonana cez DMA TRANSFER.
					// Nakopiruju sa DATA do OUTPUT BUFFER, ako simulacia DMA prenosu.
					RtlCopyMemory(PCHAR(UserModeBuffer)+DeviceExtensionData->DMANumberOfAlreadyTransferedBytes,DeviceExtensionData->ReadBuffer+DeviceExtensionData->DMANumberOfAlreadyTransferedBytes,BytesToTransfer);

					PrintReadBuffer(PCHAR(UserModeBuffer)+DeviceExtensionData->DMANumberOfAlreadyTransferedBytes,BytesToTransfer);
				}
				else
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BUFFER is already FILLED !\n");
				}
			}
			else
			{
				// !!!!! Simuluje sa vykonanie operacie WRITE, ktora by za normalne bola vykonana cez DMA TRANSFER.
				// DATA z INPUT BUFFER sa vypisu ako DEBUG MESSAGES.
				PrintWriteBuffer(PCHAR(UserModeBuffer)+DeviceExtensionData->DMANumberOfAlreadyTransferedBytes,DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage);
			}

			DeviceExtensionData->DMANumberOfBytesRemainingToTransfer-=DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage;
			DeviceExtensionData->DMANumberOfAlreadyTransferedBytes+=DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage;

			// !!! Zisti sa ci DMA TRANSFER je tvoreny viacerymi STAGES.
			if (DeviceExtensionData->DMANumberOfBytesRemainingToTransfer>0)
			{
				// !!! DMA TRANSFER pokracuje vykonanim dalsej STAGE.
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA TRANSFER STARTING NEXT STAGE !\n");

				// !!! Zvysi sa VIRITUAL ADDRESS DMA TRANSFER o pocet prenesenych BYTES v CURRENT STAGE.
				//DeviceExtensionData->DMAVirtualAddressForCurrentStage=PVOID(PUCHAR(DeviceExtensionData->DMAVirtualAddressForCurrentStage)+DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage);

				// !!! Nastavi sa POCET BYTES, ktore ma nasledujuce STAGE preniest na pocet REMAINING BYTES, ktore sa v celom DMA TRANSFER este maju preniest.
				DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage=DeviceExtensionData->DMANumberOfBytesRemainingToTransfer;

				// Pomocou MACRO ADDRESS_AND_SIZE_TO_SPAN_PAGES() sa urci pocet MEMORY PAGES, ktore su potrebne na prenos zadaneho poctu BYTES pre dany BUFFER. Pocet MEMORY PAGES zavisi od pozicie BUFFER v MEMORY ako aj poctu BYTES, ktore maju byt prenesene.
				ULONG											NumberOfMemoryPages=ADDRESS_AND_SIZE_TO_SPAN_PAGES(DeviceExtensionData->DMAVirtualAddressForCurrentStage,DeviceExtensionData->DMANumberOfBytesRemainingToTransfer);

				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BUFFER ADDRESS [%p], NUMBER of BYTES to TRANSFER [%d], NUMBER of PAGES to TRANSFER [%d], NUMBER of MAP REGISTERS [%d] !\n",DeviceExtensionData->DMAVirtualAddressForCurrentStage,DeviceExtensionData->DMANumberOfBytesRemainingToTransfer,NumberOfMemoryPages,DeviceExtensionData->DMANumberOfMapRegisters);

				// !!!!! 1 MAP REGISTER obsahuje ADDRESS 1 MEMORY PAGE.
				// !!! Ak DRIVER pouziva mensi pocet pridelenych MAP REGISTERS ako pocet PAGES, ktore su potrebne na prenos celeho BUFFER, je prenos nutne rozdelit do viacerych STAGES.
				if (NumberOfMemoryPages>DeviceExtensionData->DMANumberOfAllocatedMapRegisters)
				{
					NumberOfMemoryPages=DeviceExtensionData->DMANumberOfAllocatedMapRegisters;

					// !!! CODE vypocita pocet BYTES, ktore budu prenesene pocas CURRENT STAGE.
					DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage=(NumberOfMemoryPages*PAGE_SIZE);
				}

				if (IsRead==false)
				{
					// !!!!! Kedze sa pouziva COMMON BUFFER je NUTNE NAPLNIT COMMON BUFFER tak, aby obsahoval data, ktore ma DMA transfer preniest.
					// !!!!! Pri WRITE sa data z IRP MDL sa prekopiruju do COMMON BUFFER.
					RtlCopyMemory(DeviceExtensionData->CommonBufferVirtualMemory,DeviceExtensionData->UserModeBufferForCurrentDMATransfer+DeviceExtensionData->DMANumberOfAlreadyTransferedBytes,DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage);
				}

				// !!! RETURN VALUE FUNCTION vo FIELD [DMA_OPERATIONS.MapTransfer] urcuje PHYSICAL ADDRESS, odkial sa maju data cez DMA prenos citat, aby boli zapisane do HW DEVICE.
				PHYSICAL_ADDRESS								Address=(*DeviceExtensionData->DMAAddapter->DmaOperations->MapTransfer)(DeviceExtensionData->DMAAddapter,CurrentMDL,DeviceExtensionData->DMAMapRegisterAddressBaseForCurrentStage,DeviceExtensionData->DMAVirtualAddressForCurrentStage,&DeviceExtensionData->DMANumberOfBytesToTransferForCurrentStage,!IsRead);

				// !!!!! ADDRESS ulozena v [PHYSICAL_ADDRESS] by sa teraz mala zaslat pomocou HAL FUNCTIONS do HW DEVICE, ktore by na tuto ADDRESS malo zapisovat/citat data.

				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PHYSICAL ADDRESS [%I64X] !\n",Address.QuadPart);
			}
			else
			{
				// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
				DeviceExtensionData->ReadyForDMAInterrupt=false;

				PSTR											DataToRead=(PSTR) MmGetSystemAddressForMdlSafe(CurrentMDL,NormalPagePriority);
				ULONG											NumberOfTransferedBytes;

				if (DataToRead!=nullptr)
				{
					// Nakopiruju sa DATA do OUTPUT BUFFER, ako simulacia DMA prenosu.
					//RtlCopyMemory(DataToRead,DeviceExtensionData->ReadBuffer,DeviceExtensionData->ReadBufferSize);

					NumberOfTransferedBytes=DeviceExtensionData->DMANumberOfAlreadyTransferedBytes;

					// !!! DMA TRANSFER sa skoncil.
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA TRANSFER COMPLETED !\n");
				}
				else
				{
					NumberOfTransferedBytes=0;

					// !!! DMA TRANSFER sa skoncil hodenim ERROR.
					// !!! Toto je len SIMULACIA ERROR. Ta vznikne, ak WINDOWS nedokazal uspesne zavolat FUNCTION MmGetSystemAddressForMdlSafe().
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA TRANSFER COMPLETED !\n");
				}

				// !!!!! Kedze sa pouziva SLAVE DMA, ktory pouziva SYSTEM DMA CONTROLLED, ktory je SHARED medzi viacerymi DEVICES, je NUTNE pocas CELEHO DMA TRANSFER blokovat DMA CHANNEL. Na konci DMA TRANSFER je potom NUTNE uvolnit ako MAP REGISTERS, tak aj DMA CHANNEL.
				// !!! FUNCTION vo FIELD [DMA_OPERATIONS.FreeAdapterChannel] uvolnie alokovane MAP REGISTERS a DMA CHANNEL.
				(*DeviceExtensionData->DMAAddapter->DmaOperations->FreeAdapterChannel)(DeviceExtensionData->DMAAddapter);

				// !!! CUSTOM FUNCTION CompleteRequest() ukonci spracovanie CURRENT IRP.
				CompleteRequest(InterruptRequestPacket,Status,NumberOfTransferedBytes);

				// !!! Spusti sa spracovanie noveho IRP.
				StartNextPacket(&DeviceExtensionData->DevQueue,DeviceObject);

				// !!! Kedze sa IRP SPRACOVAL, tak je NUTNE UVOLNIT REMOVE LOCK.
				IoReleaseRemoveLock(&DeviceExtensionData->RemoveLock,InterruptRequestPacket);
			}
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA TRANSFER FAILED [%X] !\n",Status);

			// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
			DeviceExtensionData->ReadyForDMAInterrupt=false;

			ULONG												NumberOfTransferedBytes=DeviceExtensionData->DMANumberOfAlreadyTransferedBytes;

			// !!!!! Kedze sa pouziva SLAVE DMA, ktory pouziva SYSTEM DMA CONTROLLED, ktory je SHARED medzi viacerymi DEVICES, je NUTNE pocas CELEHO DMA TRANSFER blokovat DMA CHANNEL. Na konci DMA TRANSFER je potom NUTNE uvolnit ako MAP REGISTERS, tak aj DMA CHANNEL.
			// !!! FUNCTION vo FIELD [DMA_OPERATIONS.FreeAdapterChannel] uvolnie alokovane MAP REGISTERS a DMA CHANNEL.
			(*DeviceExtensionData->DMAAddapter->DmaOperations->FreeAdapterChannel)(DeviceExtensionData->DMAAddapter);

			// !!! Pri ERROR sa ukonci CURRENT IRP volanim CUSTOM FUNCTION CompleteRequest(), ktora vola FUNCTION IoCompleteRequest().
			CompleteRequest(InterruptRequestPacket,Status,NumberOfTransferedBytes);

			// !!! Spusti sa spracovanie noveho IRP.
			StartNextPacket(&DeviceExtensionData->DevQueue,DeviceObject);

			// !!! Kedze sa IRP SPRACOVAL, tak je NUTNE UVOLNIT REMOVE LOCK.
			IoReleaseRemoveLock(&DeviceExtensionData->RemoveLock,InterruptRequestPacket);
		}
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
NTSTATUS GetReadStringSize(size_t& NumberOfBytes)
{
	const ULONG													NUMBER_OF_ITERATIONS=4000;

	NTSTATUS													Status;

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
NTSTATUS CopyReadString(PSTR Buffer, size_t BufferSize)
{
	const ULONG													NUMBER_OF_ITERATIONS=4000;

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
		DeviceExtensionData->ReadBufferSize=0;
		DeviceExtensionData->ReadBuffer=nullptr;

		if (DeviceExtensionData->LowerDeviceObject==NULL)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAttachDeviceToDeviceStack() FAILED !\n");
			Status=STATUS_DEVICE_REMOVED;
			break;
		}

		if (NT_SUCCESS(Status=GetReadStringSize(DeviceExtensionData->ReadBufferSize))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): GetReadStringSize() FAILED !\n");
			break;
		}

		if ((DeviceExtensionData->ReadBuffer=PCHAR(ExAllocatePoolWithTag(NonPagedPool,DeviceExtensionData->ReadBufferSize,'FUBR')))==nullptr)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): ExAllocatePoolWithTag() FAILED !\n");
			Status=STATUS_NO_MEMORY;
			break;
		}

		if (NT_SUCCESS(Status=CopyReadString(DeviceExtensionData->ReadBuffer,DeviceExtensionData->ReadBufferSize))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CopyReadString() FAILED !\n");
			break;
		}

		NewDeviceObject->Flags|=DO_POWER_PAGABLE;

		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_DMA_SLAVE_COMMON_BUFFER_DRIVER,NULL,&DeviceExtensionData->InterfaceName);
		
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

		if (DeviceExtensionData->ReadBuffer!=nullptr)
		{
			ExFreePoolWithTag(DeviceExtensionData->ReadBuffer,'FUBR');
			DeviceExtensionData->ReadBuffer=nullptr;
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
	ULONG														DMAChannel=0;
	ULONG														DMAPort=0;
	BOOLEAN														GotInterrupt=FALSE;
	BOOLEAN														GotDMA=FALSE;
	
	if (TranslatedList==NULL)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): TRANSLATED LIST is NULL !\n");
		return(STATUS_DEVICE_CONFIGURATION_ERROR);
	}

	NTSTATUS														Status=STATUS_UNSUCCESSFUL;

	for(;;)
	{
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

				case CmResourceTypeDma:
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CHANNEL [%d], PORT [%d] !\n",Resource->u.Dma.Channel,Resource->u.Dma.Port);
				
					DMAChannel=Resource->u.Dma.Channel;
					DMAPort=Resource->u.Dma.Port;
					GotDMA=TRUE;
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

		if (GotDMA==FALSE)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Didn't get expected DMA HW RESOURCE !\n");
			return(STATUS_DEVICE_CONFIGURATION_ERROR);
		}

		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): CONNECTING INTERRUPT REQUEST - Vector [%X], IRQL [%X], Mode [%X], IRQShare [%X], Affinity [%I64X] !\n",Vector,IRQL,Mode,IRQShare,Affinity);

		// !!! REALNY DEVICE by tu mal prinutit DEVICE, aby zastavil generovanie INTERRUPTS. Generovanie INTERRUPTS by sa malo obnovit az po dokonceni FUNCTION IoConnectInterrupt().

		LOG->WriteToLog("TEST 1 !\n");

		if (NT_SUCCESS(Status=IoConnectInterrupt(&DeviceExtensionData->InterruptObject,(PKSERVICE_ROUTINE) MyInterruptServiceRoutine,(PVOID) DeviceExtensionData,NULL,Vector,IRQL,IRQL,Mode,IRQShare,Affinity,FALSE))==false)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoConnectInterrupt() FAILED [%X] !\n",Status);

			Status=STATUS_NO_MEMORY;
			break;
		}

		DEVICE_DESCRIPTION											DeviceDesciption;

		RtlZeroMemory(&DeviceDesciption,sizeof(DeviceDesciption));

		DeviceDesciption.Version=DEVICE_DESCRIPTION_VERSION;
		// !!! Ak HW DEVICE pouziva SLAVE DMA, tak NIE je MASTER DMA, a preto hodnota musi byt nastavane na FALSE.
		DeviceDesciption.Master=FALSE;
		DeviceDesciption.InterfaceType=InterfaceTypeUndefined;
		DeviceDesciption.MaximumLength=PAGE_SIZE;
		DeviceDesciption.Dma32BitAddresses=TRUE;
		// !!! DMA CHANNEL sa nastavi na hodnotu ziskaju z CONFIGURATION.
		DeviceDesciption.DmaChannel=DMAChannel;
		// !!! DMA PORT sa nastavi na hodnotu ziskaju z CONFIGURATION.
		DeviceDesciption.DmaPort=DMAPort;
		DeviceDesciption.Dma32BitAddresses=FALSE;
		DeviceDesciption.ScatterGather=FALSE;
		DeviceDesciption.DemandMode=FALSE;
		DeviceDesciption.AutoInitialize=FALSE;
		// !!! Fungovalo mi to iba s hodnotou [Width8Bits].
		DeviceDesciption.DmaWidth=Width8Bits;
		DeviceDesciption.DmaSpeed=Compatible;

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

		// Alokuje sa COMMON BUFFER.
		if ((DeviceExtensionData->CommonBufferVirtualMemory=(*DeviceExtensionData->DMAAddapter->DmaOperations->AllocateCommonBuffer)(DeviceExtensionData->DMAAddapter,COMMON_BUFFER_SIZE,&DeviceExtensionData->CommonBufferLogicalAddress,FALSE))==nullptr)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): DMA_OPERATIONS.AllocateCommonBuffer() FAILED !\n");

			Status=STATUS_NO_MEMORY;
			break;
		}

		LOG->WriteToLog("TEST 4 !\n");

		// Alokuje sa MDL referujuci na COMMON BUFFER.
		if ((DeviceExtensionData->CommonBufferMDL=IoAllocateMdl(DeviceExtensionData->CommonBufferVirtualMemory,COMMON_BUFFER_SIZE,FALSE,FALSE,NULL))==nullptr)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAllocateMdl() FAILED !\n");

			Status=STATUS_NO_MEMORY;
			break;
		}

		LOG->WriteToLog("TEST 5 !\n");

		// !!! MDL sa ASOCIUJE s COMMON BUFFER.
		MmBuildMdlForNonPagedPool(DeviceExtensionData->CommonBufferMDL);

		LOG->WriteToLog("TEST 6 !\n");

		Status=STATUS_SUCCESS;
		break;
	}

	if (NT_SUCCESS(Status)==false)
	{
		// Uvolni sa MDL referujuci na COMMON BUFFER.
		if (DeviceExtensionData->CommonBufferMDL!=nullptr)
		{
			IoFreeMdl(DeviceExtensionData->CommonBufferMDL);
			DeviceExtensionData->CommonBufferMDL=nullptr;
		}

		// Uvolni sa COMMON BUFFER.
		if (DeviceExtensionData->CommonBufferVirtualMemory!=nullptr)
		{
			(*DeviceExtensionData->DMAAddapter->DmaOperations->FreeCommonBuffer)(DeviceExtensionData->DMAAddapter,COMMON_BUFFER_SIZE,DeviceExtensionData->CommonBufferLogicalAddress,DeviceExtensionData->CommonBufferVirtualMemory,FALSE);
			DeviceExtensionData->CommonBufferVirtualMemory=nullptr;
		}

		if (DeviceExtensionData->DMAAddapter!=NULL)
		{
			// !!! Zavola CUSTOM DMA FUNCTION vo FIELD [DMA_OPERATIONS.PutDmaAdapter] na uvolnenie DMA ADAPTER OBJECT.
			(*DeviceExtensionData->DMAAddapter->DmaOperations->PutDmaAdapter)(DeviceExtensionData->DMAAddapter);
			DeviceExtensionData->DMAAddapter=NULL;
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

	// Uvolni sa MDL referujuci na COMMON BUFFER.
	if (DeviceExtensionData->CommonBufferMDL!=nullptr)
	{
		IoFreeMdl(DeviceExtensionData->CommonBufferMDL);
		DeviceExtensionData->CommonBufferMDL=nullptr;
	}

	// Uvolni sa COMMON BUFFER.
	if (DeviceExtensionData->CommonBufferVirtualMemory!=nullptr)
	{
		(*DeviceExtensionData->DMAAddapter->DmaOperations->FreeCommonBuffer)(DeviceExtensionData->DMAAddapter,COMMON_BUFFER_SIZE,DeviceExtensionData->CommonBufferLogicalAddress,DeviceExtensionData->CommonBufferVirtualMemory,FALSE);
		DeviceExtensionData->CommonBufferVirtualMemory=nullptr;
	}

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

	if (DeviceExtensionData->ReadBuffer!=nullptr)
	{
		ExFreePoolWithTag(DeviceExtensionData->ReadBuffer,'FUBR');
		DeviceExtensionData->ReadBuffer=nullptr;
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
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): IoAcquireRemoveLock() FAILED [%X] !\n",Status));
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

	// !!!!! FUNCTION IoAcquireRemoveLock() sa NESMIE volat v tejto FUNCTION, ale az vo FUNCTION StartIO(). Je to NEVYHNUTNE, pretoze ak som tu zavolal FUNCTION IoAcquireRemoveLock(), tak pri IRP CANCELLATION (ked som cez CTRL-C uzatvoril beziaci TEST PROGRAM) a v DEVQUEUE boli nejake IRP, tieto sa sice UVOLNILI (boli CANCELLED), ale LOCK NEBOL DEKREMENTOVANY. Vysledok bol taky, ze sice REBOOT VIRTUAL MACHINE isiel korektne, ale pri pokuse odstranit DRIVER doslo k LOCK a WINDOWS do nekonecna cakal na uvolnenie LOCK.
	// !!!!! Ak sa FUNCTION IoAcquireRemoveLock() zavola az vo FUNCTION StartIO() k tomuto problemu nedochadza, pretoze FUNCTION StartIO() sa vola pri SPUSTENI SPRACOVANI IRP a teda ak su este IRP v DEVQUEUE, tak sa FUNCTION IoAcquireRemoveLock() pre ne nezavolala. Tym padom je LOCK vzdy iba na maximalnej hodnote 1, ktora klesne na 0, ked sa prace spracovany IRP ukonci. Tym padom NEDOCHADZA k VIACNASOBNEMU zamknutiu REMOVE LOCK.

	PDEVICE_EXTENSION											DeviceExtension=(PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	PMDL														CurrentMDL=InterruptRequestPacket->MdlAddress;
	ULONG														NumberOfBytesToTransfer=MmGetMdlByteCount(CurrentMDL);

	if (NumberOfBytesToTransfer<DeviceExtension->ReadBufferSize)
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