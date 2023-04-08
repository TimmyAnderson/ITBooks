//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyServerObject.h"
#include "Helpers\Lock.h"
#include <comdef.h>
//------------------------------------------------------------------------------------------------------
CMyServerObject::CMyServerObject(void)
	: MReferenceCounter(0), MCallback(0)
{
}
//------------------------------------------------------------------------------------------------------
CMyServerObject::~CMyServerObject(void)
{
	MCallback=NULL;

	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyServerObject::RegisterCallback(IMyServerCallback* Callback)
{
	CLock														Lock(MCS);

	MCallback=Callback;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyServerObject::UnRegisterCallback(void)
{
	CLock														Lock(MCS);

	MCallback=NULL;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyServerObject::SendMessageToServer(BSTR Message)
{
	CLock														Lock(MCS);

	bstr_t														MessageFromClient=Message;

	wprintf_s(L"Message from CLIENT [%s] !\n",MessageFromClient.operator const wchar_t *());

	if (MCallback.GetInterface()!=NULL)
	{
		bstr_t													MessageToClient=L"CLIENT MESSAGE [";

		MessageToClient+=MessageFromClient;
		MessageToClient+=bstr_t(L"]");

		MCallback->SendMessageToClient(MessageToClient);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyServerObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IMyServer*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMyServer)
	{
		*PointerToObject=static_cast<IMyServer*>(this);
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
ULONG STDMETHODCALLTYPE CMyServerObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyServerObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------