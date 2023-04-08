//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include "StdAfx.h"
#include <stdio.h>
#include "MySimpleCOMFactory.h"
#include "MySimpleCOM.h"
//------------------------------------------------------------------------------------------------------
CMySimpleCOMFactory::CMySimpleCOMFactory(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMySimpleCOMFactory::~CMySimpleCOMFactory(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMySimpleCOMFactory::QueryInterface(REFIID RIID, void **PPVObject)
{
	if (RIID==IID_IUnknown)
	{
		*PPVObject=static_cast<IUnknown*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IClassFactory)
	{
		*PPVObject=static_cast<IClassFactory*>(this);
		AddRef();
		return(S_OK);
	}
	else
	{
		*PPVObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMySimpleCOMFactory::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMySimpleCOMFactory::Release(void)
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
HRESULT STDMETHODCALLTYPE CMySimpleCOMFactory::CreateInstance(IUnknown *PUnkOuter, REFIID RIID, void **PPVObject)
{
	if(PUnkOuter!=NULL)
	{
		*PPVObject=NULL;
		return(CLASS_E_NOAGGREGATION);
	}

	if (RIID==IID_IMySimpleInterface)
	{
		CMySimpleCOM*											NewObject=new CMySimpleCOM();
		HRESULT													HR;

		// Vykona aj INKREMENTACIU COM objektu.
		HR=NewObject->QueryInterface(RIID,PPVObject);

		if (SUCCEEDED(HR))
		{
			return(S_OK);
		}
		else
		{
			delete(NewObject);
			NewObject=NULL;

			*PPVObject=NULL;
			return(E_NOINTERFACE);
		}
	}
	else
	{
		*PPVObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMySimpleCOMFactory::LockServer(BOOL FLock)
{
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------