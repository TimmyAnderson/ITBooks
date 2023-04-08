//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "AsynchronousMethodsServer_h.h"
//------------------------------------------------------------------------------------------------------
// !!! COM INTERFACE AsyncIAsynchronousMethodsTest predstavuje ASYNCHRONNU VERZIU COM INTERFACE IAsynchronousMethodsTest.
class CAsynchronousMethodsObject : public IAsynchronousMethodsTest, public AsyncIAsynchronousMethodsTest
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		bstr_t													MValue;

	public:
		// SYNCHRONNE METHODS.
        virtual HRESULT STDMETHODCALLTYPE SetValue(BSTR Value);
        virtual HRESULT STDMETHODCALLTYPE GetValue(BSTR* Value);

	public:
		// ASYNCHRONNE METHODS.
        virtual HRESULT STDMETHODCALLTYPE Begin_SetValue(BSTR Value);
        virtual HRESULT STDMETHODCALLTYPE Finish_SetValue(void);
        virtual HRESULT STDMETHODCALLTYPE Begin_GetValue(void);
        virtual HRESULT STDMETHODCALLTYPE Finish_GetValue(BSTR* Value);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CAsynchronousMethodsObject(void);
		virtual ~CAsynchronousMethodsObject(void);
};
//------------------------------------------------------------------------------------------------------