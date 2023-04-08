//------------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
// !!! Toto je specialny handle, ktory sa NESMIE LIKVIDOVAT cez CloseHandle(), ale cez UnregisterWait(), alebo UnregisterWaitEx().
HANDLE				RegistrationHandle;
//------------------------------------------------------------------------------
void CALLBACK RWCallback(PVOID Context, BOOLEAN TimerOrWaitFired)
{
	wchar_t			*Message=(wchar_t*) Context;
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d - [%s] BEGIN !\n",GetTickCount(),TID,Message);

	if (TimerOrWaitFired==FALSE)
		wprintf(L"Time: %d, TID: %d - EVENT WAS FIRED !\n",GetTickCount(),TID);
	else
		wprintf(L"Time: %d, TID: %d - TIMEOUT EXPIRED !\n",GetTickCount(),TID);

	Sleep(5*1000);

	wprintf(L"Time: %d, TID: %d - [%s] END !\n",GetTickCount(),TID,Message);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TestRecurrencyRelativeTimer(void)
{
	HANDLE				EventToWait=CreateEvent(NULL,FALSE,FALSE,NULL);
	HANDLE				EventForUnregister=CreateEvent(NULL,FALSE,FALSE,NULL);

	RegisterWaitForSingleObject(&RegistrationHandle,EventToWait,RWCallback,L"Hello World",10*1000,0);

	wprintf(L"Time: %d, RW STARTED - press any key to SET EVENT - or WAIT 10 seconds to TIMEOUT !\n",GetTickCount());
	_getch();

	SetEvent(EventToWait);

	wprintf(L"Time: %d, RW GOING to UNREGISTER RW !\n",GetTickCount());

	UnregisterWaitEx(RegistrationHandle,EventForUnregister);

	wprintf(L"Time: %d, WAITING FOR EventForUnregister !\n",GetTickCount());

	WaitForSingleObject(EventForUnregister,INFINITE);

	wprintf(L"Time: %d, EventForUnregister WAS UNREGISTRED !\n",GetTickCount());

	CloseHandle(EventToWait);
	CloseHandle(EventForUnregister);
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