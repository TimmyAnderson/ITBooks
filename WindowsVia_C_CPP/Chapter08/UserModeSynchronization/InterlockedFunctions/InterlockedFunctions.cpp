#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
int		SharedVariable=0;
LONG	LOCK=FALSE;
//------------------------------------------------------------------------------
void SpinLock(void)
{
	// Cyklim, az kym POVODNA HODNOTA NEBUDE FALSE.
	// Kedze nova hodnota je TRUE, tak LOCK bol UDELENY.
	while(InterlockedExchange(&LOCK,TRUE)==TRUE)
		Sleep(0);
}
//------------------------------------------------------------------------------
void SpinUnlock(void)
{
	InterlockedExchange(&LOCK,FALSE);
}
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	wprintf_s(L"Calculating...\n");

	for (int i=0;i<10000000;i++)
	{
		SpinLock();

		int			Temp=SharedVariable;

		Temp++;

		SharedVariable=Temp;

		SpinUnlock();
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

	Handle1=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);
	Handle2=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	WaitForSingleObject(Handle1,INFINITE);
	WaitForSingleObject(Handle2,INFINITE);

	wprintf_s(L"Result: [%d] !\n",SharedVariable);

	CloseHandle(Handle1);
	CloseHandle(Handle2);
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