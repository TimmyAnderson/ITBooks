//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "MySimpleCOMFactory.h"
#include "Registry.h"
//------------------------------------------------------------------------------------------------------
const CLSID CLSID_SimpleCOM={0xfd021f4d, 0x5841, 0x4d44, 0x96, 0xe3, 0xe9, 0xc4, 0x1d, 0xa5, 0x47, 0xf};
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"SimpleCOMServer.dll";
const wchar_t													FriendlyName[]=L"SimpleCOMServer COM object";
const wchar_t													VerIndProgID[]=L"SimpleCOM";
const wchar_t													ProgID[]=L"SimpleCOM.1";
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	if (CLSID==CLSID_SimpleCOM)
	{
		CMySimpleCOMFactory*									Factory=new CMySimpleCOMFactory();
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
	HRESULT														HR=RegisterServer(ModuleName,CLSID_SimpleCOM,FriendlyName,VerIndProgID,ProgID,NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE DllUnregisterServer(REFCLSID CLSID, REFIID RIID, void** PPObject)
{
	HRESULT														HR=UnregisterServer(CLSID_SimpleCOM,VerIndProgID,ProgID);

	return(HR);
}
//------------------------------------------------------------------------------------------------------