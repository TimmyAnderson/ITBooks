//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <fltKernel.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestCallbacksPendingPreOperationPreOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PFLT_CALLBACK_DATA CallbackData, PDEVICE_OBJECT DeviceObject);
FLT_POSTOP_CALLBACK_STATUS TestCallbacksPendingPreOperationPostOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation);
//----------------------------------------------------------------------------------------------------------------------