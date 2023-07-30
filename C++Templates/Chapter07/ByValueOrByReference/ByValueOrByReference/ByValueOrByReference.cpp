//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include <vector>
#include "MyDebug.h"
#include "CClassWithCopyAndMove.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26800 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY VALUE.
template<typename TType>
void FunctionParametersByValue(TType Value)
{
	wcout << L"VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMove<wstring> FunctionParametersByValueReturnValue(void)
{
	CClassWithCopyAndMove<wstring>								Object(L"Timmy");

	return(Object);
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersByValue(void)
{
	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Object(L"Timmy");

		// !!! Vola sa COPY CONSTRUCTOR co znamena PEFROFMANCE HIT.
		FunctionParametersByValue(Object);
	}

	PrintLineSeparator();

	{
		// !!!!! COMPILER vykonava OPTIMALIZATION, takze NEDOCHADZA k volaniu COPY ani MOVE CONSTRUCTORS.
		// !!!!! Od C++ 17 je COMPILER POVINNY vykonat tuto OPTIMALIZATION.
		FunctionParametersByValue(CClassWithCopyAndMove<wstring>(L"Timmy"));
	}

	PrintLineSeparator();

	{
		// !!!!! COMPILER vykonava OPTIMALIZATION, takze NEDOCHADZA k volaniu COPY ani MOVE CONSTRUCTORS.
		// !!!!! Od C++ 17 je COMPILER POVINNY vykonat tuto OPTIMALIZATION.
		FunctionParametersByValue(FunctionParametersByValueReturnValue());
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Object(L"Timmy");

		// !!! Vola sa MOVE CONSTRUCTOR.
		FunctionParametersByValue(move(Object));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY VALUE.
template<typename TType>
void FunctionParametersByValueTypeDecay1(TType Value)
{
	wcout << L"PARAMETER TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY VALUE.
// !!!!! Vykonava sa DECAY z TYPE [const TYPE] na TYPE [TYPE].
template<typename TType>
void FunctionParametersByValueTypeDecay2(TType Value)
{
	wcout << L"1 - PARAMETER TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

	Value=L"JENNY";

	wcout << L"2 - PARAMETER TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersByValueTypeDecay(void)
{
	PrintLineSeparator();

	{
		wchar_t													CArray[]=L"Timmy";

		wcout << L"ARGUMENT TYPE [" << GetTypeInfoName<decltype(CArray)>() << L"] VALUE [" << CArray << L"]." << endl;

		// !!! Vykonava sa DECAY z TYPE [wchar_t[6]] na TYPE [wchar_t].
		FunctionParametersByValueTypeDecay1(CArray);
	}

	PrintLineSeparator();

	{
		using													TYPE=const wstring;

		TYPE													Object(L"Timmy");

		wcout << L"1 - ARGUMENT TYPE [" << GetTypeInfoName<TYPE>() << L"] VALUE [" << Object << L"]." << endl;

		// !!! Vykonava sa DECAY z TYPE [const wstring] na TYPE [wstring].
		FunctionParametersByValueTypeDecay2(Object);

		wcout << L"2 - ARGUMENT TYPE [" << GetTypeInfoName<TYPE>() << L"] VALUE [" << Object << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY CONSTANT REFERENCE.
template<typename TType>
void FunctionParametersByConstReference(const TType& Value)
{
	wcout << L"VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMove<wstring> FunctionParametersByConstReferenceReturnValue(void)
{
	CClassWithCopyAndMove<wstring>								Object(L"Timmy");

	return(Object);
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersByConstReference(void)
{
	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Object(L"Timmy");

		// !!! PARAMETER je prenasany BY CONSTANT REFERENCE a teda NEDOCHADZA k volaniu COPY CONSTRUCTOR.
		FunctionParametersByConstReference(Object);
	}

	PrintLineSeparator();

	{
		// !!! PARAMETER je prenasany BY CONSTANT REFERENCE a teda NEDOCHADZA k volaniu COPY CONSTRUCTOR.
		FunctionParametersByConstReference(CClassWithCopyAndMove<wstring>(L"Timmy"));
	}

	PrintLineSeparator();

	{
		// !!! PARAMETER je prenasany BY CONSTANT REFERENCE a teda NEDOCHADZA k volaniu COPY CONSTRUCTOR.
		FunctionParametersByConstReference(FunctionParametersByConstReferenceReturnValue());
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Object(L"Timmy");

		// !!! PARAMETER je prenasany BY CONSTANT REFERENCE a teda NEDOCHADZA k volaniu COPY CONSTRUCTOR.
		FunctionParametersByConstReference(move(Object));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY CONSTANT REFERENCE.
// !!!!! NEVYKONAVA sa DECAY.
template<typename TType>
void FunctionParametersByConstReferenceTypeDecay1(const TType& Value)
{
	wcout << L"PARAMETER TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY CONSTANT REFERENCE.
// !!!!! NEVYKONAVA sa DECAY.
template<typename TType>
void FunctionParametersByConstReferenceTypeDecay2(const TType& Value)
{
	wcout << L"PARAMETER TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersByConstReferenceTypeDecay(void)
{
	PrintLineSeparator();

	{
		wchar_t													CArray[]=L"Timmy";

		wcout << L"ARGUMENT TYPE [" << GetTypeInfoName<decltype(CArray)>() << L"] VALUE [" << CArray << L"]." << endl;

		// !!! NEVYKONAVA sa DECAY.
		FunctionParametersByConstReferenceTypeDecay1(CArray);
	}

	PrintLineSeparator();

	{
		using													TYPE=const wstring;

		TYPE													Object(L"Timmy");

		wcout << L"ARGUMENT TYPE [" << GetTypeInfoName<TYPE>() << L"] VALUE [" << Object << L"]." << endl;

		// !!! NEVYKONAVA sa DECAY.
		FunctionParametersByConstReferenceTypeDecay2(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY NON-CONSTANT REFERENCE.
template<typename TType>
void FunctionParametersByNonConstReference(TType& Value)
{
	wcout << L"1 - PARAMETER VALUE [" << Value << L"]." << endl;

	// !!! PARAMETER moze byt MODIFIKOVANY.
	Value.SetValue(L"JENNY");

	wcout << L"2 - PARAMETER VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMove<wstring> FunctionParametersByNonConstReferenceReturnValue(void)
{
	CClassWithCopyAndMove<wstring>								Object(L"Timmy");

	return(Object);
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersByNonConstReference(void)
{
	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Object(L"Timmy");

		wcout << L"1 - ARGUMENT VALUE [" << Object << L"]." << endl;

		// !!! PARAMETER je prenasany BY NON-CONSTANT REFERENCE a teda NEDOCHADZA k volaniu COPY CONSTRUCTOR.
		FunctionParametersByNonConstReference(Object);

		wcout << L"2 - ARGUMENT VALUE [" << Object << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze RVALUE VALUE nie je mozne pouzit ako ARGUMENT pre NON-CONSTANT REFERENCE PARAMETER.
		FunctionParametersByNonConstReference(CClassWithCopyAndMove<wstring>(L"Timmy"));
	}

	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze RVALUE VALUE nie je mozne pouzit ako ARGUMENT pre NON-CONSTANT REFERENCE PARAMETER.
		FunctionParametersByNonConstReference(FunctionParametersByNonConstReferenceReturnValue());
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Object(L"Timmy");

		// !!!!! COMPILER hodi ERROR, pretoze RVALUE VALUE nie je mozne pouzit ako ARGUMENT pre NON-CONSTANT REFERENCE PARAMETER.
		FunctionParametersByNonConstReference(move(Object));
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY NON-CONSTANT REFERENCE.
// !!!!! NEVYKONAVA sa DECAY.
template<typename TType>
void FunctionParametersByNonConstReferenceTypeDecay1(TType& Value)
{
	wcout << L"PARAMETER TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY NON-CONSTANT REFERENCE.
// !!!!! NEVYKONAVA sa DECAY.
template<typename TType>
void FunctionParametersByNonConstReferenceTypeDecay2(TType& Value)
{
	wcout << L"PARAMETER TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersByNonConstReferenceTypeDecay(void)
{
	PrintLineSeparator();

	{
		wchar_t													CArray[]=L"Timmy";

		wcout << L"ARGUMENT TYPE [" << GetTypeInfoName<decltype(CArray)>() << L"] VALUE [" << CArray << L"]." << endl;

		// !!! NEVYKONAVA sa DECAY.
		FunctionParametersByNonConstReferenceTypeDecay1(CArray);
	}

	PrintLineSeparator();

	{
		using													TYPE=const wstring;

		TYPE													Object(L"Timmy");

		wcout << L"ARGUMENT TYPE [" << GetTypeInfoName<TYPE>() << L"] VALUE [" << Object << L"]." << endl;

		// !!! NEVYKONAVA sa DECAY.
		FunctionParametersByNonConstReferenceTypeDecay2(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY NON-CONSTANT REFERENCE.
template<typename TType>
void FunctionParametersByNonConstReferenceConstArgument(TType& Value)
{
	wcout << L"PARAMETER VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
const CClassWithCopyAndMove<wstring> FunctionParametersByNonConstReferenceReturnValueConstArgument(void)
{
	CClassWithCopyAndMove<wstring>								Object(L"Timmy");

	return(Object);
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersByNonConstReferenceConstArgument(void)
{
	PrintLineSeparator();

	{
		const CClassWithCopyAndMove<wstring>					Object(L"Timmy");

		wcout << L"ARGUMENT VALUE [" << Object << L"]." << endl;

		// !!!!! ARGUMENT je CONST OBJECT. CONST OBJECT moze byt zaslany do TEMPLATE FUNCTION, ktory ma TYPE NON-CONST REFERENCE a to tak, ze C++ vykona TYPE DEDUCTION a ako PARAMETER TYPE urci CONST REFERENCE. TEMPLATE FUNCTION potom PARAMETER NEMOZE modifikovat.
		FunctionParametersByNonConstReferenceConstArgument(Object);
	}

	PrintLineSeparator();

	{
		using													ConstCClassWithCopyAndMove=const CClassWithCopyAndMove<wstring>;

		// !!!!! ARGUMENT je CONST OBJECT. CONST OBJECT moze byt zaslany do TEMPLATE FUNCTION, ktory ma TYPE NON-CONST REFERENCE a to tak, ze C++ vykona TYPE DEDUCTION a ako PARAMETER TYPE urci CONST REFERENCE. TEMPLATE FUNCTION potom PARAMETER NEMOZE modifikovat.
		FunctionParametersByNonConstReferenceConstArgument(ConstCClassWithCopyAndMove(L"Timmy"));
	}

	PrintLineSeparator();

	{
		// !!!!! ARGUMENT je CONST OBJECT. CONST OBJECT moze byt zaslany do TEMPLATE FUNCTION, ktory ma TYPE NON-CONST REFERENCE a to tak, ze C++ vykona TYPE DEDUCTION a ako PARAMETER TYPE urci CONST REFERENCE. TEMPLATE FUNCTION potom PARAMETER NEMOZE modifikovat.
		FunctionParametersByNonConstReferenceConstArgument(FunctionParametersByNonConstReferenceReturnValueConstArgument());
	}

	PrintLineSeparator();

	{
		const CClassWithCopyAndMove<wstring>					Object(L"Timmy");

		// !!!!! ARGUMENT je CONST OBJECT. CONST OBJECT moze byt zaslany do TEMPLATE FUNCTION, ktory ma TYPE NON-CONST REFERENCE a to tak, ze C++ vykona TYPE DEDUCTION a ako PARAMETER TYPE urci CONST REFERENCE. TEMPLATE FUNCTION potom PARAMETER NEMOZE modifikovat.
		FunctionParametersByNonConstReferenceConstArgument(move(Object));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY FORWARD REFERENCE.
template<typename TType>
void FunctionParametersByForwardReference1(TType&& Value)
{
	wcout << L"PARAMETER VALUE [" << Value << L"] PROTOTYPE ["<< MACRO_FUNCTION_PROTOTYPE << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER je prenasany BY FORWARD REFERENCE.
template<typename TType>
void FunctionParametersByForwardReference2(TType&& Value)
{
	// !!! Ak je TYPE 'TType' LVALUE REFERENCE, tak COMPILER hodi ERROR, lebo VARIABLE 'Variable' nie je inicializovana.
	TType														Variable;

	Variable=Value;

	wcout << L"PARAMETER VALUE [" << Value << L"] VARIABLE [" << Variable << L"] PROTOTYPE ["<< MACRO_FUNCTION_PROTOTYPE << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersByForwardReference(void)
{
	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Object(L"Timmy");

		// !!! Nedochadza k volaniu COPY CONSTRUCTOR.
		FunctionParametersByForwardReference1(Object);
	}

	PrintLineSeparator();

	{
		// !!! Nedochadza k volaniu COPY CONSTRUCTOR.
		FunctionParametersByForwardReference1(CClassWithCopyAndMove<wstring>(L"Timmy"));
	}

	PrintLineSeparator();

	{
		// !!! Nedochadza k volaniu COPY CONSTRUCTOR.
		FunctionParametersByForwardReference1(FunctionParametersByConstReferenceReturnValue());
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Object(L"Timmy");

		// !!! Nedochadza k volaniu COPY CONSTRUCTOR.
		FunctionParametersByForwardReference1(move(Object));
	}

	PrintLineSeparator();

	{
		wchar_t													CArray[]=L"Timmy";

		wcout << L"ARGUMENT TYPE [" << GetTypeInfoName<decltype(CArray)>() << L"] VALUE [" << CArray << L"]." << endl;

		// !!! Nedochadza k volaniu COPY CONSTRUCTOR.
		FunctionParametersByForwardReference1(CArray);
	}

	PrintLineSeparator();

	{
		const CClassWithCopyAndMove<wstring>					Object(L"Timmy");

		// !!! Nedochadza k volaniu COPY CONSTRUCTOR.
		FunctionParametersByForwardReference1(Object);
	}

	PrintLineSeparator();

	{
		// !!! Nedochadza k volaniu COPY CONSTRUCTOR.
		FunctionParametersByForwardReference1(L"TIMMY");
	}

	PrintLineSeparator();

	{
		wchar_t													Array[]{L"TIMMY"};

		// !!! Nedochadza k volaniu COPY CONSTRUCTOR.
		FunctionParametersByForwardReference1(Array);
	}

	PrintLineSeparator();

	{
		// !!! CODE zbehne OK.
		FunctionParametersByForwardReference2(100);
	}

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze DEDUCED TYPE [int&] a pre tento TYPE sa vytvori v TEMPLATE FUNCTION UNITIALIZED VARIABLE.
	{
		int														Value=100;

		FunctionParametersByForwardReference2(Value);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestRefAndCRef(void)
{
	PrintLineSeparator();

	{
		wstring													Value1=L"Timmy";
		wstring													Value2=L"Jenny";
		wstring													Value3=L"Josh";
		wstring													Value4=L"Lucas";

		// !!!!! CLASS [reference_wrapper<TYPE>] umoznuje ukladat REFERENCES namiesto OBJECTS.
		vector<reference_wrapper<wstring>>						Values;

		Values.push_back(ref(Value1));
		Values.push_back(ref(Value2));
		Values.push_back(ref(Value3));
		Values.push_back(ref(Value4));

		for(reference_wrapper<wstring> Value : Values)
		{
			wcout << L"VALUE [" << Value.get() << L"]." << endl;
		}

		PrintLineSeparator();

		for(reference_wrapper<wstring> Value : Values)
		{
			// !!! Kedze REFERENCES ulozene v COLLECTION su NON-CONST, je ich mozne modifikovat.
			Value.get()+=L" MODIFIED !";
		}

		for(reference_wrapper<wstring> Value : Values)
		{
			wcout << L"VALUE [" << Value.get() << L"]." << endl;
		}
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		wstring													Value1=L"Timmy";
		wstring													Value2=L"Jenny";
		wstring													Value3=L"Josh";
		wstring													Value4=L"Lucas";

		// !!!!! CLASS [reference_wrapper<TYPE>] umoznuje ukladat REFERENCES namiesto OBJECTS.
		vector<reference_wrapper<const wstring>>				Values;

		Values.push_back(cref(Value1));
		Values.push_back(cref(Value2));
		Values.push_back(cref(Value3));
		Values.push_back(cref(Value4));

		for(reference_wrapper<const wstring> Value : Values)
		{
			wcout << L"VALUE [" << Value.get() << L"]." << endl;
		}

		/*
		PrintLineSeparator();

		for(reference_wrapper<const wstring> Value : Values)
		{
			// !!! Kedze REFERENCES ulozene v COLLECTION su CONST, NIE je ich mozne modifikovat.
			Value.get()+=L" MODIFIED !";
		}

		for(reference_wrapper<const wstring> Value : Values)
		{
			wcout << L"VALUE [" << Value.get() << L"]." << endl;
		}
		*/
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintFunctionRefAndCRefInTemplateFunctions(const wstring& Value)
{
	wcout << L"VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateFunctionRefAndCRefInTemplateFunctions(TType Parameter)
{
	wcout << L"PROTOTYPE ["<< MACRO_FUNCTION_PROTOTYPE << L"]." << endl;

	// !!!!! Ak je TYPE 'TType' TYPE [reference_wrapper<TType>], tak C++ vola CONVERSION OPERATOR, ktory konvertuje instanciu CLASS [reference_wrapper<TType>] na TYPE [TType].
	PrintFunctionRefAndCRefInTemplateFunctions(Parameter);
}
//----------------------------------------------------------------------------------------------------------------------
void TestRefAndCRefInTemplateFunctions(void)
{
	PrintLineSeparator();

	{
		wstring													Value(L"Timmy");

		TemplateFunctionRefAndCRefInTemplateFunctions(Value);
	}

	PrintLineSeparator();

	{
		wstring													Value(L"Timmy");

		// !!! Prenasa sa TYPE [reference_wrapper<TType>] BY-VALUE.
		TemplateFunctionRefAndCRefInTemplateFunctions(cref(Value));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pri prenose C-ARRAYS BY-VALUE dochadza k TYPE DECAY na POINTER na 1. ARRAY ITEM.
template<typename TType>
void ParametersCArraysPassByValue(TType Parameter, size_t ArraySize)
{
	wcout << L"BY VALUE - PROTOTYPE ["<< MACRO_FUNCTION_PROTOTYPE << L"]." << endl;

	for(size_t Index=0;Index<ArraySize;Index++)
	{
		wcout << L"ARRAY[" << Index << L"] - [" << Parameter[Index] << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pri prenose C-ARRAYS BY-REFEREBCE NEDOCHADZA k TYPE DECAY.
template<typename TType>
void ParametersCArraysPassByReference(const TType& Parameter)
{
	wcout << L"BY REFERENCE - PROTOTYPE ["<< MACRO_FUNCTION_PROTOTYPE << L"]." << endl;

	size_t														ArraySize=extent<TType>::value;

	for(size_t Index=0;Index<ArraySize;Index++)
	{
		wcout << L"ARRAY[" << Index << L"] - [" << Parameter[Index] << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pri prenose C-ARRAYS BY-VALUE dochadza k TYPE DECAY na POINTER na 1. ARRAY ITEM.
template<typename TType>
void ParametersCArraysPassByValue(TType Array1, size_t ArraySize1, TType Array2, size_t ArraySize2)
{
	wcout << L"BY VALUE - PROTOTYPE ["<< MACRO_FUNCTION_PROTOTYPE << L"]." << endl;

	size_t														ArraySize;

	if (ArraySize1>ArraySize2)
	{
		ArraySize=ArraySize1;
	}
	else
	{
		ArraySize=ArraySize2;
	}

	for(size_t Index=0;Index<ArraySize;Index++)
	{
		wstringstream											Stream;

		Stream << L"ARRAY[" << Index << L"] - ";

		if (Index<ArraySize1)
		{
			Stream << L"[" << Array1[Index] << L"]";
		}
		else
		{
			Stream << L"NULL";
		}

		Stream << L" ";

		if (Index<ArraySize2)
		{
			Stream << L"[" << Array2[Index] << L"]";
		}
		else
		{
			Stream << L"NULL";
		}

		Stream << L"." << endl;

		wcout << Stream.str();
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pri prenose C-ARRAYS BY-REFEREBCE NEDOCHADZA k TYPE DECAY.
// !!!!! Nevyhodou prenosu C-ARRAYS ARGUMENTS BY-REFERENCE spociva v tom, ze kedze sa NEROBI DECAY, tak ak TEMPLATE FUNCTION ockava ako PARAMETERS C-ARRAYS pricom tieto TEMPLATE PARAMETERS maju ROVNAKY TYPE, tak vsetky C-ARRAY ARGUMENTS MUSIA mat ROVNAKY SIZE. Je to dosledok toho, ze pri prenose C-ARRAYS ARGUMENTS BY-REFERENCE je ARRAY SIZE sucastou PARAMETER TYPE a ak PARAMETERS maju rovnaky TYPE PARAMETER, tak C-ARRAY ARGUMENTS musia mat rovnaky SIZE.
template<typename TType>
void ParametersCArraysPassByReference(const TType& Array1, const TType& Array2)
{
	wcout << L"BY REFERENCE - PROTOTYPE ["<< MACRO_FUNCTION_PROTOTYPE << L"]." << endl;

	size_t														ArraySize1=extent<TType>::value;
	size_t														ArraySize2=extent<TType>::value;

	size_t														ArraySize;

	if (ArraySize1>ArraySize2)
	{
		ArraySize=ArraySize1;
	}
	else
	{
		ArraySize=ArraySize2;
	}

	for(size_t Index=0;Index<ArraySize;Index++)
	{
		wstringstream											Stream;

		Stream << L"ARRAY[" << Index << L"] - ";

		if (Index<ArraySize1)
		{
			Stream << L"[" << Array1[Index] << L"]";
		}
		else
		{
			Stream << L"NULL";
		}

		Stream << L" ";

		if (Index<ArraySize2)
		{
			Stream << L"[" << Array2[Index] << L"]";
		}
		else
		{
			Stream << L"NULL";
		}

		Stream << L"." << endl;

		wcout << Stream.str();
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersCArrays(void)
{
	PrintLineSeparator();

	{
		const size_t											SIZE=3;
		int														Array[SIZE]{10,20,30};

		// !!! PARAMETER TYPE je TYPE [int*]. Je to preto, lebo pri prenose C-ARRAYS BY-VALUES sa ROBI TYPE DECAY.
		ParametersCArraysPassByValue(Array,SIZE);
	}

	PrintLineSeparator();

	{
		int														Array[]{10,20,30};

		// !!! PARAMETER TYPE je TYPE [const int(&)[3]]. Je to preto, lebo pri prenose C-ARRAYS BY-REFERENCES sa NEROBI TYPE DECAY.
		ParametersCArraysPassByReference(Array);
	}

	PrintLineSeparator();

	{
		const size_t											SIZE1=3;
		int														Array1[SIZE1]{10,20,30};
		const size_t											SIZE2=4;
		int														Array2[SIZE2]{100,200,300,400};

		// !!! PARAMETER TYPE je TYPE [int*]. Je to preto, lebo pri prenose C-ARRAYS BY-VALUES sa ROBI TYPE DECAY.
		ParametersCArraysPassByValue(Array1,SIZE1,Array2,SIZE2);
	}

	PrintLineSeparator();

	{
		int														Array1[]{10,20,30};
		int														Array2[]{100,200,300};

		// !!!!! CODE zbehne IBA preto, ze C-ARRAYS maju ROVNAKE SIZES.
		// !!! PARAMETER TYPE je TYPE [const int(&)[3]] a TYPE [const int(&)[3]]. Je to preto, lebo pri prenose C-ARRAYS BY-REFERENCES sa NEROBI TYPE DECAY.
		ParametersCArraysPassByReference(Array1,Array2);
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR pretoze C-ARRAYS maju ROZNE SIZES, no TEMPLATE FUNCTION ocakavat pre obe PARAMETERS rovnaky TYPE. A kedze pri prenose C-ARRAYS BY-REFERENCE je ARRAY SIZE sucastou TYPE, tak C-ARRAY SIZES MUSIA byt ROVNAKE.
	{
		int														Array1[]{10,20,30};
		int														Array2[]{100,200,300,400};

		// !!! PARAMETER TYPE je TYPE [const int(&)[3]] a TYPE [const int(&)[4]]. Je to preto, lebo pri prenose C-ARRAYS BY-REFERENCES sa NEROBI TYPE DECAY.
		ParametersCArraysPassByReference(Array1,Array2);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Specialna TEMPLATE FUNCTION pre C-ARRAYS.
template<typename TType, size_t SIZE_1, size_t SIZE_2>
void ParametersCArraysParameters1(TType (&Array1)[SIZE_1], TType (&Array2)[SIZE_2])
{
	wcout << L"1 - PROTOTYPE ["<< MACRO_FUNCTION_PROTOTYPE << L"]." << endl;

	size_t														ArraySize;

	if (SIZE_1>SIZE_2)
	{
		ArraySize=SIZE_1;
	}
	else
	{
		ArraySize=SIZE_2;
	}

	for(size_t Index=0;Index<ArraySize;Index++)
	{
		wstringstream											Stream;

		Stream << L"ARRAY[" << Index << L"] - ";

		if (Index<SIZE_1)
		{
			Stream << L"[" << Array1[Index] << L"]";
		}
		else
		{
			Stream << L"NULL";
		}

		Stream << L" ";

		if (Index<SIZE_2)
		{
			Stream << L"[" << Array2[Index] << L"]";
		}
		else
		{
			Stream << L"NULL";
		}

		Stream << L"." << endl;

		wcout << Stream.str();
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Specialna TEMPLATE FUNCTION pre C-ARRAYS.
// !!!!! TEMPLATE FUNCTION je ENABLED IBA pre C-ARRAYS.
template<typename TType1, typename TType2, typename=enable_if<is_array<typename remove_reference<TType1>::type>::value>::type,typename=enable_if<is_array<typename remove_reference<TType2>::type>::value>>
void ParametersCArraysParameters2(TType1&& Array1, TType2&& Array2)
{
	wcout << L"2 - PROTOTYPE ["<< MACRO_FUNCTION_PROTOTYPE << L"]." << endl;

	// !!! Pomocou TYPE TRAIT [remove_reference_t<>] sa odstrani REFERENCE, aby sa ziskal iba C-ARRAY TYPE a z neho dlzka.
	size_t														ArraySize1=extent<typename remove_reference<TType1>::type>::value;
	size_t														ArraySize2=extent<typename remove_reference<TType2>::type>::value;

	size_t														ArraySize;

	if (ArraySize1>ArraySize2)
	{
		ArraySize=ArraySize1;
	}
	else
	{
		ArraySize=ArraySize2;
	}

	for(size_t Index=0;Index<ArraySize;Index++)
	{
		wstringstream											Stream;

		Stream << L"ARRAY[" << Index << L"] - ";

		if (Index<ArraySize1)
		{
			Stream << L"[" << Array1[Index] << L"]";
		}
		else
		{
			Stream << L"NULL";
		}

		Stream << L" ";

		if (Index<ArraySize2)
		{
			Stream << L"[" << Array2[Index] << L"]";
		}
		else
		{
			Stream << L"NULL";
		}

		Stream << L"." << endl;

		wcout << Stream.str();
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametersCArraysParameters(void)
{
	PrintLineSeparator();

	{
		int														Array1[]{10,20,30};
		int														Array2[]{100,200,300,400,500};

		ParametersCArraysParameters1(Array1,Array2);
	}

	PrintLineSeparator();

	{
		int														Array1[]{10,20,30};
		int														Array2[]{100,200,300,400,500};

		ParametersCArraysParameters2(Array1,Array2);
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE FUNCTION je ENABLED iba pre C-ARRAYS.
	{
		int														Value1=10;
		int														Value2=100;

		ParametersCArraysParameters2(Value1,Value2);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Aby sa zabranilo vrateniu REFERENCE TYPE na LOCAL VARIABLE, RETURN VALUE TYPE je obaleny TYPE TRAIT [remove_reference<>].
template<typename TType>
typename remove_reference<TType>::type TemplateFunctionReturnValueReferenceTypeDeduction1(TType Parameter)
{
	wcout << L"PARAMETER [" << Parameter << L"] PROTOTYPE [" << MACRO_FUNCTION_PROTOTYPE << L"]." << endl;

	// !!! Vytvori sa KOPIA.
	TType														Copy(Parameter);

	return(Copy);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Aby sa zabranilo vrateniu REFERENCE TYPE na LOCAL VARIABLE, pre RETURN VALUE TYPE je pouzity KEYWORD [auto], ktory VZDY sposobi TYPE DECAY.
template<typename TType>
auto TemplateFunctionReturnValueReferenceTypeDeduction2(TType Parameter)
{
	wcout << L"PARAMETER [" << Parameter << L"] PROTOTYPE [" << MACRO_FUNCTION_PROTOTYPE << L"]." << endl;

	// !!! Vytvori sa KOPIA.
	TType														Copy(Parameter);

	return(Copy);
}
//----------------------------------------------------------------------------------------------------------------------
void TestReturnValueReferenceTypeDeduction(void)
{
	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Argument(L"Timmy");

		wcout << L"ARGUMENT [" << Argument << L"]." << endl;

		// !!!!! TYPE PARAMETER ma TYPE [CClassWithCopyAndMove<wstring>&], no vdaka pouzitiu TYPE TRAIT [remove_reference<>] je RETURN VALUE TYPE [CClassWithCopyAndMove<wstring>].
		auto													ReturnValue=TemplateFunctionReturnValueReferenceTypeDeduction1<CClassWithCopyAndMove<wstring>&>(Argument);

		wcout << L"RETURN VALUE [" << ReturnValue << L"] RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMove<int>								Argument(100);

		wcout << L"ARGUMENT [" << Argument << L"]." << endl;

		// !!!!! TYPE PARAMETER ma TYPE [CClassWithCopyAndMove<int>&], no vdaka pouzitiu TYPE TRAIT [remove_reference<>] je RETURN VALUE TYPE [CClassWithCopyAndMove<int>].
		auto													ReturnValue=TemplateFunctionReturnValueReferenceTypeDeduction1<CClassWithCopyAndMove<int>&>(Argument);

		wcout << L"RETURN VALUE [" << ReturnValue << L"] RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMove<wstring>							Argument(L"Timmy");

		wcout << L"ARGUMENT [" << Argument << L"]." << endl;

		// !!!!! TYPE PARAMETER ma TYPE [CClassWithCopyAndMove<wstring>&], no vdaka pouzitiu KEYWORD [auto], ktory robi TYPE DECAY je RETURN VALUE TYPE [CClassWithCopyAndMove<wstring>].
		auto													ReturnValue=TemplateFunctionReturnValueReferenceTypeDeduction2<CClassWithCopyAndMove<wstring>&>(Argument);

		wcout << L"RETURN VALUE [" << ReturnValue << L"] RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMove<int>								Argument(100);

		wcout << L"ARGUMENT [" << Argument << L"]." << endl;

		// !!!!! TYPE PARAMETER ma TYPE [CClassWithCopyAndMove<int>&], no vdaka pouzitiu KEYWORD [auto], ktory robi TYPE DECAY je RETURN VALUE TYPE [CClassWithCopyAndMove<int>].
		auto													ReturnValue=TemplateFunctionReturnValueReferenceTypeDeduction2<CClassWithCopyAndMove<int>&>(Argument);

		wcout << L"RETURN VALUE [" << ReturnValue << L"] RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTION pracuje s PARAMETER TYPE [vector<>], a preto je lepsie pouzit TEMPLATE TYPE [vector<TYPE>], ako TEMPLATE TYPE [TYPE].
template<typename TType>
void TemplateSpecificTypeParameters(const vector<TType>& Collection)
{
	for(size_t Index=0;Index<Collection.size();Index++)
	{
		wcout << L"COLLECTION [" << Index << L"] VALUE [" << Collection[Index] << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestSpecificTypeParameters(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection;

		Collection.push_back(100);
		Collection.push_back(200);
		Collection.push_back(300);

		TemplateSpecificTypeParameters(Collection);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestMakePairPerfectForwarding(void)
{
	PrintLineSeparator();

	{
		// !!! VOLA sa MOVE CONSTRUCTOR, pretoze sa robi PERFECT FORWARDING.
		pair<CClassWithCopyAndMove<int>,CClassWithCopyAndMove<int>>	Pair=make_pair(CClassWithCopyAndMove<int>(100),CClassWithCopyAndMove<int>(200));

		wcout << L"VALUE 1 [" << Pair.first << L"] VALUE 2 [" << Pair.second << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestParametersByValue();
	//TestParametersByValueTypeDecay();
	//TestParametersByConstReference();
	//TestParametersByConstReferenceTypeDecay();
	//TestParametersByNonConstReference();
	//TestParametersByNonConstReferenceTypeDecay();
	//TestParametersByNonConstReferenceConstArgument();
	TestParametersByForwardReference();
	//TestRefAndCRef();
	//TestRefAndCRefInTemplateFunctions();
	//TestParametersCArrays();
	//TestParametersCArraysParameters();
	//TestReturnValueReferenceTypeDeduction();
	//TestSpecificTypeParameters();
	//TestMakePairPerfectForwarding();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------