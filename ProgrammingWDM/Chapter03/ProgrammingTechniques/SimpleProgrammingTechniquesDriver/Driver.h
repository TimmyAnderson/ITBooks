//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#define DRIVERNAME "!!! ProgrammingTechniquesDriver"
#define LDRIVERNAME L"!!! ProgrammingTechniquesDriver"
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
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;
//-------------------------------------------------------------------------------------------------------