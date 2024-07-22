//----------------------------------------------------------------------------------------------------------------------
#include "TestSendDeviceControlIRPToReceivingDriver.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "..\ReceivingIRP\SharedHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CODE funguje IBA ak je spusteny DRIVER [ReceivingIRP] do ktoreho sa posiela IRP.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_RECEIVING_IRP CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_RECEIVING_IRP,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestSendDeviceControlIRPToReceivingDriver(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	// !!!!! FILE OBJECT NESMIE byt uzatvoreny kym sa DEVICE OBJECT pouziva, pretoze drzi REFERENCE COUNTER DEVICE OBJECT.
	PFILE_OBJECT												ReceivingDriverFileObject=nullptr;

	do
	{
		KEVENT													MyEvent;

		// !!! EVENT sa pouziva ako WAIT OBJECT, ktory je signalizovany pri skonceni IRP.
		KeInitializeEvent(&MyEvent,EVENT_TYPE::SynchronizationEvent,FALSE);

		UNICODE_STRING											ReceivingDriverDeviceName;

		RtlInitUnicodeString(&ReceivingDriverDeviceName,L"\\Device\\ReceivingIRP");

		PDEVICE_OBJECT											ReceivingDriverDeviceObject;

		Status=IoGetDeviceObjectPointer(&ReceivingDriverDeviceName,FILE_ALL_ACCESS,&ReceivingDriverFileObject,&ReceivingDriverDeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - FAILED to CREATE DEVICE OBJECT for RECEIVING IRP DRIVER with ERROR CODE [%lX].\n",DeviceObject->DriverObject->DriverName,FunctionName,Status));
			break;
		}

		IO_STATUS_BLOCK											ReceivingDriverIoStatusBlock;

		// !!!!! Vytvori sa IRP, ktore bude zaslane do RECEIVING IRP DRIVER.
		// MAJOR FUNCTION je nastavena na VALUE [IRP_MJ_DEVICE_CONTROL].
		PIRP													ReceivingDriverIRP=IoBuildDeviceIoControlRequest(IOCTL_TEST_RECEIVING_IRP,ReceivingDriverDeviceObject,nullptr,0,nullptr,0,FALSE,&MyEvent,&ReceivingDriverIoStatusBlock);

		if (ReceivingDriverIRP==nullptr)
		{
			KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - FAILED to CREATE IRP for RECEIVING IRP DRIVER.\n",DeviceObject->DriverObject->DriverName,FunctionName));
			break;
		}

		// !!!!! CURRENT STACK LOCATION sa NESMIE MODIFIKOVAT, pretoze ju korektne nastavila FUNCTION [IoBuildDeviceIoControlRequest()].
		// !!!!! Ak by sa zavolala napriklad FUNCTION [IoCopyCurrentIrpStackLocationToNext()], tak by doslo k modifikacii nasledujucej STRUCTURE [IO_STACK_LOCATION], ktora VOBEC NEMUSI EXISTOVAT, pretoze STACK LOCATION SIZE moze byt rovny 1 a nastavovala by sa STACK LOCATION s INDEX 2 co by sposobilo BUG CHECK.

		KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - SENDING IRP to RECEIVING IRP DRIVER.\n",DeviceObject->DriverObject->DriverName,FunctionName));

		// !!!!! IRP sa odosle do RECEIVING IRP DRIVER.
		Status=IofCallDriver(ReceivingDriverDeviceObject,ReceivingDriverIRP);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - FAILED to SEND IRP to RECEIVING IRP DRIVER with ERROR CODE [%lX].\n",DeviceObject->DriverObject->DriverName,FunctionName,Status));
			break;
		}

		KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - SENT IRP to RECEIVING IRP DRIVER with CODE [%lX].\n",DeviceObject->DriverObject->DriverName,FunctionName,Status));

		Status=KeWaitForSingleObject(&MyEvent,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - FAILED to WAIT FOR IRP EVENT with ERROR CODE [%lX].\n",DeviceObject->DriverObject->DriverName,FunctionName,Status));
			break;
		}

		KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - IRP PROCESSED BY RECEIVING IRP DRIVER with IRP INFORMATION [%I64u] IRP STATUS [%lX].\n",DeviceObject->DriverObject->DriverName,FunctionName,ReceivingDriverIoStatusBlock.Information,ReceivingDriverIoStatusBlock.Status));
	}
	while(false);

	if (ReceivingDriverFileObject!=nullptr)
	{
		// !!!!! Znizenim REFERENCE COUNTER FILE HANDLE dojde k uvolneniu DEVICE OBEJCT.
		ObDereferenceObject(ReceivingDriverFileObject);

		ReceivingDriverFileObject=nullptr;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------