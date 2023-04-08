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
	// INTERRUPT OBJECT.
	PKINTERRUPT													InterruptObject;
	LONG														InterruptCounter;
	// IRP QUEUE typu DEVQUEUE.
	DEVQUEUE													DevQueue;
	// POINTER na DMA ADAPTER OBJECT.
	PDMA_ADAPTER												DMAAddapter;
	// Pocet DMA MAP REGISTERS. Urcuje pocet MEMORY PAGES, ktore je mozne preniest v 1 STAGE. Do 1 MAP REGISTER je mozne ulozit ADDRESS 1 MEMORY PAGE.
	ULONG														DMANumberOfMapRegisters;
	// Pocet prave alokovanych DMA MAP REGISTERS.
	ULONG														DMANumberOfAllocatedMapRegisters;
	// Pocet doteraz prenesenych BYTES v aktualnom TRANSFER.
	ULONG														DMANumberOfAlreadyTransferedBytes;
	// Pocet BYTES, ktore sa maju preniest v tejto STAGE. Pocet STAGES v jednom TRANSFER moze byt aj VYSSI ako 1, ak pocet DMA REGISTERS nestaci na prenos vsetkych BYTES v jednej STAGE.
	ULONG														DMANumberOfBytesToTransferForCurrentStage;
	// Pocet BYTES, ktore sa preniest v aktualnom TRANSFER.
	ULONG														DMANumberOfBytesRemainingToTransfer;
	// Virtalna ADDRESS pre aktualnu STAGE.
	PVOID														DMAVirtualAddressForCurrentStage;
	// MAP REGISTER ADDRESS BASE pre aktualnu STAGE.
	PVOID														DMAMapRegisterAddressBaseForCurrentStage;
	// !!!!! Pomocny FLAG urcujuci ci INTERRUPT moze simulovat koniec DMA prenosu. Sluzi iba ako POISTKA, aby INTERRUPT nevznikol SKOR ako je simulacia DMA TRANSFER pripravena. V realnom HW DEVICE by tento FLAG bol ZBYTOCNY, pretoze HW DEVICE hodi INTERRUPT az ked DMA TRANSFER zacal a je skutocne aj skonceny.
	bool														ReadyForDMAInterrupt;
	// Velkost READ BUFFER.
	size_t														ReadBufferSize;
	// READ BUFFER obsahuje data, ktore sa pomocou vracaju ako reakcia na [IRP_MJ_READ].
	PCHAR														ReadBuffer;
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;
//-------------------------------------------------------------------------------------------------------