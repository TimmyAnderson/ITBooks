#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
#include "../CreateRemoteThreadDLL/CreateRemoteThreadDLL.h"
//------------------------------------------------------------------------------
void Test(void)
{
	wprintf_s(L"PID: [%d] - SLAVE !\n",GetCurrentProcessId());

	DLLLoadTest();
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