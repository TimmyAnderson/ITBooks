//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <fltKernel.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestVariableSizedContextPostCreate(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects);
FLT_PREOP_CALLBACK_STATUS TestVariableSizedContextPreRead(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects);
FLT_POSTOP_CALLBACK_STATUS TestVariableSizedContextPostRead(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects);
//----------------------------------------------------------------------------------------------------------------------