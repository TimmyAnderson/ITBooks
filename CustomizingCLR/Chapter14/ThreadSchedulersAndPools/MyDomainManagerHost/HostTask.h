//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
class CHostTask : public IHostTask
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		HANDLE													MThreadHandle;
		DWORD													MThreadID;
		ICLRTask*												MCLRTask;

	public:
        virtual HRESULT STDMETHODCALLTYPE Start(void);
        virtual HRESULT STDMETHODCALLTYPE Alert(void);
        virtual HRESULT STDMETHODCALLTYPE Join(DWORD Milliseconds, DWORD Option);
        virtual HRESULT STDMETHODCALLTYPE SetPriority(int NewPriority);
        virtual HRESULT STDMETHODCALLTYPE GetPriority(int* Priority);
        virtual HRESULT STDMETHODCALLTYPE SetCLRTask(ICLRTask* CLRTask);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CHostTask(HANDLE ThreadHandle, DWORD ThreadID);
		virtual ~CHostTask(void);
};
//------------------------------------------------------------------------------------------------------