//----------------------------------------------------------------------------------------------------------------------
#include "TestCallbacksNoPostOperation.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CallbacksPendingPreOperationPreOperationWorkItemRoutine(PVOID IoObject, PVOID Context, PIO_WORKITEM IoWorkItem)
{
	UNREFERENCED_PARAMETER(IoObject);

	IoFreeWorkItem(IoWorkItem);

	PFLT_CALLBACK_DATA											CallbackData=static_cast<PFLT_CALLBACK_DATA>(Context);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! WORK ITEM CALLBACK [%s] CALLED !!!\n",FunctionName));

	CHelpers::Sleep(1000);

	KdPrint(("!!!!! WORK ITEM CALLBACK [%s] is FINISHING PRE OPERATION !!!\n",FunctionName));

	// !!! Bude sa volat POST CALLBACK.
	FltCompletePendedPreOperation(CallbackData,FLT_PREOP_SUCCESS_WITH_CALLBACK,nullptr);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestCallbacksPendingPreOperationPreOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PFLT_CALLBACK_DATA CallbackData, PDEVICE_OBJECT DeviceObject)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	FLT_PREOP_CALLBACK_STATUS									CallbackStatus=FLT_PREOP_PENDING;
	PIO_WORKITEM												WorkItem=IoAllocateWorkItem(DeviceObject);

	if (WorkItem!=nullptr)
	{
		IoQueueWorkItemEx(WorkItem,CallbacksPendingPreOperationPreOperationWorkItemRoutine,WORK_QUEUE_TYPE::DelayedWorkQueue,CallbackData);

		CallbackStatus=FLT_PREOP_PENDING;
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - CAN NOT ALLOCATE WORK ITEM.\n",FunctionName));

		CallbackStatus=FLT_PREOP_SUCCESS_WITH_CALLBACK;
	}

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestCallbacksPendingPreOperationPostOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	FLT_POSTOP_CALLBACK_STATUS									CallbackStatus=FLT_POSTOP_FINISHED_PROCESSING;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------