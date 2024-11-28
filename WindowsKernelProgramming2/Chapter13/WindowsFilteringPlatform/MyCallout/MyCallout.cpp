//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tieto DEFINES musia byt vlozene, inak HEADER [fwpsk.h] vyhodi mnozstvo ERRORS.
#define NDIS_MINIPORT_DRIVER 1
#define NDIS630_MINIPORT 1
//----------------------------------------------------------------------------------------------------------------------
#include <fwpsk.h>
#include <fwpsk.h>
// !!!!! Tento HEADER MUSI byt vlozeny, aby MACRO [DEFINE_GUID()] vykonalo DEFINITION daneho GUID.
#include <initguid.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CFastMutexGlobal.h"
#include "Helpers\CLocker.h"
#include "Helpers\CSharedLocker.h"
#include "SharedHeader.h"
#include "CGlobals.h"
#include "SCalloutDriverRegistrationInfo.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CALLOUT DRIVERS MUSIA mat vlozenu LIBRARY [Fwpkclnt.lib].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_BLOCK_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,BLOCK_PROCESS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_PERMIT_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,PERMIT_PROCESS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CLEAR_PROCESSES CTL_CODE(FILE_DEVICE_UNKNOWN,CLEAR_PROCESSES,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CGlobals*														Globals=nullptr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS MyOnCalloutNotify(FWPS_CALLOUT_NOTIFY_TYPE NotifyType, const GUID* FilterKey, FWPS_FILTER* Filter)
{
	const char*													FunctionName=__FUNCTION__;

	UINT64														FilterID=Filter->filterId;
	UNICODE_STRING												FilterKeyString=RTL_CONSTANT_STRING(L"NO GUID");
	bool														FilterKeyConvertedToString=false;

	if (FilterKey!=nullptr)
	{
		NTSTATUS												LocalStatus=RtlStringFromGUID(*FilterKey,&FilterKeyString);

		if (NT_SUCCESS(LocalStatus)==true)
		{
			FilterKeyConvertedToString=true;
		}
		else
		{
			KdPrint(("!!!!! DRIVER FAILED to CONVERT GUID to STRING with ERROR CODE [%lX] !!!\n",LocalStatus));
		}
	}

	KdPrint(("!!!!! FUNCTION [%s] CALLED. NOTIFY TYPE [%d] FILTER KEY [%wZ] FILTER ID [%I64u].\n",FunctionName,NotifyType,FilterKeyString,FilterID));

	if (FilterKeyConvertedToString==true)
	{
		RtlFreeUnicodeString(&FilterKeyString);
	}

	NTSTATUS													Status;

	Status=STATUS_SUCCESS;

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
void MyOnCalloutClassify(const FWPS_INCOMING_VALUES* InFixedValues, const FWPS_INCOMING_METADATA_VALUES* InMetaValues, void* LayerData, const void* ClassifyContext, const FWPS_FILTER* Filter, UINT64 FlowContext, FWPS_CLASSIFY_OUT* ClassifyOut)
{
	UNREFERENCED_PARAMETER(InFixedValues);
	UNREFERENCED_PARAMETER(LayerData);
	UNREFERENCED_PARAMETER(ClassifyContext);
	UNREFERENCED_PARAMETER(Filter);
	UNREFERENCED_PARAMETER(FlowContext);

	if ((InMetaValues->currentMetadataValues & FWPS_METADATA_FIELD_PROCESS_ID)!=0)
	{
		const char*												FunctionName=__FUNCTION__;

		ULONG													PID=(ULONG)InMetaValues->processId;
		bool													Block=Globals->IsProcessBlocked(PID);

		if (Block==true)
		{
			ClassifyOut->actionType=FWP_ACTION_BLOCK;
			ClassifyOut->rights&=~FWPS_RIGHT_ACTION_WRITE;

			KdPrint(("!!!!! FUNCTION [%s] CALLED. PROCESS [%lu] was BLOCKED.\n",FunctionName,PID));
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineCreate(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineClose(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}

//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineDeviceControl(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	NTSTATUS													Status;
	ULONG_PTR													Information;
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;

	if (Code==IOCTL_BLOCK_PROCESS)
	{
		PVOID													InputBuffer=Irp->AssociatedIrp.SystemBuffer;
		ULONG													InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;

		if (InputBufferLength>=sizeof(ULONG))
		{
			ULONG*												PID=(ULONG*)InputBuffer;

			Status=Globals->AddProcess(*PID);

			if (NT_SUCCESS(Status)==true)
			{
				KdPrint(("!!!!! DRIVER [%wZ] BLOCKED PROCESS [%lu] !!!\n",DeviceObject->DriverObject->DriverName,*PID));
			}
			else
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to BLOCK PROCESS [%lu] with ERROR CODE [%lX] !!!\n",DeviceObject->DriverObject->DriverName,*PID,Status));
			}

			Information=0;
		}
		else
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			Information=0;
		}
	}
	else if (Code==IOCTL_PERMIT_PROCESS)
	{
		PVOID													InputBuffer=Irp->AssociatedIrp.SystemBuffer;
		ULONG													InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;

		if (InputBufferLength>=sizeof(ULONG))
		{
			ULONG*												PID=(ULONG*)InputBuffer;

			Status=Globals->DeleteProcess(*PID);

			if (NT_SUCCESS(Status)==true)
			{
				KdPrint(("!!!!! DRIVER [%wZ] PERMITTED PROCESS [%lu] !!!\n",DeviceObject->DriverObject->DriverName,*PID));
			}
			else
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to PERMIT PROCESS [%lu] with ERROR CODE [%lX] !!!\n",DeviceObject->DriverObject->DriverName,*PID,Status));
			}

			Information=0;
		}
		else
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			Information=0;
		}
	}
	else if (Code==IOCTL_CLEAR_PROCESSES)
	{
		Status=Globals->ClearProcesses();

		if (NT_SUCCESS(Status)==true)
		{
			KdPrint(("!!!!! DRIVER [%wZ] PERMITTED ALL PROCESSES !!!\n",DeviceObject->DriverObject->DriverName));
		}
		else
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to PERMIT ALL PROCESSES with ERROR CODE [%lX] !!!\n",DeviceObject->DriverObject->DriverName,Status));
		}
	}
	else
	{
		Status=STATUS_INVALID_DEVICE_REQUEST;
		Information=0;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,0);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

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

	UNICODE_STRING												SymbolicLink;

	const GUID*													Guids[]=
	{
		&GUID_MY_CALLOUT_DRIVER_BLOCK_V4,
		&GUID_MY_CALLOUT_DRIVER_BLOCK_V6,
		&GUID_MY_CALLOUT_DRIVER_BLOCK_UDP_V4,
		&GUID_MY_CALLOUT_DRIVER_BLOCK_UDP_V6,
	};

	for(const GUID* Guid : Guids)
	{
		// !!! Vykona sa UNREGISTER vsetkych zaregistrovanych CALLOUT DRIVERS.
		FwpsCalloutUnregisterByKey(Guid);
	}

	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(DriverObject->DeviceObject);

	delete(Globals);
	Globals=nullptr;

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

	NTSTATUS													Status;

	DriverObject->DriverUnload=FunctionDriverUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchRoutineDeviceControl;

	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	PDEVICE_OBJECT												DeviceObject=nullptr;

	bool														LockInitialized=false;
	bool														SymbolicLinkCreated=false;

	SCalloutDriverRegistrationInfo								CalloutDriverRegistrationInfoItems[]=
	{
		SCalloutDriverRegistrationInfo(&GUID_MY_CALLOUT_DRIVER_BLOCK_V4,L"BLOCK IPv4"),
		SCalloutDriverRegistrationInfo(&GUID_MY_CALLOUT_DRIVER_BLOCK_V6,L"BLOCK IPv6"),
		SCalloutDriverRegistrationInfo(&GUID_MY_CALLOUT_DRIVER_BLOCK_UDP_V4,L"BLOCK UDP IPv4"),
		SCalloutDriverRegistrationInfo(&GUID_MY_CALLOUT_DRIVER_BLOCK_UDP_V6,L"BLOCK UDP IPv4")
	};

	do
	{
		Globals=new (EPoolFlags::E_POOL_FLAG_NON_PAGED) CGlobals;

		if (Globals==nullptr)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to ALLOCATE MEMORY for GLOBALS !!!\n",DriverObject->DriverName));
			Status=STATUS_NO_MEMORY;
			break;
		}

		LockInitialized=true;

		Status=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK [%wZ] with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,SymbolicLink,Status));
			break;
		}

		SymbolicLinkCreated=true;

		for(SCalloutDriverRegistrationInfo& CalloutDriverRegistrationInfoItem : CalloutDriverRegistrationInfoItems)
		{
			FWPS_CALLOUT										Callout{};

			Callout.calloutKey=*CalloutDriverRegistrationInfoItem.MCalloutDriverGuid;
			Callout.notifyFn=MyOnCalloutNotify;
			Callout.classifyFn=MyOnCalloutClassify;

			Status=FwpsCalloutRegister(DriverObject,&Callout,nullptr);

			if (NT_SUCCESS(Status)==true)
			{
				CalloutDriverRegistrationInfoItem.MIsRegistered=true;
			}
			else
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER CALLOUT DRIVER [%S] with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,CalloutDriverRegistrationInfoItem.MCalloutDriverName,Status));
				break;
			}
		}

		if (NT_SUCCESS(Status)==false)
		{
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

		for(const SCalloutDriverRegistrationInfo& CalloutDriverRegistrationInfoItem : CalloutDriverRegistrationInfoItems)
		{
			if (CalloutDriverRegistrationInfoItem.MIsRegistered==true)
			{
				FwpsCalloutUnregisterByKey(CalloutDriverRegistrationInfoItem.MCalloutDriverGuid);
			}
		}

		if (SymbolicLinkCreated==true)
		{
			IoDeleteSymbolicLink(&SymbolicLink);
			SymbolicLinkCreated=false;
		}

		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}

		if (LockInitialized==true)
		{
			delete(Globals);
			Globals=nullptr;
		}
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------