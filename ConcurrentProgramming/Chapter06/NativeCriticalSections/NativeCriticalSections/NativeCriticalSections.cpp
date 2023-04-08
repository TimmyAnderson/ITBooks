#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
CRITICAL_SECTION		CS;
//-----------------------------------------------------------------------------
unsigned WINAPI WorkerThread(void*)
{
	printf("Worker thread STARTED !\n");

	Sleep(1000);

	while(TryEnterCriticalSection(&CS)==FALSE)
	{
		printf("Worker thread WAS NOT ALLOWED to ENTER CS !\n");
		Sleep(500);
	}

	__try
	{
		printf("Worker thread HOLDS CS !\n");
		Sleep(1000);
	}
	__finally
	{
		LeaveCriticalSection(&CS);
		printf("Worker thread LEAVES CS !\n");
	}

	return(0);
}
//-----------------------------------------------------------------------------
void TestCriticalSection(void)
{
	InitializeCriticalSection(&CS);

	HANDLE		HThread=(HANDLE)_beginthreadex(NULL,0,&WorkerThread,NULL,CREATE_SUSPENDED,NULL);

	printf("Primary thread ENTERS CS !\n");

	EnterCriticalSection(&CS);

	__try
	{
		ResumeThread(HThread);

		printf("Primary thread is GOING TO SLEEP !\n");
		Sleep(3000);
	}
	__finally
	{
		LeaveCriticalSection(&CS);
		printf("Primary thread LEAVES CS !\n");
	}

	WaitForSingleObject(HThread,INFINITE);

	DeleteCriticalSection(&CS);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	TestCriticalSection();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------