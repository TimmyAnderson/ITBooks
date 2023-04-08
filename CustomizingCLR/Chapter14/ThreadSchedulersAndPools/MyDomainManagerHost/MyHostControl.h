//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include <mscoree.h>
#include <map>
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "HostPolicyManager.h"
#include "HostGCManager.h"
#include "HostTaskManager.h"
//------------------------------------------------------------------------------------------------------
// !!! Importujem TYPE LIBRARY MANAGED ASSEMBLY vystavenu cez COM INTEROP.
#import "..\TLB\MyDomainManager.tlb"
//------------------------------------------------------------------------------------------------------
// !!! NAMESPACE z TYPE LIBRARY.
using namespace MyDomainManager;
//------------------------------------------------------------------------------------------------------
// !!! CUSTOM implementacia IHostControl.
class CMyHostControl : public IHostControl
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CSmartCOMPointer<IHostPolicyManager>					MHostPolicyManager;
		CSmartCOMPointer<IHostGCManager>						MHostGCManager;
		CSmartCOMPointer<IHostTaskManager>						MHostTaskManager;

	private:
		CCriticalSectionWrapper									MCS;
		// !!! Obsahuje POINTER na CUSTOM APP DOMAIN MANAGER pre DEFAULT APP DOMAIN.
		IMyDomainAppManager*									MDefaultAppDomainManager;
		// !!! Pre KAZDU APP DOMAIN bude FIELD obsahovat jeho CUSTOM APP DOMAIN MANAGER.
		std::map<DWORD,IMyDomainAppManager*>					MAppDomainManagerMap;

	public:
		IMyDomainAppManager* GetDefaultAppDomainManager(void);
		const std::map<DWORD,IMyDomainAppManager*>& GetAppDomainManagerMap(void) const;

	public:
        virtual HRESULT STDMETHODCALLTYPE GetHostManager(REFIID RIID, void** PointerToObject);
		// !!!!! Tuto METHOD vola CLR pri KAZDOM VYTVORENI APP DOMAIN. Vtedy sa spolu s APP DOMAIN vytvara i asociovany APP DOMAIN MANAGER. POINTER na jeho CCW WRAPPER je zaslany do HOST, vdaka comu moze HOST komunikovat s danym CUSTOM APP DOMAIN MANAGER (a tym aj s asociovanou APP DOMAIN).
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