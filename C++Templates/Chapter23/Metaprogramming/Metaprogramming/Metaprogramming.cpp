//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include <array>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "STypeMetaprogrammingRemoveAllExtens.h"
#include "SHybridMetaprogrammingDotProduct.h"
#include "SHybridMetaprogrammingUnitTypesRatio.h"
#include "SHybridMetaprogrammingUnitTypesRatioAdd.h"
#include "SHybridMetaprogrammingUnitTypesDuration.h"
#include "SOldValueMetaprogrammingSquareRoot.h"
#include "SOldValueMetaprogrammingOptimumSquareRoot.h"
#include "SMetaprogrammingRecursiveTemplateArguments.h"
#include "SMetaprogrammingEnumerationsAndStaticConstants.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26498 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
constexpr TType ValueMetaprogrammingCalculateSquareRoot(TType Value)
{
	if (Value<=TType(1))
	{
		return(Value);
	}

	TType														Low=0;
	TType														High=Value;

	for (;;)
	{
		TType													Mid=((High+Low)/TType(2));
		TType													MidSquared=(Mid*Mid);

		if ((Low+TType(1))>=High || MidSquared==Value)
		{
			return(Mid);
		}

		if (MidSquared<Value)
		{
			Low=Mid;
		}
		else
		{
			High=Mid;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<>
constexpr double ValueMetaprogrammingCalculateSquareRoot<double>(double Value)
{
	if (Value<=1.0)
	{
		return(Value);
	}

	double														Low=0;
	double														High=Value;

	for (;;)
	{
		double													Mid=((High+Low)/2.0);
		double													MidSquared=(Mid*Mid);

		if ((Low+0.001)>=High || MidSquared==Value)
		{
			return(Mid);
		}

		if (MidSquared<Value)
		{
			Low=Mid;
		}
		else
		{
			High=Mid;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestValueMetaprogramming(void)
{
	PrintLineSeparator();

	{
		constexpr int											SIZE=ValueMetaprogrammingCalculateSquareRoot(100);

		int														Array[SIZE];
		size_t													ArraySize=(sizeof(Array)/sizeof(Array[0]));

		wcout << L"VALUE METAPROGRAMMING - ARRAY SIZE [" <<  ArraySize << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr int											SIZE=ValueMetaprogrammingCalculateSquareRoot(400);

		int														Array[SIZE];
		size_t													ArraySize=(sizeof(Array)/sizeof(Array[0]));

		wcout << L"VALUE METAPROGRAMMING - ARRAY SIZE [" <<  ArraySize << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr int											SIZE=ValueMetaprogrammingCalculateSquareRoot(1000);

		int														Array[SIZE];
		size_t													ArraySize=(sizeof(Array)/sizeof(Array[0]));

		wcout << L"VALUE METAPROGRAMMING - ARRAY SIZE [" <<  ArraySize << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! VALUE je vypocitana v COMPILE TIME.
		constexpr double										VALUE=ValueMetaprogrammingCalculateSquareRoot(1000.0);

		wcout << L"COMPILE TIME - VALUE [" << VALUE << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! VALUE je vypocitana v RUN TIME.
		double													VALUE=ValueMetaprogrammingCalculateSquareRoot(1000.0);

		wcout << L"RUN TIME - VALUE [" << VALUE << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeMetaprogramming(void)
{
	PrintLineSeparator();

	{
		using													ArrayType=int[];
		using													BaseType=STypeMetaprogrammingRemoveAllExtensUsing<ArrayType>;

		wcout << L"ARRAY TYPE [" << GetTypeInfoName<ArrayType>() << L"] BASE TYPE [" << GetTypeInfoName<BaseType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													ArrayType=int[100];
		using													BaseType=STypeMetaprogrammingRemoveAllExtensUsing<ArrayType>;

		wcout << L"ARRAY TYPE [" << GetTypeInfoName<ArrayType>() << L"] BASE TYPE [" << GetTypeInfoName<BaseType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													ArrayType=int[][100];
		using													BaseType=STypeMetaprogrammingRemoveAllExtensUsing<ArrayType>;

		wcout << L"ARRAY TYPE [" << GetTypeInfoName<ArrayType>() << L"] BASE TYPE [" << GetTypeInfoName<BaseType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													ArrayType=int[100][200];
		using													BaseType=STypeMetaprogrammingRemoveAllExtensUsing<ArrayType>;

		wcout << L"ARRAY TYPE [" << GetTypeInfoName<ArrayType>() << L"] BASE TYPE [" << GetTypeInfoName<BaseType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													ArrayType=int[][100][200];
		using													BaseType=STypeMetaprogrammingRemoveAllExtensUsing<ArrayType>;

		wcout << L"ARRAY TYPE [" << GetTypeInfoName<ArrayType>() << L"] BASE TYPE [" << GetTypeInfoName<BaseType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													ArrayType=int[100][200][300];
		using													BaseType=STypeMetaprogrammingRemoveAllExtensUsing<ArrayType>;

		wcout << L"ARRAY TYPE [" << GetTypeInfoName<ArrayType>() << L"] BASE TYPE [" << GetTypeInfoName<BaseType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Toto je klasicka TEMPLATE FUNCTION, ktora nepouziva HYBRID METAPROGRAMMING.
template<typename TType, size_t SIZE>
TType NonHybridMetaprogrammingDotProduct(const array<TType,SIZE>& Array1, const array<TType,SIZE>& Array2)
{
	TType														Result{};

	for (size_t Index=0;Index<SIZE;++Index)
	{
		Result+=(Array1[Index]*Array2[Index]);
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Toto je TEMPLATE FUNCTION, ktora vyuziva HYBRID METAPROGRAMMING.
template<typename TType, size_t SIZE>
TType HybridMetaprogrammingDotProduct(const array<TType,SIZE>& Array1, const array<TType,SIZE>& Array2)
{
	TType														Result=SHybridMetaprogrammingDotProduct<TType,SIZE>::CalculateResult(Array1.data(),Array2.data());

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestHybridMetaprogramming1(void)
{
	PrintLineSeparator();

	{
		array<int,3>											Array1{1,2,3};
		array<int,3>											Array2{4,5,6};

		int														Result=NonHybridMetaprogrammingDotProduct(Array1,Array2);

		wcout << L"NON HYBRID METAPROGRAMMING [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		array<int,3>											Array1{1,2,3};
		array<int,3>											Array2{4,5,6};

		int														Result=HybridMetaprogrammingDotProduct(Array1,Array2);

		wcout << L"HYBRID METAPROGRAMMING [" << Result << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestHybridMetaprogramming2(void)
{
	PrintLineSeparator();

	{
		using													Type1=SHybridMetaprogrammingUnitTypesDuration<int,SHybridMetaprogrammingUnitTypesRatio<1,1000>>;
		using													Type2=SHybridMetaprogrammingUnitTypesDuration<int,SHybridMetaprogrammingUnitTypesRatio<2,3>>;

		int														Value1=42;
		int														Value2=77;

		Type1													Duration1(Value1);
		Type2													Duration2(Value2);

		auto													Result=(Duration1+Duration2);

		wcout << L"HYBRID METAPROGRAMMING - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=SHybridMetaprogrammingUnitTypesDuration<double,SHybridMetaprogrammingUnitTypesRatio<1,3>>;
		using													Type2=SHybridMetaprogrammingUnitTypesDuration<int,SHybridMetaprogrammingUnitTypesRatio<1,1>>;

		double													Value1=7.5;
		int														Value2=4;

		Type1													Duration1(Value1);
		Type2													Duration2(Value2);

		auto													Result=(Duration1+Duration2);

		wcout << L"HYBRID METAPROGRAMMING - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestOldMetaprogramming(void)
{
	PrintLineSeparator();

	{
		constexpr int											Value=SOldValueMetaprogrammingSquareRoot<100>::Value;

		wcout << L"OLD VALUE METAPROGRAMMING - RESULT [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr int											Value=SOldValueMetaprogrammingSquareRoot<50>::Value;

		wcout << L"OLD VALUE METAPROGRAMMING - RESULT [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestOldMetaprogrammingOptimal(void)
{
	PrintLineSeparator();

	{
		constexpr int											Value=SOldValueMetaprogrammingOptimumSquareRoot<100>::Value;

		wcout << L"OLD VALUE METAPROGRAMMING - OPTIMAL - RESULT [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr int											Value=SOldValueMetaprogrammingOptimumSquareRoot<50>::Value;

		wcout << L"OLD VALUE METAPROGRAMMING - OPTIMAL - RESULT [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestMetaprogrammingRecursiveTemplateArguments(void)
{
	PrintLineSeparator();

	{
		// !!!!! Extremne narocne na COMPILER RESOURCES.
		using													Type=SMetaprogrammingRecursiveTemplateArguments<10>::LongType;

		// !!!!! Generuje extremne dlhy TYPE NAME.
		wcout << L"METAPROGRAMMING - RECURSIVE TEMPLATE ARGUMENTS - TYPE [" << GetTypeInfoName<Type>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestMetaprogrammingEnumerationsAndStaticConstants(void)
{
	PrintLineSeparator();

	{
		constexpr int											Value=SMetaprogrammingEnumerationsAndStaticConstantsEnum<5>::Value;

		wcout << L"ENUMERATION AND STATIC CONSTANTS - ENUM - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr int											Value=SMetaprogrammingEnumerationsAndStaticConstantsStaticConst<5>::Value;

		wcout << L"ENUMERATION AND STATIC CONSTANTS - STATIC CONST - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr int											Value=SMetaprogrammingEnumerationsAndStaticConstantsStaticConstexpr<5>::Value;

		wcout << L"ENUMERATION AND STATIC CONSTANTS - STATIC CONSTEXPR - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestValueMetaprogramming();
	//TestTypeMetaprogramming();
	//TestHybridMetaprogramming1();
	//TestHybridMetaprogramming2();
	//TestOldMetaprogramming();
	//TestOldMetaprogrammingOptimal();
	//TestMetaprogrammingRecursiveTemplateArguments();
	TestMetaprogrammingEnumerationsAndStaticConstants();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------