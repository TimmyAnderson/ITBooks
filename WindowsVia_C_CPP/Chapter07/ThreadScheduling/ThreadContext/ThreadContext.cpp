#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
// !!!!! Teoreticky program moze PADNUT ak by ho kompilator skompilovat tak, zeby pouziva register 'Ecx'.
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	wprintf_s(L"WORKER THREAD - thread WAS started and will SUSPENDED ITSELF !\n");

	SuspendThread(GetCurrentThread());
	
	wprintf_s(L"WORKER THREAD - thread was RESUMED !\n");

	CONTEXT				Context;

	Context.ContextFlags=CONTEXT_INTEGER;

	GetThreadContext(GetCurrentThread(), &Context);

	wprintf_s(L"WORKER THREAD - WORKER thread register value - Ecx: [%d] !\n",Context.Ecx);

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle;

	Handle=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	// Pockam kym thread zastavi sam seba.
	Sleep(1000);

	CONTEXT				Context;

	// Nacitam hodnotu registra.
	Context.ContextFlags=CONTEXT_INTEGER;
	GetThreadContext(Handle, &Context);
	wprintf_s(L"MAIN THREAD - WORKER thread register value - Ecx: [%d] !\n",Context.Ecx);

	// Nastavim hodnotu registra.
	Context.Ecx=100;

	// Zapisem hodnotu registra.
	Context.ContextFlags=CONTEXT_INTEGER;
	SetThreadContext(Handle, &Context);

	// Nacitam hodnotu registra.
	Context.ContextFlags=CONTEXT_INTEGER;
	GetThreadContext(Handle, &Context);
	wprintf_s(L"MAIN THREAD - WORKER thread register value - Ecx: [%d] !\n",Context.Ecx);

	// Spustim znova thread.
	ResumeThread(Handle);

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