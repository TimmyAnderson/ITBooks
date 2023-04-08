//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "ConnectionPoint.h"
#include "Helpers\Lock.h"
#include <comdef.h>
#include "ConnectionPointContainer.h"
//------------------------------------------------------------------------------------------------------
CConnectionPoint::CConnectionPoint(CConnectionPointsManager* ConnectionPointsManager, CConnectionPointContainer* ConnectionPointContainer)
	: MReferenceCounter(0), MConnectionPointsManager(ConnectionPointsManager), MConnectionPointContainer(NULL)
{
	MConnectionPointContainer=ConnectionPointContainer;

	// !!!!! EXTREMNE DOLEZITE. Sposobi, ze CONNECTION POINT CONTAINER sa NEUVOLNI PREDCASNE.
	MConnectionPointContainer->AddRef();
}
//------------------------------------------------------------------------------------------------------
CConnectionPoint::~CConnectionPoint(void)
{
	if (MConnectionPointContainer!=NULL)
	{
		MConnectionPointContainer->Release();
		MConnectionPointContainer=NULL;
	}

	wprintf_s(L"!!!!!!!!!! CONNECTION POINT COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPoint::GetConnectionInterface(__RPC__out IID* IID)
{
	*IID=__uuidof(IMyConnectionPointsCallback);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPoint::GetConnectionPointContainer(__RPC__deref_out_opt IConnectionPointContainer** CPC)
{
	*CPC=MConnectionPointContainer;
	MConnectionPointContainer->AddRef();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPoint::Advise(__RPC__in_opt IUnknown* UnkSink, __RPC__out DWORD* Cookie)
{
	HRESULT														HR;
	CSmartCOMPointer<IMyConnectionPointsCallback>				Callback;

	if (SUCCEEDED(HR=UnkSink->QueryInterface(__uuidof(IMyConnectionPointsCallback),(void**)&Callback)))
	{
		HR=MConnectionPointsManager->Advise(Callback.GetInterface(),Cookie);

		Callback=NULL;

		return(HR);
	}
	else
	{
		wprintf_s(L"!!!!! ERROR - Can't get CORRECT CALLBACK COM INTERFACE !\n");

		return(CONNECT_E_CANNOTCONNECT);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPoint::Unadvise(DWORD Cookie)
{
	HRESULT														HR=MConnectionPointsManager->Unadvise(Cookie);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPoint::EnumConnections(__RPC__deref_out_opt IEnumConnections** Enum)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPoint::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IConnectionPoint*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IConnectionPoint)
	{
		*PointerToObject=static_cast<IConnectionPoint*>(this);
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
ULONG STDMETHODCALLTYPE CConnectionPoint::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CConnectionPoint::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------