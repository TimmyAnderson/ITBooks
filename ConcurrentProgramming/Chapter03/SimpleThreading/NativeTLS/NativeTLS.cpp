#include "stdafx.h"
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <time.h>
//-----------------------------------------------------------------------------
DWORD				TLSIndex=-1;
//-----------------------------------------------------------------------------
DWORD WINAPI MyTLSThread(LPVOID RND)
{
	printf("[%d]: Running - TLS VALUE: %d !\n", GetCurrentThreadId(), (int) RND);

	// Ulozim hodnotu do TLS.
	BOOL			Ret=TlsSetValue(TLSIndex,(LPVOID) RND);

	printf("[%d]: Running - TlsSetValue() RETURNED: %d !\n", GetCurrentThreadId(), Ret);

	// Nacitam hodnotu z TLS.
	printf("[%d]: Running - TLS BEFORE SLEEP: %d !\n", GetCurrentThreadId(), (int) TlsGetValue(TLSIndex));
	Sleep(5000);
	// Nacitam hodnotu z TLS.
	printf("[%d]: Running - TLS AFTER SLEEP: %d !\n", GetCurrentThreadId(), (int) TlsGetValue(TLSIndex));

    return(0);
}
//------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	// Alokujem TLS Entry.
	// !!!!! Ak by som zakomentoval toto a teda TLS ENTRY by sa NEVYTVORILA, potom TlsSetValue() by vratila FALSE a TlsGetValue() NULL s chybou v GetLastError().
	TLSIndex=TlsAlloc();

	printf("TLS ENTRY: %d !\n\n",TLSIndex);

	const int			COUNT=5;
	HANDLE				HThread[COUNT];
	
	for (int i=0;i<COUNT;i++)
		HThread[i]=CreateThread(NULL, 0, &MyTLSThread, (LPVOID) (i+1), 0, NULL);

	WaitForMultipleObjects(COUNT,HThread,TRUE,INFINITE);

	// Dealokujem TLS Entry.
	::TlsFree(TLSIndex);

	printf("\nPress any key to EXIT !\n");
	_getch();

	return(0);
}
//------------------------------------------------------------------------