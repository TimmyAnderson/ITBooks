//----------------------------------------------------------------------------------------------------------------------
#include "TestCallbacksPendingWorkItemPostOperation.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
VOID CallbacksPendingWorkItemPostOperationWorkItemCallback(PFLT_DEFERRED_IO_WORKITEM FltWorkItem, PFLT_CALLBACK_DATA CallbackData, PVOID Context)
{
	UNREFERENCED_PARAMETER(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST OPERATION WORK ITEM CALLBACK [%s] is CALLED !!!\n",FunctionName));

	CHelpers::Sleep(1000);

	KdPrint(("!!!!! POST OPERATION WORK ITEM CALLBACK [%s] is FINISHING !!!\n",FunctionName));

	// !!!!! FUNCTION oznami FILTER MANAGER, ze POST OPERATION CALLBACK bol ukonceny a moze pokracovat v dalsom spracovani IO OPERATION.
	FltCompletePendedPostOperation(CallbackData);

	// !!!!! WORK ITEM sa odstrani z MEMORY.
	FltFreeDeferredIoWorkItem(FltWorkItem);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestCallbacksPendingWorkItemPostOperationPreOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	FLT_PREOP_CALLBACK_STATUS									CallbackStatus=FLT_PREOP_SUCCESS_WITH_CALLBACK;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestCallbacksPendingWorkItemPostOperationPostOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PFLT_CALLBACK_DATA CallbackData, PVOID CompletionContext, FLT_POST_OPERATION_FLAGS Flags)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	// !!! WORK ITEM DEFERRED METHOD sa NESMIE pouzivat pri DRAINING.
	if ((Flags & FLTFL_POST_OPERATION_DRAINING)!=0)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	// !!! WORK ITEM DEFERRED METHOD sa moze pouzvat iba na IRP BASED REQUESTS.
	if (FLT_IS_IRP_OPERATION(CallbackData)==false)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	FLT_POSTOP_CALLBACK_STATUS									CallbackStatus;

	// !!! Alokuje sa WORK ITEM pre WORK ITEM DEFERRED METHOD.
	PFLT_DEFERRED_IO_WORKITEM									WorkItem=FltAllocateDeferredIoWorkItem();

	if (WorkItem!=nullptr)
	{
		NTSTATUS												Status=FltQueueDeferredIoWorkItem(WorkItem,CallbackData,CallbacksPendingWorkItemPostOperationWorkItemCallback,DelayedWorkQueue,CompletionContext);

		if (NT_SUCCESS(Status)==true)
		{
			KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] SUCCEEDED to DEFFER WORK ITEM !!!\n",FunctionName));

			CallbackStatus=FLT_POSTOP_MORE_PROCESSING_REQUIRED;
		}
		else
		{
			KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FAILED to DEFFER WORK ITEM with ERROR CODE [%lX] !!!\n",FunctionName,Status));

			FltFreeDeferredIoWorkItem(WorkItem);

			CallbackStatus=FLT_POSTOP_FINISHED_PROCESSING;
		}
	}
	else
	{
		KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FAILED to ALLOCATE DEFFER WORK ITEM !!!\n",FunctionName));

		CallbackStatus=FLT_POSTOP_FINISHED_PROCESSING;
	}

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------