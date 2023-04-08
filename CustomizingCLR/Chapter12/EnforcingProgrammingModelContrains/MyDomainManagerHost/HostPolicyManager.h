//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
class CHostPolicyManager : public IHostPolicyManager
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;

	public:
        virtual HRESULT STDMETHODCALLTYPE OnDefaultAction(EClrOperation Operation, EPolicyAction Action);
        virtual HRESULT STDMETHODCALLTYPE OnTimeout(EClrOperation Operation, EPolicyAction Action);
        virtual HRESULT STDMETHODCALLTYPE OnFailure(EClrFailure Failure, EPolicyAction Action);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CHostPolicyManager(void);
		virtual ~CHostPolicyManager(void);
};
//------------------------------------------------------------------------------------------------------