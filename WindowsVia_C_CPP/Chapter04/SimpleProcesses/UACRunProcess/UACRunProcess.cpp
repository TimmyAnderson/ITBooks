#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <shlobj.h>
//------------------------------------------------------------------------------
void Test(void)
{
	wchar_t				CommandLine[]=L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter04\\SimpleProcesses\\ChildProcess\\Debug\\ChildProcess.exe";
	SHELLEXECUTEINFO	SEI={sizeof(SHELLEXECUTEINFO)};

	// Musim nastavit za 'lpVerb' hodnotu 'runas'.
	SEI.lpVerb=TEXT("runas");

	SEI.lpFile=CommandLine;
	SEI.lpParameters=L"";
	SEI.nShow=SW_SHOWNORMAL;

	ShellExecuteEx(&SEI);

	wprintf(L"CHILD PROCESS CREATED !\n");
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