//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestExtendedTimersNoWake(DEVICE_OBJECT* DeviceObject, IRP* Irp);
//----------------------------------------------------------------------------------------------------------------------