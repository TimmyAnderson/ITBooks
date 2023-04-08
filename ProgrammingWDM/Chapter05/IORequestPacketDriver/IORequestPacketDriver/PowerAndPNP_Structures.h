//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <wdm.h>
#include "Defines.h"
//-------------------------------------------------------------------------------------------------------
#define GENERICAPI												extern "C" 
#define GENERIC_EXPORT											__declspec(dllexport) __stdcall
#define _IO_REMOVE_LOCK											_GENERIC_REMOVE_LOCK
#define IO_REMOVE_LOCK											GENERIC_REMOVE_LOCK
#define PIO_REMOVE_LOCK											PGENERIC_REMOVE_LOCK
// Register for AutoLaunch.
#define GENERIC_AUTOLAUNCH										0x00000001
// Device supports DeviceUsageTypePaging.
#define GENERIC_USAGE_PAGING									0x00000002
// Device supports DeviceUsageTypeDumpFile.
#define GENERIC_USAGE_DUMP										0x00000004
// Device supports DeviceUsageTypeHibernation.
#define GENERIC_USAGE_HIBERNATE									0x00000008
// Driver may cache asynchronous IOCTLs.
#define GENERIC_PENDING_IOCTLS									0x00000010
// Surprise removal of device is okay.
#define GENERIC_SURPRISE_REMOVAL_OK								0x00000020
// Device supports generic idle detection scheme.
#define GENERIC_IDLE_DETECT										0x00000040
// Mask to select client-controllable flags
#define GENERIC_CLIENT_FLAGS									0x0000007F
#define IOCTL_GET_POWERINFO										CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFF0, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SET_POWERINFO										CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFF1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IDLENOW											CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFF2, METHOD_NEITHER, FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
#undef IoInitializeRemoveLock
#define IoInitializeRemoveLock									GenericInitializeRemoveLock
#undef IoAcquireRemoveLock
#define IoAcquireRemoveLock										GenericAcquireRemoveLock
#undef IoReleaseRemoveLock
#define IoReleaseRemoveLock										GenericReleaseRemoveLock
#undef IoReleaseRemoveLockAndWait
#define IoReleaseRemoveLockAndWait								GenericReleaseRemoveLockAndWait
//-------------------------------------------------------------------------------------------------------
typedef VOID (__stdcall *PQNOTIFYFUNC)(PVOID);
typedef NTSTATUS (__stdcall *PSTART_DEVICE)(PDEVICE_OBJECT, PCM_PARTIAL_RESOURCE_LIST Raw, PCM_PARTIAL_RESOURCE_LIST Translated);
typedef VOID (__stdcall *PSTOP_DEVICE)(PDEVICE_OBJECT, BOOLEAN);
typedef VOID (__stdcall *PREMOVE_DEVICE)(PDEVICE_OBJECT);
typedef BOOLEAN (__stdcall *PQUERYFUNCTION)(PDEVICE_OBJECT);
typedef BOOLEAN (__stdcall *PQUERYPOWERFUNCTION)(PDEVICE_OBJECT, DEVICE_POWER_STATE, DEVICE_POWER_STATE);
typedef VOID (__stdcall *PCONTEXTFUNCTION)(PDEVICE_OBJECT, DEVICE_POWER_STATE, DEVICE_POWER_STATE, PVOID);
typedef VOID (__stdcall *PFLUSHIOFUNCTION)(PDEVICE_OBJECT, UCHAR, UCHAR, DEVICE_POWER_STATE, DEVICE_POWER_STATE);
typedef PIO_RESOURCE_REQUIREMENTS_LIST (__stdcall *PMODIFYRESOURCELIST)(PIO_RESOURCE_REQUIREMENTS_LIST);
typedef DEVICE_POWER_STATE (__stdcall *PGETDSTATEFUNCTION)(PDEVICE_OBJECT, SYSTEM_POWER_STATE, DEVICE_POWER_STATE);
//-------------------------------------------------------------------------------------------------------
// !!! ENUM urcuje PNP STATE v ktorom sa HW DEVICE nachadza.
enum DEVSTATE
{
	// Device stopped.
	// !!! Je to STATE do ktoreho sa nastavi DEVICE OBJECT po svojom vytvoreni vo CUSTOM FUNCTION AddDevice().
	STOPPED,
	// Started and working.
	// !!! Je to STATE kedy HW DEVICE je v beziacom stave a normalne vykonava IO OPERATIONS. Do toho STATE sa je mozne dostat z STATE [STOPPED] po prichode MINOR FUNCTION [IRP_MN_START_DEVICE]. Po prichode MINOR FUNCTION [IRP_MN_REMOVE_DEVICE] sa HW DEVICE ZASTAVI a DEVICE OBJECT je ODSTRANENY z MEMORY.
	WORKING,
	// Stop pending.
	// !!! Je to STATE kedy PLUG AND PLAY MANAGER poziada DEVICE OBJECT pomocou MINOR FUNCTION [IRP_MN_QUERY_STOP_DEVICE], aby sa pripravilo na zastavenie HW DEVICE. DEVICE OBJECT vsak aj po zastaveni OSTANE v MEMORY. STATE je mozne zmenit do STATE [WORKING] pri prichode MINOR FUNCTION [IRP_MN_CANCEL_STOP_DEVICE]. Naopak, po prichode MINOR FUNCTION [IRP_MN_STOP_DEVICE] sa DEVICE OBJECT dostane do STATE [STOPPED], no samotny DEVICE OBJECT OSTANE v MEMORY.
	PENDINGSTOP,
	// Remove pending.
	// !!! Je to STATE kedy PLUG AND PLAY MANAGER poziada DEVICE OBJECT pomocou MINOR FUNCTION [IRP_MN_QUERY_REMOVE_DEVICE], aby sa pripravilo na zastavenie HW DEVICE a ZAROVEN aj o ODSTRANENIE DEVICE OBJECT z MEMORY. STATE je mozne zmenit do STATE [WORKING] pri prichode MINOR FUNCTION [IRP_MN_CANCEL_REMOVE_DEVICE]. Naopak, po prichode MINOR FUNCTION [IRP_MN_REMOVE_DEVICE] sa DEVICE OBJECT ODSTRANI z MEMORY a HW DEVICE sa dostane do logickeho STATE [REMOVED].
	PENDINGREMOVE,
	// Removed by surprise.
	// !!! Je to STATE, ktory vznikne, ak PLUG AND PLAY MANAGER detekoval NEOCAKAVANE FYZICKE ODPOJENIE HW DEVICE od PC. Do tohto STATE je mozny prechod zo VSETKYCH OSTATNYCH STATES (okrem STATE [REMOVED]). Po prichode MINOR FUNCTION [IRP_MN_REMOVE_DEVICE] sa DEVICE OBJECT ODSTRANI z MEMORY a HW DEVICE sa dostane do logickeho STATE [REMOVED].
	SURPRISEREMOVED,
	// Removed.
	// !!! V tomto logickom STATE DEVICE OBJECT pre dany HW DEVICE NIE JE VYTVORENY. Je to pociatocny STATE.
	REMOVED,
};
//-------------------------------------------------------------------------------------------------------
typedef struct _GENERIC_REMOVE_LOCK
{
	// Reference count.
	LONG														MUsage;
	// True if removal is pending.
	BOOLEAN														MRemoving;
	// Event to wait on.
	KEVENT														MEventRemove;
}GENERIC_REMOVE_LOCK, *PGENERIC_REMOVE_LOCK;
//-------------------------------------------------------------------------------------------------------
// STRUCTURE repreznetujuca IRP QUEUE. Da sa pouzit na SAFE vykonavanie IRP CANCELLATION.
typedef struct _DEVQUEUE
{
	LIST_ENTRY													MHead;
	KSPIN_LOCK													MLock;
	PDRIVER_STARTIO												MStartIO;
	LONG														MStallCount;
	PIRP														MCurrentIRP;
	KEVENT														MEventStop;
	PQNOTIFYFUNC												MNotify;
	PVOID														MNotifyContext;
	NTSTATUS													MAbortStatus;
}DEVQUEUE, *PDEVQUEUE;
//-------------------------------------------------------------------------------------------------------
typedef struct _POWERINFO
{
	// Idle timeout in conservation mode.
	unsigned long												MConservation;
	// Idle timeout in performance mode.
	unsigned long												MPerformance;
	// TRUE if wakeup feature should be armed.
	unsigned char												MWakeup;
	// Device capable of waking system.
	unsigned char												MCanWake;
	// Device can be idled.
	unsigned char												MCanIdle;
	// Device is idle right now.
	unsigned char												MIdle;
}POWERINFO, *PPOWERINFO;
//-------------------------------------------------------------------------------------------------------
DEFINE_GUID(GUID_GENERIC_POWER, 0x894a7461, 0xa033, 0x11d2, 0x82, 0x1e, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0);
//-------------------------------------------------------------------------------------------------------
typedef struct _GENERIC_EXTENSION
{
	// Device object this extension belongs to.
	PDEVICE_OBJECT												MDeviceObject;
	// Next lower driver in same stack.
	PDEVICE_OBJECT												MLowerDeviceObject;
	// PDO.
	PDEVICE_OBJECT												MPDO;
	// Removal control locking structure.
	PGENERIC_REMOVE_LOCK										MRemoveLock;
	// Current state of device.
	DEVSTATE													MState;
	// State prior to removal query.
	DEVSTATE													MPrevState;
	// Current device power state.
	DEVICE_POWER_STATE											MDevicePower;
	// Current system power state.
	SYSTEM_POWER_STATE											MSystemPower;
	// Address of idle counter from idle detection registration.
	PULONG														MIdleCount;
	// Conservation timeout.
	ULONG														MCTO;
	// Performance timeout.
	ULONG														MPTO;
	// Idle state requested by minidriver.
	DEVICE_POWER_STATE											MIdleState;
	// Copy of most recent device capabilities.
	DEVICE_CAPABILITIES											MDeviceCaps;
	// !!! Pocet IRP QUEUE ARRAYS.
	// Number of queues.
	ULONG														MNumberQueues;
	// !!! POINTER na IRP QUEUE ARRAY.
	// IRP queues.
	PDEVQUEUE*													MQueues;
	// Routine to initialize device configuration.
	PSTART_DEVICE												MStartDevice;
	// Routine to release device configuration.
	PSTOP_DEVICE												MStopDevice;
	// Routine to remove device object.
	PREMOVE_DEVICE												MRemoveDevice;
	// Okay to stop device now.
	PQUERYFUNCTION												MOkayToStop;
	// Okay to remove device now.
	PQUERYFUNCTION												MOkayToRemove;
	// Encourage pending I/O to finish.
	PFLUSHIOFUNCTION											MFlushPendingIO;
	// Get D-state for given S-state.
	PGETDSTATEFUNCTION											MGetDevicePowerState;
	// Name for debugging messages.
	CHAR														MDebugName[64];
	// Flags from initialization call.
	ULONG														MFlags;
	// Number page files about which we've been notified.
	LONG														MNumberPageFiles;
	// Number of dump files.
	LONG														MNumberDumpFiles;
	// Number of hibernate files.
	LONG														MNumberHibernateFiles;
	// List of asynchronous IOCTLs.
	LIST_ENTRY													MPendingIoctlList;
	// Lock for pending IOCTLs.
	KSPIN_LOCK													MIoctlListLock;
	// Abort incoming IOCTLs if nonzero.
	NTSTATUS													MIoctlAbortStatus;
	// Okay to change device power.
	PQUERYPOWERFUNCTION											MQueryPower;
	// Routine to save device context.
	PCONTEXTFUNCTION											MSaveDeviceContext;
	// Routine to restore device context.
	PCONTEXTFUNCTION											MRestoreDeviceContext;
	// New PnP state bits.
	PNP_DEVICE_STATE											MPNPState;
	// Mask of changed state bits.
	PNP_DEVICE_STATE											MPNPStateMask;
	// Context restore very expensive from >= this power state.
	DEVICE_POWER_STATE											MPerfBoundary;
	// Outstanding WAIT_WAKE request (if any).
	PIRP														MWaitWakeIRP;
	// Non-zero when WAIT_WAKE has been cancelled.
	LONG														MWWCancelled;
	// Non-zero between PoRequestPowerIrp and WaitWaitCallback.
	LONG														MWWOutstanding;
	// Old power sequence numbers.
	POWER_SEQUENCE												MOldSequence;
	// For interlocking use of interface list.
	KEVENT														MIfLock;
	// List of registered device interfaces.
	LIST_ENTRY													MIfList;
	// Synch event used as a mutex for paging path notifications.
	KEVENT														MEventPagingPath;
	// We should touch hardware at stop-device time.
	BOOLEAN														MHardwareWorking;
	// Device wakeup feature is enabled.
	BOOLEAN														MWakeupEnabled;
	// Power management has stalled IRP queue.
	BOOLEAN														MStalledForPower;
	// Capabilities have been gotten already.
	BOOLEAN														MGotCapabilities;
	// !!! EXTENSION. Je to CALLBACK ROUTINE, ktora umoznuje modifikovat RESOURCES, ktore DRIVER pozaduje.
	// !!!!! CALLBACK ROUTINE ak NEPOTREBUJE modifikovat RESOURCES, tak MUSI vratit VSTUPNY PARAMETER.
	// !!!!! CALLBACK ROUTINE ak POTREBUJE modifikovat RESOURCES, tak MUSI UVOLNIT POINTER na ktory odkazuje VSTUPNY PARAMETER a ALOKOVAT NOVY MEMORY BLOCK v ktorom budu MODIFIKOVANE RESOURCES.
	PMODIFYRESOURCELIST											MModifyResources;
}GENERIC_EXTENSION;
//-------------------------------------------------------------------------------------------------------
typedef struct _INTERFACE_RECORD
{
	// Linking fields.
	LIST_ENTRY													MList;
	// GUID for registered interface.
	GUID														MGUID;
	// Symbolic link name.
	UNICODE_STRING												MLinkName;
	// True if interface currently enabled.
	BOOLEAN														MEnabled;
}INTERFACE_RECORD, *PINTERFACE_RECORD;
//-------------------------------------------------------------------------------------------------------
struct _POWERINFO;
//-------------------------------------------------------------------------------------------------------
// Opaque.
struct _GENERIC_EXTENSION;
//-------------------------------------------------------------------------------------------------------
typedef struct _GENERIC_EXTENSION* PGENERIC_EXTENSION;
//-------------------------------------------------------------------------------------------------------
struct QSIO
{
	PDEVQUEUE													MDeviceQueue;
	PDRIVER_STARTIO												MStartIO;
};
//-------------------------------------------------------------------------------------------------------
typedef struct _GENERIC_INIT_STRUCT
{
	// Size of this structure.
	ULONG														MSize;
	// The device object being registered.
	PDEVICE_OBJECT												MDeviceObject;
	// The PDO below this device object.
	PDEVICE_OBJECT												MPDO;
	// Immediately lower device object.
	PDEVICE_OBJECT												MLDO;
	// Address of remove lock in containing device extension (optional).
	PGENERIC_REMOVE_LOCK										MRemoveLock;
	// Address of queue object for read/write IRPs (optional).
	PDEVQUEUE													MDeviceQueue;
	// Start I/O routine for reads & writes (required only if DeviceQueue non-NULL).
	PDRIVER_STARTIO												MStartIO;
	// Routine to initialize device configuration.
	PSTART_DEVICE												MStartDevice;
	// Routine to release device configuration.
	PSTOP_DEVICE												MStopDevice;
	// Routine to remove device object.
	PREMOVE_DEVICE												MRemoveDevice;
	// Name to use in debug messages.
	UNICODE_STRING												MDebugName;
	// Option flags.
	ULONG														MFlags;
	// Routine to decide whether it's okay to stop device now (optional).
	PQUERYFUNCTION												MOkayToStop;
	// Routine to decide whether it's okay to remove device now (optional).
	PQUERYFUNCTION												MOkayToRemove;
	// Routine to decide whether a proposed device power change is okay (optional).
	PQUERYPOWERFUNCTION											MQueryPower;
	// Routine to save device context before power down (optional).
	PCONTEXTFUNCTION											MSaveDeviceContext;
	// Routine to restore device context after power up (optional).
	PCONTEXTFUNCTION											MRestoreDeviceContext;
	// (Optional) Power state below which context restore inordinately expensive.
	DEVICE_POWER_STATE											MPerfBoundary;
	// Number of device queues in DeviceQueues array (1.3).
	ULONG														MNumberOfQueues;
	// Encourage pending I/O to finish (optional) (2.0).
	PFLUSHIOFUNCTION											MFlushPendingIO;
	// Get D-state for given S-State (optional) (1.10).
	PGETDSTATEFUNCTION											MGetDevicePowerState;
	// Reserved for future use (1.3).
	ULONG														MReserved[6];
	// (Optional) NumberOfQueues pointers to DEVQUEUE objects and their corresponding StartIo functions.
	struct QSIO													MQueues[1];
	// !!! EXTENSION. Je to CALLBACK ROUTINE, ktora umoznuje modifikovat RESOURCES, ktore DRIVER pozaduje.
	// !!!!! CALLBACK ROUTINE ak NEPOTREBUJE modifikovat RESOURCES, tak MUSI vratit VSTUPNY PARAMETER.
	// !!!!! CALLBACK ROUTINE ak POTREBUJE modifikovat RESOURCES, tak MUSI UVOLNIT POINTER na ktory odkazuje VSTUPNY PARAMETER a ALOKOVAT NOVY MEMORY BLOCK v ktorom budu MODIFIKOVANE RESOURCES.
	PMODIFYRESOURCELIST											MModifyResources;
}GENERIC_INIT_STRUCT, *PGENERIC_INIT_STRUCT;
//-------------------------------------------------------------------------------------------------------
// Enumeration for "wf" argument to GenericWakeupControl.
enum WAKEFUNCTION
{
	// Enable system wakeup.
	EnableWakeup,
	// Disable system wakeup.
	DisableWakeup,
	// Request or cancel WAIT_WAKE IRP, as appropriate.
	ManageWaitWake,
	// Unconditionally cancel WAIT_WAKE.
	CancelWaitWake,
	// Test whether WAIT_WAKE enabled (ver 1.3).
	TestWaitWake,
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
GENERICAPI VOID GENERIC_EXPORT InitializeQueue(PDEVQUEUE PDQ, PDRIVER_STARTIO StartIo);
GENERICAPI VOID GENERIC_EXPORT StartPacket(PDEVQUEUE PDQ, PDEVICE_OBJECT FDO, PIRP IRP, PDRIVER_CANCEL Cancel);
GENERICAPI PIRP GENERIC_EXPORT StartNextPacket(PDEVQUEUE PDQ, PDEVICE_OBJECT FDO);
_IRQL_raises_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_cancel_spin_lock_)
GENERICAPI VOID GENERIC_EXPORT CancelRequest(PDEVQUEUE PDQ, PIRP IRP);
GENERICAPI VOID GENERIC_EXPORT CleanupRequests(PDEVQUEUE PDQ, PFILE_OBJECT FOP, NTSTATUS Status);
GENERICAPI VOID GENERIC_EXPORT StallRequests(PDEVQUEUE PDQ);
GENERICAPI VOID GENERIC_EXPORT RestartRequests(PDEVQUEUE PDQ, PDEVICE_OBJECT FDO);
GENERICAPI PIRP GENERIC_EXPORT GetCurrentIRP(PDEVQUEUE PDQ);
GENERICAPI BOOLEAN GENERIC_EXPORT CheckBusyAndStall(PDEVQUEUE PDQ);
GENERICAPI VOID GENERIC_EXPORT WaitForCurrentIrp(PDEVQUEUE PDQ);
GENERICAPI VOID GENERIC_EXPORT AbortRequests(PDEVQUEUE PDQ, NTSTATUS Status);
GENERICAPI VOID GENERIC_EXPORT AllowRequests(PDEVQUEUE PDQ);
GENERICAPI NTSTATUS GENERIC_EXPORT AreRequestsBeingAborted(PDEVQUEUE PDQ);
GENERICAPI NTSTATUS GENERIC_EXPORT StallRequestsAndNotify(PDEVQUEUE PDQ, PQNOTIFYFUNC Notify, PVOID Context);
GENERICAPI VOID GENERIC_EXPORT CleanupAllRequests(PDEVQUEUE* Queue, ULONG NQ, PFILE_OBJECT FOP, NTSTATUS Status);
GENERICAPI VOID GENERIC_EXPORT StallAllRequests(PDEVQUEUE* Queue, ULONG NQ);
GENERICAPI VOID GENERIC_EXPORT RestartAllRequests(PDEVQUEUE* Queue, ULONG NQ, PDEVICE_OBJECT FDO);
GENERICAPI BOOLEAN GENERIC_EXPORT CheckAnyBusyAndStall(PDEVQUEUE* Queue, ULONG NQ, PDEVICE_OBJECT FDO);
GENERICAPI VOID GENERIC_EXPORT WaitForCurrentIRPS(PDEVQUEUE* Queue, ULONG NQ);
GENERICAPI VOID GENERIC_EXPORT AbortAllRequests(PDEVQUEUE* Queue, ULONG NQ, NTSTATUS Status);
GENERICAPI VOID GENERIC_EXPORT AllowAllRequests(PDEVQUEUE* Queue, ULONG NQ);
GENERICAPI NTSTATUS GENERIC_EXPORT StallAllRequestsAndNotify(PDEVQUEUE* Queue, ULONG NQ, PQNOTIFYFUNC Notify, PVOID Context);
GENERICAPI VOID GENERIC_EXPORT GenericInitializeRemoveLock(PGENERIC_REMOVE_LOCK Lock, ULONG Tag, ULONG Minutes, ULONG MaxCount);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericAcquireRemoveLock(PGENERIC_REMOVE_LOCK Lock, PVOID Tag);
GENERICAPI VOID GENERIC_EXPORT GenericReleaseRemoveLock(PGENERIC_REMOVE_LOCK Lock, PVOID Tag);
GENERICAPI VOID GENERIC_EXPORT GenericReleaseRemoveLockAndWait(PGENERIC_REMOVE_LOCK Lock, PVOID Tag);
GENERICAPI VOID GENERIC_EXPORT CleanupGenericExtension(PGENERIC_EXTENSION PDX);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericCacheControlRequest(PGENERIC_EXTENSION PDX, PIRP IRP, PIRP* PIRP);
GENERICAPI VOID GENERIC_EXPORT GenericCleanupAllRequests(PGENERIC_EXTENSION PDX, PFILE_OBJECT FOP, NTSTATUS Status);
GENERICAPI VOID GENERIC_EXPORT GenericCleanupControlRequests(PGENERIC_EXTENSION PDX, NTSTATUS Status, PFILE_OBJECT FOP);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericDeregisterInterface(PGENERIC_EXTENSION PDX, const GUID* GUID);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericDispatchPNP(PGENERIC_EXTENSION, PIRP);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericDispatchPower(PGENERIC_EXTENSION, PIRP);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericEnableInterface(PGENERIC_EXTENSION PDX, const GUID* GUID, BOOLEAN Enable);
GENERICAPI PDEVICE_CAPABILITIES GENERIC_EXPORT GenericGetDeviceCapabilities(PGENERIC_EXTENSION PDX);
GENERICAPI PVOID GENERIC_EXPORT GenericGetSystemAddressForMDL(PMDL MDL);
GENERICAPI ULONG GENERIC_EXPORT GenericGetVersion(void);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericHandlePowerIoctl(PGENERIC_EXTENSION PDX, PIRP IRP);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericIdleDevice(PGENERIC_EXTENSION PDX, DEVICE_POWER_STATE State, BOOLEAN Wait=FALSE);
GENERICAPI VOID GENERIC_EXPORT GenericMarkDeviceBusy(PGENERIC_EXTENSION);
GENERICAPI VOID GENERIC_EXPORT GenericRegisterForIdleDetection(PGENERIC_EXTENSION, ULONG ConservationTimeout, ULONG PerformanceTimeout, DEVICE_POWER_STATE State);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericRegisterInterface(PGENERIC_EXTENSION PDX, const GUID* GUID);
GENERICAPI VOID GENERIC_EXPORT GenericSaveRestoreComplete(PVOID Context);
GENERICAPI VOID GENERIC_EXPORT GenericSetDeviceState(PGENERIC_EXTENSION PDX, PNP_DEVICE_STATE PNPState);
GENERICAPI PIRP GENERIC_EXPORT GenericUncacheControlRequest(PGENERIC_EXTENSION PDX, PIRP* PIRP);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericWakeupControl(PGENERIC_EXTENSION PDX, enum WAKEFUNCTION WF);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericWakeupFromIdle(PGENERIC_EXTENSION PDX, BOOLEAN Wait=FALSE);
GENERICAPI ULONG GENERIC_EXPORT GetSizeofGenericExtension(VOID);
GENERICAPI NTSTATUS GENERIC_EXPORT InitializeGenericExtension(PGENERIC_EXTENSION, PGENERIC_INIT_STRUCT);
//-------------------------------------------------------------------------------------------------------
VOID AbortPendingIoctls(PGENERIC_EXTENSION PDX, NTSTATUS Status);
VOID AdjustSpecialFileCounter(PGENERIC_EXTENSION PDX, BOOLEAN InPath, PLONG Counter);
NTSTATUS CompleteRequest(PIRP IRP, NTSTATUS Status, ULONG_PTR Info);
NTSTATUS CompleteRequest(PIRP IRP, NTSTATUS Status);
NTSTATUS ForwardAndWait(PGENERIC_EXTENSION PDX, PIRP IRP);
NTSTATUS GetPowerInfoFromRegistry(PGENERIC_EXTENSION PDX, _POWERINFO* PIP);
NTSTATUS ImplementPowerPolicy(PGENERIC_EXTENSION PDX, _POWERINFO* PIP);
BOOLEAN OkayToRemove(PGENERIC_EXTENSION PDX);
BOOLEAN OkayToStop(PGENERIC_EXTENSION PDX);
NTSTATUS SendDeviceSetPower(PGENERIC_EXTENSION PDX, DEVICE_POWER_STATE State, BOOLEAN Wait=FALSE);
NTSTATUS WritePowerInfoToRegistry(PGENERIC_EXTENSION PDX, _POWERINFO* PIP);
//-------------------------------------------------------------------------------------------------------
VOID DeregisterAllInterfaces(PGENERIC_EXTENSION PDX);
//-------------------------------------------------------------------------------------------------------