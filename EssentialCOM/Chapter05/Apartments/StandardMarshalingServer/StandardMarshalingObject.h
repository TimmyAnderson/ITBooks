//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "StandardMarshalingServer_h.h"
//------------------------------------------------------------------------------------------------------
class CStandardMarshalingObject : public IStandardMarshalingTest
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
		CStandardMarshalingObject(void);
		virtual ~CStandardMarshalingObject(void);
};
//------------------------------------------------------------------------------------------------------