//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\CompositionServer\CompositionServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void GetText1(CSmartCOMPointer<IGetText1> Interface)
{
	wchar_t														Buffer[1024]={'\0'};
	wchar_t*													Text=(wchar_t*) &Buffer;

	Interface->GetText(_countof(Buffer),(wchar_t**) &Text);

	wprintf_s(L"TEXT_1 - Text: [%s] !\n",Text);
}
//------------------------------------------------------------------------------------------------------
void GetText2(CSmartCOMPointer<IGetText2> Interface)
{
	wchar_t														Buffer[1024]={'\0'};
	wchar_t*													Text=(wchar_t*) &Buffer;

	Interface->GetText(_countof(Buffer),(wchar_t**) &Text);

	wprintf_s(L"TEXT_2 - Text: [%s] !\n",Text);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM(void)
{
	CSmartCOMPointer<IGetText1>									Interface1=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_CompositionObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGetText1),(void**) &Interface1);

	if (SUCCEEDED(HR))
	{
		GetText1(Interface1);

		CSmartCOMPointer<IGetText2>								Interface2=NULL;

		if (SUCCEEDED(HR=Interface1->QueryInterface(__uuidof(IGetText2),(void**) &Interface2)))
		{
			GetText2(Interface2);

			CSmartCOMPointer<IGetText1>							Interface3=NULL;

			if (SUCCEEDED(HR=Interface2->QueryInterface(__uuidof(IGetText1),(void**) &Interface3)))
			{
				GetText1(Interface3);

				Interface3=NULL;
			}

			Interface2=NULL;
		}

		Interface1=NULL;
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

	CoInitialize(NULL);

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