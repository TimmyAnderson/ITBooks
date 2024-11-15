//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <fltKernel.h>
#include "SharedHeader.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CHelpers.h"
#include "Helpers\CFilterFileNameInformation.h"
#include "Helpers\CMiniFilterRegistryHelpers.h"
#include "Helpers\CLocker.h"
#include "SFileContext.h"
#include "SFileBackupPortMessage.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE SYSTEM MINI FILTERS MUSIA mat vlozenu LIBRARY [FltMgr.lib].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER robi BACKUP FILE otvoreneho pre WRITE pred kazdym dalsim WRITE. Udrziava sa iba 1 predosla kopila FILE v STREAM [:backup] daneho FILE.
// !!!!! COMMAD [FileBackupClient.exe 1 FileName.txt TEXT1 TEXT2] vykona BACKUP iba ak je povodny FILE OVERRIDEN. Nie ked je prvykrat vytvoreny. Co je aj logicke, kedze sa robi iba BACKUP uz vytvoreneho FILE.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PDRIVER_OBJECT													GlobalDriverObject;
CMiniFilterRegistryHelpers										MiniFilterRegistryHelpers;
PFLT_FILTER														Filter=nullptr;
PFLT_PORT														Port=nullptr;
PFLT_PORT														ClientPort=nullptr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ShouldBackupFile(CFilterFileNameInformation& NameInfo)
{
	NTSTATUS													Status=NameInfo.Parse();

	if (NT_SUCCESS(Status)==false)
	{
		return(false);
	}

	static PCWSTR												Extensions[]={L"txt", L"docx", L"doc", L"jpg", L"png"};

	for (PCWSTR Extension : Extensions)
	{
		if (NameInfo->Extension.Buffer!=nullptr)
		{
			int													CompareResult=_wcsnicmp(Extension,NameInfo->Extension.Buffer,wcslen(Extension));

			if (CompareResult==0)
			{
				return(true);
			}
		}
	}

	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS BackupFile(PUNICODE_STRING Path, PCFLT_RELATED_OBJECTS FltObjects)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status;
	LARGE_INTEGER												FileSize;

	Status=FsRtlGetFileSize(FltObjects->FileObject,&FileSize);

	if (NT_SUCCESS(Status)==false || FileSize.QuadPart==0)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to GET FILE SIZE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
		return(Status);
	}

	HANDLE														HandleSourceFile=nullptr;
	HANDLE														HandleTargetFile=nullptr;
	PFILE_OBJECT												SourceFile=nullptr;
	PFILE_OBJECT												TargetFile=nullptr;
	IO_STATUS_BLOCK												IoStatus;
	void*														Buffer=nullptr;

	do
	{
		OBJECT_ATTRIBUTES										SourceFileAttributes;

		InitializeObjectAttributes(&SourceFileAttributes,Path,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,nullptr,nullptr);

		Status=FltCreateFileEx(FltObjects->Filter,FltObjects->Instance,&HandleSourceFile,&SourceFile,GENERIC_READ | SYNCHRONIZE,&SourceFileAttributes,&IoStatus,nullptr,FILE_ATTRIBUTE_NORMAL,FILE_SHARE_READ | FILE_SHARE_WRITE,FILE_OPEN,FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY,nullptr,0,IO_IGNORE_SHARE_ACCESS_CHECK);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to OPEN SOURCE FILE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
			break;
		}

		UNICODE_STRING											TargetFileName;
		const WCHAR												BackupStream[]=BACKUP_STREAM_NAME;

		TargetFileName.MaximumLength=(Path->Length+sizeof(BackupStream));

		TargetFileName.Buffer=((WCHAR*)ExAllocatePool2(POOL_FLAG_PAGED,TargetFileName.MaximumLength,MY_TAG));

		if (TargetFileName.Buffer==nullptr)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE MEMORY for TARGET FILE NAME !!!\n",FunctionName));
			Status=STATUS_NO_MEMORY;
			break;
		}

		RtlCopyUnicodeString(&TargetFileName,Path);
		RtlAppendUnicodeToString(&TargetFileName,BackupStream);

		OBJECT_ATTRIBUTES										TargetFileAttributes;

		InitializeObjectAttributes(&TargetFileAttributes,&TargetFileName,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,nullptr,nullptr);

		Status=FltCreateFileEx(FltObjects->Filter,FltObjects->Instance,&HandleTargetFile,&TargetFile,GENERIC_WRITE | SYNCHRONIZE,&TargetFileAttributes,&IoStatus,nullptr,FILE_ATTRIBUTE_NORMAL,0,FILE_OVERWRITE_IF,FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY,nullptr,0,0);

		ExFreePoolWithTag(TargetFileName.Buffer,MY_TAG);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to OPEN TARGET FILE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
			break;
		}

		ULONG													Size=(1 << 20);

		Buffer=ExAllocatePool2(POOL_FLAG_PAGED,Size,MY_TAG);

		if (Buffer==nullptr)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE MEMORY !!!\n",FunctionName));
			Status=STATUS_NO_MEMORY;
			break;
		}

		ULONG													Bytes;
		LARGE_INTEGER											SaveSize=FileSize;

		while(FileSize.QuadPart>0)
		{
			Status=FltReadFile(FltObjects->Instance,SourceFile,nullptr,(ULONG)min((LONGLONG)Size,FileSize.QuadPart),Buffer,0,&Bytes,nullptr,nullptr);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!! FUNCTION [%s] FAILED to READ from SOURCE FILE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
				break;
			}

			Status=FltWriteFile(FltObjects->Instance,TargetFile,nullptr,Bytes,Buffer,0,nullptr,nullptr,nullptr);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!! FUNCTION [%s] FAILED to WRITE to TARGET FILE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
				break;
			}

			FileSize.QuadPart-=Bytes;
		}

		FILE_END_OF_FILE_INFORMATION							Info;

		Info.EndOfFile=SaveSize;

		Status=FltSetInformationFile(FltObjects->Instance,TargetFile,&Info,sizeof(Info),FileEndOfFileInformation);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to SET INFORMATION on TARGET FILE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
			break;
		}

		KdPrint(("!!!!!!!!!! FUNCTION [%s] SUCCESSFULLY BACKED UP FILE [%wZ] !!!\n",FunctionName,*Path));
	}
	while(false);

	if (Buffer!=nullptr)
	{
		ExFreePoolWithTag(Buffer,MY_TAG);
		Buffer=nullptr;
	}

	if (HandleSourceFile!=nullptr)
	{
		FltClose(HandleSourceFile);
		HandleSourceFile=nullptr;
	}

	if (HandleTargetFile!=nullptr)
	{
		FltClose(HandleTargetFile);
		HandleTargetFile=nullptr;
	}

	if (SourceFile!=nullptr)
	{
		ObDereferenceObject(SourceFile);
		SourceFile=nullptr;
	}

	if (TargetFile!=nullptr)
	{
		ObDereferenceObject(TargetFile);
		TargetFile=nullptr;
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS BackupFileWithSection(PUNICODE_STRING Path, PCFLT_RELATED_OBJECTS FltObjects)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status;
	LARGE_INTEGER												FileSize;

	Status=FsRtlGetFileSize(FltObjects->FileObject,&FileSize);

	if (NT_SUCCESS(Status)==false || FileSize.QuadPart==0)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to GET FILE SIZE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
		return(Status);
	}

	HANDLE														HandleSourceFile=nullptr;
	HANDLE														HandleTargetFile = nullptr;
	PFILE_OBJECT												SourceFile=nullptr;
	PFILE_OBJECT												TargetFile=nullptr;
	IO_STATUS_BLOCK												IoStatus;
	HANDLE														HandleSection=nullptr;

	do
	{
		OBJECT_ATTRIBUTES										SourceFileAttributes;

		InitializeObjectAttributes(&SourceFileAttributes,Path,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,nullptr,nullptr);

		Status=FltCreateFileEx(FltObjects->Filter,FltObjects->Instance,&HandleSourceFile,&SourceFile,GENERIC_READ | SYNCHRONIZE,&SourceFileAttributes,&IoStatus,nullptr,FILE_ATTRIBUTE_NORMAL,FILE_SHARE_READ | FILE_SHARE_WRITE,FILE_OPEN,FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY,nullptr,0,IO_IGNORE_SHARE_ACCESS_CHECK);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to OPEN SOURCE FILE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
			break;
		}

		UNICODE_STRING											TargetFileName;
		const WCHAR												BackupStream[]=BACKUP_STREAM_NAME;

		TargetFileName.MaximumLength=(Path->Length+sizeof(BackupStream));

		TargetFileName.Buffer=((WCHAR*)ExAllocatePool2(POOL_FLAG_PAGED,TargetFileName.MaximumLength,MY_TAG));

		if (TargetFileName.Buffer==nullptr)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE MEMORY !!!\n",FunctionName));
			Status=STATUS_NO_MEMORY;
			break;
		}

		RtlCopyUnicodeString(&TargetFileName,Path);
		RtlAppendUnicodeToString(&TargetFileName,BackupStream);

		OBJECT_ATTRIBUTES										TargetFileAttributes;

		InitializeObjectAttributes(&TargetFileAttributes,&TargetFileName,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,nullptr,nullptr);

		Status=FltCreateFileEx(FltObjects->Filter,FltObjects->Instance,&HandleTargetFile,&TargetFile,GENERIC_WRITE | SYNCHRONIZE,&TargetFileAttributes,&IoStatus,nullptr,FILE_ATTRIBUTE_NORMAL,0,FILE_OVERWRITE_IF,FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY,nullptr,0,0);

		ExFreePoolWithTag(TargetFileName.Buffer,MY_TAG);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to OPEN TARGET FILE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
			break;
		}

		OBJECT_ATTRIBUTES										SectionAttributes=RTL_CONSTANT_OBJECT_ATTRIBUTES((UNICODE_STRING*)nullptr,OBJ_KERNEL_HANDLE);

		Status=ZwCreateSection(&HandleSection,SECTION_MAP_READ | SECTION_QUERY,&SectionAttributes,nullptr,PAGE_READONLY,SEC_COMMIT,HandleSourceFile);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to OPEN SECTION with ERROR CODE [%lX] !!!\n",FunctionName,Status));
			break;
		}

		ULONG													Bytes;
		LARGE_INTEGER											Offset{};
		LARGE_INTEGER											SaveSize=FileSize;
		PVOID													Buffer;
		HANDLE													Process=ZwCurrentProcess();
		SIZE_T													Size=0;

		while(FileSize.QuadPart>0)
		{
			Buffer=nullptr;

			Status=ZwMapViewOfSection(HandleSection,Process,&Buffer,0,0,&Offset,&Size,ViewUnmap,0,PAGE_READONLY);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!! FUNCTION [%s] FAILED to MAP SECTION with ERROR CODE [%lX] !!!\n",FunctionName,Status));
				break;
			}

			Bytes=((ULONG)min((LONGLONG)Size,FileSize.QuadPart));

			Status=FltWriteFile(FltObjects->Instance,TargetFile,nullptr,Bytes,Buffer,0,&Bytes,nullptr,nullptr);

			ZwUnmapViewOfSection(Process,Buffer);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!! FUNCTION [%s] FAILED to WRITE to TARGET FILE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
				break;
			}

			FileSize.QuadPart-=Bytes;
			Offset.QuadPart+=Bytes;
		}

		FILE_END_OF_FILE_INFORMATION							Info;

		Info.EndOfFile=SaveSize;

		Status=FltSetInformationFile(FltObjects->Instance,TargetFile,&Info,sizeof(Info),FileEndOfFileInformation);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED to SET INFORMATION on TARGET FILE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
			break;
		}

		KdPrint(("!!!!!!!!!! FUNCTION [%s] SUCCESSFULLY BACKED UP FILE [%wZ] !!!\n",FunctionName,*Path));
	}
	while(false);

	if (HandleSection!=nullptr)
	{
		ZwClose(HandleSection);
		HandleSection=nullptr;
	}

	if (HandleSourceFile!=nullptr)
	{
		FltClose(HandleSourceFile);
		HandleSourceFile=nullptr;
	}

	if (HandleTargetFile!=nullptr)
	{
		FltClose(HandleTargetFile);
		HandleTargetFile=nullptr;
	}

	if (SourceFile!=nullptr)
	{
		ObDereferenceObject(SourceFile);
		SourceFile=nullptr;
	}

	if (TargetFile!=nullptr)
	{
		ObDereferenceObject(TargetFile);
		TargetFile=nullptr;
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS OnPostCreate(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID, FLT_POST_OPERATION_FLAGS Flags)
{
	if ((Flags & FLTFL_POST_OPERATION_DRAINING)!=0)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	NTSTATUS													Status;
	const auto&													Parameters=Data->Iopb->Parameters.Create;
	BOOLEAN														IsDirectory=FALSE;

	Status=FltIsDirectory(FltObjects->FileObject,FltObjects->Instance,&IsDirectory);

	if (NT_SUCCESS(Status)==false)
	{
		//KdPrint(("!!!!! DRIVER FAILED to CALL IS DIRECTORY with ERROR CODE [%lX] !!!\n",Status));
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	// !!!!! BACKUP sa robi iba pre USER MODE FILES, ktore su otvorene pre WRITE ACCESS a iba ak FILE NIE JE VYTVORENY. Pretoze, ak je novovytvoreny FILE, nema zmysel robit BACKUP.
	if (IsDirectory==TRUE || Data->RequestorMode==KernelMode || (Parameters.SecurityContext->DesiredAccess & FILE_WRITE_DATA)==0 || Data->IoStatus.Status!=STATUS_SUCCESS || Data->IoStatus.Information==FILE_CREATED)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	CFilterFileNameInformation									FileNameInfo(Status,Data,EFileNameOptions::E_QUERY_DEFAULT | EFileNameOptions::E_NORMALIZED);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER FAILED to PARSE FILE NAME with ERROR CODE [%lX] !!!\n",Status));
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	if (ShouldBackupFile(FileNameInfo)==false)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	if (FileNameInfo->Stream.Length>0)
	{
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	SFileContext*												Context;

	Status=FltAllocateContext(FltObjects->Filter,FLT_FILE_CONTEXT,sizeof(SFileContext),PagedPool,(PFLT_CONTEXT*)&Context);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER FAILED to ALLOCATED CONTEXT with ERROR CODE [%lX] !!!\n",Status));
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}

	Context->MWritten=FALSE;
	Context->MLock.Init();
	Context->MBackupTime.QuadPart=0;

	Status=FltSetFileContext(FltObjects->Instance,FltObjects->FileObject,FLT_SET_CONTEXT_REPLACE_IF_EXISTS,Context,nullptr);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER FAILED to SET FILE CONTEXT with ERROR CODE [%lX] !!!\n",Status));
	}

	FltReleaseContext(Context);

	KdPrint(("!!!!!!!!!! DRIVER SUCCESSFULLY SET FILE CONTEXT for FILE [%wZ] !!!\n",FileNameInfo->Name));

	return(FLT_POSTOP_FINISHED_PROCESSING);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS OnPreWrite(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext)
{
	UNREFERENCED_PARAMETER(CompletionContext);

	NTSTATUS													Status;
	SFileContext*												Context;

	Status=FltGetFileContext(FltObjects->Instance,FltObjects->FileObject,(PFLT_CONTEXT*)&Context);

	if (NT_SUCCESS(Status)==false || Context==nullptr)
	{
		//KdPrint(("!!!!! DRIVER FAILED to GET FILE CONTEXT with ERROR CODE [%lX] !!!\n",Status));
		return(FLT_PREOP_SUCCESS_NO_CALLBACK);
	}

	KdPrint(("!!!!!!!!!! DRIVER SUCCESSFULLY GOT FILE CONTEXT !!!\n"));

	do
	{
		CLocker													Locker(Context->MLock);

		if (Context->MWritten==TRUE)
		{
			break;
		}

		CFilterFileNameInformation								Name(Status,Data,EFileNameOptions::E_QUERY_DEFAULT | EFileNameOptions::E_NORMALIZED);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER FAILED to PARSE NAME with ERROR CODE [%lX] !!!\n",Status));
			break;
		}

		Status=BackupFile(&Name->Name,FltObjects);
		//Status=BackupFileWithSection(&Name->Name,FltObjects);

		if (NT_SUCCESS(Status)==true)
		{
			KeQuerySystemTimePrecise(&Context->MBackupTime);

			if (ClientPort!=nullptr)
			{
				USHORT											NameLength=Name->Name.Length;
				USHORT											Length=(sizeof(SFileBackupPortMessage)+NameLength);

				SFileBackupPortMessage*							Message=(SFileBackupPortMessage*)ExAllocatePool2(POOL_FLAG_PAGED,Length,MY_TAG);

				if (Message!=nullptr)
				{
					Message->MFileNameLength=(NameLength/sizeof(WCHAR));

					RtlCopyMemory(Message->MFileName,Name->Name.Buffer,NameLength);

					LARGE_INTEGER								Timeout;

					Timeout.QuadPart=(-10000*100);

					Status=FltSendMessage(Filter,&ClientPort,Message,Length,nullptr,nullptr,&Timeout);

					ExFreePoolWithTag(Message,MY_TAG);

					if (NT_SUCCESS(Status)==false)
					{
						KdPrint(("!!!!! DRIVER FAILED to SEND MESSAGE with ERROR CODE [%lX] !!!\n",Status));
					}
				}
				else
				{
					KdPrint(("!!!!! DRIVER FAILED to ALLOCATE MESSAGE !!!\n"));
				}
			}
		}
		else
		{
			KdPrint(("!!!!! DRIVER FAILED to BACKUP FILE with ERROR CODE [%lX] !!!\n",Status));
		}

		Context->MWritten=TRUE;
	}
	while(false);

	FltReleaseContext(Context);

	return(FLT_PREOP_SUCCESS_NO_CALLBACK);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS OnPostCleanup(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID, FLT_POST_OPERATION_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(Flags);
	UNREFERENCED_PARAMETER(Data);

	NTSTATUS													Status;
	SFileContext*												Context;

	Status=FltGetFileContext(FltObjects->Instance,FltObjects->FileObject,(PFLT_CONTEXT*)&Context);

	if (NT_SUCCESS(Status)==false || Context==nullptr)
	{
		//KdPrint(("!!!!! DRIVER FAILED to GET FILE CONTEXT with ERROR CODE [%lX] !!!\n",Status));
		return(FLT_POSTOP_FINISHED_PROCESSING);
	}
	else
	{
		// !!! Odstrani sa CONTEXT.
		FltReleaseContext(Context);
		FltDeleteContext(Context);

		KdPrint(("!!!!!!!!!! DRIVER SUCCESSFULLY RELEASED FILE CONTEXT !!!\n"));

		return(FLT_POSTOP_FINISHED_PROCESSING);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS PortConnectNotify(PFLT_PORT LocalClientPort, PVOID ServerPortCookie, PVOID ConnectionContext, ULONG SizeOfContext, PVOID* ConnectionPortCookie)
{
	UNREFERENCED_PARAMETER(ServerPortCookie);
	UNREFERENCED_PARAMETER(ConnectionContext);
	UNREFERENCED_PARAMETER(SizeOfContext);
	UNREFERENCED_PARAMETER(ConnectionPortCookie);

	ClientPort=LocalClientPort;

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void PortDisconnectNotify(PVOID ConnectionCookie)
{
	UNREFERENCED_PARAMETER(ConnectionCookie);

	FltCloseClientPort(Filter,&ClientPort);
	ClientPort=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS PortMessageNotify(PVOID PortCookie, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength, PULONG ReturnOutputBufferLength)
{
	UNREFERENCED_PARAMETER(PortCookie);
	UNREFERENCED_PARAMETER(InputBuffer);
	UNREFERENCED_PARAMETER(InputBufferLength);
	UNREFERENCED_PARAMETER(OutputBuffer);
	UNREFERENCED_PARAMETER(OutputBufferLength);
	UNREFERENCED_PARAMETER(ReturnOutputBufferLength);

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS FileBackupInstanceSetup(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_SETUP_FLAGS Flags, DEVICE_TYPE VolumeDeviceType, FLT_FILESYSTEM_TYPE VolumeFilesystemType)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);
	UNREFERENCED_PARAMETER(VolumeDeviceType);

	const char*													FunctionName=__FUNCTION__;

	if (VolumeFilesystemType==FLT_FSTYPE_NTFS)
	{
		if (FltObjects->Volume!=nullptr)
		{
			NTSTATUS											Status;
			ULONG												BufferSize;

			Status=FltGetVolumeName(FltObjects->Volume,nullptr,&BufferSize);

			if (NT_SUCCESS(Status)!=false || Status==STATUS_BUFFER_TOO_SMALL)
			{
				PWCH											Buffer=(PWCH)ExAllocatePool2(POOL_FLAG_PAGED,BufferSize,MY_TAG);

				if (Buffer!=nullptr)
				{
					UNICODE_STRING								VolumeName;

					VolumeName.Length=(USHORT)BufferSize;
					VolumeName.MaximumLength=(USHORT)BufferSize;
					VolumeName.Buffer=Buffer;

					Status=FltGetVolumeName(FltObjects->Volume,&VolumeName,nullptr);

					if (NT_SUCCESS(Status)!=false)
					{
						KdPrint(("!!!!! FUNCTION [%s] ATTACHING to VOLUE [%wZ] !!!\n",FunctionName,VolumeName));
					}
					else
					{
						KdPrint(("!!!!! FUNCTION [%s] FAILED to GET VOLUME NAME with ERROR CODE [%lX] !!!\n",FunctionName,Status));
					}

					ExFreePoolWithTag(Buffer,MY_TAG);
				}
				else
				{
					KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE BUFFER for VOLUME NAME !!!\n",FunctionName));
				}
			}
			else
			{
				KdPrint(("!!!!! FUNCTION [%s] FAILED to GET VOLUME NAME SIZE with ERROR CODE [%lX] !!!\n",FunctionName,Status));
			}
		}

		return(STATUS_SUCCESS);
	}
	else
	{
		return(STATUS_FLT_DO_NOT_ATTACH);
	}
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS FileBackupInstanceQueryTeardown(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
VOID FileBackupInstanceTeardownStart(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_TEARDOWN_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);
}
//----------------------------------------------------------------------------------------------------------------------
VOID FileBackupInstanceTeardownComplete(PCFLT_RELATED_OBJECTS FltObjects, FLT_INSTANCE_TEARDOWN_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS FileBackupUnload(FLT_FILTER_UNLOAD_FLAGS Flags)
{
	UNREFERENCED_PARAMETER(Flags);

	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",GlobalDriverObject->DriverName));

	WCHAR														Instance[]=MY_DRIVER_NAME L"DefaultInstance";

	FltCloseCommunicationPort(Port);
	Port=nullptr;

	FltUnregisterFilter(Filter);
	Filter=nullptr;

	NTSTATUS													Status=MiniFilterRegistryHelpers.DeleteRegistryKeys(Instance);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER KEYS from REGISTRY with ERROR CODE [%lX] !!!\n",GlobalDriverObject->DriverName,Status));
	}

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",GlobalDriverObject->DriverName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	GlobalDriverObject=DriverObject;

	WCHAR														Instance[]=MY_DRIVER_NAME L"DefaultInstance";
	WCHAR														Altitude[]=L"425342";

	UNICODE_STRING												DeviceName;
	UNICODE_STRING												SymbolicLink;

	RtlInitUnicodeString(&DeviceName,L"\\Device\\" MY_DRIVER_NAME);
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\" MY_DRIVER_NAME);

	NTSTATUS													Status;
	bool														RegistryKeyCreated=false;

	do
	{
		Status=MiniFilterRegistryHelpers.CreateRegistryKeys(RegistryPath,Instance,sizeof(Instance),Altitude,sizeof(Altitude),0);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER KEYS into REGISTRY with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		RegistryKeyCreated=true;

		const FLT_OPERATION_REGISTRATION						Callbacks[]=
		{
			{ IRP_MJ_CREATE, 0, nullptr, OnPostCreate },
			{ IRP_MJ_WRITE, 0, OnPreWrite },
			{ IRP_MJ_CLEANUP, 0, nullptr, OnPostCleanup },
			{ IRP_MJ_OPERATION_END }
		};

		const FLT_CONTEXT_REGISTRATION							Context[]=
		{
			{ FLT_FILE_CONTEXT, 0, nullptr, sizeof(SFileContext), MY_TAG },
			{ FLT_CONTEXT_END }
		};

		const FLT_REGISTRATION									Registration=
		{
			sizeof(FLT_REGISTRATION),
			FLT_REGISTRATION_VERSION,
			0,
			Context,
			Callbacks,
			FileBackupUnload,
			FileBackupInstanceSetup,
			FileBackupInstanceQueryTeardown,
			FileBackupInstanceTeardownStart,
			FileBackupInstanceTeardownComplete,
		};

		Status=FltRegisterFilter(DriverObject,&Registration,&Filter);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to REGISTER FILE SYSTEM MINI FILTER with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		UNICODE_STRING											Name=RTL_CONSTANT_STRING(L"\\" COMMUNICATION_PORT_NAME);
		PSECURITY_DESCRIPTOR									SecurityDesciptor;

		Status=FltBuildDefaultSecurityDescriptor(&SecurityDesciptor,FLT_PORT_ALL_ACCESS);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to BUILD SECURITY DESCRIPTOR with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		OBJECT_ATTRIBUTES										Attributes;

		InitializeObjectAttributes(&Attributes,&Name,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,nullptr,SecurityDesciptor);

		Status=FltCreateCommunicationPort(Filter,&Port,&Attributes,nullptr,PortConnectNotify,PortDisconnectNotify,PortMessageNotify,1);

		FltFreeSecurityDescriptor(SecurityDesciptor);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE COMMUNICATION PORT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
			break;
		}

		Status=FltStartFiltering(Filter);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!! DRIVER [%wZ] FAILED to START FILTERING with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status));
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

		if (Port!=nullptr)
		{
			FltCloseCommunicationPort(Port);
			Port=nullptr;
		}

		if (Filter!=nullptr)
		{
			FltUnregisterFilter(Filter);
			Filter=nullptr;
		}

		if (RegistryKeyCreated==true)
		{
			NTSTATUS											LocalStatus=MiniFilterRegistryHelpers.DeleteRegistryKeys(Instance);

			if (NT_SUCCESS(LocalStatus)==false)
			{
				KdPrint(("!!!!! DRIVER [%wZ] FAILED to UNREGISTER KEYS from REGISTRY with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,LocalStatus));
			}
		}
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------