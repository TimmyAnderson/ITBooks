#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include "ExitTest.h"
//------------------------------------------------------------------------------
DWORD*			ThreadStackMem=NULL;
//------------------------------------------------------------------------------
struct PH
{
	HANDLE		PseudoHandle;
	HANDLE		RealHandle;
};
//------------------------------------------------------------------------------
DWORD WINAPI PseudoHandleThread(PVOID Param)
{
	PH*			Handles=(PH*) Param;

	// Bezi iba pod Vistou.
	//DWORD		PseudoID=GetThreadId(Handles->PseudoHandle);
	//DWORD		RealID=GetThreadId(Handles->RealHandle);

	DWORD		PseudoID=(DWORD) Handles->PseudoHandle;
	DWORD		RealID=(DWORD) Handles->RealHandle;

	wprintf_s(L"Thread [%d] - PseudoID: [%d], RealID: [%d] !\n",GetCurrentThreadId(),PseudoID,RealID);

	Sleep(3000);

	wprintf_s(L"Thread [%d] FINISHED !\n",GetCurrentThreadId());

	return(0);
}
//------------------------------------------------------------------------------
DWORD WINAPI MyAPIThread(PVOID Param)
{
	CExitTest		Local(L"LOCAL");
	wchar_t*		Data=(wchar_t*) Param;

	wprintf_s(L"Thread [%d] - Thread with data [%s] STARTED !\n",GetCurrentThreadId(),Data);

	Sleep(3000);

	wprintf_s(L"Thread [%d] - Thread with data [%s] is going to be FINISHED !\n",GetCurrentThreadId(),Data);

	return(0);
}
//------------------------------------------------------------------------------
DWORD WINAPI DoExitThread(PVOID Param)
{
	CExitTest		Local(L"LOCAL");
	wchar_t*		Data=(wchar_t*) Param;
	DWORD			StackMem=100;

	ThreadStackMem=&StackMem;

	wprintf_s(L"Thread [%d] - Thread with data [%s] STARTED !\n",GetCurrentThreadId(),Data);

	Sleep(3000);

	wprintf_s(L"Thread [%d] - Thread with data [%s] is going to be TERMINATE !\n",GetCurrentThreadId(),Data);

	ExitThread(0);

	// Tu sa uz nikdy nedostanem.
	wprintf_s(L"Thread [%d] - UNREACHABLE !\n",GetCurrentThreadId(),Data);

	return(0);
}
//------------------------------------------------------------------------------
DWORD WINAPI DoEndThread(PVOID Param)
{
	CExitTest		Local(L"LOCAL");
	wchar_t*		Data=(wchar_t*) Param;
	DWORD			StackMem=100;

	ThreadStackMem=&StackMem;

	wprintf_s(L"Thread [%d] - Thread with data [%s] STARTED !\n",GetCurrentThreadId(),Data);

	Sleep(3000);

	wprintf_s(L"Thread [%d] - Thread with data [%s] is going to be TERMINATE !\n",GetCurrentThreadId(),Data);

	_endthreadex(0);

	// Tu sa uz nikdy nedostanem.
	wprintf_s(L"Thread [%d] - UNREACHABLE !\n",GetCurrentThreadId(),Data);

	return(0);
}
//------------------------------------------------------------------------------
DWORD WINAPI DoTerminateThread(PVOID Param)
{
	CExitTest		Local(L"LOCAL");
	wchar_t*		Data=(wchar_t*) Param;
	DWORD			StackMem=100;

	ThreadStackMem=&StackMem;

	wprintf_s(L"Thread [%d] - Thread with data [%s] WAITING to be TERMINATED !\n",GetCurrentThreadId(),Data);

	Sleep(INFINITE);

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	wchar_t*		Data=L"Timmy Anderson";
	HANDLE			HThread;

	wprintf_s(L"Thread [%d] - Thread with data [%s] is going to be STARTED !\n",GetCurrentThreadId(),Data);

	HThread=CreateThread(NULL,0,MyAPIThread,Data,0,NULL);

	WaitForSingleObject(HThread,INFINITE);

	wprintf_s(L"Thread [%d] - Thread with data [%s] FINISHED !\n",GetCurrentThreadId(),Data);

	CloseHandle(HThread);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	wchar_t*		Data=L"Timmy Anderson";
	HANDLE			HThread;

	wprintf_s(L"Thread [%d] - Thread with data [%s] is going to be STARTED !\n",GetCurrentThreadId(),Data);

	HThread=CreateThread(NULL,0,DoExitThread,Data,0,NULL);

	WaitForSingleObject(HThread,INFINITE);

	wprintf_s(L"Thread [%d] - Thread with data [%s] FINISHED !\n",GetCurrentThreadId(),Data);

	// Zlyha, kedze ExitThread() LIKVIDUJE STACK UKONCOVANEHO THREADU.
	//wprintf_s(L"Thread [%d] - ThreadStackMem value: [%d] !\n",GetCurrentThreadId(),*ThreadStackMem);

	CloseHandle(HThread);
}
//------------------------------------------------------------------------------
void Test3(void)
{
	wchar_t*		Data=L"Timmy Anderson";
	HANDLE			HThread;

	wprintf_s(L"Thread [%d] - Thread with data [%s] is going to be STARTED !\n",GetCurrentThreadId(),Data);

	HThread=CreateThread(NULL,0,DoEndThread,Data,0,NULL);

	WaitForSingleObject(HThread,INFINITE);

	wprintf_s(L"Thread [%d] - Thread with data [%s] FINISHED !\n",GetCurrentThreadId(),Data);

	CloseHandle(HThread);
}
//------------------------------------------------------------------------------
void Test4(void)
{
	wchar_t*		Data=L"Timmy Anderson";
	HANDLE			HThread;

	wprintf_s(L"Thread [%d] - Thread with data [%s] is going to be STARTED !\n",GetCurrentThreadId(),Data);

	HThread=CreateThread(NULL,0,DoTerminateThread,Data,0,NULL);

	// Pockam kym sa Thread rozbehne.
	Sleep(1000);

	// !!!!! Signalizujem, ze Thread ma by TERMINATED.
	TerminateThread(HThread,999);

	// !!!!! Pockam kym sa Thread OZAJ TERMINUJE.
	WaitForSingleObject(HThread,INFINITE);

	DWORD			ExitCode;

	GetExitCodeThread(HThread,&ExitCode);

	wprintf_s(L"Thread [%d] - Thread with data [%s] FINISHED, ExitCode: [%d] !\n",GetCurrentThreadId(),Data,ExitCode);

	// !!!!! PREBEHNE KOREKTNE, kedze TerminateThread() NEUVOLNUJE STACK likvidovaneho Threadu.
	wprintf_s(L"Thread [%d] - ThreadStackMem value: [%d] - THREAD'S STACK HASN'T BEEN CLEANED !\n",GetCurrentThreadId(),*ThreadStackMem);

	CloseHandle(HThread);
}
//------------------------------------------------------------------------------
void Test5(void)
{
	HANDLE			HThread;
	PH				PHO;

	wprintf_s(L"Thread [%d] STARTED !\n",GetCurrentThreadId());

	PHO.PseudoHandle=GetCurrentThread();

	// Spravim duplikat z PSEUDOHANDLE na SKUTOCNY HANDLE.
	DuplicateHandle(GetCurrentProcess(),PHO.PseudoHandle,GetCurrentProcess(),&PHO.RealHandle,0,FALSE,DUPLICATE_SAME_ACCESS);

	HThread=CreateThread(NULL,0,PseudoHandleThread,&PHO,0,NULL);

	WaitForSingleObject(HThread,INFINITE);

	wprintf_s(L"Thread [%d] FINISHED !\n",GetCurrentThreadId());

	CloseHandle(HThread);

	// Musim uzavriet i DUPLIKOVANY HANDLE.
	CloseHandle(PHO.RealHandle);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	Test5();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------