//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
#include "MyDefines.h"
#include "TestPsCreateSystemThread.h"
#include "TestIoCreateSystemThread.h"
#include "TestExAllocatePool2.h"
#include "TestExAllocatePool3.h"
#include "TestSecurePool.h"
#include "TestGlobalOperatorsNewDelete.h"
#include "TestSpecificTypeOperatorsNewDelete.h"
#include "CLookasideEntry.h"
#include "TestOldLookasideListPagedMemory.h"
#include "TestOldLookasideListNonPagedMemory.h"
#include "TestNewLookasideList.h"
#include "TestSendDeviceControlIRPToReceivingDriver.h"
#include "TestSendInternalDeviceControlIRPToReceivingDriver.h"
#include "TestZwQuerySystemInformation.h"
#include "TestZwQueryInformationProcess.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_PS_CREATE_SYSTEM_THREAD CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_PS_CREATE_SYSTEM_THREAD,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_IO_CREATE_SYSTEM_THREAD CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IO_CREATE_SYSTEM_THREAD,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EX_ALLOCATE_POOL_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EX_ALLOCATE_POOL_2,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EX_ALLOCATE_POOL_3 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EX_ALLOCATE_POOL_3,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SECURE_POOL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SECURE_POOL,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_GLOBAL_OPERATORS_NEW_DELETE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_GLOBAL_OPERATORS_NEW_DELETE,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPECIFIC_TYPE_OPERATORS_NEW_DELETE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPECIFIC_TYPE_OPERATORS_NEW_DELETE,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_OLD_LOOKASIDE_LIST_PAGED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_OLD_LOOKASIDE_LIST_PAGED,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_OLD_LOOKASIDE_LIST_NON_PAGED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_OLD_LOOKASIDE_LIST_NON_PAGED,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_NEW_LOOKASIDE_LIST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_NEW_LOOKASIDE_LIST,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEND_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEND_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEND_INTERNAL_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEND_INTERNAL_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_ZW_QUERY_SYSTEM_INFORMATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_ZW_QUERY_SYSTEM_INFORMATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_ZW_QUERY_INFORMATION_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_ZW_QUERY_INFORMATION_PROCESS,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SNewLookasideListParameters
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		ULONG													Tag;
		LOOKASIDE_LIST_EX										Lookaside;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PAGED_LOOKASIDE_LIST											LookasidePaged;
NPAGED_LOOKASIDE_LIST											LookasideNonPaged;
// !!! LOOKASIDE LIST je sucastou STRUCTURE, aby sa dala demonstrovat funkcionalita MACRO [CONTAINING_RECORD()].
SNewLookasideListParameters										LookasideStructure;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
HANDLE															SecurePoolHandle=nullptr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! ALLOCATION FUNCTION pre OLD API.
PVOID MyLookasideAllocationFunction(POOL_TYPE PoolType, SIZE_T NumberOfBytes, ULONG Tag)
{
	POOL_FLAGS													Flags=0;

	if (PoolType==POOL_TYPE::PagedPool)
	{
		Flags|=POOL_FLAG_PAGED;
	}
	else if (PoolType==POOL_TYPE::NonPagedPool)
	{
		Flags|=POOL_FLAG_NON_PAGED;
	}

	PVOID														Buffer=ExAllocatePool2(Flags,NumberOfBytes,Tag);

	KdPrint(("!!!!!!!!!! ALLOCATION for OLD LOOKASIDE LIST - POOL TYPE [%X] BUFFER [%p] SIZE [%I64u].\n",PoolType,Buffer,NumberOfBytes));

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! DEALLOCATION FUNCTION pre OLD API.
VOID MyLookasideFreeFunction(PVOID Buffer)
{
	KdPrint(("!!!!!!!!!! DEALLOCATION for OLD LOOKASIDE LIST - BUFFER [%p].\n",Buffer));

	ExFreePoolWithTag(Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! ALLOCATION FUNCTION pre NEW API.
PVOID MyNewLookasideAllocationFunction(POOL_TYPE PoolType, SIZE_T NumberOfBytes, ULONG Tag, PLOOKASIDE_LIST_EX Lookaside)
{
	UNREFERENCED_PARAMETER(Lookaside);

	POOL_FLAGS													Flags=0;

	if (PoolType==POOL_TYPE::PagedPool)
	{
		Flags|=POOL_FLAG_PAGED;
	}
	else if (PoolType==POOL_TYPE::NonPagedPool)
	{
		Flags|=POOL_FLAG_NON_PAGED;
	}

	PVOID														Buffer=ExAllocatePool2(Flags,NumberOfBytes,Tag);

	KdPrint(("!!!!!!!!!! ALLOCATION for NEW LOOKASIDE LIST - POOL TYPE [%X] BUFFER [%p] SIZE [%I64u].\n",PoolType,Buffer,NumberOfBytes));

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! DEALLOCATION FUNCTION pre NEW API.
VOID MyNewLookasideFreeFunction(PVOID Buffer, PLOOKASIDE_LIST_EX Lookaside)
{
	// !!!!! Pomocou MACRO [CONTAINING_RECORD()] sa ziska POINTER na STRUCTURE, ktora obsahuje FIELD TYPE [LOOKASIDE_LIST_EX].
	SNewLookasideListParameters*								NewLookasideListParameters=CONTAINING_RECORD(Lookaside,SNewLookasideListParameters,Tag);
	ULONG														Tag=NewLookasideListParameters->Tag;

	KdPrint(("!!!!!!!!!! DEALLOCATION for NEW LOOKASIDE LIST - BUFFER [%p] TAG [%lu].\n",Buffer,Tag));

	ExFreePoolWithTag(Buffer,Tag);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineCreate(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineClose(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineDeviceControl(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	NTSTATUS													Status;
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
	
	if (Code==IOCTL_TEST_PS_CREATE_SYSTEM_THREAD)
	{
		Status=TestPsCreateSystemThread(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_IO_CREATE_SYSTEM_THREAD)
	{
		Status=TestIoCreateSystemThread(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_EX_ALLOCATE_POOL_2)
	{
		Status=TestExAllocatePool2(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_EX_ALLOCATE_POOL_3)
	{
		Status=TestExAllocatePool3(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_SECURE_POOL)
	{
		Status=TestSecurePool(DeviceObject,Irp,SecurePoolHandle);
	}
	else if (Code==IOCTL_TEST_GLOBAL_OPERATORS_NEW_DELETE)
	{
		Status=TestGlobalOperatorsNewDelete(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_SPECIFIC_TYPE_OPERATORS_NEW_DELETE)
	{
		Status=TestSpecificTypeOperatorsNewDelete(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_OLD_LOOKASIDE_LIST_PAGED)
	{
		Status=TestOldLookasideListPagedMemory(DeviceObject,Irp,&LookasidePaged);
	}
	else if (Code==IOCTL_TEST_OLD_LOOKASIDE_LIST_NON_PAGED)
	{
		Status=TestOldLookasideListNonPagedMemory(DeviceObject,Irp,&LookasideNonPaged);
	}
	else if (Code==IOCTL_TEST_NEW_LOOKASIDE_LIST)
	{
		Status=TestNewLookasideList(DeviceObject,Irp,&LookasideStructure.Lookaside);
	}
	else if (Code==IOCTL_TEST_SEND_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP)
	{
		Status=TestSendDeviceControlIRPToReceivingDriver(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_SEND_INTERNAL_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP)
	{
		Status=TestSendInternalDeviceControlIRPToReceivingDriver(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_ZW_QUERY_SYSTEM_INFORMATION)
	{
		Status=TestZwQuerySystemInformation(DeviceObject,Irp);
	}
	else if (Code==IOCTL_TEST_ZW_QUERY_INFORMATION_PROCESS)
	{
		Status=TestZwQueryInformationProcess(DeviceObject,Irp);
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to RECOGNIZE CODE [%lu] !!!\n",DeviceObject->DriverObject->DriverName,Code));

		Status=CHelpers::CompleteIRP(Irp,STATUS_INVALID_DEVICE_REQUEST,0);
	}

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	UNICODE_STRING												SymbolicLink;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

#ifdef USE_LOOKSIDE_LISTS
	// !!! Uvolni sa LOOKASIDE LIST pre PAGED MEMORY POOL.
	ExDeletePagedLookasideList(&LookasidePaged);

	// !!! Uvolni sa LOOKASIDE LIST pre NON-PAGED MEMORY POOL.
	ExDeleteNPagedLookasideList(&LookasideNonPaged);

	// !!! Uvolni sa LOOKASIDE LIST.
	ExDeleteLookasideListEx(&LookasideStructure.Lookaside);
#endif

#ifdef USE_SECURE_POOL
	ExDestroyPool(SecurePoolHandle);
	SecurePoolHandle=nullptr;
#endif

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(DriverObject->DeviceObject);

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	LookasideStructure.Tag=MY_TAG;

	DriverObject->DriverUnload=FunctionDriverUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchRoutineDeviceControl;

	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	NTSTATUS													Status;
	PDEVICE_OBJECT												DeviceObject;

#ifdef USE_LOOKSIDE_LISTS
	bool														OldLookasideListsInitialized=false;
#endif

	do
	{
		Status=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK [%wZ] with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,SymbolicLink,Status));
			break;
		}

#ifdef USE_SECURE_POOL
		// !!!!! Vytvori sa SECURE POOL.
		Status=ExCreatePool(POOL_CREATE_FLG_SECURE_POOL | POOL_CREATE_FLG_USE_GLOBAL_POOL,MY_TAG,nullptr,&SecurePoolHandle);
		
		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SECURE POOL with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}
#endif

#ifdef USE_LOOKSIDE_LISTS
		// !!! Vytvori sa LOOKASIDE LIST pre PAGED MEMORY POOL.
		// !!! NEPOUZIVAJU sa CUSTOM ALLOCATION FUNCTION a CUSTOM DEALLOCATION FUNCTION.
		ExInitializePagedLookasideList(&LookasidePaged,nullptr,nullptr,0,sizeof(CLookasideEntry),MY_TAG,0);

		// !!! Vytvori sa LOOKASIDE LIST pre NON-PAGED MEMORY POOL.
		// !!! POUZIVAJU sa CUSTOM ALLOCATION FUNCTION a CUSTOM DEALLOCATION FUNCTION.
		ExInitializeNPagedLookasideList(&LookasideNonPaged,MyLookasideAllocationFunction,MyLookasideFreeFunction,0,sizeof(CLookasideEntry),MY_TAG,0);

		OldLookasideListsInitialized=true;

		// !!! Vytvori sa LOOKASIDE LIST pre NEW API.
		// !!! POUZIVAJU sa CUSTOM ALLOCATION FUNCTION a CUSTOM DEALLOCATION FUNCTION.
		Status=ExInitializeLookasideListEx(&LookasideStructure.Lookaside,MyNewLookasideAllocationFunction,MyNewLookasideFreeFunction,POOL_TYPE::NonPagedPool,0,sizeof(CLookasideEntry),MY_TAG,0);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SECURE POOL with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}
#endif
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to START !!!\n",DriverObject->DriverName));

#ifdef USE_LOOKSIDE_LISTS
		if (OldLookasideListsInitialized==true)
		{
			// !!! Uvolni sa LOOKASIDE LIST pre PAGED MEMORY POOL.
			ExDeletePagedLookasideList(&LookasidePaged);

			// !!! Uvolni sa LOOKASIDE LIST pre NON-PAGED MEMORY POOL.
			ExDeleteNPagedLookasideList(&LookasideNonPaged);
		}
#endif

#ifdef USE_SECURE_POOL
		if (SecurePoolHandle!=nullptr)
		{
			ExDestroyPool(SecurePoolHandle);
			SecurePoolHandle=nullptr;
		}
#endif

		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------