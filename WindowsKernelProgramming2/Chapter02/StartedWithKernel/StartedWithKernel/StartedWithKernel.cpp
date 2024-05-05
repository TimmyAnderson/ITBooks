//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	DbgPrint("!!!!! DBG PRINT - DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName);

	KdPrint(("!!!!! KD PRINT - DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION [DriverEntry()] MUSI mat pouzity C-LINKAGE.
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	// !!! MACRO oznacuje, ze PARAMETER sa NEPOUZIVA. Je to preto, aby COMPILER hodil WARNING, ktory sa interpretuje ako ERROR.
	UNREFERENCED_PARAMETER(RegistryPath);

	// !!! Zaregistruje sa DRIVER UNLOAD FUNCTION.
	DriverObject->DriverUnload=FunctionDriverUnload;

	DbgPrint("!!!!! DBG PRINT - DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName);

	// !!!!! MUSIA sa pouzit 2 ZATVORKY, aby COMPILER nehodil ERROR.
	KdPrint(("!!!!! KD PRINT - DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------