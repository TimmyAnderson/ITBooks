//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
#include "CDeviceHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OBJECT je UNDOCUMENTED, takze musi byt DECLARED explicitne.
extern "C" POBJECT_TYPE* IoDriverObjectType;
// !!!!! FUNCTION je UNDOCUMENTED, takze musi byt DECLARED explicitne.
extern "C" NTSYSAPI NTSTATUS NTAPI ObReferenceObjectByName(PUNICODE_STRING ObjectPath, ULONG Attributes, PACCESS_STATE PassedAccessState, ACCESS_MASK DesiredAccess, POBJECT_TYPE ObjectType, KPROCESSOR_MODE AccessMode, PVOID ParseContext, PVOID *Object);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_SET_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SET_DEVICE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CLEAR_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_CLEAR_DEVICE,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CDeviceHelpers*													Global;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS RemoteDriverDispatchRoutine(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! DRIVER EXECUTING REMOTE DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=Global->CallOriginalDispatchRoutine(DeviceObject,Irp);

	KdPrint(("!!!!!!!!!! DRIVER EXECUTED REMOTE DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
void RemoteDriverDriverUnloadRoutine(PDRIVER_OBJECT DriverObject)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! DRIVER EXECUTING REMOTE DRIVER UNLOAD ROUTINE [%s] !!!\n",FunctionName));

	Global->CallOriginalDriverUnloadRoutine(DriverObject);

	// !!!!! DEVICE sa odstrani z GLOBAL VARIABLE a uvolni sa ziskany DRIVER OBJECT.
	bool														DeviceCleared=Global->ClearDevice();

	if (DeviceCleared==true)
	{
		KdPrint(("!!!!! DRIVER CLEARED DEVICE !!!\n"));
	}
	else
	{
		KdPrint(("!!!!! DRIVER didn't CLEAR DEVICE !!!\n"));
	}

	KdPrint(("!!!!!!!!!! DRIVER EXECUTED REMOTE DRIVER UNLOAD ROUTINE [%s] !!!\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineCreate(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineClose(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=CHelpers::CompleteIRP(Irp,STATUS_SUCCESS,0);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineDeviceControl(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTING DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	const ULONG													MAX_BUFFER_SIZE=512;

	NTSTATUS													Status;
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
	CDeviceHelpers*												DeviceHelpers=static_cast<CDeviceHelpers*>(DeviceObject->DeviceExtension);

	if (Code==IOCTL_SET_DEVICE)
	{
		WCHAR*													Buffer=(WCHAR*)Irp->AssociatedIrp.SystemBuffer;
		ULONG													BufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;

		if (Buffer!=nullptr && BufferLength<=MAX_BUFFER_SIZE)
		{
			Buffer[BufferLength/sizeof(WCHAR)-1]=L'\0';

			PDRIVER_OBJECT										DriverObject;
			UNICODE_STRING										Name;

			RtlInitUnicodeString(&Name,Buffer);

			Status=ObReferenceObjectByName(&Name,OBJ_CASE_INSENSITIVE,nullptr,0,*IoDriverObjectType,KernelMode,nullptr,(PVOID*)&DriverObject);

			if (NT_SUCCESS(Status)==true)
			{
				DeviceHelpers->ClearDevice();

				bool											DeviceSet=DeviceHelpers->SetDevice(DriverObject,RemoteDriverDispatchRoutine,RemoteDriverDriverUnloadRoutine);

				if (DeviceSet==true)
				{
					KdPrint(("!!!!! DRIVER SET DEVICE !!!\n"));
				}
				else
				{
					KdPrint(("!!!!! DRIVER didn't SET DEVICE !!!\n"));
				}
			}
			else
			{
				KdPrint(("!!!!! DRIVER FAILED to GET DRIVER OBJECT with ERROR CODE [%lX] !!!\n",Status));
			}
		}
		else
		{
			Status=STATUS_INVALID_BUFFER_SIZE;
		}
	}
	else if (Code==IOCTL_CLEAR_DEVICE)
	{
		bool													DeviceCleared=DeviceHelpers->ClearDevice();

		if (DeviceCleared==true)
		{
			KdPrint(("!!!!! DRIVER CLEARED DEVICE !!!\n"));
		}
		else
		{
			KdPrint(("!!!!! DRIVER didn't CLEAR DEVICE !!!\n"));
		}

		Status=STATUS_SUCCESS;
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to RECOGNIZE CODE [%lu] !!!\n",DeviceObject->DriverObject->DriverName,Code));

		Status=STATUS_INVALID_DEVICE_REQUEST;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,0);

	KdPrint(("!!!!! DRIVER [%wZ] EXECUTED DISPATCH ROUTINE [%s] !!!\n",DeviceObject->DriverObject->DriverName,FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER UNLOAD sa vola AZ ked su ukoncene vsetky IRP, pricom dalsie IRP po spusteni iniciovani UNLOAD procesu uz nedovoli WINDOWS odoslat.
// !!!!! To znamena, ze DRIVER UNLOAD NEMUSI kontrolovat ci este nebezia nejake IRP daneho DRIVER, pretoze ak by bezali, tak WINDOWS DRIVER UNLOAD NESPUSTI, az kym nebudu vsetky IRP ukoncene.
// !!!!! DRIVER UNLOAD NIE JE spusteny, az kym vsetky DEFFERED PROCEDURE CALLS, ktore spustil dany DRIVER NIE su UKONCENE.
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	UNICODE_STRING												SymbolicLink;

	// !!!!! DEVICE sa odstrani z GLOBAL VARIABLE a uvolni sa ziskany DRIVER OBJECT.
	bool														DeviceCleared=Global->ClearDevice();

	if (DeviceCleared==true)
	{
		KdPrint(("!!!!! DRIVER CLEARED DEVICE !!!\n"));
	}
	else
	{
		KdPrint(("!!!!! DRIVER didn't CLEAR DEVICE !!!\n"));
	}

	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

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

	NTSTATUS													Status=STATUS_SUCCESS;
	PDEVICE_OBJECT												DeviceObject=nullptr;
	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	bool														SymbolicLinkCreated=false;
	
	do
	{
		Status=IoCreateDevice(DriverObject,sizeof(CDeviceHelpers),&DeviceName,FILE_DEVICE_UNKNOWN,0,TRUE,&DeviceObject);

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

		CDeviceHelpers*											DeviceHelpers=static_cast<CDeviceHelpers*>(DeviceObject->DeviceExtension);

		DeviceHelpers->Init();

		Global=DeviceHelpers;
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to START !!!\n",DriverObject->DriverName));

		if (SymbolicLinkCreated==true)
		{
			IoDeleteSymbolicLink(&SymbolicLink);
		}
	
		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}

		return(Status);
	}

	DriverObject->DriverUnload=FunctionDriverUnload;
	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchRoutineDeviceControl;

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------