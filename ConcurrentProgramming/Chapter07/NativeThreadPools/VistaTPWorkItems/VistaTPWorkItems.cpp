//------------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
void CALLBACK MyWorkCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WORK Work)
{
	wchar_t			*Message=(wchar_t*) Context;
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d - BEGIN [%s] !\n",GetTickCount(),TID,Message);

	Sleep(3*1000);

	wprintf(L"Time: %d, TID: %d - END [%s] !\n",GetTickCount(),TID,Message);
}
//------------------------------------------------------------------------------
void Test(void)
{
	PTP_WORK		WI;

	// Vytvorim WI.
	WI=CreateThreadpoolWork(&MyWorkCallback,L"Hello World",NULL);

	if (WI==NULL)
	{
		wprintf(L"ERROR !!!\n");
		return;
	}

	wprintf(L"WORK WILL BY STARTED !\n");

	// Spustim 10 instancii WI.
	for (int i=0;i<10;i++)
		SubmitThreadpoolWork(WI);

	// Cakam na skoncenie VSETKYCH INSTANCII WI.
	WaitForThreadpoolWorkCallbacks(WI,FALSE);

	// Uzavriem PTP_WORK.
	CloseThreadpoolWork(WI);

	wprintf(L"WORK WAS FINISHED !\n");
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