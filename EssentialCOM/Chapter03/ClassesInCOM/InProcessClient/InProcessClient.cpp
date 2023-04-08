//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\InProcessServer\InProcessObject_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void SetName1(CSmartCOMPointer<IInProcessName> Interface)
{
	Interface->SetFirstName(L"Timmy");
	Interface->SetLastName(L"Anderson");
	Interface->SetAge(12);
}
//------------------------------------------------------------------------------------------------------
void GetName1(CSmartCOMPointer<IInProcessName> Interface)
{
	wchar_t														Buffer1[1024]={'\0'};
	wchar_t														Buffer2[1024]={'\0'};

	wchar_t*													FirstName=(wchar_t*) &Buffer1;
	wchar_t*													LastName=(wchar_t*) &Buffer2;
	int															Age=0;

	Interface->GetFirstName(_countof(Buffer1),(wchar_t**) &FirstName);
	Interface->GetLastName(_countof(Buffer2),(wchar_t**) &LastName);
	Interface->GetAge(&Age);

	wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName);
	wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName);
	wprintf_s(L"CLIENT - Age: [%d] !\n",Age);
}
//------------------------------------------------------------------------------------------------------
void SetName2(CSmartCOMPointer<IInProcessName> Interface)
{
	Interface->SetFirstName(L"Jenny");
	Interface->SetLastName(L"Thompson");
	Interface->SetAge(13);
}
//------------------------------------------------------------------------------------------------------
void GetName2(CSmartCOMPointer<IInProcessName> Interface)
{
	wchar_t														Buffer1[1024]={'\0'};
	wchar_t														Buffer2[1024]={'\0'};

	wchar_t*													FirstName=(wchar_t*) &Buffer1;
	wchar_t*													LastName=(wchar_t*) &Buffer2;
	int															Age=0;

	Interface->GetFirstName(_countof(Buffer1),(wchar_t**) &FirstName);
	Interface->GetLastName(_countof(Buffer2),(wchar_t**) &LastName);
	Interface->GetAge(&Age);

	wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName);
	wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName);
	wprintf_s(L"CLIENT - Age: [%d] !\n",Age);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM1(void)
{
	CLSID														ClassID;
	wchar_t														Buffer[1024];
	wchar_t*													ProgID=Buffer;

	if (SUCCEEDED(CLSIDFromProgID(L"InProcessObject.1",&ClassID)))
	{
		wprintf_s(L"CLSID [%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x] !\n",ClassID.Data1,ClassID.Data2,ClassID.Data3,ClassID.Data4[0],ClassID.Data4[1],ClassID.Data4[2],ClassID.Data4[3],ClassID.Data4[4],ClassID.Data4[5],ClassID.Data4[6],ClassID.Data4[7]);
	}
	else
	{
		wprintf_s(L"OPERATION FAILED !\n");
	}

	if (SUCCEEDED(ProgIDFromCLSID(CLSID_InProcessObject,&ProgID)))
	{
		wprintf_s(L"ProgID [%s] !\n",ProgID);
	}
	else
	{
		wprintf_s(L"OPERATION FAILED !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM2(void)
{
	CSmartCOMPointer<IInProcessName>							Interface1=NULL;
	CSmartCOMPointer<IInProcessName>							Interface2=NULL;

	// !!! COM OBJECT sa vytvaraju pomocou CoCreateInstance().
	HRESULT														HR1=CoCreateInstance(CLSID_InProcessObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IInProcessName),(void**) &Interface1);
	HRESULT														HR2=CoCreateInstance(CLSID_InProcessObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IInProcessName),(void**) &Interface2);

	if (SUCCEEDED(HR1) && SUCCEEDED(HR2))
	{
		SetName1(Interface1);
		SetName2(Interface2);

		// !!! Kedze OBE COM OBJECTS obsahuju INE HODNOTY je zrejme, ze sa NEJEDNA o SINGLETON COM OBJECT a pre kazdy dotaz na vytvorenie noveho COM OBJECT sa vytvori NOVA INSTANCIA COM OBJECT.
		GetName1(Interface1);
		GetName2(Interface2);
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}

	Interface1=NULL;
	Interface2=NULL;
}
//------------------------------------------------------------------------------------------------------
void TestCOM3(void)
{
	CSmartCOMPointer<IClassFactory>								ClassFactoryInterface=NULL;
	CSmartCOMPointer<IInProcessName>							Interface1=NULL;
	CSmartCOMPointer<IInProcessName>							Interface2=NULL;

	HRESULT														HR1=E_FAIL;
	HRESULT														HR2=E_FAIL;

	// !!! Najprv sa vytvori CLASS OBJECT (CLASS FACTORY).
	if (SUCCEEDED(CoGetClassObject(CLSID_InProcessObject,CLSCTX_INPROC,NULL,IID_IClassFactory,(void**) &ClassFactoryInterface)))
	{
		// !!! Teraz sa z CLASS OBJECT vytvoria COM OBJECTS
		HR1=ClassFactoryInterface->CreateInstance(NULL,__uuidof(IInProcessName),(void**) &Interface1);
		HR2=ClassFactoryInterface->CreateInstance(NULL,__uuidof(IInProcessName),(void**) &Interface2);

		ClassFactoryInterface=NULL;
	}

	if (SUCCEEDED(HR1) && SUCCEEDED(HR2))
	{
		SetName1(Interface1);
		SetName2(Interface2);

		// !!! Kedze OBE COM OBJECTS obsahuju INE HODNOTY je zrejme, ze sa NEJEDNA o SINGLETON COM OBJECT a pre kazdy dotaz na vytvorenie noveho COM OBJECT sa vytvori NOVA INSTANCIA COM OBJECT.
		GetName1(Interface1);
		GetName2(Interface2);
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}

	Interface1=NULL;
	Interface2=NULL;
}
//------------------------------------------------------------------------------------------------------
void TestCOM4(void)
{
	IInProcessName*												Interface1=NULL;
	IInProcessName*												Interface2=NULL;

	MULTI_QI													InterfaceArray1[1];
	MULTI_QI													InterfaceArray2[1];

	IID															InterfaceID1=__uuidof(IInProcessName);
	IID															InterfaceID2=__uuidof(IInProcessName);

	InterfaceArray1[0].hr=E_FAIL;
	InterfaceArray1[0].pIID=&InterfaceID1;
	// !!! MUSI byt NULL.
	InterfaceArray1[0].pItf=NULL;

	InterfaceArray2[0].hr=E_FAIL;
	InterfaceArray2[0].pIID=&InterfaceID2;
	// !!! MUSI byt NULL.
	InterfaceArray2[0].pItf=NULL;

	// !!! COM OBJECTS sa vytvaraju pomocou CoCreateInstanceEx().
	// !!!!! FUNCTION CoCreateInstanceEx() vytvara VZDY iba 1 COM OBJECT, ale moze vratia VIACERO ROZLICNYCH COM INTERFACES na TEN ISTY COM OBJECT.
	HRESULT														HR1=CoCreateInstanceEx(CLSID_InProcessObject,NULL,CLSCTX_INPROC_SERVER,NULL,_countof(InterfaceArray1),InterfaceArray1);
	HRESULT														HR2=CoCreateInstanceEx(CLSID_InProcessObject,NULL,CLSCTX_INPROC_SERVER,NULL,_countof(InterfaceArray2),InterfaceArray2);

	if (SUCCEEDED(HR1) && SUCCEEDED(HR2) && SUCCEEDED(InterfaceArray1[0].hr) && SUCCEEDED(InterfaceArray2[0].hr))
	{
		Interface1=(IInProcessName*) InterfaceArray1[0].pItf;
		Interface2=(IInProcessName*) InterfaceArray2[0].pItf;

		SetName1(Interface1);
		SetName2(Interface2);

		// !!! Kedze OBE COM OBJECTS obsahuju INE HODNOTY je zrejme, ze sa NEJEDNA o SINGLETON COM OBJECT a pre kazdy dotaz na vytvorenie noveho COM OBJECT sa vytvori NOVA INSTANCIA COM OBJECT.
		GetName1(Interface1);
		GetName2(Interface2);
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}

	if (InterfaceArray1[0].pItf!=NULL)
	{
		InterfaceArray1[0].pItf->Release();
		InterfaceArray1[0].pItf=NULL;
	}
	
	if (InterfaceArray2[0].pItf!=NULL)
	{
		InterfaceArray2[0].pItf->Release();
		InterfaceArray2[0].pItf=NULL;
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM5(void)
{
	CSmartCOMPointer<IMoniker>									Moniker=NULL;

	HRESULT														HR=E_FAIL;

	// !!! Priklad demonstruje vytvorenie COM OBJECT cez CLASS MONIKER, ktory je vytvoreny pomocou CreateClassMoniker().
	if (SUCCEEDED(CreateClassMoniker(CLSID_InProcessObject,&Moniker)))
	{
		CSmartCOMPointer<IBindCtx>								BindingContext=NULL;

		if (SUCCEEDED(CreateBindCtx(0,&BindingContext)))
		{
			CSmartCOMPointer<IClassFactory>						ClassFactory=NULL;

			// !!!!! Vytvara CLASS FACTORY a NIE instanciu samotneho COM OBJECT.
			if (SUCCEEDED(HR=Moniker->BindToObject(BindingContext.GetInterface(),NULL,__uuidof(IClassFactory),(void**) &ClassFactory)))
			{
				CSmartCOMPointer<IInProcessName>				Interface=NULL;

				// !!! Vytvori sa instancia COM OBJECT.
				if (SUCCEEDED(HR=ClassFactory->CreateInstance(NULL,__uuidof(IInProcessName),(void**) &Interface)))
				{
					SetName1(Interface);
					GetName1(Interface);

					Interface=NULL;
				}
				else
				{
					wprintf_s(L"Can't create COM OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				}

				ClassFactory=NULL;
			}

			BindingContext=NULL;
		}

		Moniker=NULL;
	}
	else
	{
		wprintf_s(L"Can't create MONIKER OBJECT !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM6(void)
{
	CSmartCOMPointer<IMoniker>									Moniker=NULL;

	HRESULT														HR=E_FAIL;

	CSmartCOMPointer<IBindCtx>									BindingContext=NULL;
	ULONG														Eaten=0;

	if (SUCCEEDED(CreateBindCtx(0,&BindingContext)))
	{
		// !!! Priklad demonstruje vytvorenie COM OBJECT cez CLASS MONIKER, ktory je vytvoreny pomocou MkParseDisplayName().
		if (SUCCEEDED(HR=MkParseDisplayName(BindingContext.GetInterface(),L"clsid:4E72CC54-3EC7-4240-9AAB-45285DB4B2FD:",&Eaten,&Moniker)))
		{
			CSmartCOMPointer<IClassFactory>						ClassFactory=NULL;

			// !!!!! Vytvara CLASS FACTORY a NIE instanciu samotneho COM OBJECT.
			if (SUCCEEDED(HR=Moniker->BindToObject(BindingContext.GetInterface(),NULL,__uuidof(IClassFactory),(void**) &ClassFactory)))
			{
				CSmartCOMPointer<IInProcessName>				Interface=NULL;

				// !!! Vytvori sa instancia COM OBJECT.
				if (SUCCEEDED(HR=ClassFactory->CreateInstance(NULL,__uuidof(IInProcessName),(void**) &Interface)))
				{
					SetName1(Interface);
					GetName1(Interface);

					Interface=NULL;
				}
				else
				{
					wprintf_s(L"Can't create COM OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				}

				ClassFactory=NULL;
			}

			Moniker=NULL;
		}
		else
		{
			wprintf_s(L"Can't create MONIKER OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
		}

		BindingContext=NULL;
	}
	else
	{
		wprintf_s(L"Can't create BINDING CONTEXT !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM7(void)
{
	HRESULT														HR=E_FAIL;

	CSmartCOMPointer<IClassFactory>								ClassFactory=NULL;

	// !!! Priklad demonstruje vytvorenie COM OBJECT cez CLASS MONIKER, ktory je vytvoreny pomocou CoGetObject().
	if (SUCCEEDED(HR=CoGetObject(L"clsid:4E72CC54-3EC7-4240-9AAB-45285DB4B2FD:",NULL,__uuidof(IClassFactory),(void**) &ClassFactory)))
	{
		CSmartCOMPointer<IInProcessName>						Interface=NULL;

		// !!! Vytvori sa instancia COM OBJECT.
		if (SUCCEEDED(HR=ClassFactory->CreateInstance(NULL,__uuidof(IInProcessName),(void**) &Interface)))
		{
			SetName1(Interface);
			GetName1(Interface);

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
		}

		ClassFactory=NULL;
	}
	else
	{
		wprintf_s(L"Can't create MONIKER OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
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
		//TestCOM5();
		//TestCOM6();
		TestCOM7();
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