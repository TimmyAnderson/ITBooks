//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestSequencedSinglyLinkedLists(DEVICE_OBJECT* DeviceObject, IRP* Irp, ULONG NumberOfItems, bool Dump);
//----------------------------------------------------------------------------------------------------------------------