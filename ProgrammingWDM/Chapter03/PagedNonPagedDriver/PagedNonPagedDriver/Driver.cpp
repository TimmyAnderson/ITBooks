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
// Identifikatory IO OPERATIONS.
#define IOCTL_SIMPLE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_PAGED_MEMORY_TEST_1 CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_PAGED_MEMORY_TEST_2 CTL_CODE(FILE_DEVICE_UNKNOWN,0x803,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_PAGED_MEMORY_TEST_3 CTL_CODE(FILE_DEVICE_UNKNOWN,0x804,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_PAGED_MEMORY_TEST_4 CTL_CODE(FILE_DEVICE_UNKNOWN,0x805,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_NON_PAGED_MEMORY_TEST_1 CTL_CODE(FILE_DEVICE_UNKNOWN,0x806,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_NON_PAGED_MEMORY_TEST_2 CTL_CODE(FILE_DEVICE_UNKNOWN,0x807,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_NON_PAGED_MEMORY_TEST_3 CTL_CODE(FILE_DEVICE_UNKNOWN,0x808,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_NON_PAGED_MEMORY_TEST_4 CTL_CODE(FILE_DEVICE_UNKNOWN,0x809,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_PAGED_CODE_WITH_DYNAMIC_LOCKING CTL_CODE(FILE_DEVICE_UNKNOWN,0x80A,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_MUTEX_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x80B,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! Simuluje UKONCENIE IRP po nejakom case, ktory simuluje PROCESSING IRP.
_Function_class_(KSTART_ROUTINE)
void IRPCompleteSimulator(PVOID Parameter)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD STARTED !\n");

	PIRP														InterruptRequestPacket=(PIRP) Parameter;
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

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): WORKER THREAD FINISHED !\n");

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v PAGED MEMORY.
#pragma code_seg("PAGE")
// !!!!! CODE sposobi BUG CHECK, aj ked az po intenzivnom opakovanom testovani (radovo 1000ce iteracii).
// !!!!! Ak sa vsak odkomentuje MACRO PAGED_CODE(), tak dojde k STUHNUTIU WINDOWS, pretoze sa vyvola ASSERT. Tento ASSERT je mozne odchytit, ak je WINDOWS spusteny so zapnutym DEBUGGEROM.
void PagedFunction(void)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION PagedFunction1(): CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	// !!!!! Ak sa MACRO PAGED_CODE() pouzije v FREE BUILD, tak vykona kontrolu IRQL a ak plati, ze IRQL>=DISPATCH_LEVEL, tak sposobi ASSERT. V praxi je vysledok taky, ze WINDOWS UPLNE STUHNE. Ak je pripojeny DEBUGGER, tak tento zobrazi ASSERT hlasku.
	PAGED_CODE()

	KdPrint((DRIVERLOGNAME " - FUNCTION PagedFunction2(): CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));
}
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v NON-PAGED MEMORY.
#pragma code_seg()
void NonPagedFunction(void)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION NonPagedFunction(): CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));
}
//-------------------------------------------------------------------------------------------------------
// !!! Sposobi, ze nasledujuca FUNCTION bude ulozena v PAGED MEMORY. C++ staci ak CODE SEGMENT zacina textom 'PAGE'.
#pragma code_seg("PAGEXXX")
// !!!!! CODE sposobi BUG CHECK, aj ked az po intenzivnom opakovanom testovani (radovo 1000ce iteracii).
void PagedFunctionWithDynamicLocking(void)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION PagedFunctionWithDynamicLocking1(): CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	// !!!!! Tu MACRO PAGED_CODE() NESMIE BYT POUZITE.
	// !!!!! V tomto CODE sa ulozenie v PAGED, alebo NON-PAGED MEMORY DYNAMICKY MENI (pomocou FUNCTIONS MmLockPagableCodeSection() a MmUnlockPageableImageSection()). Kedze vsak MACRO vykonava iba jednoducho kontrolu ci IRQL<DISPATCH_LEVEL, pricom ak tato podmienka plati - AJ NAPRIEK TOMU, ze CODE je aktualne LOCKED v NON-PAGED MEMORY pomocou FUNCTION MmLockPagableCodeSection() - tak MACRO PAGED_CODE() generuje INTERRUPT 2C, ktore sposobi BUG CHECK. Preto sa MACRO PAGED_CODE() v takomto CODE NESMIE POUZIVAT.
	//PAGED_CODE()

	// !!!!! MACRO PAGED_CODE_LOCKED() na rozdiel od MACRO PAGED_CODE() NESPOSOBI BUG CHECK.
	// !!!!! MACRO PAGED_CODE_LOCKED() okrem IRQL kontroluje aj to ci je V DANEJ CHVILI CODE LOCKED (je v NON-PAGED MEMORY). Ak je IRQL>=DISPATCH_LEVEL a ZAROVEN je CODE v NON-PAGED MEMORY, tak sa BUG CHECK NEGENERUJE.
	PAGED_CODE_LOCKED()

	KdPrint((DRIVERLOGNAME " - FUNCTION PagedFunctionWithDynamicLocking2(): CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma code_seg()
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
// Sposobi, ze nasledujuca FUNCTION bude ulozena v PAGED MEMORY.
// !!!!! CODE sposobi BUG CHECK, aj ked az po intenzivnom opakovanom testovani (radovo 1000ce iteracii).
#pragma code_seg("PAGE")
NTSTATUS ProcessIOControlPagedMemoryTest1(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest1(): BEFORE PAGED_CODE() !\n"));

	// !!!!! Ak sa MACRO PAGED_CODE() pouzije v FREE BUILD, tak vykona kontrolu IRQL a ak plati, ze IRQL>=DISPATCH_LEVEL, tak sposobi ASSERT. V praxi je vysledok taky, ze WINDOWS UPLNE STUHNE. Ak je pripojeny DEBUGGER, tak tento zobrazi ASSERT hlasku.
	PAGED_CODE()

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest1(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	KIRQL														OriginalIRQL;

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest1(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest1(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	KeLowerIrql(OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest1(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v PAGED MEMORY.
// !!!!! CODE sposobi BUG CHECK, aj ked az po intenzivnom opakovanom testovani (radovo 1000ce iteracii).
#pragma code_seg("PAGE")
NTSTATUS ProcessIOControlPagedMemoryTest2(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest2(): BEFORE PAGED_CODE() !\n"));

	// !!!!! Ak sa MACRO PAGED_CODE() pouzije v FREE BUILD, tak vykona kontrolu IRQL a ak plati, ze IRQL>=DISPATCH_LEVEL, tak sposobi ASSERT. V praxi je vysledok taky, ze WINDOWS UPLNE STUHNE. Ak je pripojeny DEBUGGER, tak tento zobrazi ASSERT hlasku.
	PAGED_CODE()

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest2(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	KIRQL														OriginalIRQL;

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest2(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest2(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	// Zavola FUNCTION v PAGED MEMORY.
	PagedFunction();

	KeLowerIrql(OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest2(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v PAGED MEMORY.
// !!!!! CODE sposobi BUG CHECK, aj ked az po intenzivnom opakovanom testovani (radovo 1000ce iteracii).
#pragma code_seg("PAGE")
NTSTATUS ProcessIOControlPagedMemoryTest3(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest3(): BEFORE PAGED_CODE() !\n"));

	// !!!!! Ak sa MACRO PAGED_CODE() pouzije v FREE BUILD, tak vykona kontrolu IRQL a ak plati, ze IRQL>=DISPATCH_LEVEL, tak sposobi ASSERT. V praxi je vysledok taky, ze WINDOWS UPLNE STUHNE. Ak je pripojeny DEBUGGER, tak tento zobrazi ASSERT hlasku.
	PAGED_CODE()

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest3(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest3(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	for (int Index=0;Index<1000;Index++)
	{
		KIRQL													OriginalIRQL;

		KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest3(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		KeLowerIrql(OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest3(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v PAGED MEMORY.
// !!!!! CODE sposobi BUG CHECK, aj ked az po intenzivnom opakovanom testovani (radovo 1000ce iteracii).
#pragma code_seg("PAGE")
NTSTATUS ProcessIOControlPagedMemoryTest4(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest4(): BEFORE PAGED_CODE() !\n"));

	// !!!!! Ak sa MACRO PAGED_CODE() pouzije v FREE BUILD, tak vykona kontrolu IRQL a ak plati, ze IRQL>=DISPATCH_LEVEL, tak sposobi ASSERT. V praxi je vysledok taky, ze WINDOWS UPLNE STUHNE. Ak je pripojeny DEBUGGER, tak tento zobrazi ASSERT hlasku.
	PAGED_CODE()

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest4(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for (int Index=0;Index<1000;Index++)
	{
		KIRQL													OriginalIRQL;

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest4(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest4(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		// Zavola FUNCTION v PAGED MEMORY.
		PagedFunction();

		KeLowerIrql(OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlPagedMemoryTest4(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v NON-PAGED MEMORY.
#pragma code_seg()
NTSTATUS ProcessIOControlNonPagedMemoryTest1(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest1(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	KIRQL														OriginalIRQL;

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest1(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest1(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	KeLowerIrql(OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest1(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v NON-PAGED MEMORY.
#pragma code_seg()
NTSTATUS ProcessIOControlNonPagedMemoryTest2(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest2(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	KIRQL														OriginalIRQL;

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest2(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest2(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	NonPagedFunction();

	KeLowerIrql(OriginalIRQL);

	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest2(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v NON-PAGED MEMORY.
#pragma code_seg()
NTSTATUS ProcessIOControlNonPagedMemoryTest3(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest3(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	for (int Index=0;Index<1000;Index++)
	{
		KIRQL													OriginalIRQL;

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest3(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest3(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		KeLowerIrql(OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest3(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v NON-PAGED MEMORY.
#pragma code_seg()
NTSTATUS ProcessIOControlNonPagedMemoryTest4(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest4(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for (int Index=0;Index<1000;Index++)
	{
		KIRQL													OriginalIRQL;

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest4(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest4(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		NonPagedFunction();

		KeLowerIrql(OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlNonPagedMemoryTest4(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
// Sposobi, ze nasledujuca FUNCTION bude ulozena v NON-PAGED MEMORY.
#pragma code_seg()
NTSTATUS ProcessIOControlPagedCodeDynamicLocking(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDynamicLocking(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	for (int Index=0;Index<1000;Index++)
	{
		// !!! Vykona sa LOCKING CODE SECTION cim sa SECTION presunie do NON-PAGED MEMORY.
		PVOID													ImageSectionHandle=MmLockPagableCodeSection(PagedFunctionWithDynamicLocking);

		KIRQL													OriginalIRQL;

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDynamicLocking(): BEFORE RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		KeRaiseIrql(DISPATCH_LEVEL,&OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDynamicLocking(): AFTER RAISE - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		// Zavola FUNCTION v PAGED MEMORY.
		PagedFunctionWithDynamicLocking();

		KeLowerIrql(OriginalIRQL);

		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlDynamicLocking(): AFTER LOWER - CURRENT IRQL [%d] !\n",KeGetCurrentIrql()));

		// !!! Vykona sa LOCKING CODE SECTION cim sa SECTION presunie do PAGED MEMORY.
		MmUnlockPagableImageSection(ImageSectionHandle);
	}

	Status=STATUS_SUCCESS;

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma code_seg()
_Function_class_(KSTART_ROUTINE)
void WorkerThreadTestMutex(PVOID Param)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD STARTED [%p] !\n",PsGetCurrentThreadId()));

	NTSTATUS													Status=STATUS_SUCCESS;
	PKMUTEX														TypedParam=(PKMUTEX) Param;

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD [%p] - BEFORE WAIT - KERNEL MUTEX STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateMutex(TypedParam)));

	KeWaitForSingleObject(TypedParam,Executive,KernelMode,FALSE,NULL);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD [%p] - AFTER WAIT - KERNEL MUTEX STATE [%d], IRQL [%d] !\n",PsGetCurrentThreadId(),KeReadStateMutex(TypedParam),KeGetCurrentIrql()));

	LARGE_INTEGER												Timeout;

	Timeout.QuadPart=1000*(-10*1000);

	// !!! POCKAM 1 SEKUNDU.
	if (NT_SUCCESS(Status=KeDelayExecutionThread(KernelMode,FALSE,&Timeout))==true)
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): THREAD DELAY FINISHED !\n"));
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): KeDelayExecutionThread() FAILED [%X] !\n",Status));
	}

	// !!! UVOLNI sa MUTEX.
	KeReleaseMutex(TypedParam,FALSE);

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD [%p] - AFTER RELEASE - KERNEL MUTEX STATE [%d] !\n",PsGetCurrentThreadId(),KeReadStateMutex(TypedParam)));

	KdPrint((DRIVERLOGNAME " - FUNCTION WorkerThreadTestMutex(): WORKER THREAD FINISHED [%p] !\n",PsGetCurrentThreadId()));

	PsTerminateSystemThread(Status);
}
//-------------------------------------------------------------------------------------------------------
#pragma code_seg()
NTSTATUS ProcessIOControlMutexTest(PIRP, DEVICE_EXTENSION*, ULONG, ULONG, ULONG, ULONG&)
{
	KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): PROCESSING IO CONTROL !\n"));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	// !!! KERNEL MUTEX MUSI byt v NON-PAGED MEMORY.
	PKMUTEX														Mutex=(PKMUTEX) ExAllocatePoolWithTag(NonPagedPool,sizeof(KMUTEX),' TUM');

	if (Mutex!=NULL)
	{
		// !!! VYTVORI sa MUTEX. Je v SIGNALIZED STATE.
		KeInitializeMutex(Mutex,0);

		const int												THREAD_COUNT=10;

		HANDLE													ThreadHandles[THREAD_COUNT];
		OBJECT_ATTRIBUTES										ThreadHandleObjectAttributes[THREAD_COUNT];
		PKTHREAD												Threads[THREAD_COUNT];

		RtlZeroMemory(ThreadHandles,sizeof(ThreadHandles));
		RtlZeroMemory(ThreadHandleObjectAttributes,sizeof(ThreadHandleObjectAttributes));
		RtlZeroMemory(Threads,sizeof(Threads));

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			InitializeObjectAttributes(&ThreadHandleObjectAttributes[Index],NULL,OBJ_KERNEL_HANDLE,NULL,NULL);
		}

		bool													HasError=false;

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandles[Index],THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes[Index],NULL,NULL,WorkerThreadTestMutex,Mutex))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): CAN'T CREATE THREAD !\n"));
				HasError=true;
				break;
			}
		}

		if (HasError==false)
		{
			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (ThreadHandles[Index]!=NULL)
				{
					if (NT_SUCCESS(Status=ObReferenceObjectByHandle(ThreadHandles[Index],THREAD_ALL_ACCESS,NULL,KernelMode,(PVOID*) &Threads[Index],NULL))==false)
					{
						KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): ObReferenceObjectByHandle() for THREAD FAILED [%X] !\n",Status));
						HasError=true;
						break;
					}
				}
			}

			if (HasError==false)
			{
				KWAIT_BLOCK										WaitBlocks[THREAD_COUNT];

				Status=KeWaitForMultipleObjects(THREAD_COUNT,(PVOID*) Threads,WaitAll,Executive,KernelMode,FALSE,NULL,WaitBlocks);

				if (Status==STATUS_SUCCESS)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): WAIT for WORKER THREADS to FINISH COMPLETED SUCCESSFULLY - STATUS [%X] !\n",Status));
				}
				else if (Status==STATUS_TIMEOUT)
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): WAIT for WORKER THREADS to FINISH COMPLETED after TIMEOUT EXPIRATION - STATUS [%X] !\n",Status));
				}
				else
				{
					KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): WAIT for WORKER THREADS to FINISH COMPLETED wih FAILURE - STATUS [%X] !\n",Status));
				}
			}

			for (int Index=0;Index<THREAD_COUNT;Index++)
			{
				if (Threads[Index]!=NULL)
				{
					ObDereferenceObject(Threads[Index]);
					Threads[Index]=NULL;
				}
			}
		}

		for (int Index=0;Index<THREAD_COUNT;Index++)
		{
			if (ThreadHandles[Index]!=NULL)
			{
				ZwClose(ThreadHandles[Index]);
				ThreadHandles[Index]=NULL;
			}
		}

		ExFreePoolWithTag(Mutex,' TUM');
		Mutex=NULL;

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION ProcessIOControlMutexTest(): CAN'T ALLOCATE NON PAGED MEMORY !\n"));
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

		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_DEVICE_INTERFACE_DRIVER,NULL,&DeviceExtensionData->InterfaceName);
		
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
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_READ)
NTSTATUS DispatchRead(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);

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
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_WRITE)
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket);
	
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - MdlAddress [%p], UserBuffer [%p], AssociatedIrp.SystemBuffer [%p] !\n",InterruptRequestPacket->MdlAddress,InterruptRequestPacket->UserBuffer,InterruptRequestPacket->AssociatedIrp.SystemBuffer);

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;
	HANDLE														ThreadHandle;
	OBJECT_ATTRIBUTES											ThreadHandleObjectAttributes;

	InitializeObjectAttributes(&ThreadHandleObjectAttributes,NULL,OBJ_KERNEL_HANDLE,NULL,NULL);

	// !!!!! V THREADE sa SIMULUJE PROCESSING IRP.
	if (NT_SUCCESS(Status=PsCreateSystemThread(&ThreadHandle,THREAD_ALL_ACCESS,&ThreadHandleObjectAttributes,NULL,NULL,IRPCompleteSimulator,InterruptRequestPacket))==true)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): SYSTEM THREAD CREATED !\n");

		ZwClose(ThreadHandle);
		ThreadHandle=NULL;

		// !!!!! IRP je NUTNE nastavit na PENDING.
		IoMarkIrpPending(InterruptRequestPacket);

		// !!!!! Kedze IRP NEBOL SKONCENY, tak sa vracia hodnota STATUS_PENDING.
		return(STATUS_PENDING);
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status);

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
_Function_class_(DRIVER_DISPATCH)
_Dispatch_type_(IRP_MJ_WRITE)
NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP InterruptRequestPacket)
{
	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): BEGIN - DeviceObject [%p], InterruptRequestPacket [%p] !\n",DeviceObject,InterruptRequestPacket));

	NTSTATUS													Status=STATUS_UNSUCCESSFUL;

	DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): PsCreateSystemThread() FAILED [%X] !\n",Status));

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

		case IOCTL_PAGED_MEMORY_TEST_1:
		{
			Status=ProcessIOControlPagedMemoryTest1(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_PAGED_MEMORY_TEST_2:
		{
			Status=ProcessIOControlPagedMemoryTest2(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_PAGED_MEMORY_TEST_3:
		{
			Status=ProcessIOControlPagedMemoryTest3(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_PAGED_MEMORY_TEST_4:
		{
			Status=ProcessIOControlPagedMemoryTest4(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_NON_PAGED_MEMORY_TEST_1:
		{
			Status=ProcessIOControlNonPagedMemoryTest1(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_NON_PAGED_MEMORY_TEST_2:
		{
			Status=ProcessIOControlNonPagedMemoryTest2(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_NON_PAGED_MEMORY_TEST_3:
		{
			Status=ProcessIOControlNonPagedMemoryTest3(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_NON_PAGED_MEMORY_TEST_4:
		{
			Status=ProcessIOControlNonPagedMemoryTest4(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_PAGED_CODE_WITH_DYNAMIC_LOCKING:
		{
			Status=ProcessIOControlPagedCodeDynamicLocking(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
		}
		break;

		case IOCTL_MUTEX_TEST:
		{
			Status=ProcessIOControlMutexTest(InterruptRequestPacket,DeviceExtensionData,Code,InputBufferLength,OutputBufferLength,Info);
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