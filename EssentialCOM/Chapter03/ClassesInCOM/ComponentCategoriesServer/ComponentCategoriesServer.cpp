//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <ComCat.h>
#include "Helpers\Registry.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "ComponentCategoriesObjectFactory.h"
#include "ComponentCategoriesObject_h.h"
//------------------------------------------------------------------------------------------------------
static const GUID												CATID_MyImplementedCategory={0xf1a92594, 0x5fc8, 0x4843, { 0xbe, 0xca, 0xdf, 0x1, 0xe6, 0xee, 0x8d, 0x4d}};
static const GUID												CATID_MyRequiredCategory={0x6ff7169a, 0x7851, 0x40a2, { 0xa0, 0x65, 0x75, 0x5f, 0x67, 0x46, 0x8e, 0xa8}};
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"ComponentCategoriesServer.dll";
const wchar_t													FriendlyName[]=L"ComponentCategoriesServer COM object";
const wchar_t													VerIndProgID[]=L"ComponentCategoriesObject";
const wchar_t													ProgID[]=L"ComponentCategoriesObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_ComponentCategoriesObject)
	{
		CComponentCategoriesObjectFactory*						Factory=new CComponentCategoriesObjectFactory();
		HRESULT													HR;

		HR=Factory->QueryInterface(RIID,PPObject);

		if (SUCCEEDED(HR))
		{
			return(S_OK);
		}
		else
		{
			delete(Factory);
			Factory=NULL;

			*PPObject=NULL;
			return(E_NOINTERFACE);
		}
	}
	else
	{
		*PPObject=NULL;
		return(CLASS_E_CLASSNOTAVAILABLE);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllRegisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=RegisterServer(ModuleName,CLSID_ComponentCategoriesObject,FriendlyName,VerIndProgID,ProgID,NULL);

	if (SUCCEEDED(HR))
	{
		CSmartCOMPointer<ICatRegister>							CatRegister;

		// !!! Vytvori sa CATEGORY MANAGER.
		if (SUCCEEDED(HR=CoCreateInstance(CLSID_StdComponentCategoriesMgr,NULL,CLSCTX_INPROC,IID_ICatRegister,(void**) &CatRegister)))
		{
			CATEGORYINFO										CategoryInfo[2];

			CategoryInfo[0].catid=CATID_MyImplementedCategory;
			CategoryInfo[1].catid=CATID_MyRequiredCategory;

			// USA.
			CategoryInfo[0].lcid=0x409;
			CategoryInfo[1].lcid=0x409;

			wcscpy_s(CategoryInfo[0].szDescription,L"My IMPLEMENTED CATEGORY !");
			wcscpy_s(CategoryInfo[1].szDescription,L"My REQUIRED CATEGORY !");

			// !!! Zaregistruju sa CATEGORIES.
			if (SUCCEEDED(HR=CatRegister->RegisterCategories(_countof(CategoryInfo),CategoryInfo)))
			{
				CATID											ImplementedCategories[]={CATID_MyImplementedCategory};
				CATID											RequiredCategories[]={CATID_MyRequiredCategory};
				
				if (SUCCEEDED(HR=CatRegister->RegisterClassImplCategories(CLSID_ComponentCategoriesObject,_countof(ImplementedCategories),ImplementedCategories)))
				{
					HR=CatRegister->RegisterClassReqCategories(CLSID_ComponentCategoriesObject,_countof(RequiredCategories),RequiredCategories);
				}
			}

			CatRegister=NULL;
		}
	}

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	CSmartCOMPointer<ICatRegister>								CatRegister;

	// !!! Vytvori sa CATEGORY MANAGER.
	if (SUCCEEDED(CoCreateInstance(CLSID_StdComponentCategoriesMgr,NULL,CLSCTX_INPROC,IID_ICatRegister,(void**) &CatRegister)))
	{
		CATID													CategoryIDs[2];

		CategoryIDs[0]=CATID_MyImplementedCategory;
		CategoryIDs[1]=CATID_MyRequiredCategory;

		// !!! Odregistruju sa CATEGORIES.
		CatRegister->UnRegisterCategories(_countof(CategoryIDs),CategoryIDs);

		CATID													ImplementedCategories[]={CATID_MyImplementedCategory};
		CATID													RequiredCategories[]={CATID_MyRequiredCategory};

		CatRegister->UnRegisterClassImplCategories(CLSID_ComponentCategoriesObject,_countof(ImplementedCategories),ImplementedCategories);
		CatRegister->UnRegisterClassReqCategories(CLSID_ComponentCategoriesObject,_countof(RequiredCategories),RequiredCategories);

		CatRegister=NULL;
	}

	HRESULT														HR=UnregisterServer(CLSID_ComponentCategoriesObject,VerIndProgID,ProgID,LIBID_ComponentCategoriesServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------