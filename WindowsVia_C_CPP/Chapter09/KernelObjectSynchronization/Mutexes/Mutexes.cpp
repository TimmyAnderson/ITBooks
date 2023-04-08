#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
HANDLE				MyMutex;
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	wchar_t		Buffer[1024];
	int			Size=_countof(Buffer);

	StringCchPrintf(Buffer,Size,L"Before 1. CS !\n");
	WriteDebugText(Buffer);

	WaitForSingleObject(MyMutex,INFINITE);

	StringCchPrintf(Buffer,Size,L"Before 2. CS !\n");
	WriteDebugText(Buffer);
	Sleep(1000);

	WaitForSingleObject(MyMutex,INFINITE);

	StringCchPrintf(Buffer,Size,L"INSIDE 2. CS !\n");
	WriteDebugText(Buffer);
	Sleep(1000);

	ReleaseMutex(MyMutex);

	StringCchPrintf(Buffer,Size,L"After 1. RELEASE !\n");
	WriteDebugText(Buffer);
	Sleep(1000);

	ReleaseMutex(MyMutex);

	StringCchPrintf(Buffer,Size,L"After 2. RELEASE !\n");
	WriteDebugText(Buffer);
	Sleep(1000);

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle1;
	HANDLE				Handle2;

	MyMutex=CreateMutex(NULL,FALSE,NULL);

	Handle1=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);
	Handle2=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	WaitForSingleObject(Handle1,INFINITE);
	WaitForSingleObject(Handle2,INFINITE);

	CloseHandle(MyMutex);
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