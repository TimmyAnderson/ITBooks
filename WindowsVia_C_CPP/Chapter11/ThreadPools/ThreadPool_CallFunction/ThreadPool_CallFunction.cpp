#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
//------------------------------------------------------------------------------
void WINAPI SimpleWorkFunction(PTP_CALLBACK_INSTANCE CI,void* Param)
{
	wchar_t*			Data=(wchar_t*) Param;
	wchar_t				Buffer[1024];

	StringCchPrintf(Buffer,_countof(Buffer),L"Work item [%s] STARTED !\n",Data);
	WriteDebugText(Buffer);

	Sleep(2000);

	StringCchPrintf(Buffer,_countof(Buffer),L"Work item [%s] FINISHED !\n",Data);
	WriteDebugText(Buffer);
}
//------------------------------------------------------------------------------
void WINAPI WorkFunction(PTP_CALLBACK_INSTANCE CI,void* Param, PTP_WORK Work)
{
	wchar_t*			Data=(wchar_t*) Param;
	wchar_t				Buffer[1024];

	StringCchPrintf(Buffer,_countof(Buffer),L"Work item [%s] STARTED !\n",Data);
	WriteDebugText(Buffer);

	Sleep(2000);

	StringCchPrintf(Buffer,_countof(Buffer),L"Work item [%s] FINISHED !\n",Data);
	WriteDebugText(Buffer);
}
//------------------------------------------------------------------------------
void Test1(void)
{
	PTP_WORK		Work=CreateThreadpoolWork(WorkFunction,L"Timmy",NULL);

	wprintf_s(L"Work item CREATED !\n");

	SubmitThreadpoolWork(Work);

	wprintf_s(L"Work item SUBMITTED !\n");

	WaitForThreadpoolWorkCallbacks(Work,FALSE);

	wprintf_s(L"Work item FINISHED !\n");

	CloseThreadpoolWork(Work);

	wprintf_s(L"Work item DELETED !\n");
}
//------------------------------------------------------------------------------
void Test2(void)
{
	const int		WORK_ITEMS_COUNT=30;
	PTP_WORK		WorkItems[WORK_ITEMS_COUNT];
	PVOID			Buffers[WORK_ITEMS_COUNT];

	for (int i=0;i<WORK_ITEMS_COUNT;i++)
	{
		const int	BUFFER_SIZE=1024;
	
		Buffers[i]=malloc(BUFFER_SIZE*sizeof(wchar_t));

		wchar_t*	Buffer=(wchar_t*) Buffers[i];

		StringCchPrintf(Buffer,BUFFER_SIZE,L"ITEM [%d]",i+1);
		WorkItems[i]=CreateThreadpoolWork(WorkFunction,Buffer,NULL);
	}

	wprintf_s(L"ALL Work items CREATED !\n");

	for (int i=0;i<WORK_ITEMS_COUNT;i++)
		SubmitThreadpoolWork(WorkItems[i]);

	wprintf_s(L"ALL Work items SUBMITTED !\n");

	Sleep(100);
	
	wprintf_s(L"ALL Work items is BEING CANCELLED !\n");

	for (int i=WORK_ITEMS_COUNT-1;i>=0;i--)
		WaitForThreadpoolWorkCallbacks(WorkItems[i],TRUE);

	wprintf_s(L"ALL Work items FINISHED !\n");

	for (int i=0;i<WORK_ITEMS_COUNT;i++)
	{
		CloseThreadpoolWork(WorkItems[i]);

		free(Buffers[i]);
	}

	wprintf_s(L"ALL Work items DELETED !\n");
}
//------------------------------------------------------------------------------
void Test3(void)
{
	TrySubmitThreadpoolCallback(SimpleWorkFunction,L"Timmy Anderson",NULL);

	wprintf_s(L"Work item SUBMITTED !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	//Test2();
	Test3();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------