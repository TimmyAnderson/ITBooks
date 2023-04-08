//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include "StdAfx.h"
#include <stdio.h>
#include "MySimpleCOM.h"
//------------------------------------------------------------------------------------------------------
CMySimpleCOM::CMySimpleCOM(void)
	: MReferenceCounter(0)
{
	InitializeCriticalSection(&MCS);

	MIntValue=12;
	MStringValue=L"Timmy Anderson";
}
//------------------------------------------------------------------------------------------------------
CMySimpleCOM::~CMySimpleCOM(void)
{
	DeleteCriticalSection(&MCS);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMySimpleCOM::QueryInterface(REFIID RIID, void **PPVObject)
{
	if (RIID==IID_IUnknown)
	{
		*PPVObject=static_cast<IUnknown*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMySimpleInterface)
	{
		*PPVObject=static_cast<IMySimpleInterface*>(this);
		AddRef();
		return(S_OK);
	}
	else
	{
		*PPVObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMySimpleCOM::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMySimpleCOM::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT CMySimpleCOM::GetInt(int* Value)
{
	wprintf_s(L"GetInt() CALLED !\n");

	EnterCriticalSection(&MCS);

	try
	{
		*Value=MIntValue;

		LeaveCriticalSection(&MCS);

		return(S_OK);
	}
	catch(...)
	{
		LeaveCriticalSection(&MCS);
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT CMySimpleCOM::SetInt(int Value)
{
	wprintf_s(L"SetInt() CALLED !\n");

	EnterCriticalSection(&MCS);

	try
	{
		MIntValue=Value;

		LeaveCriticalSection(&MCS);
	}
	catch(...)
	{
		LeaveCriticalSection(&MCS);
		return(E_FAIL);
	}

	wprintf_s(L"INT was set to [%d] !\n",MIntValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT CMySimpleCOM::GetString(BSTR* Value)
{
	wprintf_s(L"GetString() CALLED !\n");

	EnterCriticalSection(&MCS);

	try
	{
		BSTR													StringCopy=MStringValue.copy();

		*Value=StringCopy;

		LeaveCriticalSection(&MCS);

		return(S_OK);
	}
	catch(...)
	{
		LeaveCriticalSection(&MCS);
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT CMySimpleCOM::SetString(BSTR Value)
{
	wprintf_s(L"SetString() CALLED !\n");

	EnterCriticalSection(&MCS);

	try
	{
		MStringValue=Value;

		LeaveCriticalSection(&MCS);
	}
	catch(...)
	{
		LeaveCriticalSection(&MCS);
		return(E_FAIL);
	}

	wprintf_s(L"STRING was set to [%s] !\n",static_cast<wchar_t*>(MStringValue));

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------