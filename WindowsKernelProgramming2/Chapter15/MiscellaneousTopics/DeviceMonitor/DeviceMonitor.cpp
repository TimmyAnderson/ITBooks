//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
#include "SDeviceExtension.h"
#include "CDevMonManager.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CDevMonManager													Manager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER kvoli jednoduchosti NEMA implementovany REMOVE LOCK. Implementacia REMOVE LOCK je v DRIVER [MyHWDeviceFilter].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER pekne funguje pre DEVICE [\device\procexp152] a DEVICE [\device\keyboardclass0].
// !!!!! DRIVER sa vsak dostal do pravdepodobne DEADLOCK pri pokuse o spravenie FILTER DEVICE OBJECT nad DEVICE [\device\CdRom0]. DEADLOCK sa spravil pri volani FUNCTION [IoGetDeviceObjectPointer()], ktora sa NIKDY NEVRATILA. Je mozne, ze problem je v tom, ze DEVICE NIE je MOUNTED a pri pokuse o MOUNT dojde k DEADLOCK, alebo niecomu podobnemu.
// !!!!! DRIVER vykonal BUG CHECK pri pokuse o pripojenie k DEVICE [\device\HarddiskVolume2]. Dovodom moze byt, ze DEVICE OBJECT je BOOT DEVICE a je PRAVDEPODOBNE na PAGEABLE PATH, kedy DRIVER participuje na PAGING, kedy su definovane daleko restriktivnejsie podmienky, ako napriklad nemoznost volat FUNCTION [IoCallDriver()] pre IRQL [IRQL>APC_LEVEL]. A tuto podmienku tento DRIVER nesplna.
// !!!!! DRIVER naopak FUNGOVAL pri pripojeni k DEVICE [\device\HarddiskVolume1] a k DEVICE [\device\HarddiskVolume3], ktore NIE su BOOT DEVICES a ASI NIE su na PAGEABLE PATH.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_DEVMON_ADD_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_DEVMON_ADD_DEVICE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DEVMON_REMOVE_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_DEVMON_REMOVE_DEVICE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DEVMON_REMOVE_ALL_DEVICES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_DEVMON_REMOVE_ALL_DEVICES,METHOD_BUFFERED,FILE_ANY_ACCESS)
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
NTSTATUS DevMonDeviceControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	const ULONG													MAX_BUFFER_SIZE=512;

	NTSTATUS													Status;
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;

	if (Code==IOCTL_DEVMON_ADD_DEVICE)
	{
		WCHAR*													Buffer=(WCHAR*)Irp->AssociatedIrp.SystemBuffer;
		ULONG													BufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;

		if (Buffer!=nullptr && BufferLength<=MAX_BUFFER_SIZE)
		{
			Buffer[BufferLength/sizeof(WCHAR)-1]=L'\0';

			Status=Manager.AddDevice(Buffer);
		}
		else
		{
			Status=STATUS_INVALID_BUFFER_SIZE;
		}
	}
	else if (Code==IOCTL_DEVMON_REMOVE_DEVICE)
	{
		WCHAR*													Buffer=(WCHAR*)Irp->AssociatedIrp.SystemBuffer;
		ULONG													BufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;

		if (Buffer!=nullptr && BufferLength<=MAX_BUFFER_SIZE)
		{
			Buffer[BufferLength/sizeof(WCHAR)-1]=L'\0';

			bool												Removed=Manager.RemoveDevice(Buffer);

			if (Removed==true)
			{
				Status=STATUS_SUCCESS;
			}
			else
			{
				Status=STATUS_NOT_FOUND;
			}
		}
		else
		{
			Status=STATUS_INVALID_BUFFER_SIZE;
		}
	}
	else if (Code==IOCTL_DEVMON_REMOVE_ALL_DEVICES)
	{
		Manager.RemoveAllDevices();

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to RECOGNIZE CODE [%lu] !!!\n",DeviceObject->DriverObject->DriverName,Code));

		Status=STATUS_INVALID_DEVICE_REQUEST;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,0);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS HandleFilterFunction(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	const PDEVICE_OBJECT										FilterDeviceObject=Manager.GetFilterDeviceObject();

	// !!!!! Ak je INTERRUPT REQUEST PACKET urceny priamo pre FILTER DEVICE OBJECT a nie pre DEVICE OBJECT na ktorym sa FILTER DEVICE OBJECT nachadza, znamena to, ze sa jedna o INTERRUPT REQUEST PACKET na ADD/REMOVE/CLEAR DEVICE OBJECTS nad ktorymi ma byt FILTER DEVICE OBJECT aplikovany.
	if (DeviceObject==FilterDeviceObject)
	{
		NTSTATUS												Status;
		PIO_STACK_LOCATION										CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

		if (CurrentStackLocation->MajorFunction==IRP_MJ_CREATE)
		{
			Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);
		}
		else if (CurrentStackLocation->MajorFunction==IRP_MJ_CLOSE)
		{
			Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);
		}
		else if (CurrentStackLocation->MajorFunction==IRP_MJ_DEVICE_CONTROL)
		{
			Status=DevMonDeviceControl(DeviceObject,Irp);
		}
		else
		{
			Status=CHelpers::CompleteIRP(Irp,STATUS_INVALID_DEVICE_REQUEST,0);
		}

		return(Status);
	}
	// !!!!! INTERRUPT REQUEST PACKET je urceny pre TARGET DEVICE OBJECT nad ktorym sa nachadza FILTER DEVICE OBJECT.
	else
	{
		SDeviceExtension*										DeviceExtension=(SDeviceExtension*)DeviceObject->DeviceExtension;
		PIO_STACK_LOCATION										Stack=IoGetCurrentIrpStackLocation(Irp);
		PETHREAD												Thread=Irp->Tail.Overlay.Thread;
		HANDLE													ProcessID=nullptr;
		HANDLE													ThreadID=nullptr;

		if (Thread!=nullptr)
		{
			ProcessID=PsGetThreadProcessId(Thread);
			ThreadID=PsGetThreadId(Thread);
		}

		UNICODE_STRING&											DriverName=DeviceExtension->MLowerDeviceObject->DriverObject->DriverName;
		ULONG													ProcessIDNumber=HandleToULong(ProcessID);
		ULONG													ThreadIDNumber=HandleToULong(ThreadID);
		UCHAR													MajorFunction=Stack->MajorFunction;
		PCSTR													MajorFunctionName=MajorFunctionToString(MajorFunction);

		KdPrint(("!!!!!!!!!! DRIVER [%wZ] PID [%lu] TID [%lu] MAJOR FUNCTION CODE [%hhu] MAJOR FUNCTION NAME [%s] !!!\n",DriverName,ProcessIDNumber,ThreadIDNumber,MajorFunction,MajorFunctionName));

		// !!! Pripravi sa INTERRUPT REQUEST PACKETS pre DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK.
		IoSkipCurrentIrpStackLocation(Irp);

		NTSTATUS												Status=IoCallDriver(DeviceExtension->MLowerDeviceObject,Irp);

		return(Status);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
NTSTATUS FilterAddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT PhysicalDeviceObject)
{
	PDEVICE_OBJECT												DeviceObject;
	NTSTATUS													Status=IoCreateDevice(DriverObject,sizeof(SDeviceExtension),nullptr,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
		return(Status);
	}

	SDeviceExtension*											DeviceExtension=(SDeviceExtension*)DeviceObject->DeviceExtension;

	Status=IoAttachDeviceToDeviceStackSafe(DeviceObject,PhysicalDeviceObject,&DeviceExtension->MLowerDeviceObject);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to ATTACH DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));

		IoDeleteDevice(DeviceObject);

		return(Status);
	}

	DeviceObject->Flags|=(DeviceExtension->MLowerDeviceObject->Flags & (DO_BUFFERED_IO | DO_DIRECT_IO));
	DeviceObject->DeviceType=DeviceExtension->MLowerDeviceObject->DeviceType;

	DeviceObject->Flags&=~DO_DEVICE_INITIALIZING;
	DeviceObject->Flags|=DO_POWER_PAGABLE;


	return(Status);
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER UNLOAD sa vola AZ ked su ukoncene vsetky IRP, pricom dalsie IRP po spusteni iniciovani UNLOAD procesu uz nedovoli WINDOWS odoslat.
// !!!!! To znamena, ze DRIVER UNLOAD NEMUSI kontrolovat ci este nebezia nejake IRP daneho DRIVER, pretoze ak by bezali, tak WINDOWS DRIVER UNLOAD NESPUSTI, az kym nebudu vsetky IRP ukoncene.
// !!!!! DRIVER UNLOAD NIE JE spusteny, az kym vsetky DEFFERED PROCEDURE CALLS, ktore spustil dany DRIVER NIE su UKONCENE.
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(DriverObject->DeviceObject);

	// !!!!! FUNCTION vykona DETACH a DELETE vsetkych FILTER DEVICE OBJECTS, ktore su este stale pripojene.
	Manager.RemoveAllDevices();

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

	NTSTATUS													Status=STATUS_SUCCESS;
	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	PDEVICE_OBJECT												DeviceObject;

	Status=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,TRUE,&DeviceObject);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
		return(Status);
	}

	Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK [%wZ] with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,SymbolicLink,Status));

		IoDeleteDevice(DeviceObject);

		return(Status);
	}

	DriverObject->DriverUnload=FunctionDriverUnload;

	for(PDRIVER_DISPATCH& Function : DriverObject->MajorFunction)
	{
		Function=HandleFilterFunction;
	}

	Manager.SetFilterDeviceObject(DeviceObject);

	Manager.Init(DriverObject);

	KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------