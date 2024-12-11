//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <wdf.h>
// !!!!! Tento HEADER MUSI byt vlozeny, aby MACRO [DEFINE_GUID()] vykonalo DEFINITION daneho GUID.
#include <initguid.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
#include "SThreadData.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PREPROCESSOR DEFINITION [IS_KERNEL] must be defined.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_BOOSTER_SET_PRIORITY CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_BOOSTER_SET_PRIORITY,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void BoosterDeviceControl(WDFQUEUE Queue, WDFREQUEST Request, size_t OutputBufferLength, size_t InputBufferLength, ULONG IoControlCode)
{
	UNREFERENCED_PARAMETER(Queue);
	UNREFERENCED_PARAMETER(InputBufferLength);
	UNREFERENCED_PARAMETER(OutputBufferLength);

	KdPrint(("!!!!! DRIVER is EXECUTING DEVICE CONTROL HANDLER !!!\n"));

	NTSTATUS													Status=STATUS_INVALID_DEVICE_REQUEST;
	ULONG														Info=0;

	switch(IoControlCode)
	{
		case IOCTL_BOOSTER_SET_PRIORITY:
		{
			SThreadData*										Data;

			Status=WdfRequestRetrieveInputBuffer(Request,sizeof(SThreadData),(PVOID*)&Data,nullptr);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!! DRIVER FAILED to RETRIEVE INPUT BUFFER with ERROR CODE [%lX] !!!\n",Status));
				break;
			}

			if (Data->MPriority<1 || Data->MPriority>31)
			{
				Status=STATUS_INVALID_PARAMETER;
				break;
			}

			PKTHREAD											Thread;
			HANDLE												ThreadID=ULongToHandle(Data->MThreadID);

			Status=PsLookupThreadByThreadId(ThreadID,&Thread);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!! DRIVER FAILED to GET THREAD by THREAD ID with ERROR CODE [%lX] !!!\n",Status));
				break;
			}

			// !!! Nastavi sa THREAD PRIORITY.
			KPRIORITY											OldPriority=KeSetPriorityThread(Thread,Data->MPriority);

			KdPrint(("!!!!! DRIVER SET THREAD ID [%lu] to PRIORITY [%d] !!! OLD PRIORITY [%ld].\n",Data->MThreadID,Data->MPriority,OldPriority));

			ObDereferenceObject(Thread);

			Info=sizeof(SThreadData);
		}
		break;
	}

	WdfRequestCompleteWithInformation(Request,Status,Info);

	KdPrint(("!!!!! DRIVER is EXECUTIED DEVICE CONTROL HANDLER with CODE [%lX] !!!\n",Status));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS BoosterDeviceAdd(WDFDRIVER Driver, PWDFDEVICE_INIT DeviceInit)
{
	UNREFERENCED_PARAMETER(Driver);

	KdPrint(("!!!!! DRIVER is ADDING DEVICE !!!\n"));

	NTSTATUS													Status;

	do
	{
		WDFDEVICE													Device;

		// !!! Vytvori sa DEVICE OBJCT.
		Status=WdfDeviceCreate(&DeviceInit,WDF_NO_OBJECT_ATTRIBUTES,&Device);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",Status));
			break;
		}

		// !!! Vytvori sa DEVICE OBJCT INTERFACE.
		Status=WdfDeviceCreateDeviceInterface(Device,&GUID_BOOST_INTERFACE,nullptr);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER FAILED to CREATE DEVICE INTERFACE with ERROR CODE [%lX] !!!\n",Status));
			break;
		}

		WDF_IO_QUEUE_CONFIG										Config;

		WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&Config,WdfIoQueueDispatchParallel);

		Config.EvtIoDeviceControl=BoosterDeviceControl;

		WDFQUEUE												Queue;

		// !!! Vytvori sa DEVICE OBJECT QUEUE.
		Status=WdfIoQueueCreate(Device,&Config,WDF_NO_OBJECT_ATTRIBUTES,&Queue);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER FAILED to CREATE DEVICE OBJECT QUEUE with ERROR CODE [%lX] !!!\n",Status));
			break;
		}
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER ADDED DEVICE !!!\n"));
	}
	else
	{
		KdPrint(("!!!!! DRIVER FAILED to ADD DEVICE !!!\n"));
	}

	return(Status);
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

	// !!! CONFIGURATION pre DRIVER OBJECT.
	WDF_DRIVER_CONFIG											Config;

	// !!! Inicializuje sa CONFIGURATION pre DRIVER OBJECT.
	WDF_DRIVER_CONFIG_INIT(&Config,BoosterDeviceAdd);

	// !!! Priradi sa CUSTOM DRIVER UNLOAD FUNCTION.
	Config.EvtDriverUnload=MyFunctionDriverUnload;

	Status=WdfDriverCreate(DriverObject,RegistryPath,WDF_NO_OBJECT_ATTRIBUTES,&Config,WDF_NO_HANDLE);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to START !!!\n",DriverObject->DriverName));
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------