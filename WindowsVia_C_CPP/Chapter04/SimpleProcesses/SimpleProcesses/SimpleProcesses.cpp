#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
//------------------------------------------------------------------------------
void Test1(void)
{
	// Priklad vypisu globalnych premennych.
	wprintf(L"__argc: [%d] !\n",__argc);
	
	for (int i=0;i<__argc;i++)
		wprintf(L"__wargv[%d]: [%s] !\n",i,__wargv[i]);

	// DEPRECATED.
	// Namiesto '_wpgmptr' by sa mal pouzivat '_get_wpgmptr()'.
	//wprintf(L"_wpgmptr: [%d] !\n",_wpgmptr);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	HINSTANCE		APP=GetModuleHandle(NULL);
	HINSTANCE		SIMPLEPROCESS_EXE=GetModuleHandle(L"SimpleProcesses.exe");
	HINSTANCE		KERNEL32_DLL=GetModuleHandle(L"KERNEL32.DLL");
	HINSTANCE		SIMPLEPROCESS_EXE_ByEx;
	HINSTANCE		KERNEL32_DLL_ByEx;

	// Parameter je ADRESA na Test2().
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,(LPCWSTR) Test2,&SIMPLEPROCESS_EXE_ByEx);

	// Parameter je ADRESA na CreateThread(), ktory je v KERNE32.DLL.
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,(LPCWSTR) CreateProcess,&KERNEL32_DLL_ByEx);

	wprintf_s(L"APP [%X] !\n",APP);
	wprintf_s(L"SIMPLEPROCESS_EXE [%X] !\n",SIMPLEPROCESS_EXE);
	wprintf_s(L"KERNEL32_DLL [%X] !\n",KERNEL32_DLL);
	wprintf_s(L"SIMPLEPROCESS_EXE_ByEx [%X] !\n",SIMPLEPROCESS_EXE_ByEx);
	wprintf_s(L"KERNEL32_DLL_ByEx [%X] !\n",KERNEL32_DLL_ByEx);
}
//------------------------------------------------------------------------------
void Test3(void)
{
	OSVERSIONINFOEX	OSInfo;

	ZeroMemory(&OSInfo,sizeof(OSInfo));
	OSInfo.dwOSVersionInfoSize=sizeof(OSInfo);

	GetVersionEx((LPOSVERSIONINFOW) &OSInfo);

	wprintf_s(L"MajorVersion: [%d] !\n",OSInfo.dwMajorVersion);
	wprintf_s(L"MinorVersion: [%d] !\n",OSInfo.dwMinorVersion);
	wprintf_s(L"ServicePackMajor: [%d] !\n",OSInfo.wServicePackMajor);
	wprintf_s(L"ServicePackMinor: [%d] !\n",OSInfo.wServicePackMinor);
}
//------------------------------------------------------------------------------
void Test4(void)
{
	DWORD			IDs[500];
	DWORD			ProcessCount=0;

	EnumProcesses(IDs,sizeof(IDs),&ProcessCount);

	wprintf_s(L"Process count: [%d] !\n",ProcessCount);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	//Test2();
	//Test3();
	Test4();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------