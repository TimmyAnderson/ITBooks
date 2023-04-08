//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "QITestObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CQITestObject::CQITestObject(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CQITestObject::~CQITestObject(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CQITestObject::GetText1(int BufferSize, wchar_t** Text)
{
	CLock														Lock(MCS);

	wcscpy_s(*Text,BufferSize,L"Text 111 !");
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CQITestObject::GetText2(int BufferSize, wchar_t** Text)
{
	CLock														Lock(MCS);

	wcscpy_s(*Text,BufferSize,L"Text 222 !");
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CQITestObject::GetText3(int BufferSize, wchar_t** Text)
{
	CLock														Lock(MCS);

	wcscpy_s(*Text,BufferSize,L"Text 333 !");
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CQITestObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IGetText1*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IGetText1)
	{
		*PointerToObject=static_cast<IGetText1*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IGetText2)
	{
		*PointerToObject=static_cast<IGetText2*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IGetText3)
	{
		*PointerToObject=static_cast<IGetText3*>(this);
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
ULONG STDMETHODCALLTYPE CQITestObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CQITestObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------