//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\CustomDispatchServer\CustomDispatchServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void TestNonDispatch(void)
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<ICustomDispatchTest>					Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_CustomDispatchObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ICustomDispatchTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			if (SUCCEEDED(Interface->SetValue(bstr_t(L"Timmy Anderson"))))
			{
				bstr_t											Value;

				if (SUCCEEDED(Interface->GetValue(Value.GetAddress())))
				{
					wprintf(L"VALUE: [%s] !\n",Value.operator const wchar_t *());
				}
				else
				{
					wprintf_s(L"METHOD CALL FAILED !\n");
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
void TestDispatch(void)
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<ICustomDispatchTest>					Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_CustomDispatchObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ICustomDispatchTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			CSmartCOMPointer<IDispatch>							DispatchInterface=NULL;

			if (SUCCEEDED(Interface->QueryInterface(__uuidof(IDispatch),(void**) &DispatchInterface)))
			{
				DISPID											SetValueID=0;
				DISPID											GetValueID=0;
				OLECHAR*										SetValueName=L"SetValue";
				OLECHAR*										GetValueName=L"GetValue";

				if (SUCCEEDED(HR=DispatchInterface->GetIDsOfNames(GUID_NULL,&SetValueName,1,LOCALE_SYSTEM_DEFAULT,&SetValueID)))
				{
					if (SUCCEEDED(HR=DispatchInterface->GetIDsOfNames(GUID_NULL,&GetValueName,1,LOCALE_SYSTEM_DEFAULT,&GetValueID)))
					{
						variant_t								SetValueParamsArray[1];

						SetValueParamsArray[0]=bstr_t(L"Timmy Anderson");

						DISPPARAMS								SetValueParams={SetValueParamsArray,NULL,_countof(SetValueParamsArray),0};
						variant_t								SetValueResult;

						if (SUCCEEDED(DispatchInterface->Invoke(SetValueID,IID_NULL,LOCALE_SYSTEM_DEFAULT,DISPATCH_METHOD,&SetValueParams,SetValueResult.GetAddress(),NULL,NULL)))
						{
							VARIANTARG							GetValueParamsArray[1];
							bstr_t								Value;

							VariantInit(GetValueParamsArray);

							GetValueParamsArray[0].vt=VT_BYREF | VT_BSTR;
							GetValueParamsArray[0].pbstrVal=Value.GetAddress();

							DISPPARAMS							GetValueParams={GetValueParamsArray,NULL,_countof(GetValueParamsArray),0};
							variant_t							GetValueResult;

							if (SUCCEEDED(DispatchInterface->Invoke(GetValueID,IID_NULL,LOCALE_SYSTEM_DEFAULT,DISPATCH_METHOD,&GetValueParams,GetValueResult.GetAddress(),NULL,NULL)))
							{
								wprintf(L"VALUE: [%s] !\n",Value.operator const wchar_t *());
							}
							else
							{
								wprintf_s(L"METHOD CALL FAILED !\n");
							}

							VariantClear(GetValueParamsArray);
						}
						else
						{
							wprintf_s(L"METHOD CALL FAILED !\n");
						}
					}
					else
					{
						wprintf_s(L"Can't GET METHOD ID !\n");
					}
				}
				else
				{
					wprintf_s(L"Can't GET METHOD ID !\n");
				}

				DispatchInterface=NULL;
			}
			else
			{
				wprintf_s(L"Can't GET DISPATCH INTERFACE !\n");
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

	//TestNonDispatch();
	TestDispatch();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------