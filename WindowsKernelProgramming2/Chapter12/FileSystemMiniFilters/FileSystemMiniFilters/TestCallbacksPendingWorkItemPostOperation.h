//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <fltKernel.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestCallbacksPendingWorkItemPostOperationPreOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation);
FLT_POSTOP_CALLBACK_STATUS TestCallbacksPendingWorkItemPostOperationPostOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PFLT_CALLBACK_DATA CallbackData, PVOID CompletionContext, FLT_POST_OPERATION_FLAGS Flags);
//----------------------------------------------------------------------------------------------------------------------