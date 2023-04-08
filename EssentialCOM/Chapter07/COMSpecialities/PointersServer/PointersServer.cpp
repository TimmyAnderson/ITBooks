//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "PointersObjectFactory.h"
#include "PointersServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"PointersServer.dll";
const wchar_t													FriendlyName[]=L"PointersServer COM object";
const wchar_t													VerIndProgID[]=L"PointersObject";
const wchar_t													ProgID[]=L"PointersObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_PointersObject)
	{
		CPointersObjectFactory*									Factory=new CPointersObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_PointersObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_PointersObject,VerIndProgID,ProgID,LIBID_PointersServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------