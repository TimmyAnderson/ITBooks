//-------------------------------------------------------------------------------------------------------
#include <Ntddk.h>
#include <wdm.h>
#include "Defines.h"
#include "Log.h"
//-------------------------------------------------------------------------------------------------------
CLog::CLog(const wchar_t* Path)
{
	KeInitializeEvent(&MEvent,NotificationEvent,TRUE);

	// !!!!! PREFIX '\\??\\C:' oznacuje DISK 'C:' pomenovany cez MS DOS NAMING CONVENTION. Namiesto toho by sa dala pouzit aj PATH obsahujuca NAZOV DISKU.
	RtlInitUnicodeString(&MFilePath,Path);
	RtlUnicodeStringToAnsiString(&MFilePathANSI,&MFilePath,TRUE);
}
//-------------------------------------------------------------------------------------------------------
CLog::~CLog()
{
	RtlFreeAnsiString(&MFilePathANSI);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CLog::WriteToLog(CLog* Log, char* LogRecord)
{
	if (Log!=NULL)
	{
		Log->WriteToLog(LogRecord);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CLog::WriteToLog(char* LogRecord)
{
	NTSTATUS													Status;

	if (NT_SUCCESS(Status=KeWaitForSingleObject(&MEvent,Executive,KernelMode,FALSE,NULL))==true)
	{
		OBJECT_ATTRIBUTES										Attributes;

		InitializeObjectAttributes(&Attributes,&MFilePath,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,NULL,NULL);

		HANDLE													HFile=NULL;

		for(;;)
		{
			IO_STATUS_BLOCK										IoStatusBlock;

			// Otvorim FILE pre WRITE.
			if (NT_SUCCESS(Status=ZwCreateFile(&HFile,GENERIC_WRITE | FILE_APPEND_DATA | SYNCHRONIZE,&Attributes,&IoStatusBlock,NULL,0,FILE_SHARE_WRITE,FILE_OPEN_IF,FILE_SYNCHRONOUS_IO_NONALERT,NULL,0))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Can't OPEN FILE [%s], STATUS [%X], IO STATUS [%X] !\n",MFilePathANSI.Buffer,Status,IoStatusBlock.Status));
				break;
			}

			FILE_STANDARD_INFORMATION							FileInfo;
			
			// Ziskam velkost FILE.
			if (NT_SUCCESS(Status=ZwQueryInformationFile(HFile,&IoStatusBlock,&FileInfo,sizeof(FileInfo),FileStandardInformation))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Can't GET FILE [%s] INFO DATA, STATUS [%X], IO STATUS [%X] !\n",MFilePathANSI.Buffer,Status,IoStatusBlock.Status));
				break;
			}
			
			ULONG												LogRecordLength=ULONG(strnlen_s(LogRecord,2048));

			// Zapisem DATA do FILE.
			if (NT_SUCCESS(Status=ZwWriteFile(HFile,NULL,NULL,NULL,&IoStatusBlock,LogRecord,LogRecordLength,&FileInfo.EndOfFile,NULL))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Can't WRITE to FILE [%s], STATUS [%X], IO STATUS [%X] !\n",MFilePathANSI.Buffer,Status,IoStatusBlock.Status));
				break;
			}

			break;
		}

		if (HFile!=NULL)
		{
			// Uzatvorim HANDLE.
			if (NT_SUCCESS(ZwClose(HFile))==false)
			{
				KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Can't CLOSE HANDLE, STATUS [%X] !\n",Status));
			}
		}

		KeSetEvent(&MEvent,IO_NO_INCREMENT,FALSE);
	}
	else
	{
		KdPrint((DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): KeWaitForSingleObject() FAILED [%X] !\n",Status));
	}
}
//-------------------------------------------------------------------------------------------------------