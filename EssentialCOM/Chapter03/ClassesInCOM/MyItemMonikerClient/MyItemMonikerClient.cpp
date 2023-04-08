//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\MyItemMonikerServer\MyItemMonikerObject_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void GetName(CSmartCOMPointer<IMyItemMonikerName> Interface)
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
	HRESULT														HR=E_FAIL;
	CSmartCOMPointer<IMyItemMonikerName>						Interface1=NULL;
	CSmartCOMPointer<IMyItemMonikerName>						Interface2=NULL;

	// !!! Priklad demonstruje vytvorenie COM OBJECT cez CLASS MONIKER, ktory je vytvoreny pomocou CoGetObject().
	// !!! Vytvorim OBJECT s naplnenym menom [Timmy Anderson].
	if (SUCCEEDED(HR=CoGetObject(L"clsid:6F3F078E-D088-4F1E-BD62-C79F390E8AA6:!Timmy",NULL,__uuidof(IMyItemMonikerName),(void**) &Interface1)))
	{
		GetName(Interface1);

		Interface1=NULL;
	}
	else
	{
		wprintf_s(L"Can't create MONIKER OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
	}

	// !!! Vytvorim OBJECT s naplnenym menom [Jenny Thompson].
	if (SUCCEEDED(HR=CoGetObject(L"clsid:6F3F078E-D088-4F1E-BD62-C79F390E8AA6:!Jenny",NULL,__uuidof(IMyItemMonikerName),(void**) &Interface2)))
	{
		GetName(Interface2);

		Interface2=NULL;
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