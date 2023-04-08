#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
//------------------------------------------------------------------------------
unsigned int __stdcall MyThread(void* Param)
{
	wchar_t*		Data=(wchar_t*) Param;

	wprintf_s(L"Thread [%d] - Thread with data [%s] STARTED !\n",GetCurrentThreadId(),Data);

	Sleep(3000);

	wprintf_s(L"Thread [%d] - Thread with data [%s] is going to be FINISHED !\n",GetCurrentThreadId(),Data);

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	wchar_t*		Data=L"Timmy Anderson";
	HANDLE			HThread;

	wprintf_s(L"Thread [%d] - Thread with data [%s] is going to be STARTED !\n",GetCurrentThreadId(),Data);
	
	HThread=(HANDLE)::_beginthreadex(NULL,0,MyThread,Data,0,NULL);

	WaitForSingleObject(HThread,INFINITE);

	wprintf_s(L"Thread [%d] - Thread with data [%s] FINISHED !\n",GetCurrentThreadId(),Data);

	CloseHandle(HThread);
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