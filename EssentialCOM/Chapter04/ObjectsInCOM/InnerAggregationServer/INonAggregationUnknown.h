//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
//------------------------------------------------------------------------------------------------------
// !!! Poradie METHODS musi byt ROVNAKE ako IUnknown.
class INonAggregationUnknown
{
	public:
		virtual HRESULT STDMETHODCALLTYPE NonAggregationUnknown_QueryInterface(REFIID RIID, void** PointerToObject)=0;
		virtual ULONG STDMETHODCALLTYPE NonAggregationUnknown_AddRef(void)=0;
		virtual ULONG STDMETHODCALLTYPE NonAggregationUnknown_Release(void)=0;
};
//------------------------------------------------------------------------------------------------------