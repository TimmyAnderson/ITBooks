//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineCreate(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	Irp->IoStatus.Status=STATUS_SUCCESS;
	Irp->IoStatus.Information=0;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineClose(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	Irp->IoStatus.Status=STATUS_SUCCESS;
	Irp->IoStatus.Information=0;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(STATUS_SUCCESS);
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
		// !!!!! Vykona sa mapovanie LIST STRUCTURES [MDL] do KERNEL MODE SYSTEM ADDRESS SPACE.
		PVOID													ReadBuffer=MmGetSystemAddressForMdlSafe(Irp->MdlAddress,MM_PAGE_PRIORITY::NormalPagePriority);

		if (ReadBuffer==nullptr)
		{
			KdPrint(("!!!!!!!!!! READ DISPATCH ROUTINE [%s] FAILED to MAP MDL to KERNEL MODE SYSTEM ADDRESS SPACE !!!\n",FunctionName));

			Status=STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		ULONG													ReadBufferSize=CurrentStackLocation->Parameters.Read.Length;

		KdPrint(("!!!!!!!!!! READ DISPATCH ROUTINE [%s] - BUFFER [%p] BUFFER SIZE [%lu] !!!\n",FunctionName,ReadBuffer,ReadBufferSize));

		if (ReadBufferSize<DataReadFromHWDeviceSize)
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			break;
		}

		// !!! Skopiruju sa data nacitane z HW DEVICE do READ BUFFER.
		RtlCopyMemory(ReadBuffer,DataReadFromHWDevice,DataReadFromHWDeviceSize);

		KdPrint(("!!!!!!!!!! READ DISPATCH ROUTINE [%s] - DATA READ [%S] !!!\n",FunctionName,DataReadFromHWDevice));

		Status=STATUS_SUCCESS;
		NumberOfBytesRead=DataReadFromHWDeviceSize;
	}
	while(false);

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=NumberOfBytesRead;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

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
		// !!!!! Vykona sa mapovanie LIST STRUCTURES [MDL] do KERNEL MODE SYSTEM ADDRESS SPACE.
		PVOID													WriteBuffer=MmGetSystemAddressForMdlSafe(Irp->MdlAddress,MM_PAGE_PRIORITY::NormalPagePriority);

		if (WriteBuffer==nullptr)
		{
			KdPrint(("!!!!!!!!!! WRITE DISPATCH ROUTINE [%s] FAILED to MAP MDL to KERNEL MODE SYSTEM ADDRESS SPACE !!!\n",FunctionName));

			Status=STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		ULONG													WriteBufferSize=CurrentStackLocation->Parameters.Write.Length;

		KdPrint(("!!!!!!!!!! WRITE DISPATCH ROUTINE [%s] - BUFFER [%p] BUFFER SIZE [%lu] !!!\n",FunctionName,WriteBuffer,WriteBufferSize));

		if (WriteBufferSize<MinDataWriteToHWDeviceSize)
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			break;
		}

		const wchar_t*											TypedWriteBuffer=reinterpret_cast<const wchar_t*>(WriteBuffer);

		KdPrint(("!!!!!!!!!! WRITE DISPATCH ROUTINE [%s] - DATA WRITTEN [%S] !!!\n",FunctionName,TypedWriteBuffer));

		Status=STATUS_SUCCESS;
		NumberOfBytesWritten=WriteBufferSize;
	}
	while(false);

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=NumberOfBytesWritten;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

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
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\DirectIOMode");

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
	DriverObject->MajorFunction[IRP_MJ_READ]=DispatchRoutineRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE]=DispatchRoutineWrite;

	UNICODE_STRING												DeviceName;

	// !!! DEVICE NAME by mal mat PREFIX [\Device].
	RtlInitUnicodeString(&DeviceName,L"\\Device\\DirectIOMode");

	PDEVICE_OBJECT												DeviceObject;

	NTSTATUS													Status1=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

	if (NT_SUCCESS(Status1)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status1));
		return(Status1);
	}

	// !!!!! DEVICE OBJECT sa nastavi do DIRECT IO MODE.
	DeviceObject->Flags|=DO_DIRECT_IO;

	UNICODE_STRING												SymbolicLink;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\DirectIOMode");

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