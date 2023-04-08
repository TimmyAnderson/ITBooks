#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
SRWLOCK				LOCK;
//-----------------------------------------------------------------------------
unsigned WINAPI WorkerThreadReader1(void*)
{
	printf("WorkerThreadReader 111 STARTED !\n");

	Sleep(100);

	__try
	{
		::AcquireSRWLockShared(&LOCK);
		printf("WorkerThreadReader 111 READER LOCK - ACQUIRED !\n");

		Sleep(3*1000);
	}
	__finally
	{
		printf("WorkerThreadReader 111 READER LOCK - WILL BE RELEASED !\n");
		ReleaseSRWLockShared(&LOCK);
	}

	printf("WorkerThreadReader 111 FINISHED !\n");

	return(0);
}
//-----------------------------------------------------------------------------
unsigned WINAPI WorkerThreadReader2(void*)
{
	printf("WorkerThreadReader 222 STARTED !\n");

	Sleep(100);

	__try
	{
		::AcquireSRWLockShared(&LOCK);
		printf("WorkerThreadReader 222 READER LOCK - ACQUIRED !\n");

		Sleep(3*1000);
	}
	__finally
	{
		printf("WorkerThreadReader 222 READER LOCK - WILL BE RELEASED !\n");
		ReleaseSRWLockShared(&LOCK);
	}

	printf("WorkerThreadReader 222 FINISHED !\n");

	return(0);
}
//-----------------------------------------------------------------------------
unsigned WINAPI WorkerThreadWriter(void*)
{
	printf("WorkerThreadWriter STARTED !\n");

	// !!!!! KED TU PREDLZIM LOCK na 500, tak OBE READER THREADS sa vykonaju SKOR a OBE VOJDU DO LOCKU zatial co WRITER LOCK CAKA.
	// !!!!! KED TU DAM NAOPAK 0, tak WRITER LOCK JE ZISKANY AKO PRVY a OBE READER LOCK CAKAJU kym WRITER LOCK NESKONCI a KED SKONCI, tak OBE READER THREADS VOJDU DO LOCK.
	//Sleep(500);
	Sleep(0);

	__try
	{
		::AcquireSRWLockExclusive(&LOCK);
		printf("WorkerThreadWriter WRITER LOCK - ACQUIRED !\n");

		Sleep(3*1000);
	}
	__finally
	{
		printf("WorkerThreadWriter WRITER LOCK - WILL BE RELEASED !\n");
		ReleaseSRWLockExclusive(&LOCK);
	}

	printf("WorkerThreadWriter FINISHED !\n");

	return(0);
}
//-----------------------------------------------------------------------------
void TestSRWL(void)
{
	const int		THREADS_COUNT=3;
	HANDLE			HThread[THREADS_COUNT];

	// Inicializuje SRWLOCK - NIE JE TREBA HO LIKVIDOVAT - na rozdiel od CS.
	InitializeSRWLock(&LOCK);

	HThread[0]=(HANDLE)_beginthreadex(NULL,0,&WorkerThreadReader1,NULL,CREATE_SUSPENDED,NULL);
	HThread[1]=(HANDLE)_beginthreadex(NULL,0,&WorkerThreadReader2,NULL,CREATE_SUSPENDED,NULL);
	HThread[2]=(HANDLE)_beginthreadex(NULL,0,&WorkerThreadWriter,NULL,CREATE_SUSPENDED,NULL);

	for (int i=0;i<THREADS_COUNT;i++)
		ResumeThread(HThread[i]);

	WaitForMultipleObjects(THREADS_COUNT,HThread,TRUE,INFINITE);

	for (int i=0;i<THREADS_COUNT;i++)
		CloseHandle(HThread[i]);
}
//-----------------------------------------------------------------------------
void RecursionTest()
{
	// Inicializuje SRWLOCK - NIE JE TREBA HO LIKVIDOVAT - na rozdiel od CS.
	InitializeSRWLock(&LOCK);

	__try
	{
		AcquireSRWLockShared(&LOCK);
		printf("%d - LOCK 1 time - ACQUIRED !\n",GetTickCount());

		Sleep(3*1000);

		__try
		{
			// Simulacie rekurzie.
			AcquireSRWLockShared(&LOCK);
			printf("%d - LOCK 2 time - ACQUIRED !\n",GetTickCount());

			Sleep(3*1000);
		}
		__finally
		{
			printf("%d - LOCK 2 time - WILL BE RELEASED !\n",GetTickCount());
			ReleaseSRWLockShared(&LOCK);
		}
	}
	__finally
	{
		printf("%d - LOCK 1 time - WILL BE RELEASED !\n",GetTickCount());
		ReleaseSRWLockShared(&LOCK);
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	//TestSRWL();
	RecursionTest();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------