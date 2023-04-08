//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\OutOfProcessWithMarshallingServer\OutOfProcessWithMarshallingServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void PrintName1(CSmartCOMPointer<IName> Interface)
{
	wchar_t														Buffer1[1024]={'\0'};
	wchar_t														Buffer2[1024]={'\0'};

	wchar_t*													FirstName=(wchar_t*) Buffer1;
	wchar_t*													LastName=(wchar_t*) Buffer2;
	int															Age=0;

	Interface->SetFirstName(L"Timmy");
	Interface->SetLastName(L"Anderson");
	Interface->SetAge(12);

	Interface->GetFirstName(_countof(Buffer1),FirstName);
	Interface->GetLastName(_countof(Buffer2),LastName);
	Interface->GetAge(&Age);

	wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName);
	wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName);
	wprintf_s(L"CLIENT - Age: [%d] !\n",Age);
}
//------------------------------------------------------------------------------------------------------
void PrintName2(CSmartCOMPointer<IName> Interface)
{
	wchar_t														Buffer1[1024]={'\0'};
	wchar_t														Buffer2[1024]={'\0'};

	wchar_t*													FirstName=(wchar_t*) Buffer1;
	wchar_t*													LastName=(wchar_t*) Buffer2;
	int															Age=0;

	Interface->SetFirstName(L"Jenny");
	Interface->SetLastName(L"Thompson");
	Interface->SetAge(13);

	Interface->GetFirstName(_countof(Buffer1),FirstName);
	Interface->GetLastName(_countof(Buffer2),LastName);
	Interface->GetAge(&Age);

	wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName);
	wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName);
	wprintf_s(L"CLIENT - Age: [%d] !\n",Age);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void Test1(void)
{
	CSmartCOMPointer<IName>										Interface=NULL;
	HRESULT														HR=CoCreateInstance(CLSID_OutOfProcessWithMarshallingObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IName),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		PrintName1(Interface);

		Interface=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void Test2(void)
{
	CSmartCOMPointer<IName>										Interface1=NULL;
	CSmartCOMPointer<IName>										Interface2=NULL;
	HRESULT														HR1=CoCreateInstance(CLSID_OutOfProcessWithMarshallingObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IName),(void**) &Interface1);
	HRESULT														HR2=CoCreateInstance(CLSID_OutOfProcessWithMarshallingObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IName),(void**) &Interface2);

	if (SUCCEEDED(HR1) && SUCCEEDED(HR2))
	{
		PrintName1(Interface1);
		PrintName2(Interface2);

		Interface1=NULL;
		Interface2=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void Test3(void)
{
	CSmartCOMPointer<IName>										Interface1=NULL;
	CSmartCOMPointer<IName>										Interface2=NULL;
	HRESULT														HR1=CoCreateInstance(CLSID_OutOfProcessWithMarshallingObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IName),(void**) &Interface1);
	HRESULT														HR2=CoCreateInstance(CLSID_OutOfProcessWithMarshallingObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IName),(void**) &Interface2);

	if (SUCCEEDED(HR1) && SUCCEEDED(HR2))
	{
		PrintName1(Interface1);
		PrintName2(Interface2);

		wprintf_s(L"PROCESS will be TERMINATED !\n");
		_getch();

		// !!! Teraz je treba na skusku NASILNE UKONCIT CLIENT.
		// !!!!! Kedze sa REFERENCES na COM OBJECTS NEUZATVORILI, tak OUT-OF-PROCESS SERVER bude bezat DALEJ, az kym nevyprsi 3 KRAT COM PING. Ten standardne trva 2 minuty, takze OUT-OF-PROCESS SERVER sa uzavrie do 6 minut.
		terminate();

		Interface1=NULL;
		Interface2=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void Test4(void)
{
	// ZMENI sa DEFAULT COM SECURITY.
	// !!! Zapne sa KRYPTOVANIE a DELEGATION.
	HRESULT														HR=CoInitializeSecurity(NULL,-1,NULL,NULL,RPC_C_AUTHN_LEVEL_PKT_PRIVACY,RPC_C_IMP_LEVEL_DELEGATE,NULL,EOAC_NONE,NULL);

	if (SUCCEEDED(HR))
	{
		CSmartCOMPointer<IName>									Interface1=NULL;
		CSmartCOMPointer<IName>									Interface2=NULL;
		HRESULT													HR1=CoCreateInstance(CLSID_OutOfProcessWithMarshallingObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IName),(void**) &Interface1);
		HRESULT													HR2=CoCreateInstance(CLSID_OutOfProcessWithMarshallingObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IName),(void**) &Interface2);

		if (SUCCEEDED(HR1) && SUCCEEDED(HR2))
		{
			PrintName1(Interface1);
			PrintName2(Interface2);

			Interface1=NULL;
			Interface2=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECTS !\n");
		}
	}
	else
	{
		wprintf_s(L"COM SECURITY INITIALIZATION FAILED !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void Test5(void)
{
	// ZMENI sa DEFAULT COM SECURITY.
	// !!! Zapne sa KRYPTOVANIE a DELEGATION.
	HRESULT														HR=CoInitializeSecurity(NULL,-1,NULL,NULL,RPC_C_AUTHN_LEVEL_PKT_PRIVACY,RPC_C_IMP_LEVEL_DELEGATE,NULL,EOAC_NONE,NULL);

	if (SUCCEEDED(HR))
	{
		CSmartCOMPointer<IName>									Interface=NULL;

		if (SUCCEEDED(HR=CoCreateInstance(CLSID_OutOfProcessWithMarshallingObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IName),(void**) &Interface)))
		{
			CSmartCOMPointer<IClientSecurity>					ClientSecurity=NULL;

			// !!!!! Kedze PROXY OBJECT VZDY implementuje IClientSecurity, je mozne ziskat POINTER na tento COM INTERFACE.
			if (SUCCEEDED(HR=Interface->QueryInterface(__uuidof(IClientSecurity),(void**) &ClientSecurity)))
			{
				DWORD											AuthnSvc;
				DWORD											AuthzSvc;
				OLECHAR*										ServerPrincName=NULL;
				DWORD											AuthnLevel;
				DWORD											ImpLevel;
				DWORD											Capabilites;

				if (SUCCEEDED(HR=ClientSecurity->QueryBlanket(Interface.GetInterface(),&AuthnSvc,&AuthzSvc,&ServerPrincName,&AuthnLevel,&ImpLevel,NULL,&Capabilites)))
				{
					PrintName1(Interface);

					// !!! Hodnoty su uvedene v dokumentacii.
					wprintf_s(L"\tAuthnSvc: [%d] !\n",AuthnSvc);
					wprintf_s(L"\tAuthzSvc: [%d] !\n",AuthzSvc);
					wprintf_s(L"\tServerPrincName: [%s] !\n",ServerPrincName);
					wprintf_s(L"\tAuthnLevel: [%d] !\n",AuthnLevel);
					wprintf_s(L"\tImpLevel: [%d] !\n",ImpLevel);
					wprintf_s(L"\tCapabilites: [%d] !\n",Capabilites);

					if (ServerPrincName!=NULL)
					{
						CoTaskMemFree(ServerPrincName);
						ServerPrincName=NULL;
					}
				}
				else
				{
					wprintf_s(L"Can't QUERY BLANKET !\n");
				}

				ClientSecurity=NULL;
			}
			else
			{
				wprintf_s(L"Can't get IClientSecurity COM INTERFACE !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	else
	{
		wprintf_s(L"COM SECURITY INITIALIZATION FAILED !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void Test6(void)
{
	// ZMENI sa DEFAULT COM SECURITY.
	// !!! Zapne sa KRYPTOVANIE a DELEGATION.
	HRESULT														HR=CoInitializeSecurity(NULL,-1,NULL,NULL,RPC_C_AUTHN_LEVEL_PKT_PRIVACY,RPC_C_IMP_LEVEL_DELEGATE,NULL,EOAC_NONE,NULL);

	if (SUCCEEDED(HR))
	{
		CSmartCOMPointer<IName>									Interface=NULL;

		if (SUCCEEDED(HR=CoCreateInstance(CLSID_OutOfProcessWithMarshallingObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IName),(void**) &Interface)))
		{
			DWORD												AuthnSvc;
			DWORD												AuthzSvc;
			OLECHAR*											ServerPrincName=NULL;
			DWORD												AuthnLevel;
			DWORD												ImpLevel;
			DWORD												Capabilites;

			// !!! Volam HELPER FUNCTION CoQueryProxyBlanket().
			if (SUCCEEDED(HR=CoQueryProxyBlanket(Interface.GetInterface(),&AuthnSvc,&AuthzSvc,&ServerPrincName,&AuthnLevel,&ImpLevel,NULL,&Capabilites)))
			{
				PrintName1(Interface);

				// !!! Hodnoty su uvedene v dokumentacii.
				wprintf_s(L"\tAuthnSvc: [%d] !\n",AuthnSvc);
				wprintf_s(L"\tAuthzSvc: [%d] !\n",AuthzSvc);
				wprintf_s(L"\tServerPrincName: [%s] !\n",ServerPrincName);
				wprintf_s(L"\tAuthnLevel: [%d] !\n",AuthnLevel);
				wprintf_s(L"\tImpLevel: [%d] !\n",ImpLevel);
				wprintf_s(L"\tCapabilites: [%d] !\n",Capabilites);

				if (ServerPrincName!=NULL)
				{
					CoTaskMemFree(ServerPrincName);
					ServerPrincName=NULL;
				}
			}
			else
			{
				wprintf_s(L"Can't QUERY BLANKET !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	else
	{
		wprintf_s(L"COM SECURITY INITIALIZATION FAILED !\n");
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
		//Test1();
		//Test2();
		//Test3();
		//Test4();
		Test5();
		//Test6();
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