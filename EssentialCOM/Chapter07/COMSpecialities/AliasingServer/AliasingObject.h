//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "AliasingServer_h.h"
//------------------------------------------------------------------------------------------------------
class CAliasingObject : public IAliasingTest
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE Dummy(void);
        virtual HRESULT STDMETHODCALLTYPE FillArray(int ArraySize, int* ArrayLength, int* Array);
        virtual HRESULT STDMETHODCALLTYPE CallFunctionDefinedByCPPQuote(void);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CAliasingObject(void);
		virtual ~CAliasingObject(void);
};
//------------------------------------------------------------------------------------------------------