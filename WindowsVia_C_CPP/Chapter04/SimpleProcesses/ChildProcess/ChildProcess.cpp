#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
void Test()
{
	wprintf_s(L"CHILD PROCESS !\n");
	wprintf(L"PROCESS ID: [%d] !\n",GetCurrentProcessId());
	wprintf(L"THREAD ID: [%d] !\n",GetCurrentThreadId());
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------