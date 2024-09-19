//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CFastMutexGlobal.h"
#include "Helpers\CLocker.h"
#include "SharedHeader.h"
#include "TestKernelTimersLongTime.h"
#include "TestKernelTimersNotification.h"
#include "TestKernelTimersSynchronization.h"
#include "TestKernelTimersCancelBySetTimer.h"
#include "TestKernelTimersDPC.h"
#include "TestKernelTimersPeriodic.h"
#include "TestKernelTimersCoalescable.h"
#include "TestKernelTimersResolution.h"
#include "TestExtendedTimers.h"
#include "TestExtendedTimersDeleteWait.h"
#include "TestExtendedTimersDeleteCancel.h"
#include "TestExtendedTimersNotification.h"
#include "TestExtendedTimersSynchronization.h"
#include "TestExtendedTimersCancel.h"
#include "TestExtendedTimersNoWake.h"
#include "TestExtendedTimersPeriodic.h"
#include "TestIoTimers.h"
#include "TestSplayTrees.h"
#include "TestAvlTrees.h"
#include "TestSinglyLinkedLists.h"
#include "TestSinglyLinkedListsThreadSafe.h"
#include "TestSequencedSinglyLinkedLists.h"
#include "TestCallbackObjects.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_KERNEL_TIMERS_LONG_TIME CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_LONG_TIME,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_NOTIFICATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_NOTIFICATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_SYNCHRONIZATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_SYNCHRONIZATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_CANCEL_BY_SET_TIMER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_CANCEL_BY_SET_TIMER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_DPC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_DPC,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_PERIODIC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_PERIODIC,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_COALESCABLE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_COALESCABLE,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_RESOLUTION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_RESOLUTION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_DELETE_WAIT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_DELETE_WAIT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_DELETE_CANCEL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_DELETE_CANCEL,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_NOTIFICATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_NOTIFICATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_SYNCHRONIZATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_SYNCHRONIZATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_CANCEL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_CANCEL,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_NO_WAKE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_NO_WAKE,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_PERIODIC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_PERIODIC,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_IO_TIMERS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IO_TIMERS,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPLAY_TREES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPLAY_TREES,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_AVL_TREES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_AVL_TREES,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SINGLY_LINKED_LISTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SINGLY_LINKED_LISTS,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_1 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_1,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_2,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEQUENCED_SINGLY_LINKED_LISTS_1 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEQUENCED_SINGLY_LINKED_LISTS_1,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEQUENCED_SINGLY_LINKED_LISTS_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEQUENCED_SINGLY_LINKED_LISTS_2,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_CALLBACK_OBJECTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_CALLBACK_OBJECTS,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFastMutexGlobal												MutexForDispatchRoutineDeviceControl;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MyIoTimerRoutine(_DEVICE_OBJECT* DeviceObject, PVOID Context)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! EXECUTING IO TIMER CALLBACK FUNCTION [%s] !!!\n",FunctionName));
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
	// !!!!! Vykonava sa LOCK, aby DEVICE CONTROL ROUTINE NEMOHLA sa volat naraz viackrat, kedze niektore TESTS pristupuju ku GLOBAL VARIABLES a teda NESMU byt spustane PARALELNE.
	CLocker														Lock(MutexForDispatchRoutineDeviceControl);

	{
		UNREFERENCED_PARAMETER(DeviceObject);

		const char*												FunctionName=__FUNCTION__;

		KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

		NTSTATUS												Status;
		IO_STACK_LOCATION*										CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
		ULONG													Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
	
		if (Code==IOCTL_TEST_KERNEL_TIMERS_LONG_TIME)
		{
			Status=TestKernelTimersLongTime(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_KERNEL_TIMERS_NOTIFICATION)
		{
			Status=TestKernelTimersNotification(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_KERNEL_TIMERS_SYNCHRONIZATION)
		{
			Status=TestKernelTimersSynchronization(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_KERNEL_TIMERS_CANCEL_BY_SET_TIMER)
		{
			Status=TestKernelTimersCancelBySetTimer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_KERNEL_TIMERS_DPC)
		{
			Status=TestKernelTimersDPC(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_KERNEL_TIMERS_PERIODIC)
		{
			Status=TestKernelTimersPeriodic(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_KERNEL_TIMERS_COALESCABLE)
		{
			Status=TestKernelTimersCoalescable(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_KERNEL_TIMERS_RESOLUTION)
		{
			Status=TestKernelTimersResolution(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXTENDED_TIMERS)
		{
			Status=TestExtendedTimers(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXTENDED_TIMERS_DELETE_WAIT)
		{
			Status=TestExtendedTimersDeleteWait(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXTENDED_TIMERS_DELETE_CANCEL)
		{
			Status=TestExtendedTimersDeleteCancel(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXTENDED_TIMERS_NOTIFICATION)
		{
			Status=TestExtendedTimersNotification(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXTENDED_TIMERS_SYNCHRONIZATION)
		{
			Status=TestExtendedTimersSynchronization(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXTENDED_TIMERS_CANCEL)
		{
			Status=TestExtendedTimersCancel(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXTENDED_TIMERS_NO_WAKE)
		{
			Status=TestExtendedTimersNoWake(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXTENDED_TIMERS_PERIODIC)
		{
			Status=TestExtendedTimersPeriodic(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_IO_TIMERS)
		{
			Status=TestIoTimers(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_SPLAY_TREES)
		{
			Status=TestSplayTrees(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_AVL_TREES)
		{
			Status=TestAvlTrees(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_SINGLY_LINKED_LISTS)
		{
			Status=TestSinglyLinkedLists(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_1)
		{
			Status=TestSinglyLinkedListsThreadSafe(DeviceObject,Irp,20,true);
		}
		else if (Code==IOCTL_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_2)
		{
			Status=TestSinglyLinkedListsThreadSafe(DeviceObject,Irp,1000000,false);
		}
		else if (Code==IOCTL_TEST_SEQUENCED_SINGLY_LINKED_LISTS_1)
		{
			Status=TestSequencedSinglyLinkedLists(DeviceObject,Irp,20,true);
		}
		else if (Code==IOCTL_TEST_SEQUENCED_SINGLY_LINKED_LISTS_2)
		{
			Status=TestSequencedSinglyLinkedLists(DeviceObject,Irp,1000000,false);
		}
		else if (Code==IOCTL_TEST_CALLBACK_OBJECTS)
		{
			Status=TestCallbackObjects(DeviceObject,Irp);
		}
		else
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to RECOGNIZE CODE [%lu] !!!\n",DeviceObject->DriverObject->DriverName,Code));

			Status=CHelpers::CompleteIRP(Irp,STATUS_INVALID_DEVICE_REQUEST,0);
		}

		KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

		return(Status);
	}
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

	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	MutexForDispatchRoutineDeviceControl.Init();

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

		Status=IoInitializeTimer(DeviceObject,MyIoTimerRoutine,nullptr);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to INITIALIZE IO TIMER with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
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