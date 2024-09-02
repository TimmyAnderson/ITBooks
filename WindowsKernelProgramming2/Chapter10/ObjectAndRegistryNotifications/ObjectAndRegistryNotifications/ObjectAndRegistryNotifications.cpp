//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
#include "TestReadObjectNotificationCounters.h"
#include "TestReadRegistryNotificationCounters.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER, ktory pouziva OBJECT NOTIFICATION MUSI mat v PE FILE povoleny FLAG [IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY]. To sa robi pridanim COMMAND [/integritycheck] do LINKER COMMAND LINE.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//#define														OBJECT_NOTIFICATION_LOG
//#define														OBJECT_NOTIFICATION_LOG_INTERNALS
//#define														REGISTRY_NOTIFICATION_LOG_INTERNALS
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_READ_OBJECT_NOTIFICATION_COUNTERS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_READ_OBJECT_NOTIFICATION_COUNTERS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_READ_REGISTRY_NOTIFICATION_COUNTERS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_READ_REGISTRY_NOTIFICATION_COUNTERS,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PVOID															ObjectNotificationRegistrationHandle=nullptr;
LARGE_INTEGER													RegistryNotificationRegistrationCookie{0};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
volatile LONG64													NumberOfPreProcessHandleCreatedCalled;
volatile LONG64													NumberOfPreProcessHandleDuplicatedCalled;
volatile LONG64													NumberOfPostProcessHandleCreatedCalled;
volatile LONG64													NumberOfPostProcessHandleDuplicatedCalled;
volatile LONG64													NumberOfPreThreadHandleCreatedCalled;
volatile LONG64													NumberOfPreThreadHandleDuplicatedCalled;
volatile LONG64													NumberOfPostThreadHandleCreatedCalled;
volatile LONG64													NumberOfPostThreadHandleDuplicatedCalled;
//----------------------------------------------------------------------------------------------------------------------
volatile LONG64													NumberOfPreCreateKeyCalled;
volatile LONG64													NumberOfPostCreateKeyCalled;
volatile LONG64													NumberOfPreCreateKeyExCalled;
volatile LONG64													NumberOfPostCreateKeyExCalled;
volatile LONG64													NumberOfPreDeleteValueKeyCalled;
volatile LONG64													NumberOfPostDeleteValueKeyCalled;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const char* GetObjectTypeName(POBJECT_TYPE ObjectType)
{
	if (ObjectType==(*PsProcessType))
	{
		static char												Text[]{"PROCESS"};

		return(Text);
	}
	if (ObjectType==(*PsThreadType))
	{
		static char												Text[]{"THREAD"};

		return(Text);
	}
	if (ObjectType==(*ExDesktopObjectType))
	{
		static char												Text[]{"DESKTOP"};

		return(Text);
	}
	else
	{
		static char												Text[]{"UNKNOWN"};

		return(Text);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OB_PREOP_CALLBACK_STATUS ProcessObjectPreOperationCallback(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION OperationInformation)
{
	UNREFERENCED_PARAMETER(RegistrationContext);

#ifdef OBJECT_NOTIFICATION_LOG
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PROCESS PRE OPERATION CALLBACK [%s] is EXECUTING !!!\n",FunctionName));
#endif

	if (OperationInformation->Operation==OB_OPERATION_HANDLE_CREATE)
	{
		InterlockedIncrement64(&NumberOfPreProcessHandleCreatedCalled);

#ifdef OBJECT_NOTIFICATION_LOG_INTERNALS
		PVOID													Object=OperationInformation->Object;
		POBJECT_TYPE											ObjectType=OperationInformation->ObjectType;
		const char*												ObjectTypeString=GetObjectTypeName(ObjectType);
		ACCESS_MASK												OriginalDesiredAccess=OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess;

		// !!! DRIVER moze ZMENIT VALUE [OB_PRE_CREATE_HANDLE_INFORMATION::DesiredAccess].

		KdPrint(("!!!!! PROCESS - PRE OPERATION CALLBACK - CREATE - OBJECT [%p] OBJECT TYPE [%s] DESIRED ACCESS [%lX].\n",Object,ObjectTypeString,OriginalDesiredAccess));
#endif
	}
	else if (OperationInformation->Operation==OB_OPERATION_HANDLE_DUPLICATE)
	{
		InterlockedIncrement64(&NumberOfPreProcessHandleDuplicatedCalled);

#ifdef OBJECT_NOTIFICATION_LOG_INTERNALS
		PVOID													Object=OperationInformation->Object;
		POBJECT_TYPE											ObjectType=OperationInformation->ObjectType;
		const char*												ObjectTypeString=GetObjectTypeName(ObjectType);
		ACCESS_MASK												OriginalDesiredAccess=OperationInformation->Parameters->DuplicateHandleInformation.OriginalDesiredAccess;

		// !!! DRIVER moze ZMENIT VALUE [OB_PRE_DUPLICATE_HANDLE_INFORMATION::DesiredAccess].

		KdPrint(("!!!!! PROCESS - PRE OPERATION CALLBACK - DUPLICATE - OBJECT [%p] OBJECT TYPE [%s] DESIRED ACCESS [%lX].\n",Object,ObjectTypeString,OriginalDesiredAccess));
#endif
	}

#ifdef OBJECT_NOTIFICATION_LOG
	KdPrint(("!!!!! PROCESS PRE OPERATION CALLBACK [%s] is EXECUTED !!!\n",FunctionName));
#endif

	return(OB_PREOP_CALLBACK_STATUS::OB_PREOP_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ProcessObjectPostOperationCallback(PVOID RegistrationContext, POB_POST_OPERATION_INFORMATION OperationInformation)
{
	UNREFERENCED_PARAMETER(RegistrationContext);

#ifdef OBJECT_NOTIFICATION_LOG
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PROCESS POST OPERATION CALLBACK [%s] is EXECUTING !!!\n",FunctionName));
#endif

	if (OperationInformation->Operation==OB_OPERATION_HANDLE_CREATE)
	{
		InterlockedIncrement64(&NumberOfPostProcessHandleCreatedCalled);

#ifdef OBJECT_NOTIFICATION_LOG_INTERNALS
		PVOID													Object=OperationInformation->Object;
		POBJECT_TYPE											ObjectType=OperationInformation->ObjectType;
		const char*												ObjectTypeString=GetObjectTypeName(ObjectType);
		NTSTATUS												ReturnStatus=OperationInformation->ReturnStatus;
		ACCESS_MASK												GrantedAccess=OperationInformation->Parameters->CreateHandleInformation.GrantedAccess;

		// !!! DRIVER moze ZMENIT VALUE [OB_POST_CREATE_HANDLE_INFORMATION::DesiredAccess].

		KdPrint(("!!!!! PROCESS - POST OPERATION CALLBACK - CREATE - OBJECT [%p] OBJECT TYPE [%s] RETURN STATUS [%lX] GRANTED ACCESS [%lX].\n",Object,ObjectTypeString,ReturnStatus,GrantedAccess));
#endif
	}
	else if (OperationInformation->Operation==OB_OPERATION_HANDLE_DUPLICATE)
	{
		InterlockedIncrement64(&NumberOfPostProcessHandleDuplicatedCalled);

#ifdef OBJECT_NOTIFICATION_LOG_INTERNALS
		PVOID													Object=OperationInformation->Object;
		POBJECT_TYPE											ObjectType=OperationInformation->ObjectType;
		const char*												ObjectTypeString=GetObjectTypeName(ObjectType);
		NTSTATUS												ReturnStatus=OperationInformation->ReturnStatus;
		ACCESS_MASK												GrantedAccess=OperationInformation->Parameters->DuplicateHandleInformation.GrantedAccess;

		// !!! DRIVER moze ZMENIT VALUE [OB_POST_DUPLICATE_HANDLE_INFORMATION::DesiredAccess].

		KdPrint(("!!!!! PROCESS - POST OPERATION CALLBACK - DUPLICATE - OBJECT [%p] OBJECT TYPE [%s] RETURN STATUS [%lX] GRANTED ACCESS [%lX].\n",Object,ObjectTypeString,ReturnStatus,GrantedAccess));
#endif
	}

#ifdef OBJECT_NOTIFICATION_LOG
	KdPrint(("!!!!! PROCESS POST OPERATION CALLBACK [%s] is EXECUTED !!!\n",FunctionName));
#endif
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS ProcessRegistryOperationCallback(PVOID CallbackContext, PVOID Argument1, PVOID Argument2)
{
	UNREFERENCED_PARAMETER(CallbackContext);

#ifndef REGISTRY_NOTIFICATION_LOG_INTERNALS
	UNREFERENCED_PARAMETER(Argument2);
#endif

	REG_NOTIFY_CLASS											OperationType=(REG_NOTIFY_CLASS)reinterpret_cast<ULONG_PTR>(Argument1);

	if (OperationType==REG_NOTIFY_CLASS::RegNtPreCreateKey)
	{
		InterlockedIncrement64(&NumberOfPreCreateKeyCalled);

#ifdef REGISTRY_NOTIFICATION_LOG_INTERNALS
		PREG_PRE_CREATE_KEY_INFORMATION							OperationData=static_cast<PREG_PRE_CREATE_KEY_INFORMATION>(Argument2);

		KdPrint(("!!!!! OPERATION [PRE CREATE KEY] EXECUTED. COMPLETE NAME [%wZ].\n",*(OperationData->CompleteName)));
#endif
	}
	else if (OperationType==REG_NOTIFY_CLASS::RegNtPostCreateKey)
	{
		InterlockedIncrement64(&NumberOfPostCreateKeyCalled);

#ifdef REGISTRY_NOTIFICATION_LOG_INTERNALS
		PREG_POST_CREATE_KEY_INFORMATION						OperationData=static_cast<PREG_POST_CREATE_KEY_INFORMATION>(Argument2);

		KdPrint(("!!!!! OPERATION [POST CREATE KEY] EXECUTED. COMPLETE NAME [%wZ] STATUS [%lX].\n",*(OperationData->CompleteName),OperationData->Status));
#endif
	}
	else if (OperationType==REG_NOTIFY_CLASS::RegNtPreCreateKeyEx)
	{
		InterlockedIncrement64(&NumberOfPreCreateKeyExCalled);

#ifdef REGISTRY_NOTIFICATION_LOG_INTERNALS
		PREG_CREATE_KEY_INFORMATION_V1							OperationData=static_cast<PREG_CREATE_KEY_INFORMATION_V1>(Argument2);
		
		KdPrint(("!!!!! OPERATION [PRE CREATE KEY EX] EXECUTED. COMPLETE NAME [%wZ].\n",*(OperationData->CompleteName)));
#endif
	}
	else if (OperationType==REG_NOTIFY_CLASS::RegNtPostCreateKeyEx)
	{
		InterlockedIncrement64(&NumberOfPostCreateKeyExCalled);

#ifdef REGISTRY_NOTIFICATION_LOG_INTERNALS
		PREG_POST_OPERATION_INFORMATION							OperationData=static_cast<PREG_POST_OPERATION_INFORMATION>(Argument2);
		PREG_CREATE_KEY_INFORMATION_V1							PreInformation=static_cast<PREG_CREATE_KEY_INFORMATION_V1>(OperationData->PreInformation);

		KdPrint(("!!!!! OPERATION [POST CREATE KEY EX] EXECUTED. COMPLETE NAME [%wZ] STATUS [%lX].\n",*(PreInformation->CompleteName),OperationData->ReturnStatus));
#endif
	}
	else if (OperationType==REG_NOTIFY_CLASS::RegNtPreDeleteValueKey)
	{
		InterlockedIncrement64(&NumberOfPreDeleteValueKeyCalled);

#ifdef REGISTRY_NOTIFICATION_LOG_INTERNALS
		PREG_DELETE_VALUE_KEY_INFORMATION						OperationData=static_cast<PREG_DELETE_VALUE_KEY_INFORMATION>(Argument2);
		PCUNICODE_STRING										ObjectName;

		// !!! Ziska sa REGISTRY OBJECT NAME pre dany REGISTRY OBJECT.
		NTSTATUS												Status=CmCallbackGetKeyObjectIDEx(&RegistryNotificationRegistrationCookie,OperationData->Object,nullptr,&ObjectName,0);

		if (NT_SUCCESS(Status)!=false)
		{
			KdPrint(("!!!!! OPERATION [PRE DELETE VALUE KEY] EXECUTED. OBJECT NAME [%wZ] VALUE NAME [%wZ].\n",*(ObjectName),*(OperationData->ValueName)));

			// !!! Uvolni sa REGISTRY OBJECT NAME.
			CmCallbackReleaseKeyObjectIDEx(ObjectName);
		}
		else
		{
			KdPrint(("!!!!!!!!!! OPERATION [PRE DELETE VALUE KEY] FAILED to GET REGISTRY KEY NAME with ERROR CODE [%lX] !!!\n",Status));

			KdPrint(("!!!!! OPERATION [PRE DELETE VALUE KEY] EXECUTED. VALUE NAME [%wZ].\n",*(OperationData->ValueName)));
		}
#endif
	}
	else if (OperationType==REG_NOTIFY_CLASS::RegNtPostDeleteValueKey)
	{
		InterlockedIncrement64(&NumberOfPostDeleteValueKeyCalled);

#ifdef REGISTRY_NOTIFICATION_LOG_INTERNALS
		PREG_POST_OPERATION_INFORMATION							OperationData=static_cast<PREG_POST_OPERATION_INFORMATION>(Argument2);
		PREG_DELETE_VALUE_KEY_INFORMATION						PreInformation=static_cast<PREG_DELETE_VALUE_KEY_INFORMATION>(OperationData->PreInformation);
		PCUNICODE_STRING										ObjectName;

		// !!! Ziska sa REGISTRY OBJECT NAME pre dany REGISTRY OBJECT.
		NTSTATUS												Status=CmCallbackGetKeyObjectIDEx(&RegistryNotificationRegistrationCookie,OperationData->Object,nullptr,&ObjectName,0);

		if (NT_SUCCESS(Status)!=false)
		{
			KdPrint(("!!!!! OPERATION [POST DELETE VALUE KEY] EXECUTED. OBJECT NAME [%wZ] VALUE NAME [%wZ] STATUS [%lX].\n",*(ObjectName),*(PreInformation->ValueName),OperationData->ReturnStatus));

			// !!! Uvolni sa REGISTRY OBJECT NAME.
			CmCallbackReleaseKeyObjectIDEx(ObjectName);
		}
		else
		{
			KdPrint(("!!!!!!!!!! OPERATION [POST DELETE VALUE KEY] FAILED to GET REGISTRY KEY NAME with ERROR CODE [%lX] !!!\n",Status));

			KdPrint(("!!!!! OPERATION [POST DELETE VALUE KEY] EXECUTED. VALUE NAME [%wZ] STATUS [%lX].\n",*(PreInformation->ValueName),OperationData->ReturnStatus));
		}
#endif
	}

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OB_PREOP_CALLBACK_STATUS ThreadObjectPreOperationCallback(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION OperationInformation)
{
	UNREFERENCED_PARAMETER(RegistrationContext);

#ifdef OBJECT_NOTIFICATION_LOG
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! THREAD PRE OPERATION CALLBACK [%s] is EXECUTING !!!\n",FunctionName));
#endif

	if (OperationInformation->Operation==OB_OPERATION_HANDLE_CREATE)
	{
		InterlockedIncrement64(&NumberOfPreThreadHandleCreatedCalled);

#ifdef OBJECT_NOTIFICATION_LOG_INTERNALS
		PVOID													Object=OperationInformation->Object;
		POBJECT_TYPE											ObjectType=OperationInformation->ObjectType;
		const char*												ObjectTypeString=GetObjectTypeName(ObjectType);
		ACCESS_MASK												OriginalDesiredAccess=OperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess;

		// !!! DRIVER moze ZMENIT VALUE [OB_PRE_CREATE_HANDLE_INFORMATION::DesiredAccess].

		KdPrint(("!!!!! THREAD - PRE OPERATION CALLBACK - CREATE - OBJECT [%p] OBJECT TYPE [%s] DESIRED ACCESS [%lX].\n",Object,ObjectTypeString,OriginalDesiredAccess));
#endif
	}
	else if (OperationInformation->Operation==OB_OPERATION_HANDLE_DUPLICATE)
	{
		InterlockedIncrement64(&NumberOfPreThreadHandleDuplicatedCalled);

#ifdef OBJECT_NOTIFICATION_LOG_INTERNALS
		PVOID													Object=OperationInformation->Object;
		POBJECT_TYPE											ObjectType=OperationInformation->ObjectType;
		const char*												ObjectTypeString=GetObjectTypeName(ObjectType);
		ACCESS_MASK												OriginalDesiredAccess=OperationInformation->Parameters->DuplicateHandleInformation.OriginalDesiredAccess;

		// !!! DRIVER moze ZMENIT VALUE [OB_PRE_DUPLICATE_HANDLE_INFORMATION::DesiredAccess].

		KdPrint(("!!!!! THREAD - PRE OPERATION CALLBACK - DUPLICATE - OBJECT [%p] OBJECT TYPE [%s] DESIRED ACCESS [%lX].\n",Object,ObjectTypeString,OriginalDesiredAccess));
#endif
	}

#ifdef OBJECT_NOTIFICATION_LOG
	KdPrint(("!!!!! THREAD PRE OPERATION CALLBACK [%s] is EXECUTED !!!\n",FunctionName));
#endif

	return(OB_PREOP_CALLBACK_STATUS::OB_PREOP_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void ThreadObjectPostOperationCallback(PVOID RegistrationContext, POB_POST_OPERATION_INFORMATION OperationInformation)
{
	UNREFERENCED_PARAMETER(RegistrationContext);

#ifdef OBJECT_NOTIFICATION_LOG
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! THREAD POST OPERATION CALLBACK [%s] is EXECUTING !!!\n",FunctionName));
#endif

	if (OperationInformation->Operation==OB_OPERATION_HANDLE_CREATE)
	{
		InterlockedIncrement64(&NumberOfPostThreadHandleCreatedCalled);

#ifdef OBJECT_NOTIFICATION_LOG_INTERNALS
		PVOID													Object=OperationInformation->Object;
		POBJECT_TYPE											ObjectType=OperationInformation->ObjectType;
		const char*												ObjectTypeString=GetObjectTypeName(ObjectType);
		NTSTATUS												ReturnStatus=OperationInformation->ReturnStatus;
		ACCESS_MASK												GrantedAccess=OperationInformation->Parameters->CreateHandleInformation.GrantedAccess;

		// !!! DRIVER moze ZMENIT VALUE [OB_POST_CREATE_HANDLE_INFORMATION::DesiredAccess].

		KdPrint(("!!!!! THREAD - POST OPERATION CALLBACK - CREATE - OBJECT [%p] OBJECT TYPE [%s] RETURN STATUS [%lX] GRANTED ACCESS [%lX].\n",Object,ObjectTypeString,ReturnStatus,GrantedAccess));
#endif
	}
	else if (OperationInformation->Operation==OB_OPERATION_HANDLE_DUPLICATE)
	{
		InterlockedIncrement64(&NumberOfPostThreadHandleDuplicatedCalled);

#ifdef OBJECT_NOTIFICATION_LOG_INTERNALS
		PVOID													Object=OperationInformation->Object;
		POBJECT_TYPE											ObjectType=OperationInformation->ObjectType;
		const char*												ObjectTypeString=GetObjectTypeName(ObjectType);
		NTSTATUS												ReturnStatus=OperationInformation->ReturnStatus;
		ACCESS_MASK												GrantedAccess=OperationInformation->Parameters->DuplicateHandleInformation.GrantedAccess;

		// !!! DRIVER moze ZMENIT VALUE [OB_POST_DUPLICATE_HANDLE_INFORMATION::DesiredAccess].

		KdPrint(("!!!!! THREAD - POST OPERATION CALLBACK - DUPLICATE - OBJECT [%p] OBJECT TYPE [%s] RETURN STATUS [%lX] GRANTED ACCESS [%lX].\n",Object,ObjectTypeString,ReturnStatus,GrantedAccess));
#endif
	}

#ifdef OBJECT_NOTIFICATION_LOG
	KdPrint(("!!!!! THREAD POST OPERATION CALLBACK [%s] is EXECUTED !!!\n",FunctionName));
#endif
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
	
	if (Code==IOCTL_TEST_READ_OBJECT_NOTIFICATION_COUNTERS)
	{
		SObjectNotificationStatistics							Statistics;

		Statistics.MNumberOfPreProcessHandleCreatedCalled=InterlockedOr64(&NumberOfPreProcessHandleCreatedCalled,0);
		Statistics.MNumberOfPreProcessHandleDuplicatedCalled=InterlockedOr64(&NumberOfPreProcessHandleDuplicatedCalled,0);
		Statistics.MNumberOfPostProcessHandleCreatedCalled=InterlockedOr64(&NumberOfPostProcessHandleCreatedCalled,0);
		Statistics.MNumberOfPostProcessHandleDuplicatedCalled=InterlockedOr64(&NumberOfPostProcessHandleDuplicatedCalled,0);
		Statistics.MNumberOfPreThreadHandleCreatedCalled=InterlockedOr64(&NumberOfPreThreadHandleCreatedCalled,0);
		Statistics.MNumberOfPreThreadHandleDuplicatedCalled=InterlockedOr64(&NumberOfPreThreadHandleDuplicatedCalled,0);
		Statistics.MNumberOfPostThreadHandleCreatedCalled=InterlockedOr64(&NumberOfPostThreadHandleCreatedCalled,0);
		Statistics.MNumberOfPostThreadHandleDuplicatedCalled=InterlockedOr64(&NumberOfPostThreadHandleDuplicatedCalled,0);

		Status=TestReadObjectNotificationCounters(DeviceObject,Irp,Statistics);
	}
	else if (Code==IOCTL_TEST_READ_REGISTRY_NOTIFICATION_COUNTERS)
	{
		SRegistryNotificationStatistics							Statistics;

		Statistics.MNumberOfPreCreateKeyCalled=InterlockedOr64(&NumberOfPreCreateKeyCalled,0);
		Statistics.MNumberOfPostCreateKeyCalled=InterlockedOr64(&NumberOfPostCreateKeyCalled,0);
		Statistics.MNumberOfPreCreateKeyExCalled=InterlockedOr64(&NumberOfPreCreateKeyExCalled,0);
		Statistics.MNumberOfPostCreateKeyExCalled=InterlockedOr64(&NumberOfPostCreateKeyExCalled,0);
		Statistics.MNumberOfPreDeleteValueKeyCalled=InterlockedOr64(&NumberOfPreDeleteValueKeyCalled,0);
		Statistics.MNumberOfPostDeleteValueKeyCalled=InterlockedOr64(&NumberOfPostDeleteValueKeyCalled,0);

		Status=TestReadRegistryNotificationCounters(DeviceObject,Irp,Statistics);
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

	// !!! Odregistruje sa CALLBACK FUNCTION pre OBJECT NOFITICATIONS.
	NTSTATUS													Status=CmUnRegisterCallback(RegistryNotificationRegistrationCookie);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER REGISTRY NOTIFICATIONS with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
	}

	RegistryNotificationRegistrationCookie.QuadPart=0;

	// !!! Odregistruju sa CALLBACK FUNCTIONS pre OBJECT NOFITICATIONS.
	ObUnRegisterCallbacks(ObjectNotificationRegistrationHandle);
	ObjectNotificationRegistrationHandle=nullptr;

	KdPrint(("!!!!! OBJECT CALLBACKS UNREGISTERED !!!\n"));

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
	bool														SymbolicLinkCreated=false;

	ObjectNotificationRegistrationHandle=nullptr;

	do
	{
		Status=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		// !!!!! DEVICE OBJECT sa nastavi do BUFFERED IO MODE.
		DeviceObject->Flags|=DO_BUFFERED_IO;

		Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK [%wZ] with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,SymbolicLink,Status));
			break;
		}

		SymbolicLinkCreated=true;

		constexpr USHORT										NUMBER_OF_OPERATION_REGISTRATIONS=2;

		OB_OPERATION_REGISTRATION								OperationsRegistrations[NUMBER_OF_OPERATION_REGISTRATIONS];

		OperationsRegistrations[0].ObjectType=PsProcessType;
		OperationsRegistrations[0].Operations=(OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE);
		OperationsRegistrations[0].PreOperation=ProcessObjectPreOperationCallback;
		OperationsRegistrations[0].PostOperation=ProcessObjectPostOperationCallback;

		OperationsRegistrations[1].ObjectType=PsThreadType;
		OperationsRegistrations[1].Operations=(OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE);
		OperationsRegistrations[1].PreOperation=ThreadObjectPreOperationCallback;
		OperationsRegistrations[1].PostOperation=ThreadObjectPostOperationCallback;

		OB_CALLBACK_REGISTRATION								CallbackRegistration;

		CallbackRegistration.Version=OB_FLT_REGISTRATION_VERSION;
		CallbackRegistration.OperationRegistrationCount=NUMBER_OF_OPERATION_REGISTRATIONS;
		CallbackRegistration.Altitude=RTL_CONSTANT_STRING(L"12345.999888777");
		CallbackRegistration.RegistrationContext=nullptr;
		CallbackRegistration.OperationRegistration=OperationsRegistrations;

		// !!! Zaregistruju sa CALLBACK FUNCTIONS pre OBJECT NOFITICATIONS.
		Status=ObRegisterCallbacks(&CallbackRegistration,&ObjectNotificationRegistrationHandle);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER OBJECT NOTIFICATION with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		UNICODE_STRING											Altitude=RTL_CONSTANT_STRING(L"12345.999888777666");

		// !!! Zaregistruje sa CALLBACK FUNCTION pre REGISTRY NOFITICATIONS.
		Status=CmRegisterCallbackEx(ProcessRegistryOperationCallback,&Altitude,DriverObject,nullptr,&RegistryNotificationRegistrationCookie,nullptr);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER REGISTRY NOTIFICATIONS with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to START !!!\n",DriverObject->DriverName));

		if (ObjectNotificationRegistrationHandle!=nullptr)
		{
			ObUnRegisterCallbacks(ObjectNotificationRegistrationHandle);
			ObjectNotificationRegistrationHandle=nullptr;
		}

		if (SymbolicLinkCreated==true)
		{
			IoDeleteSymbolicLink(&SymbolicLink);
		}

		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------