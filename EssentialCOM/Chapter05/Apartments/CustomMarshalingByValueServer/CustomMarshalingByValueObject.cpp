//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CustomMarshalingByValueObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CCustomMarshalingByValueObject::CCustomMarshalingByValueObject(void)
	: MReferenceCounter(0), MValue(0)
{
}
//------------------------------------------------------------------------------------------------------
CCustomMarshalingByValueObject::~CCustomMarshalingByValueObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByValueObject::SetValue(long Value)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	MValue=Value;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByValueObject::GetValue(long* Value)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.

	*Value=MValue;

	wprintf_s(L"!!!!! SERVER VALUE: [%d] !\n",MValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByValueObject::GetUnmarshalClass(__in REFIID RIID, __in_opt void* PointerToObject, __in DWORD DestContext, __reserved void* ReservedDestContext, __in DWORD Flags, __out CLSID* CID)
{
	wprintf_s(L"MARSHALLING METHODS GetUnmarshalClass() CALLED !\n");

	// !!!!! Ako PROXY OBJECT sa pouzije THIS.
	// !!!!! To znaci, ze aj METHOD CCustomMarshalingByReferenceObject::UnmarshalInterface() v DESTINATION APARTMENT BUDE VOLANA. Takisto sa vola CCustomMarshalingByReferenceObject::GetMarshalSizeMax().
	*CID=CLSID_CustomMarshalingByValueObject;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByValueObject::GetMarshalSizeMax(__in REFIID RIID, __in_opt void* PointerToObject, __in DWORD DestContext, __reserved void* ReservedDestContext, __in DWORD Flags, __out DWORD* Size)
{
	wprintf_s(L"MARSHALLING METHODS GetMarshalSizeMax() CALLED !\n");

	// !!! Kedze COM OBJECT obsahuje iba 1 LONG FIELD, tak staci alokovat tuto velkost 
	*Size+=sizeof(MValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByValueObject::MarshalInterface(__in IStream* Stream, __in REFIID RIID, __in_opt void* PointerToObject, __in DWORD DestContext, __reserved void* ReservedDestContext, __in DWORD Flags)
{
	HRESULT														HR;

	wprintf_s(L"MARSHALLING METHODS MarshalInterface() CALLED !\n");

	// !!!!! Do STREAM sa zapise MValue.
	HR=Stream->Write(&MValue,sizeof(MValue),NULL);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByValueObject::UnmarshalInterface(__in IStream* Stream, __in REFIID RIID, __deref_out void** PointerToObject)
{
	HRESULT														HR;

	wprintf_s(L"MARSHALLING METHODS UnmarshalInterface() CALLED !\n");

	// !!!!! Hodnota MValue sa cita zo STRAEMU, kde som ju ulozil v CCustomMarshalingByReferenceObject::MarshalInterface() a miesto pre ne v STREAM som alokoval v CCustomMarshalingByReferenceObject::GetMarshalSizeMax().
	if (SUCCEEDED(HR=Stream->Read(&MValue,sizeof(MValue),NULL)))
	{
		// !!! Musim naplnit PointerToObject. Kedze THIS sluzi ako PROXY, tak volam QueryInterface().
		HR=QueryInterface(RIID,PointerToObject);
	}

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByValueObject::ReleaseMarshalData(__in IStream* Stream)
{
	wprintf_s(L"MARSHALLING METHODS ReleaseMarshalData() CALLED !\n");

	// !!! NEIMPLEMENTUJEM ju, kedze v priklade sa NEPOUZIVA.
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByValueObject::DisconnectObject(__in DWORD Reserved)
{
	wprintf_s(L"MARSHALLING METHODS DisconnectObject() CALLED !\n");

	// !!! NEIMPLEMENTUJEM ju, kedze v priklade sa NEPOUZIVA.
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByValueObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<ICustomMarshalingByValueTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_ICustomMarshalingByValueTest)
	{
		*PointerToObject=static_cast<ICustomMarshalingByValueTest*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMarshal)
	{
		*PointerToObject=static_cast<IMarshal*>(this);
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
ULONG STDMETHODCALLTYPE CCustomMarshalingByValueObject::AddRef(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	ULONG														Ret=++MReferenceCounter;

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CCustomMarshalingByValueObject::Release(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	ULONG														Ret=--MReferenceCounter;

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------