//-----------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <windows.h>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
DWORD WINAPI Thread111(LPVOID LPParameter)
{
    printf_s("Thread111 METHOD - Thread with [%d] is in PHASE 1 !\n", GetCurrentThreadId());
	Sleep(10*1000);
    printf_s("Thread111 METHOD - Thread with [%d] is in PHASE 2 !\n", GetCurrentThreadId());

    return(0);
}
//-----------------------------------------------------------------------------
DWORD WINAPI Thread222(LPVOID LPParameter)
{
    printf_s("Thread222 METHOD - Thread with [%d] is in PHASE 1 !\n", GetCurrentThreadId());
	Sleep(10*1000);
    printf_s("Thread222 METHOD - Thread with [%d] is in PHASE 2 !\n", GetCurrentThreadId());

    return(0);
}
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	// !!!!! Hodi EXCEPTION.

    HANDLE			HThreads[2];

	CONTEXT			T1;
	CONTEXT			T2;
	CONTEXT			T3;
	CONTEXT			T4;

	ZeroMemory(&T1,sizeof(T1));
	ZeroMemory(&T2,sizeof(T2));
	ZeroMemory(&T3,sizeof(T3));
	ZeroMemory(&T4,sizeof(T4));

	T1.ContextFlags=CONTEXT_ALL;
	T2.ContextFlags=CONTEXT_ALL;
	T3.ContextFlags=CONTEXT_ALL;
	T4.ContextFlags=CONTEXT_ALL;

    HThreads[0]=CreateThread(NULL, 0, &Thread111, NULL, 0, NULL);
    HThreads[1]=CreateThread(NULL, 0, &Thread222, NULL, 0, NULL);

	Sleep(1000);

	SuspendThread(HThreads[0]);
	SuspendThread(HThreads[1]);

    printf_s("Threads have been SUSPENDED !\n");

	Sleep(1000);

	printf_s("%d !\n",GetThreadContext(HThreads[0],&T1));
	printf_s("%d !\n",GetThreadContext(HThreads[1],&T2));

	printf_s("T1 CS_IP: %p, T2 CS_IP: %p !\n",T1.SegCs,T2.SegCs);

	printf_s("%d !\n",SetThreadContext(HThreads[0],&T2));
	printf_s("%d !\n",SetThreadContext(HThreads[1],&T1));

	printf_s("%d !\n",GetThreadContext(HThreads[0],&T3));
	printf_s("%d !\n",GetThreadContext(HThreads[1],&T4));

    printf_s("CONTEXT SWITCH HAS BEEN DONE !\n");

	Sleep(1000);
	ResumeThread(HThreads[0]);
	ResumeThread(HThreads[1]);

    printf_s("Threads have been RESUMED !\n");

	WaitForMultipleObjects(2,HThreads,TRUE,INFINITE);

	ShowExitLine();
	return(0);
}
//-----------------------------------------------------------------------------