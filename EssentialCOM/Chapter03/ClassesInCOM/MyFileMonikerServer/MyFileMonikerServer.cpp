//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "MyFileMonikerObjectFactory.h"
#include "MyFileMonikerObject_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"MyFileMonikerServer.dll";
const wchar_t													FriendlyName[]=L"MyFileMonikerServer COM object";
const wchar_t													VerIndProgID[]=L"MyFileMonikerObject";
const wchar_t													ProgID[]=L"MyFileMonikerObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_MyFileMonikerObject)
	{
		CMyFileMonikerObjectFactory*							Factory=new CMyFileMonikerObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_MyFileMonikerObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_MyFileMonikerObject,VerIndProgID,ProgID,LIBID_MyFileMonikerServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------