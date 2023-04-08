//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "InProcessObjectFactory.h"
#include "InProcessObject_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"InProcessServer.dll";
const wchar_t													FriendlyName[]=L"InProcessServer COM object";
const wchar_t													VerIndProgID[]=L"InProcessObject";
const wchar_t													ProgID[]=L"InProcessObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_InProcessObject)
	{
		CInProcessObjectFactory*								Factory=new CInProcessObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_InProcessObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_InProcessObject,VerIndProgID,ProgID,LIBID_InProcessServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------