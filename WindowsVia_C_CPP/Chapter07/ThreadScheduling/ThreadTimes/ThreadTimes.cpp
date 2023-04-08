#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
HANDLE		Exit;
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	wprintf_s(L"Thread WAS started and will last for 1 second !\n");

	Sleep(1000);

	wprintf_s(L"Thread lasted for 1 second is going to FINISH !\n");

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
unsigned __int64 GetTime(FILETIME FT)
{
	unsigned __int64	High=FT.dwHighDateTime;
	unsigned __int64	Low=FT.dwLowDateTime;
	unsigned __int64	Ret=High<<32;
	
	Ret+=Low;

	return(Ret);
}
//------------------------------------------------------------------------------
void Test1(void)
{
	HANDLE				Handle;

	Handle=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	WaitForSingleObject(Handle,INFINITE);

    FILETIME			CreationTime;
    FILETIME			ExitTime;
    FILETIME			KernelTime;
    FILETIME			UserTime;

	GetThreadTimes(Handle,&CreationTime,&ExitTime,&KernelTime,&UserTime);

    unsigned __int64		ICreationTime=GetTime(CreationTime);
    unsigned __int64		IExitTime=GetTime(ExitTime);
    unsigned __int64		IKernelTime=GetTime(KernelTime);
    unsigned __int64		IUserTime=GetTime(UserTime);
	unsigned __int64		Diff=IExitTime-ICreationTime;
	unsigned long double	DiffInMS=(unsigned long double) Diff/10/1000/1000;

	wprintf_s(L"CreationTime: [%I64d], ExitTime: [%I64d], KernelTime: [%I64d], UserTime: [%I64d], Diff: [%I64i], DiffInMS: [%f] !\n",ICreationTime,IExitTime,IKernelTime,IUserTime,Diff,DiffInMS);

	CloseHandle(Handle);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	HANDLE				Handle;
	LARGE_INTEGER		LIStart;
	LARGE_INTEGER		LIEnd;

	QueryPerformanceCounter(&LIStart);

	Handle=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	WaitForSingleObject(Handle,INFINITE);

	QueryPerformanceCounter(&LIEnd);

	__int64					Diff=LIEnd.QuadPart-LIStart.QuadPart;
	unsigned long double	DiffInMS=(unsigned long double) Diff/10/1000/1000;

	wprintf_s(L"Diff: [%I64i], DiffInMS: [%f] !\n",Diff,DiffInMS);

	CloseHandle(Handle);
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