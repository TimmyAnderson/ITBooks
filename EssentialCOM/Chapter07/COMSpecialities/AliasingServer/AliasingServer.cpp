//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "AliasingObjectFactory.h"
#include "AliasingServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"AliasingServer.dll";
const wchar_t													FriendlyName[]=L"AliasingServer COM object";
const wchar_t													VerIndProgID[]=L"AliasingObject";
const wchar_t													ProgID[]=L"AliasingObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_AliasingObject)
	{
		CAliasingObjectFactory*									Factory=new CAliasingObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_AliasingObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_AliasingObject,VerIndProgID,ProgID,LIBID_AliasingServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------