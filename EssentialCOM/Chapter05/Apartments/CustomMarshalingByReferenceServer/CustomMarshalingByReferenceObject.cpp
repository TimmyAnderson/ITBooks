//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CustomMarshalingByReferenceObject.h"
#include "Helpers\Lock.h"
//------------------------------------------------------------------------------------------------------
CCustomMarshalingByReferenceObject::CCustomMarshalingByReferenceObject(void)
	: MReferenceCounter(0), MValue(0)
{
}
//------------------------------------------------------------------------------------------------------
CCustomMarshalingByReferenceObject::~CCustomMarshalingByReferenceObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::IncrementValue(void)
{
	// !!!!! Kedze realizujem CUSTOM MARSHALING pricom THIS (CCustomMarshalingByReferenceObject) sluzi aj ako PROXY OBJECT, tak by tu mal byt UNIVERZALNY KOD, ktory v pripade, ze CLIENT a COM OBJECT APARTMENTS lezia v INYCH PROCESSES, alebo INYCH HOSTS by realizoval NETWORK COMMUNICATION z CLIENT na REMOTE COM OBJECT. Kedze vsak priklad demonstruje iba prechod medzi IN-PROCESS APARTMENTS, ktore maju SPOLOCNY ADDRESS SPACE, tak nie je NUTNA NEWTWORK COMMUNICATION a priamo z PROXY OBJECT (THIS) pristupujem k FIELDS 'REMOTE' COM OBJECT.

	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	MValue++;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::GetValue(long* Value)
{
	// !!!!! Kedze realizujem CUSTOM MARSHALING pricom THIS (CCustomMarshalingByReferenceObject) sluzi aj ako PROXY OBJECT, tak by tu mal byt UNIVERZALNY KOD, ktory v pripade, ze CLIENT a COM OBJECT APARTMENTS lezia v INYCH PROCESSES, alebo INYCH HOSTS by realizoval NETWORK COMMUNICATION z CLIENT na REMOTE COM OBJECT. Kedze vsak priklad demonstruje iba prechod medzi IN-PROCESS APARTMENTS, ktore maju SPOLOCNY ADDRESS SPACE, tak nie je NUTNA NEWTWORK COMMUNICATION a priamo z PROXY OBJECT (THIS) pristupujem k FIELDS 'REMOTE' COM OBJECT.

	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.

	*Value=MValue;

	wprintf_s(L"!!!!! SERVER VALUE: [%d] !\n",MValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::GetUnmarshalClass(__in REFIID RIID, __in_opt void* PointerToObject, __in DWORD DestContext, __reserved void* ReservedDestContext, __in DWORD Flags, __out CLSID* CID)
{
	HRESULT														HR=S_OK;
	CSmartCOMPointer<IMarshal>									StandardMarshaller;

	wprintf_s(L"MARSHALLING METHODS GetUnmarshalClass() CALLED !\n");

	/*
	// ALTERNATIVA 1.
	// !!!!! Ako PROXY OBJECT sa pouzije PROXY generovane STANDARD MARSHALLER.
	// !!!!! To znamena, ze PROXY je REALIZOVANE cez STANDARD MARSHALING a vola sa IBA METHOD CCustomMarshalingByReferenceObject::MarshalInterface(). METHODS CCustomMarshalingByReferenceObject::GetMarshalSizeMax() a CCustomMarshalingByReferenceObject::UnmarshalInterface() sa NEVOLAJU.
	if (SUCCEEDED(HR=CoGetStandardMarshal(RIID,(IUnknown*)PointerToObject,DestContext,ReservedDestContext,Flags,&StandardMarshaller)))
	{
		HRESULT													HR=StandardMarshaller->GetUnmarshalClass(RIID,PointerToObject,DestContext,ReservedDestContext,Flags,CID);

		return(HR);
	}
	else
	{
		return(HR);
	}
	*/

	// ALTERNATIVA 2.
	// !!!!! Ako PROXY OBJECT sa pouzije THIS.
	// !!!!! To znaci, ze aj METHOD CCustomMarshalingByReferenceObject::UnmarshalInterface() v DESTINATION APARTMENT BUDE VOLANA. Takisto sa vola CCustomMarshalingByReferenceObject::GetMarshalSizeMax().
	*CID=CLSID_CustomMarshalingByReferenceObject;

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::GetMarshalSizeMax(__in REFIID RIID, __in_opt void* PointerToObject, __in DWORD DestContext, __reserved void* ReservedDestContext, __in DWORD Flags, __out DWORD* Size)
{
	HRESULT														HR;
	CSmartCOMPointer<IMarshal>									StandardMarshaller;

	wprintf_s(L"MARSHALLING METHODS GetMarshalSizeMax() CALLED !\n");

	if (SUCCEEDED(HR=CoGetStandardMarshal(RIID,(IUnknown*)PointerToObject,DestContext,ReservedDestContext,Flags,&StandardMarshaller)))
	{
		HRESULT													HR=StandardMarshaller->GetMarshalSizeMax(RIID,PointerToObject,DestContext,ReservedDestContext,Flags,Size);

		// !!!!! Kedze do STREAM si zapisem CUSTOM DATA DestContext a Flags, ktore potrebujem pri UNMARSHALING v CCustomMarshalingByReferenceObject::UnmarshalInterface(), tak MUSI ZVACSIT STREAM.
		*Size+=sizeof(DestContext)+sizeof(Flags);

		return(HR);
	}
	else
	{
		return(HR);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::MarshalInterface(__in IStream* Stream, __in REFIID RIID, __in_opt void* PointerToObject, __in DWORD DestContext, __reserved void* ReservedDestContext, __in DWORD Flags)
{
	HRESULT														HR;
	CSmartCOMPointer<IMarshal>									StandardMarshaller;

	wprintf_s(L"MARSHALLING METHODS MarshalInterface() CALLED !\n");

	if (SUCCEEDED(HR=CoGetStandardMarshal(RIID,(IUnknown*)PointerToObject,DestContext,ReservedDestContext,Flags,&StandardMarshaller)))
	{
		// !!!!! Do STREAM si zapisem CUSTOM DATA. Su to DestContext a Flags, ktore potrebujem pri UNMARSHALING v CCustomMarshalingByReferenceObject::UnmarshalInterface().
		if (SUCCEEDED(HR=Stream->Write(&DestContext,sizeof(DestContext),NULL)))
		{
			if (SUCCEEDED(HR=Stream->Write(&Flags,sizeof(Flags),NULL)))
			{
				HR=StandardMarshaller->MarshalInterface(Stream,RIID,PointerToObject,DestContext,ReservedDestContext,Flags);
			}
		}

		return(HR);
	}
	else
	{
		return(HR);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::UnmarshalInterface(__in IStream* Stream, __in REFIID RIID, __deref_out void** PointerToObject)
{
	HRESULT														HR;
	CSmartCOMPointer<IMarshal>									StandardMarshaller;

	wprintf_s(L"MARSHALLING METHODS UnmarshalInterface() CALLED !\n");

	// ALTERNATIVA 1.
	// !!!!! Hodnoty MSHCTX_INPROC a MSHLFLAGS_NORMAL su ulozene NATVRDO v KODE.
	// !!!!! POZOR ak odkomentujem tento kod, tak MUSIM upravit aj CCustomMarshalingByReferenceObject::MarshalInterface() a CCustomMarshalingByReferenceObject::GetMarshalSizeMax(), aby NEUKLADALI DestContext a Flags do STREAM.
	/*
	// !!!!! Hodnoty MSHCTX_INPROC a MSHLFLAGS_NORMAL som dal NATVRDO, kedze tieto hodnoty sa pouzivaju pri CCustomMarshalingByReferenceObject::MarshalInterface().
	// ????? Predpokladam, ze hodnoty MSHCTX_INPROC a MSHLFLAGS_NORMAL by sa pri SKUTOCNOM CUSTOM MARSHALINGU mali vytiahnut z IStream.
	if (SUCCEEDED(HR=CoGetStandardMarshal(RIID,NULL,MSHCTX_INPROC,NULL,MSHLFLAGS_NORMAL,&StandardMarshaller)))
	{
		HR=StandardMarshaller->UnmarshalInterface(Stream,RIID,PointerToObject);

		return(HR);
	}
	else
	{
		return(HR);
	}
	*/

	// ALTERNATIVA 2.
	// !!!!! Hodnoty DestContext a Flags sa citaju zo STRAEMU, kde som ich ulozil v CCustomMarshalingByReferenceObject::MarshalInterface() a miesto pre ne v STREAM som alokoval v CCustomMarshalingByReferenceObject::GetMarshalSizeMax().
	DWORD														DestContext;
	DWORD														Flags;

	// !!!!! Nacitam CUSTOM data DestContext a Flags zo STREAM, kam som ich ulozil v CCustomMarshalingByReferenceObject::MarshalInterface() a miesto pred v STREAM som alokoval v CCustomMarshalingByReferenceObject::GetMarshalSizeMax().
	if (SUCCEEDED(HR=Stream->Read(&DestContext,sizeof(DestContext),NULL)))
	{
		if (SUCCEEDED(HR=Stream->Read(&Flags,sizeof(Flags),NULL)))
		{
			if (SUCCEEDED(HR=CoGetStandardMarshal(RIID,NULL,MSHCTX_INPROC,NULL,Flags,&StandardMarshaller)))
			{
				HR=StandardMarshaller->UnmarshalInterface(Stream,RIID,PointerToObject);

				return(HR);
			}
			else
			{
				return(HR);
			}
		}
	}

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::ReleaseMarshalData(__in IStream* Stream)
{
	wprintf_s(L"MARSHALLING METHODS ReleaseMarshalData() CALLED !\n");

	// !!! NEIMPLEMENTUJEM ju, kedze v priklade sa NEPOUZIVA.
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::DisconnectObject(__in DWORD Reserved)
{
	wprintf_s(L"MARSHALLING METHODS DisconnectObject() CALLED !\n");

	// !!! NEIMPLEMENTUJEM ju, kedze v priklade sa NEPOUZIVA.
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<ICustomMarshalingByReferenceTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_ICustomMarshalingByReferenceTest)
	{
		*PointerToObject=static_cast<ICustomMarshalingByReferenceTest*>(this);
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
ULONG STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::AddRef(void)
{
	// !!! Kedze sa jedna o APARTMENT THREAD COM OBJECT, NIE JE NUTNE THREAD SYNCHRONIZATION.
	ULONG														Ret=++MReferenceCounter;

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CCustomMarshalingByReferenceObject::Release(void)
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