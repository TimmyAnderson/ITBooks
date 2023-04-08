#include "stdafx.h"
#include <process.h>
#include <windows.h>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
void TestAbsoluteWaitableTimerNoCycle(void)
{
	HANDLE			WT=CreateWaitableTimer(NULL,FALSE,NULL);
	SYSTEMTIME		ST;
	FILETIME		FT;
	LARGE_INTEGER	LI;

	// Ziskam AKTUALNY CAS.
	GetSystemTime(&ST);
	SystemTimeToFileTime(&ST,&FT);

	// Zvysim jeho hodnotu o 3 SEKUNDY. Teda zvysim ABSOLUTNY CAS o 5 SEKUNDY - nie relativny.
	FT.dwLowDateTime+=3*10*1000*1000;

	LI.HighPart=FT.dwHighDateTime;
	LI.LowPart=FT.dwLowDateTime;

	// Periodicita je ==0.
	SetWaitableTimer(WT,&LI,0,NULL,NULL,FALSE);

	wprintf(L"WAIT STARTED !\n");

	while(true)
	{
		DWORD			Ret=WaitForSingleObject(WT,10*1000);

		if (Ret==WAIT_OBJECT_0)
			wprintf(L"!!! WAIT TIMER OCCURED !\n");
		else if (Ret==WAIT_TIMEOUT)
		{
			wprintf(L"TIMEOUT !\n");
			break;
		}
		else
			wprintf(L"UNEXPECTED VALUE !\n");
	}
}
//-----------------------------------------------------------------------------
void TestAbsoluteWaitableTimerWithCycle(void)
{
	HANDLE			WT=CreateWaitableTimer(NULL,FALSE,NULL);
	SYSTEMTIME		ST;
	FILETIME		FT;
	LARGE_INTEGER	LI;

	// Ziskam AKTUALNY CAS.
	GetSystemTime(&ST);
	SystemTimeToFileTime(&ST,&FT);

	// Zvysim jeho hodnotu o 3 SEKUNDY. Teda zvysim ABSOLUTNY CAS o 3 SEKUNDY - nie relativny.
	FT.dwLowDateTime+=3*10*1000*1000;

	LI.HighPart=FT.dwHighDateTime;
	LI.LowPart=FT.dwLowDateTime;

	// Periodicita je ==5 sekund.
	SetWaitableTimer(WT,&LI,5*1000,NULL,NULL,FALSE);

	int			Counter=0;

	// Len na otestovanie, ze je to prave SetWaitableTimer(), ktory startuje Timer.
	//Sleep(3*1000);

	wprintf(L"WAIT STARTED !\n");

	while(true)
	{
		DWORD			Ret=WaitForSingleObject(WT,10*1000);

		if (Ret==WAIT_OBJECT_0)
		{
			wprintf(L"!!! WAIT TIMER OCCURED !\n");

			if (Counter++>=5)
			{
				// Resetnem Timer - da sa aj cez SetWaitableTimer().
				// Bude sa cakat na timeot.
				CancelWaitableTimer(WT);
				wprintf(L"TIMER WAS RESET !\n");
			}
		}
		else if (Ret==WAIT_TIMEOUT)
		{
			wprintf(L"TIMEOUT !\n");
			break;
		}
		else
			wprintf(L"UNEXPECTED VALUE !\n");
	}
}
//-----------------------------------------------------------------------------
void TestRelativeWaitableTimerNoCycle(void)
{
	HANDLE			WT=CreateWaitableTimer(NULL,FALSE,NULL);
	LARGE_INTEGER	LI;

	// !!! Zaporna hodnota znamena RELATIVNY CAS.
	LI.QuadPart=-3*10*1000*1000;

	// Periodicita je ==0.
	SetWaitableTimer(WT,&LI,0,NULL,NULL,FALSE);

	wprintf(L"WAIT STARTED !\n");

	while(true)
	{
		DWORD			Ret=WaitForSingleObject(WT,10*1000);

		if (Ret==WAIT_OBJECT_0)
			wprintf(L"!!! WAIT TIMER OCCURED !\n");
		else if (Ret==WAIT_TIMEOUT)
		{
			wprintf(L"TIMEOUT !\n");
			break;
		}
		else
			wprintf(L"UNEXPECTED VALUE !\n");
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	//TestAbsoluteWaitableTimerNoCycle();
	//TestAbsoluteWaitableTimerWithCycle();
	TestRelativeWaitableTimerNoCycle();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------