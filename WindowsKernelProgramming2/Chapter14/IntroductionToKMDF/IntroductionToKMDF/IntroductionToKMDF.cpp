//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <wdf.h>
// !!!!! Tento HEADER MUSI byt vlozeny, aby MACRO [DEFINE_GUID()] vykonalo DEFINITION daneho GUID.
#include <initguid.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MyFunctionRead(WDFQUEUE Queue, WDFREQUEST Request, size_t Length)
{
	UNREFERENCED_PARAMETER(Queue);
	UNREFERENCED_PARAMETER(Length);

	NTSTATUS													Status;
	ULONG_PTR													Info=0;
	
	// !!!!! Simuluje data nacitane z HW DEVICE.
	wchar_t														DataReadFromHWDevice[]=L"Timmy READ.";
	constexpr size_t											DataReadFromHWDeviceSize=sizeof(DataReadFromHWDevice);

	PVOID														ReadBuffer;

	// !!! Ziska sa POINTER na OUTPUT BUFFER.
	Status=WdfRequestRetrieveOutputBuffer(Request,DataReadFromHWDeviceSize,(PVOID*)&ReadBuffer,nullptr);

	if (NT_SUCCESS(Status)==true)
	{
		// !!! Skopiruju sa data nacitane z HW DEVICE do READ BUFFER.
		RtlCopyMemory(ReadBuffer,DataReadFromHWDevice,DataReadFromHWDeviceSize);

		Info=DataReadFromHWDeviceSize;

		KdPrint(("!!!!!!!!!! READ DISPATCH ROUTINE - DATA SIZE [%I64u] DATA READ [%S] !!!\n",Info,DataReadFromHWDevice));
	}
	else
	{
		KdPrint(("!!!!! DRIVER FAILED to GET OUTPUT BUFFER with ERROR CODE [%lX] !!!\n",Status));
	}

	WdfRequestCompleteWithInformation(Request,Status,Info);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MyFunctionWrite(WDFQUEUE Queue, WDFREQUEST Request, size_t Length)
{
	UNREFERENCED_PARAMETER(Queue);
	UNREFERENCED_PARAMETER(Length);

	NTSTATUS													Status=STATUS_INVALID_DEVICE_REQUEST;
	ULONG_PTR													Info=0;
	
	constexpr size_t											MinDataWriteToHWDeviceSize=sizeof(wchar_t);

	PVOID														WriteBuffer;
	size_t														WriteBufferSize;

	// !!! Ziska sa POINTER na INPUT BUFFER.
	Status=WdfRequestRetrieveInputBuffer(Request,MinDataWriteToHWDeviceSize,(PVOID*)&WriteBuffer,&WriteBufferSize);

	if (NT_SUCCESS(Status)==true)
	{
		Info=WriteBufferSize;

		const wchar_t*											TypedWriteBuffer=reinterpret_cast<const wchar_t*>(WriteBuffer);

		KdPrint(("!!!!!!!!!! WRITE DISPATCH ROUTINE - DATA SIZE [%I64u] DATA WRITTEN [%S] !!!\n",Info,TypedWriteBuffer));
	}
	else
	{
		KdPrint(("!!!!! DRIVER FAILED to GET INTPUT BUFFER with ERROR CODE [%lX] !!!\n",Status));
	}

	WdfRequestCompleteWithInformation(Request,Status,Info);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS MyFunctionDeviceAdd(WDFDRIVER Driver, PWDFDEVICE_INIT DeviceInit)
{
	PDRIVER_OBJECT												DriverObject=WdfDriverWdmGetDriverObject(Driver);

	KdPrint(("!!!!! DRIVER [%wZ] is ADDING DEVICE !!!\n",DriverObject->DriverName));

	NTSTATUS													Status;

	do
	{
		WDFDEVICE													Device;

		// !!! Vytvori sa DEVICE OBJCT.
		Status=WdfDeviceCreate(&DeviceInit,WDF_NO_OBJECT_ATTRIBUTES,&Device);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		// !!! Vytvori sa DEVICE OBJCT INTERFACE.
		Status=WdfDeviceCreateDeviceInterface(Device,&GUID_INTRODUCTION_TO_KDF_INTERFACE,nullptr);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE INTERFACE with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		WDF_IO_QUEUE_CONFIG										Config;

		WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&Config,WdfIoQueueDispatchParallel);

		Config.EvtIoRead=MyFunctionRead;
		Config.EvtIoWrite=MyFunctionWrite;

		WDFQUEUE												Queue;

		// !!! Vytvori sa DEVICE OBJECT QUEUE.
		Status=WdfIoQueueCreate(Device,&Config,WDF_NO_OBJECT_ATTRIBUTES,&Queue);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT QUEUE with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] ADDED DEVICE !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to ADD DEVICE !!!\n",DriverObject->DriverName));
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MyFunctionCleanup(WDFOBJECT Object)
{
	UNREFERENCED_PARAMETER(Object);

	KdPrint(("!!!!! DRIVER OBJECT CLEANED UP !!!\n"));
}
//----------------------------------------------------------------------------------------------------------------------
void MyFunctionDestroy(WDFOBJECT Object)
{
	UNREFERENCED_PARAMETER(Object);

	KdPrint(("!!!!! DRIVER OBJECT DELETED !!!\n"));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MyFunctionDriverUnload(WDFDRIVER Driver)
{
	PDRIVER_OBJECT												DriverObject=WdfDriverWdmGetDriverObject(Driver);

	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	NTSTATUS													Status;
	WDF_OBJECT_ATTRIBUTES										Attributes;

	WDF_OBJECT_ATTRIBUTES_INIT(&Attributes);

	Attributes.EvtCleanupCallback=MyFunctionCleanup;
	Attributes.EvtDestroyCallback=MyFunctionDestroy;

	// !!! CONFIGURATION pre DRIVER OBJECT.
	WDF_DRIVER_CONFIG											Config;

	// !!! Inicializuje sa CONFIGURATION pre DRIVER OBJECT.
	WDF_DRIVER_CONFIG_INIT(&Config,MyFunctionDeviceAdd);

	// !!! Priradi sa CUSTOM DRIVER UNLOAD FUNCTION.
	Config.EvtDriverUnload=MyFunctionDriverUnload;

	Status=WdfDriverCreate(DriverObject,RegistryPath,&Attributes,&Config,WDF_NO_HANDLE);

	if (NT_SUCCESS(Status)==true)
	{
		// !!!!! DEVICE OBJECT sa v tejto FUNCTION NEVYTVARA, hoci sa jedna no NON-PLUG AND PLAY DRIVER. Automaticke vytvorenie DEVICE OBJECT sa dosiahne pomocou nastavenia vo FILE [.inf].

		KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to START !!!\n",DriverObject->DriverName));
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------