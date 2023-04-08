//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "OutOfProcessWithMarshallingObjectFactory.h"
#include "OutOfProcessWithMarshallingObject.h"
//------------------------------------------------------------------------------------------------------
COutOfProcessWithMarshallingObjectFactory::COutOfProcessWithMarshallingObjectFactory(HANDLE ProcessExitEvent)
	: MReferenceCounter(0), MProcessExitEvent(ProcessExitEvent)
{
}
//------------------------------------------------------------------------------------------------------
COutOfProcessWithMarshallingObjectFactory::~COutOfProcessWithMarshallingObjectFactory(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE COutOfProcessWithMarshallingObjectFactory::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE COutOfProcessWithMarshallingObjectFactory::Release(void)
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
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObjectFactory::CreateInstance(IUnknown* UnkOuter, REFIID RIID, void** PointerToObject)
{
	if (UnkOuter!=NULL)
	{
		*PointerToObject=NULL;
		return(CLASS_E_NOAGGREGATION);
	}

	// !!! Musi tu byt aj IUnknown, inak nedokaze CLIENT vytvorit instanciu COM OBJECT.
	if (RIID==IID_IUnknown || RIID==IID_IName)
	{
		// !!! Pre kazdu novu poziadavku na COM OBJECT sa vytvara NOVY COM OBJECT. FUNCTION by vsak mohla vracat i VZDY TEN ISTY OBJECT, cim by sa realizovala implementacia SINGLETON COM OBJECT.
		COutOfProcessWithMarshallingObject*									NewObject=new COutOfProcessWithMarshallingObject(MProcessExitEvent);
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
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObjectFactory::LockServer(BOOL Lock)
{
	if (Lock!=FALSE)
	{
		CoAddRefServerProcess();
	}
	else
	{
		if (CoReleaseServerProcess()==0)
		{
			SetEvent(MProcessExitEvent);
		}
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObjectFactory::QueryInterface(REFIID RIID, void** PointerToObject)
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