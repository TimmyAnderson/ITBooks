//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\TearOffServer\TearOffServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void SetOuterName(CSmartCOMPointer<ITearOffTextOuter> Interface)
{
	Interface->SetTextOuter(L"Timmy Anderson");
}
//------------------------------------------------------------------------------------------------------
void GetOuterName(CSmartCOMPointer<ITearOffTextOuter> Interface)
{
	wchar_t														Buffer[1024]={'\0'};
	wchar_t*													Text=(wchar_t*) &Buffer;

	Interface->GetTextOuter(_countof(Buffer),(wchar_t**) &Text);

	wprintf_s(L"OUTER - Text: [%s] !\n",Text);
}
//------------------------------------------------------------------------------------------------------
void SetInnerName(CSmartCOMPointer<ITearOffTextInner> Interface)
{
	Interface->SetTextInner(L"Jenny Thompson");
}
//------------------------------------------------------------------------------------------------------
void GetInnerName(CSmartCOMPointer<ITearOffTextInner> Interface)
{
	wchar_t														Buffer[1024]={'\0'};
	wchar_t*													Text=(wchar_t*) &Buffer;

	Interface->GetTextInner(_countof(Buffer),(wchar_t**) &Text);

	wprintf_s(L"INNER - Text: [%s] !\n",Text);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM1(void)
{
	CSmartCOMPointer<ITearOffTextOuter>							Interface=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_TearOffObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ITearOffTextOuter),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		SetOuterName(Interface);

		GetOuterName(Interface);

		Interface=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM2(void)
{
	CSmartCOMPointer<ITearOffTextOuter>							OuterInterface=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_TearOffObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ITearOffTextOuter),(void**) &OuterInterface);

	if (SUCCEEDED(HR))
	{
		SetOuterName(OuterInterface);
		GetOuterName(OuterInterface);

		CSmartCOMPointer<ITearOffTextInner>						InnerInterface1=NULL;
		CSmartCOMPointer<ITearOffTextInner>						InnerInterface2=NULL;
		CSmartCOMPointer<ITearOffTextInner>						InnerInterface3=NULL;

		if (SUCCEEDED(HR=OuterInterface->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface1)))
		{
			SetInnerName(InnerInterface1);
			GetInnerName(InnerInterface1);

			GetOuterName(OuterInterface);

			InnerInterface1=NULL;
		}

		if (SUCCEEDED(HR=OuterInterface->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface2)))
		{
			GetInnerName(InnerInterface2);

			GetOuterName(OuterInterface);

			InnerInterface2=NULL;
		}

		if (SUCCEEDED(HR=OuterInterface->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface3)))
		{
			GetInnerName(InnerInterface3);

			GetOuterName(OuterInterface);

			InnerInterface3=NULL;
		}

		OuterInterface=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM3(void)
{
	CSmartCOMPointer<ITearOffTextOuter>							OuterInterface=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_TearOffObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ITearOffTextOuter),(void**) &OuterInterface);

	if (SUCCEEDED(HR))
	{
		SetOuterName(OuterInterface);
		GetOuterName(OuterInterface);

		CSmartCOMPointer<ITearOffTextInner>						InnerInterface1=NULL;
		CSmartCOMPointer<ITearOffTextInner>						InnerInterface2=NULL;
		CSmartCOMPointer<ITearOffTextInner>						InnerInterface3=NULL;

		HRESULT													HR1=OuterInterface->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface1);
		HRESULT													HR2=OuterInterface->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface2);
		HRESULT													HR3=OuterInterface->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface3);

		// !!! Umyselne odstranim COM OBJECT, pricom ale POINTERS na TEAR-OFF INTERFACES su PLATNE.
		OuterInterface=NULL;

		if (SUCCEEDED(HR1))
		{
			SetInnerName(InnerInterface1);
			GetInnerName(InnerInterface1);

			InnerInterface1=NULL;
		}

		if (SUCCEEDED(HR2))
		{
			GetInnerName(InnerInterface2);

			InnerInterface2=NULL;
		}

		if (SUCCEEDED(HR3))
		{
			GetInnerName(InnerInterface3);

			InnerInterface3=NULL;
		}
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM4(void)
{
	CSmartCOMPointer<ITearOffTextOuter>							OuterInterface=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_TearOffObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ITearOffTextOuter),(void**) &OuterInterface);

	if (SUCCEEDED(HR))
	{
		SetOuterName(OuterInterface);
		GetOuterName(OuterInterface);

		CSmartCOMPointer<ITearOffTextInner>						InnerInterface1=NULL;
		CSmartCOMPointer<ITearOffTextInner>						InnerInterface2=NULL;
		CSmartCOMPointer<ITearOffTextInner>						InnerInterface3=NULL;
		CSmartCOMPointer<ITearOffTextInner>						InnerInterface4=NULL;
		CSmartCOMPointer<ITearOffTextInner>						InnerInterface5=NULL;
		CSmartCOMPointer<ITearOffTextOuter>						OuterInterfaceFromInner=NULL;

		HRESULT													HR1=OuterInterface->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface1);
		HRESULT													HR2=OuterInterface->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface2);
		HRESULT													HR3=OuterInterface->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface3);
		HRESULT													HR4=InnerInterface3->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface4);
		HRESULT													HR5=InnerInterface3->QueryInterface(IID_ITearOffTextInner,(void**) &InnerInterface5);
		HRESULT													HR6=InnerInterface3->QueryInterface(IID_ITearOffTextOuter,(void**) &OuterInterfaceFromInner);


		// !!! Umyselne odstranim COM OBJECT, pricom ale POINTERS na TEAR-OFF INTERFACES su PLATNE.
		OuterInterface=NULL;

		if (SUCCEEDED(HR1))
		{
			SetInnerName(InnerInterface1);
			GetInnerName(InnerInterface1);

			InnerInterface1=NULL;
		}

		if (SUCCEEDED(HR2))
		{
			GetInnerName(InnerInterface2);

			InnerInterface2=NULL;
		}

		if (SUCCEEDED(HR3))
		{
			GetInnerName(InnerInterface3);

			InnerInterface3=NULL;
		}

		if (SUCCEEDED(HR4))
		{
			GetInnerName(InnerInterface4);

			InnerInterface4=NULL;
		}

		if (SUCCEEDED(HR5))
		{
			GetInnerName(InnerInterface5);

			InnerInterface5=NULL;
		}

		if (SUCCEEDED(HR6))
		{
			GetOuterName(OuterInterfaceFromInner);

			OuterInterfaceFromInner=NULL;
		}
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
		TestCOM4();
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