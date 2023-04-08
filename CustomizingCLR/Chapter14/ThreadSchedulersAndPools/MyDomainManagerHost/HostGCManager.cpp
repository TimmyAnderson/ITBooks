//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "HostGCManager.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CHostGCManager::CHostGCManager(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CHostGCManager::~CHostGCManager(void)
{
	wprintf_s(L"!!!!!!!!!! HOST GC MANAGER COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostGCManager::ThreadIsBlockingForSuspension(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"*************** ThreadIsBlockingForSuspension() CALLED ! ***************\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostGCManager::SuspensionStarting(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"*************** SuspensionStarting() CALLED ! ***************\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostGCManager::SuspensionEnding(DWORD Generation)
{
	CLock														Lock(MCS);

	wprintf_s(L"*************** SuspensionEnding() CALLED ! ***************\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostGCManager::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostGCManager*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostGCManager*>(this);
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
ULONG STDMETHODCALLTYPE CHostGCManager::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CHostGCManager::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------