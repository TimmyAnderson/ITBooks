#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
// !!! Premenna MUSI BYT VOLATAILE.
volatile bool		ThreadFinished=false;
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	// Znizim sam sebe prioritu, aby bola NIZSIA ako MAIN THREAD.
	SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_BELOW_NORMAL);

	for (int i=0;i<1000;i++)
		wprintf_s(L"Working: [%d] !\n",i+1);

	// Nastavim priznak, ze thread skoncil svoju pracu.
	ThreadFinished=true;

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle;

	Handle=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	// Simulujem CAKANIE na WORKER THREAD - pricom NEUSTALE ZATAZUJEM CPU.
	while(ThreadFinished==false)
		;

	wprintf_s(L"Main thread FINISHED !\n");

	WaitForSingleObject(Handle,INFINITE);

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