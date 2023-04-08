//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "InnerAggregationObjectFactory.h"
#include "InnerAggregationObject_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"InnerAggregationServer.dll";
const wchar_t													FriendlyName[]=L"InnerAggregationServer COM object";
const wchar_t													VerIndProgID[]=L"InnerAggregationObject";
const wchar_t													ProgID[]=L"InnerAggregationObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_InnerAggregationObject)
	{
		CInnerAggregationObjectFactory*							Factory=new CInnerAggregationObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_InnerAggregationObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_InnerAggregationObject,VerIndProgID,ProgID,LIBID_InnerAggregationServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------