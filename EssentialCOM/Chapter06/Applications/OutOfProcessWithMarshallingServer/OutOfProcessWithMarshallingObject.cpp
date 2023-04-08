//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "OutOfProcessWithMarshallingObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
COutOfProcessWithMarshallingObject::COutOfProcessWithMarshallingObject(HANDLE ProcessExitEvent)
	: MReferenceCounter(0), MProcessExitEvent(ProcessExitEvent), MFirstName(NULL), MLastName(NULL), MAge(0)
{
	// !!! V EXE SERVER je nutne zaregistrovat COM OBJECT pomocou FUNCTION CoAddRefServerProcess().
	CoAddRefServerProcess();
}
//------------------------------------------------------------------------------------------------------
COutOfProcessWithMarshallingObject::~COutOfProcessWithMarshallingObject(void)
{
	// !!! V EXE SERVER je NUTNE ODREGISTROVAT COM OBJECT. RETURN VALUE FUNCTION (CoReleaseServerProcess() informuje ci je NUTNE UKONCIT EXE COM HOST. Ak vrati hodnotu 0, tak je EXE COM HOST mozne ukoncit.
	if (CoReleaseServerProcess()==0)
	{
		// !!! Signalizujem, ze OUT-OF-PROCESS SERVER MOZE SKONCIT odpalenim EVENTU na ktory caka MAIN THREAD.
		SetEvent(MProcessExitEvent);
	}

	MProcessExitEvent=NULL;

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

	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObject::SetFirstName(wchar_t* FirstName)
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
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObject::SetLastName(wchar_t* LastName)
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
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObject::SetAge(int Age)
{
	CLock														Lock(MCS);

	MAge=Age;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObject::GetFirstName(int BufferSize, wchar_t* FirstName)
{
	CLock														Lock(MCS);

	if (MFirstName!=NULL)
	{
		wcscpy_s(FirstName,BufferSize,MFirstName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObject::GetLastName(int BufferSize, wchar_t* LastName)
{
	CLock														Lock(MCS);

	if (MLastName!=NULL)
	{
		wcscpy_s(LastName,BufferSize,MLastName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObject::GetAge(int *Age)
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
HRESULT STDMETHODCALLTYPE COutOfProcessWithMarshallingObject::QueryInterface(REFIID RIID, void** PointerToObject)
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
ULONG STDMETHODCALLTYPE COutOfProcessWithMarshallingObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE COutOfProcessWithMarshallingObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------