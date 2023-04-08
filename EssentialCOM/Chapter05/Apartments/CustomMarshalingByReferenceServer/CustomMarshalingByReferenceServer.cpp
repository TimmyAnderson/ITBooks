//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "CustomMarshalingByReferenceObjectFactory.h"
#include "CustomMarshalingByReferenceServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"CustomMarshalingByReferenceServer.dll";
const wchar_t													FriendlyName[]=L"CustomMarshalingByReferenceServer COM object";
const wchar_t													VerIndProgID[]=L"CustomMarshalingByReferenceObject";
const wchar_t													ProgID[]=L"CustomMarshalingByReferenceObject.1";
const wchar_t													ThreadingModel[]=L"Apartment";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_CustomMarshalingByReferenceObject)
	{
		CCustomMarshalingByReferenceObjectFactory*				Factory=new CCustomMarshalingByReferenceObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_CustomMarshalingByReferenceObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_CustomMarshalingByReferenceObject,VerIndProgID,ProgID,LIBID_CustomMarshalingByReferenceServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------