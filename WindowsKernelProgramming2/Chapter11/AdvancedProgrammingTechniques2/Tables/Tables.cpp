//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CLocker.h"
#include "SharedHeader.h"
#include "CGlobals.h"
#include "SProcessData.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER, ktory pouziva OBJECT NOTIFICATION MUSI mat v PE FILE povoleny FLAG [IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY]. To sa robi pridanim COMMAND [/integritycheck] do LINKER COMMAND LINE.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TABLES_GET_PROCESS_COUNT CTL_CODE(TABLES_DEVICE, TABLES_GET_PROCESS_COUNT, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TABLES_GET_PROCESS_BY_ID CTL_CODE(TABLES_DEVICE, TABLES_GET_PROCESS_BY_ID, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TABLES_GET_PROCESS_BY_INDEX CTL_CODE(TABLES_DEVICE, TABLES_GET_PROCESS_BY_INDEX, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TABLES_DELETE_ALL CTL_CODE(TABLES_DEVICE, TABLES_DELETE_ALL, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TABLES_GET_ALL CTL_CODE(TABLES_DEVICE, TABLES_GET_ALL, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CGlobals														Globals;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void OnProcessNotify(PEPROCESS Process, HANDLE PID, PPS_CREATE_NOTIFY_INFO CreateInfo)
{
	UNREFERENCED_PARAMETER(Process);

	if(!CreateInfo)
	{
		CLocker													Locker(Globals.MLock);
		{
			SProcessData										Data;

			Data.MID=HandleToULong(PID);

			BOOLEAN												Deleted=RtlDeleteElementGenericTable(&Globals.MProcessTable,&Data);

			if (Deleted==TRUE)
			{
				KdPrint(("!!!!!!!!!! DRIVER DELETED PROCESS with PID [%lu].\n",Data.MID));
			}
			else
			{
				KdPrint(("!!!!!!!!!! DRIVER FAILED to DELETE PROCESS with PID [%lu].\n",Data.MID));
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS OnRegistryNotify(PVOID, PVOID Argument1, PVOID Argument2)
{
	UNREFERENCED_PARAMETER(Argument2);

	REG_NOTIFY_CLASS											Type=(REG_NOTIFY_CLASS)(ULONG_PTR)Argument1;

	switch (Type)
	{
		case RegNtPostSetValueKey:
		case RegNtPostCreateKey:
		case RegNtPostCreateKeyEx:
		case RegNtPostRenameKey:
		case RegNtPostDeleteValueKey:
		case RegNtPostDeleteKey:
		{
			PVOID												Buffer;
			ULONG												PID=HandleToULong(PsGetCurrentProcessId());

			{
				CLocker											Locker(Globals.MLock);
				{
					Buffer=RtlLookupElementGenericTable(&Globals.MProcessTable,&PID);

					if (Buffer==nullptr)
					{
						SProcessData							Data{};

						Data.MID=PID;

						Buffer=RtlInsertElementGenericTable(&Globals.MProcessTable,&Data,sizeof(Data),nullptr);

						if (Buffer!=nullptr)
						{
							KdPrint(("ADDED PROCESS [%lu] from REGISTRY CALLBACK.\n",PID));
						}
					}
				}
			}

			if (Buffer!=nullptr)
			{
				SProcessData*									Data=(SProcessData*)Buffer;

				switch(Type)
				{
					case RegNtPostSetValueKey:
					{
						InterlockedIncrement64(&Data->MRegistrySetValueOperations); 
						break;
					}

					case RegNtPostCreateKey: 
					case RegNtPostCreateKeyEx:
					{
						InterlockedIncrement64(&Data->MRegistryCreateKeyOperations); 
						break;
					}

					case RegNtPostRenameKey: 
					{
						InterlockedIncrement64(&Data->MRegistryRenameOperations); 
						break;
					}

					case RegNtPostDeleteKey: 
					case RegNtPostDeleteValueKey:
					{
						InterlockedIncrement64(&Data->MRegistryDeleteOperations); 
						break;
					}
				}
			}
		}
	}

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void DeleteAllProcesses(void)
{
	CLocker														Locker(Globals.MLock);
	{
		PVOID													Pointer;

		RTL_GENERIC_TABLE*										Table=&Globals.MProcessTable;

		while ((Pointer=RtlGetElementGenericTable(Table,0))!=nullptr)
		{
			RtlDeleteElementGenericTable(Table,Pointer);
		}
	}
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
	ULONG														Information=0;
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	const auto&													Parameters=CurrentStackLocation->Parameters.DeviceIoControl;
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;

	if (Code==IOCTL_TABLES_GET_PROCESS_COUNT)
	{
		do
		{
			if (Parameters.OutputBufferLength<sizeof(ULONG))
			{
				Status=STATUS_BUFFER_TOO_SMALL;
				break;
			}

			CLocker												Locker(Globals.MLock);
			{
				*(ULONG*)Irp->AssociatedIrp.SystemBuffer=RtlNumberGenericTableElements(&Globals.MProcessTable);

				Information=sizeof(ULONG);

				Status=STATUS_SUCCESS;
			}
		}
		while(false);
	}
	else if (Code==IOCTL_TABLES_GET_PROCESS_BY_ID)
	{
		do
		{
			if (Parameters.OutputBufferLength<sizeof(SProcessData) || Parameters.InputBufferLength<sizeof(ULONG))
			{
				Status=STATUS_BUFFER_TOO_SMALL;
				break;
			}

			ULONG												PID=*(ULONG*)Irp->AssociatedIrp.SystemBuffer;

			CLocker												Locker(Globals.MLock);
			{
				SProcessData*									Data=(SProcessData*)RtlLookupElementGenericTable(&Globals.MProcessTable,&PID);

				if (Data==nullptr)
				{
					Status=STATUS_INVALID_CID;
					break;
				}

				Information=sizeof(SProcessData);

				memcpy(Irp->AssociatedIrp.SystemBuffer,Data,Information);

				Status=STATUS_SUCCESS;
			}
		}
		while(false);
	}
	else if (Code==IOCTL_TABLES_GET_PROCESS_BY_INDEX)
	{
		do
		{
			if (Parameters.OutputBufferLength<sizeof(SProcessData) || Parameters.InputBufferLength<sizeof(ULONG))
			{
				Status=STATUS_BUFFER_TOO_SMALL;
				break;
			}

			ULONG												Index=*(ULONG*)Irp->AssociatedIrp.SystemBuffer;

			CLocker												Locker(Globals.MLock);
			{
				SProcessData*									Data=(SProcessData*)RtlGetElementGenericTable(&Globals.MProcessTable,Index);

				if (Data==nullptr)
				{
					Status=STATUS_INVALID_PARAMETER;
					break;
				}

				Information=sizeof(SProcessData);

				memcpy(Irp->AssociatedIrp.SystemBuffer,Data,Information);

				Status=STATUS_SUCCESS;
			}
		}
		while(false);
	}
	else if (Code==IOCTL_TABLES_GET_ALL)
	{
		do
		{
			if (Parameters.OutputBufferLength<sizeof(SProcessData))
			{
				Status=STATUS_BUFFER_TOO_SMALL;
				break;
			}

			CLocker												Locker(Globals.MLock);
			{
				ULONG											Count=RtlNumberGenericTableElements(&Globals.MProcessTable);

				if (Count==0)
				{
					Status=STATUS_NO_DATA_DETECTED;
					break;
				}

				NT_ASSERT(Irp->MdlAddress);

				Count=min(Count,Parameters.OutputBufferLength/sizeof(SProcessData));

				SProcessData*									Buffer=(SProcessData*)MmGetSystemAddressForMdlSafe(Irp->MdlAddress,NormalPagePriority);

				if (Buffer==nullptr)
				{
					Status=STATUS_INSUFFICIENT_RESOURCES;
					break;
				}

				for (ULONG Index=0;Index<Count;Index++)
				{
					SProcessData*								Data=(SProcessData*)RtlGetElementGenericTable(&Globals.MProcessTable,Index);

					NT_ASSERT(Data);

					memcpy(Buffer,Data,sizeof(SProcessData));

					Buffer++;
				}

				Information=(Count*sizeof(SProcessData));

				Status=STATUS_SUCCESS;
			}
		}
		while(false);
	}
	else if (Code==IOCTL_TABLES_DELETE_ALL)
	{
		DeleteAllProcesses();
		
		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to RECOGNIZE CODE [%lu] !!!\n",DeviceObject->DriverObject->DriverName,Code));
		Status=STATUS_INVALID_DEVICE_REQUEST;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

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

	CmUnRegisterCallback(Globals.MRegistryCookie);

	PsSetCreateProcessNotifyRoutineEx(OnProcessNotify,TRUE);

	DeleteAllProcesses();

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
	bool														ProcessCallbackRegistered=false;

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

		SymbolicLinkCreated=true;

		Globals.Init();

		Status=PsSetCreateProcessNotifyRoutineEx(OnProcessNotify,FALSE);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER PROCESS NOTIFY CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		ProcessCallbackRegistered=true;

		UNICODE_STRING											Altitude=RTL_CONSTANT_STRING(L"123456.789");

		Status=CmRegisterCallbackEx(OnRegistryNotify,&Altitude,DriverObject,nullptr,&Globals.MRegistryCookie,nullptr);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER REGISTRY NOTIFY CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
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

		if (ProcessCallbackRegistered==true)
		{
			PsSetCreateProcessNotifyRoutineEx(OnProcessNotify,TRUE);
			ProcessCallbackRegistered=false;
		}

		if (SymbolicLinkCreated==true)
		{
			IoDeleteSymbolicLink(&SymbolicLink);
			SymbolicLinkCreated=false;
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