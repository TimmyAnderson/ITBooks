#include "stdafx.h"
//------------------------------------------------------------------------------
BOOL APIENTRY DllMain(HMODULE Module, DWORD ReasonForCall, LPVOID Reserved)
{
	if (ReasonForCall==DLL_PROCESS_ATTACH)
		MDLLHandle=Module;

	return(TRUE);
}
//------------------------------------------------------------------------------