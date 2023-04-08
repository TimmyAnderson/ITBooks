//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "InnerAggregationObject_h.h"
#include "INonAggregationUnknown.h"
//------------------------------------------------------------------------------------------------------
// !!!!! COM OBJECT MUSI implementovat INonAggregationUnknown.
class CInnerAggregationObject : public IInnerAggregationText, public INonAggregationUnknown
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		// !!! POINTER na OUTER COM OBJECT.
		IUnknown*												MOuterCOMObject;

	private:
		wchar_t*												MText;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetText(wchar_t* Text);
        virtual HRESULT STDMETHODCALLTYPE GetText(int BufferSize, wchar_t** Text);

	public:
		virtual HRESULT STDMETHODCALLTYPE NonAggregationUnknown_QueryInterface(REFIID RIID, void** PointerToObject);
		virtual ULONG STDMETHODCALLTYPE NonAggregationUnknown_AddRef(void);
		virtual ULONG STDMETHODCALLTYPE NonAggregationUnknown_Release(void);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CInnerAggregationObject(IUnknown* UnknownOuter);
		virtual ~CInnerAggregationObject(void);
};
//------------------------------------------------------------------------------------------------------