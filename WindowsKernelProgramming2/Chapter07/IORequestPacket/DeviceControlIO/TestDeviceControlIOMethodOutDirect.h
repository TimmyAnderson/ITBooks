//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestDeviceControlIOMethodOutDirect(DEVICE_OBJECT* DeviceObject, IRP* Irp);
//----------------------------------------------------------------------------------------------------------------------