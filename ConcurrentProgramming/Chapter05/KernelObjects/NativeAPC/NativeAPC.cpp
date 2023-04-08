#include "stdafx.h"
#include <process.h>
#include "MyDebug.h"
#include "WaitHelper.h"
//-----------------------------------------------------------------------------
HANDLE			ExitHandle=NULL;
//-----------------------------------------------------------------------------
void WINAPI MyAPCFunction(ULONG_PTR Param)
{
	wchar_t*		Text=(wchar_t*) Param;

	wprintf(L"MyAPCFunction(): [%s] !\n",Text);
}
//-----------------------------------------------------------------------------
unsigned WINAPI NonAlertableThread(void*)
{
	// !!! Kedze sa jedna o NON-ALERTABLE WAIT, tak APC ho NEPRERUSI.
	DWORD	Ret=WaitForSingleObjectEx(ExitHandle,INFINITE,FALSE);

	if (Ret==WAIT_OBJECT_0)
		wprintf(L"OBJECT SIGNALIZED !\n");
	else if (Ret==WAIT_TIMEOUT)
		wprintf(L"TIMEOUT !\n");
	else if (Ret==WAIT_IO_COMPLETION)
		wprintf(L"APC !\n");
	else
		wprintf(L"UNEXPECTED VALUE !\n");

	return(0);
}
//-----------------------------------------------------------------------------
unsigned WINAPI AlertableThread(void*)
{
	while(true)
	{
		// !!! Kedze sa jedna o ALERTABLE WAIT, tak APC ho PRERUSI.
		DWORD	Ret=WaitForSingleObjectEx(ExitHandle,INFINITE,TRUE);

		if (Ret==WAIT_OBJECT_0)
		{
			wprintf(L"OBJECT SIGNALIZED !\n");
			break;
		}
		else if (Ret==WAIT_TIMEOUT)
		{
			wprintf(L"TIMEOUT !\n");
			break;
		}
		// !!!!! OPAKUJE WAIT.
		else if (Ret==WAIT_IO_COMPLETION)
			wprintf(L"APC !\n");
		else
		{
			wprintf(L"UNEXPECTED VALUE !\n");
			break;
		}
	}

	return(0);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNonAlertableWait(void)
{
	HANDLE		HThread=(HANDLE)_beginthreadex(NULL,0,&NonAlertableThread,NULL,0,NULL);

	ExitHandle=CreateEvent(NULL,FALSE,FALSE,NULL);

	Sleep(1000);

	wprintf(L"APC WILL be ENQUEUED !\n");
	QueueUserAPC(&MyAPCFunction,HThread,(ULONG_PTR) L"Hello APC !");
	wprintf(L"APC WAS ENQUEUED !\n");
	Sleep(3000);

	wprintf(L"EXIT EVENT WILL be FIRED !\n");
	SetEvent(ExitHandle);
	wprintf(L"EXIT EVENT WAS FIRED !\n");

	WaitForSingleObject(HThread,INFINITE);
	wprintf(L"THREAD FINISHED !\n");

	CloseHandle(ExitHandle);
	CloseHandle(HThread);
}
//-----------------------------------------------------------------------------
void TestAlertableWait(void)
{
	HANDLE		HThread=(HANDLE)_beginthreadex(NULL,0,&AlertableThread,NULL,0,NULL);

	ExitHandle=CreateEvent(NULL,FALSE,FALSE,NULL);

	Sleep(1000);

	wprintf(L"APC WILL be ENQUEUED !\n");
	QueueUserAPC(&MyAPCFunction,HThread,(ULONG_PTR) L"Hello APC !");
	wprintf(L"APC WAS ENQUEUED !\n");
	Sleep(3000);

	wprintf(L"EXIT EVENT WILL be FIRED !\n");
	SetEvent(ExitHandle);
	wprintf(L"EXIT EVENT WAS FIRED !\n");

	WaitForSingleObject(HThread,INFINITE);
	wprintf(L"THREAD FINISHED !\n");

	CloseHandle(ExitHandle);
	CloseHandle(HThread);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	TestNonAlertableWait();
	//TestAlertableWait();


	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------