//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "CustomDispatchObjectFactory.h"
#include "CustomDispatchServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"CustomDispatchServer.dll";
const wchar_t													FriendlyName[]=L"CustomDispatchServer COM object";
const wchar_t													VerIndProgID[]=L"CustomDispatchObject";
const wchar_t													ProgID[]=L"CustomDispatchObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_CustomDispatchObject)
	{
		CCustomDispatchObjectFactory*							Factory=new CCustomDispatchObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_CustomDispatchObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_CustomDispatchObject,VerIndProgID,ProgID,LIBID_CustomDispatchServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------