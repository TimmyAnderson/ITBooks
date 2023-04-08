//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyMessageFilter.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CMyMessageFilter::CMyMessageFilter(void)
	: MReferenceCounter(0), MRejectCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMyMessageFilter::~CMyMessageFilter(void)
{
	wprintf_s(L"!!!!!!!!!! MESSAGE FILTER OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
DWORD STDMETHODCALLTYPE CMyMessageFilter::HandleInComingCall(__in DWORD CallType, __in HTASK TaskCaller, __in DWORD TickCount, __in_opt LPINTERFACEINFO InterfaceInfo)
{
	wprintf_s(L"HandleInComingCall() CALLED - CallType: [%d] !\n",CallType);

	if ((MRejectCounter++ % 2)==0)
	{
		return(SERVERCALL_ISHANDLED);
	}
	else
	{
		return(SERVERCALL_REJECTED);
	}
}
//------------------------------------------------------------------------------------------------------
DWORD STDMETHODCALLTYPE CMyMessageFilter::RetryRejectedCall(__in HTASK TaskCallee, __in DWORD TickCount, __in DWORD RejectType)
{
	wprintf_s(L"RetryRejectedCall() CALLED - RejectType: [%d] !\n",RejectType);

	// !!! MESSAGE bude REJECTED.
	return(-1);
}
//------------------------------------------------------------------------------------------------------
DWORD STDMETHODCALLTYPE CMyMessageFilter::MessagePending(__in HTASK TaskCallee, __in DWORD TickCount, __in DWORD PendingType)
{
	wprintf_s(L"MessagePending() CALLED - PendingType: [%d] !\n",PendingType);

	return(PENDINGMSG_WAITDEFPROCESS);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyMessageFilter::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IMessageFilter*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMessageFilter)
	{
		*PointerToObject=static_cast<IMessageFilter*>(this);
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
ULONG STDMETHODCALLTYPE CMyMessageFilter::AddRef(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	ULONG														Ret=++MReferenceCounter;

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyMessageFilter::Release(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	ULONG														Ret=--MReferenceCounter;

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------