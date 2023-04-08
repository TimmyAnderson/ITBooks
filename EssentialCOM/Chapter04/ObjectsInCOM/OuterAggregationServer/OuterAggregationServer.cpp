//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "Helpers\Registry.h"
#include "OuterAggregationObjectFactory.h"
#include "OuterAggregationObject_h.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"OuterAggregationServer.dll";
const wchar_t													FriendlyName[]=L"OuterAggregationServer COM object";
const wchar_t													VerIndProgID[]=L"OuterAggregationObject";
const wchar_t													ProgID[]=L"OuterAggregationObject.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_OuterAggregationObject)
	{
		COuterAggregationObjectFactory*							Factory=new COuterAggregationObjectFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_OuterAggregationObject,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_OuterAggregationObject,VerIndProgID,ProgID,LIBID_OuterAggregationServerLib);

	return(HR);
}
//------------------------------------------------------------------------------------------------------