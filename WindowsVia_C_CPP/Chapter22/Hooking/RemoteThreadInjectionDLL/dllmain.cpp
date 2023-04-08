#include "stdafx.h"
#include <StrSafe.h>
//------------------------------------------------------------------------------
void WriteToFile(wchar_t* Text)
{
	const int		CHARS=1024;
	wchar_t			Buffer[CHARS];

	StringCchPrintf(Buffer,CHARS,L"PID: [%d] - Text: [%s] !\r\n",GetCurrentProcessId(),Text);

	size_t			StringSize=0;

	StringCchLength(Buffer,CHARS,&StringSize);

	HANDLE			Handle=CreateFile(L"C:\\RemoteThreadInjection.txt",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

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
void InjectedDLLLoaded(void)
{
	WriteToFile(L"DLL LOADED");
}
//------------------------------------------------------------------------------
void InjectedDLLUnoaded(void)
{
	WriteToFile(L"DLL UNLOADED");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
BOOL APIENTRY DllMain(HMODULE Module, DWORD ReasonForCall, LPVOID Reserved)
{
	if (ReasonForCall==DLL_PROCESS_ATTACH)
		InjectedDLLLoaded();
	else if (ReasonForCall==DLL_PROCESS_DETACH)
		InjectedDLLUnoaded();

	return(TRUE);
}
//------------------------------------------------------------------------------