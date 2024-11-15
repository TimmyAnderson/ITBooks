//----------------------------------------------------------------------------------------------------------------------
#include "TestCallbacksNoPostOperation.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestCallbacksNoPostOperationPreOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	FLT_PREOP_CALLBACK_STATUS									CallbackStatus=FLT_PREOP_SUCCESS_NO_CALLBACK;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestCallbacksNoPostOperationPostOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	FLT_POSTOP_CALLBACK_STATUS									CallbackStatus=FLT_POSTOP_FINISHED_PROCESSING;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------