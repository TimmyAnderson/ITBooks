#include "stdafx.h"
#include <windows.h>
#include <StrSafe.h>
//------------------------------------------------------------------------------
// !!!!! Smiem pouzivat funkcie IBA z Kernel32.DLL.
//------------------------------------------------------------------------------
void WriteLogToFile(DWORD ReasonToCall)
{
	const int		CHARS=1024;
	wchar_t			Reason[CHARS];

	if (ReasonToCall==DLL_PROCESS_ATTACH)
		StringCchPrintf(Reason,CHARS,L"PID: [%d] - DLL_PROCESS_ATTACH !\r\n",GetCurrentProcessId());
	else if (ReasonToCall==DLL_THREAD_ATTACH)
		StringCchPrintf(Reason,CHARS,L"PID: [%d] - DLL_THREAD_ATTACH !\r\n",GetCurrentProcessId());
	else if (ReasonToCall==DLL_THREAD_DETACH)
		StringCchPrintf(Reason,CHARS,L"PID: [%d] - DLL_THREAD_DETACH !\r\n",GetCurrentProcessId());
	else if (ReasonToCall==DLL_PROCESS_DETACH)
		StringCchPrintf(Reason,CHARS,L"PID: [%d] - DLL_PROCESS_DETACH !\r\n",GetCurrentProcessId());
	else
		StringCchPrintf(Reason,CHARS,L"PID: [%d] - UNKNOWN !\r\n",GetCurrentProcessId());

	size_t			StringSize=0;

	StringCchLength(Reason,CHARS,&StringSize);

	HANDLE			Handle=CreateFile(L"C:\\RegistryHook.txt",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		SetFilePointer(Handle,0,NULL,FILE_END);

		DWORD		NumberOfBytesWritten=0;

		// !!! NumberOfBytesWritten NESMIE BYT NULL vo WriteFile() - inak to CELE ZBLBNE.
		WriteFile(Handle,(void*) Reason,StringSize*sizeof(wchar_t),&NumberOfBytesWritten,NULL);

		CloseHandle(Handle);
	}
}
//------------------------------------------------------------------------------
BOOL APIENTRY DllMain(HMODULE Module, DWORD ReasonForCall, LPVOID Reserved)
{
	WriteLogToFile(ReasonForCall);

	return(TRUE);
}
//------------------------------------------------------------------------------