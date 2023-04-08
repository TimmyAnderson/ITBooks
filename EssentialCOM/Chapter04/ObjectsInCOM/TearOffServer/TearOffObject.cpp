//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "TearOffObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CTearOffObject::CTearOffObject(void)
	: MReferenceCounter(0), MTearOffInterface(NULL), MText(NULL)
{
}
//------------------------------------------------------------------------------------------------------
CTearOffObject::~CTearOffObject(void)
{
	if (MText!=NULL)
	{
		delete[](MText);
		MText=NULL;
	}

	// !!! Musi zavolat Release() CLASS implementujuce TEAR-OFF INTERFACE.
	if (MTearOffInterface!=NULL)
	{
		MTearOffInterface->Release();
		MTearOffInterface=NULL;
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CTearOffObject::SetTextOuter(wchar_t* Text)
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
HRESULT STDMETHODCALLTYPE CTearOffObject::GetTextOuter(int BufferSize, wchar_t** Text)
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
HRESULT STDMETHODCALLTYPE CTearOffObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_ITearOffTextOuter)
	{
		*PointerToObject=static_cast<ITearOffTextOuter*>(this);
		AddRef();
		return(S_OK);
	}
	// !!! Pre TEAR-OFF INTERFACE musim bud vytvorit NOVU INSTANCIU CInnerTearOffObject, alebo pouzit UZ VYTVORENU.
	else if (RIID==IID_ITearOffTextInner)
	{
		if (MTearOffInterface==NULL)
		{
			// !!! Vytvori sa instancia CLASS implementujucej TEAR-OFF INTERFACE.
			*PointerToObject=MTearOffInterface=new CInnerTearOffObject(this);

			// !!!!! Inkrementuje sa REFERENCE COUNTER CLASS implementujucej TEAR-OFF INTERFACE, ale NIE REFERENCE COUNTER COM OBJECT.
			// !!! Je to preto, lebo COM OBJECT je vrateny do CALLER FUNCTION.
			((IUnknown*)*PointerToObject)->AddRef();

			// !!!!! Inkrementuje sa REFERENCE COUNTER CLASS implementujucej TEAR-OFF INTERFACE, ale NIE REFERENCE COUNTER COM OBJECT.
			// !!!!! Je to preto, lebo COM OBJECT je ULOZELNY do FIELD.
			((IUnknown*)*PointerToObject)->AddRef();
		}
		else
		{
			MTearOffInterface->QueryInterface(RIID,PointerToObject);
		}

		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CTearOffObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CTearOffObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------