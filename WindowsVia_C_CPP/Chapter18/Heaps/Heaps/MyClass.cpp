#include "MyClass.h"
#include <stdio.h>
//------------------------------------------------------------------------------
HANDLE		CMyClass::MHeap=NULL;
UINT		CMyClass::MNumAllocsInHeap=0;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
CMyClass::CMyClass(int Data)
	: MData(Data)
{
}
//------------------------------------------------------------------------------
CMyClass::~CMyClass(void)
{
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int CMyClass::GetData(void)
{
	return(MData);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void* CMyClass::operator new (size_t Size)
{
	wprintf_s(L"Operator NEW - Called !\n");

	if (MHeap==NULL)
	{
		// !!! Vytvorim NESERIALIZOVANU HEAP.
		MHeap=HeapCreate(HEAP_NO_SERIALIZE,0,0);

		if (MHeap==NULL)
			return(NULL);

		wprintf_s(L"Operator NEW - HEAP successfully created !\n");
	}

	// Alokujem pamat z HEAP.
	void*		P=HeapAlloc(MHeap, 0, Size);

	wprintf_s(L"Operator NEW - Memory block with address [%p] allocated !\n",P);

	if (P!=NULL)
	{
		// Inkrementujem pocitadlo objektov.
		MNumAllocsInHeap++;
	}

	wprintf_s(L"Operator NEW - Counter [%d] !\n",MNumAllocsInHeap);

	return(P);
}
//------------------------------------------------------------------------------
void CMyClass::operator delete(void* P)
{
	wprintf_s(L"Operator DELETE - Called, memory at address [%p] will be deleted !\n",P);

	// Dealokujem pamat.
	if (HeapFree(MHeap, 0, P)!=FALSE)
	{
		// Dekrementujem pocitadlo objektov.
		MNumAllocsInHeap--;

		wprintf_s(L"Operator DELETE - Counter [%d] !\n",MNumAllocsInHeap);
	}

	// Ak je pocitadlo objektov na 0, zlikvidujem HEAP.
	if (MNumAllocsInHeap==0)
	{
		if (HeapDestroy(MHeap)!=FALSE)
		{
			MHeap=NULL;
			wprintf_s(L"Operator DELETE - HEAP was destroyed !\n");
		}
	}
}
//------------------------------------------------------------------------------