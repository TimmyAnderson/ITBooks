//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "ExternalConnectionObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CExternalConnectionObject::CExternalConnectionObject(void)
	: MReferenceCounter(0), MValue(0), MExternalReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CExternalConnectionObject::~CExternalConnectionObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CExternalConnectionObject::IncrementValue(void)
{
	CLock														Lock(MCS);

	MValue++;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CExternalConnectionObject::GetValue(long* Value)
{
	CLock														Lock(MCS);

	*Value=MValue;

	wprintf_s(L"!!!!! SERVER VALUE: [%d] !\n",MValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// !!! POCET volani AddConnection() NEKORESPONDUJE 1:1 s poctom EXTERNYCH PROXIES. Avsak je GARANTOVANE, ze ak existuje aspon 1 EXTERNAL PROXY, tak hodnota COUNTER>0.
DWORD STDMETHODCALLTYPE CExternalConnectionObject::AddConnection(__in DWORD ExternalConnection, __in DWORD Reserved)
{
	DWORD														Result=0;

	// Treba skontrolovat tento BIT.
	if ((ExternalConnection & EXTCONN_STRONG)!=0)
	{
		wprintf_s(L">>>>>>>>>>>>>>>> AT LEAST 1 EXTERNAL OBJECT EXISTS !\n");

		Result=InterlockedIncrement(&MExternalReferenceCounter);
	}

	return(Result);
}
//------------------------------------------------------------------------------------------------------
// !!! POCET volani ReleaseConnection() NEKORESPONDUJE 1:1 s poctom EXTERNYCH PROXIES. Avsak je GARANTOVANE, ze ak neexistuje ani 1 EXTERNAL PROXY, tak hodnota COUNTER==0.
DWORD STDMETHODCALLTYPE CExternalConnectionObject::ReleaseConnection(__in DWORD ExternalConnection, __in DWORD Reserved, __in BOOL LastReleaseCloses)
{
	DWORD														Result=0;

	// Treba skontrolovat tento BIT.
	if ((ExternalConnection & EXTCONN_STRONG)!=0)
	{
		Result=InterlockedDecrement(&MExternalReferenceCounter);

		if (Result==0 && LastReleaseCloses!=FALSE)
		{
			// !!! Pri uvolneni POSLEDNEJ EXTERNAL CONNECTION je NUTNE volat CoDisconnectObject().
			CoDisconnectObject(static_cast<IUnknown*>(static_cast<IExternalConnectionTest*>(this)),0);

			wprintf_s(L"<<<<<<<<<<<<<< NO EXTERNAL OBJECTS EXIST !\n");
		}
	}

	return(Result);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CExternalConnectionObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IExternalConnectionTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IExternalConnectionTest)
	{
		*PointerToObject=static_cast<IExternalConnectionTest*>(this);
		AddRef();
		return(S_OK);
	}
	// !!! Implementujem aj IExternalConnection.
	else if (RIID==IID_IExternalConnection)
	{
		*PointerToObject=static_cast<IExternalConnection*>(this);
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
ULONG STDMETHODCALLTYPE CExternalConnectionObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CExternalConnectionObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------