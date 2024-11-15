//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <fltKernel.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestFixedSizedContextPostCreate(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects);
FLT_PREOP_CALLBACK_STATUS TestFixedSizedContextPreRead(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects);
FLT_POSTOP_CALLBACK_STATUS TestFixedSizedContextPostRead(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects);
//----------------------------------------------------------------------------------------------------------------------