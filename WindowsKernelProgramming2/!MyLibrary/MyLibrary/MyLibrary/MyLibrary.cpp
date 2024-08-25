//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CFastMutexGlobal.h"
#include "Helpers\CLocker.h"
#include "SharedHeader.h"
#include "TestMemoryOperators.h"
#include "TestMutexGlobalGlobalObject.h"
#include "TestMutexGlobalGlobalPointer.h"
#include "TestMutexGlobalLocalObject.h"
#include "TestMutexGlobalLocalPointer.h"
#include "TestMutexGlobalPointer.h"
#include "TestMutexLocalObject.h"
#include "TestMutexLocalPointer.h"
#include "TestFastMutexGlobalGlobalObject.h"
#include "TestFastMutexGlobalGlobalPointer.h"
#include "TestFastMutexGlobalLocalObject.h"
#include "TestFastMutexGlobalLocalPointer.h"
#include "TestFastMutexGlobalPointer.h"
#include "TestFastMutexLocalObject.h"
#include "TestFastMutexLocalPointer.h"
#include "TestLookasideListGlobalObject.h"
#include "TestLookasideListGlobalPointer.h"
#include "TestExecutiveResourceGlobalGlobalObject.h"
#include "TestExecutiveResourceGlobalGlobalPointer.h"
#include "TestExecutiveResourceLocalObject.h"
#include "TestExecutiveResourceLocalPointer.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_MEMORY_OPERATORS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MEMORY_OPERATORS,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_MUTEX_GLOBAL_GLOBAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_GLOBAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_GLOBAL_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_GLOBAL_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_GLOBAL_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_MUTEX_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_GLOBAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_GLOBAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_LOOKASIDE_LIST_GLOBAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_LOOKASIDE_LIST_GLOBAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_LOOKASIDE_LIST_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_LOOKASIDE_LIST_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCE_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXECUTIVE_RESOURCE_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCE_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXECUTIVE_RESOURCE_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFastMutexGlobal												MutexForDispatchRoutineDeviceControl;
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
	
		if (Code==IOCTL_TEST_MEMORY_OPERATORS)
		{
			Status=TestMemoryOperators(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_MUTEX_GLOBAL_GLOBAL_OBJECT)
		{
			Status=TestMutexGlobalGlobalObject(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_MUTEX_GLOBAL_GLOBAL_POINTER)
		{
			Status=TestMutexGlobalGlobalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_MUTEX_GLOBAL_LOCAL_OBJECT)
		{
			Status=TestMutexGlobalLocalObject(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_MUTEX_GLOBAL_LOCAL_POINTER)
		{
			Status=TestMutexGlobalLocalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_MUTEX_GLOBAL_POINTER)
		{
			Status=TestMutexGlobalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_MUTEX_LOCAL_OBJECT)
		{
			Status=TestMutexLocalObject(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_MUTEX_LOCAL_POINTER)
		{
			Status=TestMutexLocalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_FAST_MUTEX_GLOBAL_GLOBAL_OBJECT)
		{
			Status=TestFastMutexGlobalGlobalObject(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_FAST_MUTEX_GLOBAL_GLOBAL_POINTER)
		{
			Status=TestFastMutexGlobalGlobalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_FAST_MUTEX_GLOBAL_LOCAL_OBJECT)
		{
			Status=TestFastMutexGlobalLocalObject(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_FAST_MUTEX_GLOBAL_LOCAL_POINTER)
		{
			Status=TestFastMutexGlobalLocalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_FAST_MUTEX_GLOBAL_POINTER)
		{
			Status=TestFastMutexGlobalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_FAST_MUTEX_LOCAL_OBJECT)
		{
			Status=TestFastMutexLocalObject(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_FAST_MUTEX_LOCAL_POINTER)
		{
			Status=TestFastMutexLocalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_LOOKASIDE_LIST_GLOBAL_OBJECT)
		{
			Status=TestLookasideListGlobalObject(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_LOOKASIDE_LIST_GLOBAL_POINTER)
		{
			Status=TestLookasideListGlobalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_OBJECT)
		{
			Status=TestExecutiveResourceGlobalGlobalObject(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_POINTER)
		{
			Status=TestExecutiveResourceGlobalGlobalPointer(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXECUTIVE_RESOURCE_LOCAL_OBJECT)
		{
			Status=TestExecutiveResourceLocalObject(DeviceObject,Irp);
		}
		else if (Code==IOCTL_TEST_EXECUTIVE_RESOURCE_LOCAL_POINTER)
		{
			Status=TestExecutiveResourceLocalPointer(DeviceObject,Irp);
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

	MutexForDispatchRoutineDeviceControl.Init();

	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	DriverObject->DriverUnload=FunctionDriverUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchRoutineDeviceControl;

	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	NTSTATUS													Status;
	PDEVICE_OBJECT												DeviceObject;

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
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------