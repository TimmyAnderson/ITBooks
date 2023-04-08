//------------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
DWORD WINAPI MyWorkCallback(LPVOID Context)
{
	wchar_t			*Message=(wchar_t*) Context;
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d - BEGIN %d [%s] !\n",GetTickCount(),TID,Message,Message);

	Sleep(3*1000);

	wprintf(L"Time: %d, TID: %d - END [%s] !\n",GetTickCount(),TID,Message);

	return(0);
}
//------------------------------------------------------------------------------
void Test(void)
{
	const int				COUNT=20;
	wchar_t					Buffers[COUNT][35];

	for(int i=0;i<COUNT;i++)
	{
		wsprintf(Buffers[i],L"HELLO WORLD %d",i+1);

		// !!! Je treba nastavit WT_EXECUTELONGFUNCTION, aby SKUTOCNE vytvoril viac threads. Inak si bude mysliet, ze staci iba tolko Threads kolko CPU - teda 1, pretoze predpoklada, ze CALLBACK skonci velmi rychlo.
		QueueUserWorkItem(MyWorkCallback,Buffers[i],WT_EXECUTELONGFUNCTION);
	}

	wprintf(L"WORK FINISHED !\n");
	_getch();
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