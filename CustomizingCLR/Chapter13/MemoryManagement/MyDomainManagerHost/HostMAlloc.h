//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
class CHostMAlloc : public IHostMalloc
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		bool													MUseHeap;

	public:
        virtual HRESULT STDMETHODCALLTYPE Alloc(SIZE_T Size, EMemoryCriticalLevel CriticalLevel, void** Mem);
        virtual HRESULT STDMETHODCALLTYPE DebugAlloc(SIZE_T Size, EMemoryCriticalLevel CriticalLevel, _In_ char* FileName, int LineNo, _Outptr_result_maybenull_ void** Mem);
        virtual HRESULT STDMETHODCALLTYPE Free(void* Mem);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CHostMAlloc(bool UseHeap);
		virtual ~CHostMAlloc(void);
};
//------------------------------------------------------------------------------------------------------