//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "ConnectionPointsFactory.h"
#include "ConnectionPointsServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"ConnectionPointsServer.dll";
const wchar_t													FriendlyName[]=L"ConnectionPointsServer COM object";
const wchar_t													VerIndProgID[]=L"ConnectionPointsObject";
const wchar_t													ProgID[]=L"ConnectionPointsObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_ConnectionPointsObject)
	{
		CConnectionPointsFactory*								Factory=new CConnectionPointsFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_ConnectionPointsObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_ConnectionPointsObject,VerIndProgID,ProgID,LIBID_ConnectionPointsServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------