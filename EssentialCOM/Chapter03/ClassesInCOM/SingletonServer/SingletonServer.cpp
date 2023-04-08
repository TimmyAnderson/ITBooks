//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "SingletonObjectFactory.h"
#include "SingletonObject_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"SingletonServer.dll";
const wchar_t													FriendlyName[]=L"SingletonServer COM object";
const wchar_t													VerIndProgID[]=L"SingletonObject";
const wchar_t													ProgID[]=L"SingletonObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_SingletonObject)
	{
		CSingletonObjectFactory*								Factory=new CSingletonObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_SingletonObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_SingletonObject,VerIndProgID,ProgID,LIBID_SingletonServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------