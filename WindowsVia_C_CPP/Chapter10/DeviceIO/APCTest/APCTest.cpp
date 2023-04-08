#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
void APIENTRY APCFunction(ULONG_PTR Param)
{
	wchar_t*		Data=(wchar_t*) Param;
	wchar_t			Buf[1024];

	StringCchPrintf(Buf,_countof(Buf),L"INSIDE APC, Data: [%s] !\n",Data);
	WriteDebugText(Buf);
}
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	WriteDebugText(L"Worker thread is running and GOING to ALERTABLE WAIT !\n");

	SleepEx(INFINITE,TRUE);

	WriteDebugText(L"Worker thread RETURNED from ALERTABLE WAIT !\n");

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle;

	Handle=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	Sleep(1000);

	WriteDebugText(L"MAIN thread is GOING to POST APC to Worker thread !\n");

	QueueUserAPC(APCFunction,Handle,(ULONG_PTR) L"Timmy Anderson");

	WaitForSingleObject(Handle,INFINITE);

	CloseHandle(Handle);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	Test();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------