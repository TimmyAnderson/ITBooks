//----------------------------------------------------------------------------------------------------------------------
#include "TestCallbacksPendingSafePostOperation.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS CallbacksPendingSafePostOperationSafeCallback(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID CompletionContext, FLT_POST_OPERATION_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(Data);
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);
	UNREFERENCED_PARAMETER(Flags);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST OPERATION SAFE CALLBACK [%s] is CALLED !!!\n",FunctionName));

	CHelpers::Sleep(1000);

	KdPrint(("!!!!! POST OPERATION SAFE CALLBACK [%s] is FINISHING !!!\n",FunctionName));

	// !!!!! Ak by CALLBACK FUNCTION vratila RETURN VALUE [FLT_POSTOP_MORE_PROCESSING_REQUIRED], pretoze by napriklad spustila WORK ITEM, ktory by ukoncoval IO OPERATION, tak by vo WORK ITEM MUSELA volat FUNCTION [FltCompletePendedPostOperation()], aby FILTER MANAGER oznamila, ze PROCESSING je skonceny.
	// !!!!! Ak vsak CALLBACK FUNCTION vrati RETURN VALUE [FLT_POSTOP_FINISHED_PROCESSING], tak sa NESMIE volat FUNCTION [FltCompletePendedPostOperation()], inak dojde k BUG CHECK. FUNCTION FUNCTION [FltCompletePendedPostOperation()] je volana INTERNE FILTER MANAGER.
	return(FLT_POSTOP_FINISHED_PROCESSING);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestCallbacksPendingSafePostOperationPreOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	FLT_PREOP_CALLBACK_STATUS									CallbackStatus=FLT_PREOP_SUCCESS_WITH_CALLBACK;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestCallbacksPendingSafePostOperationPostOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PFLT_CALLBACK_DATA CallbackData, PCFLT_RELATED_OBJECTS FltObjects, FLT_POST_OPERATION_FLAGS Flags)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	// !!! SAFE DEFERRED METHOD sa NESMIE pouzivat pri DRAINING.
	if ((Flags & FLTFL_POST_OPERATION_DRAINING)!=0)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	// !!! SAFE DEFERRED METHOD sa moze pouzvat iba na IRP BASED REQUESTS.
	if (FLT_IS_IRP_OPERATION(CallbackData)==false)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	UCHAR														MajorFunction=CallbackData->Iopb->MajorFunction;

	// !!! SAFE DEFERRED METHOD sa NESMIE pouzivat pre tieto MAJOR FUNCTIONS.
	if (MajorFunction==IRP_MJ_READ || MajorFunction==IRP_MJ_WRITE || MajorFunction==IRP_MJ_FLUSH_BUFFERS)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	FLT_POSTOP_CALLBACK_STATUS									CallbackStatus;

	// !!! Obsahuje RETURN VALUE, ktoru by mala POST OPERATION vratit.
	FLT_POSTOP_CALLBACK_STATUS									RetPostOperationStatus;

	// !!!!! Spusti sa SAFE DEFERRED METHOD, ktora vykona CALLBACK na IRQL [IRQL<DISPATCH_LEVEL].
	if (FltDoCompletionProcessingWhenSafe(CallbackData,FltObjects,nullptr,Flags,CallbacksPendingSafePostOperationSafeCallback,&RetPostOperationStatus)==TRUE)
	{
		KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] SUCCEEDED to DEFFER EXECUTION with POST OPERATION STATUS [%lu] !!!\n",FunctionName,RetPostOperationStatus));
	}
	else
	{
		KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FAILED to DEFFER EXECUTION with POST OPERATION STATUS [%lu] !!!\n",FunctionName,RetPostOperationStatus));
	}

	// !!! Ako RETURN VALUE sa nastavi to co vratila FUNCTION [FltDoCompletionProcessingWhenSafe()].
	CallbackStatus=RetPostOperationStatus;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------