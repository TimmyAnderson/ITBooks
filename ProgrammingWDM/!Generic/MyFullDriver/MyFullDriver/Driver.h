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
	// IRP QUEUE typu DEVQUEUE.
	DEVQUEUE													DevQueue;
	// HANDLE na THREAD.
	PKTHREAD													Thread;
	// EXIT EVENT pouzivany na signalizaciu ukoncenia THREAD.
	KEVENT														ThreadExitEvent;
	// EXIT EVENT pouzivany na signalizaciu prichodu noveho IRP do THREAD.
	KEVENT														ThreadIRPEvent;
	// INTERRUPT OBJECT.
	PKINTERRUPT													InterruptObject;
	LONG														InterruptCounter;
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;
//-------------------------------------------------------------------------------------------------------