//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
#include "SGlobals.h"
#include "SFullItem.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PREPROCESSOR DEFINITION [IS_KERNEL] must be defined.
// !!!!! DRIVER, ktory pouziva PROCESS NOTIFICATION MUSI mat v PE FILE povoleny FLAG [IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY]. To sa robi pridanim COMMAND [/integritycheck] do LINKER COMMAND LINE.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MUSI byt vytvoreny ako POINTER, pretoze TYPE [SGlobals] obsahuje FIELD TYPE [CFastMutex], ktory ma CONSTRUCTOR a DESTRUCTOR a tie nema kto zavolat, kedze v KERNEL MODE neexistuje C++ RUNTIME.
SGlobals*														Globals=nullptr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void OnProcessNotify(PEPROCESS Process, HANDLE ProcessID, PPS_CREATE_NOTIFY_INFO CreateInfo)
{
	if (CreateInfo!=nullptr)
	{
		SIZE_T													AllocSize=sizeof(SFullItem<SProcessCreateInfo>);
		USHORT													CommandLineSize=0;

		if (CreateInfo->CommandLine!=nullptr)
		{
			CommandLineSize=CreateInfo->CommandLine->Length;
			AllocSize+=CommandLineSize;
		}

		SFullItem<SProcessCreateInfo>*							Info=(SFullItem<SProcessCreateInfo>*)ExAllocatePool2(POOL_FLAG_PAGED,AllocSize,MY_TAG);

		if (Info==nullptr)
		{
			KdPrint(("Can't ALLOCATE MEMORY for PROCESS CREATE INFO.\n"));
			return;
		}

		SProcessCreateInfo&										Item=Info->MData;

		KeQuerySystemTimePrecise(&Item.MTime);

		Item.MType=EItemType::E_PROCESS_CREATE;
		Item.MSize=(sizeof(SProcessCreateInfo)+CommandLineSize);
		Item.MProcessID=HandleToULong(ProcessID);
		Item.MParentProcessID=HandleToULong(CreateInfo->ParentProcessId);
		Item.MCreatingProcessID=HandleToULong(CreateInfo->CreatingThreadId.UniqueProcess);
		Item.MCreatingThreadID=HandleToULong(CreateInfo->CreatingThreadId.UniqueThread);

		if (CommandLineSize>0)
		{
			memcpy(Item.MCommandLine,CreateInfo->CommandLine->Buffer,CommandLineSize);
			Item.MCommandLineLength=(CommandLineSize/sizeof(WCHAR));
		}
		else
		{
			Item.MCommandLineLength=0;
		}

		Globals->AddItem(&Info->MEntry);

		KdPrint(("PROCESS CREATE INFO ADDED to LIST.\n"));
	}
	else
	{
		SFullItem<SProcessExitInfo>*							Info=(SFullItem<SProcessExitInfo>*)ExAllocatePool2(POOL_FLAG_PAGED,sizeof(SFullItem<SProcessExitInfo>),MY_TAG);

		if (Info==nullptr)
		{
			KdPrint(("Can't ALLOCATE MEMORY for PROCESS EXIT INFO.\n"));
			return;
		}

		SProcessExitInfo&										Item=Info->MData;

		KeQuerySystemTimePrecise(&Item.MTime);

		Item.MType=EItemType::E_PROCESS_EXIT;
		Item.MProcessID=HandleToULong(ProcessID);
		Item.MSize=sizeof(SProcessExitInfo);
		Item.MExitCode=PsGetProcessExitStatus(Process);

		Globals->AddItem(&Info->MEntry);

		KdPrint(("PROCESS EXIT INFO ADDED to LIST.\n"));
	}
}
//----------------------------------------------------------------------------------------------------------------------
void OnThreadNotify(HANDLE ProcessID, HANDLE ThreadID, BOOLEAN Create)
{
	if (Create==TRUE)
	{
		SIZE_T													Size=sizeof(SFullItem<SThreadCreateInfo>);
		SFullItem<SThreadCreateInfo>*							Info=(SFullItem<SThreadCreateInfo>*)ExAllocatePool2(POOL_FLAG_PAGED,Size,MY_TAG);

		if (Info==nullptr)
		{
			KdPrint(("Can't ALLOCATE MEMORY for THREAD CREATE INFO.\n"));
			return;
		}

		SThreadCreateInfo&										Item=Info->MData;

		KeQuerySystemTimePrecise(&Item.MTime);

		Item.MSize=sizeof(SThreadCreateInfo);
		Item.MType=EItemType::E_THREAD_CREATE;
		Item.MProcessID=HandleToULong(ProcessID);
		Item.MThreadID=HandleToULong(ThreadID);

		Globals->AddItem(&Info->MEntry);

		KdPrint(("THREAD CREATE INFO ADDED to LIST.\n"));
	}
	else
	{
		SIZE_T													Size=sizeof(SFullItem<SThreadExitInfo>);
		SFullItem<SThreadExitInfo>*								Info=(SFullItem<SThreadExitInfo>*)ExAllocatePool2(POOL_FLAG_PAGED,Size,MY_TAG);

		if (Info==nullptr)
		{
			KdPrint(("Can't ALLOCATE MEMORY for THREAD EXIT INFO.\n"));
			return;
		}

		SThreadExitInfo&										Item=Info->MData;

		KeQuerySystemTimePrecise(&Item.MTime);

		Item.MSize=sizeof(SThreadExitInfo);
		Item.MType=EItemType::E_THREAD_EXIT;
		Item.MProcessID=HandleToULong(ProcessID);
		Item.MThreadID=HandleToULong(ThreadID);

		PETHREAD												Thread;
		NTSTATUS												Status=PsLookupThreadByThreadId(ThreadID,&Thread);

		if (NT_SUCCESS(Status)==true)
		{
			Item.MExitCode=PsGetThreadExitStatus(Thread);

			ObDereferenceObject(Thread);
		}
		else
		{
			KdPrint(("LOOKUP THREAD BY THREAD ID FAILED.\n"));
		}

		Globals->AddItem(&Info->MEntry);

		KdPrint(("THREAD EXIT INFO ADDED to LIST.\n"));
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
NTSTATUS DispatchRoutineRead(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													NumberOfBytesRead=0;

	PIO_STACK_LOCATION											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

	ULONG														ReadBufferSize=CurrentStackLocation->Parameters.Read.Length;
	PUCHAR														ReadBuffer=(PUCHAR)MmGetSystemAddressForMdlSafe(Irp->MdlAddress,NormalPagePriority);

	if (ReadBuffer!=nullptr)
	{
		while (true)
		{
			LIST_ENTRY*											Entry=Globals->RemoveItem();

			if (Entry==nullptr)
			{
				break;
			}

			SFullItem<SItemHeader>*								Info=CONTAINING_RECORD(Entry,SFullItem<SItemHeader>,MEntry);
			USHORT												Size=Info->MData.MSize;

			// !!!!! Ak je USER BUFFER prilis kratky, ITEM sa vrati spat do LINKED LIST.
			if (ReadBufferSize<Size)
			{
				Globals->AddHeadItem(Entry);
				break;
			}

			memcpy(ReadBuffer,&Info->MData,Size);

			// !!! Skrati sa pocet BYTES ostavajucich v USER MODE BUFFER.
			ReadBufferSize-=Size;

			// !!! Posunie sa POINTER v USER MODE BUFFER.
			ReadBuffer+=Size;

			// !!! Zvysi sa pocet BYTES zapisanych do READ BUFFER.
			NumberOfBytesRead+=Size;

			ExFreePoolWithTag(Info,MY_TAG);

			KdPrint(("PROCESS INFO REMOVED from LIST.\n"));
		}
	}
	else
	{
		KdPrint(("Can't MAP MDL ADDRESS.\n"));

		Status=STATUS_INSUFFICIENT_RESOURCES;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,NumberOfBytesRead);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	UNICODE_STRING												SymbolicLink;
	NTSTATUS													Status;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	Status=PsRemoveCreateThreadNotifyRoutine(OnThreadNotify);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER THREAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
	}

	Status=PsSetCreateProcessNotifyRoutineEx(OnProcessNotify,TRUE);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER PROCESS NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
	}

	LIST_ENTRY*													Entry;

	// !!!!! Odstrania sa ENTRIES, ktore neboli vycitane z CLIENT.
	while((Entry=Globals->RemoveItem())!=nullptr)
	{
		SFullItem<SItemHeader>*									FullItem=CONTAINING_RECORD(Entry,SFullItem<SItemHeader>,MEntry);

		ExFreePoolWithTag(FullItem,MY_TAG);

		KdPrint(("PROCESS INFO REMOVED from LIST - STOPPING DRIVER.\n"));
	}

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(DriverObject->DeviceObject);

	if (Globals!=nullptr)
	{
		delete(Globals);
		Globals=nullptr;
	}

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING)
{
	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	NTSTATUS													Status=STATUS_SUCCESS;
	PDEVICE_OBJECT												DeviceObject=nullptr;
	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	bool														SymbolicLinkCreated=false;
	bool														ProcessCallbacksCreated=false;

	do
	{
		Globals=new (EPoolFlags::E_POOL_FLAG_NON_PAGED) SGlobals(50);

		if (Globals==nullptr)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to ALLOCATE MEMORY for GLOBALS !!!\n",DriverObject->DriverName));
			Status=STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		Status=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,TRUE,&DeviceObject);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		DeviceObject->Flags|=DO_DIRECT_IO;

		Status=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK [%wZ] with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,SymbolicLink,Status));
			break;
		}

		SymbolicLinkCreated=true;

		Status=PsSetCreateProcessNotifyRoutineEx(OnProcessNotify,FALSE);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER PROCESS NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		ProcessCallbacksCreated=true;

		Status=PsSetCreateThreadNotifyRoutine(OnThreadNotify);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER THREAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
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

		if (ProcessCallbacksCreated==true)
		{
			PsSetCreateProcessNotifyRoutineEx(OnProcessNotify,TRUE);
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

		if (Globals!=nullptr)
		{
			delete(Globals);
			Globals=nullptr;
		}

		return(Status);
	}

	DriverObject->DriverUnload=FunctionDriverUnload;
	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_READ]=DispatchRoutineRead;

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------