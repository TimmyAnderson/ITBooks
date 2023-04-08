//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "ObjectUsedByFTMObjectFactory.h"
#include "ObjectUsedByFTMServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"ObjectUsedByFTMServer.dll";
const wchar_t													FriendlyName[]=L"ObjectUsedByFTMServer COM object";
const wchar_t													VerIndProgID[]=L"ObjectUsedByFTMObject";
const wchar_t													ProgID[]=L"ObjectUsedByFTMObject.1";
const wchar_t													ThreadingModel[]=L"Apartment";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_ObjectUsedByFTMObject)
	{
		CObjectUsedByFTMObjectFactory*							Factory=new CObjectUsedByFTMObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_ObjectUsedByFTMObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_ObjectUsedByFTMObject,VerIndProgID,ProgID,LIBID_ObjectUsedByFTMServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------