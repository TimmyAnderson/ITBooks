//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "CompositionObjectFactory.h"
#include "CompositionServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"CompositionServer.dll";
const wchar_t													FriendlyName[]=L"CompositionServer COM object";
const wchar_t													VerIndProgID[]=L"CompositionObject";
const wchar_t													ProgID[]=L"CompositionObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_CompositionObject)
	{
		CCompositionObjectFactory*								Factory=new CCompositionObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_CompositionObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_CompositionObject,VerIndProgID,ProgID,LIBID_CompositionServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------