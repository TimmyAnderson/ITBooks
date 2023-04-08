//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "MyItemMonikerObjectFactory.h"
#include "MyItemMonikerObject_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"MyItemMonikerServer.dll";
const wchar_t													FriendlyName[]=L"MyItemMonikerServer COM object";
const wchar_t													VerIndProgID[]=L"MyItemMonikerObject";
const wchar_t													ProgID[]=L"MyItemMonikerObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_MyItemMonikerObject)
	{
		CMyItemMonikerObjectFactory*							Factory=new CMyItemMonikerObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_MyItemMonikerObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_MyItemMonikerObject,VerIndProgID,ProgID,LIBID_MyItemMonikerServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------