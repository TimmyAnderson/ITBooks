//------------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
void CALLBACK RecurrencyTimerCallback(PVOID Context, BOOLEAN TimerOrWaitFired)
{
	wchar_t			*Message=(wchar_t*) Context;
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d - [%s] BEGIN !\n",GetTickCount(),TID,Message);

	Sleep(3*1000);

	wprintf(L"Time: %d, TID: %d - [%s] END !\n",GetTickCount(),TID,Message);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TestRecurrencyRelativeTimer(void)
{
	const int			COUNT=5;
	HANDLE				TQ;
	HANDLE				Timers[COUNT];
	HANDLE				EventForFirstTimer=CreateEvent(NULL,FALSE,FALSE,NULL);
	HANDLE				EventForTimerGroup=CreateEvent(NULL,FALSE,FALSE,NULL);

	// Vytvorim novu TQ.
	TQ=CreateTimerQueue();

	// Vytvorim TIMERS v danej TQ.
	for (int i=0;i<COUNT;i++)
		CreateTimerQueueTimer(&Timers[i],TQ,RecurrencyTimerCallback,L"Hello World",5*1000,10*1000,0);

	wprintf(L"Time: %d, TIMERS STARTED - press any key to STOP 1. TIMER !\n",GetTickCount());
	_getch();

	// Cakam na skoncenie 1. Timer
	DeleteTimerQueueTimer(TQ,Timers[0],EventForFirstTimer);

	wprintf(L"Time: %d, WAITING FOR EventForFirstTimer !\n",GetTickCount());

	WaitForSingleObject(EventForFirstTimer,INFINITE);

	wprintf(L"Time: %d, EventForFirstTimer WAS SINGALIZED !\n",GetTickCount());
	wprintf(L"Time: %d, Press any key to STOP ALL TIMERS !\n",GetTickCount());
	_getch();

	DeleteTimerQueueEx(TQ,EventForTimerGroup);

	wprintf(L"Time: %d, WAITING FOR EventForTimerGroup !\n",GetTickCount());

	WaitForSingleObject(EventForTimerGroup,INFINITE);

	wprintf(L"Time: %d, EventForTimerGroup WAS SINGALIZED !\n",GetTickCount());

	// Zlikvidujem vsetky Timer okrem toho PRVHEO - ten bol zlikvidovany vyssie.
	for (int i=1;i<COUNT;i++)
		CreateTimerQueueTimer(&Timers[i],TQ,RecurrencyTimerCallback,L"Hello World",5*1000,10*1000,0);

	CloseHandle(EventForFirstTimer);
	CloseHandle(EventForTimerGroup);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	TestRecurrencyRelativeTimer();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------