//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "ComponentCategoriesObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CComponentCategoriesObject::CComponentCategoriesObject(void)
	: MReferenceCounter(0), MFirstName(NULL), MLastName(NULL), MAge(0)
{
}
//------------------------------------------------------------------------------------------------------
CComponentCategoriesObject::~CComponentCategoriesObject(void)
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
HRESULT STDMETHODCALLTYPE CComponentCategoriesObject::SetFirstName(wchar_t* FirstName)
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
HRESULT STDMETHODCALLTYPE CComponentCategoriesObject::SetLastName(wchar_t* LastName)
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
HRESULT STDMETHODCALLTYPE CComponentCategoriesObject::SetAge(int Age)
{
	CLock														Lock(MCS);

	MAge=Age;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CComponentCategoriesObject::GetFirstName(int BufferSize, wchar_t** FirstName)
{
	CLock														Lock(MCS);

	if (MFirstName!=NULL)
	{
		wcscpy_s(*FirstName,BufferSize,MFirstName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CComponentCategoriesObject::GetLastName(int BufferSize, wchar_t** LastName)
{
	CLock														Lock(MCS);

	if (MLastName!=NULL)
	{
		wcscpy_s(*LastName,BufferSize,MLastName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CComponentCategoriesObject::GetAge(int *Age)
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
HRESULT STDMETHODCALLTYPE CComponentCategoriesObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IComponentCategoriesName*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IComponentCategoriesName)
	{
		*PointerToObject=static_cast<IComponentCategoriesName*>(this);
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
ULONG STDMETHODCALLTYPE CComponentCategoriesObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CComponentCategoriesObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------