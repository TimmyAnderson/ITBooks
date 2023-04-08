//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "PointersObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CPointersObject::CPointersObject(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CPointersObject::~CPointersObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObject::Dummy(void)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER METHOD CALLED !\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObject::NoAttributePointer(int* Pointer)
{
	CLock														Lock(MCS);

	if (Pointer!=NULL)
	{
		wprintf_s(L"NoAttributePointer() - POINTER VALUE [%d] !\n",*Pointer);
	}
	else
	{
		wprintf_s(L"NoAttributePointer() - POINTER is NULL !\n");
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObject::RefAttributePointer(int* Pointer)
{
	CLock														Lock(MCS);

	if (Pointer!=NULL)
	{
		wprintf_s(L"RefAttributePointer() - POINTER VALUE [%d] !\n",*Pointer);
	}
	else
	{
		wprintf_s(L"RefAttributePointer() - POINTER is NULL !\n");
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObject::UniqueAttributePointer(int* Pointer)
{
	CLock														Lock(MCS);

	if (Pointer!=NULL)
	{
		wprintf_s(L"UniqueAttributePointer() - POINTER VALUE [%d] !\n",*Pointer);
	}
	else
	{
		wprintf_s(L"UniqueAttributePointer() - POINTER is NULL !\n");
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObject::NoPtrAttributePointer(int* Pointer1, int* Pointer2)
{
	CLock														Lock(MCS);

	wprintf_s(L"NoPtrAttributePointer() - POINTER [%p] !\n",Pointer1);
	wprintf_s(L"NoPtrAttributePointer() - POINTER [%p] !\n",Pointer2);

	wprintf_s(L"NoPtrAttributePointer() - POINTER VALUE [%d] !\n",*Pointer1);
	wprintf_s(L"NoPtrAttributePointer() - POINTER VALUE [%d] !\n",*Pointer2);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObject::PtrAttributePointer(int* Pointer1, int* Pointer2)
{
	CLock														Lock(MCS);

	wprintf_s(L"PtrAttributePointer() - POINTER [%p] !\n",Pointer1);
	wprintf_s(L"PtrAttributePointer() - POINTER [%p] !\n",Pointer2);

	wprintf_s(L"PtrAttributePointer() - POINTER VALUE [%d] !\n",*Pointer1);
	wprintf_s(L"PtrAttributePointer() - POINTER VALUE [%d] !\n",*Pointer2);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObject::MallocSpyTest(int** PointerToMallocData)
{
	CLock														Lock(MCS);

	CSmartCOMPointer<IMalloc>									Malloc;

	if (SUCCEEDED(CoGetMalloc(1,&Malloc)))
	{
		*PointerToMallocData=(int*) Malloc->Alloc(sizeof(int));
		**PointerToMallocData=100;

		Malloc=NULL;
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObject::MemoryAllocatedByServer(struct SName* Name)
{
	CLock														Lock(MCS);

	CSmartCOMPointer<IMalloc>									Malloc;

	if (SUCCEEDED(CoGetMalloc(1,&Malloc)))
	{
		wchar_t													Data[]=L"Timmy Anderson";
		size_t													Length=wcslen(Data);
		
		// !!!!! Kedze 'Name->MName' je EMBEDDED POINTER MAL BY BYT ALKOVANY na COM OBJECT.
		// !!!!! Na alokaciu pamate sa pouziva IMalloc namiesto OPERATOR NEW. Je to preto, lebo IMalloc je STANDARDIZOVANY SPOSOB ALOKACIE PAMATE, ktoru podporuju VSETKY COM LANGUAGES. Ak by sa pouzil OPERATOR NEW, ktory je C++ SPECIFIC, tak by takuto pamat CLIENT napriklad beziaci v JAVA NEMUSEL VEDIET UVOLNIT. EXISTENCIA IMalloc umoznuje pouzitie STANDARDIZOVANEHO SPOSOBU ALOKACIE a DEALOKACIE PAMATE pre VSETKY COM LANGUAGES.
		Name->MName=(wchar_t*) Malloc->Alloc((Length+1)*sizeof(wchar_t));

		for (int Index=0;Index<(Length+1);Index++)
		{
			Name->MName[Index]=Data[Index];
		}
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CPointersObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IPointersTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IPointersTest)
	{
		*PointerToObject=static_cast<IPointersTest*>(this);
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
ULONG STDMETHODCALLTYPE CPointersObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CPointersObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------