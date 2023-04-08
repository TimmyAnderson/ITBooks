//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "InnerTearOffObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CInnerTearOffObject::CInnerTearOffObject(ITearOffTextOuter* COMObjectInterface)
	: MReferenceCounter(0), MCOMObjectInterface(COMObjectInterface), MText(NULL)
{
	// !!! Musi zavolat AddRef() COM OBJECT.
//	MCOMObjectInterface->AddRef();
}
//------------------------------------------------------------------------------------------------------
CInnerTearOffObject::~CInnerTearOffObject(void)
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
HRESULT STDMETHODCALLTYPE CInnerTearOffObject::SetTextInner(wchar_t* Text)
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
HRESULT STDMETHODCALLTYPE CInnerTearOffObject::GetTextInner(int BufferSize, wchar_t** Text)
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
HRESULT STDMETHODCALLTYPE CInnerTearOffObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_ITearOffTextInner)
	{
		*PointerToObject=static_cast<ITearOffTextInner*>(this);
		AddRef();
		return(S_OK);
	}
	else
	{
		// !!! Pre vsetky NON TEAR-OFF INTERFACES je volana QueryInterface() COM OBJECT.
		return(MCOMObjectInterface->QueryInterface(RIID,PointerToObject));
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CInnerTearOffObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CInnerTearOffObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------