//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "..\UnmanagedCOMServer\UnmanagedCOMServer_h.h"
//------------------------------------------------------------------------------------------------------
class CUnmanagedCOMServerCallback : public IUnmanagedCOMServerCallback
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE SendMessageToClient(BSTR Message);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CUnmanagedCOMServerCallback(void);
		virtual ~CUnmanagedCOMServerCallback(void);
};
//------------------------------------------------------------------------------------------------------