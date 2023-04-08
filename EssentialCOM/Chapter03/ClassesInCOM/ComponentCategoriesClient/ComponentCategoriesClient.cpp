//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <string>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include <ComCat.h>
#include "..\ComponentCategoriesServer\ComponentCategoriesObject_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
static const GUID												CATID_MyImplementedCategory={0xf1a92594, 0x5fc8, 0x4843, { 0xbe, 0xca, 0xdf, 0x1, 0xe6, 0xee, 0x8d, 0x4d}};
static const GUID												CATID_MyRequiredCategory={0x6ff7169a, 0x7851, 0x40a2, { 0xa0, 0x65, 0x75, 0x5f, 0x67, 0x46, 0x8e, 0xa8}};
//------------------------------------------------------------------------------------------------------
void SetName(CSmartCOMPointer<IComponentCategoriesName> Interface)
{
	Interface->SetFirstName(L"Timmy");
	Interface->SetLastName(L"Anderson");
	Interface->SetAge(12);
}
//------------------------------------------------------------------------------------------------------
void GetName(CSmartCOMPointer<IComponentCategoriesName> Interface)
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
	CSmartCOMPointer<IComponentCategoriesName>					Interface=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_ComponentCategoriesObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IComponentCategoriesName),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		SetName(Interface);
		GetName(Interface);
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
	CSmartCOMPointer<ICatInformation>							CatInformation;

	// !!! Vytvori sa CATEGORY MANAGER.
	if (SUCCEEDED(CoCreateInstance(CLSID_StdComponentCategoriesMgr,NULL,CLSCTX_INPROC,IID_ICatInformation,(void**) &CatInformation)))
	{
		CSmartCOMPointer<IEnumGUID>								ImplementedCategoriesEnum;
		CSmartCOMPointer<IEnumGUID>								RequiredCategoriesEnum;

		if (SUCCEEDED(CatInformation->EnumImplCategoriesOfClass(CLSID_ComponentCategoriesObject,&ImplementedCategoriesEnum)))
		{
			HRESULT												HR;

			do
			{
				ULONG											Retrieved=0;
				CATID											CategoryID;

				if ((HR=ImplementedCategoriesEnum->Next(1,&CategoryID,&Retrieved))==S_OK)
				{
					wstring										String=CHelpers::ConvertGuidToString(CategoryID);

					wprintf_s(L"IMPLEMENTED CATEGORY [%s] !\n",String.c_str());
				}
			}
			while(HR==S_OK);

			ImplementedCategoriesEnum=NULL;
		}

		if (SUCCEEDED(CatInformation->EnumReqCategoriesOfClass(CLSID_ComponentCategoriesObject,&RequiredCategoriesEnum)))
		{
			HRESULT												HR;

			do
			{
				ULONG											Retrieved=0;
				CATID											CategoryID;

				if ((HR=RequiredCategoriesEnum->Next(1,&CategoryID,&Retrieved))==S_OK)
				{
					wstring										String=CHelpers::ConvertGuidToString(CategoryID);

					wprintf_s(L"REQUIRED CATEGORY [%s] !\n",String.c_str());
				}
			}
			while(HR==S_OK);

			RequiredCategoriesEnum=NULL;
		}

		CatInformation=NULL;
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