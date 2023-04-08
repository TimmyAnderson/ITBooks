#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
void Test()
{
	SECURITY_ATTRIBUTES	SA;

	ZeroMemory(&SA,sizeof(SA));

	// Musim nastavit bInheritHandle na TRUE.
	SA.bInheritHandle=TRUE;

	HANDLE				Handle1=CreateEvent(&SA,TRUE,FALSE,NULL);
	HANDLE				Handle2=CreateEvent(NULL,TRUE,FALSE,NULL);

	// Iny sposob nastavenia bInheritHandle na TRUE.
	SetHandleInformation(Handle2,HANDLE_FLAG_INHERIT,HANDLE_FLAG_INHERIT);

	wprintf(L"Handles [%d] and [%d] CREATED !\n",Handle1,Handle2);

	wchar_t				CommandLine[300];

	swprintf_s(CommandLine,_countof(CommandLine),L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter03\\KernelObjectInheritance\\Child\\Debug\\Child.exe %d %d",Handle1,Handle2);

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

		wprintf(L"PRESS ANY KEY to execute EVENTS !\n");
		_getch();

		SetEvent(Handle1);
		SetEvent(Handle2);

		wprintf(L"BOTH EVENTS were FIRED !\n");
	}

	CloseHandle(Handle1);
	Handle1=NULL;

	CloseHandle(Handle2);
	Handle2=NULL;
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