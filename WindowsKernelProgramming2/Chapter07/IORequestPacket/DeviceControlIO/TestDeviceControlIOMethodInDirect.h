//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestDeviceControlIOMethodInDirect(DEVICE_OBJECT* DeviceObject, IRP* Irp);
//----------------------------------------------------------------------------------------------------------------------