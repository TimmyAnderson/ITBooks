//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
// !!! FILE [CCWAssembly.tlb] MUSI byt v CURRENT DIRECTORY.
// !!! ASSEMBLY [CCWAssembly] MUSI byt skompilovana a TYPE LIBRARY vytvorena pred kompilaciou tohto PROJECTU.
#import "CCWAssembly.tlb"
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM(void)
{
	CSmartCOMPointer<CCWAssembly::ICCWInterface>				Interface=NULL;
	
	HRESULT														HR=CoCreateInstance(__uuidof(CCWAssembly::CCCWObject),NULL,CLSCTX_INPROC_SERVER,__uuidof(CCWAssembly::ICCWInterface),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		Interface->PrintString("My name is TIMMY ANDERSON !\n");

		Interface=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		TestCOM();
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------