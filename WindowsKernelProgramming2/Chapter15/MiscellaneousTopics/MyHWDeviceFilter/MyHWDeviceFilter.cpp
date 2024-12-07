//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
#include "SDeviceExtension.h"
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
NTSTATUS MyGenericDispatchRoutine(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	PIO_STACK_LOCATION											CurrentIrpStackLocation=IoGetCurrentIrpStackLocation(Irp);
	PCSTR														MajorFunctionName=MajorFunctionToString(CurrentIrpStackLocation->MajorFunction);

	KdPrint(("!!!!! DRIVER [%p] EXECUTING DISPATCH ROUTINE [%s] for MAJOR FUNCTION [%s] !!!\n",DeviceObject,FunctionName,MajorFunctionName));

	NTSTATUS													Status;
	SDeviceExtension*											DeviceExtension=static_cast<SDeviceExtension*>(DeviceObject->DeviceExtension);

	// !!!!! Vykona sa pokus o ziskanie REMOVE LOCK.
	// !!! 2. PARAMETER je TAG.
	Status=IoAcquireRemoveLock(&DeviceExtension->MRemoveLock,Irp);

	if (NT_SUCCESS(Status)==true)
	{
		// !!!!! CURRENT [PIO_STACK_LOCATION] sa skopiruje do pozicie pre DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK.
		IoCopyCurrentIrpStackLocationToNext(Irp);

		// !!!!! IRP sa odosle do DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK.
		// !!!!! Po zavolani FUNCTION [IoCallDriver()] uz CURRENT STACK LOCATION POINTER je NEPLATNY.
		Status=IoCallDriver(DeviceExtension->MLowerDeviceObject,Irp);

		// !!!!! Uvolni sa REMOVE LOCK.
		// !!! 2. PARAMETER je TAG.
		IoReleaseRemoveLock(&DeviceExtension->MRemoveLock,Irp);
	}
	// !!!!! PRISIEL ERROR CODE [STATUS_DELETE_PENDING], ktory znamena, ze IRP je treba okamzite ukoncit, pretoze sa zajahil proces DEVICE REMOVAL.
	else
	{
		KdPrint(("!!!!! DRIVER [%p] FAILED to ACQUIRE REMOVE LOCK with ERROR CODE [%lX] !!!\n",DeviceObject,Status));

		// !!!!! Nastavi sa ERROR STATUS na IRP.
		Status=CHelpers::CompleteIRP(Irp,Status,0);
	}

	KdPrint(("!!!!! DRIVER [%p] EXECUTED DISPATCH ROUTINE [%s] for MAJOR FUNCTION [%s] !!!\n",DeviceObject,FunctionName,MajorFunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineForPNP(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	PIO_STACK_LOCATION											CurrentIrpStackLocation=IoGetCurrentIrpStackLocation(Irp);
	PCSTR														MajorFunctionName=MajorFunctionToString(CurrentIrpStackLocation->MajorFunction);
	UCHAR														MinorFunction=CurrentIrpStackLocation->MinorFunction;

	KdPrint(("!!!!! DRIVER [%p] EXECUTING DISPATCH ROUTINE [%s] for MAJOR FUNCTION [%s] and MINOR FUNCTION [%hhu] !!!\n",DeviceObject,FunctionName,MajorFunctionName,MinorFunction));

	NTSTATUS													Status;
	SDeviceExtension*											DeviceExtension=static_cast<SDeviceExtension*>(DeviceObject->DeviceExtension);

	// !!!!! Vykona sa pokus o ziskanie REMOVE LOCK.
	// !!! 2. PARAMETER je TAG.
	Status=IoAcquireRemoveLock(&DeviceExtension->MRemoveLock,Irp);

	if (NT_SUCCESS(Status)==true)
	{
		// !!!!! CURRENT [PIO_STACK_LOCATION] sa skopiruje do pozicie pre DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK.
		IoCopyCurrentIrpStackLocationToNext(Irp);

		// !!!!! IRP sa odosle do DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK.
		// !!!!! Po zavolani FUNCTION [IoCallDriver()] uz CURRENT STACK LOCATION POINTER je NEPLATNY.
		Status=IoCallDriver(DeviceExtension->MLowerDeviceObject,Irp);

		// !!!!! Po odoslani INTERRUPT REQUEST PACKET do DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK sa vykonava kontrola ci sa nejedna o INTERRUPT REQUEST PACKET s MINOR FUNCTION [IRP_MN_REMOVE_DEVICE]. Ta je indikatorom, ze DEVICE OBJECT musi byt DETACHED a DELETED.
		// !!!!! Ak sa nejedna o MINOR FUNCTION [IRP_MN_REMOVE_DEVICE], tak sa PNP IRP spracuje normalne a RELEASE LOCK uvolni volanim FUNCTION [IoReleaseRemoveLock()].
		if (MinorFunction!=IRP_MN_REMOVE_DEVICE)
		{
			// !!!!! Uvolni sa REMOVE LOCK.
			// !!! 2. PARAMETER je TAG.
			IoReleaseRemoveLock(&DeviceExtension->MRemoveLock,Irp);
		}
		// !!!!! Ak sa nejedna o MINOR FUNCTION [IRP_MN_REMOVE_DEVICE], tak sa PNP IRP spracuje normalne a RELEASE LOCK uvolni volanim FUNCTION [IoReleaseRemoveLockAndWait()].
		else
		{
			KdPrint(("!!!!! IRP PNP DETECTED MINOR CODE [IRP_MN_REMOVE_DEVICE] !!!\n"));

			// !!!!! FUNCTION vykona WAIT, az kym VSETKY IRP spracovavane dany DEVICE OBJECT STACK nie su ukoncene.
			// !!! 2. PARAMETER je TAG.
			IoReleaseRemoveLockAndWait(&DeviceExtension->MRemoveLock,Irp);

			KdPrint(("!!!!! REMOVE LOCK UNLOCKED. DEVICE OBJECT will be DETACHED !!!\n"));

			// !!!!! Vykona sa DETACH DEVICE OBJECT.
			IoDetachDevice(DeviceExtension->MLowerDeviceObject);

			KdPrint(("!!!!! DEVICE OBJECT is DETACHED !!!\n"));

			// !!!!! Vykona sa DELETE DEVICE OBJECT.
			IoDeleteDevice(DeviceObject);

			KdPrint(("!!!!! DEVICE OBJECT is DELETED !!!\n"));
		}
	}
	// !!!!! PRISIEL ERROR CODE [STATUS_DELETE_PENDING], ktory znamena, ze IRP je treba okamzite ukoncit, pretoze sa zajahil proces DEVICE REMOVAL.
	else
	{
		KdPrint(("!!!!! DRIVER FAILED to ACQUIRE REMOVE LOCK with ERROR CODE [%lX] !!!\n",Status));

		// !!!!! Nastavi sa ERROR STATUS na IRP.
		Status=CHelpers::CompleteIRP(Irp,Status,0);
	}

	// !!!!! Aj ked sa pri prichode MINOR FUNCTION [IRP_MN_REMOVE_DEVICE] uvolnil DEVICE OBJECT [DeviceObject], ktory je tam NEPLATNY, tak jeho POINTER je mozne vypisat do LOGU, kedze sa vypisuje iba POINTER, a nevykona POINTER DEREFERENCING. Ak by sa vsak POINTER DEREFERENCING vykonal (napriklad pristupom k DEVICE OBJECT EXTENSION) doslo by k pristupu k neplatnemu POINTER a tym padom k BUG CHECK.
	KdPrint(("!!!!! DRIVER [%p] EXECUTED DISPATCH ROUTINE [%s] for MAJOR FUNCTION [%s] and MINOR FUNCTION [%hhu] !!!\n",DeviceObject,FunctionName,MajorFunctionName,MinorFunction));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION sa vola, ak PLUG AND PLAY MANAGER potrebuje pridat DEVICE OBJECT do DEVICE OBJECT STACK.
NTSTATUS MyAddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT PhysicalDeviceObject)
{
	UNREFERENCED_PARAMETER(PhysicalDeviceObject);

	KdPrint(("!!!!! DRIVER [%wZ] ADDING DEVICE !!!\n",DriverObject->DriverName));

	NTSTATUS													Status;
	PDEVICE_OBJECT												DeviceObject=nullptr;

	do
	{
		// !!!!! FILTER DEVICE OBJECTS nemusia mat NAME. A ak ho aj maju, musi sa vytvarat DYNAMICKY ako UNIKATNY NAME, ak by bol DRIVER pouzivany vo viacerych DEVICE OBJECT STACKS.
		Status=IoCreateDevice(DriverObject,sizeof(SDeviceExtension),nullptr,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		SDeviceExtension*										DeviceExtension=static_cast<SDeviceExtension*>(DeviceObject->DeviceExtension);

		DeviceExtension->MPhysicalDeviceObject=PhysicalDeviceObject;

		// !!! Inicializuje sa REMOVE LOCK.
		// !!!!! STRUCTURE [IO_REMOVE_LOCK] NESMIE byt NIKDY REINITIALIZED. Po skonceni jej pouzivania sa NESMIE opatovne pouzit pre iny DEVICE OBJECT. Preto najrozumnejsie miesto ulozenia REMOVE LOCK je DEVICE OBJECT EXTENSION, ktora sa alokuje pri vytvoreni DEVICE OBJECT a uvolnuje pri odstraneni DEVICE OBJECT.
		IoInitializeRemoveLock(&DeviceExtension->MRemoveLock,MY_TAG,0,0);

		// !!!!! DEVICE OBJECT SETTINGS MUSIA byt nastavene ESTE pred ATTACH, pretoze po zavolani ATTACH uz mozu prichadza IRPs.
		DeviceObject->Flags|=(PhysicalDeviceObject->Flags & (DO_BUFFERED_IO | DO_DIRECT_IO));
		DeviceObject->DeviceType=PhysicalDeviceObject->DeviceType;

		// !!!!! Volanie ATTACH sposobi, ze OKAMZITE mozu zacat prichadzat IRPs.
		// !!!!! Volanie FUNCTION OKAMZITE generuje INTERRUPT REQUEST PACKETS s MAJOR FUNCTION [IRP_MJ_CREATE] a MAJOR FUNCTION [IRP_MJ_CLEANUP], a kedze DISPATCH ROUTINES, ak chcu posielat tieto INTERRUPT REQUEST PACKETS do DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK, MUSIA mat uz k dispozicii POINTER na DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK. Preto PARAMETER [PDEVICE_OBJECT* AttachedDevice] sa MUSI ukladat do VARIABLE, ktora je pristupna z DISPATCH ROUTINES.
		// !!!!! VARIABLE [DeviceExtension->MLowerDeviceObject] sa pouziva v DISPATCH ROUTINE, takze je to OK.
		Status=IoAttachDeviceToDeviceStackSafe(DeviceObject,PhysicalDeviceObject,&DeviceExtension->MLowerDeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to ATTACH to PHYSICAL DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		// !!! Nastavia sa FLAGS, aby k danemu DEVICE OBJECT mohli byt pripojene dalsie.
		DeviceObject->Flags&=~DO_DEVICE_INITIALIZING;
		DeviceObject->Flags|=DO_POWER_PAGABLE;
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] ADDED DEVICE !!!\n",DriverObject->DriverName));
	}
	else
	{
		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}

		KdPrint(("!!!!! DRIVER [%wZ] FAILED to ADD DEVICE !!!\n",DriverObject->DriverName));
	}

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER UNLOAD sa vola AZ ked su ukoncene vsetky IRP, pricom dalsie IRP po spusteni iniciovani UNLOAD procesu uz nedovoli WINDOWS odoslat.
// !!!!! To znamena, ze DRIVER UNLOAD NEMUSI kontrolovat ci este nebezia nejake IRP daneho DRIVER, pretoze ak by bezali, tak WINDOWS DRIVER UNLOAD NESPUSTI, az kym nebudu vsetky IRP ukoncene.
// !!!!! DRIVER UNLOAD NIE JE spusteny, az kym vsetky DEFFERED PROCEDURE CALLS, ktore spustil dany DRIVER NIE su UKONCENE.
void MyDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

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

	// !!!!! Ak sa prida FUNCTION ADD DEVICE, tak DRIVER NIE je mozne zastavit volanim COMMAND LINE COMMAND [sc stop MyHWDeviceFilter].
	DriverObject->DriverExtension->AddDevice=MyAddDevice;

	DriverObject->DriverUnload=MyDriverUnload;

	for (size_t Index=0;Index<ARRAYSIZE(DriverObject->MajorFunction);Index++)
	{
		if (Index!=IRP_MJ_PNP)
		{
			DriverObject->MajorFunction[Index]=MyGenericDispatchRoutine;
		}
		else
		{
			DriverObject->MajorFunction[Index]=DispatchRoutineForPNP;
		}
	}

	KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------