//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "FreeThreadingModelObjectFactory.h"
#include "FreeThreadingModelServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"FreeThreadingModelServer.dll";
const wchar_t													FriendlyName[]=L"FreeThreadingModelServer COM object";
const wchar_t													VerIndProgID[]=L"FreeThreadingModelObject";
const wchar_t													ProgID[]=L"FreeThreadingModelObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_FreeThreadingModelObject)
	{
		CFreeThreadingModelObjectFactory*						Factory=new CFreeThreadingModelObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_FreeThreadingModelObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_FreeThreadingModelObject,VerIndProgID,ProgID,LIBID_FreeThreadingModelServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------