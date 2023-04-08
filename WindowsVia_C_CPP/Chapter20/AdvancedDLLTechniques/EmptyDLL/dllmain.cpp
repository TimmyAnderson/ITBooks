#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------
BOOL ProcessAttach(void)
{
	wprintf_s(L"PROCESS ATTACH - PID: [%d], TID: [%d] !\n",GetCurrentProcessId(),GetCurrentThreadId());

	// Ak vratim TRUE, DLL sa zavedie, ak FALSE, nezavedie sa.
	return(TRUE);
}
//-----------------------------------------------------------------------------
void ThreadAttach(void)
{
	wprintf_s(L"THREAD ATTACH - PID: [%d], TID: [%d] !\n",GetCurrentProcessId(),GetCurrentThreadId());
}
//-----------------------------------------------------------------------------
void ThreadDetach(void)
{
	wprintf_s(L"THREAD DETACH - PID: [%d], TID: [%d] !\n",GetCurrentProcessId(),GetCurrentThreadId());
}
//-----------------------------------------------------------------------------
void ProcessDetach(void)
{
	wprintf_s(L"PROCESS DETACH - PID: [%d], TID: [%d] !\n",GetCurrentProcessId(),GetCurrentThreadId());
}
//-----------------------------------------------------------------------------
BOOL APIENTRY DllMain(HMODULE Module, DWORD  ReasonForCall, LPVOID Reserved)
{
	BOOL		Ret=TRUE;

	switch (ReasonForCall)
	{
		case DLL_PROCESS_ATTACH:
			// Zablokujem volanie DLL_THREAD_ATTACH a DLL_THREAD_DETACH.
			//DisableThreadLibraryCalls(Module);

			Ret=ProcessAttach();
		break;

		case DLL_THREAD_ATTACH:
			ThreadAttach();
		break;

		case DLL_THREAD_DETACH:
			ThreadDetach();
		break;

		case DLL_PROCESS_DETACH:
			ProcessDetach();
		break;
	}

	return(Ret);
}
//-----------------------------------------------------------------------------