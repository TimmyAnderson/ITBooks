//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
HANDLE MyGetProcessID(ULONG SessionID, const UNICODE_STRING& ProcessName);
HANDLE MyGetProcessHandle(HANDLE ProcessID);
//----------------------------------------------------------------------------------------------------------------------