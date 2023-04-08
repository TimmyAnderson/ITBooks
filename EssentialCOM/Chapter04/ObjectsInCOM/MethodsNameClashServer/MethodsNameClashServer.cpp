//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "MethodsNameClashObjectFactory.h"
#include "MethodsNameClashServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"MethodsNameClashServer.dll";
const wchar_t													FriendlyName[]=L"MethodsNameClashServer COM object";
const wchar_t													VerIndProgID[]=L"MethodsNameClashObject";
const wchar_t													ProgID[]=L"MethodsNameClashObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_MethodsNameClashObject)
	{
		CMethodsNameClashObjectFactory*							Factory=new CMethodsNameClashObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_MethodsNameClashObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_MethodsNameClashObject,VerIndProgID,ProgID,LIBID_MethodsNameClashServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------