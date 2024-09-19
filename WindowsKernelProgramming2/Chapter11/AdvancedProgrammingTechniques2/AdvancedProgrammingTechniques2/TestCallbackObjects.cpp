//----------------------------------------------------------------------------------------------------------------------
#include "TestCallbackObjects.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
VOID CallbackObjectsCallback(PVOID CallbackContext, PVOID Argument1, PVOID Argument2)
{
	UNREFERENCED_PARAMETER(CallbackContext);
	UNREFERENCED_PARAMETER(Argument1);
	UNREFERENCED_PARAMETER(Argument2);

	const char*													TypedArgument1=static_cast<const char*>(Argument1);
	ULONG64														TypedArgument2=((ULONG64)Argument2);

	KdPrint(("!!!!!!!!!! CALLBACK FUNCTION of CALLBACK OBJECT CALLED. ARGUMENT 1 [%s] ARGUMENT 2 [%lu].\n",TypedArgument1,TypedArgument2));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestCallbackObjects(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		UNICODE_STRING											CallbackObjectName=RTL_CONSTANT_STRING(L"\\Callback\\MyCallbackObject");
		OBJECT_ATTRIBUTES										Attributes;

		InitializeObjectAttributes(&Attributes,&CallbackObjectName,OBJ_CASE_INSENSITIVE,nullptr,nullptr);

		PCALLBACK_OBJECT										CallbackObject;

		// !!! Vytvori sa novy CALLBACK OBJECT.
		Status=ExCreateCallback(&CallbackObject,&Attributes,TRUE,TRUE);

		if (NT_SUCCESS(Status)==true)
		{
			// !!! Zaregistruje sa CALLBACK FUNCTION pre CALLBACK OBJECT.
			PVOID												CallbackObjectHandle=ExRegisterCallback(CallbackObject,CallbackObjectsCallback,nullptr);

			if (CallbackObjectHandle!=nullptr)
			{
				for(ULONG64 Index=0;Index<5;Index++)
				{
					ExNotifyCallback(CallbackObject,(PVOID)"Some TEXT !",(PVOID)((Index+1)*100));

					CHelpers::Sleep(2*1000);
				}

				// !!! Odregistruje sa CALLBACK FUNCTION pre CALLBACK OBJECT.
				ExUnregisterCallback(CallbackObjectHandle);
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - REGISTRATION of CALLBACK FUNCTION for CALLBACK OBJECT FAILED !!!\n",FunctionName));
			}

			// !!!!! CALLBACK OBJECT MUSI byt DEREFERENCED, aby sa odstranil z WINDOWS.
			ObDereferenceObject(CallbackObject);
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - CREATION of CALLBACK OBJECT FAILED with ERROR CODE [%lX] !!!\n",FunctionName,Status));
		}

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------