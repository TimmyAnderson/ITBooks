#include <stdio.h>
#include <windows.h>
//-----------------------------------------------------------------------------
DWORD DoSingleWait(HANDLE H, DWORD DWMilliseconds, BOOL BAlertable)
{
    // Ulozim si zaciatok WAIT operacie.
    DWORD			DWStart=GetTickCount();
    DWORD			DWElapsed=0;

    DWORD			DWRet=0;

	// Budem realizovat cyklus ak by vdaka bAlertable==TRUE vratil WAIT_IO_COMPLETION.
    while ((DWRet=WaitForSingleObjectEx(H, DWMilliseconds-DWElapsed, BAlertable))==WAIT_IO_COMPLETION)
    {
        if (DWMilliseconds!=INFINITE)
        {
			// Upravim TIMEOUT.
            DWElapsed=GetTickCount()-DWStart;

            if (DWElapsed>=DWMilliseconds)
            {
                // Timeout bol prekroceny.
                DWRet=WAIT_TIMEOUT;
                break;
            }
        }

        // Kedze doslo APC (navratova hodnota WAIT_IO_COMPLETION) ZOPAKUJEM WaitXXX() s UPRAVENYM TIMEOUT.
    }

    return(DWRet);
}
//-----------------------------------------------------------------------------
DWORD DoMultipleWait(DWORD DWCount, HANDLE Handles[], BOOL BWaitAll, DWORD DWMilliseconds, BOOL BAlertable)
{
    // Ulozim si zaciatok WAIT operacie.
    DWORD			DWStart=GetTickCount();
    DWORD			DWElapsed=0;

    DWORD			DWRet=0;

	// Budem realizovat cyklus ak by vdaka bAlertable==TRUE vratil WAIT_IO_COMPLETION.
	while ((DWRet=WaitForMultipleObjectsEx(DWCount, Handles, BWaitAll, DWMilliseconds-DWElapsed, BAlertable))==WAIT_IO_COMPLETION)
    {
        if (DWMilliseconds!=INFINITE)
        {
			// Upravim TIMEOUT.
            DWElapsed=GetTickCount()-DWStart;

            if (DWElapsed>=DWMilliseconds)
            {
                // Timeout bol prekroceny.
                DWRet=WAIT_TIMEOUT;
                break;
            }
        }

        // Kedze doslo APC (navratova hodnota WAIT_IO_COMPLETION) ZOPAKUJEM WaitXXX() s UPRAVENYM TIMEOUT.
    }

    return(DWRet);
}
//-----------------------------------------------------------------------------
DWORD DoWait(const HANDLE *PHandles, int CHandles, DWORD DWMilliseconds, BOOL BAlertable, BOOL &ProgramExit)
{
    DWORD		DWRet;
    DWORD		DWStart=GetTickCount();
    DWORD		DWElapsed=0;

	ProgramExit=FALSE;

    while(TRUE)
    {
        // Wait zaroven caka aj na prichod Messages do MESSAGE QUEUE.
        DWRet=MsgWaitForMultipleObjectsEx(CHandles, PHandles, DWMilliseconds-DWElapsed, QS_ALLINPUT, BAlertable ? MWMO_ALERTABLE : 0);

		// Dosla MESSAGE.
        if (DWRet==WAIT_OBJECT_0+CHandles)
        {
            MSG				Msg;

            while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)==TRUE)
            {
				// Ak dosla Message na ukoncenie programu vyskocim z cyklu.
                if (Msg.message == WM_QUIT)
                {
                    PostQuitMessage((int)Msg.wParam);
                    ProgramExit=TRUE;
					DWRet=WAIT_TIMEOUT;
                    break;
                }

                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
            }

			// Ak dosla Message na ukoncenie programu, tak vyskocim z funkcie.
            if (ProgramExit==TRUE)
                break;
        }
		// Ak doslo k singnalizacii niektoreho z HANDLES, tak ukoncim funkciu.
        else if (DWRet!=WAIT_IO_COMPLETION)
        {
            break;
        }

        if (DWMilliseconds!=INFINITE)
        {
			// Ak nastala APC - preratam TIMEOUT.
			DWElapsed=GetTickCount()-DWStart;

			if (DWMilliseconds<DWElapsed)
			{
				DWRet=WAIT_TIMEOUT;
				break;
			}
		}
    }

    return(DWRet);
}
//-----------------------------------------------------------------------------