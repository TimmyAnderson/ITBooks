#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
#include "../SimpleDLL/SimpleDLL.h"
//------------------------------------------------------------------------------
typedef void (*PDLL_ConvertToUpper)(wchar_t* Text);
typedef void (*PDLL_ConvertToLower)(wchar_t* Text);
//------------------------------------------------------------------------------
void Test(void)
{
	wchar_t					SomeText[1024]={L"Timmy"};
	HMODULE					HDLL=LoadLibrary(L"..//SimpleDLL//Debug//SimpleDLL.dll");

	// !!!!! MENA NESMU BYT MANGLED - a preto MUSIM pri generovani DLL pouzit klauzulu 'extern "C"'.
	FARPROC					P1=GetProcAddress(HDLL,"DLL_ConvertToLower");
	FARPROC					P2=GetProcAddress(HDLL,"DLL_ConvertToUpper");

	PDLL_ConvertToLower		Func1=(PDLL_ConvertToLower) P1;
	PDLL_ConvertToUpper		Func2=(PDLL_ConvertToUpper) P2;

	Func1(SomeText);
	wprintf_s(L"DLL_ConvertToLower() returns: [%s] !\n",SomeText);

	Func2(SomeText);
	wprintf_s(L"DLL_ConvertToUpper() returns: [%s] !\n",SomeText);

	FreeLibrary(HDLL);
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