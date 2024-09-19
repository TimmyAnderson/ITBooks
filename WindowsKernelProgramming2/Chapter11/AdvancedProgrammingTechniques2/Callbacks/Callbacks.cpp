//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PVOID															RegistrationCookie;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CallbackSystemTimeChanged(PVOID Context, PVOID Argument1, PVOID Argument2)
{
	UNREFERENCED_PARAMETER(Context);

	KdPrint(("!!!!!!!!!! SYSTEM TIME CHANGED. ARGUMENT 1 [%p] ARGUMENT 2 [%p].\n",Argument1,Argument2));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	ExUnregisterCallback(RegistrationCookie);

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

	NTSTATUS													Status=STATUS_SUCCESS;

	do
	{
		OBJECT_ATTRIBUTES										Attributes;
		UNICODE_STRING											Name=RTL_CONSTANT_STRING(L"\\Callback\\SetSystemTime");

		InitializeObjectAttributes(&Attributes,&Name,OBJ_CASE_INSENSITIVE,nullptr,nullptr);

		PCALLBACK_OBJECT										Callback;

		Status=ExCreateCallback(&Callback,&Attributes,FALSE,TRUE);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to OPEN CALLBACK OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		RegistrationCookie=ExRegisterCallback(Callback,CallbackSystemTimeChanged,nullptr);

		if (RegistrationCookie==nullptr)
		{
			ObDereferenceObject(Callback);

			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER CALLBACK FUNCTION for CALLBACK OBJECT !!!\n",DriverObject->DriverName));

			Status=STATUS_UNSUCCESSFUL;
			break;
		}

		ObDereferenceObject(Callback);
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to START !!!\n",DriverObject->DriverName));
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------