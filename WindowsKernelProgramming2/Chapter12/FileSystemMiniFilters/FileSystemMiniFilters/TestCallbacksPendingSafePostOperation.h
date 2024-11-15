//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <fltKernel.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestCallbacksPendingSafePostOperationPreOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation);
FLT_POSTOP_CALLBACK_STATUS TestCallbacksPendingSafePostOperationPostOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PFLT_CALLBACK_DATA CallbackData, PCFLT_RELATED_OBJECTS FltObjects, FLT_POST_OPERATION_FLAGS Flags);
//----------------------------------------------------------------------------------------------------------------------