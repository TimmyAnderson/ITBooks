//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "PowerAndPNP_Structures.h"
//-------------------------------------------------------------------------------------------------------
// !!!!! CUSTOM STRUCTURE, ktore obsahuje DRIVER SPECIFIC DATA. Je tu mozne pridat LUBOVOLNE DALSIE DATA.
typedef struct _DEVICE_EXTENSION
{
	// Instancia DEVICE_OBJECT ku ktorej _DEVICE_EXTENSION prinalezi.
	PDEVICE_OBJECT												DeviceObject;
	// Nasledujuci DEVICE_OBJECT NIZSIE v DRIVER STACK.
	PDEVICE_OBJECT												LowerDeviceObject;
	// PHYSICAL DEVICE_OBJECT (PDO).
	PDEVICE_OBJECT												PDO;
	// Obsahuje INTERFACE NAME.
	UNICODE_STRING												InterfaceName;
	// LOCK, ktory sa pouziva pri detekcii ci je DEVICE_OBJECT mozne uvolnit z MEMORY.
	IO_REMOVE_LOCK												RemoveLock;
	// SUPPORT pre POWER MANAGEMENT a PNP DEVICES.
	GENERIC_EXTENSION*											PowerAndPNP;
	// Pocet otvorenych HANDLERS, ktore otvorili USER MODE PROCESSES.
	LONG														Handles;
	// QUEUE do ktorej sa ukladaju IRP.
	LIST_ENTRY													IRPQueue;
	// LOCK pouzivany pre pristup do IRP QUEUE.
	KSPIN_LOCK													IRPQueueLock;
	// Identifikator ci DEVICE je BUSY.
	BOOLEAN														DeviceBusy;
	// POINTER na IRP QUEUE typu DEVQUEUE.
	DEVQUEUE													DevQueue;
	// POINTER na STRUCTURE reprezentujucu CANCEL SAFE IRP QUEUE.
	IO_CSQ														CancelSafeIRPQueue;
	// POINTER na CANCEL SAFE IRP QUEUE LIST.
	LIST_ENTRY													CancelSafeIRPQueueList;
	// POINTER na CANCEL SAFE IRP QUEUE LOCK.
	KSPIN_LOCK													CancelSafeIRPQueueLock;
	// Pouziva sa v CancelAsynchronousIRPCompletionRoutine() a sluzi na zabranenie predcasneho uvolnenia IRP z MEMORY.
	PVOID														CurrentIRP;
	// Tiez sa pouziva v CancelAsynchronousIRPCompletionRoutine() a sluzi na zabranenie predcasneho uvolnenia IRP z MEMORY.
	LONG														CancelFlag;
	KEVENT														SingleCallEvent;
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;
//-------------------------------------------------------------------------------------------------------