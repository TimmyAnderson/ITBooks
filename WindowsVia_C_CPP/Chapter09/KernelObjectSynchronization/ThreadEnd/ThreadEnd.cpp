#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	wprintf_s(L"Worker thread is runnting !\n");

	Sleep(1000);

	wprintf_s(L"Worker thread finished !\n");

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle;

	Handle=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	// Ked skonci thread, tak KO je STALE SIGNALIZOVANY.
	for (int i=0;i<10;i++)
	{
		if (WaitForSingleObject(Handle,INFINITE)==WAIT_OBJECT_0)
			wprintf_s(L"Thread KO WAS SIGNALIZED !\n");
		else
			wprintf_s(L"ERROR !\n");
	}

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