//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestSpinLockGlobalLocalPointer(DEVICE_OBJECT* DeviceObject, IRP* Irp);
//----------------------------------------------------------------------------------------------------------------------