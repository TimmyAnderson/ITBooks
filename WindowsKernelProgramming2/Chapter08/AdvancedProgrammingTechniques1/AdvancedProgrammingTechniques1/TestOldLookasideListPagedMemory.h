//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestOldLookasideListPagedMemory(DEVICE_OBJECT* DeviceObject, IRP* Irp, PAGED_LOOKASIDE_LIST* LookasidePaged);
//----------------------------------------------------------------------------------------------------------------------