#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <list>
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
SRWLOCK				Lock;
CONDITION_VARIABLE	QueueNotEmpty;
HANDLE				ExitHandle;
list<int>			List;
//------------------------------------------------------------------------------
unsigned int WINAPI ReaderThread(void* Param)
{
	DWORD			ID=GetCurrentThreadId();

	while(true)
	{
		AcquireSRWLockExclusive(&Lock);

		if (List.size()==0)
			// !!! Uvolni 'Lock' a zaroven CAKA NA SIGNALIZACIU 'QueueNotEmpty'.
			// !!! Ked je 'QueueNotEmpty' SIGNALIZOVANY, POKUSI SA ZISKAT 'Lock'. AZ KED HO ZISKA, moze pokracovat.
			// !!! Thread, ktory prvy ziska 'Lock' a 'QueueNotEmpty' je SIGNALIZOVANY - pre neho volanie SleepConditionVariableSRW() SKONCI a ZAROVEN sa 'QueueNotEmpty' RESETNE DO NESIGNALIZOVANEHO STAVU.
			SleepConditionVariableSRW(&QueueNotEmpty,&Lock,INFINITE,0);

		if (WaitForSingleObject(ExitHandle,0)==WAIT_OBJECT_0)
		{
			ReleaseSRWLockExclusive(&Lock);
			return(0);
		}

		int			Value=*List.begin();
			
		List.pop_front();

		ReleaseSRWLockExclusive(&Lock);

		wprintf_s(L"[%d] - Reader reads: [%d] !\n",ID,Value);
	}

	return(0);
}
//------------------------------------------------------------------------------
unsigned int WINAPI WriterThread(void* Param)
{
	DWORD			ID=GetCurrentThreadId();
	int				Counter=0;

	while(true)
	{
		wprintf_s(L"[%d] - Press eny key or 'Q' to quit !\n",ID);

		int			Key=_getch();

		if (Key=='q' || Key=='Q')
		{
			SetEvent(ExitHandle);
			WakeAllConditionVariable(&QueueNotEmpty);
			break;
		}

		for (int i=0;i<10;i++)
		{
			AcquireSRWLockExclusive(&Lock);

			List.push_back(++Counter);

			WakeConditionVariable(&QueueNotEmpty);

			wprintf_s(L"[%d] - Writer writes: [%d] !\n",ID,Counter);

			ReleaseSRWLockExclusive(&Lock);
		}
	}

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle1;
	HANDLE				Handle2;
	HANDLE				Handle3;

	ExitHandle=CreateEvent(NULL,TRUE,FALSE,NULL);

	InitializeSRWLock(&Lock);
	InitializeConditionVariable(&QueueNotEmpty);

	Handle1=(HANDLE)_beginthreadex(NULL,0,ReaderThread,NULL,0,NULL);
	Handle2=(HANDLE)_beginthreadex(NULL,0,ReaderThread,NULL,0,NULL);
	Handle3=(HANDLE)_beginthreadex(NULL,0,WriterThread,NULL,0,NULL);

	WaitForSingleObject(Handle1,INFINITE);
	WaitForSingleObject(Handle2,INFINITE);
	WaitForSingleObject(Handle3,INFINITE);

	CloseHandle(ExitHandle);
	CloseHandle(Handle1);
	CloseHandle(Handle2);
	CloseHandle(Handle3);
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