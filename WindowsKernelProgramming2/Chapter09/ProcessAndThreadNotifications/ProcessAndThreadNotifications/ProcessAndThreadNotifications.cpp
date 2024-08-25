//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "SharedHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER, ktory pouziva PROCESS NOTIFICATION MUSI mat v PE FILE povoleny FLAG [IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY]. To sa robi pridanim COMMAND [/integritycheck] do LINKER COMMAND LINE.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//#define											DUMP_PROCESSES
//#define											DUMP_THREADS
//#define											DUMP_IMAGES
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
volatile LONG64										NumberOfProcesesCreated;
volatile LONG64										NumberOfProcesesFinished;
volatile LONG64										NumberOfThreadsCreated;
volatile LONG64										NumberOfThreadsFinished;
volatile LONG64										NumberOfLoadedImages;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MyProcessNotifyCallback(PEPROCESS Process, HANDLE ProcessId, PPS_CREATE_NOTIFY_INFO CreateInfo)
{
	if (CreateInfo!=nullptr)
	{
		InterlockedIncrement64(&NumberOfProcesesCreated);

		if (CreateInfo->ImageFileName!=nullptr)
		{
			UNICODE_STRING										NotepadName;
		
			RtlInitUnicodeString(&NotepadName,L"\\??\\C:\\WINDOWS\\system32\\notepad.exe");

			LONG												Result=RtlEqualUnicodeString(CreateInfo->ImageFileName,&NotepadName,TRUE);

			if (Result==TRUE)
			{
				KdPrint(("!!!!!!!!!! LAUNCH of NOTEPAD DETECTED !!!\n"));

				// !!!!!! Zabrani sa spusteniu NOTEPAD.
				CreateInfo->CreationStatus=STATUS_INSUFFICIENT_RESOURCES;
			}
		}
	}
	else
	{
		InterlockedIncrement64(&NumberOfProcesesFinished);
	}

#ifdef DUMP_PROCESSES
	UNREFERENCED_PARAMETER(Process);

	ULONG											ProcessIDAsULong=HandleToULong(ProcessId);

	if (CreateInfo!=nullptr)
	{
		if (CreateInfo->FileOpenNameAvailable==true && CreateInfo->ImageFileName!=nullptr)
		{
			KdPrint(("!!!!!!!!!! PROCESS [%lu] with NAME [%wZ] CREATED !!!\n",ProcessIDAsULong,*(CreateInfo->ImageFileName)));
		}
		else
		{
			KdPrint(("!!!!!!!!!! PROCESS [%lu] CREATED !!!\n",ProcessIDAsULong));
		}
	}
	else
	{
		KdPrint(("!!!!!!!!!! PROCESS [%lu] FINISHED !!!\n",ProcessIDAsULong));
	}
#else
	UNREFERENCED_PARAMETER(Process);
	UNREFERENCED_PARAMETER(ProcessId);
	UNREFERENCED_PARAMETER(CreateInfo);
#endif
}
//----------------------------------------------------------------------------------------------------------------------
void MyCreateThreadNotifyRoutine(HANDLE ProcessId, HANDLE ThreadId, BOOLEAN Create)
{
	if (Create==TRUE)
	{
		InterlockedIncrement64(&NumberOfThreadsCreated);
	}
	else
	{
		InterlockedIncrement64(&NumberOfThreadsFinished);
	}

#ifdef DUMP_THREADS
	ULONG											ProcessIDAsULong=HandleToULong(ProcessId);
	ULONG											ThreadIDAsULong=HandleToULong(ThreadId);

	if (Create==TRUE)
	{
		KdPrint(("!!!!!!!!!! THREAD [%lu] CREATED in PROCESS [%lu] !!!\n",ThreadIDAsULong,ProcessIDAsULong));
	}
	else
	{
		KdPrint(("!!!!!!!!!! THREAD [%lu] FINISHED in PROCESS [%lu] !!!\n",ThreadIDAsULong,ProcessIDAsULong));
	}
#else
	UNREFERENCED_PARAMETER(ProcessId);
	UNREFERENCED_PARAMETER(ThreadId);
	UNREFERENCED_PARAMETER(Create);
#endif
}
//----------------------------------------------------------------------------------------------------------------------
void MyLoadImageNotifyRoutine(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	InterlockedIncrement64(&NumberOfLoadedImages);
	
#ifdef DUMP_IMAGES
	ULONG											ProcessIDAsULong=HandleToULong(ProcessId);
	_FILE_OBJECT*									FileObject=nullptr;

	if (ImageInfo->ExtendedInfoPresent!=0)
	{
		// !!! Ziska sa POINTER na EXTENSION STRUCTURE [IMAGE_INFO_EX].
		IMAGE_INFO_EX*								ImageInfoEx=CONTAINING_RECORD(ImageInfo,IMAGE_INFO_EX,ImageInfo);

		FileObject=ImageInfoEx->FileObject;
	}

	if (FullImageName!=nullptr)
	{
		KdPrint(("!!!!!!!!!! IMAGE [%wZ] LOADED in PROCESS [%lu] !!! IMAGE SIZE [%I64u] FILE OBECT [%p].\n",*FullImageName,ProcessIDAsULong,ImageInfo->ImageSize,FileObject));
	}
	else
	{
		KdPrint(("!!!!!!!!!! IMAGE LOADED in PROCESS [%lu] !!! IMAGE SIZE [%I64u] FILE OBECT [%p].\n",ProcessIDAsULong,ImageInfo->ImageSize,FileObject));
	}
#else
	UNREFERENCED_PARAMETER(FullImageName);
	UNREFERENCED_PARAMETER(ProcessId);
	UNREFERENCED_PARAMETER(ImageInfo);
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
NTSTATUS DispatchRoutineRead(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													NumberOfBytesRead=0;

	PIO_STACK_LOCATION											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

	constexpr size_t											OutputBufferSize=sizeof(SNotificationStatistics);

	PVOID														ReadBuffer=Irp->AssociatedIrp.SystemBuffer;
	ULONG														ReadBufferSize=CurrentStackLocation->Parameters.Read.Length;

	KdPrint(("!!!!!!!!!! READ DISPATCH ROUTINE [%s] - BUFFER [%p] BUFFER SIZE [%lu] !!!\n",FunctionName,ReadBuffer,ReadBufferSize));

	do
	{
		if (ReadBuffer==nullptr)
		{
			Status=STATUS_INVALID_PARAMETER;
			break;
		}

		if (ReadBufferSize<OutputBufferSize)
		{
			Status=STATUS_BUFFER_TOO_SMALL;
			break;
		}

		SNotificationStatistics*							Statistics=static_cast<SNotificationStatistics*>(ReadBuffer);

		Statistics->MNumberOfProcesesCreated=InterlockedOr64(&NumberOfProcesesCreated,0);
		Statistics->MNumberOfProcesesFinished=InterlockedOr64(&NumberOfProcesesFinished,0);
		Statistics->MNumberOfThreadsCreated=InterlockedOr64(&NumberOfThreadsCreated,0);
		Statistics->MNumberOfThreadsFinished=InterlockedOr64(&NumberOfThreadsFinished,0);
		Statistics->MNumberOfLoadedImages=InterlockedOr64(&NumberOfLoadedImages,0);

		KdPrint(("!!!!!!!!!! READ DISPATCH ROUTINE [%s] CALLED !!!\n",FunctionName));

		Status=STATUS_SUCCESS;
		NumberOfBytesRead=OutputBufferSize;
	}
	while(false);

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=NumberOfBytesRead;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

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

	Status=PsRemoveLoadImageNotifyRoutine(MyLoadImageNotifyRoutine);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER IMAGE LOAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
	}

	// !!! Odregistruje sa CALLBACK pre THREAD NOTIFICATION.
	Status=PsRemoveCreateThreadNotifyRoutine(MyCreateThreadNotifyRoutine);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER THREAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
	}

	// !!! Odregistruje sa CALLBACK pre PROCESS NOTIFICATION.
	Status=PsSetCreateProcessNotifyRoutineEx(MyProcessNotifyCallback,TRUE);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER PROCESS NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
	}

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
	DriverObject->MajorFunction[IRP_MJ_READ]=DispatchRoutineRead;
	
	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	NTSTATUS													Status;
	PDEVICE_OBJECT												DeviceObject;
	bool														SymbolicLinkCreated=false;
	bool														ProcessNotificationRegistered=false;
	bool														ThreadNotificationRegistered=false;
	bool														ImageLoadNotificationRegistered=false;

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

		// !!! Zaregistruje sa CALLBACK pre PROCESS NOTIFICATION.
		Status=PsSetCreateProcessNotifyRoutineEx(MyProcessNotifyCallback,FALSE);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER PROCESS NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		ProcessNotificationRegistered=true;

		// !!! Zaregistruje sa CALLBACK pre THREAD NOTIFICATION.
		Status=PsSetCreateThreadNotifyRoutine(MyCreateThreadNotifyRoutine);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to THREAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		ThreadNotificationRegistered=true;

		// !!! Zaregistruje sa CALLBACK pre IMAGE LOAD NOTIFICATION.
		Status=PsSetLoadImageNotifyRoutine(MyLoadImageNotifyRoutine);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to IMAGE LOAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		ImageLoadNotificationRegistered=true;
	}
	while(false);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to START !!!\n",DriverObject->DriverName));

		if (ImageLoadNotificationRegistered==true)
		{
			NTSTATUS											LocalStatus=PsRemoveLoadImageNotifyRoutine(MyLoadImageNotifyRoutine);

			if (NT_SUCCESS(LocalStatus)==false)
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER IMAGE LOAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,LocalStatus));
			}
		}

		if (ThreadNotificationRegistered==true)
		{
			NTSTATUS											LocalStatus=PsRemoveCreateThreadNotifyRoutine(MyCreateThreadNotifyRoutine);

			if (NT_SUCCESS(LocalStatus)==false)
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER THREAD NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,LocalStatus));
			}
		}

		if (ProcessNotificationRegistered==true)
		{
			NTSTATUS											LocalStatus=PsSetCreateProcessNotifyRoutineEx(MyProcessNotifyCallback,TRUE);

			if (NT_SUCCESS(LocalStatus)==false)
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER PROCESS NOTIFICATION CALLBACK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,LocalStatus));
			}
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