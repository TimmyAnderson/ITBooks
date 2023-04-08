//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "ArraysObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CArraysObject::CArraysObject(void)
	: MReferenceCounter(0)
{
}
//------------------------------------------------------------------------------------------------------
CArraysObject::~CArraysObject(void)
{
	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::Dummy(void)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD Dummy() was CALLED !\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::JustPointer(int* Array)
{
	CLock														Lock(MCS);
	int															Index=0;

	wprintf(L"SERVER: METHOD JustPointer() was CALLED !\n");

	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	Index++;
	// !!!!! Vsetky NASLEDUJUCE ITEMS sa zobrazia NESPRAVNE (asi mozu aj hodit MEMORY FAULT), kedze pri prenose POINTER sa prenasa IBA 1 ITEM a NIE CELY ARRAY.
	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	Index++;
	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	Index++;
	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	Index++;
	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	Index++;
	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	Index++;
	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	Index++;
	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	Index++;
	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	Index++;
	wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::FixedArray(int Array[10])
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD FixedArray() was CALLED !\n");

	for(int Index=0;Index<10;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::SizeIs1(int ArraySize, int* Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SizeIs1() was CALLED !\n");

	for(int Index=0;Index<ArraySize;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::SizeIs2(int ArraySize, int Array[])
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SizeIs2() was CALLED !\n");

	for(int Index=0;Index<ArraySize;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::SizeIs3(int ArraySize, int Array[])
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SizeIs3() was CALLED !\n");

	for(int Index=0;Index<ArraySize;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::SizeIsExpression(int ArraySize1, int ArraySize2, int Array[])
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SizeIsExpression() was CALLED !\n");

	int															ArraySize=(ArraySize1<ArraySize2) ? ArraySize1 : ArraySize2;

	for(int Index=0;Index<ArraySize;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::SizeIsInStruct(SArray* Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SizeIsInStruct() was CALLED !\n");

	for(int Index=0;Index<Array->ArraySize;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array->Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::SizeIsConstant(int* Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SizeIsConstant() was CALLED !\n");

	for(int Index=0;Index<10;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::MaxIsConstant(int* Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD MaxIsConstant() was CALLED !\n");

	for(int Index=0;Index<10;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::SizeIsForOutputParameter(int ArraySize, int* Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SizeIsForOutputParameter() was CALLED !\n");

	// !!! Kontrolujem maximalnu velkost ARRAY.
	for(int Index=0;Index<10 && Index<ArraySize;Index++)
	{
		Array[Index]=9-Index;
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::SizeIsForOutputStringParameter(int ArraySize, wchar_t* Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SizeIsForOutputStringParameter() was CALLED !\n");

	wchar_t														Text[]={L"Timmy Anderson"};

	// !!! Kontrolujem maximalnu velkost ARRAY.
	for(int Index=0;Index<_countof(Text) && Index<ArraySize;Index++)
	{
		Array[Index]=Text[Index];
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::LengthIs(int ArrayLength, int Array[20])
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD LengthIs() was CALLED !\n");
	wprintf(L"SERVER: ArrayLength [%d] !\n",ArrayLength);

	for(int Index=0;Index<20;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::FirstIs(int StartIndex, int ArrayLength, int Array[20])
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD FirstIs() was CALLED !\n");
	wprintf(L"SERVER: StartIndex [%d] !\n",StartIndex);
	wprintf(L"SERVER: ArrayLength [%d] !\n",ArrayLength);

	for(int Index=0;Index<20;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::LastIs(int StartIndex, int EndIndex, int Array[20])
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD LastIs() was CALLED !\n");
	wprintf(L"SERVER: StartIndex [%d] !\n",StartIndex);
	wprintf(L"SERVER: EndIndex [%d] !\n",EndIndex);

	for(int Index=0;Index<20;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::LengthIsAndSizeIs(int ArraySize, int ArrayLength, int* Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD LengthIsAndSizeIs() was CALLED !\n");
	wprintf(L"SERVER: ArraySize [%d] !\n",ArraySize);
	wprintf(L"SERVER: ArrayLength [%d] !\n",ArrayLength);

	for(int Index=0;Index<ArraySize;Index++)
	{
		wprintf(L"SERVER: ITEM[%d]: [%d] !\n",Index,Array[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::LengthIsAndSizeIsForOutputParamerter(int ArraySize, int* ArrayLength, int* Array)
{
	CLock														Lock(MCS);

	// !!! Kontrolujem maximalnu velkost ARRAY.
	for(int Index=0;Index<10 && Index<ArraySize;Index++)
	{
		Array[Index]=9-Index;
	}

	*ArrayLength=10;

	wprintf(L"SERVER: METHOD LengthIsAndSizeIsForOutputParamerter() was CALLED !\n");
	wprintf(L"SERVER: ArraySize [%d] !\n",ArraySize);
	wprintf(L"SERVER: ArrayLength [%d] !\n",*ArrayLength);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::PointerToPointer(int** Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD PointerToPointer() was CALLED !\n");

	wprintf(L"SERVER: Array [%d] !\n",**Array);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::ArrayOfPointers(int** Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD ArrayOfPointers() was CALLED !\n");

	for (int Index=0;Index<3;Index++)
	{
		int*													PointerToValue=Array[Index];

		wprintf(L"SERVER: ITEM [%d]: [%d] !\n",Index,*PointerToValue);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::PointerToArray(int** Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD PointerToArray() was CALLED !\n");

	int*														PointerToArray=*Array;

	for (int Index=0;Index<4;Index++)
	{
		wprintf(L"SERVER: ITEM [%d]: [%d] !\n",Index,PointerToArray[Index]);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::ArrayToArray(int** Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD ArrayToArray() was CALLED !\n");

	for (int Index1=0;Index1<3;Index1++)
	{
		int*													PointerToArray=Array[Index1];

		for (int Index2=0;Index2<4;Index2++)
		{
			wprintf(L"SERVER: ITEM [%d][%d]: [%d] !\n",Index1,Index2,PointerToArray[Index2]);
		}
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::Matrix(int Array[3][4])
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD Matrix() was CALLED !\n");

	for (int Index1=0;Index1<3;Index1++)
	{
		for (int Index2=0;Index2<4;Index2++)
		{
			wprintf(L"SERVER: ITEM [%d][%d]: [%d] !\n",Index1,Index2,Array[Index1][Index2]);
		}
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::String(wchar_t* String)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD String() was CALLED !\n");

	wprintf(L"SERVER: TEXT [%s] !\n",String);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::OutputString(wchar_t** String)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD OutputString() was CALLED !\n");

	wchar_t														Text[]=L"Timmy Anderson";

	// !!!!! Pamat, ktoru METHOD vrati MUSI byt alokovana cez CoTaskMemAlloc(), pricom CLIENT ju MUSI UVOLNIT volanim CoTaskMemFree().
	wchar_t*													Buffer=(wchar_t*) CoTaskMemAlloc((_countof(Text)+1)*sizeof(wchar_t));

	for (int Index=0;Index<(_countof(Text)+1);Index++)
	{
		Buffer[Index]=Text[Index];
	}

	*String=Buffer;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::SafeArrayInt(SAFEARRAY** Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SafeArrayInt() was CALLED !\n");

	// !!! Podporujem iba SAFEARRAYS s 1 DIMENSION.
	if (SafeArrayGetDim(*Array)==1)
	{
		HRESULT													HR=S_OK;
		long													LowerBound;
		long													UpperBound;

		if (SUCCEEDED(HR=SafeArrayGetLBound(*Array,1,&LowerBound)))
		{
			if (SUCCEEDED(HR=SafeArrayGetUBound(*Array,1,&UpperBound)))
			{
				int*											Data=NULL;

				// Ziska sa POINTER na DATA.
				if (SUCCEEDED(HR=SafeArrayAccessData(*Array,(void**) &Data)))
				{
					// !!! Malo by to byt (UpperBound-LowerBound)+1.
					for (long Index=0;Index<(UpperBound-LowerBound)+1;Index++)
					{
						wprintf(L"SERVER: ITEM [%d]: [%d] !\n",Index,Data[Index]);
					}

					// Uvolni sa POINTER na DATA.
					if (FAILED(HR=SafeArrayUnaccessData(*Array)))
					{
						wprintf_s(L"Can't UNACCESS DATA !\n");
					}
				}
				else
				{
					wprintf_s(L"Can't ACCESS DATA !\n");
				}
			}
			else
			{
				wprintf_s(L"Can't GET UPPER BOUND !\n");
			}
		}
		else
		{
			wprintf_s(L"Can't GET LOWER BOUND !\n");
		}

		return(HR);
	}
	else
	{
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CArraysObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IArraysTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IArraysTest)
	{
		*PointerToObject=static_cast<IArraysTest*>(this);
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
ULONG STDMETHODCALLTYPE CArraysObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CArraysObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------