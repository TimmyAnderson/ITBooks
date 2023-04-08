#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
//------------------------------------------------------------------------------
HANDLE					Event;
//------------------------------------------------------------------------------
void WINAPI WorkFunction(PTP_CALLBACK_INSTANCE CI, void* Param, PTP_WORK Work)
{
	wchar_t*			Data=(wchar_t*) Param;
	wchar_t				Buffer[1024];

	StringCchPrintf(Buffer,_countof(Buffer),L"Work item [%s] STARTED !\n",Data);
	WriteDebugText(Buffer);

	SetEventWhenCallbackReturns(CI,Event);

	Sleep(2000);

	StringCchPrintf(Buffer,_countof(Buffer),L"Work item [%s] FINISHED !\n",Data);
	WriteDebugText(Buffer);
}
//------------------------------------------------------------------------------
void Test(void)
{
	PTP_WORK			WorkItem;
	const int			BUFFER_SIZE=1024;

	Event=CreateEvent(NULL,FALSE,FALSE,NULL);

	wchar_t*			Buffer=(wchar_t*) malloc(BUFFER_SIZE*sizeof(wchar_t));

	StringCchPrintf(Buffer,BUFFER_SIZE,L"ITEM");
	WorkItem=CreateThreadpoolWork(WorkFunction,Buffer,NULL);

	wprintf_s(L"ALL Work items CREATED !\n");

	SubmitThreadpoolWork(WorkItem);

	wprintf_s(L"ALL Work items SUBMITTED !\n");

	WaitForSingleObject(Event,INFINITE);
	
	wprintf_s(L"EVENT WAS SIGNALIZED !\n");

	WaitForThreadpoolWorkCallbacks(WorkItem,TRUE);

	wprintf_s(L"Work item FINISHED !\n");

	CloseThreadpoolWork(WorkItem);

	free(Buffer);

	wprintf_s(L"Work item DELETED !\n");

	CloseHandle(Event);
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