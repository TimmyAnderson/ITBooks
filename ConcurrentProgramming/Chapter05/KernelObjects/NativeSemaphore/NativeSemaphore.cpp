#include "stdafx.h"
#include <process.h>
#include <windows.h>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
HANDLE			Semaphore;
//-----------------------------------------------------------------------------
struct ThreadParams
{
	HANDLE			ExitHandle;
	wchar_t			*Text;
};
//-----------------------------------------------------------------------------
unsigned WINAPI MutexThread(void* Param)
{
	ThreadParams	*TP=(ThreadParams*)Param;
	wchar_t			*Text=TP->Text;
	HANDLE			Handles[]={TP->ExitHandle,Semaphore};

	while(true)
	{
		DWORD	Ret=WaitForMultipleObjects(sizeof(Handles)/sizeof(Handles[0]),Handles,FALSE,INFINITE);

		if (Ret==WAIT_OBJECT_0)
		{
			wprintf(L"%s - EXIT HANDLE SIGNALIZED !\n",Text);
			break;
		}
		// Nerobim ReleaseSemaphore()
		else if (Ret==(WAIT_OBJECT_0+1))
		{
			wprintf(L"%s - SEMAPHORE SIGNALIZED !\n",Text);
			Sleep(300);
		}
		else
			wprintf(L"%s - UNEXPECTED VALUE !\n",Text);
	}

	return(0);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleSempahore(void)
{
	Semaphore=CreateSemaphore(NULL,5,5,NULL);

	HANDLE			ExitHandle=CreateEvent(NULL,FALSE,FALSE,NULL);
	ThreadParams	TP[]={{ExitHandle,L"WORKER"}};
	HANDLE			HThread=(HANDLE)_beginthreadex(NULL,0,MutexThread,&TP[0],0,NULL);

	Sleep(3000);

	wprintf(L"!!! RELEASING SEMAPHORE !\n");
	ReleaseSemaphore(Semaphore,5,NULL);

	Sleep(3000);

	wprintf(L"EXIT EVENT WILL be FIRED !\n");
	SetEvent(ExitHandle);
	wprintf(L"EXIT EVENT WAS FIRED !\n");

	WaitForSingleObject(HThread,INFINITE);
	wprintf(L"THREAD FINISHED !\n");

	CloseHandle(ExitHandle);
	CloseHandle(HThread);
	CloseHandle(Semaphore);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	TestSimpleSempahore();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------