//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "AliasingObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CAliasingObject::CAliasingObject(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CAliasingObject::~CAliasingObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAliasingObject::Dummy(void)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD Dummy() was CALLED !\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAliasingObject::FillArray(int ArraySize, int* ArrayLength, int* Array)
{
	CLock														Lock(MCS);

	// !!! Kontrolujem maximalnu velkost ARRAY.
	for(int Index=0;Index<10 && Index<ArraySize;Index++)
	{
		Array[Index]=9-Index;
	}

	*ArrayLength=10;

	wprintf(L"SERVER: METHOD FillArray() was CALLED !\n");
	wprintf(L"SERVER: ArraySize [%d] !\n",ArraySize);
	wprintf(L"SERVER: ArrayLength [%d] !\n",*ArrayLength);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAliasingObject::CallFunctionDefinedByCPPQuote(void)
{
	// !!!!! FUNCTION bola DEKLAROVANA cez cpp_quote().
	PrintText();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CAliasingObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IAliasingTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IAliasingTest)
	{
		*PointerToObject=static_cast<IAliasingTest*>(this);
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
ULONG STDMETHODCALLTYPE CAliasingObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CAliasingObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------