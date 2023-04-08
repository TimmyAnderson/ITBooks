//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "PointersObjectFactory.h"
#include "PointersObject.h"
//------------------------------------------------------------------------------------------------------
CPointersObjectFactory::CPointersObjectFactory(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CPointersObjectFactory::~CPointersObjectFactory(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CPointersObjectFactory::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CPointersObjectFactory::Release(void)
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
HRESULT STDMETHODCALLTYPE CPointersObjectFactory::CreateInstance(IUnknown* UnkOuter, REFIID RIID, void** PointerToObject)
{
	if (UnkOuter!=NULL)
	{
		*PointerToObject=NULL;
		return(CLASS_E_NOAGGREGATION);
	}

	if (RIID==IID_IPointersTest || RIID==IID_IUnknown)
	{
		// !!! Pre kazdu novu poziadavku na COM OBJECT sa vytvara NOVY COM OBJECT. FUNCTION by vsak mohla vracat i VZDY TEN ISTY OBJECT, cim by sa realizovala implementacia SINGLETON COM OBJECT.
		CPointersObject*										NewObject=new CPointersObject();
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
HRESULT STDMETHODCALLTYPE CPointersObjectFactory::LockServer(BOOL Lock)
{
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObjectFactory::QueryInterface(REFIID RIID, void** PointerToObject)
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