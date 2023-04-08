//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "BagHostAssemblyManager.h"
#include "Helpers\Lock.h"
#include "Helpers\Helpers.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "BagFileRecords.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CBagHostAssemblyManager::CBagHostAssemblyManager(CSmartCOMPointer<ICLRAssemblyIdentityManager> AssemblyIdentityManager, CBagFileRecords* BagFileRecords)
	: MReferenceCounter(0), MAssemblyIdentityManager(AssemblyIdentityManager)
{
	MHostAssemblyStore=new CBagHostAssemblyStore(BagFileRecords);
}
//------------------------------------------------------------------------------------------------------
CBagHostAssemblyManager::~CBagHostAssemblyManager(void)
{
	wprintf_s(L"!!!!!!!!!! HOST MANAGER COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CBagHostAssemblyManager::GetNonHostStoreAssemblies(ICLRAssemblyReferenceList** ReferenceList)
{
	CLock														Lock(MCS);

	LPCWSTR														AssembliesToLoadByCLR[]=
	{
		// !!! Standardne .NET ASSEMBLIES, ktore BagExecutable potrebuje k svojej cinnosti.
		L"mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=B77A5C561934E089",
		L"System, Version=4.0.0.0, Culture=neutral, PublicKeyToken=B77A5C561934E089",
		// !!! ASSEMBLY v ktorej je implementovany CUSTOM APP DOMAIN MANAGER.
		// !!!!! Program PEKNE FUNGUJE. To znamena, ze ked ODSTRANIM ASSEMBLY NAME BagAppDomainManager z tohto ARRAY, tak HOST zavola IHostAssemblyStore::ProvideAssembly() aby nacital tuto ASSEMBLY.
		// !!!!! BagAppDomainManager ma STRONG NAME.
		L"BagAppDomainManager, Version=1.0.0.0, Culture=neutral, PublicKeyToken=AE009311F56808A0"
	};

	HRESULT														HR;
	
	// !!! Vytvori ZOZNAM s ASSEMBLIES, ktore ma CLR sama nacitat.
	HR=MAssemblyIdentityManager->GetCLRAssemblyReferenceList(AssembliesToLoadByCLR,_countof(AssembliesToLoadByCLR),ReferenceList);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CBagHostAssemblyManager::GetAssemblyStore(IHostAssemblyStore** AssemblyStore)
{
	CLock														Lock(MCS);

	*AssemblyStore=MHostAssemblyStore.GetInterface();

	// !!!!! NESMIE sa volat AddRef(), inak dojde k MEMORY LEAK.
	//MHostAssemblyStore->AddRef();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CBagHostAssemblyManager::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostAssemblyManager*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostAssemblyManager*>(this);
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
ULONG STDMETHODCALLTYPE CBagHostAssemblyManager::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CBagHostAssemblyManager::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------