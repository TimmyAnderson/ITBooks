#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
CRITICAL_SECTION		CS;
CONDITION_VARIABLE		CV;
bool					SharedCondition=false;
//-----------------------------------------------------------------------------
unsigned WINAPI WorkerThread1(void*)
{
	printf("%d - Worker thread 111 STARTED !\n",GetTickCount());

	// Dam threadu 222 casu na start.
	Sleep(3*1000);

	printf("%d - Worker thread 111 IS GOING to ENTER CS !\n",GetTickCount());

	// Pokusam sa vstupit do CS.
	EnterCriticalSection(&CS);

	printf("%d - Worker thread 111 HAS ENTERED CS !\n",GetTickCount());

	Sleep(3*1000);

	// Nastavim podmienku na ktoru 2. thread caka.
	SharedCondition=true;

	printf("%d - Worker thread 111 HAS CHANGED SharedCondition to TRUE !\n",GetTickCount());

	printf("%d - Worker thread 111 IS GOING TO WAKE CV !\n",GetTickCount());

	// Uvolnim CV.
	WakeConditionVariable(&CV);

	printf("%d - Worker thread 111 HAS WOKEN CV and is WAITING for 1 SECOND !\n",GetTickCount());

	// Dam tu pauzu, aby bolo jasne vidiet, ze AJ PO UVOLNENI CV 2. thread NEMOZE VSTUPIT do CS, pretoze ta je drzana tymto threadom.
	Sleep(1*1000);

	printf("%d - Worker thread 111 IS GOING TO LEAVE CS !\n",GetTickCount());

	// Az teraz ked sa uvolni aj CS, skonci volanie SleepConditionVariableCS() v 2. threade.
	LeaveCriticalSection(&CS);

	printf("%d - Worker thread 111 FINISHED !\n",GetTickCount());

	return(0);
}
//-----------------------------------------------------------------------------
unsigned WINAPI WorkerThread2(void*)
{
	printf("%d - Worker thread 222 STARTED !\n",GetTickCount());

	Sleep(100);

	printf("%d - Worker thread 222 IS GOING to ENTER CS !\n",GetTickCount());

	// Vstupim do CS.
	EnterCriticalSection(&CS);

	printf("%d - Worker thread 222 HAS ENTERED CS !\n",GetTickCount());

	// !!! Pristupujem k ZDIELANEJ PAMETI a testujem ci THREAD MOZE POKRACOVAT VO VYKONAVANI KODU.
	// !!! Ak SharedCondition je stale FALSE - tak sa volanim SleepConditionVariableCS UVOLNI CS a ATOMICKY sa SPUSTI WAIT na CV.
	if (SharedCondition==false)
	{
		printf("%d - Worker thread 222 CONDITION SharedCondition is FLASE and THREAD CAN WILL WAIT FOR CV and CS !\n",GetTickCount());
		SleepConditionVariableCS(&CV,&CS,INFINITE);
		printf("%d - Worker thread 222 CONDITION SharedCondition is now TRUE and THREAD CAN CONTINUE !\n",GetTickCount());
	}
	else
	{
		printf("%d - Worker thread 222 CONDITION SharedCondition is now TRUE and THREAD CAN CONTINUE !\n",GetTickCount());
	}

	printf("%d - Worker thread 222 HAS RE-ENTERED CS because CV was RELEASED !\n",GetTickCount());

	Sleep(3*1000);

	printf("%d - Worker thread 222 IS GOING TO LEAVE CS !\n",GetTickCount());

	// Ukoncim CS.
	LeaveCriticalSection(&CS);

	printf("%d - Worker thread 222 FINISHED !\n",GetTickCount());

	return(0);
}
//-----------------------------------------------------------------------------
void Test(void)
{
	InitializeCriticalSection(&CS);

	const int		THREADS_COUNT=2;
	HANDLE			HThread[THREADS_COUNT];

	// Inicializuje CV - NIE JE TREBA JU LIKVIDOVAT - na rozdiel od CS.
	InitializeConditionVariable(&CV);

	HThread[0]=(HANDLE)_beginthreadex(NULL,0,&WorkerThread1,NULL,CREATE_SUSPENDED,NULL);
	HThread[1]=(HANDLE)_beginthreadex(NULL,0,&WorkerThread2,NULL,CREATE_SUSPENDED,NULL);

	for (int i=0;i<THREADS_COUNT;i++)
		ResumeThread(HThread[i]);

	WaitForMultipleObjects(THREADS_COUNT,HThread,TRUE,INFINITE);

	for (int i=0;i<THREADS_COUNT;i++)
		CloseHandle(HThread[i]);

	DeleteCriticalSection(&CS);
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