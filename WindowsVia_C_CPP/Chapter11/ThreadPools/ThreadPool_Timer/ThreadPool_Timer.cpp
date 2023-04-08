#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
//------------------------------------------------------------------------------
void WINAPI TimerFunction(PTP_CALLBACK_INSTANCE CI,void* Param, PTP_TIMER Work)
{
	wchar_t*			Data=(wchar_t*) Param;
	wchar_t				Buffer[1024];

	StringCchPrintf(Buffer,_countof(Buffer),L"Timer [%s] was EXECUTED !\n",Data);
	WriteDebugText(Buffer);
}
//------------------------------------------------------------------------------
void Test1(void)
{
	PTP_TIMER		Timer=CreateThreadpoolTimer(TimerFunction,L"Timmy",NULL);

	WriteDebugText(L"Timer CREATED !\n");

    FILETIME		FT;
    ULARGE_INTEGER	DueTime;

    DueTime.QuadPart=(LONGLONG) -(3 * 10 * 1000 * 1000);
    FT.dwHighDateTime=DueTime.HighPart;
    FT.dwLowDateTime=DueTime.LowPart;

	SetThreadpoolTimer(Timer,&FT,0,0);

	WriteDebugText(L"Timer SET !\n");

	_getch();

	SetThreadpoolTimer(Timer,NULL,0,0);

	WriteDebugText(L"Timer SET to NULL !\n");

	WaitForThreadpoolTimerCallbacks(Timer,FALSE);

	WriteDebugText(L"Timer FINISHED !\n");

	CloseThreadpoolTimer(Timer);

	WriteDebugText(L"Timer DELETED !\n");
}
//------------------------------------------------------------------------------
void Test2(void)
{
	PTP_TIMER		Timer=CreateThreadpoolTimer(TimerFunction,L"Timmy",NULL);

	WriteDebugText(L"Timer CREATED !\n");

    FILETIME		FT;
    ULARGE_INTEGER	DueTime;

    DueTime.QuadPart=(LONGLONG) -(3 * 10 * 1000 * 1000);
    FT.dwHighDateTime=DueTime.HighPart;
    FT.dwLowDateTime=DueTime.LowPart;

	SetThreadpoolTimer(Timer,&FT,1000,0);

	WriteDebugText(L"Timer SET !\n");

	_getch();

	SetThreadpoolTimer(Timer,NULL,0,0);

	WriteDebugText(L"Timer SET to NULL !\n");

	WaitForThreadpoolTimerCallbacks(Timer,FALSE);

	WriteDebugText(L"Timer FINISHED !\n");

	CloseThreadpoolTimer(Timer);

	WriteDebugText(L"Timer DELETED !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	Test2();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------