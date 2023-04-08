//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CLREventHandler.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CCLREventHandler::CCLREventHandler(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CCLREventHandler::~CCLREventHandler(void)
{
	wprintf_s(L"!!!!!!!!!! EVENT HANDLER COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCLREventHandler::OnEvent(EClrEvent EventType, PVOID Data)
{
	CLock														Lock(MCS);

	if (EventType==Event_DomainUnload)
	{
		// !!! Pri zachytavani EVENTS Event_DomainUnload 'Data' obsahuje APP DOMAIN ID.
		DWORD													AppDomainID=(DWORD) Data;

		wprintf_s(L"!!!!! APP DOMAIN UNLOAD EVENT for APP DOMAIN [%d] OCCURRED !\n",AppDomainID);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCLREventHandler::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IActionOnCLREvent*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IActionOnCLREvent*>(this);
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
ULONG STDMETHODCALLTYPE CCLREventHandler::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CCLREventHandler::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------