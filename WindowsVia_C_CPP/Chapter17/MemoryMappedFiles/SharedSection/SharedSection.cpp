#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
// !!!!! Nato aby program mohol demonstrovat svoju cinnost, MUSIA BYT SPUSTENE 2 INSTANCIE PROGRAMU.
//------------------------------------------------------------------------------
// Vytvorim NOVU SECTION.
#pragma data_seg("Shared")
volatile LONG		SharedValue=0;
#pragma data_seg()
//------------------------------------------------------------------------------
// Nastavim LINKER, aby nova section bola SHARED medzi VIACERYMI INSTANCIAMI TEJ ISTEJ APLIKACIE.
#pragma comment(linker,"/Section:Shared,RWS")
//------------------------------------------------------------------------------
HANDLE				SharedEvent;
HANDLE				ExitEvent;
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	HANDLE			Handles[]={ExitEvent,SharedEvent};

	while(true)
	{
		DWORD		Ret=WaitForMultipleObjects(_countof(Handles),Handles,FALSE,INFINITE);

		if (Ret==WAIT_OBJECT_0)
			break;

		ResetEvent(SharedEvent);

		if (Ret==(WAIT_OBJECT_0+1))
			wprintf_s(L"SHARED value: [%d] !\n",SharedValue);
	}

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle;

	SharedEvent=CreateEvent(NULL,TRUE,FALSE,L"SharedEvent");
	ExitEvent=CreateEvent(NULL,FALSE,FALSE,NULL);
	
	Handle=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	while(true)
	{
		wprintf_s(L"Press key to INCREMENT VALUE, or 'q' to QUIT !\n");

		int				Value=_getch();

		if (Value=='q')
			break;

		InterlockedIncrement(&SharedValue);
		SetEvent(SharedEvent);
	}

	SetEvent(ExitEvent);

	WaitForSingleObject(Handle,INFINITE);

	CloseHandle(SharedEvent);
	CloseHandle(ExitEvent);
	CloseHandle(Handle);
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