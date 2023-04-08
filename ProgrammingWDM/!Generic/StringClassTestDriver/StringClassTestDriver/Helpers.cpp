//-------------------------------------------------------------------------------------------------------
#include "Helpers.h"
#include "Defines.h"
//-------------------------------------------------------------------------------------------------------
ETestMode CHelpers::GetTestModeValueFromFile(const WCHAR* Path)
{
	ETestMode													TestMode=E_TM_ERROR;
	NTSTATUS													Status;
	OBJECT_ATTRIBUTES											Attributes;
	UNICODE_STRING												FilePath;
	ANSI_STRING													FilePathANSI;
	CHAR*														Buffer=NULL;

	// !!!!! PREFIX '\\??\\C:' oznacuje DISK 'C:' pomenovany cez MS DOS NAMING CONVENTION. Namiesto toho by sa dala pouzit aj PATH obsahujuca NAZOV DISKU.
	RtlInitUnicodeString(&FilePath,Path);

	RtlUnicodeStringToAnsiString(&FilePathANSI,&FilePath,TRUE);
	InitializeObjectAttributes(&Attributes,&FilePath,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,NULL,NULL);

	HANDLE														HFile=NULL;

	for(;;)
	{
		IO_STATUS_BLOCK											IoStatusBlock;

		// Otvorim FILE pre WRITE.
		if (NT_SUCCESS(Status=ZwCreateFile(&HFile,GENERIC_READ,&Attributes,&IoStatusBlock,NULL,0,FILE_SHARE_READ,FILE_OPEN,FILE_SYNCHRONOUS_IO_NONALERT,NULL,0))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION GetTestModeValueFromFile(): Can't OPEN FILE [%s], STATUS [%X], IO STATUS [%X] !\n",FilePathANSI.Buffer,Status,IoStatusBlock.Status));
			break;
		}

		FILE_STANDARD_INFORMATION								FileInfo;

		// Ziskam velkost FILE.
		if (NT_SUCCESS(Status=ZwQueryInformationFile(HFile,&IoStatusBlock,&FileInfo,sizeof(FileInfo),FileStandardInformation))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION GetTestModeValueFromFile(): Can't GET FILE [%s] INFO DATA, STATUS [%X], IO STATUS [%X] !\n",FilePathANSI.Buffer,Status,IoStatusBlock.Status));
			break;
		}

		ULONG													FileLength=FileInfo.EndOfFile.LowPart;

		Buffer=(CHAR*) ExAllocatePool(PagedPool,FileLength);

		if (Buffer==NULL)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION GetTestModeValueFromFile(): Can't ALLOCATE MEMORY !\n"));
			break;
		}

		RtlZeroMemory(Buffer,FileLength);

		// Nacitam DATA z FILE.
		if (NT_SUCCESS(Status=ZwReadFile(HFile,NULL,NULL,NULL,&IoStatusBlock,Buffer,FileLength,NULL,NULL))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION GetTestModeValueFromFile(): Can't READ to FILE [%s], STATUS [%X], IO STATUS [%X] !\n",FilePathANSI.Buffer,Status,IoStatusBlock.Status));
			break;
		}

		if (FileLength>0)
		{
			CHAR												TestModeAsChar=Buffer[0];
			ETestMode											TestModeAsEnum=(ETestMode) (TestModeAsChar-'0');

			if (TestModeAsEnum>=E_TM_MIN && TestModeAsEnum<=E_TM_MAX)
			{
				TestMode=TestModeAsEnum;
			}
		}

		break;
	}

	if (HFile!=NULL)
	{
		// Uzatvorim HANDLE.
		if (NT_SUCCESS(ZwClose(HFile))==false)
		{
			KdPrint((DRIVERLOGNAME " - FUNCTION GetTestModeValueFromFile(): Can't CLOSE HANDLE, STATUS [%X] !\n",Status));
		}
	}

	if (Buffer!=NULL)
	{
		ExFreePool(Buffer);
		Buffer=NULL;
	}

	RtlFreeAnsiString(&FilePathANSI);

	return(TestMode);
}
//-------------------------------------------------------------------------------------------------------