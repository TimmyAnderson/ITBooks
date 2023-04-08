//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "SingletonObjectFactory.h"
#include "SingletonObject.h"
//------------------------------------------------------------------------------------------------------
CSingletonObject												CSingletonObjectFactory::MSingletonInstance;
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
CSingletonObjectFactory::CSingletonObjectFactory(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CSingletonObjectFactory::~CSingletonObjectFactory(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CSingletonObjectFactory::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CSingletonObjectFactory::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CSingletonObjectFactory::CreateInstance(IUnknown* UnkOuter, REFIID RIID, void** PointerToObject)
{
	if (UnkOuter!=NULL)
	{
		*PointerToObject=NULL;
		return(CLASS_E_NOAGGREGATION);
	}

	if (RIID==IID_ISingletonName)
	{
		// !!! Vracia SINGLETON instanciu.
		MSingletonInstance.QueryInterface(RIID,PointerToObject);

		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CSingletonObjectFactory::LockServer(BOOL Lock)
{
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CSingletonObjectFactory::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IClassFactory)
	{
		*PointerToObject=static_cast<IClassFactory*>(this);
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