//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "UnmanagedCOMObjectFactory.h"
#include "UnmanagedCOMServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"UnmanagedCOMServer.dll";
const wchar_t													FriendlyName[]=L"UnmanagedCOMServer COM object";
const wchar_t													VerIndProgID[]=L"UnmanagedCOMObject";
const wchar_t													ProgID[]=L"UnmanagedCOMObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_UnmanagedCOMObject)
	{
		CUnmanagedCOMObjectFactory*								Factory=new CUnmanagedCOMObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_UnmanagedCOMObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_UnmanagedCOMObject,VerIndProgID,ProgID,LIBID_UnmanagedCOMServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------