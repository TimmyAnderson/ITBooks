//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyConnectionPointsCallback.h"
#include "Helpers\Lock.h"
#include <comdef.h>
//------------------------------------------------------------------------------------------------------
CMyConnectionPointsCallback::CMyConnectionPointsCallback(wchar_t* CallbackName)
	: MReferenceCounter(0), MCallbackName(CallbackName)
{
}
//------------------------------------------------------------------------------------------------------
CMyConnectionPointsCallback::~CMyConnectionPointsCallback(void)
{
	wprintf_s(L"!!!!!!!!!! CALLBACK COM OBJECT [%s] DESTROYED !!!!!!!!!!\n",MCallbackName);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyConnectionPointsCallback::SendMessageToClient(BSTR Message)
{
	bstr_t														MessageFromServer(Message);

	wprintf_s(L"CallbackName [%s] -----> Message from SERVER [%s] !\n",MCallbackName,MessageFromServer.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyConnectionPointsCallback::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IMyConnectionPointsCallback*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMyConnectionPointsCallback)
	{
		*PointerToObject=static_cast<IMyConnectionPointsCallback*>(this);
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
ULONG STDMETHODCALLTYPE CMyConnectionPointsCallback::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyConnectionPointsCallback::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------