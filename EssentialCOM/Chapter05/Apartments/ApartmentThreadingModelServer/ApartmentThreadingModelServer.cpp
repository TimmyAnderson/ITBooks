//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "ApartmentThreadingModelObjectFactory.h"
#include "ApartmentThreadingModelServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"ApartmentThreadingModelServer.dll";
const wchar_t													FriendlyName[]=L"ApartmentThreadingModelServer COM object";
const wchar_t													VerIndProgID[]=L"ApartmentThreadingModelObject";
const wchar_t													ProgID[]=L"ApartmentThreadingModelObject.1";
const wchar_t													ThreadingModel[]=L"Apartment";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_ApartmentThreadingModelObject)
	{
		CApartmentThreadingModelObjectFactory*					Factory=new CApartmentThreadingModelObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_ApartmentThreadingModelObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_ApartmentThreadingModelObject,VerIndProgID,ProgID,LIBID_ApartmentThreadingModelServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------