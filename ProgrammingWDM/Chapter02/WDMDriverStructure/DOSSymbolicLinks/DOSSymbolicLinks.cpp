//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
//-------------------------------------------------------------------------------------------------------
void ReadFile(wchar_t* Filename)
{
	HANDLE														FileHandle=CreateFile(Filename,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	while(true)
	{
		if (FileHandle==INVALID_HANDLE_VALUE)
		{
			wprintf_s(L"Can't OPEN FILE [%s] !\n",Filename);
			break;
		}

		char														Buffer[1000];
		DWORD														NumberOfBytesRead;

		if (ReadFile(FileHandle,Buffer,_countof(Buffer)-1,&NumberOfBytesRead,NULL)==FALSE)
		{
			wprintf_s(L"Can't READ FILE [%s] !\n",Filename);
			break;
		}

		Buffer[NumberOfBytesRead]='\0';

		wprintf_s(L"FILE [%s] - ",Filename);
		printf_s("FILE CONTENT [%s] !\n",Buffer);

		break;
	}

	if (FileHandle!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(FileHandle);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// FUNCTION zobrazi VSETKY DOS DEVICE NAMES.
void Test1(void)
{
	wchar_t														Buffer[1024*100];
	DWORD														Length=QueryDosDevice(NULL,Buffer,1024*100);

	if (Length>0)
	{
		wchar_t*												Iterator=Buffer;
		int														Counter=0;

		while(true)
		{
			if (*Iterator=='\0')
			{
				break;
			}

			size_t												MaxBufferLength=_countof(Buffer)-(Buffer-Iterator);
			size_t												DosNameLength=wcsnlen_s(Iterator,MaxBufferLength);

			wprintf_s(L"%d. [%s] !\n",++Counter,Iterator);

			Iterator+=DosNameLength+1;
		}
	}
	else
	{
		wprintf_s(L"Can't QUERY DOS DEVICES !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION zobrazi DOS DEVICE NAME pre DISK [C:].
void Test2(void)
{
	wchar_t														Buffer[1024*100];
	DWORD														Length=QueryDosDevice(L"C:",Buffer,1024*100);

	if (Length>0)
	{
		wchar_t*												Iterator=Buffer;
		int														Counter=0;

		while(true)
		{
			if (*Iterator=='\0')
			{
				break;
			}

			size_t												MaxBufferLength=_countof(Buffer)-(Buffer-Iterator);
			size_t												DosNameLength=wcsnlen_s(Iterator,MaxBufferLength);

			wprintf_s(L"%d. [%s] !\n",++Counter,Iterator);

			Iterator+=DosNameLength+1;
		}
	}
	else
	{
		wprintf_s(L"Can't QUERY DOS DEVICES !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION vytvara vlastny SYMBOLIC LINK.
// !!! Predpoklada sa, ze CURRENT DIRECTORY sa nachadza FILE [SomeText.txt].
void Test3(void)
{
	wchar_t														Path[1000];
	wchar_t														VolumeDosName[3];

	while(true)
	{
		if (GetCurrentDirectory(_countof(Path),Path)==0)
		{
			wprintf_s(L"Can't get CURRENT DIRECTORY !\n");
			break;
		}

		if (wcsncpy_s(VolumeDosName,Path,2)!=0)
		{
			wprintf_s(L"Can't get VOLUME NAME !\n");
			break;
		}

		if (wcscat_s(Path,L"\\SomeText.txt")!=0)
		{
			wprintf_s(L"Can't get CONCAT PATH !\n");
			break;
		}

		wprintf_s(L"PATH [%s] !\n",Path);

		ReadFile(Path);

		wchar_t													VolumeBuffer[1024];
		DWORD													QueryDosDeviceLength=QueryDosDevice(VolumeDosName,VolumeBuffer,_countof(VolumeBuffer));

		if (QueryDosDeviceLength==0)
		{
			wprintf_s(L"Can't get SYMBOLIC LINK for DOS NAME [%s] !\n",VolumeDosName);
			break;
		}
		else
		{
			wprintf_s(L"DOS NAME [%s] has SYMBOLIC LINK [%s] !\n",VolumeDosName,VolumeBuffer);
		}

		wchar_t*										VolumePath=VolumeBuffer;
		wchar_t*										FilePathWithoutDiskName=Path+2;
		wchar_t											VolumeFilePath[1000];

		if (swprintf_s(VolumeFilePath,L"%s%s",VolumePath,FilePathWithoutDiskName)==0)
		{
			wprintf_s(L"Can't PREPARE VOLUME PATH !\n");
			break;
		}

		wprintf_s(L"SYMBOLIC NAME PATH [%s] !\n",VolumeFilePath);

		wchar_t*												SymbolicLinkName=L"MySymbolicLink";

		// !!!!! Po uspesnom volani je LINK VIDIET v WinObj.exe.
		if (DefineDosDevice(DDD_RAW_TARGET_PATH,SymbolicLinkName,VolumeFilePath)==FALSE)
		{
			wprintf_s(L"Can't CREATE SYMBOLIC LINK !\n");
			break;
		}

		wchar_t											VolumeFilePathWithPrefix[1000];

		if (swprintf_s(VolumeFilePathWithPrefix,L"\\\\.\\%s",SymbolicLinkName)==0)
		{
			wprintf_s(L"Can't PREPARE VOLUME PATH with PREFIX !\n");

			// !!! Odstrani sa SYMBOLIC LINK.
			if (DefineDosDevice(DDD_RAW_TARGET_PATH | DDD_REMOVE_DEFINITION,SymbolicLinkName,VolumeFilePath)==FALSE)
			{
				wprintf_s(L"Can't DELETE SYMBOLIC LINK !\n");
			}

			break;
		}

		// !!! FILE sa nacita cez SYMBOLIC LINK.
		ReadFile(VolumeFilePathWithPrefix);

		// !!! Odstrani sa SYMBOLIC LINK.
		if (DefineDosDevice(DDD_RAW_TARGET_PATH | DDD_REMOVE_DEFINITION,SymbolicLinkName,VolumeFilePath)==FALSE)
		{
			wprintf_s(L"Can't DELETE SYMBOLIC LINK !\n");
			break;
		}

		break;
	}
}
//-------------------------------------------------------------------------------------------------------
// FUNCTION vytvara vlastny SYMBOLIC LINK na PATH [C:\WINDOWS].
void Test4(void)
{
	wchar_t														VolumeDosName[]=L"C:";

	while(true)
	{
		wchar_t													VolumeBuffer[1024];
		DWORD													QueryDosDeviceLength=QueryDosDevice(VolumeDosName,VolumeBuffer,_countof(VolumeBuffer));

		if (QueryDosDeviceLength==0)
		{
			wprintf_s(L"Can't get SYMBOLIC LINK for DOS NAME [%s] !\n",VolumeDosName);
			break;
		}
		else
		{
			wprintf_s(L"DOS NAME [%s] has SYMBOLIC LINK [%s] !\n",VolumeDosName,VolumeBuffer);
		}

		wchar_t											Path[]=L"\\WINDOWS\\";
		wchar_t*										VolumePath=VolumeBuffer;
		wchar_t											SymbolicLinkDirectoryPath[1000];

		if (swprintf_s(SymbolicLinkDirectoryPath,L"%s%s",VolumePath,Path)==0)
		{
			wprintf_s(L"Can't PREPARE VOLUME PATH !\n");
			break;
		}

		wprintf_s(L"SYMBOLIC NAME PATH [%s] !\n",SymbolicLinkDirectoryPath);

		wchar_t*												SymbolicLinkName=L"MyDir";

		// !!!!! Po uspesnom volani je LINK VIDIET v WinObj.exe.
		if (DefineDosDevice(DDD_RAW_TARGET_PATH,SymbolicLinkName,SymbolicLinkDirectoryPath)==FALSE)
		{
			wprintf_s(L"Can't CREATE SYMBOLIC LINK !\n");
			break;
		}

		wchar_t											PathWithPrefix[1000];

		if (swprintf_s(PathWithPrefix,L"\\\\.\\%s\\",SymbolicLinkName)==0)
		{
			wprintf_s(L"Can't PREPARE PATH with PREFIX !\n");

			// !!! Odstrani sa SYMBOLIC LINK.
			if (DefineDosDevice(DDD_RAW_TARGET_PATH | DDD_REMOVE_DEFINITION,SymbolicLinkName,SymbolicLinkDirectoryPath)==FALSE)
			{
				wprintf_s(L"Can't DELETE SYMBOLIC LINK !\n");
			}

			break;
		}

		if (SetCurrentDirectory(PathWithPrefix)==FALSE)
		{
			wprintf_s(L"Can't SET DIRECTORY by SYMBOLIC LINK !\n");
		}
		else
		{
			wprintf_s(L"CURRENT DIRECTORY set by SYMBOLIC LINK to [%s] !\n",PathWithPrefix);
		}

		// !!!!! Teraz je mozne zmenit DIRECTORY aj vo FAR MANAGER pomocou SYMBOLIC LINK.
		wprintf_s(L"\nNow command [cd \\\\.\\%s] will work even in FAR MANAGER !\n\n",SymbolicLinkName);
		wprintf_s(L"Press any KEY to CONTINUE !\n");
		_getch();

		// !!! Odstrani sa SYMBOLIC LINK.
		// !!!!! Ak sa vytvori TA ISTA SYMBOLIC LINK VIACKRAT, je nu NUTNE aj VIACKRAT UVOLNIT, aby sa zrusila jej platnost.
		if (DefineDosDevice(DDD_RAW_TARGET_PATH | DDD_REMOVE_DEFINITION,SymbolicLinkName,SymbolicLinkDirectoryPath)==FALSE)
		{
			wprintf_s(L"Can't DELETE SYMBOLIC LINK !\n");
			break;
		}

		break;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int wmain(int argc, wchar_t* argv[])
{
	//Test1();
	//Test2();
	//Test3();
	Test4();

	wprintf_s(L"Press any KEY to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------