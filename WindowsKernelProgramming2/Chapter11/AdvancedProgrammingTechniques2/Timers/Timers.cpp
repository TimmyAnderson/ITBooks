//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TIMERS_SET_ONESHOT CTL_CODE(TIMERS_DEVICE, TIMERS_SET_ONESHOT, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TIMERS_SET_PERIODIC CTL_CODE(TIMERS_DEVICE, TIMERS_SET_PERIODIC, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TIMERS_GET_RESOLUTION CTL_CODE(TIMERS_DEVICE, TIMERS_GET_RESOLUTION, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TIMERS_SET_HIRES CTL_CODE(TIMERS_DEVICE, TIMERS_SET_HIRES, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TIMERS_STOP CTL_CODE(TIMERS_DEVICE, TIMERS_STOP, METHOD_NEITHER, FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
KDPC															MyDPC;
KTIMER															MyNormalTimer;
PEX_TIMER														MyHighResolutionTimer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TimerDPCCallback(PKDPC, PVOID, PVOID, PVOID)
{
	LARGE_INTEGER												Counter=KeQueryPerformanceCounter(nullptr);
	int															IRQL=(int)KeGetCurrentIrql();
	
	DbgPrint("!!!!!!!!!! TIMER DPC - IRQL [%d] COUNTER [%lld].\n",IRQL,Counter.QuadPart);
}
//----------------------------------------------------------------------------------------------------------------------
void HighRessolutionCallback(PEX_TIMER, PVOID)
{
	LARGE_INTEGER												Counter=KeQueryPerformanceCounter(nullptr);
	int															IRQL=(int)KeGetCurrentIrql();

	DbgPrint("!!!!!!!!!! HIGH RESOLUTION TIMER DPC - IRQL [%d] COUNTER [%lld].\n",IRQL,Counter.QuadPart);
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
	ULONG														Information=0;
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	const auto&													Parameters=CurrentStackLocation->Parameters.DeviceIoControl;
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;

	if (Code==IOCTL_TIMERS_GET_RESOLUTION)
	{
		if (Parameters.OutputBufferLength>=sizeof(STimerResolution))
		{
			STimerResolution*									Data=(STimerResolution*)Irp->AssociatedIrp.SystemBuffer;

			ExQueryTimerResolution(&Data->MMaximum,&Data->MMinimum,&Data->MCurrent);

			Data->MIncrement=KeQueryTimeIncrement();

			KdPrint(("!!!!!!!!!! GET RESOLUTION - CURRENT [%lu] MINIMUM [%lu] MAXIMUM [%lu] INCREMENT [%lu].\n",Data->MCurrent,Data->MMinimum,Data->MMaximum,Data->MIncrement));

			Information=sizeof(*Data);

			Status=STATUS_SUCCESS;
		}
		else
		{
			Status=STATUS_BUFFER_TOO_SMALL;
		}
	}
	else if (Code==IOCTL_TIMERS_SET_ONESHOT)
	{
		if (Parameters.InputBufferLength>=sizeof(ULONG))
		{
			ULONG												RawInterval=(*(ULONG*)Irp->AssociatedIrp.SystemBuffer);

			KdPrint(("!!!!!!!!!! SETTING ONE SHOT TIMER - INTERVAL [%lu].\n",RawInterval));

			LARGE_INTEGER										Interval;

			Interval.QuadPart=(-10000LL*RawInterval);

			KeSetTimer(&MyNormalTimer,Interval,&MyDPC);

			Status=STATUS_SUCCESS;
		}
		else
		{
			Status=STATUS_BUFFER_TOO_SMALL;
		}
	}
	else if (Code==IOCTL_TIMERS_SET_PERIODIC)
	{
		if (Parameters.InputBufferLength>=sizeof(SPeriodicTimer))
		{
			SPeriodicTimer*										Data=(SPeriodicTimer*)Irp->AssociatedIrp.SystemBuffer;

			KdPrint(("!!!!!!!!!! SETTING PERIODIC TIMER - INTERVAL [%lu] PERIOD [%lu].\n",Data->MInterval,Data->MPeriod));

			LARGE_INTEGER										Interval;

			Interval.QuadPart=(-10000LL*Data->MInterval);

			KeSetTimerEx(&MyNormalTimer,Interval,Data->MPeriod,&MyDPC);

			Status=STATUS_SUCCESS;
		}
		else
		{
			Status=STATUS_BUFFER_TOO_SMALL;
		}
	}
	else if (Code==IOCTL_TIMERS_SET_HIRES)
	{
		if (Parameters.InputBufferLength>=sizeof(SPeriodicTimer))
		{
			SPeriodicTimer*										Data=(SPeriodicTimer*)Irp->AssociatedIrp.SystemBuffer;

			KdPrint(("!!!!!!!!!! SETTING HIGH RESOLUTION TIMER - INTERVAL [%lu] PERIOD [%lu].\n",Data->MInterval,Data->MPeriod));

			ExSetTimer(MyHighResolutionTimer,-10000LL*Data->MInterval,10000LL*Data->MPeriod,nullptr);

			Status=STATUS_SUCCESS;
		}
		else
		{
			Status=STATUS_BUFFER_TOO_SMALL;
		}
	}
	else if (Code==IOCTL_TIMERS_STOP)
	{
		KeCancelTimer(&MyNormalTimer);
		ExCancelTimer(MyHighResolutionTimer,nullptr);

		KdPrint(("!!!!!!!!!! RESETTING TIMERS.\n"));

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to RECOGNIZE CODE [%lu] !!!\n",DeviceObject->DriverObject->DriverName,Code));
		Status=STATUS_INVALID_DEVICE_REQUEST;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

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
	
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	KeCancelTimer(&MyNormalTimer);

	ExDeleteTimer(MyHighResolutionTimer,TRUE,TRUE,nullptr);

	IoDeleteSymbolicLink(&SymbolicLink);

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

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchRoutineDeviceControl;

	KeInitializeDpc(&MyDPC,TimerDPCCallback,nullptr);
	KeInitializeTimer(&MyNormalTimer);

	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	NTSTATUS													Status;
	PDEVICE_OBJECT												DeviceObject;

	bool														SymbolicLinkCreated=false;

	do
	{
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

		MyHighResolutionTimer=ExAllocateTimer(HighRessolutionCallback,nullptr,EX_TIMER_HIGH_RESOLUTION);

		if (MyHighResolutionTimer==nullptr)
		{
			Status=STATUS_UNSUCCESSFUL;
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
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------