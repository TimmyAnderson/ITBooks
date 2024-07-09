//----------------------------------------------------------------------------------------------------------------------
#include "TestIrpPassDownSkipStackLocation.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestIrpPassDownSkipStackLocation(DEVICE_OBJECT* DeviceObject, DEVICE_OBJECT* LowerDeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	// !!!!! CURRENT STACK LOCATION sa PRESKOCI cim CURRENT STACK LOCATION a NEXT STACK LOCATION budu ukazovat na TU ISTU LOCATION.
	// !!!!! Pri pouziti FUNCTION [IoSkipCurrentIrpStackLocation()] NEMOZE CURRENT DRIVER registrovat CALLBACK FUNCTION.
	IoSkipCurrentIrpStackLocation(Irp);

	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] UPPER DRIVER - SENDING IRP TO LOWER DRIVER !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));
	
	// !!!!! IRP sa odosle do LOWER DRIVER.
	NTSTATUS													Status=IoCallDriver(LowerDeviceObject,Irp);

	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] UPPER DRIVER - SENT IRP TO LOWER DRIVER with RETURN CODE [%lX] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName,Status));

	// !!!!! Musi sa vratit RETURN VALUE, ktoru vratilo MACRO [IoCallDriver()].
	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------