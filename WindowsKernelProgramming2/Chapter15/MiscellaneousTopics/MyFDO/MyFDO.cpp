//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
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

	PVOID														ReadBuffer=Irp->AssociatedIrp.SystemBuffer;
	ULONG														ReadBufferSize=CurrentStackLocation->Parameters.Read.Length;

	KdPrint(("!!!!!!!!!! READ DISPATCH ROUTINE [%s] - BUFFER [%p] BUFFER SIZE [%lu] !!!\n",FunctionName,ReadBuffer,ReadBufferSize));

	do
	{
		if (ReadBuffer==nullptr)
		{
			Status=STATUS_INVALID_PARAMETER;
			break;
		}

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

	Status=CHelpers::CompleteIRP(Irp,Status,NumberOfBytesRead);

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

	PVOID														WriteBuffer=Irp->AssociatedIrp.SystemBuffer;
	ULONG														WriteBufferSize=CurrentStackLocation->Parameters.Write.Length;

	KdPrint(("!!!!!!!!!! WRITE DISPATCH ROUTINE [%s] - BUFFER [%p] BUFFER SIZE [%lu] !!!\n",FunctionName,WriteBuffer,WriteBufferSize));

	do
	{
		if (WriteBuffer==nullptr)
		{
			Status=STATUS_INVALID_PARAMETER;
			break;
		}

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

	Status=CHelpers::CompleteIRP(Irp,Status,NumberOfBytesWritten);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

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

	NTSTATUS													Status=STATUS_SUCCESS;
	PDEVICE_OBJECT												DeviceObject=nullptr;
	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	bool														SymbolicLinkCreated=false;
	
	do
	{
		Status=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,TRUE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		DeviceObject->Flags|=DO_BUFFERED_IO;

		Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK [%wZ] with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,SymbolicLink,Status));
			break;
		}

		SymbolicLinkCreated=true;
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
		}
	
		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}

		return(Status);
	}

	DriverObject->DriverUnload=FunctionDriverUnload;
	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_READ]=DispatchRoutineRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE]=DispatchRoutineWrite;

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------