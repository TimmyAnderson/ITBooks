//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "QITestObjectFactory.h"
#include "QITestServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"QITestServer.dll";
const wchar_t													FriendlyName[]=L"QITestServer COM object";
const wchar_t													VerIndProgID[]=L"QITestObject";
const wchar_t													ProgID[]=L"QITestObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_QITestObject)
	{
		CQITestObjectFactory*									Factory=new CQITestObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_QITestObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_QITestObject,VerIndProgID,ProgID,LIBID_QITestServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------