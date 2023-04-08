//-------------------------------------------------------------------------------------------------------
#include <Ntddk.h>
#include <wdm.h>
#include "Defines.h"
#include "FileLogger.h"
//-------------------------------------------------------------------------------------------------------
CFileLogger::CFileLogger(const wchar_t* Path)
{
	KeInitializeEvent(&MEvent,NotificationEvent,TRUE);

	// !!!!! PREFIX '\\??\\C:' oznacuje DISK 'C:' pomenovany cez MS DOS NAMING CONVENTION. Namiesto toho by sa dala pouzit aj PATH obsahujuca NAZOV DISKU.
	RtlInitUnicodeString(&MFilePath,Path);

	NTSTATUS													Status;

	if (NT_SUCCESS(Status=RtlUnicodeStringToAnsiString(&MFilePathANSI,&MFilePath,TRUE))==false)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): RtlUnicodeStringToAnsiString() FAILED [%X] !\n",Status);
	}
}
//-------------------------------------------------------------------------------------------------------
CFileLogger::~CFileLogger()
{
	RtlFreeAnsiString(&MFilePathANSI);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CFileLogger::WriteToLog(CFileLogger* Log, char* LogRecord)
{
	if (Log!=NULL)
	{
		Log->WriteToLog(LogRecord);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CFileLogger::WriteToLog(char* LogRecord)
{
	NTSTATUS													Status;

	if (NT_SUCCESS(Status=KeWaitForSingleObject(&MEvent,Executive,KernelMode,FALSE,NULL))==true)
	{
		OBJECT_ATTRIBUTES										Attributes;

		InitializeObjectAttributes(&Attributes,&MFilePath,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,NULL,NULL);

		HANDLE													HFile=NULL;
		IO_STATUS_BLOCK											IoStatusBlock;

		// Otvorim FILE pre WRITE.
		if (NT_SUCCESS(Status=ZwCreateFile(&HFile,GENERIC_WRITE | FILE_APPEND_DATA | SYNCHRONIZE,&Attributes,&IoStatusBlock,NULL,0,FILE_SHARE_WRITE,FILE_OPEN_IF,FILE_SYNCHRONOUS_IO_NONALERT,NULL,0))==true)
		{
			FILE_STANDARD_INFORMATION							FileInfo;
			
			// Ziskam velkost FILE.
			if (NT_SUCCESS(Status=ZwQueryInformationFile(HFile,&IoStatusBlock,&FileInfo,sizeof(FileInfo),FileStandardInformation))==true)
			{
				ULONG											LogRecordLength=ULONG(strnlen_s(LogRecord,2048));

				// Zapisem DATA do FILE.
				if (NT_SUCCESS(Status=ZwWriteFile(HFile,NULL,NULL,NULL,&IoStatusBlock,LogRecord,LogRecordLength,&FileInfo.EndOfFile,NULL))==false)
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Can't WRITE to FILE [%s], STATUS [%X] !\n",MFilePathANSI.Buffer,Status);
				}
			}
			else
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Can't GET FILE [%s] INFO DATA, STATUS [%X] !\n",MFilePathANSI.Buffer,Status);
			}

			if (HFile!=NULL)
			{
				// Uzatvorim HANDLE.
				if (NT_SUCCESS(ZwClose(HFile))==false)
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Can't CLOSE HANDLE, STATUS [%X] !\n",Status);
				}
			}
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Can't OPEN FILE [%s], STATUS [%X] !\n",MFilePathANSI.Buffer,Status);
		}

		KeSetEvent(&MEvent,IO_NO_INCREMENT,FALSE);
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status);
	}
}
//-------------------------------------------------------------------------------------------------------