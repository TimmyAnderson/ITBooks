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

	Sleep(1*1000);

	wprintf(L"Time: %d, TID: %d - END [%s] !\n",GetTickCount(),TID,Message);
}
//------------------------------------------------------------------------------
void CALLBACK MyCleanupCallback(PVOID ObjectContext, PVOID CleanupContext)
{
	wchar_t			*Message=(wchar_t*) CleanupContext;
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d - BEGIN [%s] !\n",GetTickCount(),TID,Message);

	Sleep(5*1000);

	wprintf(L"Time: %d, TID: %d - END [%s] !\n",GetTickCount(),TID,Message);
}
//------------------------------------------------------------------------------
void Test(void)
{
	const int				COUNT=20;
	// Toto pole NEMUSIM ODSTRANOVAT, lebo CLENUP GROUP to spravi AUTOMATICKY.
	PTP_WORK				WI[COUNT];
	wchar_t					Buffers[COUNT][100];
	TP_CALLBACK_ENVIRON		TPE;
	PTP_POOL				CustomPool;
	PTP_CLEANUP_GROUP		CleanupGroup;

	// Vytvorim TPE.
	InitializeThreadpoolEnvironment(&TPE);

	// Vytvorim CUSTOM TP.
	CustomPool=CreateThreadpool(NULL);

	// Vytvorim CLEANING GROUP.
	CleanupGroup=CreateThreadpoolCleanupGroup();

	// Asociujem PTP_CALLBACK_ENVIRON s TP.
	SetThreadpoolCallbackPool(&TPE,CustomPool);

	// Asociujem CALLBACK s CleanupGroup.
	SetThreadpoolCallbackCleanupGroup(&TPE,CleanupGroup,&MyCleanupCallback);

	for (int i=0;i<COUNT;i++)
	{
		wsprintf(Buffers[i],L"HELLO WORLD %d",i+1);

		WI[i]=CreateThreadpoolWork(&MyWorkCallback,Buffers[i],&TPE);

		if (WI[i]==NULL)
		{
			wprintf(L"ERROR !!!\n");
			return;
		}
	}

	wprintf(L"WORK WILL BE STARTED !\n");

	for (int i=0;i<COUNT;i++)
		SubmitThreadpoolWork(WI[i]);

	wprintf(L"WORK WAS STARTED !\n");

	wprintf(L"BEFORE CloseThreadpoolCleanupGroupMembers() !\n");

	// CAKAM NA SKONCENIE TP GROUP a UVOLNENIE VSETKYCH JEJ RESOURCES.
	// !!!!! Pole WI[] NEMUSIM ODSTRANOVAT, lebo CLENUP GROUP to spravi AUTOMATICKY.
	CloseThreadpoolCleanupGroupMembers(CleanupGroup,FALSE,L"BYE BYE");

	wprintf(L"BEFORE CloseThreadpoolCleanupGroup() !\n");

	// Zlikvidujem CLEANUP GROUP.
	CloseThreadpoolCleanupGroup(CleanupGroup);

	wprintf(L"BEFORE CloseThreadpool() !\n");

	// Zlikvidujem CUSTOM TP.
	CloseThreadpool(CustomPool);

	wprintf(L"BEFORE DestoryThreadpoolEnvironment() !\n");

	// Zlikvidujem TPE.
	DestroyThreadpoolEnvironment(&TPE);

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