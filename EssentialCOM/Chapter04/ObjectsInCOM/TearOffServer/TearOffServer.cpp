//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "TearOffObjectFactory.h"
#include "TearOffServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"TearOffServer.dll";
const wchar_t													FriendlyName[]=L"TearOffServer COM object";
const wchar_t													VerIndProgID[]=L"TearOffObject";
const wchar_t													ProgID[]=L"TearOffObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_TearOffObject)
	{
		CTearOffObjectFactory*									Factory=new CTearOffObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_TearOffObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_TearOffObject,VerIndProgID,ProgID,LIBID_TearOffServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------