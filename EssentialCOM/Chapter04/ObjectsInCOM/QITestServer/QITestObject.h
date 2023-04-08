//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "QITestServer_h.h"
//------------------------------------------------------------------------------------------------------
class CQITestObject : public IGetText1, public IGetText2, public IGetText3
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE GetText1(int BufferSize, wchar_t** Text);
        virtual HRESULT STDMETHODCALLTYPE GetText2(int BufferSize, wchar_t** Text);
        virtual HRESULT STDMETHODCALLTYPE GetText3(int BufferSize, wchar_t** Text);

	public:
        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        ULONG STDMETHODCALLTYPE AddRef(void);
        ULONG STDMETHODCALLTYPE Release(void);

	public:
		CQITestObject(void);
		virtual ~CQITestObject(void);
};
//------------------------------------------------------------------------------------------------------