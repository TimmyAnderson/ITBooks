//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
#include "..\MyFDO\SharedHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PDEVICE_OBJECT													LowerDeviceObject=nullptr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PCSTR MajorFunctionToString(UCHAR Major)
{
	static const char*											Strings[]=
	{
		"IRP_MJ_CREATE",
		"IRP_MJ_CREATE_NAMED_PIPE",
		"IRP_MJ_CLOSE",
		"IRP_MJ_READ",
		"IRP_MJ_WRITE",
		"IRP_MJ_QUERY_INFORMATION",
		"IRP_MJ_SET_INFORMATION",
		"IRP_MJ_QUERY_EA",
		"IRP_MJ_SET_EA",
		"IRP_MJ_FLUSH_BUFFERS",
		"IRP_MJ_QUERY_VOLUME_INFORMATION",
		"IRP_MJ_SET_VOLUME_INFORMATION",
		"IRP_MJ_DIRECTORY_CONTROL",
		"IRP_MJ_FILE_SYSTEM_CONTROL",
		"IRP_MJ_DEVICE_CONTROL",
		"IRP_MJ_INTERNAL_DEVICE_CONTROL",
		"IRP_MJ_SHUTDOWN",
		"IRP_MJ_LOCK_CONTROL",
		"IRP_MJ_CLEANUP",
		"IRP_MJ_CREATE_MAILSLOT",
		"IRP_MJ_QUERY_SECURITY",
		"IRP_MJ_SET_SECURITY",
		"IRP_MJ_POWER",
		"IRP_MJ_SYSTEM_CONTROL",
		"IRP_MJ_DEVICE_CHANGE",
		"IRP_MJ_QUERY_QUOTA",
		"IRP_MJ_SET_QUOTA",
		"IRP_MJ_PNP",
	};

	if (Major<=IRP_MJ_MAXIMUM_FUNCTION)
	{
		const char*												Name=Strings[Major];

		return(Name);
	}
	else
	{
		return("UNKNOWN");
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPLETION ROUTINE je volana na IRQL [IRQL=DISPATCH_LEVEL] a na ARBITRARY THREAD.
NTSTATUS IrpPassDownWithCompletionRoutineCompletionRoutine(PDEVICE_OBJECT DeviceObject, PIRP Irp, PVOID Context)
{
	UNREFERENCED_PARAMETER(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - COMPLETION ROUTINE is CALLING !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	// !!!!! COMPLETION ROUTINES mozu pristupovat v CURRENT STACK LOCATION.
	PIO_STACK_LOCATION											CurrentIrpStackLocation=IoGetCurrentIrpStackLocation(Irp);
	UCHAR														MajorFunction=CurrentIrpStackLocation->MajorFunction;
	UCHAR														MinorFunction=CurrentIrpStackLocation->MinorFunction;
	PCSTR														MajorFunctionName=MajorFunctionToString(MajorFunction);
	NTSTATUS													Status=Irp->IoStatus.Status;
	ULONG_PTR													Information=Irp->IoStatus.Information;

	// !!!!! Ak DRIVER nastavi COMPLETION ROUTINE musi v COMPLETION ROUTINE VZDY skontrolovat FLAG [PendingReturned]. Ak je nastaveny, MUSI COMPLETION ROUTINE volat FUNCTION [IoMarkIrpPending()].
	if (Irp->PendingReturned!=FALSE)
	{
		// !!!!! Vykona sa propagacia FLAG [SL_PENDING_RETURNED] do STRUCTURE [IO_STACK_LOCATION] zodpovedajucemu DEVICE OBJECT VYSSIE v DEVICE OBJECT STACK.
		IoMarkIrpPending(Irp);
	}

	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - COMPLETION ROUTINE is CALLED !!! MAJOR [%hhu] MINOR [%hhu] MAJOR NAME [%s] STATUS [%lX] INFORMATION [%I64u].\n",DeviceObject->DriverObject->DriverName,FunctionName,MajorFunction,MinorFunction,MajorFunctionName,Status,Information));

	// !!!!! STATUS iny ako STATUS [STATUS_MORE_PROCESSING_REQUIRED] znamena, ze INTERRUPT REQUEST PACKET bude dalej propagovany nahor v DEVICE OBJECT STACK.
	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineForAllIRPs(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status;
	PIO_STACK_LOCATION											CurrentIrpStackLocation=IoGetCurrentIrpStackLocation(Irp);
	PCSTR														MajorFunctionName=MajorFunctionToString(CurrentIrpStackLocation->MajorFunction);

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] for MAJOR FUNCTION [%s] !!!\n",FunctionName,MajorFunctionName));

	// !!!!! CURRENT [PIO_STACK_LOCATION] sa skopiruje do pozicie pre DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK.
	IoCopyCurrentIrpStackLocationToNext(Irp);

	// !!!!! Nastavi sa COMPLETION ROUTINE.
	// !!!!! FUNCTION [IoSetCompletionRoutineEx()] sa MUSI volat AZ po FUNCTION [IoCopyCurrentIrpStackLocationToNext()], pretoze POINTER na COMPLETION ROUTINE sa uklada do STACK LOCATION pre DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK.
	Status=IoSetCompletionRoutineEx(DeviceObject,Irp,IrpPassDownWithCompletionRoutineCompletionRoutine,nullptr,true,true,true);

	// !!!!!! FUNCTION [IoSetCompletionRoutineEx()] pri uspesnom skonceni alokuje MEMORY BLOCK, ktory je uvolneny IBA ak DRIVER nasledne zavola FUNCTION [IoCallDriver()].
	if (NT_SUCCESS(Status)==true)
	{
		// !!!!! IRP sa odosle do DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK.
		Status=IoCallDriver(LowerDeviceObject,Irp);
	}
	else
	{
		KdPrint(("!!!!! DRIVER FUNCTION [%s] FAILED to SET COMPLETION ROUTINE with ERROR CODE [%lX] !!!\n",FunctionName,Status));

		// !!!!! Kedze sa nenastavila COMPLETION ROUTINE, tak INTERRUPT REQUEST PACKET je okamzite ukonceny
		Status=CHelpers::CompleteIRP(Irp,Status,0);
	}

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] for MAJOR FUNCTION [%s] !!!\n",FunctionName,MajorFunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER UNLOAD sa vola AZ ked su ukoncene vsetky IRP, pricom dalsie IRP po spusteni iniciovani UNLOAD procesu uz nedovoli WINDOWS odoslat.
// !!!!! To znamena, ze DRIVER UNLOAD NEMUSI kontrolovat ci este nebezia nejake IRP daneho DRIVER, pretoze ak by bezali, tak WINDOWS DRIVER UNLOAD NESPUSTI, az kym nebudu vsetky IRP ukoncene.
// !!!!! DRIVER UNLOAD NIE JE spusteny, az kym vsetky DEFFERED PROCEDURE CALLS, ktore spustil dany DRIVER NIE su UKONCENE.
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	// !!! Odpoji sa FILTER DEVICE OBJECT od LOWER DEVICE OBJECT.
	IoDetachDevice(LowerDeviceObject);

	LowerDeviceObject=nullptr;

	IoDeleteDevice(DriverObject->DeviceObject);

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	DriverObject->DriverUnload=FunctionDriverUnload;

	for (size_t Index=0;Index<ARRAYSIZE(DriverObject->MajorFunction);Index++)
	{
		DriverObject->MajorFunction[Index]=DispatchRoutineForAllIRPs;
	}

	NTSTATUS													Status=STATUS_SUCCESS;
	PFILE_OBJECT												FileObject;
	PDEVICE_OBJECT												TargetDeviceObject=nullptr;
	PDEVICE_OBJECT												DeviceObject=nullptr;
	UNICODE_STRING												TargetDeviceName;
	UNICODE_STRING												DeviceName;

	RtlInitUnicodeString(&TargetDeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_FILTER_DRIVER_NAME);

	do
	{
		// !!!!! Najde sa LOWER DEVICE OBJECT.
		Status=IoGetDeviceObjectPointer(&TargetDeviceName,FILE_READ_DATA,&FileObject,&TargetDeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to FIND TARGET DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		Status=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,TRUE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		// !!!!! Skopiruje sa SETTINGS z LOWER DEVICE OBJECT do FILTER DEVICE OBJECT.
		DeviceObject->Flags|=(TargetDeviceObject->Flags & (DO_BUFFERED_IO | DO_DIRECT_IO));
		DeviceObject->DeviceType=TargetDeviceObject->DeviceType;

		// !!!!! Ak by bolo pripojenych viacero DEVICE OBJECT FILTERS k TARGET DEVICE OBJECT, tak VARIABLE [TargetDeviceObject] a VARIABLE [LowerDeviceObject] sa budu LISIT.
		// !!!!! Volanie FUNCTION OKAMZITE generuje INTERRUPT REQUEST PACKETS s MAJOR FUNCTION [IRP_MJ_CREATE] a MAJOR FUNCTION [IRP_MJ_CLEANUP], a kedze DISPATCH ROUTINES, ak chcu posielat tieto INTERRUPT REQUEST PACKETS do DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK, MUSIA mat uz k dispozicii POINTER na DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK. Preto PARAMETER [PDEVICE_OBJECT* AttachedDevice] sa MUSI ukladat do VARIABLE, ktora je pristupna z DISPATCH ROUTINES.
		// !!!!! VARIABLE [LowerDeviceObject] sa pouziva v DISPATCH ROUTINE, takze je to OK.
		Status=IoAttachDeviceToDeviceStackSafe(DeviceObject,TargetDeviceObject,&LowerDeviceObject);

		// !!!!! Tieto FLAGS musia byt nastavene pre FILTER DEVICE OBJECTS nad HW DEVICES.
		DeviceObject->Flags&=~DO_DEVICE_INITIALIZING;
		DeviceObject->Flags|=DO_POWER_PAGABLE;

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to ATTACH to TARGET DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to START !!!\n",DriverObject->DriverName));

		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}

		LowerDeviceObject=nullptr;
	}

	// !!!!! FILE OBJECT sa uvolni VZDY. Ak je ATTACHED, tak ATTACH drzi REFERENCE a ak nie je ATTACHED, tak doslo k ERROR a je potrebne FILE OBJECT uvolnit.
	if (FileObject!=nullptr)
	{
		ObDereferenceObject(FileObject);
		FileObject=nullptr;
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------