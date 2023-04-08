//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\AliasingServer\AliasingServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void TestDummy(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE Aliasing.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IAliasingTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_AliasingObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IAliasingTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			if (SUCCEEDED(Interface->Dummy()))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void TestDontCrossApartment(void)
{
	// !!!!! CLIENT zavadza MULTI-TRHEADED APARTMENT, a kedze COM OBJECT pouziva KOMPATIBLINY FREE THREADED APARTMENT NEDOCHADZA k MARSHALING.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IAliasingTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_AliasingObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IAliasingTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[20];
			int													ArrayLength=0;

			// !!! Do COM OBJECT sa prenesie POLE na 20 ITEMS, ale COM OBJECT z neho vyuzije iba 'ArrayLength' ITEMS.
			// !!!!! Kedze CLIENT aj COM OBJECT je v ROVNAKOM APARTMENT, NEROBI sa MARSHALING a NEVOLAJU sa METHODS IAliasingTest_FillArray_Proxy() a IAliasingTest_FillArray_Stub().
			if (SUCCEEDED(Interface->FillArray(_countof(Array),&ArrayLength,Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");

				for(int Index=0;Index<ArrayLength;Index++)
				{
					wprintf(L"CLIENT: ITEM[%d]: [%d] !\n",Index,Array[Index]);
				}
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void TestCrossApartment(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE Aliasing.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IAliasingTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_AliasingObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IAliasingTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[20];
			int													ArrayLength=0;

			// !!! Do COM OBJECT sa prenesie POLE na 20 ITEMS, ale COM OBJECT z neho vyuzije iba 'ArrayLength' ITEMS.
			// !!!!! Kedze CLIENT aj COM OBJECT su v ROZDIELNYCH APARTMENTS, ROBI sa MARSHALING a teda sa VOLAJU METHODS IAliasingTest_FillArray_Proxy() a IAliasingTest_FillArray_Stub().
			if (SUCCEEDED(Interface->FillArray(_countof(Array),&ArrayLength,Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");

				for(int Index=0;Index<ArrayLength;Index++)
				{
					wprintf(L"CLIENT: ITEM[%d]: [%d] !\n",Index,Array[Index]);
				}
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void TestFunctionFromCPPQuote(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE Aliasing.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IAliasingTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_AliasingObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IAliasingTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			if (SUCCEEDED(Interface->CallFunctionDefinedByCPPQuote()))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	//TestDummy();
	//TestDontCrossApartment();
	//TestCrossApartment();
	TestFunctionFromCPPQuote();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------