//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyAccessControl.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CMyAccessControl::CMyAccessControl(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMyAccessControl::~CMyAccessControl(void)
{
	wprintf_s(L"!!!!!!!!!! SECURITY COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyAccessControl::GrantAccessRights(__RPC__in PACTRL_ACCESSW AccessList)
{
	CLock														Lock(MCS);

	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyAccessControl::SetAccessRights(__RPC__in PACTRL_ACCESSW AccessList)
{
	CLock														Lock(MCS);

	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyAccessControl::SetOwner(__RPC__in PTRUSTEEW Owner, __RPC__in PTRUSTEEW Group)
{
	CLock														Lock(MCS);

	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyAccessControl::RevokeAccessRights(__RPC__in LPWSTR Property, ULONG CTrustees, __RPC__in_ecount_full(CTrustees) TRUSTEEW Trustees[])
{
	CLock														Lock(MCS);

	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyAccessControl::GetAllAccessRights(__RPC__in LPWSTR Property, __RPC__deref_out_opt PACTRL_ACCESSW_ALLOCATE_ALL_NODES* AccessList, __RPC__deref_out_opt PTRUSTEEW* Owner, __RPC__deref_out_opt PTRUSTEEW* Group)
{
	CLock														Lock(MCS);

	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyAccessControl::IsAccessAllowed(__RPC__in PTRUSTEEW Trustee, __RPC__in LPWSTR Property, ACCESS_RIGHTS AccessRights, __RPC__out BOOL* AccessAllowed)
{
	CLock														Lock(MCS);

	if (Trustee->TrusteeForm==TRUSTEE_IS_NAME)
	{
		wprintf_s(L"USER [%s] AUTHORIZED !\n",Trustee->ptstrName);
	}
	else
	{
		wprintf_s(L"USER [by SID] AUTHORIZED !\n");
	}

	*AccessAllowed=TRUE;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyAccessControl::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IAccessControl*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IAccessControl)
	{
		*PointerToObject=static_cast<IAccessControl*>(this);
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
ULONG STDMETHODCALLTYPE CMyAccessControl::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyAccessControl::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------