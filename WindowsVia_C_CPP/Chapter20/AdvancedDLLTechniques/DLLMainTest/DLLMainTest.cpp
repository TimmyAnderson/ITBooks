#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
unsigned int WINAPI SubWorkerThread(void* Param)
{
	wprintf_s(L"SUBWORKER THREAD - PID: [%d], TID: [%d] !\n",GetCurrentProcessId(),GetCurrentThreadId());

	Sleep(1000);

	return(0);
}
//------------------------------------------------------------------------------
unsigned int WINAPI WorkerThread(void* Param)
{
	wprintf_s(L"WORKER THREAD - PID: [%d], TID: [%d] !\n",GetCurrentProcessId(),GetCurrentThreadId());

	Sleep(1000);

	HANDLE				Handle;

	Handle=(HANDLE)_beginthreadex(NULL,0,SubWorkerThread,NULL,0,NULL);

	WaitForSingleObject(Handle,INFINITE);

	return(0);
}
//------------------------------------------------------------------------------
void Test(void)
{
	wprintf_s(L"MAIN THREAD - PID: [%d], TID: [%d] !\n",GetCurrentProcessId(),GetCurrentThreadId());

	HMODULE					HDLL=LoadLibrary(L"..//EmptyDLL//Debug//EmptyDLL.dll");

	HANDLE				Handle;

	Handle=(HANDLE)_beginthreadex(NULL,0,WorkerThread,NULL,0,NULL);

	WaitForSingleObject(Handle,INFINITE);

	CloseHandle(Handle);

	FreeLibrary(HDLL);
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