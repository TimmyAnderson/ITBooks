//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "SingletonObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CSingletonObject::CSingletonObject(void)
	: MFirstName(NULL), MLastName(NULL), MAge(0)
{
}
//------------------------------------------------------------------------------------------------------
CSingletonObject::~CSingletonObject(void)
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
HRESULT STDMETHODCALLTYPE CSingletonObject::SetFirstName(wchar_t* FirstName)
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
HRESULT STDMETHODCALLTYPE CSingletonObject::SetLastName(wchar_t* LastName)
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
HRESULT STDMETHODCALLTYPE CSingletonObject::SetAge(int Age)
{
	CLock														Lock(MCS);

	MAge=Age;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CSingletonObject::GetFirstName(int BufferSize, wchar_t** FirstName)
{
	CLock														Lock(MCS);

	if (MFirstName!=NULL)
	{
		wcscpy_s(*FirstName,BufferSize,MFirstName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CSingletonObject::GetLastName(int BufferSize, wchar_t** LastName)
{
	CLock														Lock(MCS);

	if (MLastName!=NULL)
	{
		wcscpy_s(*LastName,BufferSize,MLastName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CSingletonObject::GetAge(int *Age)
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
HRESULT STDMETHODCALLTYPE CSingletonObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<ISingletonName*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_ISingletonName)
	{
		*PointerToObject=static_cast<ISingletonName*>(this);
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
ULONG STDMETHODCALLTYPE CSingletonObject::AddRef(void)
{
	// !!! Kedze sa jedna o SINGLETON, instancie sa NEPOCITAJU.
	return(1);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CSingletonObject::Release(void)
{
	// !!! Kedze sa jedna o SINGLETON, instancie sa NEPOCITAJU.
	return(1);
}
//------------------------------------------------------------------------------------------------------