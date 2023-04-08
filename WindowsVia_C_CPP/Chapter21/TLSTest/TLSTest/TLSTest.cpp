#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
// Dynamicke TLS.
DWORD							TLSSlot1;
DWORD							TLSSlot2;
// Staticke TLS.
__declspec(thread) DWORD		TLSStatic=0;
// !!!!! NEMUSIA MAT DLZKU sizeof(POINTER), ale KLUDNE TO MOZU BYT I VELKE POLIA.
__declspec(thread) DWORD		TLSStaticArray[4]={0,0,0,0};
//------------------------------------------------------------------------------
unsigned int WINAPI WorkerThread(void* Param)
{
	// !!!!! Pri volani TlsAlloc() je vo vsetkych threads dany SLOT nastaveny na 0.
	wprintf_s(L"START - TID: [%d], Slot1: [%d], Slot2: [%d], Static: [%d], SA[0]: [%d], SA[1]: [%d], SA[2]: [%d], SA[3]: [%d] !\n",GetCurrentThreadId(),(DWORD) TlsGetValue(TLSSlot1),(DWORD) TlsGetValue(TLSSlot2),TLSStatic,TLSStaticArray[0],TLSStaticArray[1],TLSStaticArray[2],TLSStaticArray[3]);

	TlsSetValue(TLSSlot1,(PVOID) GetCurrentThreadId());
	TlsSetValue(TLSSlot2,(PVOID) GetCurrentThreadId());
	TLSStatic=GetCurrentThreadId();
	TLSStaticArray[0]=GetCurrentThreadId();
	TLSStaticArray[1]=GetCurrentThreadId()-1;
	TLSStaticArray[2]=GetCurrentThreadId()-2;
	TLSStaticArray[3]=GetCurrentThreadId()-3;

	wprintf_s(L"AFTER SET - TID: [%d], Slot1: [%d], Slot2: [%d], Static: [%d], SA[0]: [%d], SA[1]: [%d], SA[2]: [%d], SA[3]: [%d] !\n",GetCurrentThreadId(),(DWORD) TlsGetValue(TLSSlot1),(DWORD) TlsGetValue(TLSSlot2),TLSStatic,TLSStaticArray[0],TLSStaticArray[1],TLSStaticArray[2],TLSStaticArray[3]);

	Sleep(1000);

	wprintf_s(L"END - TID: [%d], Slot1: [%d], Slot2: [%d], Static: [%d], SA[0]: [%d], SA[1]: [%d], SA[2]: [%d], SA[3]: [%d] !\n",GetCurrentThreadId(),(DWORD) TlsGetValue(TLSSlot1),(DWORD) TlsGetValue(TLSSlot2),TLSStatic,TLSStaticArray[0],TLSStaticArray[1],TLSStaticArray[2],TLSStaticArray[3]);

	return(0);
}
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle1;
	HANDLE				Handle2;

	TLSSlot1=TlsAlloc();

	// Thread su SUSPENDED.
	Handle1=(HANDLE)_beginthreadex(NULL,0,WorkerThread,NULL,CREATE_SUSPENDED,NULL);
	Handle2=(HANDLE)_beginthreadex(NULL,0,WorkerThread,NULL,CREATE_SUSPENDED,NULL);

	// Vytvorim SLOT az po vytvoreni THREADS, no i tento SLOT je mozne NORMALNE POUZTIT, kedze je v zasade jedno kedy sa SLOT vytvori.
	TLSSlot2=TlsAlloc();

	ResumeThread(Handle1);
	ResumeThread(Handle2);

	WaitForSingleObject(Handle1,INFINITE);
	WaitForSingleObject(Handle2,INFINITE);

	TlsFree(TLSSlot1);
	TlsFree(TLSSlot2);

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