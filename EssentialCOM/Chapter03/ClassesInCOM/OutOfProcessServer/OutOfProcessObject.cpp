//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "OutOfProcessObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
COutOfProcessObject::COutOfProcessObject(HANDLE ProcessExitEvent)
	: MReferenceCounter(0), MProcessExitEvent(ProcessExitEvent), MFirstName(), MLastName(), MAge(0)
{
	// !!! V EXE SERVER je nutne zaregistrovat COM OBJECT pomocou FUNCTION CoAddRefServerProcess().
	CoAddRefServerProcess();
}
//------------------------------------------------------------------------------------------------------
COutOfProcessObject::~COutOfProcessObject(void)
{
	// !!! V EXE SERVER je NUTNE ODREGISTROVAT COM OBJECT. RETURN VALUE FUNCTION (CoReleaseServerProcess() informuje ci je NUTNE UKONCIT EXE COM HOST. Ak vrati hodnotu 0, tak je EXE COM HOST mozne ukoncit.
	if (CoReleaseServerProcess()==0)
	{
		// !!! Signalizujem, ze OUT-OF-PROCESS SERVER MOZE SKONCIT odpalenim EVENTU na ktory caka MAIN THREAD.
		SetEvent(MProcessExitEvent);
	}

	MProcessExitEvent=NULL;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessObject::SetFirstName(BSTR FirstName)
{
	CLock														Lock(MCS);

	MFirstName=FirstName;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessObject::SetLastName(BSTR LastName)
{
	CLock														Lock(MCS);

	MLastName=LastName;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessObject::SetAge(int Age)
{
	CLock														Lock(MCS);

	MAge=Age;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessObject::GetFirstName(BSTR* FirstName)
{
	CLock														Lock(MCS);

	*FirstName=MFirstName.copy();
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessObject::GetLastName(BSTR* LastName)
{
	CLock														Lock(MCS);

	*LastName=MLastName.copy();
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessObject::GetAge(int *Age)
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
HRESULT STDMETHODCALLTYPE COutOfProcessObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IOutOfProcessName*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IOutOfProcessName)
	{
		*PointerToObject=static_cast<IOutOfProcessName*>(this);
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
ULONG STDMETHODCALLTYPE COutOfProcessObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE COutOfProcessObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------