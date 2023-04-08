//-----------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <windows.h>
//-----------------------------------------------------------------------------
DWORD WINAPI MyThreadStart(LPVOID LPParameter)
{
    printf("[%d]: Running: [%s] !\n", GetCurrentThreadId(), reinterpret_cast<char *>(LPParameter));
    return(0);
}
//-----------------------------------------------------------------------------
void Test1(void)
{
    HANDLE			HThread;
    DWORD			DWThreadId;

    // Vytvorim Thread.
	// !!!!! Ak nastane chyba tak vrati NULL.
    HThread=CreateThread(NULL, 0, &MyThreadStart, "Hello, World", 0, &DWThreadId);

    if (HThread==NULL)
    {
        fprintf(stderr, "Thread creation failed: [%d] !\n", GetLastError());
        return;
    }

    printf("[%d]: Created thread [%X] - (ID %d) !\n", GetCurrentThreadId(), HThread, DWThreadId);

    // Wait for it to exit and then print the exit code.
    WaitForSingleObject(HThread, INFINITE);

    DWORD			DWExitCode;

	// Ziska navratovu hodnotu Threadu.
    GetExitCodeThread(HThread, &DWExitCode);
    printf("[%d]: Thread exited: [%d] !\n", GetCurrentThreadId(), DWExitCode);
	CloseHandle(HThread);
}
//-----------------------------------------------------------------------------
void Test2(void)
{
	// !!!!! Funkcia GetCurrentHandle() vracia PSEUDO-HANDLE, ktory ma VZDY HONDOTU -2. !!!!! Tento HANDLE NETREBA UZATVARAT.
	HANDLE			H1=GetCurrentThread();

    printf("Pseudo:\t%X !\n", H1);

    HANDLE			H2;

	// !!!!! Ak chcem ziskat SKUTOCNY HANDLE MUSIM POUZIT FUNKCIU DuplicateHandle().
    DuplicateHandle(GetCurrentProcess(), H1, GetCurrentProcess(), &H2, 0, FALSE, DUPLICATE_SAME_ACCESS);

    printf("Real:\t%X !\n", H2);

    CloseHandle(H2);
}
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//Test1();
	Test2();

	printf("\nPress any key to EXIT !\n");
	_getch();

	return(0);
}
//-----------------------------------------------------------------------------