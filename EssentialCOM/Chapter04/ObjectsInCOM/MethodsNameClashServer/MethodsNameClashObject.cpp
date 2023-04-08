//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MethodsNameClashObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CMethodsNameClashObject::CMethodsNameClashObject(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMethodsNameClashObject::~CMethodsNameClashObject(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMethodsNameClashObject::GetText1(int BufferSize, wchar_t** Text)
{
	CLock														Lock(MCS);

	wcscpy_s(*Text,BufferSize,L"Text 111 !");
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMethodsNameClashObject::GetText2(int BufferSize, wchar_t** Text)
{
	CLock														Lock(MCS);

	wcscpy_s(*Text,BufferSize,L"Text 222 !");
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMethodsNameClashObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IGetText1*>(this));
		((IUnknown*)(*PointerToObject))->AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IGetText1)
	{
		*PointerToObject=static_cast<IGetText1*>(this);
		((IUnknown*)(*PointerToObject))->AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IGetText2)
	{
		*PointerToObject=static_cast<IGetText2*>(this);
		((IUnknown*)(*PointerToObject))->AddRef();
		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMethodsNameClashObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMethodsNameClashObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------