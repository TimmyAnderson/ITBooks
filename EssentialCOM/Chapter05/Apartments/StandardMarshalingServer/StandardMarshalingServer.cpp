//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "StandardMarshalingObjectFactory.h"
#include "StandardMarshalingServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"StandardMarshalingServer.dll";
const wchar_t													FriendlyName[]=L"StandardMarshalingServer COM object";
const wchar_t													VerIndProgID[]=L"StandardMarshalingObject";
const wchar_t													ProgID[]=L"StandardMarshalingObject.1";
const wchar_t													ThreadingModel[]=L"Free";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_StandardMarshalingObject)
	{
		CStandardMarshalingObjectFactory*						Factory=new CStandardMarshalingObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_StandardMarshalingObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_StandardMarshalingObject,VerIndProgID,ProgID,LIBID_StandardMarshalingServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------