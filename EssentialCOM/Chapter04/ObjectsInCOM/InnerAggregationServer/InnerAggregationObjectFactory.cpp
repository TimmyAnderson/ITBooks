//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "InnerAggregationObjectFactory.h"
#include "InnerAggregationObject.h"
//------------------------------------------------------------------------------------------------------
CInnerAggregationObjectFactory::CInnerAggregationObjectFactory(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CInnerAggregationObjectFactory::~CInnerAggregationObjectFactory(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CInnerAggregationObjectFactory::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CInnerAggregationObjectFactory::Release(void)
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
HRESULT STDMETHODCALLTYPE CInnerAggregationObjectFactory::CreateInstance(IUnknown* UnkOuter, REFIID RIID, void** PointerToObject)
{
	// !!!!! Podla COM SPECIFIKACIE MUSI OUTER COM OBJECT pozadovat IBA IUnknown.
	if (UnkOuter!=NULL && RIID!=IID_IUnknown)
	{
		*PointerToObject=NULL;
		return(CLASS_E_NOAGGREGATION);
	}

	if (RIID==IID_IInnerAggregationText || RIID==IID_IUnknown)
	{
		// !!! Pre kazdu novu poziadavku na COM OBJECT sa vytvara NOVY COM OBJECT. FUNCTION by vsak mohla vracat i VZDY TEN ISTY OBJECT, cim by sa realizovala implementacia SINGLETON COM OBJECT.
		CInnerAggregationObject*								NewObject=new CInnerAggregationObject(UnkOuter);
		HRESULT													HR;

		NewObject->NonAggregationUnknown_AddRef();

		// !!!!! Musi volan NON-AGGREGATION verziu COM OBJECT.
		// Vykona aj INKREMENTACIU COUNTER vytvoreneho COM OBJECT.
		HR=NewObject->NonAggregationUnknown_QueryInterface(RIID,PointerToObject);

		NewObject->NonAggregationUnknown_Release();

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
HRESULT STDMETHODCALLTYPE CInnerAggregationObjectFactory::LockServer(BOOL Lock)
{
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CInnerAggregationObjectFactory::QueryInterface(REFIID RIID, void** PointerToObject)
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