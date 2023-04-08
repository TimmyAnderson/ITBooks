#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
void Test()
{
	HANDLE				Handle=CreateEvent(NULL,TRUE,FALSE,NULL);
	DWORD				ParentProcessID=GetCurrentProcessId();

	wprintf(L"Handles [%d] in process [%d] CREATED !\n",Handle,ParentProcessID);

	wchar_t				CommandLine[300];

	swprintf_s(CommandLine,_countof(CommandLine),L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter03\\DuplicateKernelObject\\Child\\Debug\\Child.exe %d %d",Handle,ParentProcessID);

	PROCESS_INFORMATION	PI;
	STARTUPINFO			SI;

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
		CloseHandle(PI.hProcess);
		CloseHandle(PI.hThread);

		wprintf(L"CHILD PROCESS CREATED !\n");

		wprintf(L"PRESS ANY KEY to execute EVENT !\n");
		_getch();

		SetEvent(Handle);

		wprintf(L"EVENT was FIRED !\n");
	}

	CloseHandle(Handle);
	Handle=NULL;
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