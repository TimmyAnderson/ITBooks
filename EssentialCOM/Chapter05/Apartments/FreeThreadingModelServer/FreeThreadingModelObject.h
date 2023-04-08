//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "FreeThreadingModelServer_h.h"
//------------------------------------------------------------------------------------------------------
class CFreeThreadingModelObject : public IFreeThreadingModelTest
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
		CFreeThreadingModelObject(void);
		virtual ~CFreeThreadingModelObject(void);
};
//------------------------------------------------------------------------------------------------------