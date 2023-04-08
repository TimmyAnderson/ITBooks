#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
int					TIMER=1000;
//------------------------------------------------------------------------------
void WriteToFile(wchar_t* Text)
{
	const int		CHARS=1024;
	wchar_t			Buffer[CHARS];

	StringCchPrintf(Buffer,CHARS,L"PID: [%d] - Text: [%s] !\r\n",GetCurrentProcessId(),Text);

	size_t			StringSize=0;

	StringCchLength(Buffer,CHARS,&StringSize);

	HANDLE			Handle=CreateFile(L"C:\\MyRecoveryLog.txt",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		SetFilePointer(Handle,0,NULL,FILE_END);

		DWORD		NumberOfBytesWritten=0;
		DWORD		Size=((DWORD)StringSize)*sizeof(wchar_t);

		// !!! NumberOfBytesWritten NESMIE BYT NULL vo WriteFile() - inak to CELE ZBLBNE.
		WriteFile(Handle,(void*) Buffer,Size,&NumberOfBytesWritten,NULL);

		CloseHandle(Handle);
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
DWORD WINAPI MyRecoveryCallback(PVOID Parameter)
{
	BOOL			Result=FALSE;
	int				MAX_COUNTER=10;
	int				Counter=1;

	while(true)
	{
		// !!!!! Tu nesmiem pisat na KONZOLU.
		WriteToFile(L"!!! Recovering...\n");

		BOOL		Cancelled=FALSE;

		if (ApplicationRecoveryInProgress(&Cancelled)!=S_OK)
		{
			WriteToFile(L"RegisterApplicationRestart() FAILED to CALL !\n");
			break;
		}

		if (Cancelled==TRUE)
		{
			WriteToFile(L"Recovery WAS CANCELLED !\n");
			Sleep(TIMER/2);
			break;
		}

		Sleep(TIMER);

		if (Counter++>=MAX_COUNTER)
		{
			WriteToFile(L"Recovery FINISHED !\n");
			Sleep(TIMER/2);
			Result=TRUE;
			break;
		}
	}
	
	ApplicationRecoveryFinished(Result);

	return(0);
}
//------------------------------------------------------------------------------
void RegisterForRestart(void)
{
	// Dam nejake data do COMMAND LINE, aby som mohol pri RESTART detekovat, ze program bol RESTARTED.
	if (RegisterApplicationRestart(L"SomeData",0)==S_OK)
		wprintf_s(L"RegisterApplicationRestart() SUCCESSFULLY CALLED !\n");
	else
		wprintf_s(L"RegisterApplicationRestart() FAILED to CALL !\n");

	if (RegisterApplicationRecoveryCallback(MyRecoveryCallback,NULL,TIMER*2,0)==S_OK)
		wprintf_s(L"RegisterApplicationRecoveryCallback() SUCCESSFULLY CALLED !\n");
	else
		wprintf_s(L"RegisterApplicationRecoveryCallback() FAILED to CALL !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(int Argc)
{
	if (Argc==1)
	{
		RegisterForRestart();

		wprintf_s(L"\n!!! PRESS ANY KEY to GENERATE UNHANDLED EXCEPTION !\n");
		wprintf_s(L"!!!!! Program MUST RUN for 60+ seconds to be RESTARTED after CRASH !\n");
		_getch();

		BYTE*		Temp=(BYTE*) 0x200;

		// Vyvolam EXCEPTION.
		*Temp=100;
	}
	else
		wprintf_s(L"PROGRAM WAS RESTARTED !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int Argc, _TCHAR* argv[])
{
	SafeMain();

	Test(Argc);

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------