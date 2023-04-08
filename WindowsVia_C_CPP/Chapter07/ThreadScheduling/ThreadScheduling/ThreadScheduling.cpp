#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <set>
//------------------------------------------------------------------------------
using namespace std;
typedef set<DWORD>	SET;
typedef set<DWORD>*	PSET;
//------------------------------------------------------------------------------
HANDLE			ManualResetEvent;
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	PSET		PSet=(PSET) Param;

	WaitForSingleObject(ManualResetEvent,INFINITE);

	const int	MAX_TIME=1000;
	DWORD		InitialTime=GetTickCount();

	while(true)
	{
		DWORD	ActualTime=GetTickCount();

		if (ActualTime>(InitialTime+MAX_TIME))
			break;

		PSet->insert(ActualTime);
	}

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	ManualResetEvent=CreateEvent(NULL,TRUE,FALSE,NULL);

    DWORD		TimeAdjustment;
    DWORD		TimeIncrement;
    BOOL		TimeAdjustmentDisabled;

	GetSystemTimeAdjustment(&TimeAdjustment,&TimeIncrement,&TimeAdjustmentDisabled);

	wprintf_s(L"TimeAdjustment: [%d], TimeIncrement: [%d], TimeAdjustmentDisabled: [%d] !\n",TimeAdjustment,TimeIncrement,TimeAdjustmentDisabled);

	/*
	// Na volanie nema proces patricne privilegia.
	if (SetSystemTimeAdjustment(TimeAdjustment*2,TimeAdjustmentDisabled)==FALSE)
		wprintf_s(L"SetSystemTimeAdjustment() FAILED !\n");
	*/


	const int			MAX_THREADS=100;
	HANDLE*				Handles=new HANDLE[MAX_THREADS];
	PSET*				Sets=new PSET[MAX_THREADS];

	for (int i=0;i<MAX_THREADS;i++)
	{
		Sets[i]=new SET();
		Handles[i]=(HANDLE)_beginthreadex(NULL,0,MyThread,Sets[i],0,NULL);
	}

	wprintf_s(L"Waiting for all threads to START !\n");

	Sleep(10000);

	SetEvent(ManualResetEvent);

	wprintf_s(L"Now ALL threads will START their JOBS !\n");

	for (int i=0;i<MAX_THREADS;i++)
	{
		WaitForSingleObject(Handles[i],INFINITE);
		CloseHandle(Handles[i]);
	}

	wprintf_s(L"ALL threads FINISHED their JOBS !\n");
	wprintf_s(L"\n");

	DWORD			TotalCount=0;

	for (int i=0;i<MAX_THREADS;i++)
	{
		wprintf_s(L"Set[%d].size(): [%d] !\n",i,Sets[i]->size());

		TotalCount+=Sets[i]->size();

		if (((i+1) % 10)==0)
			_getch();

		delete(Sets[i]);
	}

	wprintf_s(L"Total count: [%d] !\n",TotalCount);

	delete[](Sets);
	delete[](Handles);

	CloseHandle(ManualResetEvent);
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