//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "FreeThreadingModelObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CFreeThreadingModelObject::CFreeThreadingModelObject(void)
	: MReferenceCounter(0), MValue(0)
{
}
//------------------------------------------------------------------------------------------------------
CFreeThreadingModelObject::~CFreeThreadingModelObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CFreeThreadingModelObject::IncrementValue(void)
{
	CLock														Lock(MCS);

	MValue++;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CFreeThreadingModelObject::GetValue(long* Value)
{
	CLock														Lock(MCS);

	*Value=MValue;

	wprintf_s(L"!!!!! SERVER VALUE: [%d] !\n",MValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CFreeThreadingModelObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IFreeThreadingModelTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IFreeThreadingModelTest)
	{
		*PointerToObject=static_cast<IFreeThreadingModelTest*>(this);
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
ULONG STDMETHODCALLTYPE CFreeThreadingModelObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CFreeThreadingModelObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------