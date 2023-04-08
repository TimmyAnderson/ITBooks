//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
class CHostGCManager : public IHostGCManager
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE ThreadIsBlockingForSuspension(void);
        virtual HRESULT STDMETHODCALLTYPE SuspensionStarting(void);
        virtual HRESULT STDMETHODCALLTYPE SuspensionEnding(DWORD Generation);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CHostGCManager(void);
		virtual ~CHostGCManager(void);
};
//------------------------------------------------------------------------------------------------------