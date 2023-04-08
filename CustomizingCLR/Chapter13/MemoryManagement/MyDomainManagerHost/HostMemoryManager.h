//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include "Helpers\CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
class CHostMemoryManager : public IHostMemoryManager
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		ICLRMemoryNotificationCallback*							MCLRMemoryNotificationCallback;

	public:
        virtual HRESULT STDMETHODCALLTYPE CreateMalloc(DWORD MallocType, IHostMalloc** Malloc);
        virtual HRESULT STDMETHODCALLTYPE VirtualAlloc(void* Address, SIZE_T Size, DWORD AllocationType, DWORD Protect, EMemoryCriticalLevel CriticalLevel, void** Mem);
        virtual HRESULT STDMETHODCALLTYPE VirtualFree(LPVOID Address, SIZE_T Size, DWORD FreeType);
        virtual HRESULT STDMETHODCALLTYPE VirtualQuery(void* Address, void* Buffer, SIZE_T Length, SIZE_T* Result);
        virtual HRESULT STDMETHODCALLTYPE VirtualProtect(void* Address, SIZE_T Size, DWORD NewProtect, DWORD* OldProtect);
        virtual HRESULT STDMETHODCALLTYPE GetMemoryLoad(DWORD* MemoryLoad, SIZE_T* AvailableBytes);
        virtual HRESULT STDMETHODCALLTYPE RegisterMemoryNotificationCallback(ICLRMemoryNotificationCallback* Callback);
        virtual HRESULT STDMETHODCALLTYPE NeedsVirtualAddressSpace(LPVOID StartAddress, SIZE_T Size);
        virtual HRESULT STDMETHODCALLTYPE AcquiredVirtualAddressSpace(LPVOID StartAddress, SIZE_T Size);
        virtual HRESULT STDMETHODCALLTYPE ReleasedVirtualAddressSpace(LPVOID StartAddress);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CHostMemoryManager(void);
		virtual ~CHostMemoryManager(void);
};
//------------------------------------------------------------------------------------------------------