#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
void APIENTRY APCForWaitableTimer(void* ArgToCompletionRoutine, DWORD TimerLowValue, DWORD TimerHighValue)
{
	// !!!!! Vykona sa v HLAVNOM THREADE APLIKACIE.
	WriteDebugText(L"I'm in APC !!!\n");

	Sleep(1000);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	HANDLE				Handle;

	// MANUAL RESET TIMER.
	Handle=CreateWaitableTimer(NULL,TRUE,NULL);

	LARGE_INTEGER		LI;

	// Nastavim relativny cas na 5 sekund.
	LI.QuadPart=-50*1000*1000;

	if (SetWaitableTimer(Handle,&LI,0,NULL,NULL,FALSE)==TRUE)
	{
		WriteTextWithTime(L"Waiting...\n");

		for (int i=0;i<10;i++)
		{
			if (WaitForSingleObject(Handle,INFINITE)==WAIT_OBJECT_0)
				WriteTextWithTime(L"Thread KO WAS SIGNALIZED !\n");
			else
				WriteTextWithTime(L"ERROR !\n");
		}
	}
	else
		wprintf_s(L"Error !\n");

	CloseHandle(Handle);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	HANDLE				Handle;

	// AUTO RESET TIMER.
	Handle=CreateWaitableTimer(NULL,FALSE,NULL);

	LARGE_INTEGER		LI;

	// Nastavim relativny cas na 5 sekund.
	LI.QuadPart=-50*1000*1000;

	// Nastavim periodu na 1 sekundu.
	if (SetWaitableTimer(Handle,&LI,1000,NULL,NULL,FALSE)==TRUE)
	{
		WriteTextWithTime(L"Waiting...\n");

		for (int i=0;i<10;i++)
		{
			if (WaitForSingleObject(Handle,INFINITE)==WAIT_OBJECT_0)
				WriteTextWithTime(L"Thread KO WAS SIGNALIZED !\n");
			else
				WriteTextWithTime(L"ERROR !\n");
		}
	}
	else
		wprintf_s(L"Error !\n");

	CloseHandle(Handle);
}
//------------------------------------------------------------------------------
void Test3(void)
{
	HANDLE				Handle;

	// MANUAL RESET TIMER.
	Handle=CreateWaitableTimer(NULL,TRUE,NULL);

	LARGE_INTEGER		LI;

	// Nastavim relativny cas na 5 sekund.
	LI.QuadPart=-50*1000*1000;

	if (SetWaitableTimer(Handle,&LI,0,APCForWaitableTimer,NULL,FALSE)==TRUE)
	{
		WriteDebugText(L"I'm going to ALERTABLE WAIT !\n");

		// Skocim do ALERTABLE WAIT.
		SleepEx(INFINITE,TRUE);

		WriteDebugText(L"Waiting FINISHED !\n");
	}
	else
		wprintf_s(L"Error !\n");

	CloseHandle(Handle);
}
//------------------------------------------------------------------------------
void Test4(void)
{
	HANDLE				Handle;

	// MANUAL RESET TIMER.
	Handle=CreateWaitableTimer(NULL,TRUE,NULL);

	LARGE_INTEGER		LI;

	// Nastavim relativny cas na 5 sekund.
	LI.QuadPart=-50*1000*1000;

	if (SetWaitableTimer(Handle,&LI,0,APCForWaitableTimer,NULL,FALSE)==TRUE)
	{
		WriteDebugText(L"I'm going to ALERTABLE WAIT - WAITING for Waitable Timer KO !\n");

		// Skocim do ALERTABLE WAIT.
		// !!!!! Kedze cakam na Waitable Timer KO tak sa APC NEZAVOLA.
		WaitForSingleObjectEx(Handle,INFINITE,TRUE);

		WriteDebugText(L"Waiting FINISHED !\n");
	}
	else
		wprintf_s(L"Error !\n");

	CloseHandle(Handle);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	//Test2();
	//Test3();
	Test4();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------