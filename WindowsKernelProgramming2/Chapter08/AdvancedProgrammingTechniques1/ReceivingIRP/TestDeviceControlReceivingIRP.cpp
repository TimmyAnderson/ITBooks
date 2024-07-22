//----------------------------------------------------------------------------------------------------------------------
#include "TestDeviceControlReceivingIRP.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestDeviceControlReceivingIRP(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - STARTED EXECUTION.\n",DeviceObject->DriverObject->DriverName,FunctionName));

	CHelpers::Sleep(2000);

	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] - FINISHED EXECUTION.\n",DeviceObject->DriverObject->DriverName,FunctionName));

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------