#include "stdafx.h"
#include <windows.h>
#include "..\LockingDuringShutdownDLL\LockingDuringShutdownDLL.h"
#include "MyDebug.h"
//------------------------------------------------------------------------------
void Test(void)
{
	IgnoreCriticalSection();

    // Vytvorim thread, ktory v DLL ziska LOCKS.
    CreateThread(NULL, 0, &GetAndBlock, NULL, 0, NULL);

    // Pockam kym sa thread spusti.
    SleepEx(3000, TRUE);

    // Spustim PROCESS SHUTDOWN.
    ExitProcess(0);
}
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------