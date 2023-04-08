//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "InnerAggregationObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CInnerAggregationObject::CInnerAggregationObject(IUnknown* UnknownOuter)
	: MReferenceCounter(0), MText(NULL)
{
	if (UnknownOuter!=NULL)
	{
		// Pouziva sa AGGREGATION.
		// !!!!! Aj ked si ukladam POINTER na OUTER COM OBJECT, jeho AddRef() sa NESMIE VOLAT. Inak by INNER a OUTER COM OBJECTS drzali POINTERS jeden na druhy a doslo by k CYKLU, kedy by sa ani INNER, ani OUTER COM OBJECT NEMOHOL UVOLNIT z PAMATE.
		// !!!!! OUTER COM OBJECT vsak VOLA AddRef() INNER COM OBJECT, ale OPACNE sa to NESMIE SPRAVIT.
		MOuterCOMObject=UnknownOuter;
	}
	else
	{
		// !!!!! AGGREGATION sa NEPOUZIVA a 'MOuterCOMObject' odkazuje na INonAggregationUnknown obsahujuci STANDARDNU IMPLEMENTACIU IUnknown.
		MOuterCOMObject=(IUnknown*)(INonAggregationUnknown*)this;
	}
}
//------------------------------------------------------------------------------------------------------
CInnerAggregationObject::~CInnerAggregationObject(void)
{
	if (MText!=NULL)
	{
		delete[](MText);
		MText=NULL;
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CInnerAggregationObject::SetText(wchar_t* Text)
{
	CLock														Lock(MCS);

	if (MText!=NULL)
	{
		delete[](MText);
		MText=NULL;
	}

	size_t														Length=wcslen(Text)+1;

	MText=new wchar_t[Length];
	wcscpy_s(MText,Length,Text);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CInnerAggregationObject::GetText(int BufferSize, wchar_t** Text)
{
	CLock														Lock(MCS);

	if (MText!=NULL)
	{
		wcscpy_s(*Text,BufferSize,MText);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CInnerAggregationObject::NonAggregationUnknown_QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		// !!!!! Musi VZDY vratit POINTER na INonAggregationUnknown, ktory NEROBI FORWARDING na OUTER COM OBJECT.
		*PointerToObject=static_cast<INonAggregationUnknown*>(this);

		// !!!!! Odkazuje na INonAggregationUnknown METHODS.
		// !!!!! Je to dosledok toho, ze THIS sa NAJPRV konvertoval na INonAggregationUnknown.
		// !!!!! Nasledne sa THIS konvertoval na IUnknown a to tak, ze COMPILER priratal OFFSET 0 k POINTER na INonAggregationUnknown cim som dostal ZNOVA POINTER na INonAggregationUnknown. Kedze INonAggregationUnknown ma TIE ISTE METHODS ako IUknown na BINARNEJ UROVNI ma INonAggregationUnknown ROVNAKY TVAR ako IUnknown.
		IUnknown*												Unknown=static_cast<IUnknown*>(*PointerToObject);

		// !!!!! Vola sa INonAggregationUnknown::AddRef().
		Unknown->AddRef();

		return(S_OK);
	}
	else if (RIID==IID_IInnerAggregationText)
	{
		// !!! Vracia POINTER na IInnerAggregationText.
		*PointerToObject=static_cast<IInnerAggregationText*>(this);

		// !!!!! Odkazuje na IUnknown METHODS.
		// !!!!! Je to dosledok toho, ze THIS sa NAJPRV konvertoval na IInnerAggregationText.
		// !!!!! Nasledne sa THIS konvertoval na IUnknown a to tak, ze COMPILER priratal OFFSET 0 k POINTER na IInnerAggregationText cim som dostal ZNOVA POINTER na IInnerAggregationText. Kedze COM OBJECT ma na OFFSET 0 IUnknown, tak ziskavam POINTER na IUnknown (ktory nasledne robi FORWARDNG na OUTER COM OBJECT).
		IUnknown*												Unknown=static_cast<IInnerAggregationText*>(*PointerToObject);

		// !!!!! Vola sa IUnknown::AddRef().
		Unknown->AddRef();

		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CInnerAggregationObject::NonAggregationUnknown_AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CInnerAggregationObject::NonAggregationUnknown_Release(void)
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
HRESULT STDMETHODCALLTYPE CInnerAggregationObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	// !!!!! Vykonava FORWARDING na OUTER COM OBJECT.
	return(MOuterCOMObject->QueryInterface(RIID,PointerToObject));
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CInnerAggregationObject::AddRef(void)
{
	// !!!!! Vykonava FORWARDING na OUTER COM OBJECT.
	return(MOuterCOMObject->AddRef());
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CInnerAggregationObject::Release(void)
{
	// !!!!! Vykonava FORWARDING na OUTER COM OBJECT.
	return(MOuterCOMObject->Release());
}
//------------------------------------------------------------------------------------------------------