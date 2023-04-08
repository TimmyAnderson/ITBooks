//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyHostControl.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
CMyHostControl::CMyHostControl(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMyHostControl::~CMyHostControl(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyHostControl::GetHostManager(REFIID RIID, void** PointerToObject)
{
	CLock														Lock(MCS);

	wprintf_s(L"HOST MANAGER [%s] REQUESTED !\n",CHelpers::ConvertGuidToString(RIID).c_str());

	// !!! Kedze NEIMPLEMENTUJEM ZIADEN HOST MANAGER, tak pre VSETKY INTERFACES je vratena hodnota E_NOINTERFACE.
	return(E_NOINTERFACE);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyHostControl::SetAppDomainManager(DWORD AppDomainID, IUnknown* UnkAppDomainManager)
{
	CLock														Lock(MCS);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyHostControl::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostControl*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostControl*>(this);
		AddRef();
		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyHostControl::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyHostControl::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------