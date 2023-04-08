//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "UnmanagedCOMServerCallback.h"
#include "Helpers\Lock.h"
#include <comdef.h>
//------------------------------------------------------------------------------------------------------
CUnmanagedCOMServerCallback::CUnmanagedCOMServerCallback(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CUnmanagedCOMServerCallback::~CUnmanagedCOMServerCallback(void)
{
	wprintf_s(L"!!!!!!!!!! CALLBACK COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMServerCallback::SendMessageToClient(BSTR Message)
{
	bstr_t														MessageFromServer(Message);

	wprintf_s(L"Message from SERVER [%s] !\n",MessageFromServer.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMServerCallback::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IUnmanagedCOMServerCallback*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IUnmanagedCOMServerCallback)
	{
		*PointerToObject=static_cast<IUnmanagedCOMServerCallback*>(this);
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
ULONG STDMETHODCALLTYPE CUnmanagedCOMServerCallback::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CUnmanagedCOMServerCallback::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------