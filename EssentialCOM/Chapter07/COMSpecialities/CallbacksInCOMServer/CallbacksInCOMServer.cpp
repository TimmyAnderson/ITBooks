//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "MyServerObjectFactory.h"
#include "CallbacksInCOMServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"CallbacksInCOMServer.dll";
const wchar_t													FriendlyName[]=L"CallbacksInCOMServer COM object";
const wchar_t													VerIndProgID[]=L"MyServerObject";
const wchar_t													ProgID[]=L"MyServerObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_CallbacksInCOMObject)
	{
		CMyServerObjectFactory*									Factory=new CMyServerObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_CallbacksInCOMObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_CallbacksInCOMObject,VerIndProgID,ProgID,LIBID_CallbacksInCOMServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------