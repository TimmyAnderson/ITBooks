#include "stdafx.h"
#include <process.h>
#include <windows.h>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
struct ThreadParams
{
	HANDLE			ExitHandle;
	wchar_t			*Text;
};
//-----------------------------------------------------------------------------
unsigned WINAPI MutexThread(void* Param)
{
	ThreadParams	*TP=(ThreadParams*)Param;
	HANDLE			Mutex=CreateMutex(NULL,FALSE,L"MyMutex");
	wchar_t			*Text=TP->Text;
	HANDLE			Handles[]={TP->ExitHandle,Mutex};

	while(true)
	{
		DWORD	Ret=WaitForMultipleObjects(sizeof(Handles)/sizeof(Handles[0]),Handles,FALSE,INFINITE);

		if (Ret==WAIT_OBJECT_0)
		{
			wprintf(L"%s - EXIT HANDLE SIGNALIZED !\n",Text);
			break;
		}
		else if (Ret==(WAIT_OBJECT_0+1))
		{
			wprintf(L"%s - MUTEX SIGNALIZED - START !\n",Text);
			Sleep(300);
			wprintf(L"%s - MUTEX SIGNALIZED - END !\n",Text);
			ReleaseMutex(Mutex);
		}
		else if (Ret==(WAIT_ABANDONED_0+1))
		{
			wprintf(L"%s - MUTEX ABANDONED - START !\n",Text);
			Sleep(300);
			wprintf(L"%s - MUTEX ABANDONED - END !\n",Text);

			// !!!!! Tu MUSIM SPRAVIT ReleaseMutex(), lebo AJ KED je vrateny WAIT_ABANDONED_0 tak ABANDONED MUTEX je LOCKUTY.
			ReleaseMutex(Mutex);
		}
		else
			wprintf(L"%s - UNEXPECTED VALUE !\n",Text);
	}

	return(0);
}
//-----------------------------------------------------------------------------
unsigned WINAPI AbandonedMutexThread(void* Param)
{
	ThreadParams	*TP=(ThreadParams*)Param;
	HANDLE			Mutex=CreateMutex(NULL,FALSE,L"MyMutex");
	wchar_t			*Text=TP->Text;
	HANDLE			Handles[]={TP->ExitHandle,Mutex};

	while(true)
	{
		DWORD	Ret=WaitForMultipleObjects(sizeof(Handles)/sizeof(Handles[0]),Handles,FALSE,INFINITE);

		if (Ret==WAIT_OBJECT_0)
		{
			wprintf(L"%s - EXIT HANDLE SIGNALIZED !\n",Text);
			break;
		}
		else if (Ret==(WAIT_OBJECT_0+1))
		{
			wprintf(L"%s - MUTEX SIGNALIZED - START !\n",Text);
			Sleep(300);
			wprintf(L"%s - MUTEX SIGNALIZED - END !\n",Text);

			wprintf(L"%s - MUTEX WILL NOT BE RELEASED !\n",Text);
			return(0);
		}
		else if (Ret==(WAIT_ABANDONED_0+1))
		{
			wprintf(L"%s - MUTEX ABANDONED - START !\n",Text);
			Sleep(300);
			wprintf(L"%s - MUTEX ABANDONED - END !\n",Text);

			// !!!!! Tu MUSIM SPRAVIT ReleaseMutex(), lebo AJ KED je vrateny WAIT_ABANDONED_0 tak ABANDONED MUTEX je LOCKUTY.
			ReleaseMutex(Mutex);
		}
		else
			wprintf(L"%s - UNEXPECTED VALUE !\n",Text);
	}

	return(0);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleMutexes(void)
{
	HANDLE			ExitHandle1=CreateEvent(NULL,FALSE,FALSE,NULL);
	HANDLE			ExitHandle2=CreateEvent(NULL,FALSE,FALSE,NULL);
	ThreadParams	TP[]={{ExitHandle1,L"111"},{ExitHandle2,L"222"}};
	HANDLE			HThread1=(HANDLE)_beginthreadex(NULL,0,MutexThread,&TP[0],0,NULL);
	HANDLE			HThread2=(HANDLE)_beginthreadex(NULL,0,MutexThread,&TP[1],0,NULL);

	// Teraz sa budu MUTEXES PREPINAT.
	Sleep(3000);

	wprintf(L"EXIT EVENTS WILL be FIRED !\n");
	SetEvent(ExitHandle1);
	SetEvent(ExitHandle2);
	wprintf(L"EXIT EVENTS WERE FIRED !\n");

	WaitForSingleObject(HThread1,INFINITE);
	WaitForSingleObject(HThread2,INFINITE);
	wprintf(L"THREADS FINISHED !\n");

	CloseHandle(ExitHandle1);
	CloseHandle(ExitHandle2);
	CloseHandle(HThread1);
	CloseHandle(HThread2);
}
//-----------------------------------------------------------------------------
void TestAbandonedMutex(void)
{
	HANDLE			ExitHandle1=CreateEvent(NULL,FALSE,FALSE,NULL);
	HANDLE			ExitHandle2=CreateEvent(NULL,FALSE,FALSE,NULL);
	HANDLE			ExitHandle3=CreateEvent(NULL,FALSE,FALSE,NULL);
	ThreadParams	TP[]={{ExitHandle1,L"111"},{ExitHandle2,L"222"},{ExitHandle3,L"ABANDONED"}};
	HANDLE			HThread1=(HANDLE)_beginthreadex(NULL,0,MutexThread,&TP[0],0,NULL);
	HANDLE			HThread2=(HANDLE)_beginthreadex(NULL,0,MutexThread,&TP[1],0,NULL);
	HANDLE			HThread3=(HANDLE)_beginthreadex(NULL,0,AbandonedMutexThread,&TP[2],0,NULL);

	// Teraz sa budu MUTEXES PREPINAT.
	Sleep(5000);

	wprintf(L"EXIT EVENTS WILL be FIRED !\n");
	SetEvent(ExitHandle1);
	SetEvent(ExitHandle2);
	SetEvent(ExitHandle3);
	wprintf(L"EXIT EVENTS WERE FIRED !\n");

	WaitForSingleObject(HThread1,INFINITE);
	WaitForSingleObject(HThread2,INFINITE);
	WaitForSingleObject(HThread3,INFINITE);
	wprintf(L"THREADS FINISHED !\n");

	CloseHandle(ExitHandle1);
	CloseHandle(ExitHandle2);
	CloseHandle(ExitHandle3);
	CloseHandle(HThread1);
	CloseHandle(HThread2);
	CloseHandle(HThread3);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	//TestSimpleMutexes();
	TestAbandonedMutex();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------