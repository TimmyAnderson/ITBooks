//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "MyKernelHelpers.h"
#include "SThreadData.h"
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
NTSTATUS DispatchRoutineWrite(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	// !!! FUNCTION vrati CURRENT STACK LOCATION.
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

	do
	{
		// !!! Vykona sa kontrola ci BUFFER obsahuje instanciu CUSTOM STRUCTURE [SThreadData].
		if (CurrentStackLocation->Parameters.Write.Length<sizeof(SThreadData))
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			break;
		}

		SThreadData*											Data=static_cast<SThreadData*>(Irp->UserBuffer);

		// !!! Vykona sa kontrola ci BUFFER nie je NULL.
		if (Data==nullptr)
		{
			Status=STATUS_INVALID_PARAMETER;
			break;
		}

		// !!! Vykona sa kontrola ci THREAD PRIORITY neobsahuje nespravnu hodnotu.
		if (Data->Priority<1 || Data->Priority>31)
		{
			Status=STATUS_INVALID_PARAMETER;
			break;
		}

		PETHREAD										Thread;

		// !!! Pre THREAD ID sa ziska POINTER na STRUCTURE [_KTHREAD].
		// !!!!! FUNCTION ZVYSUJE COUNTER pre THREAD s danym THREAD ID. Je to preto, aby sa zabranilo tomu, ze ak by sa THREAD nahodou uvolnil, aby STRUCTURE [_KTHREAD] obsahovala neplatne data. COUNTER je NUTNE uvolnit volanim FUNCTION [ObfDereferenceObject()].
		Status=PsLookupThreadByThreadId(ULongToHandle(Data->ThreadID),&Thread);

		if (NT_SUCCESS(Status)==false)
		{
			break;
		}

		// !!! Zmeni PRIORITY daneho THREADU.
		KPRIORITY												OldPriority=KeSetPriorityThread(Thread,Data->Priority);

		KdPrint(("!!!!! DRIVER CHANGED THREAD [%lu] PRIORITY from PRIORITY [%ld] to PRIORITY [%ld] !!!\n",Data->ThreadID,OldPriority,Data->Priority));

		// !!!!! Uvolni INTERNAL COUNTER STRUCTURE [_KTHREAD] cim umozni jej uvolnenie z MEMORY, ak sa THREAD skonci.
		ObfDereferenceObject(Thread);

		// !!! Nastavi sa pocet 'zapisanych' BYTES.
		Information=sizeof(Data);
	}
	while(false);

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp, IO_NO_INCREMENT);

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
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\DriverFromStartToFinish");

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
	DriverObject->MajorFunction[IRP_MJ_WRITE]=DispatchRoutineWrite;

	UNICODE_STRING												DeviceName;

	// !!! DEVICE NAME by mal mat PREFIX [\Device].
	RtlInitUnicodeString(&DeviceName,L"\\Device\\DriverFromStartToFinish");

	PDEVICE_OBJECT												DeviceObject;

	NTSTATUS													Status1=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

	if (NT_SUCCESS(Status1)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status1));
		return(Status1);
	}

	UNICODE_STRING												SymbolicLink;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\DriverFromStartToFinish");

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