//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "HostMemoryManager.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "Helpers\Helpers.h"
#include "HostMAlloc.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CHostMemoryManager::CHostMemoryManager(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CHostMemoryManager::~CHostMemoryManager(void)
{
	wprintf_s(L"!!!!!!!!!! HOST MEMORY MANAGER COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::CreateMalloc(DWORD MallocType, IHostMalloc** Malloc)
{
	CLock														Lock(MCS);

	wprintf_s(L"CreateMalloc() was CALLED !\n");

	// !!!!! Instanciu tohto OBJECT CLR NEUVOLNI a sposobi maly 64 BYTES MEMORY LEAK.
	// !!!!! MUSI sa pouzivat HEAP MEMORY (true). Ak som to skusal s C++ HEAP (false) dochadzalo k OBROVSKYM MEMORY LEAKS.
	*Malloc=new CHostMAlloc(true);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::VirtualAlloc(void* Address, SIZE_T Size, DWORD AllocationType, DWORD Protect, EMemoryCriticalLevel CriticalLevel, void** Mem)
{
	CLock														Lock(MCS);

	wprintf_s(L"VirtualAlloc() was CALLED - Size [%d] !\n",Size);

	*Mem=::VirtualAlloc(Address,Size,AllocationType,Protect);

	if (Mem!=NULL)
	{
		return(S_OK);
	}
	else
	{
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::VirtualFree(LPVOID Address, SIZE_T Size, DWORD FreeType)
{
	CLock														Lock(MCS);

	wprintf_s(L"VirtualFree() was CALLED - Size [%d] !\n",Size);

	if (::VirtualFree(Address,Size,FreeType)!=FALSE)
	{
		return(S_OK);
	}
	else
	{
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::VirtualQuery(void* Address, void* Buffer, SIZE_T Length, SIZE_T* Result)
{
	CLock														Lock(MCS);

	wprintf_s(L"VirtualQuery() was CALLED - Length [%d] !\n",Length);

	*Result=::VirtualQuery(Address,(MEMORY_BASIC_INFORMATION*) Buffer,Length);

	if ((*Result)!=0)
	{
		return(S_OK);
	}
	else
	{
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::VirtualProtect(void* Address, SIZE_T Size, DWORD NewProtect, DWORD* OldProtect)
{
	CLock														Lock(MCS);

	wprintf_s(L"VirtualProtect() was CALLED - Size [%d] !\n",Size);

	if (::VirtualProtect(Address,Size,NewProtect,OldProtect)!=FALSE)
	{
		return(S_OK);
	}
	else
	{
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::GetMemoryLoad(DWORD* MemoryLoad, SIZE_T* AvailableBytes)
{
	CLock														Lock(MCS);

	wprintf_s(L"GetMemoryLoad() was CALLED !\n");

	MEMORYSTATUS												MS;

	GlobalMemoryStatus(&MS);

	*MemoryLoad=MS.dwMemoryLoad;
	*AvailableBytes=MS.dwAvailPhys;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::RegisterMemoryNotificationCallback(ICLRMemoryNotificationCallback* Callback)
{
	CLock														Lock(MCS);

	wprintf_s(L"RegisterMemoryNotificationCallback() was CALLED !\n");

	// !!! Neviem ci by sa tu nemal volat AddRef().
	MCLRMemoryNotificationCallback=Callback;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::NeedsVirtualAddressSpace(LPVOID StartAddress, SIZE_T Size)
{
	CLock														Lock(MCS);

	wprintf_s(L"NeedsVirtualAddressSpace() was CALLED - Size [%d] !\n",Size);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::AcquiredVirtualAddressSpace(LPVOID StartAddress, SIZE_T Size)
{
	CLock														Lock(MCS);

	wprintf_s(L"AcquiredVirtualAddressSpace() was CALLED - Size [%d] !\n",Size);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::ReleasedVirtualAddressSpace(LPVOID StartAddress)
{
	CLock														Lock(MCS);

	wprintf_s(L"ReleasedVirtualAddressSpace() was CALLED !\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMemoryManager::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostMemoryManager*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostMemoryManager*>(this);
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
ULONG STDMETHODCALLTYPE CHostMemoryManager::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CHostMemoryManager::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------