//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "ExternalConnectionServer_h.h"
//------------------------------------------------------------------------------------------------------
// !!! Implementujem aj IExternalConnection.
class CExternalConnectionObject : public IExternalConnectionTest, public IExternalConnection
{
	private:
		volatile ULONG											MReferenceCounter;
		// !!! Vyuziva ho IExternalConnection.
		volatile ULONG											MExternalReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		long													MValue;

	public:
        virtual HRESULT STDMETHODCALLTYPE IncrementValue(void);
        virtual HRESULT STDMETHODCALLTYPE GetValue(long* Value);

	public:
        virtual DWORD STDMETHODCALLTYPE AddConnection(__in DWORD ExternalConnection, __in DWORD Reserved);
        virtual DWORD STDMETHODCALLTYPE ReleaseConnection(__in DWORD ExternalConnection, __in DWORD Reserved, __in BOOL LastReleaseCloses);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CExternalConnectionObject(void);
		virtual ~CExternalConnectionObject(void);
};
//------------------------------------------------------------------------------------------------------