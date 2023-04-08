//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "HostMAlloc.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CHostMAlloc::CHostMAlloc(bool UseHeap)
	: MReferenceCounter(0), MUseHeap(UseHeap)
{
}
//------------------------------------------------------------------------------------------------------
CHostMAlloc::~CHostMAlloc(void)
{
	wprintf_s(L"!!!!!!!!!! HOST MALLOC COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMAlloc::Alloc(SIZE_T Size, EMemoryCriticalLevel CriticalLevel, void** Mem)
{
	CLock														Lock(MCS);

	wprintf_s(L"Alloc() was CALLED - Size [%d] !\n",Size);

	if (MUseHeap==false)
	{
		// !!!!! NEPOUZIVAT. SPOSOBUJE MEMORY LEAKS.
		*Mem=new BYTE[Size];

		return(S_OK);
	}
	else
	{
		// !!!!! NESPOSOBUJE MEMORY LEAKS.
		if ((*Mem=HeapAlloc(GetProcessHeap(),0,Size))!=NULL)
		{
			return(S_OK);
		}
		else
		{
			return(E_FAIL);
		}
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMAlloc::DebugAlloc(SIZE_T Size, EMemoryCriticalLevel CriticalLevel, _In_ char* FileName, int LineNo, _Outptr_result_maybenull_ void** Mem)
{
	CLock														Lock(MCS);

	wprintf_s(L"DebugAlloc() was CALLED - Size [%d] !\n",Size);

	if (MUseHeap==false)
	{
		// !!!!! NEPOUZIVAT. SPOSOBUJE MEMORY LEAKS.
		*Mem=new BYTE[Size];

		return(S_OK);
	}
	else
	{
		// !!!!! NESPOSOBUJE MEMORY LEAKS.
		if ((*Mem=HeapAlloc(GetProcessHeap(),0,Size))!=NULL)
		{
			return(S_OK);
		}
		else
		{
			return(E_FAIL);
		}
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMAlloc::Free(void* Mem)
{
	CLock														Lock(MCS);

	wprintf_s(L"Free() was CALLED !\n");

	if (MUseHeap==false)
	{
		// !!!!! NEPOUZIVAT. SPOSOBUJE MEMORY LEAKS.
		delete[](Mem);

		return(S_OK);
	}
	else
	{
		// !!!!! NESPOSOBUJE MEMORY LEAKS.
		if ((HeapFree(GetProcessHeap(),0,Mem))!=NULL)
		{
			return(S_OK);
		}
		else
		{
			return(E_FAIL);
		}
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostMAlloc::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostMalloc*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostMalloc*>(this);
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
ULONG STDMETHODCALLTYPE CHostMAlloc::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CHostMAlloc::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------