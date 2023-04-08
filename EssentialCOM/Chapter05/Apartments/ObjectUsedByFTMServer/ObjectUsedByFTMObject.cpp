//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "ObjectUsedByFTMObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CObjectUsedByFTMObject::CObjectUsedByFTMObject(void)
	: MReferenceCounter(0), MValue(0)
{
}
//------------------------------------------------------------------------------------------------------
CObjectUsedByFTMObject::~CObjectUsedByFTMObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT [CObjectUsedByFTMObject] DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CObjectUsedByFTMObject::IncrementValue(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	MValue++;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CObjectUsedByFTMObject::GetValue(long* Value)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.

	*Value=MValue;

	wprintf_s(L"!!!!! SERVER VALUE [CObjectUsedByFTMObject]: [%d] !\n",MValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CObjectUsedByFTMObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IObjectUsedByFTMTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IObjectUsedByFTMTest)
	{
		*PointerToObject=static_cast<IObjectUsedByFTMTest*>(this);
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
ULONG STDMETHODCALLTYPE CObjectUsedByFTMObject::AddRef(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	ULONG														Ret=++MReferenceCounter;

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CObjectUsedByFTMObject::Release(void)
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