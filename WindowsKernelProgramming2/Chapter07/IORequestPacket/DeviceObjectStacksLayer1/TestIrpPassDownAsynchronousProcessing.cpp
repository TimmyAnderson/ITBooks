//----------------------------------------------------------------------------------------------------------------------
#include "TestIrpPassDownAsynchronousProcessing.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS IrpPassDownAsynchronousProcessingCompletionRoutine(PDEVICE_OBJECT DeviceObject, PIRP Irp, PVOID Context)
{
	UNREFERENCED_PARAMETER(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] UPPER DRIVER - COMPLETION ROUTINE CALLED - PENDING RETURNED [%hhu] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName,Irp->PendingReturned));

	// !!!!! Ak DRIVER nastavi COMPLETION ROUTINE musi v COMPLETION ROUTINE VZDY skontrolovat FLAG [PendingReturned]. Ak je nastaveny, MUSI COMPLETION ROUTINE volat FUNCTION [IoMarkIrpPending()].
	if (Irp->PendingReturned!=FALSE)
	{
		// !!!!! Vykona sa propagacia FLAG [SL_PENDING_RETURNED] do STRUCTURE [IO_STACK_LOCATION] zodpovedajucemu DRIVER VYSSIE v DEVICE OBJECT STACK.
		IoMarkIrpPending(Irp);
	}

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestIrpPassDownAsynchronousProcessing(DEVICE_OBJECT* DeviceObject, DEVICE_OBJECT* LowerDeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	// !!!!! CURRENT STACK LOCATION sa nakopiruje do NEXT STACK LOCATION.
	IoCopyCurrentIrpStackLocationToNext(Irp);

	// !!!!! Nastavi sa COMPLETION ROUTINE.
	// !!!!! FUNCTION [IoSetCompletionRoutine()] sa MUSI volat AZ po FUNCTION [IoCopyCurrentIrpStackLocationToNext()], pretoze POINTER na COMPLETION ROUTINE sa uklada do STACK LOCATION pre DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK.
	IoSetCompletionRoutine(Irp,IrpPassDownAsynchronousProcessingCompletionRoutine,nullptr,true,true,true);

	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] UPPER DRIVER - SENDING IRP TO LOWER DRIVER !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));
	
	// !!!!! IRP sa odosle do LOWER DRIVER.
	NTSTATUS													Status=IoCallDriver(LowerDeviceObject,Irp);

	KdPrint(("!!!!!!!!!! DRIVER [%wZ] ROUTINE [%s] UPPER DRIVER - SENT IRP TO LOWER DRIVER with RETURN CODE [%lX] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName,Status));

	// !!!!! Musi sa vratit RETURN VALUE, ktoru vratilo MACRO [IoCallDriver()].
	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------