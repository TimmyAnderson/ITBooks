#include "stdafx.h"
#include <StrSafe.h>
#include "CreateRemoteThreadDLL.h"
//------------------------------------------------------------------------------
// !!!!! DLL MUSI BYT zadefinovana ako FIXED, aby funkcie boli NA ROVNAKEJ ADRESE vo VSETKYCH PROCESOCH.
//------------------------------------------------------------------------------
void WriteToFile(wchar_t* Text)
{
	const int		CHARS=1024;
	wchar_t			Buffer[CHARS];

	StringCchPrintf(Buffer,CHARS,L"PID: [%d] - Text: [%s] !\r\n",GetCurrentProcessId(),Text);

	size_t			StringSize=0;

	StringCchLength(Buffer,CHARS,&StringSize);

	HANDLE			Handle=CreateFile(L"C:\\RemoteThreadCreation.txt",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		SetFilePointer(Handle,0,NULL,FILE_END);

		DWORD		NumberOfBytesWritten=0;

		// !!! NumberOfBytesWritten NESMIE BYT NULL vo WriteFile() - inak to CELE ZBLBNE.
		WriteFile(Handle,(void*) Buffer,StringSize*sizeof(wchar_t),&NumberOfBytesWritten,NULL);

		CloseHandle(Handle);
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DLLLoadTest(void)
{
	wprintf_s(L"DLL is LOADED in PROCESS !\n");
}
//------------------------------------------------------------------------------
// Toto je THREAD funkcia, ktora bude realizovat THREAD vytvoreny v INOM PROCESE.
DWORD WINAPI RemoteThreadFunction(LPVOID Parameter)
{
	WriteToFile(L"REMOTE thread EXECUTED - PHASE 1");
	wprintf_s(L"PID: [%d] - REMOTE thread EXECUTED - PHASE 1 !\n",GetCurrentProcessId());

	Sleep(2000);

	WriteToFile(L"REMOTE thread EXECUTED - PHASE 2");
	wprintf_s(L"PID: [%d] - REMOTE thread EXECUTED - PHASE 2 !\n",GetCurrentProcessId());

	return(0);
}
//------------------------------------------------------------------------------