//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <stdarg.h>
#include <TraceLoggingProvider.h>
#include <evntrace.h>
#include "MyKernelHelpers.h"
#include "SThreadData.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// GUID [7B03FB4E-8E4B-4A74-9D90-63E5403D8650].
TRACELOGGING_DEFINE_PROVIDER(MyETWProvider,"MyETWProvider",(0x7b03fb4e, 0x8e4b, 0x4a74, 0x9d, 0x90, 0x63, 0xe5, 0x40, 0x3d, 0x86, 0x50));
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
ULONG Log1(PCSTR Format, ...)
{
	va_list															List;

	va_start(List,Format);

	ULONG															Result=vKdPrintEx((DPFLTR_IHVDRIVER_ID,1,Format,List));

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
ULONG Log2(PCSTR Format, ...)
{
	va_list															List;

	va_start(List,Format);

	ULONG															Result=vKdPrintExWithPrefix(("MY PREFIX - ",DPFLTR_IHVDRIVER_ID,1,Format,List));

	return(Result);
}
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

	// !!! ASSERT vyvola EXCEPTION.
	// !!!!! WINDOWS umoznuje aj po vzniku EXCEPTION, kedy je REMOTE MACHINE FROZEN pripojit DEBUGGER a zistit na ktorom mieste doslo k ASSERTION FAILURE.
	//NT_ASSERT(false);

	// !!! Zapise LOG do ETW.
	TraceLoggingWrite(MyETWProvider,"My ETW LOG in DRIVER ROUTINE WRITE.",TraceLoggingLevel(TRACE_LEVEL_INFORMATION),TraceLoggingValue("DebuggingAndTracing Driver","DriverName"),TraceLoggingInt32(-100,"IntValue"),TraceLoggingUInt32(100,"UIntValue"),TraceLoggingNTStatus(STATUS_SUCCESS,"Status","Returned status"));

	KdPrintEx((DPFLTR_IHVDRIVER_ID,1,"!!!!! LOG with LEVEL ID [%lu] !!!\n",1));
	KdPrintEx((DPFLTR_IHVDRIVER_ID,4,"!!!!! LOG with LEVEL ID [%lu] !!!\n",4));
	KdPrintEx((DPFLTR_IHVDRIVER_ID,100,"!!!!! LOG with LEVEL ID [%lu] !!!\n",100));
	KdPrintEx((DPFLTR_IHVDRIVER_ID,1000,"!!!!! LOG with LEVEL ID [%lu] !!!\n",1000));
	KdPrintEx((DPFLTR_IHVDRIVER_ID,1024,"!!!!! LOG with LEVEL ID [%lu] !!!\n",1024));

	Log(DPFLTR_IHVDRIVER_ID,ELogLevel::E_DEBUG,"!!!!! LOG FUNCTION Log() with COMPONENT ID [%lu] LEVEL ID [%lu] !!!\n",DPFLTR_IHVDRIVER_ID,static_cast<ULONG>(ELogLevel::E_DEBUG));
	Log(ELogLevel::E_VERBOSE,"!!!!! LOG FUNCTION Log() with LEVEL ID [%lu] !!!\n",static_cast<ULONG>(ELogLevel::E_VERBOSE));

	LogError("!!!!! LOG FUNCTION LogError() with VALUES [%d,%d] !!!\n",100,1100);
	LogWarning("!!!!! LOG FUNCTION LogWarning() with VALUES [%d,%d] !!!\n",200,1200);
	LogInformation("!!!!! LOG FUNCTION LogInformation() with VALUES [%d,%d] !!!\n",300,1300);
	LogDebug("!!!!! LOG FUNCTION LogDebug() with VALUES [%d,%d] !!!\n",400,1400);
	LogVerbose("!!!!! LOG FUNCTION LogVerbose() CALLED with VALUES [%d,%d] !!!\n",500,1500);

	Log1("!!!!! LOG 1 with VALUES [%d,%d] !!!\n",2000,3000);
	Log2("!!!!! LOG 2 with VALUES [%d,%d] !!!\n",4000,5000);

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
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\DebuggingAndTracing");

	// !!! Zapise LOG do ETW.
	TraceLoggingWrite(MyETWProvider,"My ETW LOG in DRIVER UNLOAD.",TraceLoggingLevel(TRACE_LEVEL_INFORMATION),TraceLoggingValue("DebuggingAndTracing Driver","DriverName"),TraceLoggingUnicodeString(&SymbolicLink,"SymbolicLink"),TraceLoggingInt32(-100,"IntValue"),TraceLoggingUInt32(100,"UIntValue"),TraceLoggingNTStatus(STATUS_SUCCESS,"Status","Returned status"));

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(DriverObject->DeviceObject);

	TraceLoggingUnregister(MyETWProvider);

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	// !!! ASSERT prebehne uspesne.
	NT_ASSERT(true);

	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	DriverObject->DriverUnload=FunctionDriverUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_WRITE]=DispatchRoutineWrite;

	UNICODE_STRING												DeviceName;

	// !!! DEVICE NAME by mal mat PREFIX [\Device].
	RtlInitUnicodeString(&DeviceName,L"\\Device\\DebuggingAndTracing");

	// !!! Registruje sa ETW PROVIDER.
	NTSTATUS													Status1=TraceLoggingRegister(MyETWProvider);

	if (NT_SUCCESS(Status1)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE ETW PROVIDER with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status1));
		return(Status1);
	}

	PDEVICE_OBJECT												DeviceObject;

	NTSTATUS													Status2=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

	if (NT_SUCCESS(Status2)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status2));

		TraceLoggingUnregister(MyETWProvider);

		return(Status2);
	}

	UNICODE_STRING												SymbolicLink;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\DebuggingAndTracing");

	NTSTATUS													Status3=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

	if (NT_SUCCESS(Status3)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status3));

		TraceLoggingUnregister(MyETWProvider);

		IoDeleteDevice(DeviceObject);

		return(Status3);
	}

	// !!! Zapise LOG do ETW.
	TraceLoggingWrite(MyETWProvider,"My ETW LOG in DRIVER ENTRY.",TraceLoggingLevel(TRACE_LEVEL_INFORMATION),TraceLoggingValue("DebuggingAndTracing Driver", "DriverName"),TraceLoggingUnicodeString(RegistryPath, "RegistryPath"),TraceLoggingInt32(-100, "IntValue"),TraceLoggingUInt32(100, "UIntValue"),TraceLoggingNTStatus(STATUS_SUCCESS,"Status","Returned status"));

	KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------