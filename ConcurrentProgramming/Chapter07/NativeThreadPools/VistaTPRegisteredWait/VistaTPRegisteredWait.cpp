#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
void CALLBACK MyRWCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WAIT Wait, TP_WAIT_RESULT WaitResult)
{
	wchar_t			*Message=(wchar_t*) Context;
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d, WaitResult: %d - [%s] BEGIN !\n",GetTickCount(),TID,WaitResult,Message);

	if (WaitResult==WAIT_OBJECT_0)
		wprintf(L"OBJECT SIGNALIZED !!!\n");
	else if (WaitResult==WAIT_TIMEOUT)
		wprintf(L"TIMEOUT !!!\n");
	else
		wprintf(L"SOMETHING ELSE HAPPENED !!!\n");

	Sleep(10*1000);

	wprintf(L"Time: %d, TID: %d, WaitResult: %d - [%s] END !\n",GetTickCount(),TID,WaitResult,Message);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	PTP_WAIT			Wait;
	HANDLE				HEvent=CreateEvent(NULL,FALSE,FALSE,NULL);

	Wait=CreateThreadpoolWait(&MyRWCallback,L"Hello World",NULL);

	wprintf(L"Time: %d, SETTING WAIT !\n",GetTickCount());

	SetThreadpoolWait(Wait,HEvent,NULL);

	// Pockam 3 sekundy.
	Sleep(3*1000);

	wprintf(L"Time: %d, EVENT IS SET !\n",GetTickCount());

	// SIGNALIZUJEM Event.
	SetEvent(HEvent);

	wprintf(L"Time: %d, WAITING for WAIT !\n",GetTickCount());

	// !!! Zrusim registraciu Registered Wait.
	SetThreadpoolWait(Wait,NULL,NULL);

	// !!!!! Nato aby SetThreadpoolWait() bezala MUSI WAIT CALLBACK BYT UZ SPUSTENY.
	WaitForThreadpoolWaitCallbacks(Wait,FALSE);

	CloseThreadpoolWait(Wait);
	CloseHandle(HEvent);

	wprintf(L"Time: %d, WAIT FINISHED !\n",GetTickCount());
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