//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
class CMyMessageFilter : public IMessageFilter
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		long													MRejectCounter;

	public:
        virtual DWORD STDMETHODCALLTYPE HandleInComingCall(__in DWORD CallType, __in HTASK TaskCaller, __in DWORD TickCount, __in_opt LPINTERFACEINFO InterfaceInfo);
        virtual DWORD STDMETHODCALLTYPE RetryRejectedCall(__in HTASK TaskCallee, __in DWORD TickCount, __in DWORD RejectType);
        virtual DWORD STDMETHODCALLTYPE MessagePending(__in HTASK TaskCallee, __in DWORD TickCount, __in DWORD PendingType);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMyMessageFilter(void);
		virtual ~CMyMessageFilter(void);
};
//------------------------------------------------------------------------------------------------------