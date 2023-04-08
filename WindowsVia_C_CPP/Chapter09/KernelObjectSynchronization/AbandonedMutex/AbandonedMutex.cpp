#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
HANDLE				MyMutex;
//------------------------------------------------------------------------------
unsigned int WINAPI MyThreadNormal(void* Param)
{
	wchar_t		Buffer[1024];
	int			Size=_countof(Buffer);

	StringCchPrintf(Buffer,Size,L"Before CS !\n");
	WriteDebugText(Buffer);

	DWORD		Ret=WaitForSingleObject(MyMutex,INFINITE);

	if (Ret==WAIT_OBJECT_0)
		StringCchPrintf(Buffer,Size,L"INSIDE CS - WAIT FINISHED NORMALLY !\n");
	else
		StringCchPrintf(Buffer,Size,L"INSIDE CS - WAIT FINISHED by ABANDONING !\n");

	WriteDebugText(Buffer);
	Sleep(3000);

	ReleaseMutex(MyMutex);

	StringCchPrintf(Buffer,Size,L"After RELEASE !\n");
	WriteDebugText(Buffer);

	return(0);
}
//------------------------------------------------------------------------------
unsigned int WINAPI MyThreadAbandoned(void* Param)
{
	wchar_t		Buffer[1024];
	int			Size=_countof(Buffer);

	StringCchPrintf(Buffer,Size,L"KILL THREAD - Before CS !\n");
	WriteDebugText(Buffer);

	DWORD		Ret=WaitForSingleObject(MyMutex,INFINITE);

	if (Ret==WAIT_OBJECT_0)
		StringCchPrintf(Buffer,Size,L"KILL THREAD - INSIDE CS - WAIT FINISHED NORMALLY !\n");
	else
		StringCchPrintf(Buffer,Size,L"KILL THREAD - INSIDE CS - WAIT FINISHED by ABANDONING !\n");

	WriteDebugText(Buffer);
	Sleep(3000);

	StringCchPrintf(Buffer,Size,L"Mutex WILL BE ABANDONED !\n");
	WriteDebugText(Buffer);

	// NEZAVOLAM ReleaseMutex() a MUTEX sa stane ABANDONED.

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

	MyMutex=CreateMutex(NULL,FALSE,NULL);

	Handle1=(HANDLE)_beginthreadex(NULL,0,MyThreadAbandoned,NULL,0,NULL);

	Sleep(1000);

	Handle2=(HANDLE)_beginthreadex(NULL,0,MyThreadNormal,NULL,0,NULL);
	Handle3=(HANDLE)_beginthreadex(NULL,0,MyThreadNormal,NULL,0,NULL);

	WaitForSingleObject(Handle1,INFINITE);
	WaitForSingleObject(Handle2,INFINITE);
	WaitForSingleObject(Handle3,INFINITE);

	CloseHandle(MyMutex);
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