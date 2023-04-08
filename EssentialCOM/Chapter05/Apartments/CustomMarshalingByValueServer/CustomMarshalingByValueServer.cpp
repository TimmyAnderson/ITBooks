//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "CustomMarshalingByValueObjectFactory.h"
#include "CustomMarshalingByValueServer_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"CustomMarshalingByValueServer.dll";
const wchar_t													FriendlyName[]=L"CustomMarshalingByValueServer COM object";
const wchar_t													VerIndProgID[]=L"CustomMarshalingByValueObject";
const wchar_t													ProgID[]=L"CustomMarshalingByValueObject.1";
const wchar_t													ThreadingModel[]=L"Apartment";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_CustomMarshalingByValueObject)
	{
		CCustomMarshalingByValueObjectFactory*					Factory=new CCustomMarshalingByValueObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_CustomMarshalingByValueObject,FriendlyName,VerIndProgID,ProgID,ThreadingModel);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_CustomMarshalingByValueObject,VerIndProgID,ProgID,LIBID_CustomMarshalingByValueServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------