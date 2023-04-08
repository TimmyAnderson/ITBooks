#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
//------------------------------------------------------------------------------
HANDLE				Event;
PTP_WAIT			Wait;
//------------------------------------------------------------------------------
void WINAPI WaitFunction(PTP_CALLBACK_INSTANCE CI, void* Param, PTP_WAIT Work, TP_WAIT_RESULT Result)
{
	wchar_t*		Data=(wchar_t*) Param;
	wchar_t			Buffer[1024];

    FILETIME		FT;
    ULARGE_INTEGER	DueTime;

    DueTime.QuadPart=(LONGLONG) -(3 * 10 * 1000 * 1000);
    FT.dwHighDateTime=DueTime.HighPart;
    FT.dwLowDateTime=DueTime.LowPart;

	if (Result==WAIT_ABANDONED_0)
		StringCchPrintf(Buffer,_countof(Buffer),L"Wait [%s] was RELEASED - WAIT_ABANDONED_0 !\n",Data);
	else if (Result==WAIT_OBJECT_0)
		StringCchPrintf(Buffer,_countof(Buffer),L"Wait [%s] was RELEASED - WAIT_OBJECT_0 !\n",Data);
	else
	{
		StringCchPrintf(Buffer,_countof(Buffer),L"Wait [%s] was RELEASED - WAIT_TIMEOUT - WAIT will be RESET !\n",Data);

		SetThreadpoolWait(Wait,Event,&FT);
	}

	WriteDebugText(Buffer);
}
//------------------------------------------------------------------------------
void Test(void)
{
	Wait=CreateThreadpoolWait(WaitFunction,L"Timmy",NULL);

	Event=CreateEvent(NULL,FALSE,FALSE,NULL);

	WriteDebugText(L"Wait CREATED !\n");

    FILETIME		FT;
    ULARGE_INTEGER	DueTime;

    DueTime.QuadPart=(LONGLONG) -(3 * 10 * 1000 * 1000);
    FT.dwHighDateTime=DueTime.HighPart;
    FT.dwLowDateTime=DueTime.LowPart;

	SetThreadpoolWait(Wait,Event,&FT);

	WriteDebugText(L"Wait SET !\n");

	_getch();

	WriteDebugText(L"HANDLE was SIGNALIZED !\n");

	SetEvent(Event);

	_getch();

	WaitForThreadpoolWaitCallbacks(Wait,FALSE);

	WriteDebugText(L"Wait FINISHED !\n");

	CloseThreadpoolWait(Wait);

	WriteDebugText(L"Wait DELETED !\n");
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