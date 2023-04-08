//------------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
int					Counter=0;
//------------------------------------------------------------------------------
void SetAbsoluteTime(FILETIME &FT)
{
	SYSTEMTIME		ST;

	// Ziskam AKTUALNY CAS.
	GetSystemTime(&ST);
	SystemTimeToFileTime(&ST,&FT);

	// Zvysim jeho hodnotu o 3 SEKUNDY. Teda zvysim ABSOLUTNY CAS o 3 SEKUNDY - nie relativny.
	FT.dwLowDateTime+=3*10*1000*1000;
}
//------------------------------------------------------------------------------
void SetRelativeTime(FILETIME &FT)
{
	FT.dwHighDateTime=0;
	// !!! Zaporna hodnota znamena RELATIVNY CAS.
	FT.dwLowDateTime=-3*10*1000*1000;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void CALLBACK TimerCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer)
{
	wchar_t			*Message=(wchar_t*) Context;
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d - [%s] BEGIN !\n",GetTickCount(),TID,Message);

	Sleep(10*1000);

	wprintf(L"Time: %d, TID: %d - [%s] END !\n",GetTickCount(),TID,Message);
}
//------------------------------------------------------------------------------
void CALLBACK RecurencyTimerCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer)
{
	wchar_t			*Message=(wchar_t*) Context;
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d - [%s] !\n",GetTickCount(),TID,Message);

	// Po 3 opakovaniach ZASTAVIM TIMER.
	if (++Counter==3)
	{
		CloseThreadpoolTimer(Timer);
		wprintf(L"Time: %d, TIMER FINISHED !\n",GetTickCount());
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TestNONRecurrencyAbsoluteTimer(void)
{
	PTP_TIMER			Timer;

	Timer=CreateThreadpoolTimer(&TimerCallback,L"Hello World",NULL);

	FILETIME			FT;

	wprintf(L"Time: %d, SETTING TIMER !\n",GetTickCount());

	SetAbsoluteTime(FT);

	SetThreadpoolTimer(Timer,&FT,0,0);

	// Na simulaciu WaitForThreadpoolTimerCallbacks().
	Sleep(4*1000);

	wprintf(L"Time: %d, WAITING for TIMER !\n",GetTickCount());

	// !!!!! Pred samotnym uzavretim Timer BY SOM VZDY mal RESETNUT TIMER, aby nedoslo (pri rekurentnom Timer) k OPETNOVNEMU VOLANIU CALLBACK, ktore mohlo znamenat, ze POCAS VOLANIA CloseThreadpoolWork() by sa SUCASTNE mohol volat CALLBACK, co by viedlo K FATALNEJ CHYBE.
	// !!! Tu to vsak nehrozi, kedze toto NIE JE REKURENTNY TIMER.
	SetThreadpoolTimer(Timer,NULL,0,0);

	// !!!!! Nato aby WaitForThreadpoolTimerCallbacks() bezala MUSI TIMER CALLBACK BYT UZ SPUSTENY. Ak je IBA V QUEUE, tak WaitForThreadpoolTimerCallbacks() OKAMZITE SKONCI.
	WaitForThreadpoolTimerCallbacks(Timer,FALSE);

	CloseThreadpoolTimer(Timer);

	wprintf(L"Time: %d, TIMER FINISHED !\n",GetTickCount());
}
//------------------------------------------------------------------------------
void TestRecurrencyRelativeTimer(void)
{
	PTP_TIMER			Timer;

	Timer=CreateThreadpoolTimer(&RecurencyTimerCallback,L"Hello World",NULL);

	FILETIME			FT;

	SetRelativeTime(FT);

	wprintf(L"Time: %d, SETTING TIMER !\n",GetTickCount());

	// Nastavim RECURRENCY.
	SetThreadpoolTimer(Timer,&FT,10*1000,0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	TestNONRecurrencyAbsoluteTimer();
	//TestRecurrencyRelativeTimer();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------