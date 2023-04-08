//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "ApartmentThreadingModelObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CApartmentThreadingModelObject::CApartmentThreadingModelObject(void)
	: MReferenceCounter(0), MValue(0)
{
}
//------------------------------------------------------------------------------------------------------
CApartmentThreadingModelObject::~CApartmentThreadingModelObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CApartmentThreadingModelObject::IncrementValue(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	MValue++;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CApartmentThreadingModelObject::GetValue(long* Value)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.

	*Value=MValue;

	wprintf_s(L"!!!!! SERVER VALUE: [%d] !\n",MValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CApartmentThreadingModelObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IApartmentThreadingModelTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IApartmentThreadingModelTest)
	{
		*PointerToObject=static_cast<IApartmentThreadingModelTest*>(this);
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
ULONG STDMETHODCALLTYPE CApartmentThreadingModelObject::AddRef(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	ULONG														Ret=++MReferenceCounter;

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CApartmentThreadingModelObject::Release(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	ULONG														Ret=--MReferenceCounter;

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------