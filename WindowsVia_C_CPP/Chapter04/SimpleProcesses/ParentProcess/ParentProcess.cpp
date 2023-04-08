#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
void Test()
{
	wprintf_s(L"PARENT PROCESS !\n");

	wchar_t				CommandLine[]=L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter04\\SimpleProcesses\\ChildProcess\\Debug\\ChildProcess.exe";

	PROCESS_INFORMATION	PI;
	STARTUPINFO			SI;

	// Musim vynulovat PROCESS_INFORMATION.
	ZeroMemory(&SI,sizeof(SI));
	SI.cb=sizeof(SI);
	ZeroMemory(&PI,sizeof(PI));

	// Musim nastavit bInheritHandles na TRUE.
	if (CreateProcess(NULL,CommandLine,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&SI,&PI)==0)
	{
		wprintf(L"CHILD PROCESS FAILED to CREATE !\n");
	}
	else
	{
		// Ak nepotrebujem tieto HANDLES MUSIM ICH UZAVRIET.
		CloseHandle(PI.hProcess);
		CloseHandle(PI.hThread);

		wprintf(L"CHILD PROCESS CREATED !\n");
		wprintf(L"CHILD PROCESS ID: [%d] !\n",PI.dwProcessId);
		wprintf(L"CHILD THREAD ID: [%d] !\n",PI.dwThreadId);
	}
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