//----------------------------------------------------------------------------------------------------------------------
#include "TestFileOperations.h"
#include "Helpers\MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FileOperationsCreateCopy(PCFLT_RELATED_OBJECTS FltObjects, UNICODE_STRING& FileName, UNICODE_STRING& BackupFileName)
{
	constexpr SIZE_T											COPY_BUFFER_SIZE=12;

	void*														CopyBuffer=ExAllocatePool2(POOL_FLAG_PAGED,COPY_BUFFER_SIZE,MY_TAG);

	// !!! Alokuje sa maly BUFFER, aby sa spravilo viac READ OPERATIONS.
	if (CopyBuffer!=nullptr)
	{
		NTSTATUS												Status;
		LARGE_INTEGER											FileSize;

		Status=FsRtlGetFileSize(FltObjects->FileObject,&FileSize);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!!!!!!! BACKUP - FAILED to GET FILE SIZE with ERROR CODE [%lX] !!!\n",Status));
			return;
		}

		if (FileSize.QuadPart==0)
		{
			KdPrint(("!!!!!!!!!! BACKUP - FILE has ZERO SIZE !!!\n"));
			return;
		}

		KdPrint(("!!!!!!!!!! BACKUP - BACKUP FILE NAME [%wZ] BACKUP FILE SIZE [%I64d] !!!\n",BackupFileName,FileSize.QuadPart));

		HANDLE													SourceFileHandle=nullptr;
		HANDLE													DestinationFileHandle=nullptr;
		PFILE_OBJECT											SourceFile=nullptr;
		PFILE_OBJECT											DestinationFile=nullptr;

		do
		{
			IO_STATUS_BLOCK										IoStatusBlock;
			OBJECT_ATTRIBUTES									SourceFileAttributes;

			InitializeObjectAttributes(&SourceFileAttributes,&FileName,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,nullptr,nullptr);

			Status=FltCreateFileEx(FltObjects->Filter,FltObjects->Instance,&SourceFileHandle,&SourceFile,GENERIC_READ | SYNCHRONIZE,&SourceFileAttributes,&IoStatusBlock,nullptr,FILE_ATTRIBUTE_NORMAL,FILE_SHARE_READ | FILE_SHARE_WRITE,FILE_OPEN,FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY,nullptr,0,IO_IGNORE_SHARE_ACCESS_CHECK);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!!!!!!! BACKUP - FAILED to OPEN SOURCE FILE with ERROR CODE [%lX] !!!\n",Status));
				break;
			}

			OBJECT_ATTRIBUTES									DestinationFileAttributes;

			InitializeObjectAttributes(&DestinationFileAttributes,&BackupFileName,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,nullptr,nullptr);

			Status=FltCreateFileEx(FltObjects->Filter,FltObjects->Instance,&DestinationFileHandle,&DestinationFile,GENERIC_WRITE | SYNCHRONIZE,&DestinationFileAttributes,&IoStatusBlock,nullptr,FILE_ATTRIBUTE_NORMAL,0,FILE_OVERWRITE_IF,FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY,nullptr,0,0);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!!!!!!! BACKUP - FAILED to OPEN DESTINATION FILE with ERROR CODE [%lX] !!!\n",Status));
				break;
			}

			LONGLONG											BytesToCopy=FileSize.QuadPart;
			LARGE_INTEGER										BytesWritten{};

			while(BytesToCopy>0)
			{
				ULONG											BytesRead;
				ULONG											BytesToRead=ULONG(min((LONGLONG)COPY_BUFFER_SIZE,BytesToCopy));

				Status=FltReadFile(FltObjects->Instance,SourceFile,nullptr,BytesToRead,CopyBuffer,0,&BytesRead,nullptr,nullptr);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! BACKUP - FAILED to READ SOURCE FILE with ERROR CODE [%lX] !!!\n",Status));
					break;
				}

				Status=FltWriteFile(FltObjects->Instance,DestinationFile,nullptr,BytesRead,CopyBuffer,0,nullptr,nullptr,nullptr);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!!!!!!! BACKUP - FAILED to WRITE DESTINATION FILE with ERROR CODE [%lX] !!!\n",Status));
					break;
				}

				BytesToCopy-=BytesRead;
				BytesWritten.QuadPart+=BytesRead;
			}


			FILE_END_OF_FILE_INFORMATION						Info;

			Info.EndOfFile=BytesWritten;

			// !!!!! Pri FILE OVERWRITE moze byt dlzka povodneho FILE vacsia ako aktualneho FILE, a preto dlzku DESTINATION FILE je treba explicitne nastavit na pocet skutocne zapisanych BYTES.
			Status=FltSetInformationFile(FltObjects->Instance,DestinationFile,&Info,sizeof(Info),FileEndOfFileInformation);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!!!!!!! BACKUP - FAILED to SET INFORMATION for DESTINATION FILE with ERROR CODE [%lX] !!!\n",Status));
				break;
			}
		}
		while(false);

		if (NT_SUCCESS(Status)==true)
		{
			KdPrint(("!!!!!!!!!! BACKUP - BACKUP CREATED !!!\n"));
		}
		else
		{
			KdPrint(("!!!!!!!!!! BACKUP - BACKUP FAILED !!!\n"));
		}

		if (SourceFileHandle!=nullptr)
		{
			FltClose(SourceFileHandle);
		}

		if (DestinationFileHandle!=nullptr)
		{
			FltClose(DestinationFileHandle);
		}

		if (SourceFile!=nullptr)
		{
			ObDereferenceObject(SourceFile);
		}

		if (DestinationFile!=nullptr)
		{
			ObDereferenceObject(DestinationFile);
		}

		ExFreePoolWithTag(CopyBuffer,MY_TAG);
	}
	else
	{
		KdPrint(("!!!!!!!!!! BACKUP - FAILED to ALLOCATE MEMORY !!!\n"));
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestFileOperationsPreReadOperation(PCFLT_RELATED_OBJECTS FltObjects, const PFLT_FILE_NAME_INFORMATION FileNameInformation)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] FINAL COMPONENT [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->FinalComponent,FileNameInformation->Extension));

	NTSTATUS													Status;
	UNICODE_STRING&												FileName=FileNameInformation->Name;
	PWCH														Buffer=PWCH(ExAllocatePool2(POOL_FLAG_PAGED,FileName.Length,MY_TAG));

	if (Buffer!=nullptr)
	{
		UNICODE_STRING											BackupFileName;

		BackupFileName.Buffer=Buffer;
		BackupFileName.Length=FileName.Length;
		BackupFileName.MaximumLength=FileName.Length;

		wcscpy(BackupFileName.Buffer,FileName.Buffer);

		UNICODE_STRING											BackupExtension{};

		Status=FltParseFileName(&BackupFileName,&BackupExtension,nullptr,nullptr);

		if (NT_SUCCESS(Status)==true)
		{
			for(USHORT Index=0;Index<BackupExtension.Length;Index++)
			{
				// !!!!! Kedze VARIABLE [BackupExtension] odkazuje na ten isty BUFFER ako VARIABLE [BackupFileName], zmenou jednej VARIABLE sa meni aj druha VARIABLE.
				BackupExtension.Buffer[Index]=L'!';
			}

			FileOperationsCreateCopy(FltObjects,FileName,BackupFileName);
		}
		else
		{
			KdPrint(("!!!!! PRE CALLBACK - FAILED to PARSE FILENAME with ERROR CODE [%lX] !!!\n",Status));
		}

		ExFreePoolWithTag(Buffer,MY_TAG);
	}
	else
	{
		KdPrint(("!!!!! PRE CALLBACK - FAILED to ALLOCATE MEMORY !!!\n"));
	}

	FLT_PREOP_CALLBACK_STATUS									CallbackStatus=FLT_PREOP_SUCCESS_NO_CALLBACK;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------