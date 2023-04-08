//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyMallocSpy.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CMyMallocSpy::CMyMallocSpy(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMyMallocSpy::~CMyMallocSpy(void)
{
	wprintf_s(L"!!!!!!!!!! MALLOC SPY OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
SIZE_T STDMETHODCALLTYPE CMyMallocSpy::PreAlloc(__in SIZE_T Request)
{
	CLock														Lock(MCS);

	wprintf_s(L"PreAlloc() CALLED !\n");

	return(Request);
}
//------------------------------------------------------------------------------------------------------
void* STDMETHODCALLTYPE CMyMallocSpy::PostAlloc(__in void* Actual)
{
	CLock														Lock(MCS);

	wprintf_s(L"PostAlloc() CALLED !\n");

	return(Actual);
}
//------------------------------------------------------------------------------------------------------
void* STDMETHODCALLTYPE CMyMallocSpy::PreFree(__in void* Request, __in BOOL Spyed)
{
	CLock														Lock(MCS);

	wprintf_s(L"PreFree() CALLED !\n");

	return(Request);
}
//------------------------------------------------------------------------------------------------------
void STDMETHODCALLTYPE CMyMallocSpy::PostFree(__in BOOL Spyed)
{
	CLock														Lock(MCS);

	wprintf_s(L"PostFree() CALLED !\n");
}
//------------------------------------------------------------------------------------------------------
SIZE_T STDMETHODCALLTYPE CMyMallocSpy::PreRealloc(__in void* Request, __in  SIZE_T CountRequest, __deref_out void** NewRequest, __in BOOL Spyed)
{
	CLock														Lock(MCS);

	wprintf_s(L"PreRealloc() CALLED !\n");

	return(CountRequest);
}
//------------------------------------------------------------------------------------------------------
void* STDMETHODCALLTYPE CMyMallocSpy::PostRealloc(__in void* Actual, __in BOOL Spyed)
{
	CLock														Lock(MCS);

	wprintf_s(L"PostRealloc() CALLED !\n");

	return(Actual);
}
//------------------------------------------------------------------------------------------------------
void* STDMETHODCALLTYPE CMyMallocSpy::PreGetSize(__in void* Request, __in BOOL Spyed)
{
	CLock														Lock(MCS);

	wprintf_s(L"PreGetSize() CALLED !\n");

	return(Request);
}
//------------------------------------------------------------------------------------------------------
SIZE_T STDMETHODCALLTYPE CMyMallocSpy::PostGetSize(__in SIZE_T Actual, __in BOOL Spyed)
{
	CLock														Lock(MCS);

	wprintf_s(L"PostGetSize() CALLED !\n");

	return(Actual);
}
//------------------------------------------------------------------------------------------------------
void* STDMETHODCALLTYPE CMyMallocSpy::PreDidAlloc(__in void* Request, __in BOOL Spyed)
{
	CLock														Lock(MCS);

	wprintf_s(L"PreDidAlloc() CALLED !\n");

	return(Request);
}
//------------------------------------------------------------------------------------------------------
int STDMETHODCALLTYPE CMyMallocSpy::PostDidAlloc(__in void* Request, __in BOOL Spyed, __in int Actual)
{
	CLock														Lock(MCS);

	wprintf_s(L"PostDidAlloc() CALLED !\n");

	return(Actual);
}
//------------------------------------------------------------------------------------------------------
void STDMETHODCALLTYPE CMyMallocSpy::PreHeapMinimize(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"PreHeapMinimize() CALLED !\n");
}
//------------------------------------------------------------------------------------------------------
void STDMETHODCALLTYPE CMyMallocSpy::PostHeapMinimize(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"PostHeapMinimize() CALLED !\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyMallocSpy::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IMallocSpy*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMallocSpy)
	{
		*PointerToObject=static_cast<IMallocSpy*>(this);
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
ULONG STDMETHODCALLTYPE CMyMallocSpy::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyMallocSpy::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------