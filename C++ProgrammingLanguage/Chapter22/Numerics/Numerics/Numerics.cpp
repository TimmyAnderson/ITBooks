//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <cmath>
#include <valarray>
#include <complex>
#include <numeric>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void MyInvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t pReserved)
{
   wprintf_s(L"\n\n\nInvalid parameter detected in function %s ! File: %s Line: %d !\n", Function, File, Line);
   wprintf_s(L"Expression: %s !\n\n\n", Expression);
}
//-------------------------------------------------------------------------------------------------------
int Add10(int Value)
{
	return(Value+10);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	wprintf_s(L"FLOAT - IS_SPECIALIZED: [%d] !\n",numeric_limits<float>::is_specialized);
	wprintf_s(L"DOUBLE - IS_SPECIALIZED: [%d] !\n",numeric_limits<double>::is_specialized);

	wprintf_s(L"FLOAT - MIN: [%e] !\n",numeric_limits<float>::min());
	wprintf_s(L"DOUBLE - MIN: [%e] !\n",numeric_limits<double>::min());

	wprintf_s(L"FLOAT - MAX: [%e] !\n",numeric_limits<float>::max());
	wprintf_s(L"DOUBLE - MAX: [%e] !\n",numeric_limits<double>::max());

	wprintf_s(L"FLOAT - EPSILON: [%e] !\n",numeric_limits<float>::epsilon());
	wprintf_s(L"DOUBLE - EPSILON: [%e] !\n",numeric_limits<double>::epsilon());

	// !!! NUMERIC LIMITS pre WSTRING NEEXISTUJE.
	wprintf_s(L"WSTRING - IS_SPECIALIZED: [%d] !\n",numeric_limits<wstring>::is_specialized);
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	wprintf_s(L"POW[2,3]: [%f] !\n",pow(2.0,3.0));

	// !!! Umyselne SIMULUJEM CHYBU.
	double														Value=sqrt(-4.0);
	int															Error=errno;
	
	if (Error==0)
	{
		wprintf_s(L"SQRT[-4]: [%f] !\n",Value);
	}
	else
	{
		wprintf_s(L"ERROR: [%d] !\n",Error);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	int															Values1[]={1,2,3};
	int															Values2[]={1,0,0};

	// Inicializujem VAL ARRAY z ARRAY.
	valarray<int>												ValArray1(Values1,_countof(Values1));

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray1.size();i++)
	{
		wprintf_s(L"%d",ValArray1[i]);
	}

	wprintf_s(L"] !\n");

	// Inicializujem VAL ARRAY z ARRAY.
	valarray<int>												ValArray2(Values2,_countof(Values2));

	ValArray1+=ValArray2;

	wprintf_s(L"VALARRAY after ADD: [");

	for (int i=0;i<ValArray1.size();i++)
	{
		wprintf_s(L"%d",ValArray1[i]);
	}

	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	// Kludne do VALARRAY mozem dat i VIACCIFERNE HONDOTY.
	int															Values1[]={1,25,3};
	int															Values2[]={1,1,1};

	// Inicializujem VAL ARRAY z ARRAY.
	valarray<int>												ValArray1(Values1,_countof(Values1));

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray1.size();i++)
	{
		wprintf_s(L"%d",ValArray1[i]);
	}

	wprintf_s(L"] !\n");

	// Inicializujem VAL ARRAY z ARRAY.
	valarray<int>												ValArray2(Values2,_countof(Values2));

	ValArray1+=ValArray2;

	wprintf_s(L"VALARRAY after ADD: [");

	for (int i=0;i<ValArray1.size();i++)
	{
		wprintf_s(L"%d",ValArray1[i]);
	}

	wprintf_s(L"] !\n");

	ValArray1=-ValArray1;

	wprintf_s(L"VALARRAY after OPERATOR-: [");

	for (int i=0;i<ValArray1.size();i++)
	{
		wprintf_s(L"%d",ValArray1[i]);
	}

	wprintf_s(L"] !\n");

	wprintf_s(L"VALARRAY MIN: [%d] !\n",ValArray1.min());
	wprintf_s(L"VALARRAY MAX: [%d] !\n",ValArray1.max());
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	int															Values[]={1,2,3};

	// Inicializujem VAL ARRAY z ARRAY.
	valarray<int>												ValArray(Values,_countof(Values));

	ValArray=ValArray.apply(Add10);

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray.size();i++)
	{
		if (i!=0)
		{
			wprintf_s(L" ");
		}

		wprintf_s(L"%d",ValArray[i]);
	}

	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	int															Values[]={1,2,9};

	valarray<int>												ValArray(Values,_countof(Values));

	ValArray=ValArray.shift(1);

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray.size();i++)
	{
		if (i!=0)
		{
			wprintf_s(L" ");
		}

		wprintf_s(L"%d",ValArray[i]);
	}

	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	int															Values[]={1,2,9};

	valarray<int>												ValArray(Values,_countof(Values));

	ValArray<<=2;

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray.size();i++)
	{
		if (i!=0)
		{
			wprintf_s(L" ");
		}

		wprintf_s(L"%d",ValArray[i]);
	}

	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	int															Values[]={-1,2,-9};

	valarray<int>												ValArray(Values,_countof(Values));
	
	ValArray=abs(ValArray);

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray.size();i++)
	{
		if (i!=0)
		{
			wprintf_s(L" ");
		}

		wprintf_s(L"%d",ValArray[i]);
	}

	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	int															Values[]={1,2,3,4,11,12,13,14,21,22,23,24};
	valarray<int>												ValArray(Values,_countof(Values));

	valarray<int>												ValArrayRow(100,4);
	valarray<int>												ValArrayColumn(100,3);

	slice														SliceRow2(4,4,1);
	slice														SliceColumn2(1,3,4);

	slice_array<int>											Row2=ValArray[SliceRow2];
	slice_array<int>											Column2=ValArray[SliceColumn2];

	// Pricitam k 2. riadku VALARRAY obsahujuci hodnoty 100.
	Row2+=ValArrayRow;
	// Pricitam k 2. stlpcu VALARRAY obsahujuci hodnoty 100.
	Column2+=ValArrayColumn;

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray.size();i++)
	{
		if (i!=0)
		{
			wprintf_s(L" ");
		}

		wprintf_s(L"%d",ValArray[i]);
	}

	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	int															Values[]={1,2,3,4,11,12,13,14,21,22,23,24};
	valarray<int>												ValArray(Values,_countof(Values));

	valarray<int>												ValArrayAdd(100,6);

	size_t														SizeLengths[]={2,3};
	size_t														SizeStrides[]={4,1};

	valarray<size_t>											Lengths(SizeLengths,2);
	valarray<size_t>											Strides(SizeStrides,2);

	// GSLICE sa odkazuje ma SUBMATICU 2 RIADKY a 3 SLTPCE v LAVOM HORNOM ROHU celej matice.
	gslice														GSlice(0,Lengths,Strides);

	gslice_array<int>											SliceArray=ValArray[GSlice];

	// Pricitam k SUMBMATICI VALARRAY obsahujuci hodnoty 100.
	SliceArray+=ValArrayAdd;

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray.size();i++)
	{
		if (i!=0)
		{
			wprintf_s(L" ");
		}

		wprintf_s(L"%d",ValArray[i]);
	}

	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	int															Values[]={1,2,3,4,11,12,13,14,21,22,23,24};
	valarray<int>												ValArray(Values,_countof(Values));

	// !!! Maska MUSIM MAT ROVNAKU VELKOST ako 'ValArray'.
	bool														Mask[]={true,false,false,true,false,false,false,false,true,false,false,true};

	valarray<bool>												SliceMask(Mask,_countof(Values));

	mask_array<int>												MaskArray=ValArray[SliceMask];

	valarray<int>												ValArrayAdd(100,4);

	MaskArray+=ValArrayAdd;

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray.size();i++)
	{
		if (i!=0)
		{
			wprintf_s(L" ");
		}

		wprintf_s(L"%d",ValArray[i]);
	}

	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	int															Values[]={1,2,3,4,11,12,13,14,21,22,23,24};
	valarray<int>												ValArray(Values,_countof(Values));

	// !!! Pole INDEXOV MUSI MAT ROVNAKU VELKOST ako 'ValArray'.
	size_t														Indices[]={11,10,9,8,7,6,5,4,3,2,1,0};

	valarray<size_t>											SliceIndices(Indices,_countof(Values));

	indirect_array<int>											MaskArray=ValArray[SliceIndices];

	valarray<int>												ValArrayAdd(100,12);

	MaskArray+=ValArrayAdd;

	wprintf_s(L"VALARRAY: [");

	for (int i=0;i<ValArray.size();i++)
	{
		if (i!=0)
		{
			wprintf_s(L" ");
		}

		wprintf_s(L"%d",ValArray[i]);
	}

	wprintf_s(L"] !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	complex<double>												Number(3.2,8.4);

	wprintf_s(L"COMPLEX: [%f,%f] !\n",Number.real(),Number.imag());

	Number*=2.0;

	wprintf_s(L"COMPLEX: [%f,%f] !\n",Number.real(),Number.imag());
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	int															Input[]={1,2,3,4,5};
	int															Output[_countof(Input)];

	// Pretazena verzia umoznuje definovat o OPERATOR.
	partial_sum(&Input[0],&Input[_countof(Input)],Output);

	for(int i=0;i<_countof(Input);i++)
	{
		wprintf_s(L"ITEM[%d]: [%d] !\n",i,Output[i]);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	int															Input[]={1,4,9,16,25,36,49,64,81,100};
	int															Output[_countof(Input)];

	// Pretazena verzia umoznuje definovat o OPERATOR.
	adjacent_difference(&Input[0],&Input[_countof(Input)],Output);

	for(int i=0;i<_countof(Input);i++)
	{
		wprintf_s(L"ITEM[%d]: [%d] !\n",i,Output[i]);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	int															Values1[]={10,20,30};
	int															Values2[]={1,2,3};

	// !!! DEFAULT verzia ma za 'OP1' OPERATOR* a za 'OP2' OPERATOR+.
	// Vysledkom je [100+(10*1)+(20*2)+(3*30)].
	int															Result=inner_product(&Values1[0],&Values1[_countof(Values1)],Values2,100);

	wprintf_s(L"Result: [%d] !\n",Result);
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	int															Values[]={10,20,30,40,50};

	// !!! DEFAULT verzia ma za 'OP' OPERATOR+.
	// Vysledkom je [100+10+20+30+40+50].
	int															Result=accumulate(&Values[0],&Values[_countof(Values)],100);

	wprintf_s(L"Result: [%d] !\n",Result);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	_set_invalid_parameter_handler(MyInvalidParameterHandler);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT,0);

	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	//Test11();
	//Test12();
	//Test13();
	//Test14();
	//Test15();
	//Test16();
	Test17();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------