//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CustomDispatchObject.h"
#include "Helpers\Lock.h"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
CCustomDispatchObject::CCustomDispatchObject(void)
	: MReferenceCounter(0), MTypeInfo(NULL), MValue()
{
	CSmartCOMPointer<ITypeLib>									TypeLibrary;
	HRESULT														HR;

	// !!! Nacitam TYPE LIBRARY.
	if (SUCCEEDED(HR=LoadRegTypeLib(LIBID_CustomDispatchServerLib,1,0,0,&TypeLibrary)))
	{
		// !!! Ziskam POINTER na TYPE INFO.
		if (FAILED(TypeLibrary->GetTypeInfoOfGuid(IID_ICustomDispatchTest,&MTypeInfo)))
		{
			wprintf_s(L"Can't GET TYPE INFO !\n");
		}

		TypeLibrary=NULL;
	}
	else
	{
		wprintf_s(L"Can't LOAD TYPE LIBRARY [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
	}
}
//------------------------------------------------------------------------------------------------------
CCustomDispatchObject::~CCustomDispatchObject(void)
{
	// !!! Uvolni TYPE INFO.
	MTypeInfo=NULL;

	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomDispatchObject::SetValue(BSTR Value)
{
	CLock														Lock(MCS);

	MValue=Value;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomDispatchObject::GetValue(BSTR* Value)
{
	CLock														Lock(MCS);

	*Value=MValue.copy();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomDispatchObject::GetTypeInfoCount(__RPC__out UINT* TypeInfo)
{
	CLock														Lock(MCS);

	*TypeInfo=1;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomDispatchObject::GetTypeInfo(UINT TInfo, LCID LCID, __RPC__deref_out_opt ITypeInfo** TypeInfo)
{
	CLock														Lock(MCS);

	MTypeInfo->AddRef();
	*TypeInfo=MTypeInfo.GetInterface();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomDispatchObject::GetIDsOfNames(__RPC__in REFIID RIID, __RPC__in_ecount_full(CountNames) LPOLESTR* Names, __RPC__in_range(0,16384) UINT CountNames, LCID LCID, __RPC__out_ecount_full(CountNames) DISPID* DispID)
{
	CLock														Lock(MCS);
	HRESULT														HR;

	// !!! Vyuzije sa METHOD ITypeInfo.
	HR=MTypeInfo->GetIDsOfNames(Names,CountNames,DispID);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomDispatchObject::Invoke(DISPID DispIDMember, REFIID RIID, LCID LCID, WORD Flags, DISPPARAMS* DispParams, VARIANT* VarResult, EXCEPINFO* ExcepInfo, UINT* ArgErr)
{
	CLock														Lock(MCS);

	ICustomDispatchTest*										This=static_cast<ICustomDispatchTest*>(this);
	HRESULT														HR;

	// !!! Vyuzije sa METHOD ITypeInfo.
	HR=MTypeInfo->Invoke(This,DispIDMember,Flags,DispParams,VarResult,ExcepInfo,ArgErr);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomDispatchObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<ICustomDispatchTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_ICustomDispatchTest)
	{
		*PointerToObject=static_cast<ICustomDispatchTest*>(this);
		AddRef();
		return(S_OK);
	}
	// !!! Implementuje sa aj IDispatch.
	else if (RIID==IID_IDispatch)
	{
		*PointerToObject=static_cast<IDispatch*>(this);
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
ULONG STDMETHODCALLTYPE CCustomDispatchObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CCustomDispatchObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------