//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\OutOfProcessServer\OutOfProcessObject_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void SetName1(CSmartCOMPointer<IOutOfProcessName> Interface)
{
	Interface->SetFirstName(bstr_t(L"Timmy"));
	Interface->SetLastName(bstr_t(L"Anderson"));
	Interface->SetAge(12);
}
//------------------------------------------------------------------------------------------------------
void GetName1(CSmartCOMPointer<IOutOfProcessName> Interface)
{
	bstr_t														FirstName;
	bstr_t														LastName;
	int															Age=0;

	Interface->GetFirstName(FirstName.GetAddress());
	Interface->GetLastName(LastName.GetAddress());
	Interface->GetAge(&Age);

	wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName.operator const wchar_t *());
	wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName.operator const wchar_t *());
	wprintf_s(L"CLIENT - Age: [%d] !\n",Age);
}
//------------------------------------------------------------------------------------------------------
void SetName2(CSmartCOMPointer<IOutOfProcessName> Interface)
{
	Interface->SetFirstName(bstr_t(L"Jenny"));
	Interface->SetLastName(bstr_t(L"Thompson"));
	Interface->SetAge(13);
}
//------------------------------------------------------------------------------------------------------
void GetName2(CSmartCOMPointer<IOutOfProcessName> Interface)
{
	bstr_t														FirstName;
	bstr_t														LastName;
	int															Age=0;

	Interface->GetFirstName(FirstName.GetAddress());
	Interface->GetLastName(LastName.GetAddress());
	Interface->GetAge(&Age);

	wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName.operator const wchar_t *());
	wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName.operator const wchar_t *());
	wprintf_s(L"CLIENT - Age: [%d] !\n",Age);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM1(void)
{
	CSmartCOMPointer<IOutOfProcessName>							Interface=NULL;

	// !!! Vytvorim instancie ako OUT-OF-PROCESS SERVER.
	HRESULT														HR=CoCreateInstance(CLSID_OutOfProcessObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IOutOfProcessName),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		SetName1(Interface);

		GetName1(Interface);
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT !\n");
	}

	Interface=NULL;
}
//------------------------------------------------------------------------------------------------------
void TestCOM2(void)
{
	CSmartCOMPointer<IOutOfProcessName>							Interface1=NULL;
	CSmartCOMPointer<IOutOfProcessName>							Interface2=NULL;

	// !!! Vytvorim instancie ako OUT-OF-PROCESS SERVER.
	HRESULT														HR1=CoCreateInstance(CLSID_OutOfProcessObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IOutOfProcessName),(void**) &Interface1);
	HRESULT														HR2=CoCreateInstance(CLSID_OutOfProcessObject,NULL,CLSCTX_LOCAL_SERVER,__uuidof(IOutOfProcessName),(void**) &Interface2);

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
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		//TestCOM1();
		TestCOM2();
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