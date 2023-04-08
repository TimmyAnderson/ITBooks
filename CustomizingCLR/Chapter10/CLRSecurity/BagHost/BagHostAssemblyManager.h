//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "BagHostAssemblyStore.h"
//------------------------------------------------------------------------------------------------------
class CBagHostAssemblyManager : public IHostAssemblyManager
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		CSmartCOMPointer<IHostAssemblyStore>					MHostAssemblyStore;
		CSmartCOMPointer<ICLRAssemblyIdentityManager>			MAssemblyIdentityManager;

	public:
        virtual HRESULT STDMETHODCALLTYPE GetNonHostStoreAssemblies(ICLRAssemblyReferenceList** ReferenceList);
        virtual HRESULT STDMETHODCALLTYPE GetAssemblyStore(IHostAssemblyStore** AssemblyStore);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CBagHostAssemblyManager(CSmartCOMPointer<ICLRAssemblyIdentityManager> AssemblyIdentityManager, CBagFileRecords* BagFileRecords);
		~CBagHostAssemblyManager(void);
};
//------------------------------------------------------------------------------------------------------