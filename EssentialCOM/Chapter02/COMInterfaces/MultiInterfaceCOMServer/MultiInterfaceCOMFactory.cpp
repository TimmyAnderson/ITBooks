//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MultiInterfaceCOMFactory.h"
#include "MultiInterfaceCOM.h"
//------------------------------------------------------------------------------------------------------
CMultiInterfaceCOMFactory::CMultiInterfaceCOMFactory(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMultiInterfaceCOMFactory::~CMultiInterfaceCOMFactory(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMultiInterfaceCOMFactory::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMultiInterfaceCOMFactory::Release(void)
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
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOMFactory::CreateInstance(IUnknown* UnkOuter, REFIID RIID, void** PointerToObject)
{
	if (UnkOuter!=NULL)
	{
		*PointerToObject=NULL;
		return(CLASS_E_NOAGGREGATION);
	}

	if (RIID==IID_IName || RIID==IID_IToString || RIID==IID_ITest || RIID==IID_IExceptionTest || RIID==IID_ISupportErrorInfo)
	{
		CMultiInterfaceCOM*										NewObject=new CMultiInterfaceCOM();
		HRESULT													HR;

		// Vykona aj INKREMENTACIU COM objektu.
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
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOMFactory::LockServer(BOOL Lock)
{
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOMFactory::QueryInterface(REFIID RIID, void** PointerToObject)
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