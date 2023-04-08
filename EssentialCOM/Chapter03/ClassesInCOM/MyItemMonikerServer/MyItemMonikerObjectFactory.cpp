//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyItemMonikerObjectFactory.h"
#include "MyItemMonikerObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CMyItemMonikerObjectFactory::CMyItemMonikerObjectFactory(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CMyItemMonikerObjectFactory::~CMyItemMonikerObjectFactory(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyItemMonikerObjectFactory::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyItemMonikerObjectFactory::Release(void)
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
// !!!!! Podla STRINGU v Item vytvori COM OBJECT a naplni ho prislusnymi datami.
HRESULT STDMETHODCALLTYPE CMyItemMonikerObjectFactory::GetObject(__RPC__in LPOLESTR Item, DWORD SpeedNeeded, __RPC__in_opt IBindCtx* PBC, __RPC__in REFIID RIID, __RPC__deref_out_opt void** PointerToObject)
{
	if (RIID==IID_IMyItemMonikerName)
	{
		// STRING [Timmy] pochadza z [clsid:6F3F078E-D088-4F1E-BD62-C79F390E8AA6:!Timmy].
		if (wcscmp(Item,L"Timmy")==0)
		{
			CMyItemMonikerObject*								NewObject=new CMyItemMonikerObject();
			HRESULT												HR;

			// Vykona aj INKREMENTACIU COUNTER vytvoreneho COM OBJECT.
			HR=NewObject->QueryInterface(RIID,PointerToObject);

			if (SUCCEEDED(HR))
			{
				NewObject->SetFirstName(L"Timmy");
				NewObject->SetLastName(L"Anderson");
				NewObject->SetAge(12);

				return(S_OK);
			}
			else
			{
				delete(NewObject);
				NewObject=NULL;

				*PointerToObject=NULL;
				return(E_NOINTERFACE);
			}

			return(S_OK);
		}
		// STRING [Jenny] pochadza z [clsid:6F3F078E-D088-4F1E-BD62-C79F390E8AA6:!Jenny].
		else if (wcscmp(Item,L"Jenny")==0)
		{
			CMyItemMonikerObject*								NewObject=new CMyItemMonikerObject();
			HRESULT												HR;

			// Vykona aj INKREMENTACIU COUNTER vytvoreneho COM OBJECT.
			HR=NewObject->QueryInterface(RIID,PointerToObject);

			if (SUCCEEDED(HR))
			{
				NewObject->SetFirstName(L"Jenny");
				NewObject->SetLastName(L"Thompson");
				NewObject->SetAge(13);

				return(S_OK);
			}
			else
			{
				delete(NewObject);
				NewObject=NULL;

				*PointerToObject=NULL;
				return(E_NOINTERFACE);
			}

			return(S_OK);
		}
		else
		{
			return(MK_E_NOOBJECT);
		}
	}
	else
	{
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObjectFactory::GetObjectStorage(__RPC__in LPOLESTR Item, __RPC__in_opt IBindCtx* PBC, __RPC__in REFIID RIID, __RPC__deref_out_opt void** PointerToStorage)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObjectFactory::IsRunning(__RPC__in LPOLESTR Item)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObjectFactory::EnumObjects(DWORD Flags, __RPC__deref_out_opt IEnumUnknown** Enum)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObjectFactory::LockContainer(BOOL Lock)
{
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObjectFactory::ParseDisplayName(__RPC__in_opt IBindCtx* PBC, __RPC__in LPOLESTR DisplayName, __RPC__out ULONG* Eaten, __RPC__deref_out_opt IMoniker** Moniker)
{
	CLock														Lock(MCS);

	// !!! Vytvorim ITEM MONIKER.
	// !!! Ako SEPARATOR sa pouziva znak '!'.
	HRESULT														HR=CreateItemMoniker(L"!",DisplayName+1,Moniker);

	if (SUCCEEDED(HR))
	{
		*Eaten=(ULONG) wcslen(DisplayName);
	}
	else
	{
		*Eaten=NULL;
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyItemMonikerObjectFactory::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IParseDisplayName*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IParseDisplayName)
	{
		*PointerToObject=static_cast<IParseDisplayName*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IOleItemContainer)
	{
		*PointerToObject=static_cast<IOleItemContainer*>(this);
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