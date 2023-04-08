#include "stdafx.h"
#include "LockingDuringShutdownDLL.h"
#include <stdio.h>
//------------------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE HInstDLL, DWORD FDWReason, LPVOID LPReserved)
{
    DWORD								ThreadID=GetCurrentThreadId();

    switch (FDWReason)
    {
		// Inicializujem synchronizacne objekty.
        case DLL_PROCESS_ATTACH:
		{
            InitializeCriticalSection(&GCS);
            GIgnoreCS=FALSE;
            GMutex=CreateMutex(NULL, FALSE, NULL);

#ifdef USE_SWR
            InitializeSRWLock(&GRWL);
#endif
		}
        break;

		// Pri PROCESS SHUTDOWN sa pokusim ZISKAT LOCKS nad synchronizacnymi objektmi.
        case DLL_PROCESS_DETACH:
		{
            if (GIgnoreCS==FALSE)
			{
                wprintf_s(L"%x: Acquiring GCS during shutdown...", ThreadID);

                EnterCriticalSection(&GCS);
                printf("SUCCESS !!!\n");
                DeleteCriticalSection(&GCS);
            }

            wprintf_s(L"%x: Acquiring GMUTEX during shutdown...", ThreadID);

            DWORD		Result=WaitForSingleObject(GMutex, INFINITE);

            if (Result==WAIT_ABANDONED)
                wprintf_s(L"ABANDONED !!!\n");
            else
                wprintf_s(L"SUCCESS !!!\n");

            CloseHandle(GMutex);

#ifdef USE_SWR
            wprintf_s(L"%x: Acquiring GRWL(X) during shutdown...", ThreadID);
            AcquireSRWLockExclusive(&GRWL);
            wprintf_s(L"SUCCESS !!!\n");
#endif
		}
		break;
    }

    return(TRUE);
}
//------------------------------------------------------------------------------
// Tato funkcia je vyvolana z EXE programu.
// Funkcia ma za ulohu ziskat LOCKS a simulovat nejaky WAIT akoze drzi locks.
LOCKINGDURINGSHUTDOWNDLL_API DWORD WINAPI GetAndBlock(LPVOID LPParameter)
{
    DWORD				ThreadID=GetCurrentThreadId();

    // Ziskam locks.
    EnterCriticalSection(&GCS);
    wprintf_s(L"%x: GCS ACQUIRED !!!\n", ThreadID);

#ifdef USE_SWR
    AcquireSRWLockExclusive(&GRWL);
    wprintf_s(L"%x: GRWL(X) ACQUIRED !!!\n", ThreadID);
#endif

    WaitForSingleObject(GMutex, INFINITE);
    wprintf_s(L"%x: GMUTEX ACQUIRED !!!\n", ThreadID);

    // Simulacia WAIT - akoze drzim LOCKS.
    SleepEx(25000, TRUE);

    return(0);
}
//------------------------------------------------------------------------------
LOCKINGDURINGSHUTDOWNDLL_API VOID WINAPI IgnoreCriticalSection()
{
    GIgnoreCS=TRUE;
}
//------------------------------------------------------------------------------