//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
class CMyMallocSpy : public IMallocSpy
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual SIZE_T STDMETHODCALLTYPE PreAlloc(__in SIZE_T Request);
        virtual void* STDMETHODCALLTYPE PostAlloc(__in void* Actual);
        virtual void* STDMETHODCALLTYPE PreFree(__in void* Request, __in BOOL Spyed);
        virtual void STDMETHODCALLTYPE PostFree(__in BOOL Spyed);
        virtual SIZE_T STDMETHODCALLTYPE PreRealloc(__in void* Request, __in  SIZE_T CountRequest, __deref_out void** NewRequest, __in BOOL Spyed);
        virtual void* STDMETHODCALLTYPE PostRealloc(__in void* Actual, __in BOOL Spyed);
        virtual void* STDMETHODCALLTYPE PreGetSize(__in void* Request, __in BOOL Spyed);
        virtual SIZE_T STDMETHODCALLTYPE PostGetSize(__in SIZE_T Actual, __in BOOL Spyed);
        virtual void* STDMETHODCALLTYPE PreDidAlloc(__in void* Request, __in BOOL Spyed);
        virtual int STDMETHODCALLTYPE PostDidAlloc(__in void* Request, __in BOOL Spyed, __in int Actual);
        virtual void STDMETHODCALLTYPE PreHeapMinimize(void);
        virtual void STDMETHODCALLTYPE PostHeapMinimize(void);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMyMallocSpy(void);
		virtual ~CMyMallocSpy(void);
};
//------------------------------------------------------------------------------------------------------