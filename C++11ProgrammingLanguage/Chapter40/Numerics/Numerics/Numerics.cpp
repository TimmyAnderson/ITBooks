//-------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning(disable:4244)
#endif
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <iterator>
#include <iostream>
#include <memory>
#include <random>
#include <algorithm>
#include <sstream>
#include <complex>
#include <valarray>
#include <climits>
#include <cfloat>
#include <numeric>
#include "MyDebug.h"
#include "COperatorPlus.h"
#include "COperatorMinus.h"
#include "COperatorMultiple.h"
//-----------------------------------------------------------------------------
#undef min
#undef max
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void TestDumpNumericLimits(void)
{
	PrintLineSeparator();

	bool														HasSpecialization=numeric_limits<TType>::is_specialized;

	wcout << L"TYPE [" << ConvertStringToWideString(typeid(TType).name()) << L"] !\n";

	if (HasSpecialization==true)
	{
		wcout << L"VALUE numeric_limits<TType>::is_integer [" << ((numeric_limits<TType>::is_integer==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::is_signed [" << ((numeric_limits<TType>::is_signed==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::is_iec559 [" << ((numeric_limits<TType>::is_iec559==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::min() [" << numeric_limits<TType>::min() << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::max() [" << numeric_limits<TType>::max() << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::lowest() [" << numeric_limits<TType>::lowest() << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::epsilon() [" << numeric_limits<TType>::epsilon() << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::round_error() [" << numeric_limits<TType>::round_error() << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::infinity() [" << numeric_limits<TType>::infinity() << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::quiet_NaN() [" << numeric_limits<TType>::quiet_NaN() << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::signaling_NaN() [" << numeric_limits<TType>::signaling_NaN() << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::denorm_min() [" << numeric_limits<TType>::denorm_min() << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::is_exact [" << ((numeric_limits<TType>::is_exact==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::has_infinity [" << ((numeric_limits<TType>::has_infinity==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::has_quiet_NaN [" << ((numeric_limits<TType>::has_quiet_NaN==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::has_signaling_NaN [" << ((numeric_limits<TType>::has_signaling_NaN==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::has_denorm [" << numeric_limits<TType>::has_denorm << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::has_denorm_loss [" << ((numeric_limits<TType>::has_denorm_loss==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::round_style [" << numeric_limits<TType>::round_style << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::is_bounded [" << ((numeric_limits<TType>::is_bounded==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::is_modulo [" << ((numeric_limits<TType>::is_modulo==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::digits [" << numeric_limits<TType>::digits << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::digits10 [" << numeric_limits<TType>::digits10 << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::max_digits10 [" << numeric_limits<TType>::max_digits10 << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::radix [" << numeric_limits<TType>::radix << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::min_exponent [" << numeric_limits<TType>::min_exponent << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::min_exponent10 [" << numeric_limits<TType>::min_exponent10 << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::max_exponent [" << numeric_limits<TType>::max_exponent << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::max_exponent10 [" << numeric_limits<TType>::max_exponent10 << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::traps [" << ((numeric_limits<TType>::traps==true) ? L"TRUE" : L"FALSE") << L"] !\n";
		wcout << L"VALUE numeric_limits<TType>::tinyness_before [" << ((numeric_limits<TType>::tinyness_before==true) ? L"TRUE" : L"FALSE") << L"] !\n";
	}
	else
	{
		wcout << L"TYPE has NO SPECIALIZATION !\n";
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintValarray(const wstring& Prefix, const valarray<TType>& Valarray)
{
	wcout << Prefix;
	wcout << L" [";

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Valarray[Index];
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintValarray2Dimensions(const wstring& Prefix, const valarray<TType>& Valarray, size_t Difference)
{
	wcout << Prefix;
	wcout << L" [";

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		if (Index>0 && (Index % Difference)==0)
		{
			wcout << L" ";
		}

		wcout << Valarray[Index];
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintValarray3Dimensions(const wstring& Prefix, const valarray<TType>& Valarray, size_t Difference1, size_t Difference2)
{
	wcout << Prefix;
	wcout << L" [";

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		if (Index>0 && (Index % Difference1)==0)
		{
			wcout << L" ";
		}

		if (Index>0 && (Index % Difference2)==0)
		{
			wcout << L" ";
		}

		wcout << Valarray[Index];
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TCollection>
void PrintCollection(const wstring& Prefix, const TCollection& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const auto& Item : Collection)
	{
		if (PrintSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator=true;
		}

		wcout << Item;
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNumericLimits(void)
{
	PrintLineSeparator();

	TestDumpNumericLimits<bool>();
	TestDumpNumericLimits<int8_t>();
	TestDumpNumericLimits<uint8_t>();
	TestDumpNumericLimits<int16_t>();
	TestDumpNumericLimits<uint16_t>();
	TestDumpNumericLimits<int32_t>();
	TestDumpNumericLimits<uint32_t>();
	TestDumpNumericLimits<int64_t>();
	TestDumpNumericLimits<uint64_t>();
	TestDumpNumericLimits<float>();
	TestDumpNumericLimits<double>();
	TestDumpNumericLimits<long double>();
	TestDumpNumericLimits<wstring>();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCLanguageMacros(void)
{
	PrintLineSeparator();

	wcout << L"VALUE CHAR_BIT [" << CHAR_BIT << L"] !\n";
	wcout << L"VALUE CHAR_MIN [" << CHAR_MIN << L"] !\n";
	wcout << L"VALUE CHAR_MAX [" << CHAR_MAX << L"] !\n";
	wcout << L"VALUE INT_MIN [" << INT_MIN << L"] !\n";
	wcout << L"VALUE INT_MAX [" << INT_MAX << L"] !\n";
	wcout << L"VALUE LONG_MIN [" << LONG_MIN << L"] !\n";
	wcout << L"VALUE LONG_MAX [" << LONG_MAX << L"] !\n";
	wcout << L"VALUE FLT_MIN [" << FLT_MIN << L"] !\n";
	wcout << L"VALUE FLT_MAX [" << FLT_MAX << L"] !\n";
	wcout << L"VALUE FLT_DIG [" << FLT_DIG << L"] !\n";
	wcout << L"VALUE FLT_MIN_10_EXP [" << FLT_MIN_10_EXP << L"] !\n";
	wcout << L"VALUE FLT_MAX_10_EXP [" << FLT_MAX_10_EXP << L"] !\n";
	wcout << L"VALUE DBL_MIN [" << DBL_MIN << L"] !\n";
	wcout << L"VALUE DBL_MAX [" << DBL_MAX << L"] !\n";
	wcout << L"VALUE DBL_DIG [" << DBL_DIG << L"] !\n";
	wcout << L"VALUE DBL_MIN_10_EXP [" << DBL_MIN_10_EXP << L"] !\n";
	wcout << L"VALUE DBL_MAX_10_EXP [" << DBL_MAX_10_EXP << L"] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCMathFunctions(void)
{
	PrintLineSeparator();

	double														Number=5.4;

	wcout << L"EXP() [" << exp(Number) << L"] !" << endl;
	wcout << L"SQRT() [" << sqrt(Number) << L"] !" << endl;
	wcout << L"LOG() [" << log(Number) << L"] !" << endl;
	wcout << L"LOG10() [" << log10(Number) << L"] !" << endl;
	wcout << L"SIN() [" << sin(Number) << L"] !" << endl;
	wcout << L"COS() [" << cos(Number) << L"] !" << endl;
	wcout << L"TAN() [" << tan(Number) << L"] !" << endl;
	wcout << L"SINH() [" << sinh(Number) << L"] !" << endl;
	wcout << L"COSH() [" << cosh(Number) << L"] !" << endl;
	wcout << L"TANH() [" << tanh(Number) << L"] !" << endl;
	wcout << L"ASIN() [" << asin(Number) << L"] !" << endl;
	wcout << L"ACOS() [" << acos(Number) << L"] !" << endl;
	wcout << L"ATAN() [" << atan(Number) << L"] !" << endl;
	wcout << L"ASINH() [" << asinh(Number) << L"] !" << endl;
	wcout << L"ACOSH() [" << acosh(Number) << L"] !" << endl;
	wcout << L"ATANH() [" << atanh(Number) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumbers(void)
{
	PrintLineSeparator();

	complex<double>												Number1(4,3);
	complex<double>												Number2(polar(5.0,0.75));

	wcout << L"NUMBER 1 [" << Number1 << L"] !" << endl;
	wcout << L"NUMBER 2 [" << Number2 << L"] !" << endl;

	wcout << L"NUMBER 1 - ABSOLUTE [" << abs(Number1) << L"] MAGNITUDE [" << norm(Number1) << L"] PHASE ANGLE [" << arg(Number1) << L"] CONJUGATE [" << conj(Number1) << L"] !" << endl;
	wcout << L"NUMBER 2 - ABSOLUTE [" << abs(Number2) << L"] MAGNITUDE [" << norm(Number2) << L"] PHASE ANGLE [" << arg(Number2) << L"] CONJUGATE [" << conj(Number2) << L"] !" << endl;

	PrintLineSeparator();

	complex<double>												Number3=Number1+Number2;

	wcout << L"NUMBER 3 [" << Number3 << L"] !" << endl;

	complex<double>												Number4=Number1-Number2;

	wcout << L"NUMBER 4 [" << Number4 << L"] !" << endl;

	complex<double>												Number5=Number1*Number2;

	wcout << L"NUMBER 5 [" << Number5 << L"] !" << endl;

	complex<double>												Number6=Number1/Number2;

	wcout << L"NUMBER 6 [" << Number6 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayInitialization(void)
{
	PrintLineSeparator();

	// Vytvori VALARRAY s 5 ITEMS obsahujucimi hodnotu 0.
	valarray<int>												Valarray1(5);

	PrintValarray(L"VALARRAY 1",Valarray1);

	PrintLineSeparator();

	// Vytvori VALARRAY s 5 ITEMS obsahujucimi hodnotu 3.14.
	valarray<double>											Valarray2(3.14,5);

	PrintValarray(L"VALARRAY 2",Valarray2);

	PrintLineSeparator();

	valarray<int>												Valarray3({1,2,3,4,5,6,7});

	PrintValarray(L"VALARRAY 3",Valarray3);

	PrintLineSeparator();

	int															Array[]{10,20,30,40,50};

	// Inicializacia VALARRAY z ARRAY.
	valarray<int>												Valarray4(Array,sizeof(Array)/sizeof(Array[0]));

	PrintValarray(L"VALARRAY 4",Valarray4);

	PrintLineSeparator();

	// Inicializacia VALARRAY z ARRAY.
	valarray<int>												Valarray5(Array+1,3);

	PrintValarray(L"VALARRAY 5",Valarray5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayOperations(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray1({10,20,30,40,50});
	valarray<int>												Valarray2({1,2,3,4,5});

	PrintValarray(L"VALARRAY 1",Valarray1);
	PrintValarray(L"VALARRAY 2",Valarray2);

	PrintLineSeparator();

	// Matematicke operacie je mozne vykonavat nad jednotlivymi ITEMS.
	Valarray2[0]=Valarray2[1]+Valarray2[2];

	PrintValarray(L"VALARRAY 2",Valarray2);

	PrintLineSeparator();

	// Matematicke operacie je mozne vykonavat nad CELYMI VALARRAYS.
	valarray<int>												Valarray3=3*Valarray1+Valarray2-2;

	PrintValarray(L"VALARRAY 3 - (3*VALARRAY_1+VALARRAY_2-2)",Valarray3);

	PrintLineSeparator();

	// Matematicke operacie je mozne vykonavat nad CELYMI VALARRAYS.
	valarray<int>												Valarray4=-Valarray3;

	PrintValarray(L"VALARRAY 4 - (-VALARRAY_3)",Valarray4);

	PrintLineSeparator();

	valarray<int>												Valarray5({17,3,12,28,19});
	
	PrintValarray(L"VALARRAY 5",Valarray5);

	wcout << L"VALARRAY 5 - MIN [" << Valarray5.min() << L"] !" << endl;
	wcout << L"VALARRAY 5 - MAX [" << Valarray5.max() << L"] !" << endl;
	wcout << L"VALARRAY 5 - SUM [" << Valarray5.sum() << L"] !" << endl;

	PrintLineSeparator();

	PrintValarray(L"VALARRAY 1",Valarray1);
	PrintValarray(L"VALARRAY 5",Valarray5);

	// !!! RETURN VALUE pre OPERATOR== je VALARRAY s BOOL VALUES.
	valarray<bool>												Valarray6=(Valarray1==Valarray5);

	PrintValarray(L"VALARRAY 6 - OPERATOR==",Valarray6);

	// !!! RETURN VALUE pre OPERATOR!= je VALARRAY s BOOL VALUES.
	valarray<bool>												Valarray7=(Valarray1!=Valarray5);

	PrintValarray(L"VALARRAY 7 - OPERATOR!=",Valarray7);

	// !!! RETURN VALUE pre OPERATOR< je VALARRAY s BOOL VALUES.
	valarray<bool>												Valarray8=(Valarray1<Valarray5);

	PrintValarray(L"VALARRAY 8 - OPERATOR<",Valarray8);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayIteration(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({17,3,12,28,19});
	
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	wcout << L"VALARRAY [";

	bool														PrintSeparator1=false;

	// !!! Aj ked CLASS [valarray<TType>] NEMA definovane METHOD begin() a METHOD end() ako METHODS, ma ich definovane ako FUNCTIONS.
	for(int Item : Valarray)
	{
		if (PrintSeparator1==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator1=true;
		}

		wcout << Item;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALARRAY [";

	bool														PrintSeparator2=false;

	// FUNCTION begin() a FUNCTION end() su definovane ako GLOBALNE FUNCTIONS.
	for(auto Iterator=begin(Valarray);Iterator!=end(Valarray);Iterator++)
	{
		if (PrintSeparator2==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator2=true;
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayTranscendentalFunctions(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray1({10,20,30,40,50});
	valarray<int>												Valarray2({1,2,3,4,5});

	PrintValarray(L"VALARRAY 1",Valarray1);
	PrintValarray(L"VALARRAY 2",Valarray2);

	PrintLineSeparator();

	valarray<int>												Valarray3=pow(Valarray1,Valarray2);

	PrintValarray(L"VALARRAY 3 - POW(VALARRAY_1,VALARRAY_2)",Valarray3);

	PrintLineSeparator();

	valarray<int>												Valarray4=sqrt(Valarray3);

	PrintValarray(L"VALARRAY 4 - SQRT(VALARRAY_3)",Valarray4);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarraySliceInitialization(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray(20);

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		Valarray[Index]=int(Index+1);
	}

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	slice_array<int>											Slice1=Valarray[slice(0,4,3)];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));

	slice_array<int>											Slice2=Valarray[slice(1,4,3)];

	PrintValarray(L"SLICE 2",valarray<int>(Slice2));

	slice_array<int>											Slice3=Valarray[slice(2,4,3)];

	PrintValarray(L"SLICE 3",valarray<int>(Slice3));

	// !!! Hodnota STRIDE moze byt aj ZAPORNA.
	slice_array<int>											Slice4=Valarray[slice(15,4,-3)];

	PrintValarray(L"SLICE 4",valarray<int>(Slice4));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarraySliceConstVsNonCostValarrays(void)
{
	PrintLineSeparator();

	valarray<int>												NonConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});
	const valarray<int>											ConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});
	valarray<int>												AddValarray({100,100,100,100});

	PrintValarray(L"NON-CONST VALARRAY",NonConstValarray);
	PrintValarray(L"CONST VALARRAY",ConstValarray);
	PrintValarray(L"ADD VALARRAY",AddValarray);

	PrintLineSeparator();

	// !!!!! SLICE vytvoreny z NON-CONST VALARRAY obsahuje REFERENCES na ITEMS POVODNEHO VALARRAY
	// OPERATOR[] nad NON-CONST VALARRAY vracia instanciu SLICE.
	slice_array<int>											NonConstSlice=NonConstValarray[slice(2,4,3)];

	PrintValarray(L"NON-CONST SLICE",valarray<int>(NonConstSlice));

	// !!!!! SLICE vytvoreny z CONST VALARRAY je NOVA INSTANCIA VALARRAY, ktora NEREFERUJE na POVODNY VALARRAY.
	// !!!!! OPERATOR[] nad CONST VALARRAY vracia instanciu VALARRAY.
	valarray<int>												ConstSlice=ConstValarray[slice(2,4,3)];

	PrintValarray(L"CONST SLICE",ConstSlice);

	PrintLineSeparator();

	// !!! Modifikuje ITEMS POVODNEHO VALARRAY.
	NonConstSlice+=AddValarray;

	// !!!!! Nemodifikuje ITEMS POVODNEHO VALARRAY.
	ConstSlice+=AddValarray;

	PrintValarray(L"NON-CONST SLICE",valarray<int>(NonConstSlice));
	PrintValarray(L"CONST SLICE",ConstSlice);

	PrintLineSeparator();

	PrintValarray(L"NON-CONST VALARRAY",NonConstValarray);
	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarraySliceOperations(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	slice_array<int>											Slice1=Valarray[slice(0,4,3)];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));

	slice_array<int>											Slice2=Valarray[slice(1,4,3)];

	PrintValarray(L"SLICE 2",valarray<int>(Slice2));

	slice_array<int>											Slice3=Valarray[slice(2,4,3)];

	PrintValarray(L"SLICE 3",valarray<int>(Slice3));

	PrintLineSeparator();

	// !!! Komplexna matematicka operacia.
	Slice1=static_cast<valarray<int>>(Slice2)*static_cast<valarray<int>>(Slice3);

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// !!! Komplexna matematicka operacia.
	valarray<int>												PowValarray=pow(static_cast<valarray<int>>(Slice2),static_cast<valarray<int>>(Slice3));

	PrintValarray(L"SLICE 2",valarray<int>(Slice2));
	PrintValarray(L"SLICE 3",valarray<int>(Slice3));
	PrintValarray(L"POW VALARRAY",PowValarray);

	PrintLineSeparator();

	// Priradi VALUE do kazdeho ITEM.
	Slice1=555;

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayGSlice1Dimension(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	size_t														RawSizes[]={4};
	size_t														RawStrides[]={3};
	valarray<size_t>											Sizes(RawSizes,1);
	valarray<size_t>											Strides(RawStrides,1);

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad NON-CONST VALARRAY vytvori instanciu CLASS [gslice_array<TType>].
	gslice_array<int>											Slice1=Valarray[gslice(2,Sizes,Strides)];
	gslice_array<int>											Slice2=Valarray[gslice(3,Sizes,Strides)];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"SLICE 2",valarray<int>(Slice2));

	PrintLineSeparator();

	// !!! Modifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z NON-CONST VALARRAY obsahuju REFERENCES na povodny VALARRAY.
	Slice1+=Slice2;

	PrintValarray(L"SLICE 1 (Slice1+=Slice2)",valarray<int>(Slice1));

	PrintLineSeparator();

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad CONST VALARRAY vytvori instanciu CLASS [valarray<TType>].
	valarray<int>												ValarraySlice1=ConstValarray[gslice(2,Sizes,Strides)];
	valarray<int>												ValarraySlice2=ConstValarray[gslice(3,Sizes,Strides)];

	PrintValarray(L"VALARRAY SLICE 1",valarray<int>(ValarraySlice1));
	PrintValarray(L"VALARRAY SLICE 2",valarray<int>(ValarraySlice2));

	PrintLineSeparator();

	// !!! Nemodifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z CONST VALARRAY obsahuju KOPIU dat z povodneho VALARRAY.
	ValarraySlice1+=ValarraySlice2;

	PrintValarray(L"VALARRAY SLICE 1 (ValarraySlice1+=ValarraySlice2)",valarray<int>(ValarraySlice1));

	PrintLineSeparator();

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayGSlice2Dimensions(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// !!! V 1. DIMENSION su 2 ITEMS.
	// !!! V 2. DIMENSION su 4 ITEMS.
	size_t														RawSizes[]={2,4};
	size_t														NumberOfDimensions=sizeof(RawSizes)/sizeof(RawSizes[0]);
	// !!! V 1. DIMENSION je rozdiel medzi ITEMS 10 ITEMS z VALARRAY.
	// !!! V 2. DIMENSION je rozdiel medzi ITEMS 3 ITEMS z VALARRAY.
	size_t														RawStrides[]={10,3};
	valarray<size_t>											Sizes(RawSizes,NumberOfDimensions);
	valarray<size_t>											Strides(RawStrides,NumberOfDimensions);

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad NON-CONST VALARRAY vytvori instanciu CLASS [gslice_array<TType>].
	gslice_array<int>											Slice1=Valarray[gslice(2,Sizes,Strides)];
	gslice_array<int>											Slice2=Valarray[gslice(3,Sizes,Strides)];

	PrintValarray2Dimensions(L"SLICE 1",valarray<int>(Slice1),RawSizes[NumberOfDimensions-1]);
	PrintValarray2Dimensions(L"SLICE 2",valarray<int>(Slice2),RawSizes[NumberOfDimensions-1]);

	PrintLineSeparator();

	// !!! Modifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z NON-CONST VALARRAY obsahuju REFERENCES na povodny VALARRAY.
	Slice1+=Slice2;

	PrintValarray2Dimensions(L"SLICE 1 (Slice1+=Slice2)",valarray<int>(Slice1),RawSizes[NumberOfDimensions-1]);

	PrintLineSeparator();

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad CONST VALARRAY vytvori instanciu CLASS [valarray<TType>].
	valarray<int>												ValarraySlice1=ConstValarray[gslice(2,Sizes,Strides)];
	valarray<int>												ValarraySlice2=ConstValarray[gslice(3,Sizes,Strides)];

	PrintValarray2Dimensions(L"VALARRAY SLICE 1",valarray<int>(ValarraySlice1),RawSizes[NumberOfDimensions-1]);
	PrintValarray2Dimensions(L"VALARRAY SLICE 2",valarray<int>(ValarraySlice2),RawSizes[NumberOfDimensions-1]);

	PrintLineSeparator();

	// !!! Nemodifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z CONST VALARRAY obsahuju KOPIU dat z povodneho VALARRAY.
	ValarraySlice1+=ValarraySlice2;

	PrintValarray2Dimensions(L"VALARRAY SLICE 1 (ValarraySlice1+=ValarraySlice2)",valarray<int>(ValarraySlice1),RawSizes[NumberOfDimensions-1]);

	PrintLineSeparator();

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayGSlice3Dimensions(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// !!! V 1. DIMENSION su 3 ITEMS.
	// !!! V 2. DIMENSION su 2 ITEMS.
	// !!! V 3. DIMENSION su 4 ITEMS.
	size_t														RawSizes[]={3,2,4};
	size_t														NumberOfDimensions=sizeof(RawSizes)/sizeof(RawSizes[0]);
	// !!! V 1. DIMENSION je rozdiel medzi ITEMS 30 ITEMS z VALARRAY.
	// !!! V 2. DIMENSION je rozdiel medzi ITEMS 10 ITEMS z VALARRAY.
	// !!! V 3. DIMENSION je rozdiel medzi ITEMS 3 ITEMS z VALARRAY.
	size_t														RawStrides[]={30,10,3};
	valarray<size_t>											Sizes(RawSizes,NumberOfDimensions);
	valarray<size_t>											Strides(RawStrides,NumberOfDimensions);

	// !!!!! Tento CODE v GCC sposobuje SEGMENTATION FAULT. Podla INTERNETU to vyzera, ze je to BUG v GCC. Vo VISUAL STUDIO CODE ide bez problemov.
#ifdef _MSC_VER
	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad NON-CONST VALARRAY vytvori instanciu CLASS [gslice_array<TType>].
	gslice_array<int>											Slice1=Valarray[gslice(2,Sizes,Strides)];
	gslice_array<int>											Slice2=Valarray[gslice(3,Sizes,Strides)];

	PrintValarray3Dimensions(L"SLICE 1",valarray<int>(Slice1),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);
	PrintValarray3Dimensions(L"SLICE 2",valarray<int>(Slice2),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);

	PrintLineSeparator();

	// !!! Modifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z NON-CONST VALARRAY obsahuju REFERENCES na povodny VALARRAY.
	Slice1+=Slice2;

	PrintValarray3Dimensions(L"SLICE 1 (Slice1+=Slice2)",valarray<int>(Slice1),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);
#endif

	PrintLineSeparator();

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad CONST VALARRAY vytvori instanciu CLASS [valarray<TType>].
	valarray<int>												ValarraySlice1=ConstValarray[gslice(2,Sizes,Strides)];
	valarray<int>												ValarraySlice2=ConstValarray[gslice(3,Sizes,Strides)];

	PrintValarray3Dimensions(L"VALARRAY SLICE 1",valarray<int>(ValarraySlice1),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);
	PrintValarray3Dimensions(L"VALARRAY SLICE 2",valarray<int>(ValarraySlice2),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);

	PrintLineSeparator();

	// !!! Nemodifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z CONST VALARRAY obsahuju KOPIU dat z povodneho VALARRAY.
	ValarraySlice1+=ValarraySlice2;

	PrintValarray3Dimensions(L"VALARRAY SLICE 1 (ValarraySlice1+=ValarraySlice2)",valarray<int>(ValarraySlice1),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);

	PrintLineSeparator();

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayMaskArray(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// !!! Aplikacia instancie CLASS [valarray<bool>] na NON-CONST VALARRAY vracia instanciu CLASS [mask_array<<TType>].
	mask_array<int>												Slice1=Valarray[Valarray<=20];
	mask_array<int>												Slice2=Valarray[Valarray>20];
	mask_array<int>												Slice3=Valarray[(Valarray % 2)==1];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"SLICE 2",valarray<int>(Slice2));
	PrintValarray(L"SLICE 3",valarray<int>(Slice3));

	PrintLineSeparator();

	// Komplexna matematicka operacia.
	// !!! Kedze CLASS [indirect_array<int>] obsahuje REFERENCES na povodny VALARRAY, zmenia sa ITEMS vo VALARRAY.
	Slice1=valarray<int>(Slice2)+valarray<int>(Slice3);

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Aplikacia instancie CLASS [valarray<bool>] na CONST VALARRAY vracia VALARRAY.
	valarray<int>												ConstSlice1=ConstValarray[ConstValarray<=20];
	valarray<int>												ConstSlice2=ConstValarray[ConstValarray>20];
	valarray<int>												ConstSlice3=ConstValarray[(ConstValarray % 2)==1];

	PrintValarray(L"CONST SLICE 1",ConstSlice1);
	PrintValarray(L"CONST SLICE 2",ConstSlice2);
	PrintValarray(L"CONST SLICE 3",ConstSlice3);

	PrintLineSeparator();

	// Komplexna matematicka operacia.
	// !!! Kedze CLASS [indirect_array<int>] obsahuje KOPIU povodneho VALARRAY, hodnoty ITEMS vo VALARRAY sa NEMENIA.
	ConstSlice1=valarray<int>(ConstSlice2)+valarray<int>(ConstSlice3);

	PrintValarray(L"CONST SLICE 1",valarray<int>(ConstSlice1));
	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayIndirectArray(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// INDEXY sa NESMU OPAKOVAT, no NEMUSIA byt SORTED.
	valarray<size_t>											Indices1({2,4,7,12,13,1});
	valarray<size_t>											Indices2({3,5,6,8,19,1});
	valarray<size_t>											Indices3({5,6,7,8,9,10});

	PrintValarray(L"INDICES 1",Indices1);
	PrintValarray(L"INDICES 2",Indices2);
	PrintValarray(L"INDICES 3",Indices3);

	PrintLineSeparator();

	// !!! Aplikacia instancie CLASS [valarray<size_t>] na NON-CONST VALARRAY vracia instanciu CLASS [indirect_array<<TType>].
	indirect_array<int>											Slice1=Valarray[Indices1];
	indirect_array<int>											Slice2=Valarray[Indices2];
	indirect_array<int>											Slice3=Valarray[Indices3];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"SLICE 2",valarray<int>(Slice2));
	PrintValarray(L"SLICE 3",valarray<int>(Slice3));

	PrintLineSeparator();

	// Komplexna matematicka operacia.
	// !!! Kedze CLASS [indirect_array<int>] obsahuje REFERENCES na povodny VALARRAY, zmenia sa ITEMS vo VALARRAY.
	Slice1=valarray<int>(Slice2)+valarray<int>(Slice3);

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Aplikacia instancie CLASS [valarray<size_t>] na CONST VALARRAY vracia VALARRAY.
	valarray<int>												ConstSlice1=ConstValarray[Indices1];
	valarray<int>												ConstSlice2=ConstValarray[Indices2];
	valarray<int>												ConstSlice3=ConstValarray[Indices3];

	PrintValarray(L"CONST SLICE 1",ConstSlice1);
	PrintValarray(L"CONST SLICE 2",ConstSlice2);
	PrintValarray(L"CONST SLICE 3",ConstSlice3);

	PrintLineSeparator();

	// Komplexna matematicka operacia.
	// !!! Kedze CLASS [indirect_array<int>] obsahuje KOPIU povodneho VALARRAY, hodnoty ITEMS vo VALARRAY sa NEMENIA.
	ConstSlice1=valarray<int>(ConstSlice2)+valarray<int>(ConstSlice3);

	PrintValarray(L"CONST SLICE 1",valarray<int>(ConstSlice1));
	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAlgorithmsAccumulate(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	int															Result1=accumulate(Vector.cbegin(),Vector.cend(),100);

	wcout << L"RESULT 1 [" << Result1 << L"] !" << endl;

	int															Result2=accumulate(Vector.cbegin(),Vector.cend(),100,COperatorPlus<int>());

	wcout << L"RESULT 2 [" << Result2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAlgorithmsInnerProduct(void)
{
	PrintLineSeparator();

	vector<int>													Vector1({10,20,30});
	vector<int>													Vector2({5,4,3});

	PrintCollection(L"VECTOR 1",Vector1);
	PrintCollection(L"VECTOR 2",Vector2);

	PrintLineSeparator();

	int															Result1=inner_product(Vector1.cbegin(),Vector1.cend(),Vector2.cbegin(),5);

	wcout << L"RESULT 1 [" << Result1 << L"] !" << endl;

	int															Result2=inner_product(Vector1.cbegin(),Vector1.cend(),Vector2.cbegin(),5,COperatorPlus<int>(),COperatorMultiple<int>());

	wcout << L"RESULT 2 [" << Result2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAlgorithmsAdjacentDifference(void)
{
	PrintLineSeparator();

	vector<int>													Vector({17,5,8,33,32,40});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	vector<int>													Result1;
	
	adjacent_difference(Vector.cbegin(),Vector.cend(),back_inserter(Result1));

	PrintCollection(L"RESULT 1",Result1);

	vector<int>													Result2;
	
	adjacent_difference(Vector.cbegin(),Vector.cend(),back_inserter(Result2),COperatorMinus<int>());

	PrintCollection(L"RESULT 2",Result2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAlgorithmsPartialSum(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50,60});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	vector<int>													Result1;

	partial_sum(Vector.cbegin(),Vector.cend(),back_inserter(Result1));

	PrintCollection(L"RESULT 1",Result1);

	vector<int>													Result2;

	partial_sum(Vector.cbegin(),Vector.cend(),back_inserter(Result2),COperatorPlus<int>());

	PrintCollection(L"RESULT 2",Result2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAlgorithmsItoa(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50,60});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	iota(Vector.begin(),Vector.end(),5);

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDefaultRandomGenerator(void)
{
	PrintLineSeparator();

	default_random_engine										Engine;

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10.0,20.0). Hodnota 20.0 nie je NIKDY generovana.
	uniform_real_distribution<double>							Distribution2(10,20);

	wcout << L"UNIFORM REAL DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNonDefaultRandomGenerator(void)
{
	PrintLineSeparator();

	knuth_b														Engine;

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10.0,20.0). Hodnota 20.0 nie je NIKDY generovana.
	uniform_real_distribution<double>							Distribution2(10,20);

	wcout << L"UNIFORM REAL DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomGeneratorNoSeed(void)
{
	PrintLineSeparator();

	default_random_engine										Engine1;

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine1);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	default_random_engine										Engine2;

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution2(10,20);

	wcout << L"UNIFORM DISTRIBUTION 2 [";

	// !!! Generuje sa ROVNAKA POSTUPNOST VALUES.
	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine2);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomGeneratorWithSeed(void)
{
	PrintLineSeparator();

	// !!! Pouzije sa SEED.
	default_random_engine										Engine1(10);

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine1);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pouzije sa SEED.
	default_random_engine										Engine2(20);

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution2(10,20);

	wcout << L"UNIFORM DISTRIBUTION 2 [";

	// !!! Generuje sa ROZLICNA POSTUPNOST VALUES.
	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine2);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDistributionWithParameters(void)
{
	PrintLineSeparator();

	default_random_engine										Engine1;
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine1);
	}

	wcout << L"] !" << endl;

	default_random_engine										Engine2;
	uniform_int_distribution<int>								Distribution2(100,200);

	wcout << L"UNIFORM DISTRIBUTION 2 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine2);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	default_random_engine										Engine3;

	wcout << L"UNIFORM DISTRIBUTION 2 - CUSTOM PARAMS [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		// !!! Aj ked DISTRIBUTION ma ako PARAMETER (100,200), pouziju sa CUSTOM PARAMETERS (10,20).
		wcout << Distribution2(Engine3,uniform_int_distribution<int>::param_type(10,20));
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomDevice(void)
{
	PrintLineSeparator();

	random_device												RandomDevice1;

	wcout << L"DEVICE 1 - RANDOM VALUE [" << RandomDevice1() << L"] !" << endl;
	wcout << L"DEVICE 1 - RANDOM VALUE [" << RandomDevice1() << L"] !" << endl;
	wcout << L"DEVICE 1 - RANDOM VALUE [" << RandomDevice1() << L"] !" << endl;

	PrintLineSeparator();

	random_device												RandomDevice2;

	wcout << L"DEVICE 2 - RANDOM VALUE [" << RandomDevice2() << L"] !" << endl;
	wcout << L"DEVICE 2 - RANDOM VALUE [" << RandomDevice2() << L"] !" << endl;
	wcout << L"DEVICE 2 - RANDOM VALUE [" << RandomDevice2() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MINIMUM VALUE [" << random_device::min() << L"] !" << endl;
	wcout << L"MAXIMUM VALUE [" << random_device::max() << L"] !" << endl;
	wcout << L"DEVICE 1 ENTROPY [" << RandomDevice1.entropy() << L"] !" << endl;
	wcout << L"DEVICE 2 ENTROPY [" << RandomDevice2.entropy() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCRand(void)
{
	PrintLineSeparator();

	wcout << L"RANDOM VALUE [" << rand() << L"] !" << endl;
	wcout << L"RANDOM VALUE [" << rand() << L"] !" << endl;
	wcout << L"RANDOM VALUE [" << rand() << L"] !" << endl;

	PrintLineSeparator();

	srand(1000);

	wcout << L"RANDOM VALUE [" << rand() << L"] !" << endl;
	wcout << L"RANDOM VALUE [" << rand() << L"] !" << endl;
	wcout << L"RANDOM VALUE [" << rand() << L"] !" << endl;

	PrintLineSeparator();

	srand(1000);

	wcout << L"RANDOM VALUE [" << rand() << L"] !" << endl;
	wcout << L"RANDOM VALUE [" << rand() << L"] !" << endl;
	wcout << L"RANDOM VALUE [" << rand() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MAXIMUM VALUE [" << RAND_MAX << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestNumericLimits();
	//TestCLanguageMacros();
	//TestCMathFunctions();
	//TestComplexNumbers();
	//TestValarrayInitialization();
	//TestValarrayOperations();
	//TestValarrayIteration();
	//TestValarrayTranscendentalFunctions();
	//TestValarraySliceInitialization();
	//TestValarraySliceConstVsNonCostValarrays();
	//TestValarraySliceOperations();
	//TestValarrayGSlice1Dimension();
	//TestValarrayGSlice2Dimensions();
	//TestValarrayGSlice3Dimensions();
	//TestValarrayMaskArray();
	//TestValarrayIndirectArray();
	//TestAlgorithmsAccumulate();
	//TestAlgorithmsInnerProduct();
	//TestAlgorithmsAdjacentDifference();
	//TestAlgorithmsPartialSum();
	//TestAlgorithmsItoa();
	//TestDefaultRandomGenerator();
	//TestNonDefaultRandomGenerator();
	//TestRandomGeneratorNoSeed();
	//TestRandomGeneratorWithSeed();
	//TestDistributionWithParameters();
	//TestRandomDevice();
	TestCRand();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------