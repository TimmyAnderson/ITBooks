//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "HostPolicyManager.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CHostPolicyManager::CHostPolicyManager(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CHostPolicyManager::~CHostPolicyManager(void)
{
	wprintf_s(L"!!!!!!!!!! HOST POLICY MANAGER COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostPolicyManager::OnDefaultAction(EClrOperation Operation, EPolicyAction Action)
{
	CLock														Lock(MCS);

	wprintf_s(L"++++++++++ OnDefaultAction() CALLED - Operation [%d], Action [%d] ! ++++++++++\n",Operation,Action);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostPolicyManager::OnTimeout(EClrOperation Operation, EPolicyAction Action)
{
	CLock														Lock(MCS);

	wprintf_s(L"++++++++++ OnTimeout() CALLED - Operation [%d], Action [%d] ! ++++++++++\n",Operation,Action);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostPolicyManager::OnFailure(EClrFailure Failure, EPolicyAction Action)
{
	CLock														Lock(MCS);

	wprintf_s(L"++++++++++ OnFailure() CALLED - Failure [%d], Action [%d] ! ++++++++++\n",Failure,Action);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostPolicyManager::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostPolicyManager*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostPolicyManager*>(this);
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
ULONG STDMETHODCALLTYPE CHostPolicyManager::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CHostPolicyManager::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------