#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
#include <Delayimp.h>
#include "../SimpleDLL/SimpleDLL.h"
//------------------------------------------------------------------------------
// Nato aby program fungoval, musia sa splnit nasledovne podmienky.
/*
   1. V adresari 'DLLDelayLoadingTest' musi byt nakopirovany subor 'SimpleDLL.lib'.
   2. V adresari 'Debug' musi byt subor 'SimpleDLL.dll'.
   3. V 'Project Properties->Linker->Input->Additional Dependencies' pridam 'SimpleDLL.lib'.
   4. V 'Project Properties->Linker->Input->Delay Loaded DLLs' pridam 'SimpleDLL.dll'.
   5. V 'Project Properties->Linker->Advanced->Delay Loaded DLL' pridam nastavim 'Support Unload'.
   !!!!! 6. Ked som v 'Additional Dependencies' a 'Delay Loaded DLLs' zadam CELE MENO i s CESTOU, tak mi to NESLO a LINKER hodil chybu LNK4199.
*/
//------------------------------------------------------------------------------
#pragma comment(lib, "DelayImp.lib")
//------------------------------------------------------------------------------
// DELAY DLL HOOK funkcia.
FARPROC WINAPI DliHook(unsigned Notify, PDelayLoadInfo DLI)
{
	FARPROC			FP=NULL;
	
	switch(Notify)
	{
		case dliStartProcessing:
		{
			// Called when __delayLoadHelper2 attempts to find a DLL/function.
			// Return 0 to have normal behavior or nonzero to override everything (you will still get dliNoteEndProcessing).

			printf_s("Notify - dliStartProcessing: [%d], DLL: [%s], FUNCTION: [%s] !\n",Notify,DLI->szDll,DLI->dlp.szProcName);
		}
		break;

		case dliNotePreLoadLibrary:
		{
			// Called just before LoadLibrary.
			// Return NULL to have __delayLoadHelper2 call LoadLibary or you can call LoadLibrary yourself and return the HMODULE
			FP=(FARPROC) (HMODULE) NULL;

			printf_s("Notify - dliNotePreLoadLibrary: [%d], DLL: [%s], FUNCTION: [%s] !\n",Notify,DLI->szDll,DLI->dlp.szProcName);
		}
		break;

		case dliFailLoadLib:
		{
			// Called if LoadLibrary fails.
			// Again, you can call LoadLibary yourself here and return an HMODULE.
			// If you return NULL, __delayLoadHelper2 raises the ERROR_MOD_NOT_FOUND exception.
			FP=(FARPROC) (HMODULE) NULL;

			printf_s("Notify - dliFailLoadLib: [%d], DLL: [%s], FUNCTION: [%s] !\n",Notify,DLI->szDll,DLI->dlp.szProcName);
		}
		break;

		case dliNotePreGetProcAddress:
		{
			// Called just before GetProcAddress.
			// Return NULL to have __delayLoadHelper2 call GetProcAddress, or you can call GetProcAddress yourself and return the address.
			FP=(FARPROC) NULL;

			printf_s("Notify - dliNotePreGetProcAddress: [%d], DLL: [%s], FUNCTION: [%s] !\n",Notify,DLI->szDll,DLI->dlp.szProcName);
		}
		break;

		case dliFailGetProc:
		{
			// Called if GetProcAddress fails.
			// You can call GetProcAddress yourself here and return an address.
			// If you return NULL, __delayLoadHelper2 raises the ERROR_PROC_NOT_FOUND exception.
			FP=(FARPROC) NULL;

			printf_s("Notify - dliFailGetProc: [%d], DLL: [%s], FUNCTION: [%s] !\n",Notify,DLI->szDll,DLI->dlp.szProcName);
		}
		break;

		case dliNoteEndProcessing:
		{
			// A simple notification that __delayLoadHelper2 is done.
			// You can examine the members of the DelayLoadInfo structure pointed to by pdli and raise an exception if you desire.

			printf_s("Notify - dliNoteEndProcessing: [%d], DLL: [%s], FUNCTION: [%s] !\n",Notify,DLI->szDll,DLI->dlp.szProcName);
		}
		break;
	}

	return(FP);
}
//------------------------------------------------------------------------------
// !!! Namapujem DliHook() na premenne EXPORTOVANE 'DelayImp.lib'.
PfnDliHook __pfnDliNotifyHook2  = DliHook;
PfnDliHook __pfnDliFailureHook2 = DliHook;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void IsModuleLoaded(void)
{
	HMODULE					HMODULE=GetModuleHandle(L"SimpleDLL.dll");

	if (HMODULE!=NULL)
		wprintf(L"Module WAS LOADED !\n");
	else
		wprintf(L"Module WAS NOT LOADED !\n");
}
//------------------------------------------------------------------------------
void CallDLLFunctions(void)
{
	wchar_t					SomeText[1024]={L"Timmy"};

	DLL_ConvertToLower(SomeText);
	wprintf_s(L"DLL_ConvertToLower() returns: [%s] !\n",SomeText);

	IsModuleLoaded();

	DLL_ConvertToUpper(SomeText);
	wprintf_s(L"DLL_ConvertToUpper() returns: [%s] !\n",SomeText);

	IsModuleLoaded();
}
//------------------------------------------------------------------------------
void Test(void)
{
	IsModuleLoaded();

	CallDLLFunctions();

	// Uvolni DELAYED DLL a odstrani ju z ADDRESS SPACE.
	if (__FUnloadDelayLoadedDLL2("SimpleDLL.dll")==TRUE)
		wprintf_s(L"DLL was UNLOADED !\n");
	else
		wprintf_s(L"DLL was NOT UNLOADED !\n");

	CallDLLFunctions();

	// Uvolni DELAYED DLL a odstrani ju z ADDRESS SPACE.
	if (__FUnloadDelayLoadedDLL2("SimpleDLL.dll")==TRUE)
		wprintf_s(L"DLL was UNLOADED !\n");
	else
		wprintf_s(L"DLL was NOT UNLOADED !\n");

	IsModuleLoaded();
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