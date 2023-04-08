//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "BothThreadingModelServer_h.h"
//------------------------------------------------------------------------------------------------------
class CBothThreadingModelObject : public IBothThreadingModelTest
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		long													MValue;

	public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue(void);
        virtual HRESULT STDMETHODCALLTYPE GetValue(long* Value);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CBothThreadingModelObject(void);
		virtual ~CBothThreadingModelObject(void);
};
//------------------------------------------------------------------------------------------------------