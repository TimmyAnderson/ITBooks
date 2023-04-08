//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "AsynchronousMethodsObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CAsynchronousMethodsObject::CAsynchronousMethodsObject(void)
	: MReferenceCounter(0), MValue()
{
}
//------------------------------------------------------------------------------------------------------
CAsynchronousMethodsObject::~CAsynchronousMethodsObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAsynchronousMethodsObject::SetValue(BSTR Value)
{
	CLock														Lock(MCS);

	MValue=Value;

	wprintf_s(L"SetValue() CALLED - Value: [%s] !\n",MValue.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAsynchronousMethodsObject::GetValue(BSTR* Value)
{
	CLock														Lock(MCS);

	*Value=MValue.copy();

	wprintf_s(L"GetValue() CALLED - Value: [%s] !\n",MValue.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAsynchronousMethodsObject::Begin_SetValue(BSTR Value)
{
	CLock														Lock(MCS);

	MValue=Value;

	wprintf_s(L"Begin_SetValue() CALLED - Value: [%s] !\n",MValue.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAsynchronousMethodsObject::Finish_SetValue(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"Finish_SetValue() CALLED - Value: [%s] !\n",MValue.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAsynchronousMethodsObject::Begin_GetValue(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"Begin_GetValue() CALLED - Value: [%s] !\n",MValue.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAsynchronousMethodsObject::Finish_GetValue(BSTR* Value)
{
	CLock														Lock(MCS);

	*Value=MValue.copy();

	wprintf_s(L"Finish_GetValue() CALLED - Value: [%s] !\n",MValue.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAsynchronousMethodsObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IAsynchronousMethodsTest*>(this));
		AddRef();
		return(S_OK);
	}
	// SYNCHRONNY INTERFACE.
	else if (RIID==IID_IAsynchronousMethodsTest)
	{
		*PointerToObject=static_cast<IAsynchronousMethodsTest*>(this);
		AddRef();
		return(S_OK);
	}
	// ASYNCHRONNY INTERFACE.
	else if (RIID==IID_AsyncIAsynchronousMethodsTest)
	{
		*PointerToObject=static_cast<AsyncIAsynchronousMethodsTest*>(this);
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
ULONG STDMETHODCALLTYPE CAsynchronousMethodsObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CAsynchronousMethodsObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------