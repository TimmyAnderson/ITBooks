//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "SharedHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestReadRegistryNotificationCounters(DEVICE_OBJECT* DeviceObject, IRP* Irp, const SRegistryNotificationStatistics& Statistics);
//----------------------------------------------------------------------------------------------------------------------