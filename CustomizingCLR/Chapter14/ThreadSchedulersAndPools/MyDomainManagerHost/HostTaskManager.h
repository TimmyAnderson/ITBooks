//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include <map>
#include "HostTask.h"
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
class CHostTaskManager : public IHostTaskManager
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		std::map<HANDLE,CHostTask*>								MThreadMap;
		ICLRTaskManager*										MCLRTaskManager;

	public:
        virtual HRESULT STDMETHODCALLTYPE GetCurrentTask(IHostTask** Task);
        virtual HRESULT STDMETHODCALLTYPE CreateTask(DWORD StackSize, LPTHREAD_START_ROUTINE StartAddress, PVOID Parameter, IHostTask** Task);
        virtual HRESULT STDMETHODCALLTYPE Sleep(DWORD Milliseconds, DWORD Option);
        virtual HRESULT STDMETHODCALLTYPE SwitchToTask(DWORD Option);
        virtual HRESULT STDMETHODCALLTYPE SetUILocale(LCID LocaleID);
        virtual HRESULT STDMETHODCALLTYPE SetLocale(LCID LocaleID);
        virtual HRESULT STDMETHODCALLTYPE CallNeedsHostHook(SIZE_T Target, BOOL* CallNeedsHostHook);
        virtual HRESULT STDMETHODCALLTYPE LeaveRuntime(SIZE_T Target);
        virtual HRESULT STDMETHODCALLTYPE EnterRuntime(void);
        virtual HRESULT STDMETHODCALLTYPE ReverseLeaveRuntime(void);
        virtual HRESULT STDMETHODCALLTYPE ReverseEnterRuntime(void);
        virtual HRESULT STDMETHODCALLTYPE BeginDelayAbort(void);
        virtual HRESULT STDMETHODCALLTYPE EndDelayAbort(void);
        virtual HRESULT STDMETHODCALLTYPE BeginThreadAffinity(void);
        virtual HRESULT STDMETHODCALLTYPE EndThreadAffinity(void);
        virtual HRESULT STDMETHODCALLTYPE SetStackGuarantee(ULONG Guarantee);
        virtual HRESULT STDMETHODCALLTYPE GetStackGuarantee(ULONG* Guarantee);
        virtual HRESULT STDMETHODCALLTYPE SetCLRTaskManager(ICLRTaskManager* Manager);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CHostTaskManager(void);
		virtual ~CHostTaskManager(void);
};
//------------------------------------------------------------------------------------------------------