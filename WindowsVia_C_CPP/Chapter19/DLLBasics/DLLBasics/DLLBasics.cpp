#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
#include "../SimpleDLL/SimpleDLL.h"
//------------------------------------------------------------------------------
void Test(void)
{
	// Pouzijem exportovanu premennu.
	DLL_SomeValue=100;

	wprintf_s(L"DLL_SomeValue has value: [%d] !\n",DLL_SomeValue);

	wchar_t			SomeText[1024]={L"Timmy"};

	// Pouzijem exportovanu funkciu.
	DLL_ConvertToUpper(SomeText);

	wprintf_s(L"Result of DLL_ConvertToUpper(): [%s] !\n",SomeText);

	// Pouzijem exportovanu triedu.
	CSimpleDLL*		SomeClass=new CSimpleDLL();

	SomeClass->SetBuffer(L"Timmy Anderson");

	wprintf_s(L"Result of CSimpleDLL::GetBuffer(): [%s] !\n",SomeClass->GetBuffer());

	delete(SomeClass);
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