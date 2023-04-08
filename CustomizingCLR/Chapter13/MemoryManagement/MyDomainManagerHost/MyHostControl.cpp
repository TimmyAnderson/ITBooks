//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyHostControl.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CMyHostControl::CMyHostControl(void)
	: MReferenceCounter(0), MDefaultAppDomainManager(NULL), MAppDomainManagerMap()
{
	MHostPolicyManager=new CHostPolicyManager();
	MHostMemoryManager=new CHostMemoryManager();
	MHostGCManager=new CHostGCManager();
}
//------------------------------------------------------------------------------------------------------
CMyHostControl::~CMyHostControl(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
IMyDomainAppManager* CMyHostControl::GetDefaultAppDomainManager(void)
{
	return(MDefaultAppDomainManager);
}
//------------------------------------------------------------------------------------------------------
const std::map<DWORD,IMyDomainAppManager*>& CMyHostControl::GetAppDomainManagerMap(void) const
{
	return(MAppDomainManagerMap);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyHostControl::GetHostManager(REFIID RIID, void** PointerToObject)
{
	CLock														Lock(MCS);

	wprintf_s(L"HOST MANAGER [%s] REQUESTED !\n",CHelpers::ConvertGuidToString(RIID).c_str());

	if (RIID==__uuidof(IHostPolicyManager))
	{
		wprintf_s(L"HOST MANAGER [%s] RETURNED !\n",CHelpers::ConvertGuidToString(RIID).c_str());

		*PointerToObject=MHostPolicyManager.GetInterface();

		// !!!!! NESMIE sa volat AddRef(), inak dojde k MEMORY LEAK.
		//MHostAssemblyManager->AddRef();

		return(S_OK);
	}

	if (RIID==__uuidof(IHostMemoryManager))
	{
		wprintf_s(L"HOST MANAGER [%s] RETURNED !\n",CHelpers::ConvertGuidToString(RIID).c_str());

		*PointerToObject=MHostMemoryManager.GetInterface();

		// !!!!! NESMIE sa volat AddRef(), inak dojde k MEMORY LEAK.
		//MHostAssemblyManager->AddRef();

		return(S_OK);
	}

	if (RIID==__uuidof(IHostGCManager))
	{
		wprintf_s(L"HOST MANAGER [%s] RETURNED !\n",CHelpers::ConvertGuidToString(RIID).c_str());

		*PointerToObject=MHostGCManager.GetInterface();

		// !!!!! NESMIE sa volat AddRef(), inak dojde k MEMORY LEAK.
		//MHostAssemblyManager->AddRef();

		return(S_OK);
	}

	// !!! Kedze NEIMPLEMENTUJEM ZIADEN dalsi HOST MANAGER, tak pre VSETKY INTERFACES je vratena hodnota E_NOINTERFACE.
	return(E_NOINTERFACE);
}
//------------------------------------------------------------------------------------------------------
// !!!!! Tuto METHOD vola CLR pri KAZDOM VYTVORENI APP DOMAIN. Vtedy sa spolu s APP DOMAIN vytvara i asociovany APP DOMAIN MANAGER. POINTER na jeho CCW WRAPPER je zaslany do HOST, vdaka comu moze HOST komunikovat s danym CUSTOM APP DOMAIN MANAGER (a tym aj s asociovanou APP DOMAIN).
HRESULT STDMETHODCALLTYPE CMyHostControl::SetAppDomainManager(DWORD AppDomainID, IUnknown* UnkAppDomainManager)
{
	CLock														Lock(MCS);

	wprintf_s(L"CMyHostControl::SetAppDomainManager() CALLED !\n");

	// !!! MANAGED INTERFACE.
	IMyDomainAppManager*										TypedAppDomainManager=NULL;

	// !!!!! Kedze CUSTOM APP DOMAIN MANAGER CMyDomainAppManager implementuje COM INTERFACE (WRAPPER okolo MANAGED INTERFACE) IMyDomainAppManager, tak pomocou IUnknown::QueryInterface() mozem ziskat POINTER na tento COM INTERFACE (WRAPPER okolo MANAGED INTERFACE).
	if (FAILED(UnkAppDomainManager->QueryInterface(__uuidof(IMyDomainAppManager),(void**) &TypedAppDomainManager)))
	{
		wprintf_s(L"QueryInterface() for CUSTOM APP DOMAIN MANAGED FAILED !\n");
	}
	else
	{
		MAppDomainManagerMap[AppDomainID]=TypedAppDomainManager;

		// !!! Prvy APP DOMAIN MANAGER je APP DOMAIN MANAGER pre DEFAULT APP DOMAIN.
		if (MDefaultAppDomainManager==NULL)
		{
			MDefaultAppDomainManager=TypedAppDomainManager;
		}
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyHostControl::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostControl*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostControl*>(this);
		AddRef();
		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyHostControl::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyHostControl::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------