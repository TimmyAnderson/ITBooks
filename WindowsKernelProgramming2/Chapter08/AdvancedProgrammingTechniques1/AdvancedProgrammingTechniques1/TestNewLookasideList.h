//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestNewLookasideList(DEVICE_OBJECT* DeviceObject, IRP* Irp, LOOKASIDE_LIST_EX* Lookaside);
//----------------------------------------------------------------------------------------------------------------------