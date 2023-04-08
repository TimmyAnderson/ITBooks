//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyItemMonikerObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CMyItemMonikerObject::CMyItemMonikerObject(void)
	: MReferenceCounter(0), MFirstName(NULL), MLastName(NULL), MAge(0)
{
}
//------------------------------------------------------------------------------------------------------
CMyItemMonikerObject::~CMyItemMonikerObject(void)
{
	if (MFirstName!=NULL)
	{
		delete[](MFirstName);
		MFirstName=NULL;
	}

	if (MLastName!=NULL)
	{
		delete[](MLastName);
		MLastName=NULL;
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObject::SetFirstName(wchar_t* FirstName)
{
	CLock														Lock(MCS);

	if (MFirstName!=NULL)
	{
		delete[](MFirstName);
		MFirstName=NULL;
	}

	size_t														Length=wcslen(FirstName)+1;

	MFirstName=new wchar_t[Length];
	wcscpy_s(MFirstName,Length,FirstName);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObject::SetLastName(wchar_t* LastName)
{
	CLock														Lock(MCS);

	if (MLastName!=NULL)
	{
		delete[](MLastName);
		MLastName=NULL;
	}

	size_t														Length=wcslen(LastName)+1;

	MLastName=new wchar_t[Length];
	wcscpy_s(MLastName,Length,LastName);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObject::SetAge(int Age)
{
	CLock														Lock(MCS);

	MAge=Age;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObject::GetFirstName(int BufferSize, wchar_t** FirstName)
{
	CLock														Lock(MCS);

	if (MFirstName!=NULL)
	{
		wcscpy_s(*FirstName,BufferSize,MFirstName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObject::GetLastName(int BufferSize, wchar_t** LastName)
{
	CLock														Lock(MCS);

	if (MLastName!=NULL)
	{
		wcscpy_s(*LastName,BufferSize,MLastName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObject::GetAge(int *Age)
{
	CLock														Lock(MCS);

	if (MAge!=0)
	{
		*Age=MAge;
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IMyItemMonikerName*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMyItemMonikerName)
	{
		*PointerToObject=static_cast<IMyItemMonikerName*>(this);
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
ULONG STDMETHODCALLTYPE CMyItemMonikerObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyItemMonikerObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------