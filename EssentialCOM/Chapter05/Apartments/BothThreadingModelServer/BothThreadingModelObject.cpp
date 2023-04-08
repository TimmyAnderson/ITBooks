//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "BothThreadingModelObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CBothThreadingModelObject::CBothThreadingModelObject(void)
	: MReferenceCounter(0), MValue(0)
{
}
//------------------------------------------------------------------------------------------------------
CBothThreadingModelObject::~CBothThreadingModelObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CBothThreadingModelObject::IncrementValue(void)
{
	CLock														Lock(MCS);

	MValue++;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CBothThreadingModelObject::GetValue(long* Value)
{
	CLock														Lock(MCS);

	*Value=MValue;

	wprintf_s(L"!!!!! SERVER VALUE: [%d] !\n",MValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CBothThreadingModelObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IBothThreadingModelTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IBothThreadingModelTest)
	{
		*PointerToObject=static_cast<IBothThreadingModelTest*>(this);
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
ULONG STDMETHODCALLTYPE CBothThreadingModelObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CBothThreadingModelObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------