#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
//------------------------------------------------------------------------------
int					RecursionCounter=0;
//------------------------------------------------------------------------------
void Recursion(BYTE SomeArray[256])
{
	BYTE			Dummy[256];

	RecursionCounter++;

	// Kvoli kompilatoru, aby nehadzal warning tam dam nejaku DUMMY PODMIENKU.
	if (RecursionCounter!=0)
		Recursion(Dummy);
}
//------------------------------------------------------------------------------
LONG WINAPI MyFilterFunction(void)
{
	return(EXCEPTION_EXECUTE_HANDLER);
}
//------------------------------------------------------------------------------
unsigned int WINAPI ThreadFunction(void* Param)
{
	BYTE			Dummy[256];

	__try
	{
		Recursion(Dummy);
	}
	__except(MyFilterFunction())
	{
		wprintf_s(L"Execpetion CAUGHT !\n");
	}

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	HANDLE				Handle;

	Handle=(HANDLE) _beginthreadex(NULL,0,ThreadFunction,NULL,0,NULL);

	WaitForSingleObject(Handle,INFINITE);

	CloseHandle(Handle);

	wprintf_s(L"STACK OVERFLOWED at recursion: [%d] !\n",RecursionCounter);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	HANDLE				Handle;

	// Hodnota STACK moze byt IBA VACSIA ako 1 MB.
	// !!!!! Hadze mi to SEH a neviem preco.
	Handle=(HANDLE) _beginthreadex(NULL,2*1024*1024,ThreadFunction,NULL,0,NULL);

	WaitForSingleObject(Handle,INFINITE);

	CloseHandle(Handle);

	wprintf_s(L"STACK OVERFLOWED at recursion: [%d] !\n",RecursionCounter);
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