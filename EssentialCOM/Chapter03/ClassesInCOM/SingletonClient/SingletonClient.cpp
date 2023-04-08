//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\SingletonServer\SingletonObject_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void SetName1(CSmartCOMPointer<ISingletonName> Interface)
{
	Interface->SetFirstName(L"Timmy");
	Interface->SetLastName(L"Anderson");
	Interface->SetAge(12);
}
//------------------------------------------------------------------------------------------------------
void GetName1(CSmartCOMPointer<ISingletonName> Interface)
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
void SetName2(CSmartCOMPointer<ISingletonName> Interface)
{
	Interface->SetFirstName(L"Jenny");
	Interface->SetLastName(L"Thompson");
	Interface->SetAge(13);
}
//------------------------------------------------------------------------------------------------------
void GetName2(CSmartCOMPointer<ISingletonName> Interface)
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
void TestCOM(void)
{
	CSmartCOMPointer<ISingletonName>							Interface1=NULL;
	CSmartCOMPointer<ISingletonName>							Interface2=NULL;

	HRESULT														HR1=CoCreateInstance(CLSID_SingletonObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ISingletonName),(void**) &Interface1);
	HRESULT														HR2=CoCreateInstance(CLSID_SingletonObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ISingletonName),(void**) &Interface2);

	if (SUCCEEDED(HR1) && SUCCEEDED(HR2))
	{
		SetName1(Interface1);
		SetName2(Interface2);

		// !!! Kedze COM OBJECT je SINGLETON, obe FUNCTIONS vypisu TO ISTE, aj ked COM OBJECTS boli nastavene na INE HODNOTY.
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