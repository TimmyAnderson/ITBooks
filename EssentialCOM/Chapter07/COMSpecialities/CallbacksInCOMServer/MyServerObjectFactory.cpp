//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyServerObjectFactory.h"
#include "MyServerObject.h"
//------------------------------------------------------------------------------------------------------
CMyServerObjectFactory::CMyServerObjectFactory(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMyServerObjectFactory::~CMyServerObjectFactory(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyServerObjectFactory::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyServerObjectFactory::Release(void)
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
HRESULT STDMETHODCALLTYPE CMyServerObjectFactory::CreateInstance(IUnknown* UnkOuter, REFIID RIID, void** PointerToObject)
{
	if (UnkOuter!=NULL)
	{
		*PointerToObject=NULL;
		return(CLASS_E_NOAGGREGATION);
	}

	if (RIID==IID_IMyServer)
	{
		// !!! Pre kazdu novu poziadavku na COM OBJECT sa vytvara NOVY COM OBJECT. FUNCTION by vsak mohla vracat i VZDY TEN ISTY OBJECT, cim by sa realizovala implementacia SINGLETON COM OBJECT.
		CMyServerObject*										NewObject=new CMyServerObject();
		HRESULT													HR;

		// Vykona aj INKREMENTACIU COUNTER vytvoreneho COM OBJECT.
		HR=NewObject->QueryInterface(RIID,PointerToObject);

		if (SUCCEEDED(HR))
		{
			return(S_OK);
		}
		else
		{
			delete(NewObject);
			NewObject=NULL;

			*PointerToObject=NULL;
			return(E_NOINTERFACE);
		}
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyServerObjectFactory::LockServer(BOOL Lock)
{
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyServerObjectFactory::QueryInterface(REFIID RIID, void** PointerToObject)
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