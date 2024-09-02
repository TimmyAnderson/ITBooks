//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CLocker.h"
#include "Helpers\CSharedLocker.h"
#include "SharedHeader.h"
#include "CGlobals.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER, ktory pouziva OBJECT NOTIFICATION MUSI mat v PE FILE povoleny FLAG [IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY]. To sa robi pridanim COMMAND [/integritycheck] do LINKER COMMAND LINE.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CGlobals														Globals;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define PROCESS_TERMINATE										1
#define KPROTECT_DEVICE											0x8101
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_PROTECT_ADD_PID CTL_CODE(KPROTECT_DEVICE, CODE_PROTECT_ADD_PID, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_PROTECT_REMOVE_PID CTL_CODE(KPROTECT_DEVICE, CODE_PROTECT_REMOVE_PID, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_PROTECT_REMOVE_ALL CTL_CODE(KPROTECT_DEVICE, CODE_PROTECT_REMOVE_ALL, METHOD_NEITHER, FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
ULONG AddProcesses(const ULONG* PIDsToAdd, ULONG Count)
{
	ULONG														Added=0;
	ULONG														Current=0;

	CLocker<CExecutiveResourceGlobal>							Locker(Globals.GetLock());
	{
		for(int Index=0;Index<CGlobals::MAX_PIDS && Added<Count;Index++)
		{
			ULONG												PID=Globals.GetPID(Index);

			if (PID==0)
			{
				ULONG											NewPID=PIDsToAdd[Current++];

				Globals.SetPID(Index,NewPID);

				Added++;
			}
		}

		Globals.IncrementPIDsCount(Added);
	}

	return(Added);
}
//----------------------------------------------------------------------------------------------------------------------
ULONG RemoveProcesses(const ULONG* PIDsToRemove, ULONG Count)
{
	ULONG														Removed=0;

	CLocker<CExecutiveResourceGlobal>							Locker(Globals.GetLock());
	{
		for(int Index1=0;Index1<CGlobals::MAX_PIDS && Removed<Count;Index1++)
		{
			ULONG												PID1=Globals.GetPID(Index1);

			if (PID1!=0)
			{
				for (ULONG Index2=0;Index2<Count;Index2++)
				{
					ULONG										PID2=PIDsToRemove[Index2];

					if (PID1==PID2)
					{
						Globals.SetPID(Index1,0);

						Removed++;

						break;
					}
				}
			}
		}

		Globals.DecrementPIDsCount(Removed);
	}

	return(Removed);
}
//----------------------------------------------------------------------------------------------------------------------
int FindProcess(ULONG PIDToFind)
{
	CSharedLocker<CExecutiveResourceGlobal>						Locker(Globals.GetLock());
	{
		ULONG													Exist=0;
		ULONG													PIDsCount=Globals.GetPIDsCount();

		for(int Index=0;Index<CGlobals::MAX_PIDS && Exist<PIDsCount;Index++)
		{
			ULONG												PID=Globals.GetPID(Index);

			if (PID==0)
			{
				continue;
			}

			if (PID==PIDToFind)
			{
				return(Index);
			}

			Exist++;
		}
	}

	return(-1);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OB_PREOP_CALLBACK_STATUS OnPreOpenProcess(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION Info)
{
	UNREFERENCED_PARAMETER(RegistrationContext);

	if (Info->KernelHandle!=0)
	{
		return(OB_PREOP_SUCCESS);
	}

	PEPROCESS													Process=static_cast<PEPROCESS>(Info->Object);
	ULONG														PID=HandleToULong(PsGetProcessId(Process));

	int															Index=FindProcess(PID);

	if (Index>=0)
	{
		// !!!!! Znizia sa ACCESS RIGHTS, aby PROCESS NEMOHOL byt TERMINATED.
		Info->Parameters->CreateHandleInformation.DesiredAccess&=(~PROCESS_TERMINATE);
	}

	return(OB_PREOP_SUCCESS);
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

	NTSTATUS													Status=STATUS_INVALID_DEVICE_REQUEST;
	ULONG														Information= 0;

	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;

	if (Code==IOCTL_PROTECT_ADD_PID || Code==IOCTL_PROTECT_REMOVE_PID)
	{
		if (InputBufferLength==0 || (InputBufferLength%sizeof(ULONG))!=0)
		{
			Status=STATUS_INVALID_BUFFER_SIZE;
		}
		else
		{
			ULONG*												PIDs=static_cast<ULONG*>(Irp->AssociatedIrp.SystemBuffer);

			if (PIDs==nullptr)
			{
				Status=STATUS_INVALID_PARAMETER;
			}
			else
			{
				ULONG											Count=(InputBufferLength/sizeof(ULONG));
				ULONG											Changed;

				if (Code==IOCTL_PROTECT_ADD_PID)
				{
					Changed=AddProcesses(PIDs,Count);
				}
				else
				{
					Changed=RemoveProcesses(PIDs,Count);
				}

				if (Changed==Count)
				{
					Status=STATUS_SUCCESS;
				}
				else
				{
					Status=STATUS_NOT_ALL_ASSIGNED;
				}

				Information=(Changed*sizeof(ULONG));

				if (Code==IOCTL_PROTECT_ADD_PID)
				{
					KdPrint(("!!!!! NUMBER of PIDs ADDED [%lu] !!!\n",Changed));
				}
				else if (Code==IOCTL_PROTECT_REMOVE_PID)
				{
					KdPrint(("!!!!! NUMBER of PIDs REMOVED [%lu] !!!\n",Changed));
				}
			}
		}
	}
	else if (Code==IOCTL_PROTECT_REMOVE_ALL)
	{
		CLocker<CExecutiveResourceGlobal>						Locker(Globals.GetLock());
		{
			for(int Index=0;Index<CGlobals::MAX_PIDS;Index++)
			{
				Globals.SetPID(Index,0);
			}

			Globals.SetPIDsCount(0);

			Status=STATUS_SUCCESS;

			KdPrint(("!!!!! ALL PIDs REMOVED !!!\n"));
		}
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

	ObUnRegisterCallbacks(Globals.GetRegistrationHandle());

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(DriverObject->DeviceObject);

	Globals.Delete();

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

	do
	{
		Globals.Init();

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

		OB_OPERATION_REGISTRATION								Operation;
		
		Operation.ObjectType=PsProcessType;
		Operation.Operations=(OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE);
		Operation.PreOperation=OnPreOpenProcess;
		Operation.PostOperation=nullptr;

		OB_CALLBACK_REGISTRATION								Registration;
			
		Registration.Version=OB_FLT_REGISTRATION_VERSION;
		Registration.OperationRegistrationCount=1;
		Registration.Altitude=RTL_CONSTANT_STRING(L"12345.6171");
		Registration.RegistrationContext=nullptr;
		Registration.OperationRegistration=&Operation;

		PVOID													RegistrationHandle;

		Status=ObRegisterCallbacks(&Registration,&RegistrationHandle);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER OBJECT NOTIFICATION with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		Globals.SetRegistrationHandle(RegistrationHandle);
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

		Globals.Delete();
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------