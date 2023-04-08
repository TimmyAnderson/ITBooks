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

	wprintf(L"Waiting for handles [%s] and [%s] !\n",Name1,Name2);

	HANDLE				Events[]={Handle1,Handle2};

	if (WaitForMultipleObjects(_countof(Events),Events,TRUE,INFINITE)!=WAIT_FAILED)
		wprintf(L"Waiting FINISHED !\n");
	else
		wprintf(L"Waiting FAILED !!!\n");

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