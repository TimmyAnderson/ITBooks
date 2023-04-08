#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
#include "../HookInjectionDLL/HookInjectionDLL.h"
//------------------------------------------------------------------------------
void Test(void)
{
	HHOOK			HookHandle=NULL;

	if (InstallHook(&HookHandle,true)==true)
	{
		wprintf_s(L"HOOK [%d] was INSTALLED !\n",HookHandle);

		while(true)
		{
			wprintf_s(L"Press 'X' to UNHOOK !\n");

			int		Key=_getch();

			if (Key=='x' || Key=='X')
				break;
		}

		if (UninstallHook()==true)
			wprintf_s(L"HOOK was UNINSTALLED !\n");
		else
			wprintf_s(L"HOOK FAILED to UNINSTALL !\n");
	}
	else
		wprintf_s(L"HOOK FAILED to INSTALL !\n");
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