#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
void Test()
{
	wchar_t*			Name1=L"Timmy";
	wchar_t*			Name2=L"Anderson";
	HANDLE				Handle1=CreateEvent(NULL,TRUE,FALSE,Name1);
	HANDLE				Handle2=CreateEvent(NULL,TRUE,FALSE,Name2);

	wprintf(L"Events [%s] and [%s] CREATED !\n",Name1,Name2);

	wprintf(L"PRESS ANY KEY to execute EVENTS !\n");
	_getch();

	SetEvent(Handle1);
	SetEvent(Handle2);

	wprintf(L"BOTH EVENTS were FIRED !\n");

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