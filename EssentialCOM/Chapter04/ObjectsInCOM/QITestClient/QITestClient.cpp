//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\QITestServer\QITestServer_h.h"
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

	Interface->GetText1(_countof(Buffer),(wchar_t**) &Text);

	wprintf_s(L"TEXT_1 - Text: [%s] !\n",Text);
}
//------------------------------------------------------------------------------------------------------
void GetText2(CSmartCOMPointer<IGetText2> Interface)
{
	wchar_t														Buffer[1024]={'\0'};
	wchar_t*													Text=(wchar_t*) &Buffer;

	Interface->GetText2(_countof(Buffer),(wchar_t**) &Text);

	wprintf_s(L"TEXT_2 - Text: [%s] !\n",Text);
}
//------------------------------------------------------------------------------------------------------
void GetText3(CSmartCOMPointer<IGetText3> Interface)
{
	wchar_t														Buffer[1024]={'\0'};
	wchar_t*													Text=(wchar_t*) &Buffer;

	Interface->GetText3(_countof(Buffer),(wchar_t**) &Text);

	wprintf_s(L"TEXT_3 - Text: [%s] !\n",Text);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM1(void)
{
	CSmartCOMPointer<IGetText1>									Interface1=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_QITestObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGetText1),(void**) &Interface1);

	if (SUCCEEDED(HR))
	{
		GetText1(Interface1);

		CSmartCOMPointer<IGetText2>								Interface2=NULL;

		if (SUCCEEDED(HR=Interface1->QueryInterface(__uuidof(IGetText2),(void**) &Interface2)))
		{
			GetText2(Interface2);

			CSmartCOMPointer<IGetText3>							Interface3=NULL;

			if (SUCCEEDED(HR=Interface2->QueryInterface(__uuidof(IGetText3),(void**) &Interface3)))
			{
				GetText3(Interface3);

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
void TestCOM2(void)
{
	CSmartCOMPointer<IGetText1>									Interface1=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_QITestObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGetText1),(void**) &Interface1);

	if (SUCCEEDED(HR))
	{
		GetText1(Interface1);

		CSmartCOMPointer<IGetText2>								Interface2=NULL;

		// !!! Z IGetText1 ziskam IGetText2.
		if (SUCCEEDED(HR=Interface1->QueryInterface(__uuidof(IGetText2),(void**) &Interface2)))
		{
			GetText2(Interface2);

			CSmartCOMPointer<IGetText1>							Interface3=NULL;

			// !!! Kedze z IGetText2 som schopny ziskat IGetText1, tak QueryInterface() je SYMMETRIC.
			if (SUCCEEDED(HR=Interface2->QueryInterface(__uuidof(IGetText1),(void**) &Interface3)))
			{
				GetText1(Interface3);

				wprintf_s(L"COM is SYMMETRIC !\n");

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
void TestCOM3(void)
{
	CSmartCOMPointer<IGetText1>									Interface1=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_QITestObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGetText1),(void**) &Interface1);

	if (SUCCEEDED(HR))
	{
		GetText1(Interface1);

		CSmartCOMPointer<IGetText2>								Interface2=NULL;

		// !!! Z IGetText1 ziskam IGetText2.
		if (SUCCEEDED(HR=Interface1->QueryInterface(__uuidof(IGetText2),(void**) &Interface2)))
		{
			GetText2(Interface2);

			CSmartCOMPointer<IGetText3>							Interface31=NULL;

			// !!! Z IGetText2 ziskam IGetText3.
			if (SUCCEEDED(HR=Interface2->QueryInterface(__uuidof(IGetText3),(void**) &Interface31)))
			{
				GetText3(Interface31);

				CSmartCOMPointer<IGetText3>							Interface32=NULL;

				// !!! Kedze aj z IGetText1 som schopny ziskat IGetText3, tak QueryInterface() je TRANSITIVE.
				if (SUCCEEDED(HR=Interface1->QueryInterface(__uuidof(IGetText3),(void**) &Interface32)))
				{
					GetText3(Interface32);

					wprintf_s(L"COM is TRANSITIVE !\n");

					Interface32=NULL;
				}

				Interface31=NULL;
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
void TestCOM4(void)
{
	CSmartCOMPointer<IGetText1>									Interface11=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_QITestObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGetText1),(void**) &Interface11);

	if (SUCCEEDED(HR))
	{
		GetText1(Interface11);

		CSmartCOMPointer<IGetText1>								Interface12=NULL;

		// !!! Z IGetText1 ziskam IGetText1.
		if (SUCCEEDED(HR=Interface11->QueryInterface(__uuidof(IGetText1),(void**) &Interface12)))
		{
			GetText1(Interface12);

			wprintf_s(L"COM is REFLEXIVE !\n");

			Interface12=NULL;
		}

		Interface11=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM5(void)
{
	CSmartCOMPointer<IUnknown>									Interface11=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_QITestObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IUnknown),(void**) &Interface11);

	if (SUCCEEDED(HR))
	{
		CSmartCOMPointer<IUnknown>								Interface12=NULL;

		// !!! Z IGetText1 ziskam IGetText1.
		if (SUCCEEDED(HR=Interface11->QueryInterface(__uuidof(IUnknown),(void**) &Interface12)))
		{
			if (Interface11.GetInterface()==Interface12.GetInterface())
			{
				wprintf_s(L"POINTERS are SAME !\n");
			}
			else
			{
				wprintf_s(L"POINTERS are DIFFERENT !\n");
			}

			Interface12=NULL;
		}

		Interface11=NULL;
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
		//TestCOM1();
		//TestCOM2();
		//TestCOM3();
		//TestCOM4();
		TestCOM5();
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