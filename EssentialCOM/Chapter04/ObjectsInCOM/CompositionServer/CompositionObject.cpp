//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CompositionObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CCompositionObject::CCompositionObject(void)
	: MReferenceCounter(0), MGetText1(), MGetText2()
{
	MGetText1.Initialize(this);
	MGetText2.Initialize(this);
}
//------------------------------------------------------------------------------------------------------
CCompositionObject::~CCompositionObject(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCompositionObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		// !!! Odkazuje na lubovolny COM INTERFACE CLASS.
		*PointerToObject=static_cast<IUnknown*>(&MGetText1);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IGetText1)
	{
		*PointerToObject=static_cast<IGetText1*>(&MGetText1);

		// !!! Vola sa CGetText1::AddRef().
		((IUnknown*)(*PointerToObject))->AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IGetText2)
	{
		*PointerToObject=static_cast<IGetText2*>(&MGetText2);

		// !!! Vola sa CGetText2::AddRef().
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
ULONG STDMETHODCALLTYPE CCompositionObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CCompositionObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------