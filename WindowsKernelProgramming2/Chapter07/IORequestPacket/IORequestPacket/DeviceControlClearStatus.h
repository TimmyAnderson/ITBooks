//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DeviceControlClearStatus(DEVICE_OBJECT* DeviceObject, IRP* Irp, volatile LONG64& TotalReadBytes, volatile LONG64& TotalWriteBytes);
//----------------------------------------------------------------------------------------------------------------------