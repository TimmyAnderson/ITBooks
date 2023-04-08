//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
// !!! CUSTOM implementacia IHostControl.
class CMyHostControl : public IHostControl
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE GetHostManager(REFIID RIID, void** PointerToObject);
        virtual HRESULT STDMETHODCALLTYPE SetAppDomainManager(DWORD AppDomainID, IUnknown* UnkAppDomainManager);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMyHostControl(void);
		virtual ~CMyHostControl(void);
};
//------------------------------------------------------------------------------------------------------