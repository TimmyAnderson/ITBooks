//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <comdef.h>
#include "ConnectionPointContainer.h"
#include "ConnectionPoint.h"
#include "Helpers\Lock.h"
//------------------------------------------------------------------------------------------------------
CConnectionPointContainer::CConnectionPointContainer(void)
	: MReferenceCounter(0), MConnectionPointsManager()
{
}
//------------------------------------------------------------------------------------------------------
CConnectionPointContainer::~CConnectionPointContainer(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPointContainer::SendMessageToServer(BSTR Message)
{
	CLock														Lock(MCS);

	bstr_t														MessageFromClient=Message;

	wprintf_s(L"Message from CLIENT [%s] !\n",MessageFromClient.operator const wchar_t *());

	bstr_t														MessageToClient=L"CLIENT MESSAGE [";

	MessageToClient+=MessageFromClient;
	MessageToClient+=bstr_t(L"]");

	MConnectionPointsManager.FireCallback(MessageToClient);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPointContainer::EnumConnectionPoints(__RPC__deref_out_opt IEnumConnectionPoints** Enum)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPointContainer::FindConnectionPoint(__RPC__in REFIID RIID, __RPC__deref_out_opt IConnectionPoint** CP)
{
	if (RIID==__uuidof(IMyConnectionPointsCallback))
	{
		HRESULT													HR;

		// !!! Vytvori sa NOVY CONNECTION POINT.
		CConnectionPoint*										ConnectionPoint=new CConnectionPoint(&MConnectionPointsManager,this);

		HR=ConnectionPoint->QueryInterface(__uuidof(IConnectionPoint),(void**) CP);

		return(HR);
	}
	else
	{
		return(CONNECT_E_NOCONNECTION);
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnectionPointContainer::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IMyConnectionPoints*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMyConnectionPoints)
	{
		*PointerToObject=static_cast<IMyConnectionPoints*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IConnectionPointContainer)
	{
		*PointerToObject=static_cast<IConnectionPointContainer*>(this);
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
ULONG STDMETHODCALLTYPE CConnectionPointContainer::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CConnectionPointContainer::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------