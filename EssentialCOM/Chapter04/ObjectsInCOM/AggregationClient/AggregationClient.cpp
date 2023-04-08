//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\InnerAggregationServer\InnerAggregationObject_h.h"
#include "..\OuterAggregationServer\OuterAggregationObject_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void SetInnerText(CSmartCOMPointer<IInnerAggregationText> Interface)
{
	Interface->SetText(L"Timmy Anderson");
}
//------------------------------------------------------------------------------------------------------
void GetInnerText(CSmartCOMPointer<IInnerAggregationText> Interface)
{
	wchar_t														Buffer[1024]={'\0'};
	wchar_t*													Text=(wchar_t*) &Buffer;

	Interface->GetText(_countof(Buffer),(wchar_t**) &Text);

	wprintf_s(L"INNER TEXT: [%s] !\n",Text);
}
//------------------------------------------------------------------------------------------------------
void SetOuterText(CSmartCOMPointer<IOuterAggregationText> Interface)
{
	Interface->SetText(L"Jenny Thompson");
}
//------------------------------------------------------------------------------------------------------
void GetOuterText(CSmartCOMPointer<IOuterAggregationText> Interface)
{
	wchar_t														Buffer[1024]={'\0'};
	wchar_t*													Text=(wchar_t*) &Buffer;

	Interface->GetText(_countof(Buffer),(wchar_t**) &Text);

	wprintf_s(L"OUTER TEXT: [%s] !\n",Text);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM1(void)
{
	CSmartCOMPointer<IInnerAggregationText>						Interface=NULL;

	// !!! COM OBJECT sa vytvaraju pomocou CoCreateInstance().
	HRESULT														HR=CoCreateInstance(CLSID_InnerAggregationObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IInnerAggregationText),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		SetInnerText(Interface);
		GetInnerText(Interface);
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}

	Interface=NULL;
}
//------------------------------------------------------------------------------------------------------
void TestCOM2(void)
{
	CSmartCOMPointer<IOuterAggregationText>						OuterInterface1=NULL;

	// !!! COM OBJECT sa vytvaraju pomocou CoCreateInstance().
	HRESULT														HR=CoCreateInstance(CLSID_OuterAggregationObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOuterAggregationText),(void**) &OuterInterface1);

	if (SUCCEEDED(HR))
	{
		SetOuterText(OuterInterface1);
		GetOuterText(OuterInterface1);

		CSmartCOMPointer<IInnerAggregationText>					InnerInterface=NULL;

		if (SUCCEEDED(HR=OuterInterface1->QueryInterface(IID_IInnerAggregationText,(void**) &InnerInterface)))
		{
			SetInnerText(InnerInterface);
			GetInnerText(InnerInterface);

			CSmartCOMPointer<IOuterAggregationText>				OuterInterface2=NULL;

			if (SUCCEEDED(HR=InnerInterface->QueryInterface(IID_IOuterAggregationText,(void**) &OuterInterface2)))
			{
				GetOuterText(OuterInterface2);

				OuterInterface2=NULL;
			}

			InnerInterface=NULL;
		}
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}

	OuterInterface1=NULL;
}
//------------------------------------------------------------------------------------------------------
void TestCOM3(void)
{
	CSmartCOMPointer<IOuterAggregationText>						OuterInterface1=NULL;

	// !!! COM OBJECT sa vytvaraju pomocou CoCreateInstance().
	HRESULT														HR=CoCreateInstance(CLSID_OuterAggregationObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOuterAggregationText),(void**) &OuterInterface1);

	if (SUCCEEDED(HR))
	{
		SetOuterText(OuterInterface1);
		GetOuterText(OuterInterface1);

		CSmartCOMPointer<IInnerAggregationText>					InnerInterface=NULL;

		if (SUCCEEDED(HR=OuterInterface1->QueryInterface(IID_IInnerAggregationText,(void**) &InnerInterface)))
		{
			SetInnerText(InnerInterface);
			GetInnerText(InnerInterface);

			CSmartCOMPointer<IUnknown>							InnerInterfaceUnknown=NULL;

			if (SUCCEEDED(HR=InnerInterface->QueryInterface(IID_IUnknown,(void**) &InnerInterfaceUnknown)))
			{
				CSmartCOMPointer<IOuterAggregationText>				OuterInterface2=NULL;

				if (SUCCEEDED(HR=InnerInterfaceUnknown->QueryInterface(IID_IOuterAggregationText,(void**) &OuterInterface2)))
				{
					GetOuterText(OuterInterface2);

					OuterInterface2=NULL;
				}

				InnerInterface=NULL;
			}

			InnerInterfaceUnknown=NULL;
		}
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}

	OuterInterface1=NULL;
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
		TestCOM3();
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