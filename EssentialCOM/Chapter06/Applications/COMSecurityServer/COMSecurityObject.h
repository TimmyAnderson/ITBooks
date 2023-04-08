//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "COMSecurityServer_h.h"
//------------------------------------------------------------------------------------------------------
class CCOMSecurityObject : public IName
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		HANDLE													MProcessExitEvent;
		wchar_t*												MName;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetName(wchar_t* Name);
        virtual HRESULT STDMETHODCALLTYPE GetName(int BufferSize, wchar_t* Name);
		virtual HRESULT STDMETHODCALLTYPE PrintSecuritySettings(void);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CCOMSecurityObject(HANDLE ProcessExitEvent);
		virtual ~CCOMSecurityObject(void);
};
//------------------------------------------------------------------------------------------------------