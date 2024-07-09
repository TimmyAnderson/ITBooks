//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "SharedHeader.h"
#include "TestIrpProcessImmediately.h"
#include "TestIrpPassDownCopyStackLocation.h"
#include "TestIrpPassDownSkipStackLocation.h"
#include "TestIrpPassDownWithCompletionRoutine.h"
#include "TestIrpPassDownAsynchronousProcessing.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// DRIVER predstavuje NAJNIZSI DEVICE OBJECT v DEVICE OBJECT STACK.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_IRP_PROCESS_IMMEDIATELY CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PROCESS_IMMEDIATELY,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_IRP_PASS_DOWN_COPY_STACK_LOCATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PASS_DOWN_COPY_STACK_LOCATION,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_IRP_PASS_DOWN_SKIP_STACK_LOCATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PASS_DOWN_SKIP_STACK_LOCATION,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_IRP_PASS_DOWN_WITH_COMPLETION_ROUTINE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PASS_DOWN_WITH_COMPLETION_ROUTINE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_IRP_PASS_DOWN_ASYNCHRONOUS_PROCESSING CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PASS_DOWN_ASYNCHRONOUS_PROCESSING,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineCreate(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	Irp->IoStatus.Status=STATUS_SUCCESS;
	Irp->IoStatus.Information=0;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineClose(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	Irp->IoStatus.Status=STATUS_SUCCESS;
	Irp->IoStatus.Information=0;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineDeviceControl(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] STACK SIZE [%hhd] CURRENT LOCATION [%hhd] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName,Irp->StackCount,Irp->CurrentLocation));

	NTSTATUS													Status;
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
	
	if (Code==IOCTL_TEST_IRP_PROCESS_IMMEDIATELY)
	{
		Status=TestIrpProcessImmediately(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_IRP_PASS_DOWN_COPY_STACK_LOCATION)
	{
		Status=TestIrpPassDownCopyStackLocation(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_IRP_PASS_DOWN_SKIP_STACK_LOCATION)
	{
		Status=TestIrpPassDownSkipStackLocation(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_IRP_PASS_DOWN_WITH_COMPLETION_ROUTINE)
	{
		Status=TestIrpPassDownWithCompletionRoutine(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_IRP_PASS_DOWN_ASYNCHRONOUS_PROCESSING)
	{
		Status=TestIrpPassDownAsynchronousProcessing(DeviceObject,Irp);
	}
	else
	{
		Status=STATUS_INVALID_DEVICE_REQUEST;

		Irp->IoStatus.Status=Status;
		Irp->IoStatus.Information=0;

		IofCompleteRequest(Irp,IO_NO_INCREMENT);
	}

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] STACK SIZE [%hhd] CURRENT LOCATION [%hhd] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName,Irp->StackCount,Irp->CurrentLocation));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	UNICODE_STRING												SymbolicLink;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\DeviceObjectStacksLayer2");

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

	// !!! DEVICE NAME by mal mat PREFIX [\Device].
	RtlInitUnicodeString(&DeviceName,L"\\Device\\DeviceObjectStacksLayer2");

	PDEVICE_OBJECT												DeviceObject;

	NTSTATUS													Status1=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

	if (NT_SUCCESS(Status1)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status1));
		return(Status1);
	}

	UNICODE_STRING												SymbolicLink;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\DeviceObjectStacksLayer2");

	NTSTATUS													Status2=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

	if (NT_SUCCESS(Status2)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status2));

		IoDeleteDevice(DeviceObject);
		return(Status2);
	}

	KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------