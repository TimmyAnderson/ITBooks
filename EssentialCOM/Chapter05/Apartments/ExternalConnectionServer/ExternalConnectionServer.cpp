//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "ExternalConnectionObjectFactory.h"
#include "ExternalConnectionServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"ExternalConnectionServer.dll";
const wchar_t													FriendlyName[]=L"ExternalConnectionServer COM object";
const wchar_t													VerIndProgID[]=L"ExternalConnectionObject";
const wchar_t													ProgID[]=L"ExternalConnectionObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_ExternalConnectionObject)
	{
		CExternalConnectionObjectFactory*						Factory=new CExternalConnectionObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_ExternalConnectionObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_ExternalConnectionObject,VerIndProgID,ProgID,LIBID_ExternalConnectionServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------