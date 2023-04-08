#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
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
// Vola sa pri KAZDY WORK ITEM, ktory je CANCELLED danou GROUP.
void NTAPI WorkItemCancelled(PVOID ObjectContext, PVOID CleanupContext)
{
	wchar_t*			Data=(wchar_t*) ObjectContext;
	wchar_t				Buffer[1024];

	StringCchPrintf(Buffer,_countof(Buffer),L"Work item [%s] CANCELLED !\n",Data);
	WriteDebugText(Buffer);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	const int			WORK_ITEMS_COUNT=10;
	PTP_WORK			WorkItems[WORK_ITEMS_COUNT];
	PVOID				Buffers[WORK_ITEMS_COUNT];
	PTP_POOL			Pool;
	TP_CALLBACK_ENVIRON	Environment;

	// Vytvorim TP.
	Pool=CreateThreadpool(NULL);

	// Inicializujem pocet threads.
	SetThreadpoolThreadMinimum(Pool,1);
	SetThreadpoolThreadMaximum(Pool,2);

	// Inicializujem TP ENVIRONMENT.
	InitializeThreadpoolEnvironment(&Environment);

	// Asociujem TP s TP ENVIRONMENT.
	SetThreadpoolCallbackPool(&Environment,Pool);

	for (int i=0;i<WORK_ITEMS_COUNT;i++)
	{
		const int		BUFFER_SIZE=1024;
	
		Buffers[i]=malloc(BUFFER_SIZE*sizeof(wchar_t));

		wchar_t*		Buffer=(wchar_t*) Buffers[i];

		StringCchPrintf(Buffer,BUFFER_SIZE,L"ITEM [%d]",i+1);

		// Pouzijem TP ENVIRONMENT.
		WorkItems[i]=CreateThreadpoolWork(WorkFunction,Buffer,&Environment);
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

	// Zlikvidujem TP ENVIRONMENT.
	DestroyThreadpoolEnvironment(&Environment);

	// Uzavriem TP.
	CloseThreadpool(Pool);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	const int			WORK_ITEMS_COUNT=10;
	PTP_WORK			WorkItems[WORK_ITEMS_COUNT];
	PVOID				Buffers[WORK_ITEMS_COUNT];
	PTP_POOL			Pool;
	TP_CALLBACK_ENVIRON	Environment;
	PTP_CLEANUP_GROUP	Group;

	// Vytvorim TP.
	Pool=CreateThreadpool(NULL);

	// Inicializujem pocet threads.
	SetThreadpoolThreadMinimum(Pool,1);
	SetThreadpoolThreadMaximum(Pool,2);

	// Inicializujem TP ENVIRONMENT.
	InitializeThreadpoolEnvironment(&Environment);

	// Asociujem TP s TP ENVIRONMENT.
	SetThreadpoolCallbackPool(&Environment,Pool);

	// Vytvorim CLEANUP GROUP.
	Group=CreateThreadpoolCleanupGroup();

	// Asociujem CLEANUP GROUP s TP a priradim i CANCEL CALLBACK.
	SetThreadpoolCallbackCleanupGroup(&Environment,Group,WorkItemCancelled);

	for (int i=0;i<WORK_ITEMS_COUNT;i++)
	{
		const int		BUFFER_SIZE=1024;
	
		Buffers[i]=malloc(BUFFER_SIZE*sizeof(wchar_t));

		wchar_t*		Buffer=(wchar_t*) Buffers[i];

		StringCchPrintf(Buffer,BUFFER_SIZE,L"ITEM [%d]",i+1);

		// Pouzijem TP ENVIRONMENT.
		WorkItems[i]=CreateThreadpoolWork(WorkFunction,Buffer,&Environment);
	}

	wprintf_s(L"ALL Work items CREATED !\n");

	for (int i=0;i<WORK_ITEMS_COUNT;i++)
		SubmitThreadpoolWork(WorkItems[i]);

	wprintf_s(L"ALL Work items SUBMITTED !\n");

	Sleep(100);
	
	wprintf_s(L"GROUP is GOING to be CANCELLED !\n");

	CloseThreadpoolCleanupGroupMembers(Group,TRUE,NULL);

	wprintf_s(L"ALL Work items FINISHED !\n");

	// !!!!! Odstranim CLEANUP GROUP a VSETKY WORK ITEMS.
	CloseThreadpoolCleanupGroup(Group);
	
	for (int i=0;i<WORK_ITEMS_COUNT;i++)
	{
		// !!!!! CloseThreadpoolWork() sa NESMIE VOLAT, ked volam CloseThreadpoolCleanupGroup().
		//CloseThreadpoolWork(WorkItems[i]);
		free(Buffers[i]);
	}

	wprintf_s(L"ALL Work items DELETED !\n");

	// Zlikvidujem TP ENVIRONMENT.
	DestroyThreadpoolEnvironment(&Environment);

	// Uzavriem TP.
	CloseThreadpool(Pool);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	Test2();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------