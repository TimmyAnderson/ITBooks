//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyServerCallback.h"
#include "Helpers\Lock.h"
#include <comdef.h>
//------------------------------------------------------------------------------------------------------
CMyServerCallback::CMyServerCallback(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMyServerCallback::~CMyServerCallback(void)
{
	wprintf_s(L"!!!!!!!!!! CALLBACK COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyServerCallback::SendMessageToClient(BSTR Message)
{
	bstr_t														MessageFromServer(Message);

	wprintf_s(L"Message from SERVER [%s] !\n",MessageFromServer.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyServerCallback::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IMyServerCallback*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMyServerCallback)
	{
		*PointerToObject=static_cast<IMyServerCallback*>(this);
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
ULONG STDMETHODCALLTYPE CMyServerCallback::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyServerCallback::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------