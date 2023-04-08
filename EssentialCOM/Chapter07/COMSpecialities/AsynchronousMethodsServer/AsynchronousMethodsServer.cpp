//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "AsynchronousMethodsObjectFactory.h"
#include "AsynchronousMethodsServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"AsynchronousMethodsServer.dll";
const wchar_t													FriendlyName[]=L"AsynchronousMethodsServer COM object";
const wchar_t													VerIndProgID[]=L"AsynchronousMethodsObject";
const wchar_t													ProgID[]=L"AsynchronousMethodsObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_AsynchronousMethodsObject)
	{
		CAsynchronousMethodsObjectFactory*						Factory=new CAsynchronousMethodsObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_AsynchronousMethodsObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_AsynchronousMethodsObject,VerIndProgID,ProgID,LIBID_AsynchronousMethodsServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------