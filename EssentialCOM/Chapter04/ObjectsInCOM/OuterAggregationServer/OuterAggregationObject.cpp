//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "OuterAggregationObject.h"
#include "..\InnerAggregationServer\InnerAggregationObject_h.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
COuterAggregationObject::COuterAggregationObject(void)
	: MReferenceCounter(0), MText(NULL), MInnerCOMObject(NULL)
{
}
//------------------------------------------------------------------------------------------------------
COuterAggregationObject::~COuterAggregationObject(void)
{
	// !!! Uvolni sa POINTER na INNER COM OBJECT.
	if (MInnerCOMObject!=NULL)
	{
		MInnerCOMObject->Release();
		MInnerCOMObject=NULL;
	}

	if (MText!=NULL)
	{
		delete[](MText);
		MText=NULL;
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE COuterAggregationObject::SetText(wchar_t* Text)
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
HRESULT STDMETHODCALLTYPE COuterAggregationObject::GetText(int BufferSize, wchar_t** Text)
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
HRESULT STDMETHODCALLTYPE COuterAggregationObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IOuterAggregationText*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IOuterAggregationText)
	{
		*PointerToObject=static_cast<IOuterAggregationText*>(this);
		AddRef();
		return(S_OK);
	}
	// !!! Vykona sa FORWARDING INNER COM INTERFACE do INNER COM OBJECT.
	else if (RIID==IID_IInnerAggregationText)
	{
		MInnerCOMObject->QueryInterface(RIID,PointerToObject);
		// !!!!! AddRef() sa NESMIE VOLAT, lebo QueryInterface() uz INKREMENTOVAL COUNTER INNER COM OBJECT.
		//AddRef();
		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE COuterAggregationObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE COuterAggregationObject::Release(void)
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
HRESULT COuterAggregationObject::CreateInnerCOMObject(void)
{
	InterlockedIncrement(&MReferenceCounter);

	// !!! Vytvori sa POINTER na INNER COM OBJECT.
	// !!! Ako 2. PARAMETER sa zasiela POINTER na OUTER COM OBJECT.
	// !!!!! OUTER COM OBJECT moze pri AGGREGATION ziskavat POINTER IBA na IUnknown INNER COM OBJECT.
	HRESULT														HR=CoCreateInstance(CLSID_InnerAggregationObject,this,CLSCTX_INPROC_SERVER,IID_IUnknown,(void **)&MInnerCOMObject);

	InterlockedDecrement(&MReferenceCounter);

	return(HR);
}
//------------------------------------------------------------------------------------------------------