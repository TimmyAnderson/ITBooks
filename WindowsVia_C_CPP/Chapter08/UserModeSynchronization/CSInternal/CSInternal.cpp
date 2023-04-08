#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
CRITICAL_SECTION		CS;
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	wchar_t		Buffer[1024];
	int			Size=_countof(Buffer);

	StringCchPrintf(Buffer,Size,L"Before CS [%d] !\n",CS.LockSemaphore);
	WriteDebugText(Buffer);

	// !!!!! Program demonstruje, ze EVENT KO (CS.LockSemaphore) sa vytvori AZ KED DOJDE KU CONTENTION
	EnterCriticalSection(&CS);

	StringCchPrintf(Buffer,Size,L"Inside CS [%d] !\n",CS.LockSemaphore);
	WriteDebugText(Buffer);

	Sleep(3000);

	LeaveCriticalSection(&CS);

	StringCchPrintf(Buffer,Size,L"After CS [%d] !\n",CS.LockSemaphore);
	WriteDebugText(Buffer);

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle1;
	HANDLE				Handle2;
	HANDLE				Handle3;

	InitializeCriticalSection(&CS);

	Handle1=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	Sleep(1000);

	Handle2=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);
	Handle3=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	WaitForSingleObject(Handle1,INFINITE);
	WaitForSingleObject(Handle2,INFINITE);
	WaitForSingleObject(Handle3,INFINITE);

	DeleteCriticalSection(&CS);

	CloseHandle(Handle1);
	CloseHandle(Handle2);
	CloseHandle(Handle3);
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