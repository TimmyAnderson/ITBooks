//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "Helpers\CHelpers.h"
#include "Defines.h"
#include "SharedHeader.h"
#include "Memory.h"
#include "CPlaybackState.h"
#include "CPlaybackStateSafe.h"
#include "MyGetProcessHandle.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_MELODY_PLAY CTL_CODE(MELODY_DEVICE, CODE_PLAY_MUSIC, METHOD_BUFFERED, FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
HANDLE															SystemProcessHandle=nullptr;
//CPlaybackState*												State;
CPlaybackStateSafe*												State;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS MelodyCreateClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS													Status=STATUS_SUCCESS;

	if (IoGetCurrentIrpStackLocation(Irp)->MajorFunction==IRP_MJ_CREATE)
	{
		// !!! Vytvori sa WORKER THREAD, ak este neexistuje.
		Status=State->Start(DeviceObject,SystemProcessHandle);
	}
	// !!!!! Tento CODE je CHYBNY. V KNIHE NIE JE, ale SAMPLES je.
	// !!!!! THREAD sa NESMIE zastavit, ked sa uzatvori HANDLE na DEVICE, pretoze iny PROCESS by mohol DRIVER prave pouzivat.
	/*
	else
	{
		// !!! Zastavi sa WORKER THREAD.
		State->Stop();
	}
	*/

	Status=CHelpers::CompleteIRP(Irp,Status,0);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS MelodyDeviceControl(PDEVICE_OBJECT, PIRP Irp)
{
	PIO_STACK_LOCATION											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	auto&														Parameters=CurrentStackLocation->Parameters.DeviceIoControl;
	NTSTATUS													Status=STATUS_INVALID_DEVICE_REQUEST;
	ULONG														Info=0;

	switch (Parameters.IoControlCode)
	{
		case IOCTL_MELODY_PLAY:
		{
			if (Parameters.InputBufferLength==0 || (Parameters.InputBufferLength%sizeof(SNote))!=0)
			{
				Status=STATUS_INVALID_BUFFER_SIZE;
				break;
			}

			SNote*												Data=(SNote*)Irp->AssociatedIrp.SystemBuffer;

			if (Data==nullptr)
			{
				Status=STATUS_INVALID_PARAMETER;
				break;
			}

			ULONG												NumberOfNotes=(Parameters.InputBufferLength/sizeof(SNote));

			Status=State->AddNotes(Data,NumberOfNotes);

			if (NT_SUCCESS(Status)==false)
			{
				break;
			}

			Info=Parameters.InputBufferLength;

			break;
		}
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Info);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MelodyUnload(PDRIVER_OBJECT DriverObject)
{
	delete(State);
	State=nullptr;

	UNICODE_STRING												SymLink=RTL_CONSTANT_STRING(L"\\??\\" MY_DRIVER_NAME);

	IoDeleteSymbolicLink(&SymLink);

	IoDeleteDevice(DriverObject->DeviceObject);

	ZwClose(SystemProcessHandle);
	SystemProcessHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	UNICODE_STRING												SystemProcessName=RTL_CONSTANT_STRING(L"csrss.exe");
	HANDLE														SystemProcessID=MyGetProcessID(1,SystemProcessName);

	KdPrint((DRIVER_PREFIX "PROCESS [%wZ] has ID [%lu].\n",SystemProcessName,HandleToULong(SystemProcessID)));

	SystemProcessHandle=MyGetProcessHandle(SystemProcessID);

	KdPrint((DRIVER_PREFIX "PROCESS [%wZ] has HANDLE [%lx].\n",SystemProcessName,HandleToULong(SystemProcessHandle)));

	if (SystemProcessHandle==nullptr)
	{
		KdPrint((DRIVER_PREFIX "DRIVER FAILED to OPEN PROCESS HANDLE to PROCESS [%wZ].\n",SystemProcessName));

		return(STATUS_INSUFFICIENT_RESOURCES);
	}

	// !!! Alokuje sa OBJECT, ktory obsahuje WORKER THREAD. No WORKER THREAD sa NESPUSTA.
	//State=new (POOL_FLAG_PAGED,DRIVER_TAG) CPlaybackState;
	State=new (POOL_FLAG_PAGED,DRIVER_TAG) CPlaybackStateSafe;

	if (State==nullptr)
	{
		return(STATUS_INSUFFICIENT_RESOURCES);
	}

	NTSTATUS													Status=STATUS_SUCCESS;
	PDEVICE_OBJECT												DeviceObject=nullptr;
	UNICODE_STRING												SymLink=RTL_CONSTANT_STRING(L"\\??\\" MY_DRIVER_NAME);

	do
	{
		UNICODE_STRING											Name=RTL_CONSTANT_STRING(L"\\Device\\" MY_DRIVER_NAME);

		Status=IoCreateDevice(DriverObject,0,&Name,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			break;
		}

		Status=IoCreateSymbolicLink(&SymLink,&Name);

		if (NT_SUCCESS(Status)==false)
		{
			break;
		}

	}
	while(false);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint((DRIVER_PREFIX "DRIVER FAILED to START with ERROR [0x%08X].\n",Status));

		delete(State);
		State=nullptr;

		if (DeviceObject!=nullptr)
		{
			IoDeleteDevice(DeviceObject);
			DeviceObject=nullptr;
		}

		if (SystemProcessHandle!=nullptr)
		{
			ZwClose(SystemProcessHandle);
			SystemProcessHandle=nullptr;
		}

		return(Status);
	}

	DriverObject->DriverUnload=MelodyUnload;
	DriverObject->MajorFunction[IRP_MJ_CREATE]=MelodyCreateClose;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=MelodyCreateClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=MelodyDeviceControl;

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------