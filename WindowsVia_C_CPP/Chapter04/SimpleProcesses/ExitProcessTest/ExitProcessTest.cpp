#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "ExitTest.h"
#include <process.h>
//------------------------------------------------------------------------------
// Globalny objekt na test, ci sa DESTRUKTOR ZAVOLA.
// !!!!! Napodiv ZAVOLA SA DESTRUKOR aj pri ExitProcess() ci ExitThread().
CExitTest				Global(L"GLOBAL");
//------------------------------------------------------------------------------
unsigned int WINAPI ThreadFunction(void*)
{
	wprintf_s(L"WORKER THREAD STATED !\n");

	Sleep(10*1000);

	wprintf_s(L"WORKER THREAD FINISHED !\n");

	return(0);
}
//------------------------------------------------------------------------------
void Test1(void)
{
	// !!!!! NEZAVOLA SA DESTRUKTOR.
	CExitTest			Local(L"LOCAL");

	wprintf_s(L"BEFORE ExitProcess() !\n");

	ExitProcess(0);

	wprintf_s(L"AFTER ExitProcess() !\n");
}
//------------------------------------------------------------------------------
void Test2(void)
{
	// !!!!! NEZAVOLA SA DESTRUKTOR.
	CExitTest			Local(L"LOCAL");

	wprintf_s(L"BEFORE ExitThread() !\n");

	ExitThread(0);

	wprintf_s(L"AFTER ExitThread() !\n");
}
//------------------------------------------------------------------------------
void Test3(void)
{
	// !!!!! NEZAVOLA SA DESTRUKTOR.
	CExitTest			Local(L"LOCAL");

	_beginthreadex(NULL,0,ThreadFunction,NULL,0,NULL);

	Sleep(1000);

	wprintf_s(L"BEFORE ExitProcess() !\n");

	// Zabiju sa VSETKY THREADS.
	ExitProcess(0);

	wprintf_s(L"AFTER ExitProcess() !\n");
}
//------------------------------------------------------------------------------
void Test4(void)
{
	// !!!!! NEZAVOLA SA DESTRUKTOR.
	CExitTest			Local(L"LOCAL");

	_beginthreadex(NULL,0,ThreadFunction,NULL,0,NULL);

	Sleep(1000);

	wprintf_s(L"BEFORE ExitThread() !\n");

	// PRIMARY THREAD sa sice UKOCNI, ale proces BEZI DALEJ, kedze bezi INY THREAD.
	ExitThread(0);

	wprintf_s(L"AFTER ExitThread() !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	//Test2();
	Test3();
	//Test4();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------