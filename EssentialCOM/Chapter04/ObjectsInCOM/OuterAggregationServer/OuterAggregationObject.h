//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "OuterAggregationObject_h.h"
//------------------------------------------------------------------------------------------------------
class COuterAggregationObject : public IOuterAggregationText
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		IUnknown*												MInnerCOMObject;

	private:
		wchar_t*												MText;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetText(wchar_t* Text);
        virtual HRESULT STDMETHODCALLTYPE GetText(int BufferSize, wchar_t** Text);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		HRESULT CreateInnerCOMObject(void);

	public:
		COuterAggregationObject(void);
		virtual ~COuterAggregationObject(void);
};
//------------------------------------------------------------------------------------------------------