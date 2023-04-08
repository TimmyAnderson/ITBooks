//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "COMSecurityObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CCOMSecurityObject::CCOMSecurityObject(HANDLE ProcessExitEvent)
	: MReferenceCounter(0), MProcessExitEvent(ProcessExitEvent), MName(NULL)
{
	// !!! V EXE SERVER je nutne zaregistrovat COM OBJECT pomocou FUNCTION CoAddRefServerProcess().
	CoAddRefServerProcess();
}
//------------------------------------------------------------------------------------------------------
CCOMSecurityObject::~CCOMSecurityObject(void)
{
	// !!! V EXE SERVER je NUTNE ODREGISTROVAT COM OBJECT. RETURN VALUE FUNCTION (CoReleaseServerProcess() informuje ci je NUTNE UKONCIT EXE COM HOST. Ak vrati hodnotu 0, tak je EXE COM HOST mozne ukoncit.
	if (CoReleaseServerProcess()==0)
	{
		// !!! Signalizujem, ze OUT-OF-PROCESS SERVER MOZE SKONCIT odpalenim EVENTU na ktory caka MAIN THREAD.
		SetEvent(MProcessExitEvent);
	}

	MProcessExitEvent=NULL;

	if (MName!=NULL)
	{
		delete[](MName);
		MName=NULL;
	}

	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCOMSecurityObject::SetName(wchar_t* Name)
{
	CLock														Lock(MCS);

	if (MName!=NULL)
	{
		delete[](MName);
		MName=NULL;
	}

	size_t														Length=wcslen(Name)+1;

	MName=new wchar_t[Length];
	wcscpy_s(MName,Length,Name);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCOMSecurityObject::GetName(int BufferSize, wchar_t* Name)
{
	CLock														Lock(MCS);

	if (MName!=NULL)
	{
		wcscpy_s(Name,BufferSize,MName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCOMSecurityObject::PrintSecuritySettings(void)
{
	CSmartCOMPointer<IServerSecurity>							ServerSecurity;

	if (SUCCEEDED(CoGetCallContext(__uuidof(IServerSecurity),(void**) &ServerSecurity)))
	{
		DWORD													AuthnSvc;
		DWORD													AuthzSvc;
		OLECHAR*												ServerPrincName=NULL;
		DWORD													AuthnLevel;
		DWORD													ImpLevel;
		RPC_AUTH_IDENTITY_HANDLE								AuthInfo=NULL;
		DWORD													Capabilites;

		if (SUCCEEDED(ServerSecurity->QueryBlanket(&AuthnSvc,&AuthzSvc,&ServerPrincName,&AuthnLevel,&ImpLevel,&AuthInfo,&Capabilites)))
		{
			// !!! Hodnoty su uvedene v dokumentacii.
			wprintf_s(L"\tAuthnSvc: [%d] !\n",AuthnSvc);
			wprintf_s(L"\tAuthzSvc: [%d] !\n",AuthzSvc);
			wprintf_s(L"\tServerPrincName: [%s] !\n",ServerPrincName);
			wprintf_s(L"\tAuthnLevel: [%d] !\n",AuthnLevel);
			wprintf_s(L"\tImpLevel: [%d] !\n",ImpLevel);
			wprintf_s(L"\tAuthInfo: [%p] !\n",AuthInfo);
			wprintf_s(L"\tCapabilites: [%d] !\n",Capabilites);

			if (ServerPrincName!=NULL)
			{
				CoTaskMemFree(ServerPrincName);
				ServerPrincName=NULL;
			}

			if (AuthnSvc==RPC_C_AUTHN_WINNT)
			{
				if (AuthInfo!=NULL)
				{
					// Pri RPC_C_AUTHN_WINNT obsahuje 'AuthInfo' STRING s CALLER CREDENTIALS.
					wprintf_s(L"\tAuthInfo: [%s] !\n",AuthInfo);
				}
			}
		}
		else
		{
			wprintf_s(L"Can't QUERY BLANKET !\n");
		}
	}
	else
	{
		wprintf_s(L"Can't get CALL CONTEXT !\n");
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCOMSecurityObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IName*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IName)
	{
		*PointerToObject=static_cast<IName*>(this);
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
ULONG STDMETHODCALLTYPE CCOMSecurityObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CCOMSecurityObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------