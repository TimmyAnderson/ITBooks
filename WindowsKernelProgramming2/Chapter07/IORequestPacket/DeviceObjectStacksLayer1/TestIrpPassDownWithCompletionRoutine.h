//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestIrpPassDownWithCompletionRoutine(DEVICE_OBJECT* DeviceObject, DEVICE_OBJECT* LowerDeviceObject, IRP* Irp);
//----------------------------------------------------------------------------------------------------------------------