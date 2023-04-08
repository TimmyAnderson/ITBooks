//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "BothThreadingModelObjectFactory.h"
#include "BothThreadingModelServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"BothThreadingModelServer.dll";
const wchar_t													FriendlyName[]=L"BothThreadingModelServer COM object";
const wchar_t													VerIndProgID[]=L"BothThreadingModelObject";
const wchar_t													ProgID[]=L"BothThreadingModelObject.1";
const wchar_t													ThreadingModel[]=L"Both";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_BothThreadingModelObject)
	{
		CBothThreadingModelObjectFactory*						Factory=new CBothThreadingModelObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_BothThreadingModelObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_BothThreadingModelObject,VerIndProgID,ProgID,LIBID_BothThreadingModelServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------