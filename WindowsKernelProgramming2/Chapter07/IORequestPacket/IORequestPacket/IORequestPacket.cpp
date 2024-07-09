//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
#include "TestDebugIrp.h"
#include "DeviceControlGetStatus.h"
#include "DeviceControlClearStatus.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER implementuje functionalitu ZERO DRIVER v knihe.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define MY_DRIVER_NAME L"IORequestPacket"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_DEBUG_IRP CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_DEBUG_IRP,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_GET_STATUS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_GET_STATUS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CLEAR_STATUS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_CLEAR_STATUS,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
volatile alignas(sizeof(LONG64)) LONG64						TotalReadBytes=0;
volatile alignas(sizeof(LONG64)) LONG64						TotalWriteBytes=0;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineCreate(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineClose(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineRead(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													NumberOfBytesRead=0;

	PIO_STACK_LOCATION											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

	// !!!!! Simuluje data nacitane z HW DEVICE.
	wchar_t														DataReadFromHWDevice[]=L"Timmy READ.";
	constexpr size_t											DataReadFromHWDeviceSize=sizeof(DataReadFromHWDevice);

	do
	{
		ULONG													ReadBufferSize=CurrentStackLocation->Parameters.Read.Length;

		if (ReadBufferSize<DataReadFromHWDeviceSize)
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			break;
		}

		// !!!!! Vykona sa mapovanie LIST STRUCTURES [MDL] do KERNEL MODE SYSTEM ADDRESS SPACE.
		PVOID													ReadBuffer=MmGetSystemAddressForMdlSafe(Irp->MdlAddress,MM_PAGE_PRIORITY::NormalPagePriority);

		if (ReadBuffer==nullptr)
		{
			KdPrint(("!!!!!!!!!! READ DISPATCH ROUTINE [%s] FAILED to MAP MDL to KERNEL MODE SYSTEM ADDRESS SPACE !!!\n",FunctionName));

			Status=STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		// !!! Skopiruju sa data nacitane z HW DEVICE do READ BUFFER.
		RtlCopyMemory(ReadBuffer,DataReadFromHWDevice,DataReadFromHWDeviceSize);

		NumberOfBytesRead=DataReadFromHWDeviceSize;

		KdPrint(("!!!!!!!!!! READ DISPATCH ROUTINE [%s] - DATA READ [%S] BYTES READ [%I64u] !!!\n",FunctionName,DataReadFromHWDevice,NumberOfBytesRead));

		InterlockedAdd64(&TotalReadBytes,DataReadFromHWDeviceSize);

		Status=STATUS_SUCCESS;
	}
	while(false);

	CHelpers::CompleteIRP(Irp,Status,NumberOfBytesRead);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineWrite(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													NumberOfBytesWritten=0;

	PIO_STACK_LOCATION											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

	constexpr size_t											MinDataWriteToHWDeviceSize=sizeof(wchar_t);

	do
	{
		ULONG													WriteBufferSize=CurrentStackLocation->Parameters.Write.Length;

		if (WriteBufferSize<MinDataWriteToHWDeviceSize)
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			break;
		}

		// !!!!! Vykona sa mapovanie LIST STRUCTURES [MDL] do KERNEL MODE SYSTEM ADDRESS SPACE.
		PVOID													WriteBuffer=MmGetSystemAddressForMdlSafe(Irp->MdlAddress,MM_PAGE_PRIORITY::NormalPagePriority);

		if (WriteBuffer==nullptr)
		{
			KdPrint(("!!!!!!!!!! WRITE DISPATCH ROUTINE [%s] FAILED to MAP MDL to KERNEL MODE SYSTEM ADDRESS SPACE !!!\n",FunctionName));

			Status=STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		const wchar_t*											TypedWriteBuffer=reinterpret_cast<const wchar_t*>(WriteBuffer);

		NumberOfBytesWritten=WriteBufferSize;

		InterlockedAdd64(&TotalWriteBytes,WriteBufferSize);

		KdPrint(("!!!!!!!!!! WRITE DISPATCH ROUTINE [%s] - DATA WRITTEN [%S] BYTES WRITTEN [%I64u] !!!\n",FunctionName,TypedWriteBuffer,NumberOfBytesWritten));

		Status=STATUS_SUCCESS;
	}
	while(false);

	CHelpers::CompleteIRP(Irp,Status,NumberOfBytesWritten);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineDeviceControl(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status;
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
	
	if (Code==IOCTL_TEST_DEBUG_IRP)
	{
		Status=TestDebugIrp(DeviceObject,Irp);
	}
	else if (Code==IOCTL_GET_STATUS)
	{
		Status=DeviceControlGetStatus(DeviceObject,Irp,TotalReadBytes,TotalWriteBytes);
	}
	else if (Code==IOCTL_CLEAR_STATUS)
	{
		Status=DeviceControlClearStatus(DeviceObject,Irp,TotalReadBytes,TotalWriteBytes);
	}
	else
	{
		Status=CHelpers::CompleteIRP(Irp,STATUS_INVALID_DEVICE_REQUEST,0);
	}

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
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

	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	DriverObject->DriverUnload=FunctionDriverUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchRoutineDeviceControl;
	DriverObject->MajorFunction[IRP_MJ_READ]=DispatchRoutineRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE]=DispatchRoutineWrite;

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

		// !!!!! DEVICE OBJECT sa nastavi do DIRECT IO MODE.
		DeviceObject->Flags|=DO_DIRECT_IO;

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