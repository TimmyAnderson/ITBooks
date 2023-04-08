//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "MultiInterfaceCOMFactory.h"
#include "MultiInterfaceCOM_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"MultiInterfaceCOMServer.dll";
const wchar_t													FriendlyName[]=L"MultiInterfaceCOMServer COM object";
const wchar_t													VerIndProgID[]=L"MultiInterfaceCOM";
const wchar_t													ProgID[]=L"MultiInterfaceCOM.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_MultiInterfaceCOM)
	{
		CMultiInterfaceCOMFactory*								Factory=new CMultiInterfaceCOMFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_MultiInterfaceCOM,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_MultiInterfaceCOM,VerIndProgID,ProgID,LIBID_MultiInterfaceCOMServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------