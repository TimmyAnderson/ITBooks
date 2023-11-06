//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <array>
#include <sstream>
#include <vector>
#include <tuple>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "CTypeWithUsing.h"
#include "CTemplateArgumentDeductionContext.h"
#include "CDeductionContext1.h"
#include "CDeductionContext2.h"
#include "CDeductionContext3.h"
#include "CSpecialTemplateArgumentDeduction.h"
#include "CParameterPacksPair.h"
#include "CParameterPacksTuple.h"
#include "CValue1.h"
#include "CValue2.h"
#include "CNonForwardingReferences.h"
#include "CNoImmediateContext.h"
#include "CDeductionConversionsBase.h"
#include "CDeductionConversionsDerived.h"
#include "CDeductionConversions.h"
#include "CDeductionConversionsDerived1.h"
#include "CDeductionConversionsDerived2.h"
#include "CTemplateClassDeduction.h"
#include "CDeductionDefaultArguments.h"
#include "CDeductionExceptionSpecification.h"
#include "CPointerToMember.h"
#include "CSpecifierAutoReturnValueType.h"
#include "CDecltypeAutoNonTypeTemplateParameter.h"
#include "CStructuredBindingClassBase1.h"
#include "CStructuredBindingClassBase2.h"
#include "CStructuredBindingClassDerived1.h"
#include "CStructuredBindingClassDerived2.h"
#include "CStructuredBindingClassDerived3.h"
#include "CStructuredBindingCArrayValue.h"
#include "CStructuredBindingTupleFunctions.h"
#include "CStructuredBindingTupleMethods.h"
#include "CTemplateAlias.h"
#include "CTemplateClassDeductionImplicitGuide.h"
#include "CTemplateClassDeductionImplicitGuideSupression.h"
#include "CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1.h"
#include "CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2.h"
#include "CTemplateClassDeductionUserDefinedGuideConstructorsGuides.h"
#include "CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides.h"
#include "CTemplateClassDeductionInjectedClassNames.h"
#include "CTemplateClassDeductionForwardingReferences.h"
#include "CTemplateClassDeductionUserDefinedGuideNoExplicit.h"
#include "CTemplateClassDeductionUserDefinedGuideExplicit.h"
#include "CTemplateClassDeductionCopyConstruction.h"
#include "CTemplateClassDeductionOverloadedConstructorsInner.h"
#include "CTemplateClassDeductionOverloadedConstructorsOuter.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionTemplate1(TType Value1, TType Value2)
{
	wcout << L"FUNCTION 1 - TYPE [" << GetTypeInfoName<TType>() << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionTemplate2(typename TType::MyType Value)
{
	wcout << L"FUNCTION 2A - TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionTemplate2(TType Value)
{
	wcout << L"FUNCTION 2B - TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeduction(void)
{
	PrintLineSeparator();

	{
		TemplateArgumentDeductionTemplate1(100,200);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE ARGUMENTS maju rozdielne TYPES.
		TemplateArgumentDeductionTemplate1(100,222.222);
	}
	*/

	PrintLineSeparator();

	{
		// !!! Vola sa 1. OVERLOADED TEMPLATE FUNCTION.
		TemplateArgumentDeductionTemplate2<CTypeWithUsing>(100);
	}

	PrintLineSeparator();

	{
		// !!! Vola sa 2. OVERLOADED TEMPLATE FUNCTION.
		TemplateArgumentDeductionTemplate2<int>(100);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionReferenceTypesTemplate(TType Value)
{
	wcout << L"TEMPLATE PARAMETER - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeductionReferenceTypes(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		wcout << L"TEMPLATE ARGUMENT - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

		TemplateArgumentDeductionReferenceTypesTemplate(Value);
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;
		int&													Value=OriginalValue;

		wcout << L"TEMPLATE ARGUMENT - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

		// !!!!! DEDUCED TYPE je TYPE [int], a NIE TYPE [int&].
		TemplateArgumentDeductionReferenceTypesTemplate(Value);
	}

	PrintLineSeparator();

	{
		int&&													Value=100;

		wcout << L"TEMPLATE ARGUMENT - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

		// !!!!! DEDUCED TYPE je TYPE [int], a NIE TYPE [int&&].
		TemplateArgumentDeductionReferenceTypesTemplate(Value);
	}

	PrintLineSeparator();

	{
		int&&													Value=100;

		wcout << L"TEMPLATE ARGUMENT - TYPE [" << GetTypeInfoName<decltype(move(Value))>() << L"] VALUE [" << move(Value) << L"]." << endl;

		// !!!!! DEDUCED TYPE je TYPE [int], a NIE TYPE [int&&].
		TemplateArgumentDeductionReferenceTypesTemplate(move(Value));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionDecayTemplateByValue(TType Value)
{
	wcout << L"FUNCTION BY VALUE - TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionDecayTemplateByReference(TType& Value)
{
	wcout << L"FUNCTION BY REFERENCE - TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeductionDecay(void)
{
	PrintLineSeparator();

	{
		int														Array[4]={100,200,300,400};

		// !!! Vykonava sa DECAY C-ARRAY na POINTER.
		TemplateArgumentDeductionDecayTemplateByValue(Array);
	}

	PrintLineSeparator();

	{
		int														Array[4]={100,200,300,400};

		// !!! Kedze PARAMETER je REFERENCE TYPE, tak sa NEVYKONAVA DECAY. PARAMETER ma TYPE C-ARRAY REFERENCE.
		TemplateArgumentDeductionDecayTemplateByReference(Array);
	}

	PrintLineSeparator();

	{
		const int												Value=100;

		// !!! Vykonava sa DECAY TYPE [const int] na TYPE [int].
		TemplateArgumentDeductionDecayTemplateByValue(Value);
	}

	PrintLineSeparator();

	{
		const int												Value=100;

		// !!! Kedze PARAMETER je REFERENCE TYPE, tak sa NEVYKONAVA DECAY. PARAMETER ma TYPE [const int].
		TemplateArgumentDeductionDecayTemplateByReference(Value);
	}

	PrintLineSeparator();

	{
		// !!! Vykonava sa DECAY na TYPE [int].
		TemplateArgumentDeductionDecayTemplateByValue(100);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR.
		TemplateArgumentDeductionDecayTemplateByReference(100);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION ma PARAMETER TYPE POINTER.
template<typename TType>
void TemplateArgumentDeductionContextTemplate1(TType* Value)
{
	wcout << L"FUNCTION 1 - TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION ma PARAMETER TYPE REFERENCE na C-ARRAY.
template<typename TType, size_t SIZE>
void TemplateArgumentDeductionContextTemplate2(TType(&Array)[SIZE])
{
	wcout << L"FUNCTION 2 - TYPE [" << GetTypeInfoName<TType>() << L"] SIZE [" << SIZE << L"]." << endl;

	for(size_t Index=0;Index<SIZE;Index++)
	{
		const TType												Value=Array[Index];

		wcout << L"ARRAY[" << Index << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION ma PARAMETER TYPE POINTER na METHOD [TType1 (TType2::*)(const TType3&)].
template<typename TType1, typename TType2, typename TType3>
void TemplateArgumentDeductionContextTemplate3(TType1 (TType2::*PointerToMethod)(const TType3&) const, const TType2& Object, TType3 Value)
{
	wcout << L"FUNCTION 3 - TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"] TYPE 3 [" << GetTypeInfoName<TType3>() << L"]." << endl;

	(Object.*PointerToMethod)(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<int VALUE>
void TemplateArgumentDeductionContextTemplate4(void (CDeductionContext1<VALUE>::*PointerToMethod)(typename CDeductionContext1<VALUE>::MyType) const)
{
	wcout << L"FUNCTION 4 - VALUE [" << VALUE << L"]." << endl;

	CDeductionContext1<VALUE>									Object(L"Timmy");

	(Object.*PointerToMethod)(200);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionContextTemplate5(CDeductionContext2<CDeductionContext3<TType>,CDeductionContext3<TType>> Value)
{
	wcout << L"FUNCTION 5 - TYPE [" << GetTypeInfoName<TType>() << L"] VALUE 1 [" << Value.GetField1().GetField() << L"] VALUE 2 [" << Value.GetField2().GetField() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeductionContext(void)
{
	PrintLineSeparator();

	{
		int														Value=100;
		int*													Pointer1=&Value;
		int**													Pointer2=&Pointer1;
		int***													Pointer3=&Pointer2;

		TemplateArgumentDeductionContextTemplate1(Pointer3);

		wcout << L"VALUE [" << (***Pointer3) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Array[4]={100,200,300,400};

		TemplateArgumentDeductionContextTemplate2(Array);
	}

	PrintLineSeparator();

	{
		CTemplateArgumentDeductionContext						Object(L"Timmy");

		// !!!!! C++ dokaze uspesne identifikovat TEMPLATE TYPE PARAMETER ako POINTER na METHOD.
		TemplateArgumentDeductionContextTemplate3(&CTemplateArgumentDeductionContext::Multiple2,Object,100);
	}

	PrintLineSeparator();

	{
		// !!!!! C++ dokaze uspesne identifikovat TEMPLATE NON-TYPE PARAMETER [VALUE].
		TemplateArgumentDeductionContextTemplate4(&CDeductionContext1<100>::MyMethod);
	}

	PrintLineSeparator();

	{
		CDeductionContext3<CString>								Object1(L"Timmy");
		CDeductionContext3<CString>								Object2(L"Anderson");
		CDeductionContext2<CDeductionContext3<CString>,CDeductionContext3<CString>>	Object(Object1,Object2);

		// !!!!! C++ dokaze uspesne identifikovat TEMPLATE PARAMETER [TType] ako TYPE [CString] z TEMPLATE ARGUMENT [CDeductionContext2<CDeductionContext3<CString>,CDeductionContext3<CString>>].
		TemplateArgumentDeductionContextTemplate5(Object);
	}

	/*
	PrintLineSeparator();

	{
		CDeductionContext3<CString>								Object1(L"Timmy");
		CDeductionContext3<int>									Object2(12);
		CDeductionContext2<CDeductionContext3<CString>,CDeductionContext3<int>>	Object(Object1,Object2);

		// !!!!! COMPILER hodi ERROR, pretoze TYPE PARAMETER [TType] ma v oboch TEMPLATE PARAMETERS iny TYPE, hoci FUNCTION predpoklada rovnaky.
		TemplateArgumentDeductionContextTemplate5(Object);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void SpecialTemplateArgumentDeductionTemplate(TType1 Value1, TType2 Value2)
{
	wcout << L"FUNCTION - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestSpecialTemplateArgumentDeduction(void)
{
	PrintLineSeparator();

	{
		// !!!!! C++ NEVYKONAVA TEMPLATE ARGUMENT DEDUCTION na zaklade ARGUMENTS zadany pocas volania TEMPLATE FUNCTION, ale z FUNCTION TYPE.
		void													(*PointerToFunction)(CString,int)=&SpecialTemplateArgumentDeductionTemplate;

		(*PointerToFunction)(L"Timmy",12);
	}

	PrintLineSeparator();

	{
		CSpecialTemplateArgumentDeduction						Object(123.456);

		wcout << L"OBJECT - VALUE [" << Object.GetValue() << L"]." << endl;

		// !!!!! C++ vykonava TEMPLATE ARGUMENT DEDUCTION na zaklade RETURN VALUE TYPE na ktoru ma CONVERSION OPERATOR vykonat CONVERSION.
		int														ConvertedValue=Object;

		wcout << L"CONVERTED VALUE [" << ConvertedValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionInitializerLists(initializer_list<TType> Values)
{
	size_t														Index=0;

	for(const TType& Value : Values)
	{
		wcout << L"INDEX [" << ++Index << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionNoInitializerLists(TType Value)
{
	wcout << L"VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeductionInitializerLists(void)
{
	PrintLineSeparator();

	{
		TemplateArgumentDeductionInitializerLists({100,200,300});
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze ITEMS v INITIALIZER LIST nemaju rovnaky TYPE.
		TemplateArgumentDeductionInitializerLists({100,200,333.333});
	}
	*/

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze nedokaze vykonat TEMPLATE ARGUMENT DEDUCTION pre INITIALIZER LIST ako TEMPLATE ARGUMENT, ak TEMPLATE PARAMETER nie je INITIALIZER LIST.
		TemplateArgumentDeductionNoInitializerLists({100,200,300});
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename... TTypes>
void TemplateArgumentDeductionParameterPacksTemplateInternal1(size_t Index, CParameterPacksPair<TType1,TType2> Value, CParameterPacksPair<TType1,TTypes>... Values)
{
	wcout << L"FUNCTION 1 - TEMPLATE PARAMETER [" << Index << L"] VALUE [VALUE 1 [" << Value.GetValue1() << L"] VALUE 2 [" << Value.GetValue2() << L"]]." << endl;

	if constexpr (sizeof...(Values)>0)
	{
		TemplateArgumentDeductionParameterPacksTemplateInternal1(Index+1,Values...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION VYZADUJE, aby vsetky instancie CLASS [CParameterPacksPair<TType,TTypes>] mali ROVNAKY 1. TEMPLATE PARAMETER.
template<typename TType, typename... TTypes>
void TemplateArgumentDeductionParameterPacksTemplate1(CParameterPacksPair<TType,TTypes>... Values)
{
	TemplateArgumentDeductionParameterPacksTemplateInternal1(1,Values...);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename... TTypes1, typename... TTypes2>
void TemplateArgumentDeductionParameterPacksTemplateInternal2(size_t Index, CParameterPacksPair<TType1,TType2> Value, CParameterPacksPair<TTypes1,TTypes2>... Values)
{
	wcout << L"FUNCTION 2 - TEMPLATE PARAMETER [" << Index << L"] VALUE [VALUE 1 [" << Value.GetValue1() << L"] VALUE 2 [" << Value.GetValue2() << L"]]." << endl;

	if constexpr (sizeof...(Values)>0)
	{
		TemplateArgumentDeductionParameterPacksTemplateInternal2(Index+1,Values...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes1, typename... TTypes2>
void TemplateArgumentDeductionParameterPacksTemplate2(CParameterPacksPair<TTypes1,TTypes2>... Values)
{
	TemplateArgumentDeductionParameterPacksTemplateInternal2(1,Values...);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION VYZADUJE, aby vsetky instancie CLASS [CParameterPacksTuple<TTypes>] mali ROVNAKE TEMPLATE PARAMETERS.
template<typename... TTypes>
void TemplateArgumentDeductionParameterPacksTemplate3(CParameterPacksTuple<TTypes...> Value1, CParameterPacksTuple<TTypes...> Value2)
{
	wcout << L"FUNCTION 3 - VALUE 1 [" << Value1.Print() << L"] VALUE 2 [" << Value2.Print() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes1, typename... TTypes2>
void TemplateArgumentDeductionParameterPacksTemplate4(CParameterPacksTuple<TTypes1...> Value1, CParameterPacksTuple<TTypes2...> Value2)
{
	wcout << L"FUNCTION 4 - VALUE 1 [" << Value1.Print() << L"] VALUE 2 [" << Value2.Print() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<char... CHARACTERS>
int operator"" _XXX()
{
	array<char,sizeof...(CHARACTERS)>							Characters{CHARACTERS...};

	int															Result=0;
	wstringstream												Stream;

	for(char Character : Characters)
	{
		int														Value=(Character-'0');

		Result*=10;
		Result+=Value;

		wchar_t													WideCharacter=ConvertCharToWideChar(Character);

		Stream << WideCharacter;
	}

	wcout << L"USER DEFINED LITERAL [" << Stream.str() << L"]." << endl;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeductionParameterPacks(void)
{
	PrintLineSeparator();

	{
		CParameterPacksPair<CString,int>						Value1(L"Timmy",12);
		CParameterPacksPair<CString,double>						Value2(L"Timmy",12.13);

		TemplateArgumentDeductionParameterPacksTemplate1(Value1,Value2);
	}

	/*
	PrintLineSeparator();

	{
		CParameterPacksPair<bool,int>							Value1(true,12);
		CParameterPacksPair<CString,double>						Value2(L"Timmy",12.13);

		// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE PARAMETER PACK predpoklada, ze PRVY TEMPLATE PARAMETER v TYPE [CParameterPacksPair<TType,TTypes>] je ROVNAKY TYPE.
		TemplateArgumentDeductionParameterPacksTemplate1(Value1,Value2);
	}
	*/

	PrintLineSeparator();

	{
		CParameterPacksPair<CString,int>						Value1(L"Timmy",12);
		CParameterPacksPair<CString,double>						Value2(L"Timmy",12.13);

		TemplateArgumentDeductionParameterPacksTemplate2(Value1,Value2);
	}

	PrintLineSeparator();

	{
		CParameterPacksPair<bool,int>							Value1(true,12);
		CParameterPacksPair<CString,double>						Value2(L"Timmy",12.13);

		TemplateArgumentDeductionParameterPacksTemplate2(Value1,Value2);
	}

	PrintLineSeparator();

	{
		CParameterPacksTuple<CString,int>						Value1(L"Timmy",12);
		CParameterPacksTuple<CString,int>						Value2(L"Jenny",13);

		TemplateArgumentDeductionParameterPacksTemplate3(Value1,Value2);
	}

	/*
	PrintLineSeparator();

	{
		CParameterPacksTuple<CString,int>						Value1(L"Timmy",12);
		CParameterPacksTuple<CString,double>					Value2(L"Jenny",13.123);

		// !!!!! COMPILER hodi ERROR, pretoze CLASSES [CParameterPacksTuple<TTypes>] NEMAJU rovnake VARIADIC TEMPLATE PARAMETERS.
		TemplateArgumentDeductionParameterPacksTemplate3(Value1,Value2);
	}
	*/

	PrintLineSeparator();

	{
		CParameterPacksTuple<CString,int>						Value1(L"Timmy",12);
		CParameterPacksTuple<CString,int>						Value2(L"Jenny",13);

		TemplateArgumentDeductionParameterPacksTemplate4(Value1,Value2);
	}

	PrintLineSeparator();

	{
		CParameterPacksTuple<CString,int>						Value1(L"Timmy",12);
		CParameterPacksTuple<CString,double>					Value2(L"Jenny",13.123);

		TemplateArgumentDeductionParameterPacksTemplate4(Value1,Value2);
	}

	PrintLineSeparator();

	{
		// !!!!! VOLA sa USER DEFINED LITERAL, ktory je implementovany ako TEMPLATE FUNCTION.
		int														Value=123_XXX;

		wcout << L"VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestReferenceToReference(void)
{
	PrintLineSeparator();

	{
		const int&												LValueReference=100;

		wcout << L"LVALUE REFERENCE [" << LValueReference << L"]." << endl;
	}

	PrintLineSeparator();

	{
		const int&&												RValueReference=100;

		wcout << L"RVALUE REFERENCE [" << RValueReference << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! C++ NEUMOZNUJE deklarovat REFERENCE na REFERENCE a preto COMPILER hodi ERROR.
		const int& &											ReferenceToReference=100;

		wcout << L"REFERENCE TO REFERENCE [" << ReferenceToReference << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		using													TypeReference=int&;

		int														Value=100;
		TypeReference											Reference=Value;

		// !!!!! C++ UMOZNUJE deklarovat REFERENCE na REFERENCE pri vytvarani TYPES pomocou ALIASES.
		// !!!!! Vdaka REFERENCE COLLAPSING RULES je vysledny TYPE [int&].
		const TypeReference&									ReferenceToReference=Reference;

		wcout << L"REFERENCE [" << Reference << L"]." << endl;
		wcout << L"REFERENCE TO REFERENCE [" << ReferenceToReference << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestReferenceCollapsingRules(void)
{
	PrintLineSeparator();

	{
		using													TypeLValueReference=const int&;

		int														Value=100;
		TypeLValueReference										LValueReference=Value;

		// !!!!! Vdaka REFERENCE COLLAPSING RULES je vysledny TYPE [const int&]. Najvrchnejsi MODIFIER [volatile] je aplikaciou REFERENCE COLLAPSING RULES ODSTRANENY.
		volatile TypeLValueReference&							LValueReferenceToLValueReference=LValueReference;

		wcout << L"LVALUE REFERENCE TO LVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(LValueReferenceToLValueReference)>() << L"] VALUE [" << LValueReferenceToLValueReference << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													TypeRValueReference=const int&&;

		TypeRValueReference										RValueReference=100;

		// !!!!! Vdaka REFERENCE COLLAPSING RULES je vysledny TYPE [const int&]. Najvrchnejsi MODIFIER [volatile] je aplikaciou REFERENCE COLLAPSING RULES ODSTRANENY.
		volatile TypeRValueReference&							LValueReferenceToRValueReference=RValueReference;

		wcout << L"LVALUE REFERENCE TO RVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(LValueReferenceToRValueReference)>() << L"] VALUE [" << LValueReferenceToRValueReference << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													TypeLValueReference=const int&;

		int														Value=100;
		TypeLValueReference										LValueReference=Value;

		// !!!!! Vdaka REFERENCE COLLAPSING RULES je vysledny TYPE [const int&]. Najvrchnejsi MODIFIER [volatile] je aplikaciou REFERENCE COLLAPSING RULES ODSTRANENY.
		volatile TypeLValueReference&&							RValueReferenceToLValueReference=LValueReference;

		wcout << L"RVALUE REFERENCE TO LVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(RValueReferenceToLValueReference)>() << L"] VALUE [" << RValueReferenceToLValueReference << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													TypeRValueReference=const int&&;

		// !!!!! Vdaka REFERENCE COLLAPSING RULES je vysledny TYPE [const int&&]. Najvrchnejsi MODIFIER [volatile] je aplikaciou REFERENCE COLLAPSING RULES ODSTRANENY.
		volatile TypeRValueReference&&							RValueReferenceToRValueReference=100;

		wcout << L"RVALUE REFERENCE TO RVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(RValueReferenceToRValueReference)>() << L"] VALUE [" << RValueReferenceToRValueReference << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Na FORWARDING REFERENCES C++ pri TEMPLATE ARGUMENT DEDUCTION aplikuje specialny RULE.
template<typename TType>
void TemplateArgumentDeductionForwardingReferenceTemplate1(TType&& ForwardingReference)
{
	wcout << L"TEMPLATE FUNCTION 1 - TEMPLATE PARAMETER TYPE [" << GetTypeInfoName<TType>() << L"] PARAMETER TYPE [" << GetTypeInfoName<decltype(ForwardingReference)>() << L"] VALUE [" << ForwardingReference << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Na FORWARDING REFERENCES C++ pri TEMPLATE ARGUMENT DEDUCTION aplikuje specialny RULE.
template<typename TType>
void TemplateArgumentDeductionForwardingReferenceTemplate2(TType&& ForwardingReference)
{
	// !!!!! Ak je TEMPLATE PARAMETER LVALUE REFERENCE, tak COMPILER hodi ERROR, TEMPLATE PARAMETER DEDUCTION urci za TYPE [TType] LVALUE REFERENCE. No a LOCAL VARIABLE TYPE LVALUE REFERENCE nie je INICIALIZOVANA.
	TType														LocalVariable;

	LocalVariable=ForwardingReference;

	wcout << L"TEMPLATE FUNCTION 2 - TEMPLATE PARAMETER TYPE [" << GetTypeInfoName<TType>() << L"] PARAMETER - TYPE [" << GetTypeInfoName<decltype(ForwardingReference)>() << L"] VALUE [" << ForwardingReference << L"]." << endl;
	wcout << L"TEMPLATE FUNCTION 2 - LOCAL VARIABLE - TYPE [" << GetTypeInfoName<decltype(LocalVariable)>() << L"] VALUE [" << LocalVariable << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeductionForwardingReference(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		// !!! TEMPLATE ARGUMENT je TYPE [int&]. C++ urci pomocou DEDUCTION TYPE TEMPLATE PARAMETER TYPE [int&]. PARAMETER TEMPLATE FUNCTION po aplikovani REFERENCE COLLAPSING RULES ma TYPE [int&].
		TemplateArgumentDeductionForwardingReferenceTemplate1(Value);
	}

	PrintLineSeparator();

	{
		const int														Value=200;

		// !!! TEMPLATE ARGUMENT je TYPE [const int&]. C++ urci pomocou DEDUCTION TYPE TEMPLATE PARAMETER TYPE [const int&]. PARAMETER TEMPLATE FUNCTION po aplikovani REFERENCE COLLAPSING RULES ma TYPE [const int&].
		TemplateArgumentDeductionForwardingReferenceTemplate1(Value);
	}

	PrintLineSeparator();

	{
		// !!! TEMPLATE ARGUMENT je TYPE [int&&]. C++ urci pomocou DEDUCTION TYPE TEMPLATE PARAMETER TYPE [int]. PARAMETER TEMPLATE FUNCTION ma TYPE [int&&].
		TemplateArgumentDeductionForwardingReferenceTemplate1(300);
	}

	/*
	PrintLineSeparator();

	{
		int														Value=100;

		// !!! TEMPLATE ARGUMENT je TYPE [int&]. C++ urci pomocou DEDUCTION TYPE TEMPLATE PARAMETER TYPE [int&]. PARAMETER TEMPLATE FUNCTION po aplikovani REFERENCE COLLAPSING RULES ma TYPE [int&].
		// !!!!! COMPILER hodi ERROR, pretoze v TEMPLATE FUNCTION je NENAINICIALIZOVANA LOCAL VARIABLE TYPE [TType], ktoru C++ pomocou DEDUCTION TYPE urci ako TEMPLATE PARAMETER TYPE [int&].
		TemplateArgumentDeductionForwardingReferenceTemplate2(Value);
	}
	*/

	PrintLineSeparator();

	{
		// !!! TEMPLATE ARGUMENT je TYPE [int&&]. C++ urci pomocou DEDUCTION TYPE TEMPLATE PARAMETER TYPE [int]. PARAMETER TEMPLATE FUNCTION ma TYPE [int&&].
		TemplateArgumentDeductionForwardingReferenceTemplate2(300);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTargetFunction(const CValue1& Value)
{
	wcout << L"TARGET FUNCTION - VALUE 1 - CONST LVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTargetFunction(CValue1& Value)
{
	wcout << L"TARGET FUNCTION - VALUE 1 - NON-CONST LVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTargetFunction(CValue1&& Value)
{
	wcout << L"TARGET FUNCTION - VALUE 1 - RVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTargetFunction(const CValue2& Value)
{
	wcout << L"TARGET FUNCTION - VALUE 2 - CONST LVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTargetFunction(CValue2& Value)
{
	wcout << L"TARGET FUNCTION - VALUE 2 - NON-CONST LVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTargetFunction(CValue2&& Value)
{
	wcout << L"TARGET FUNCTION - VALUE 2 - RVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Ako PARAMETER FORWARDER FUNCTION MUSI byt RVALUE REFERENCE.
template<typename TType>
void PerfectForwardingForwarderFunction(TType&& Value)
{
	wcout << L"FORWARDER FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue() << L"]." << endl;

	// !!!!! Vykona sa PERFECT FORWARDING.
	// !!!!! Ak je TYPE [TType] CONST LVALUE REFERENCE tak po aplikovani CODE [static_cast<TType&&>(Value)] ostane CONST LVALUE REFERENCE.
	// !!!!! Ak je TYPE [TType] NON-CONST LVALUE REFERENCE tak po aplikovani CODE [static_cast<TType&&>(Value)] ostane NON-CONST LVALUE REFERENCE.
	// !!!!! Ak je TYPE [TType] RVALUE REFERENCE tak po aplikovani CODE [static_cast<TType&&>(Value)] ostane RVALUE REFERENCE.
	// !!!!! Ak by sa CAST v CODE [static_cast<TType&&>(Value)] NEAPLIKOVAL, tak by C++ z bezpecnostnych dovodov vykonalo IMPLICIT CONVERSION na TYPE CONST LVALUE REFERENCE, alebo NON-CONST LVALUE REFERENCE a to aj vtedy, ak by TYPE [TType] bol RVALUE REFERENCE.
	PerfectForwardingTargetFunction(static_cast<TType&&>(Value));
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTargetFunctionPointers(int* Value)
{
	wcout << L"TARGET FUNCTION - POINTER PARAMETER - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PerfectForwardingTargetFunctionPointers(...)
{
	wcout << L"TARGET FUNCTION - ELLIPSIS PARAMETER." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Ako PARAMETER FORWARDER FUNCTION MUSI byt RVALUE REFERENCE.
template<typename TType>
void PerfectForwardingForwarderFunctionPointers(TType&& Value)
{
	wcout << L"FORWARDER FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

	// !!!!! Vykona sa PERFECT FORWARDING.
	PerfectForwardingTargetFunctionPointers(static_cast<TType&&>(Value));
}
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectForwarding(void)
{
	PrintLineSeparator();

	{
		const CValue1											Value(100);

		// !!!!! Zavola sa TARGET FUNCTION pre CONST LVALUE REFERENCE.
		PerfectForwardingForwarderFunction(Value);
	}

	PrintLineSeparator();

	{
		CValue1													Value(200);

		// !!!!! Zavola sa TARGET FUNCTION pre NON-CONST LVALUE REFERENCE.
		PerfectForwardingForwarderFunction(Value);
	}

	PrintLineSeparator();

	{
		// !!!!! Zavola sa TARGET FUNCTION pre RVALUE REFERENCE.
		PerfectForwardingForwarderFunction(CValue1(300));
	}

	PrintLineSeparator();

	{
		CValue1													Value(400);

		// !!!!! Zavola sa TARGET FUNCTION pre RVALUE REFERENCE.
		PerfectForwardingForwarderFunction(move(Value));
	}

	PrintLineSeparator();

	{
		// !!!!! Vola FUNCTION s POINTER PARAMETER.
		PerfectForwardingTargetFunctionPointers(0);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola FUNCTION s ELLIPSIS PARAMETER, co je NELOGICKE.
		PerfectForwardingForwarderFunctionPointers(0);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola FUNCTION s POINTER PARAMETER.
		PerfectForwardingTargetFunctionPointers(nullptr);
	}

	PrintLineSeparator();

	{
		// !!!!! Vola FUNCTION s POINTER PARAMETER.
		PerfectForwardingForwarderFunctionPointers(nullptr);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void PerfectForwardingForwarderFunctionVariadicInternal(TType&& Value, TTypes&&... Values)
{
	wcout << L"FORWARDER FUNCTION INTERNAL - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue() << L"]." << endl;

	// !!!!! Vykona sa PERFECT FORWARDING.
	PerfectForwardingTargetFunction(static_cast<TType&&>(Value));

	if constexpr (sizeof...(Values)>0)
	{
		PerfectForwardingForwarderFunctionVariadicInternal(static_cast<TTypes&&>(Values)...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Ako PARAMETER FORWARDER FUNCTION MUSI byt RVALUE REFERENCE. Tym padom sa PARAMETER stava FORWARDING REFERENCE a C++ pren aplikuje specialny RULE pri TEMPLATE ARGUMENT DEDUCTION.
template<typename... TTypes>
void PerfectForwardingForwarderFunctionVariadic(TTypes&&... Values)
{
	wcout << L"FORWARDER FUNCTION CALLED." << endl;

	// !!!!! Vykona sa PERFECT FORWARDING.
	PerfectForwardingForwarderFunctionVariadicInternal(static_cast<TTypes&&>(Values)...);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CValue1 PerfectForwardingTargetFunctionVariadicReturnValue(TTypes&&... Values)
{
	wcout << L"TARGET FUNCTION RETURN VALUE - NUMBER OF PARAMETERS [" << sizeof...(Values) << L"]." << endl;

	CValue1														ReturnValue(999);

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Ako PARAMETER FORWARDER FUNCTION MUSI byt RVALUE REFERENCE. Tym padom sa PARAMETER stava FORWARDING REFERENCE a C++ pren aplikuje specialny RULE pri TEMPLATE ARGUMENT DEDUCTION.
template <typename... TTypes>
auto PerfectForwardingForwarderFunctionVariadicReturnValue1(TTypes&&... Values) -> decltype(PerfectForwardingTargetFunctionVariadicReturnValue(static_cast<TTypes&&>(Values)...))
{
	wcout << L"FORWARDER FUNCTION RETURN VALUE 1 - NUMBER OF PARAMETERS [" << sizeof...(Values) << L"]." << endl;

	// !!!!! Vykona sa PERFECT FORWARDING, vratane RETURN VALUE TYPE.
	return(PerfectForwardingTargetFunctionVariadicReturnValue(static_cast<TTypes&&>(Values)...));
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Ako PARAMETER FORWARDER FUNCTION MUSI byt RVALUE REFERENCE. Tym padom sa PARAMETER stava FORWARDING REFERENCE a C++ pren aplikuje specialny RULE pri TEMPLATE ARGUMENT DEDUCTION.
template <typename... TTypes>
decltype(auto) PerfectForwardingForwarderFunctionVariadicReturnValue2(TTypes&&... Values)
{
	wcout << L"FORWARDER FUNCTION RETURN VALUE 2 - NUMBER OF PARAMETERS [" << sizeof...(Values) << L"]." << endl;

	// !!!!! Vykona sa PERFECT FORWARDING, vratane RETURN VALUE TYPE.
	return(PerfectForwardingTargetFunctionVariadicReturnValue(static_cast<TTypes&&>(Values)...));
}
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectForwardingVariadic(void)
{
	PrintLineSeparator();

	{
		const CValue1											Value1A(100);
		CValue1													Value1B(200);
		const CValue2											Value2A(400);
		CValue2													Value2B(500);

		PerfectForwardingForwarderFunctionVariadic(Value1A,Value1B,CValue1(300),Value2A,Value2B,CValue2(600));
	}

	PrintLineSeparator();

	{
		const CValue1											Value1A(100);
		CValue1													Value1B(200);
		const CValue2											Value2A(400);
		CValue2													Value2B(500);

		CValue1													ReturnValue=PerfectForwardingForwarderFunctionVariadicReturnValue1(Value1A,Value1B,CValue1(300),Value2A,Value2B,CValue2(600));

		wcout << L"RETURN VALUE [" << ReturnValue.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		const CValue1											Value1A(100);
		CValue1													Value1B(200);
		const CValue2											Value2A(400);
		CValue2													Value2B(500);

		CValue1													ReturnValue=PerfectForwardingForwarderFunctionVariadicReturnValue2(Value1A,Value1B,CValue1(300),Value2A,Value2B,CValue2(600));

		wcout << L"RETURN VALUE [" << ReturnValue.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ vykonava standardny TEMPLATE ARGUMENT DEDUCTION.
template<typename TType>
void DeductionSurprisesTemplateNoReference(TType Value)
{
	wcout << L"NO REFERENCE TEMPLATE FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void DeductionSurprisesNonTemplateLValues(int& Value)
{
	wcout << L"LVALUE NON-TEMPLATE FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ vykonava standardny TEMPLATE ARGUMENT DEDUCTION.
template<typename TType>
void DeductionSurprisesTemplateLValues(TType& Value)
{
	wcout << L"LVALUE TEMPLATE FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void DeductionSurprisesNonTemplateRValues(int&& Value)
{
	wcout << L"RVALUE NON-TEMPLATE FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze, TEMPLATE PARAMETER je FORWARDING REFERENCE, C++ aplikuje specialny RULE pre TEMPLATE ARGUMENT DEDUCTION.
// !!! 1. Pri FORWARDING REFERENCES TEMPLATE ARGUMENT DEDUCTION berie do uvahy nielen TYPE TEMPLATE ARGUMENT, ale aj to ci TEMPLATE ARGUMENT je LVALUE REFERENCE, alebo RVALUE REFERENCE.
// !!! 2. Ak pri FORWARDING REFERENCES je TEMPLATE ARGUMENT LVALUE REFERENCE, tak za TEMPLATE PARAMETER je substituovany LVALUE REFRENCE. Kedze vsak PARAMETER TEMPLATE FUNCTION je FORWARDING REFERENCE a teda RVALUE REFERENCE, po aplikovani REFERENCE COLLAPSING RULES je vysledny TYPE LVALUE REFERENCE.
// !!! 3. Ak pri FORWARDING REFERENCES je TEMPLATE ARGUMENT iny ako LVALUE REFERENCE, tak za TEMPLATE PARAMETER je substituovany NON-REFERENCE TYPE. Kedze vsak PARAMETER TEMPLATE FUNCTION je FORWARDING REFERENCE a teda RVALUE REFERENCE, tak vysledny TYPE je RVALUE REFERENCE.
template<typename TType>
void DeductionSurprisesTemplateRValues(TType&& Value)
{
	wcout << L"RVALUE TEMPLATE FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestForwardingReferenceDeductionSurprises(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		// !!! Dedukuje sa NON-REFERENCE TYPE [int].
		DeductionSurprisesTemplateNoReference(Value);
	}

	PrintLineSeparator();

	{
		int														Value=100;

		DeductionSurprisesNonTemplateLValues(Value);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze NEAKCEPTUJE RVALUE VALUES.
		DeductionSurprisesNonTemplateLValues(200);
	}
	*/

	PrintLineSeparator();

	{
		int														Value=100;

		DeductionSurprisesTemplateLValues(Value);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze NEAKCEPTUJE RVALUE VALUES.
		DeductionSurprisesTemplateLValues(200);
	}
	*/

	/*
	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! COMPILER hodi ERROR, pretoze NEAKCEPTUJE LVALUE VALUES.
		DeductionSurprisesNonTemplateRValues(Value);
	}
	*/

	PrintLineSeparator();

	{
		DeductionSurprisesNonTemplateRValues(200);
	}

	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! C++ akcpetuje LVALUE vdaka aplikovanie specialneho RULE pre FORWARDING REFERENCES.
		DeductionSurprisesTemplateRValues(Value);
	}

	PrintLineSeparator();

	{
		DeductionSurprisesTemplateRValues(200);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestNonForwardingReferences(void)
{
	PrintLineSeparator();

	/*
	{
		int														Value=100;

		// !!!!! COMPILER hodi ERROR, pretoze CONSTRUCTOR PARAMETER NIE JE TEMPLATE METHOD a preto sa NEAPLIKUJE RULE pre TEMPLATE ARGUMENT DEDUCTION FORWARDING REFERENCES. Tym padom NIE JE mozne do CONSTRUCTOR, ktory ocakava RVALUE REFERENCE poslat LVALUE REFERENCE.
		CNonForwardingReferences<int>							Object(Value);

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
	*/

	{
		CNonForwardingReferences<int>							Object(100);

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CNonForwardingReferences<int>							InnerObject(100);

		// !!!!! COMPILER hodi ERROR, pretoze JE TEMPLATE METHOD, ale PARAMETER NIE JE FORWARDING REFERENCE, a preto sa NEAPLIKUJE RULE pre TEMPLATE ARGUMENT DEDUCTION FORWARDING REFERENCES. Tym padom NIE JE mozne do CONSTRUCTOR, ktory ocakava RVALUE REFERENCE poslat LVALUE REFERENCE.
		CNonForwardingReferences<double>						Object(InnerObject);

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		CNonForwardingReferences<double>						Object(CNonForwardingReferences<int>(100));

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, unsigned SIZE>
TType* SFINAETemplateBegin(TType (&Array)[SIZE])
{
	TType*														Result=Array;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
typename TType::iterator SFINAETemplateBegin(TType& Container)
{
	typename TType::iterator									Result=Container.begin();

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, unsigned SIZE>
TType* SFINAETemplateEnd(TType (&Array)[SIZE])
{
	TType*														Result=(Array+SIZE);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
typename TType::iterator SFINAETemplateEnd(TType& Container)
{
	typename TType::iterator									Result=Container.end();

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAE(void)
{
	PrintLineSeparator();

	{
		int														Array[]{100,200,300};

		// !!!!! Vyberu sa VERSION FUNCTIONS pre ARRAYS. FUNCTIONS pre CONTAINERS su IGNORED vdaka SFINAE.
		for(int* Iterator=SFINAETemplateBegin(Array);Iterator!=SFINAETemplateEnd(Array);++Iterator)
		{
			wcout << L"ARRAY - VALUE ["<< (*Iterator) << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		vector<int>												Container{100,200,300};

		// !!!!! Vyberu sa VERSION FUNCTIONS pre CONTAINERS. FUNCTIONS pre ARRAYS su IGNORED vdaka SFINAE.
		for(vector<int>::iterator Iterator=SFINAETemplateBegin(Container);Iterator!=SFINAETemplateEnd(Container);++Iterator)
		{
			wcout << L"CONTAINER - VALUE ["<< (*Iterator) << L"]." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ImmediateContextsTemplate(const TType& Container, typename TType::iterator Begin, typename TType::iterator End)
{
	(void) Container;

	for(typename TType::iterator Iterator=Begin;Iterator!=End;++Iterator)
	{
		wcout << L"IMMEDIATE CONTEXT TEMPLATE 1 - CONTAINER - VALUE ["<< (*Iterator) << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, unsigned SIZE>
void ImmediateContextsTemplate(TType (&Array)[SIZE], const TType* Begin, const TType* End)
{
	(void) Array;

	for(const int* Iterator=Begin;Iterator!=End;++Iterator)
	{
		wcout << L"IMMEDIATE CONTEXT TEMPLATE 1 - ARRAY - VALUE ["<< (*Iterator) << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ImmediateNonContextsTemplate1(typename CNoImmediateContext<TType>::Iterator Begin, typename CNoImmediateContext<TType>::Iterator End)
{
	for(typename CNoImmediateContext<TType>::Iterator Iterator=Begin;Iterator!=End;++Iterator)
	{
		wcout << L"NON IMMEDIATE CONTEXT TEMPLATE 1 - CONTAINER - VALUE ["<< (*Iterator) << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ImmediateNonContextsTemplate1(TType Begin, TType End)
{
	for(TType Iterator=Begin;Iterator!=End;++Iterator)
	{
		wcout << L"NON IMMEDIATE CONTEXT TEMPLATE 1 - ARRAY - VALUE ["<< (*Iterator) << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ImmediateNonContextsTemplate1(...)
{
	wcout << L"NON IMMEDIATE CONTEXT TEMPLATE 1 - ELLIPSIS FUNCTION." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
auto ImmediateNonContextsTemplate2(TType Parameter)
{
	wcout << L"NON IMMEDIATE CONTEXT TEMPLATE 2 - VALUE [" << Parameter << L"]." << endl;

	auto														ReturnValue=Parameter.GetField();

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
int ImmediateNonContextsTemplate2(...)
{
	wcout << L"NON IMMEDIATE CONTEXT TEMPLATE 2 - ELLIPSIS FUNCTION." << endl;

	return(999);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
auto ImmediateNonContextsTemplate2Caller(TType Parameter) -> decltype(ImmediateNonContextsTemplate2(Parameter))
{
	wcout << L"NON IMMEDIATE CONTEXT TEMPLATE 2 - CALLER - VALUE [" << Parameter << L"]." << endl;

	auto														ReturnValue=ImmediateNonContextsTemplate2(Parameter);

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TestImmediateContexts(void)
{
	PrintLineSeparator();

	{
		vector<int>												Container{100,200,300,400,500};
		vector<int>::iterator									Begin=(Container.begin()+1);
		vector<int>::iterator									End=(Container.end()-1);

		// !!! TEMPLATE ARGUMENT DEDUCTION vyberie VERSION FUNCTION [void ImmediateContextsTemplate(const TType& Container, typename TType::iterator Begin, typename TType::iterator End)].
		ImmediateContextsTemplate(Container,Begin,End);
	}

	PrintLineSeparator();

	{
		int														Array[]{100,200,300,400,500};
		const int*												Begin=((&Array[0])+1);
		const int*												End=((&Array[sizeof(Array)/sizeof(Array[0])])-1);

		// !!! TEMPLATE ARGUMENT DEDUCTION vyberie VERSION FUNCTION [void ImmediateContextsTemplate(TType (&Array)[SIZE], const TType* Begin, const TType* End)].
		// !!!!! OVERLOADED FUNCTION [void ImmediateContextsTemplate(const TType& Container, typename TType::iterator Begin, typename TType::iterator End)] sposobi COMPILATION ERROR, ale kedze ju sposobi v IMMEDIATE CONTEXT, tak je IGNOROVANA pomocou SFINAE.
		// !!!!! Dovod preco je CODE [typename TType::iterator] povazovany za IMMEDIATE CONTEXT spociva v tom, ze COMPILATION ERROR vznikne NIE pri INSTANTIATION TYPE [TType] ale kvoli tomu, ze TYPE [TType] NEMA USING [TType::iterator]. Preto je tento CONTEXT povazovany za IMMEDIATE CONTEXT a SFINAE sa APLIKUJE.
		ImmediateContextsTemplate(Array,Begin,End);
	}

	PrintLineSeparator();

	{
		int														Array[]{100,200,300,400,500};
		int*													Begin=(&Array[0]);
		int*													End=(&Array[sizeof(Array)/sizeof(Array[0])]);
		CNoImmediateContext<int>								Object(Begin,End);

		// !!!!! Vola sa OVERLOADED FUNCTION [void ImmediateNonContextsTemplate1(typename CNoImmediateContext<TType>::Iterator Begin, typename CNoImmediateContext<TType>::Iterator End)].
		ImmediateNonContextsTemplate1<int>(Object.GetStartPointer(),Object.GetEndPointer());
	}

	PrintLineSeparator();

	{
		int														Array[]{100,200,300,400,500};
		int*													Begin=(&Array[0]);
		int*													End=(&Array[sizeof(Array)/sizeof(Array[0])]);
		CNoImmediateContext<int>								Object(Begin,End);

		// !!!!! Vola sa OVERLOADED FUNCTION [void ImmediateNonContextsTemplate1(TType Begin, TType End)].
		ImmediateNonContextsTemplate1<int*>(Object.GetStartPointer(),Object.GetEndPointer());
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER pri posudzovani OVERLOADED FUNCTION [void ImmediateNonContextsTemplate1(typename CNoImmediateContext<TType>::Iterator Begin, typename CNoImmediateContext<TType>::Iterator End)] COMPILATION ERROR a to aj napriek tomu, ze OVERLOADED FUNCTION [void ImmediateNonContextsTemplate1(...)] je mozne volat.
		// !!!!! Dovod preco COMPILER hodi COMPILATION ERROR je v tom, ze pri TEMPLATE ARGUMENT DEDUCTION dochadza k pouzitiu NON IMMEDIATE CONTEXT. Tym padom sa NEAPLIKUJE SFINAE a COMPILER vzniknutu ERROR NEIGNORUJE, ale vrati ako COMPILATION ERROR.
		// !!!!! NON IMMEDIATE CONTEXT reprezentuje CODE [typename CNoImmediateContext<TType>::Iterator]. Ten je preto NON IMMEDIATE CONTEXT a NIE IMMEDIATE CONTEXT, pretoze ku COMPILATION ERROR dojde v momente, ked sa COMPILER pokusa vykonat INSTANTIATION TYPE [CNoImmediateContext<TType>]. Pri pokuse o vykonanie INSTANTIATION COMPILER zisti, ze USING CODE [using Iterator=TType*] je ERROR, kedze NIE JE mozne vytvarat POINTERS na REFERENCES. A kedze ERROR vznikol v DEFINITION TEMPLATE CLASS [CNoImmediateContext<TType>], tak sa jedna o NON IMMEDIATE CONTEXT, a NON IMMEDIATE CONTEXT.
		// !!!!! Rozdiel oproti CODE [typename TType::iterator] z FUNCTION [void ImmediateContextsTemplate(const TType& Container, typename TType::iterator Begin, typename TType::iterator End)], ze CODE [typename TType::iterator] NESPOSOBUJE COMPILATION ERROR pri vykonavani INSTANTIATION TYPE [TType], teda nie v DEFINITION TYPE [TType], ale pri formovani TYPE [TType::iterator], kde nenajde USING [TType::iterator]. A tym padom sa jedna o IMMEDIATE CONTEXT, a NIE NONIMMEDIATE CONTEXT.
		ImmediateNonContextsTemplate1<int&>(0,0);
	}
	*/

	PrintLineSeparator();

	{
		CString													Value(L"Timmy");

		// !!!!! Vola sa OVERLOADED FUNCTION [auto ImmediateNonContextsTemplate2(TType Parameter)].
		ImmediateNonContextsTemplate2Caller(Value);
	}

	/*
	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! COMPILER hodi ERROR, pretoze pri posudzovani OVERLOADED FUNCTION [auto ImmediateNonContextsTemplate2(TType Parameter)] dochadza ku COMPILATION ERROR. TYPE [int] NEMA METHOD [TYPE GetField(void)].
		// !!!!! SFINAE sa NEAPLIKUJE, kedze ku COMPILATION ERROR doslo v DEFINITION TEMPLATE FUNCTION co NIE JE IMMEDIATE CONTEXT.
		ImmediateNonContextsTemplate2Caller(Value);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionAllowableConversionsFromDerivedToBase(CDeductionConversionsBase<TType>* Pointer)
{
	wcout << L"FROM DERIVED TO BASE FUNCTION - VALUE [" << Pointer->GetField() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION PARAMETER 'InnerObject' NIE je DEDUCED CONTEXT, a preto TEMPLATE ARGUMENT DEDUCTION zvazuje vsetky IMPLICIT CONVERSIONS.
template<typename TType>
void TemplateArgumentDeductionAllowableConversionsImplicit(TType OuterObject, typename TType::CDeductionConversionsInner InnerObject)
{
	wcout << L"IMPLICIT FUNCTION - OUTER OBJECT [" << OuterObject.GetFieldOuter() << L"] INNER OBJECT [" << InnerObject.GetFieldInner() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Obidve TEMPLATE FUNCTION PARAMETERS su DEDUCED CONTEXT, a preto TEMPLATE ARGUMENT DEDUCTION NEAPLIKUJE ZIADNE IMPLICIT CONVERSIONS.
template<typename TType>
void TemplateArgumentDeductionAllowableConversionsTwoParameters1(TType Parameter1, TType Parameter2)
{
	wcout << L"TWO PARAMETERS FUNCTION 1 - PARAMETER 1 [" << Parameter1 << L"] PARAMETER 2 [" << Parameter2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Obidve TEMPLATE FUNCTION PARAMETERS su DEDUCED CONTEXT, a preto TEMPLATE ARGUMENT DEDUCTION NEAPLIKUJE ZIADNE IMPLICIT CONVERSIONS.
template<typename TType>
void TemplateArgumentDeductionAllowableConversionsTwoParameters2(const TType* Parameter1, const TType* Parameter2)
{
	wcout << L"TWO PARAMETERS FUNCTION 2 - PARAMETER 1 TYPE [" << GetTypeInfoName<decltype(Parameter1)>() << L"] PARAMETER 1 VALUE [" << Parameter1->GetField() << L"] PARAMETER 2 TYPE [" << GetTypeInfoName<decltype(Parameter2)>() << L"] PARAMETER 2 VALUE [" << Parameter2->GetField() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeductionAllowableConversions(void)
{
	PrintLineSeparator();

	{
		CDeductionConversionsDerived<CString>					Object(L"Timmy");

		// !!!!! Aj napriek tomu, ze TEMPLATE PARAMETER je TYPE [CDeductionConversionsBase<TType>*] a TEMPLATE ARGUMENT je TYPE [CDeductionConversionsDerived<CString>*], tak TEMPLATE ARGUMENT DEDUCTION zbehne OK, pretoze CONVERSION POINTERS z DERIVED TYPES na BASE TYPES je povoleny.
		TemplateArgumentDeductionAllowableConversionsFromDerivedToBase(&Object);
	}

	PrintLineSeparator();

	{
		CDeductionConversionsOuter								OuterObject(L"Timmy");

		// !!!!! Pre 2. PARAMETER sa vola EXPLICIT CONVERSION z TYPE [double] na TYPE [CDeductionConversionsInner].
		TemplateArgumentDeductionAllowableConversionsImplicit(OuterObject,12.12);
	}

	PrintLineSeparator();

	{
		TemplateArgumentDeductionAllowableConversionsTwoParameters1(wstring(L"Timmy"),wstring(L"Jenny"));
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze aj ked TYPE [wstring] umoznuje CONVERSION z TYPE [wchar_t], tak TEMPLATE ARGUMENT DEDUCTION ho NEAPLIKUJE.
		// !!!!! Obidve TEMPLATE FUNCTION PARAMETERS su DEDUCED CONTEXT, a preto TEMPLATE ARGUMENT DEDUCTION NEAPLIKUJE ZIADNE IMPLICIT CONVERSIONS.
		TemplateArgumentDeductionAllowableConversionsTwoParameters1(wstring(L"Timmy"),L"Jenny");
	}
	*/

	PrintLineSeparator();

	{
		CDeductionConversionsDerived1<int>						Object1(100);
		CDeductionConversionsDerived1<int>						Object2(200);

		TemplateArgumentDeductionAllowableConversionsTwoParameters2(&Object1,&Object2);
	}

	PrintLineSeparator();

	{
		CDeductionConversionsDerived2<int>						Object1(100);
		CDeductionConversionsDerived2<int>						Object2(200);

		TemplateArgumentDeductionAllowableConversionsTwoParameters2(&Object1,&Object2);
	}

	/*
	PrintLineSeparator();

	{
		CDeductionConversionsDerived1<int>						Object1(100);
		CDeductionConversionsDerived2<int>						Object2(200);

		// !!!!! COMPILER hodi ERROR, pretoze pri TEMPLATE ARGUMENT DEDUCTION nezvazuje ani CONVERSION z POINTER na DERIVED TYPES na POINTER na BASE TYPES.
		TemplateArgumentDeductionAllowableConversionsTwoParameters2(&Object1,&Object2);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassDeduction(void)
{
	PrintLineSeparator();

	{
		// !!!!! Od verzie C++ 17 COMPILER robi TEMPLATE ARGUMENT DEDUCTION pre TEMPLATE CLASSES aj pri volani TEMPLATE CONSTRUCTORS.
		CTemplateClassDeduction									Object(100);

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE [" << Object.GetField() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEFAULT ARGUMENT TEMPLATE FUNCTION predpoklada, ze TYPE PARAMETER [TType] ma DEFAULT CONSTRUCTOR.
template<typename TType>
void TemplateArgumentDeductionDefaultArguments1(const TType& Value=TType())
{
	wcout << L"DEFAULT ARGUMENTS 1 - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionDefaultArguments2(const TType& Value=999)
{
	wcout << L"DEFAULT ARGUMENTS 2 - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeductionDefaultArguments(void)
{
	PrintLineSeparator();

	{
		CDeductionDefaultArguments								Object(100,200);

		// !!!!! Aj napriek tomu, ze TYPE [CDeductionDefaultArguments] NEMA DEFUALT CONSTRUCTOR, ktory vyzaduje DEFAULT ARGUMENT, tak kedze DEFAULT ARGUMENT sa NEPOUZIL, tak COMPILER NEHODI ERROR.
		TemplateArgumentDeductionDefaultArguments1(Object);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze chce aplikovat DEFAULT ARGUMENT, no ten vyzaduje existenciu DEFAULT CONSTRUCTOR, ktory TYPE [CDeductionDefaultArguments] NEMA.
		TemplateArgumentDeductionDefaultArguments1<CDeductionDefaultArguments>();
	}
	*/

	PrintLineSeparator();

	{
		TemplateArgumentDeductionDefaultArguments2<int>();
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMILER hodi ERROR, pretoze C++ NEDOKAZE spravit TEMPLATE ARGUMENT DEDUCTION na zaklade DEFAULT ARGUMENTS.
		TemplateArgumentDeductionDefaultArguments2();
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionExceptionSpecificationTemplate(TType Value1, int Value2) noexcept(TType::IsNoThrowException())
{
	wcout << L"EXCEPTION SPECIFICATION - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateArgumentDeductionExceptionSpecificationTemplate(TType Value, ...)
{
	wcout << L"EXCEPTION SPECIFICATION ELLIPSIS - VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentDeductionExceptionSpecification(void)
{
	PrintLineSeparator();

	{
		CDeductionExceptionSpecification						Object(100);

		// !!! Vola sa OVERLOADED FUNCTION [void TemplateArgumentDeductionExceptionSpecificationTemplate(TType Value1, int Value2) noexcept(TType::IsNoThrowException())].
		// !!! CODE zbehne OK, pretoze TYPE [CDeductionExceptionSpecification] ma STATIC CONSTEXPR METHOD [constexpr static bool IsNoThrowException(void) noexcept].
		TemplateArgumentDeductionExceptionSpecificationTemplate(Object,200);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR. Je to preto, lebo COMPILER vyberie OVERLOADED FUNCTION [void TemplateArgumentDeductionExceptionSpecificationTemplate(TType Value1, int Value2) noexcept(TType::IsNoThrowException())], hoci ta sposobi COMPILATION ERROR v EXCEPTION SPECIFICATION, kedze TYPE [int] NEMA STATIC CONSTEXPR FUNCTION [constexpr static bool IsNoThrowException(void) noexcept]. C++ ju vyberie preto, lebo C++ pri TEMPLATE ARGUMENT DEDUCTION NEVYUZIVA EXCEPTION SPECIFICATIONS, ale pouzije ich az pri pouziti samotnej FUNCTION.
		TemplateArgumentDeductionExceptionSpecificationTemplate(100,200);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType ExplicitTemplateArgumentsTemplate1(void)
{
	TType														ReturnValue={};

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ExplicitTemplateArgumentsTemplate2(TType Parameter)
{
	wcout << L"FUNCTION 2 - TYPE [" << GetTypeInfoName<decltype(Parameter)>() << L"] PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType1 ExplicitTemplateArgumentsTemplate3(TType2 Parameter)
{
	TType1														ReturnValue=static_cast<TType1>(Parameter);

	wcout << L"FUNCTION 3 - TYPE [" << GetTypeInfoName<decltype(Parameter)>() << L"] PARAMETER [" << Parameter << L"]." << endl;

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
void ExplicitTemplateArgumentsTemplate4(int Parameter)
{
	wcout << L"NON-TEMPLATE FUNCTION 4 - PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ExplicitTemplateArgumentsTemplate4(TType Parameter)
{
	wcout << L"TEMPLATE FUNCTION 4 - TYPE [" << GetTypeInfoName<decltype(Parameter)>() << L"] PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
typename TType::NonExistingType ExplicitTemplateArgumentsTemplate5(void)
{
	wcout << L"TEMPLATE FUNCTION 5 - VERSION 1." << endl;

	typename TType::NonExistingType								ReturnValue={};

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType ExplicitTemplateArgumentsTemplate5(void)
{
	wcout << L"TEMPLATE FUNCTION 5 - VERSION 2." << endl;

	TType														ReturnValue={};

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ExplicitTemplateArgumentsTemplate6(TType Parameter)
{
	wcout << L"TEMPLATE FUNCTION 6 - VERSION 1 - PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ExplicitTemplateArgumentsTemplate6(TType Parameter1, TType Parameter2)
{
	wcout << L"TEMPLATE FUNCTION 6 - VERSION 2 - PARAMETER 1 [" << Parameter1 << L"] PARAMETER 2 [" << Parameter2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void ExplicitTemplateArgumentsTemplateVariadicInternal(size_t Index, TType Value, TTypes... Values)
{
	wcout << L"VARIADIC TEMPLATE FUNCTION - INDEX [" << Index << L"] TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Value << L"]." << endl;

	if constexpr (sizeof...(Values)>0)
	{
		ExplicitTemplateArgumentsTemplateVariadicInternal(Index+1,Values...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void ExplicitTemplateArgumentsTemplateVariadic(TTypes... Values)
{
	ExplicitTemplateArgumentsTemplateVariadicInternal(1,Values...);
}
//----------------------------------------------------------------------------------------------------------------------
void TestExplicitTemplateArguments(void)
{
	PrintLineSeparator();

	{
		// !!! TEMPLATE PARAMETER NEMOZE byt DEDUCED a tak musi byt definovany EXPLICITNE.
		double													Value=ExplicitTemplateArgumentsTemplate1<double>();

		wcout << L"FROM FUNCTION 1 - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Ak je TEMPLATE PARAMETER definovany EXPLICITNE, tak sa vykonavaju vsetky CONVERSIONS.
		ExplicitTemplateArgumentsTemplate2<double>(100);
	}

	PrintLineSeparator();

	{
		// !!! C++ umoznuje, aby iba prvych 'N' TEMPLATE PARAMETERS bolo definovanych EXPLICITNE a ostatne su DEDUCED.
		int														Value=ExplicitTemplateArgumentsTemplate3<int>(123.456);

		wcout << L"FROM FUNCTION 3 - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Zavola sa NON-TEMPLATE FUNCTION, pretoze C++ vzdy preferuje NON-TEMPLATE FUNCTIONS pred TEMPLATE FUNCTIONS.
		ExplicitTemplateArgumentsTemplate4(100);

		// !!!!! Zavola sa TEMPLATE FUNCTION, pretoze bola pouzita SYNTAX [<>] pre explicitne zadanie TEMPLATE PARAMETERS, hoci TEMPLATE PARAMETER bol DEDUCED.
		ExplicitTemplateArgumentsTemplate4<>(100);
	}

	PrintLineSeparator();

	{
		// !!!!! C++ aplikuje SFINAE a vyberie OVERLOADED FUNCTION [TType ExplicitTemplateArgumentsTemplate5(void)], lebo TYPE [int] NEMA USING TYPE [TType::NonExistingType].
		auto													PointerToFunction=ExplicitTemplateArgumentsTemplate5<int>;
		int														Value=(*PointerToFunction)();

		wcout << L"FROM FUNCTION 5 - TYPE [" << GetTypeInfoName<decltype(PointerToFunction)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze pri ziskavanie POINTER na FUNCTION je mozne vybrat OVERLOADED FUNCTION [typename void ExplicitTemplateArgumentsTemplate6(TType Parameter)] i OVERLOADED FUNCTION [void ExplicitTemplateArgumentsTemplate6(TType Parameter1, TType Parameter2)].
		auto													PointerToFunction=ExplicitTemplateArgumentsTemplate6<int>;
		int														Value=(*PointerToFunction)(100,200);

		wcout << L"FROM FUNCTION 6 - TYPE [" << GetTypeInfoName<decltype(PointerToFunction)>() << L"] VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! C++ umoznuje definovat explicitne TEMPLATE FUNCTION PARAMETERS aj pre VARIADIC TEMPLATE FUNCTIONS.
		ExplicitTemplateArgumentsTemplateVariadic<double,double,int>(100,200,300);
	}

	PrintLineSeparator();

	{
		// !!!!! C++ umoznuje pre VARIADIC TEMPLATE FUNCTIONS definovat iba cast TEMPLATE FUNCTION PARAMETERS EXPLICITNE.
		ExplicitTemplateArgumentsTemplateVariadic<double>(100.123,200,300);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSpecifierAuto(void)
{
	PrintLineSeparator();

	{
		auto													Value=100;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!! SPECIFIER [auto] moze byt LVALUE REFERENCE.
		auto&													Value=OriginalValue;

		wcout << L"LVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!! SPECIFIER [auto] moze byt RVALUE REFERENCE.
		// !!! Z VARIABLE sa stava FORWARDING REFERENCE.
		// !!!!! DEDUCED TYPE je LVALUE REFERENCE a NIE RVALUE REFERENCE.
		// !!!!! Pre FORWARDING REFERENCE sa aplikuje specialny TEMPLATE ARGUMENT DEDUCTION, kde sa neberie do uvahy iba TYPE INITIALIZER EXPRESSION, ale aj to ci je LVALUE REFERENCE, alebo RVALUE REFERENCE.
		// !!!!! Ak je TYPE INITIALIZER EXPRESSION LVALUE REFERENCE, tak DEDUCED TYPE je LVALUE REFERENCE. Podla COLLAPSING RULES sa RVLAUE REFERENCE na LVALUE REFERENCE sa transformuje na LVALUE REFERENCE.
		// !!!!! Ak je TYPE INITIALIZER EXPRESSION RVALUE REFERENCE, tak DEDUCED TYPE je NON-REFERENCE. Vysledy TYPE je tak RVALUE REFERENCE.
		auto&&													Value=OriginalValue;

		wcout << L"RVALUE REFERENCE FOR LVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! SPECIFIER [auto] moze byt RVALUE REFERENCE.
		// !!! Z VARIABLE sa stava FORWARDING REFERENCE.
		// !!!!! DEDUCED TYPE je RVALUE REFERENCE.
		// !!!!! Pre FORWARDING REFERENCE sa aplikuje specialny TEMPLATE ARGUMENT DEDUCTION, kde sa neberie do uvahy iba TYPE INITIALIZER EXPRESSION, ale aj to ci je LVALUE REFERENCE, alebo RVALUE REFERENCE.
		// !!!!! Ak je TYPE INITIALIZER EXPRESSION LVALUE REFERENCE, tak DEDUCED TYPE je LVALUE REFERENCE. Podla COLLAPSING RULES sa RVLAUE REFERENCE na LVALUE REFERENCE sa transformuje na LVALUE REFERENCE.
		// !!!!! Ak je TYPE INITIALIZER EXPRESSION RVALUE REFERENCE, tak DEDUCED TYPE je NON-REFERENCE. Vysledy TYPE je tak RVALUE REFERENCE.
		auto&&													Value=100;

		wcout << L"RVALUE REFERENCE FOR RVALUE REFERENCE 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!! SPECIFIER [auto] moze byt RVALUE REFERENCE.
		// !!! Z VARIABLE sa stava FORWARDING REFERENCE.
		// !!!!! DEDUCED TYPE je RVALUE REFERENCE.
		// !!!!! Pre FORWARDING REFERENCE sa aplikuje specialny TEMPLATE ARGUMENT DEDUCTION, kde sa neberie do uvahy iba TYPE INITIALIZER EXPRESSION, ale aj to ci je LVALUE REFERENCE, alebo RVALUE REFERENCE.
		// !!!!! Ak je TYPE INITIALIZER EXPRESSION LVALUE REFERENCE, tak DEDUCED TYPE je LVALUE REFERENCE. Podla COLLAPSING RULES sa RVLAUE REFERENCE na LVALUE REFERENCE sa transformuje na LVALUE REFERENCE.
		// !!!!! Ak je TYPE INITIALIZER EXPRESSION RVALUE REFERENCE, tak DEDUCED TYPE je NON-REFERENCE. Vysledy TYPE je tak RVALUE REFERENCE.
		auto&&													Value=move(OriginalValue);

		wcout << L"RVALUE REFERENCE FOR RVALUE REFERENCE 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!! SPECIFIER [auto] moze byt POINTER.
		auto*													Value=&OriginalValue;

		wcout << L"POINTER - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << (*Value) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! SPECIFIER [auto] moze mat SPECIFIER [const].
		const auto												Value=100;

		wcout << L"CONST - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! SPECIFIER [auto] moze byt aj POINTER na MEMBER.
		auto													(CPointerToMember::*PointerToMember)(void) const noexcept=&CPointerToMember::GetValue;

		CPointerToMember										Object(100);

		wcout << L"POINTER TO MEMBER - TYPE [" << GetTypeInfoName<decltype(PointerToMember)>() << L"] VALUE [" << (Object.*PointerToMember)() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ vykona DEDUCTION RETURN VALUE TYPE.
auto SpecifierAutoReturnValueTypeFunction1(void)
{
	return(100);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ vykona DEDUCTION RETURN VALUE TYPE. Pouziva TRAILING RETURN TYPE SYNTAX.
auto SpecifierAutoReturnValueTypeFunction2(void) -> auto
{
	return(100);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION DECLARATION.
auto SpecifierAutoReturnValueTypeFunction3(void) -> auto;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ vykona DEDUCTION RETURN VALUE TYPE. Pouziva TRAILING RETURN TYPE SYNTAX.
auto SpecifierAutoReturnValueTypeFunction3(void) -> auto
{
	return(100);
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze RETURN EXPRESSIONS vracaju iny TYPE.
auto SpecifierAutoReturnValueTypeFunctionError(bool Value) -> auto
{
	if (Value==true)
	{
		return(100);
	}
	else
	{
		return(123.456);
	}
}
*/
//----------------------------------------------------------------------------------------------------------------------
void TestSpecifierAutoReturnValueType(void)
{
	PrintLineSeparator();

	{
		auto													Value=SpecifierAutoReturnValueTypeFunction1();

		wcout << L"FROM FUNCTION 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		auto													Value=SpecifierAutoReturnValueTypeFunction2();

		wcout << L"FROM FUNCTION 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		auto													Value=SpecifierAutoReturnValueTypeFunction3();

		wcout << L"FROM FUNCTION 3 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze RETURN EXPRESSIONS vo FUNCTION vracaju iny TYPE.
		auto													Value=SpecifierAutoReturnValueTypeFunctionError(true);

		wcout << L"FROM FUNCTION ERROR - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! C++ vykona DEDUCTION RETURN VALUE TYPE.
		auto													Lambda=[] (int Parameter) {return(2*Parameter);};

		auto													Value=Lambda(100);

		wcout << L"FROM LAMBDA 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! C++ vykona DEDUCTION RETURN VALUE TYPE. Pouziva TRAILING RETURN TYPE SYNTAX.
		auto													Lambda=[] (int Parameter) -> auto {return(2*Parameter);};

		auto													Value=Lambda(100);

		wcout << L"FROM LAMBDA 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CSpecialTemplateArgumentDeduction						Object(123.456);

		auto													Value=Object.GetValue();

		wcout << L"FROM METHOD - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! C++ vykona DEDUCTION TYPE TEMPLATE NON-TYPE PARAMETER.
template<auto VALUE>
void SpecifierAutoNonTypeTemplateParameterTemplate(void)
{
	// !!! KEYWORD [decltype(EXPRESSION)] je mozne pouzit na ziskanie TYPE DEDUCED TEMPLATE NON-TYPE PARAMETER.
	constexpr decltype(VALUE)									SQUARE=(VALUE*VALUE);

	wcout << L"TEMPLATE FUNCTION - TYPE [" << GetTypeInfoName<decltype(VALUE)>() << L"] VALUE [" << VALUE << L"] SQUARE [" << SQUARE << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! C++ vykona DEDUCTION TYPE TEMPLATE NON-TYPE PARAMETERS, kde KAZDY TEMPLATE NON-TYPE PARAMETERS moze ma INY TYPE.
template<auto VALUE, auto... VALUES>
void SpecifierAutoNonTypeTemplateParameterTemplateVariadicInternal(size_t Index)
{
	wcout << L"TEMPLATE FUNCTION VARIADIC - INDEX [" << Index << L"] TYPE [" << GetTypeInfoName<decltype(VALUE)>() << L"] VALUE [" << VALUE << L"]." << endl;

	if constexpr (sizeof...(VALUES)>0)
	{
		SpecifierAutoNonTypeTemplateParameterTemplateVariadicInternal<VALUES...>(Index+1);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! C++ vykona DEDUCTION TYPE TEMPLATE NON-TYPE PARAMETERS, kde KAZDY TEMPLATE NON-TYPE PARAMETERS moze ma INY TYPE.
template<auto... VALUES>
void SpecifierAutoNonTypeTemplateParameterTemplateVariadic(void)
{
	SpecifierAutoNonTypeTemplateParameterTemplateVariadicInternal<VALUES...>(1);
}
//----------------------------------------------------------------------------------------------------------------------
void TestSpecifierAutoNonTypeTemplateParameter(void)
{
	PrintLineSeparator();

	{
		SpecifierAutoNonTypeTemplateParameterTemplate<100>();
	}

	PrintLineSeparator();

	{
		SpecifierAutoNonTypeTemplateParameterTemplate<100ul>();
	}

	PrintLineSeparator();

	{
		SpecifierAutoNonTypeTemplateParameterTemplateVariadic<true,100u,L'X'>();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
double TestDecltypeKeywordEntityFunction1A(void)
{
	return(123.456);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! C++ urci TYPE z EXPRESSION volania FUNCTION.
decltype(TestDecltypeKeywordEntityFunction1A()) TestDecltypeKeywordEntityFunction2A(void)
{
	decltype(TestDecltypeKeywordEntityFunction1A())				Variable=TestDecltypeKeywordEntityFunction1A();

	Variable+=100;

	return(Variable);
}
//----------------------------------------------------------------------------------------------------------------------
double& TestDecltypeKeywordEntityFunction1B(void)
{
	static double												StaticVariable=123.456;

	return(StaticVariable);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! C++ urci TYPE z EXPRESSION volania FUNCTION.
decltype(TestDecltypeKeywordEntityFunction1B()) TestDecltypeKeywordEntityFunction2B(void)
{
	decltype(TestDecltypeKeywordEntityFunction1B())				Variable=TestDecltypeKeywordEntityFunction1B();

	Variable+=100;

	return(Variable);
}
//----------------------------------------------------------------------------------------------------------------------
double&& TestDecltypeKeywordEntityFunction1C(void)
{
	static double												StaticVariable=123.456;

	return(move(StaticVariable));
}
//----------------------------------------------------------------------------------------------------------------------
// !!! C++ urci TYPE z EXPRESSION volania FUNCTION.
decltype(TestDecltypeKeywordEntityFunction1C()) TestDecltypeKeywordEntityFunction2C(void)
{
	decltype(TestDecltypeKeywordEntityFunction1C())				Variable=TestDecltypeKeywordEntityFunction1C();

	Variable+=100;

	return(move(Variable));
}
//----------------------------------------------------------------------------------------------------------------------
void TestDecltypeKeywordEntity(void)
{
	PrintLineSeparator();

	{
		int														Variable=100;

		// !!!!! C++ identifikuje TYPE [int], pretoze VARIABLE [Variable] je TYPE [int].
		decltype(Variable)										DeclVariable=Variable;

		wcout << L"NON-REFERENCE - TYPE [" << GetTypeInfoName<decltype(DeclVariable)>() << L"] VALUE [" << DeclVariable << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Temporary=100;
		int&													Variable=Temporary;

		// !!!!! C++ identifikuje TYPE [int&], pretoze VARIABLE [Variable] je TYPE [int&].
		decltype(Variable)										DeclVariable=Variable;

		wcout << L"LVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(DeclVariable)>() << L"] VALUE [" << DeclVariable << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int&&													Variable=100;

		// !!!!! C++ identifikuje TYPE [int&&], pretoze VARIABLE [Variable] je TYPE [int&&].
		// !!!!! MUSI sa pouzit FUNCTION [move()], pretoze bez nej C++ RVALUE REFERENCE AUTOMATICKY z BEZPECNOSTNYCH DOVODOV konvertuje na LVALUE REFERENCE. Pouzitie FUNCTION [move()] sposobi konverziu na RVALUE REFERENCE.
		decltype(Variable)										DeclVariable=move(Variable);

		wcout << L"RVALUE REFERENCE - TYPE [" << GetTypeInfoName<decltype(DeclVariable)>() << L"] VALUE [" << DeclVariable << L"]." << endl;
	}

	PrintLineSeparator();

	{
		decltype(TestDecltypeKeywordEntityFunction2A())			Variable=TestDecltypeKeywordEntityFunction2A();

		wcout << L"FUNCTION CALL 1 - TYPE [" << GetTypeInfoName<decltype(Variable)>() << L"] VALUE [" << Variable << L"]." << endl;
	}

	PrintLineSeparator();

	{
		decltype(TestDecltypeKeywordEntityFunction2B())			Variable=TestDecltypeKeywordEntityFunction2B();

		wcout << L"FUNCTION CALL 2 - TYPE [" << GetTypeInfoName<decltype(Variable)>() << L"] VALUE [" << Variable << L"]." << endl;
	}

	PrintLineSeparator();

	{
		decltype(TestDecltypeKeywordEntityFunction2C())			Variable=TestDecltypeKeywordEntityFunction2C();

		wcout << L"FUNCTION CALL 3 - TYPE [" << GetTypeInfoName<decltype(Variable)>() << L"] VALUE [" << Variable << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDecltypeKeywordValueCategory(void)
{
	PrintLineSeparator();

	{
		int														Variable=100;

		// !!!!! C++ identifikuje TYPE [int&], pretoze VALUE CATEGORY pre LVALUE REFERENCE je LVALUE REFERENCE.
		decltype((Variable))									DeclVariable=Variable;

		wcout << L"CATEGORY 1 - TYPE [" << GetTypeInfoName<decltype(DeclVariable)>() << L"] VALUE [" << DeclVariable << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int&&													Variable=100;

		// !!!!! C++ identifikuje TYPE [int&&], pretoze VALUE CATEGORY pre XVALUE REFERENCE je RVALUE REFERENCE.
		decltype((move(Variable)))								DeclVariable=move(Variable);

		wcout << L"CATEGORY 2 - TYPE [" << GetTypeInfoName<decltype(DeclVariable)>() << L"] VALUE [" << DeclVariable << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! C++ identifikuje TYPE [int], pretoze VALUE CATEGORY pre PRVALUE REFERENCE je NON-REFERENCE.
		decltype((100))											DeclVariable=100;

		wcout << L"CATEGORY 3 - TYPE [" << GetTypeInfoName<decltype(DeclVariable)>() << L"] VALUE [" << DeclVariable << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) TestDecltypeAutoKeywordNonReferenceType(void)
{
	static int													Value=100;

	// !!! Vracia TYPE VARIABLE [Value], ktory je TYPE [int].
	return Value;
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) TestDecltypeAutoKeywordNonReferenceValueCategory(void)
{
	static int													Value=100;

	// !!!!! Pouziju sa ZATVORKY okolo KEYWORD [return], aby sa vratila VALUE CATEGORY.
	// !!!!! Kedze VALUE EXPRESSION [Reference] je LVALUE, vrateny TYPE je LVALUE TYPE [int&].
	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) TestDecltypeAutoKeywordLValueReferenceType(void)
{
	static int													Value=100;

	int&														Reference=Value;

	// !!!!! NESMU sa pouzit ZATVORKY okolo KEYWORD [return], inak KEYWORD [decltype(auto)] vrati nie DEDUCED TYPE, ale DEDUCED VALUE CATEGORY.
	// !!! Vracia TYPE VARIABLE [Value], ktory je TYPE [int&].
	return Reference;
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) TestDecltypeAutoKeywordLValueReferenceValueCategory(void)
{
	static int													Value=100;

	int&														Reference=Value;

	// !!!!! Pouziju sa ZATVORKY okolo KEYWORD [return], aby sa vratila VALUE CATEGORY.
	// !!!!! Kedze VALUE EXPRESSION [Reference] je LVALUE, vrateny TYPE je LVALUE REFERENCE TYPE [int&].
	return(Reference);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) TestDecltypeAutoKeywordRValueReferenceType(void)
{
	static int													Value=100;

	int&&														Reference=move(Value);

	// !!!!! NESMU sa pouzit ZATVORKY okolo KEYWORD [return].
	// !!! Vracia TYPE VARIABLE [Value], ktory je TYPE [int&&].
	return move(Reference);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) TestDecltypeAutoKeywordRValueReferenceValueCategory(void)
{
	static int													Value=100;

	int&&														Reference=move(Value);

	// !!!!! Pouziju sa ZATVORKY okolo KEYWORD [return], aby sa vratila VALUE CATEGORY.
	// !!!!! Kedze VALUE EXPRESSION [Reference] je XVALUE (pouzila sa FUNCTION [move()]), vrateny TYPE je RVALUE REFERENCE TYPE [int&&].
	return(move(Reference));
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) TestDecltypeAutoKeywordPRValueType(void)
{
	// !!!!! NESMU sa pouzit ZATVORKY okolo KEYWORD [return].
	// !!! Vracia TYPE VARIABLE [Value], ktory je TYPE [int].
	return 100;
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) TestDecltypeAutoKeywordPRValueValueCategory(void)
{
	// !!!!! Pouziju sa ZATVORKY okolo KEYWORD [return], aby sa vratila VALUE CATEGORY.
	// !!!!! Kedze VALUE EXPRESSION [Reference] je PRVALUE (LITERAL), vrateny TYPE je NON-REFERENCE TYPE [int].
	return(100);
}
//----------------------------------------------------------------------------------------------------------------------
template<auto VALUE>
auto DecltypeAutoKeywordNonTypeTemplateParameterDeductionContext(CDecltypeAutoNonTypeTemplateParameter<VALUE> Parameter)
{
	return(Parameter.Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<auto VALUE>
auto DecltypeAutoKeywordNonTypeTemplateParameterNonDeductionContext(decltype(VALUE) Parameter)
{
	return(Parameter);
}
//----------------------------------------------------------------------------------------------------------------------
void TestDecltypeAutoKeyword(void)
{
	PrintLineSeparator();

	{
		int														Value=100;
		int&													LValueReferenceToValue=Value;

		// !!!!! DEDUCED TYPE je TYPE [int], pretoze KEYWORD [auto] NIKDY nededukuje REFERENCE TYPES.
		auto													AutoLValueReferenceToValue=LValueReferenceToValue;

		// !!!!! DEDUCED TYPE je TYPE [int&], pretoze EXPRESSION [LValueReferenceToValue] je LVALUE a pre LVALUES KEYWORD [decltype()] vracia LVALUE REFERENCE TYPES.
		decltype(auto)											DecltypeAutoLValueReferenceToValue=LValueReferenceToValue;

		wcout << L"LVALUE REFERENCE - AUTO TYPE [" << GetTypeInfoName<decltype(AutoLValueReferenceToValue)>() << L"] VALUE [" << AutoLValueReferenceToValue << L"]." << endl;
		wcout << L"LVALUE REFERENCE - DECLTYPE AUTO TYPE [" << GetTypeInfoName<decltype(DecltypeAutoLValueReferenceToValue)>() << L"] VALUE [" << DecltypeAutoLValueReferenceToValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Value=100;
		const int&												ConstLValueReferenceToValue=Value;

		// !!!!! DEDUCED TYPE je TYPE [int], pretoze KEYWORD [auto] NIKDY nededukuje REFERENCE TYPES.
		auto													AutoConstLValueReferenceToValue=ConstLValueReferenceToValue;

		// !!!!! DEDUCED TYPE je TYPE [const int&], pretoze EXPRESSION [ConstLValueReferenceToValue] je CONST LVALUE a pre CONST LVALUES KEYWORD [decltype()] vracia CONST LVALUE REFERENCE TYPES.
		decltype(auto)											DecltypeAutoConstLValueReferenceToValue=ConstLValueReferenceToValue;

		wcout << L"CONST LVALUE REFERENCE - AUTO TYPE [" << GetTypeInfoName<decltype(AutoConstLValueReferenceToValue)>() << L"] VALUE [" << AutoConstLValueReferenceToValue << L"]." << endl;
		wcout << L"CONST LVALUE REFERENCE - DECLTYPE AUTO TYPE [" << GetTypeInfoName<decltype(DecltypeAutoConstLValueReferenceToValue)>() << L"] VALUE [" << DecltypeAutoConstLValueReferenceToValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Value=100;
		int&&													RValueReferenceToValue=move(Value);

		// !!!!! DEDUCED TYPE je TYPE [int], pretoze KEYWORD [auto] NIKDY nededukuje REFERENCE TYPES.
		auto													AutoRValueReferenceToValue=move(RValueReferenceToValue);

		// !!!!! DEDUCED TYPE je TYPE [int&&], pretoze EXPRESSION [move(RValueReferenceToValue)] je XVALUE a pre XVALUES KEYWORD [decltype()] vracia RVALUE REFERENCE TYPES.
		decltype(auto)											DecltypeAutoRValueReferenceToValue=move(RValueReferenceToValue);

		wcout << L"RVALUE REFERENCE - AUTO TYPE [" << GetTypeInfoName<decltype(AutoRValueReferenceToValue)>() << L"] VALUE [" << AutoRValueReferenceToValue << L"]." << endl;
		wcout << L"RVALUE REFERENCE - DECLTYPE AUTO TYPE [" << GetTypeInfoName<decltype(DecltypeAutoRValueReferenceToValue)>() << L"] VALUE [" << DecltypeAutoRValueReferenceToValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCED TYPE je TYPE [int], pretoze KEYWORD [auto] NIKDY nededukuje REFERENCE TYPES.
		auto													AutoRValueReferenceToValue=100;

		// !!!!! DEDUCED TYPE je TYPE [int], a NIE TYPE [int&&], pretoze EXPRESSION [100] je PRVALUE a pre PRVALUES KEYWORD [decltype()] vracia NON-REFERENCE TYPES.
		decltype(auto)											DecltypeAutoRValueReferenceToValue=100;

		wcout << L"PRVALUE - AUTO TYPE [" << GetTypeInfoName<decltype(AutoRValueReferenceToValue)>() << L"] VALUE [" << AutoRValueReferenceToValue << L"]." << endl;
		wcout << L"PRVALUE - DECLTYPE AUTO TYPE [" << GetTypeInfoName<decltype(DecltypeAutoRValueReferenceToValue)>() << L"] VALUE [" << DecltypeAutoRValueReferenceToValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		decltype(auto)											ReturnValueType=TestDecltypeAutoKeywordNonReferenceType();
		decltype(auto)											ReturnValueValueCategory=TestDecltypeAutoKeywordNonReferenceValueCategory();

		wcout << L"FUNCTION NON REFERENCE TYPE - [" << GetTypeInfoName<decltype(ReturnValueType)>() << L"] VALUE [" << ReturnValueType << L"]." << endl;
		wcout << L"FUNCTION NON REFERENCE VALUE CATEGORY - [" << GetTypeInfoName<decltype(ReturnValueValueCategory)>() << L"] VALUE [" << ReturnValueValueCategory << L"]." << endl;
	}

	PrintLineSeparator();

	{
		decltype(auto)											ReturnValueType=TestDecltypeAutoKeywordLValueReferenceType();
		decltype(auto)											ReturnValueValueCategory=TestDecltypeAutoKeywordLValueReferenceValueCategory();

		wcout << L"FUNCTION LVALUE REFERENCE TYPE - [" << GetTypeInfoName<decltype(ReturnValueType)>() << L"] VALUE [" << ReturnValueType << L"]." << endl;
		wcout << L"FUNCTION LVALUE REFERENCE VALUE CATEGORY - [" << GetTypeInfoName<decltype(ReturnValueValueCategory)>() << L"] VALUE [" << ReturnValueValueCategory << L"]." << endl;
	}

	PrintLineSeparator();

	{
		decltype(auto)											ReturnValueType=TestDecltypeAutoKeywordRValueReferenceType();
		decltype(auto)											ReturnValueValueCategory=TestDecltypeAutoKeywordRValueReferenceValueCategory();

		wcout << L"FUNCTION RVALUE REFERENCE TYPE - [" << GetTypeInfoName<decltype(ReturnValueType)>() << L"] VALUE [" << ReturnValueType << L"]." << endl;
		wcout << L"FUNCTION RVALUE REFERENCE VALUE CATEGORY - [" << GetTypeInfoName<decltype(ReturnValueValueCategory)>() << L"] VALUE [" << ReturnValueValueCategory << L"]." << endl;
	}

	PrintLineSeparator();

	{
		decltype(auto)											ReturnValueType=TestDecltypeAutoKeywordPRValueType();
		decltype(auto)											ReturnValueValueCategory=TestDecltypeAutoKeywordPRValueValueCategory();

		wcout << L"FUNCTION PRVALUE TYPE - [" << GetTypeInfoName<decltype(ReturnValueType)>() << L"] VALUE [" << ReturnValueType << L"]." << endl;
		wcout << L"FUNCTION PRVALUE VALUE CATEGORY - [" << GetTypeInfoName<decltype(ReturnValueValueCategory)>() << L"] VALUE [" << ReturnValueValueCategory << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Variable=100;

		// !!!!! DEDUCED TYPE je TYPE [int], pretoze ENTITY [Variable] ma TYPE [int].
		decltype(auto)											VariableType=Variable;

		// !!!!! DEDUCED TYPE je TYPE [int&], pretoze EXPRESSION [Variable] ma VALUE CATEGORY LVALUE a KEYWORD [decltype(auto)] pre VALUE CATEGORY LVALUE generuje LVALUE REFERENCE TYPE [int&].
		decltype(auto)											VariableValueCategory=(Variable);

		wcout << L"TYPE - [" << GetTypeInfoName<decltype(VariableType)>() << L"] VALUE [" << VariableType << L"]." << endl;
		wcout << L"VALUE CATEGORY - [" << GetTypeInfoName<decltype(VariableValueCategory)>() << L"] VALUE [" << VariableValueCategory << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr int											Value=100;

		// !!!!! DEDUCED TYPE NON-TYPE TEMPLATE PARAMETER je rovnaky ako TYPE VARIABLE [Value] TYPE [const int].
		CDecltypeAutoNonTypeTemplateParameter<Value>			Object;

		wcout << L"NON-TYPE PARAMETER - DECLTYPE TYPE - TYPE - [" << GetTypeInfoName<decltype(Object.Value)>() << L"] VALUE [" << Object.Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		static int												Value=100;

		// !!!!! DEDUCED TYPE NON-TYPE TEMPLATE PARAMETER je rovnaky ako VALUE CATEGORY VARIABLE [Value] TYPE [int&].
		CDecltypeAutoNonTypeTemplateParameter<(Value)>			Object;

		wcout << L"NON-TYPE PARAMETER - DECLTYPE VALUE CATEGORY - TYPE - [" << GetTypeInfoName<decltype(Object.Value)>() << L"] VALUE [" << Object.Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr int											ConstValue=100;

		// !!!!! DEDUCED TYPE NON-TYPE TEMPLATE PARAMETER je rovnaky ako TYPE VARIABLE [Value] TYPE [const int].
		CDecltypeAutoNonTypeTemplateParameter<ConstValue>		Object;

		// !!! C++ dokaze vykonat DEDUCTION NON-TYPE TEMPLATE PARAMETER, pretoze ten sa nachadza v DEDUCTION CONTEXT.
		decltype(auto)											Value=DecltypeAutoKeywordNonTypeTemplateParameterDeductionContext(Object);

		wcout << L"NON-TYPE PARAMETER - DEDUCTION CONTEXT - TYPE - [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! C++ NEDOKAZE vykonat DEDUCTION NON-TYPE TEMPLATE PARAMETER, pretoze ten sa nachadza v NON-DEDUCTION CONTEXT. Preto je ho NUTNE EXPLICITNE DEFINOVAT.
		decltype(auto)											Value=DecltypeAutoKeywordNonTypeTemplateParameterNonDeductionContext<100>(200);

		wcout << L"NON-TYPE PARAMETER - NON-DEDUCTION CONTEXT - TYPE - [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR. C++ NEDOKAZE vykonat DEDUCTION NON-TYPE TEMPLATE PARAMETER, pretoze ten sa nachadza v NON-DEDUCTION CONTEXT. Preto ak NIE je zadany, COMPILER hodi ERROR.
		decltype(auto)											Value=DecltypeAutoKeywordNonTypeTemplateParameterNonDeductionContext(200);

		wcout << L"NON-TYPE PARAMETER - NON-DEDUCTION CONTEXT ERROR - TYPE - [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void SpecialDeductionRulesTemplateRawParameter(TType Parameter)
{
	wcout << L"RAW - TYPE - [" << GetTypeInfoName<decltype(Parameter)>() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void SpecialDeductionRulesTemplateInitializerListParameter(initializer_list<TType> Parameter)
{
	wcout << L"INITIALIZER LIST - TYPE - [" << GetTypeInfoName<decltype(Parameter)>() << L"] PARAMETER [";

	bool														IsFirst=true;

	for(TType Value : Parameter)
	{
		if (IsFirst==false)
		{
			wcout << L",";
		}
		else
		{
			IsFirst=false;
		}

		wcout << Value;
	}

	wcout << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze INITIALIZER LIST NIE JE mozne vratit ako RETURN VALUE TYPE. Interne totizto pouziva LOCAL ARRAY, ktore je po skonceni volania FUNCTION odstraneny z MEMORY.
auto SpecialDeductionRulesReturnInitializer1(void)
{
	return {100,200,300};
}
*/
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER sice NEHODI ERROR, ale dojde k RUNTIME ERROR, pretoze INITIALIZER LIST NIE JE mozne vratit ako RETURN VALUE TYPE. Interne totizto pouziva LOCAL ARRAY, ktore je po skonceni volania FUNCTION odstraneny z MEMORY.
auto SpecialDeductionRulesReturnInitializer2(void)
{
	initializer_list<int>										Value={100,200,300};

	return(Value);
}
*/
//----------------------------------------------------------------------------------------------------------------------
// !!! CODE je korektny, pretoze vsetky KEYWORDS [return] vracaju ten isty TYPE.
auto SpecialDeductionRulesReturnValueTypeAuto(bool Value)
{
	if (Value==true)
	{
		return(100);
	}
	else
	{
		return(200);
	}
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze KEYWORDS [return] NEVRACAJU ten ISTY TYPE.
auto SpecialDeductionRulesReturnValueTypeAutoError(bool Value)
{
	if (Value==true)
	{
		return(100);
	}
	else
	{
		return(200.222);
	}
}
*/
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER dokaze vykonat DEDUCTION RETURN VALUE TYPE, pretoze KEYWORD [return] pre FINAL CASE, ktory vracia konkretny TYPE je pred KEYWORD [return] pouzity na RECURSION.
auto SpecialDeductionRulesReturnValueTypeAutoRecursion(int Value)
{
	if (Value==1)
	{
		return(1);
	}
	else
	{
		return(Value*SpecialDeductionRulesReturnValueTypeAutoRecursion(Value-1));
	}
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze KEYWORD [return] pouzity na RECURSION sa pouzije PRED KEYWORD [return] pre FINAL CASE, ktory vracia konkretny TYPE.
auto SpecialDeductionRulesReturnValueTypeAutoRecursionError(int Value)
{
	if (Value>1)
	{
		return(Value*SpecialDeductionRulesReturnValueTypeAutoRecursionError(Value-1));
	}
	else
	{
		return(1);
	}
}
*/
//----------------------------------------------------------------------------------------------------------------------
// !!! DEDUCED RETURN VALUE TYPE je TYPE [void].
auto SpecialDeductionRulesReturnValueTypeVoid1(void)
{
	wcout << L"FUNCTION RETURN VALUE TYPE VOID 1 CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! DEDUCED RETURN VALUE TYPE je TYPE [void].
auto SpecialDeductionRulesReturnValueTypeVoid2(void)
{
	wcout << L"FUNCTION RETURN VALUE TYPE VOID 2 CALLED." << endl;

	return;
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze DEDUCED RETURN VALUE TYPE je TYPE [void*] a ziadna RETURN VALUE nebola vratena.
auto* SpecialDeductionRulesReturnValueTypeVoid3(void)
{
	wcout << L"FUNCTION RETURN VALUE TYPE VOID 3 CALLED." << endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
auto SpecialDeductionRulesSFINAE(TType1 Value1, TType2 Value2) -> decltype(Value1+Value2)
{
	wcout << L"SFINAE - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	return(Value1+Value2);
}
//----------------------------------------------------------------------------------------------------------------------
auto SpecialDeductionRulesSFINAE(...)
{
	wcout << L"SFINAE - ELLIPSIS PARAMETER." << endl;

	return(100);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
auto SpecialDeductionRulesSFINAEError(TType1 Value1, TType2 Value2) -> decltype(auto)
{
	wcout << L"SFINAE ERROR - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	// !!! NESMU sa pouzit ZATVORKY [()].
	return Value1+Value2;
}
//----------------------------------------------------------------------------------------------------------------------
auto SpecialDeductionRulesSFINAEError(...)
{
	wcout << L"SFINAE ERROR - ELLIPSIS PARAMETER." << endl;

	return(100);
}
//----------------------------------------------------------------------------------------------------------------------
void TestSpecialDeductionRules(void)
{
	PrintLineSeparator();

	{
		auto													Argument={100,200,300};

		wcout << L"TEMPLATE ARGUMENT - TYPE - [" << GetTypeInfoName<decltype(Argument)>() << L"]." << endl;

		SpecialDeductionRulesTemplateRawParameter(Argument);
	}

	PrintLineSeparator();

	{
		auto													Argument={100,200,300};

		wcout << L"TEMPLATE ARGUMENT - TYPE - [" << GetTypeInfoName<decltype(Argument)>() << L"]." << endl;

		SpecialDeductionRulesTemplateInitializerListParameter(Argument);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze NEDOKAZE vykonat TEMPLATE ARGUMENT DEDUCTION pre INITIALIZER LISTS.
		SpecialDeductionRulesTemplateRawParameter({100,200,300});
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION je uspesne vykonana.
		SpecialDeductionRulesTemplateInitializerListParameter({100,200,300});
	}

	PrintLineSeparator();

	{
		// !!! C++ akcpetuje tuto SYNTAX.
		initializer_list<int>									Value{100,200,300};
		
		wcout << L"INITIALIZER LIST - FULL TYPE NO EQUAL SING - TYPE - [" << GetTypeInfoName<decltype(Value)>() << L"] SIZE [" << Value.size() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! C++ akcpetuje tuto SYNTAX.
		initializer_list<int>									Value={100,200,300};
		
		wcout << L"INITIALIZER LIST - FULL TYPE EQUAL SING - TYPE - [" << GetTypeInfoName<decltype(Value)>() << L"] SIZE [" << Value.size() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR.
		auto													Value{100,200,300};
		
		wcout << L"INITIALIZER LIST - AUTO NO EQUAL SING - TYPE - [" << GetTypeInfoName<decltype(Value)>() << L"] SIZE [" << Value.size() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!! C++ akcpetuje tuto SYNTAX.
		auto													Value={100,200,300};
		
		wcout << L"INITIALIZER LIST - AUTO EQUAL SING - TYPE - [" << GetTypeInfoName<decltype(Value)>() << L"] SIZE [" << Value.size() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		auto													Value=SpecialDeductionRulesReturnInitializer1();
		
		wcout << L"INITIALIZER LIST - FROM FUNCTION 1 - TYPE - [" << GetTypeInfoName<decltype(Value)>() << L"] SIZE [" << Value.size() << L"]." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	{
		auto													Value=SpecialDeductionRulesReturnInitializer2();
		
		wcout << L"INITIALIZER LIST - FROM FUNCTION 2 - TYPE - [" << GetTypeInfoName<decltype(Value)>() << L"] SIZE [" << Value.size() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		int														OriginalVariable=100;

		// !!!!! DEDUCTION uspeje, ak su TYPES vsetkych VARIABLES ROVNAKE, pricom sa MOZU lisit v MODIFIERS, ako napriklad MODIFIER [&].
		auto													Variable1=OriginalVariable, &Variable2=OriginalVariable;
		
		wcout << L"MULTI VARIABLES - VARIABLE 1 - TYPE - [" << GetTypeInfoName<decltype(Variable1)>() << L"] VALUE [" << Variable1 << L"] - VARIABLE 2 - TYPE - [" << GetTypeInfoName<decltype(Variable2)>() << L"] VALUE [" << Variable2 << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		int														OriginalVariable1=100;
		double													OriginalVariable2=123.456;

		// !!!!! COMPILER hodi ERROR, pretoze TYPES NIE su ROVNAKE.
		auto													Variable1=OriginalVariable1, Variable2=OriginalVariable2;
		
		wcout << L"MULTI VARIABLES - VARIABLE 1 - TYPE - [" << GetTypeInfoName<decltype(Variable1)>() << L"] VALUE [" << Variable1 << L"] - VARIABLE 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		auto													ReturnValue=SpecialDeductionRulesReturnValueTypeAuto(true);

		wcout << L"RETURN VALUE - TYPE - [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		auto													ReturnValue=SpecialDeductionRulesReturnValueTypeAutoError(true);

		wcout << L"RETURN VALUE - TYPE - [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		auto													ReturnValue=SpecialDeductionRulesReturnValueTypeAutoRecursion(4);

		wcout << L"RECURSION - TYPE - [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		auto													ReturnValue=SpecialDeductionRulesReturnValueTypeAutoRecursionError(4);

		wcout << L"RECURSION - TYPE - [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		SpecialDeductionRulesReturnValueTypeVoid1();
	}

	PrintLineSeparator();

	{
		SpecialDeductionRulesReturnValueTypeVoid2();
	}

	/*
	PrintLineSeparator();

	{
		SpecialDeductionRulesReturnValueTypeVoid3();
	}
	*/

	PrintLineSeparator();

	{
		CString													Value1(L"Timmy");
		CString													Value2(L"Jenny");

		// !!!!! C++ vola OVERLOADED FUNCTION [auto SpecialDeductionRulesSFINAE(...)], pretoze TYPE [CString] NEMA OPERATOR [OPERATOR+] FUNCTION [auto SpecialDeductionRulesSFINAE(TType1 Value1, TType2 Value2) -> decltype(Value1+Value2)] kvoli SFINAE NIE JE mozne VOLAT.
		auto													ReturnValue=SpecialDeductionRulesSFINAE(Value1,Value2);

		wcout << L"FROM SFINAE FUNCTION - TYPE - [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CString													Value1(L"Timmy");
		CString													Value2(L"Jenny");

		// !!!!! COMPILER hodi ERROR, pretoze pri OVERLOAD TEMPLATE FUNCTION [auto SpecialDeductionRulesSFINAEError(TType1 Value1, TType2 Value2) -> decltype(auto)] pouziva ako RETURN VALUE TYPE KEYWORD [auto]. V takom pripade na zistenie skutocneho RETURN VALUE TYPE musi byt TEMPLATE FUNCTION INSTANTIATED. Avsak INSTANTIATION dojde ku COMPILATION ERROR v TEMPLATE FUNCTION BODY, kedze TYPE [CString] NEMA OPERATOR [OPERATOR+]. No a kedze FUNCTION BODY NIE JE DEDUCTION CONTEXT, tak na ERROR sa NEAPLIKUJE SFINAE, ale tento ERROR je COMPILATION ERROR.
		auto													ReturnValue=SpecialDeductionRulesSFINAEError(Value1,Value2);

		wcout << L"FROM SFINAE FUNCTION - TYPE - [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestStructuredBindingsClasses(void)
{
	PrintLineSeparator();

	{
		CStructuredBindingClassBase1							Object(L"PUBLIC",100);

		auto													[Alias1,Alias2]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CStructuredBindingClassBase1							Object(L"PUBLIC",100);

		const auto&												[Alias1,Alias2]=Object;
		
		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CStructuredBindingClassBase1							Object(L"PUBLIC",100);

		// !!!!! ALIASES su REFERENCES na CLASS FIELDS.
		auto&													[Alias1,Alias2]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;

		Alias2+=50;

		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;

		wcout << L"PUBLIC FIELD BASE 1 - VALUE [" << Object.GetPublicFieldBase1() << L"]." << endl;
		wcout << L"PUBLIC FIELD BASE 2 - VALUE [" << Object.GetPublicFieldBase2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CStructuredBindingClassBase2							Object(123.456,L"PUBLIC");

		// !!!!! ALIASES su REFERENCES na CLASS FIELDS.
		auto&													[Alias1,Alias2]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;

		Alias1+=50.5;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;

		wcout << L"PUBLIC FIELD BASE 1 - VALUE [" << Object.GetPublicFieldBase1() << L"]." << endl;
		wcout << L"PUBLIC FIELD BASE 2 - VALUE [" << Object.GetPublicFieldBase2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CStructuredBindingClassDerived1							Object(L"BASE",100);

		// !!!!! ALIASES su REFERENCES na CLASS FIELDS, ktore su DERIVED z BASE CLASS.
		auto&													[Alias1,Alias2]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;

		Alias2+=50;

		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;

		wcout << L"PUBLIC FIELD BASE 1 - VALUE [" << Object.GetPublicFieldBase1() << L"]." << endl;
		wcout << L"PUBLIC FIELD BASE 2 - VALUE [" << Object.GetPublicFieldBase2() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CStructuredBindingClassDerived2							Object(L"DERIVED",100,L"BASE",200);

		// !!!!! COMPILER hodi ERROR, pretoze CLASS [CStructuredBindingClassDerived2] ma sama FIELDS a ma FIELDS aj v BASE CLASS.
		auto&													[Alias1,Alias2,Alias3,Alias4]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;
		wcout << L"ALIAS 4 - TYPE - [" << GetTypeInfoName<decltype(Alias4)>() << L"] VALUE [" << Alias4 << L"]." << endl;

		Alias2+=50;
		Alias4+=50;

		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 4 - TYPE - [" << GetTypeInfoName<decltype(Alias4)>() << L"] VALUE [" << Alias4 << L"]." << endl;

		wcout << L"PUBLIC FIELD DERIVED 1 - VALUE [" << Object.GetPublicFieldDerived1() << L"]." << endl;
		wcout << L"PUBLIC FIELD DERIVED 2 - VALUE [" << Object.GetPublicFieldDerived2() << L"]." << endl;
		wcout << L"PUBLIC FIELD BASE 1 - VALUE [" << Object.GetPublicFieldBase1() << L"]." << endl;
		wcout << L"PUBLIC FIELD BASE 2 - VALUE [" << Object.GetPublicFieldBase2() << L"]." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze CLASS [CStructuredBindingClassDerived3] ma VIACERO BASE CLASSES.
		CStructuredBindingClassDerived3							Object(L"DERIVED",100,L"BASE 1",200,123.456,L"BASE 2");

		// !!!!! ALIASES su REFERENCES na CLASS FIELDS.
		auto&													[Alias1,Alias2,Alias3,Alias4,Alias5,Alias6]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;
		wcout << L"ALIAS 4 - TYPE - [" << GetTypeInfoName<decltype(Alias4)>() << L"] VALUE [" << Alias4 << L"]." << endl;
		wcout << L"ALIAS 5 - TYPE - [" << GetTypeInfoName<decltype(Alias5)>() << L"] VALUE [" << Alias5 << L"]." << endl;
		wcout << L"ALIAS 6 - TYPE - [" << GetTypeInfoName<decltype(Alias6)>() << L"] VALUE [" << Alias6 << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
auto StructuredBindingsCArraysFunction(CStructuredBindingCArrayValue(&Array)[3]) -> CStructuredBindingCArrayValue(&)[3]
{
	wcout << L"!!!!! FUNCTION CALLED." << endl;

	return(Array);
}
//----------------------------------------------------------------------------------------------------------------------
void TestStructuredBindingsCArrays(void)
{
	PrintLineSeparator();

	{
		int														Array[]={100,200,300};

		// !!!!! ALIASES obsahuju REFERENCES na C-ARRAY ITEMS.
		auto&													[Alias1,Alias2,Alias3]=Array;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;

		Alias1+=1;
		Alias2+=2;
		Alias3+=3;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;

		wcout << L"ARRAY 1 - VALUE [" << Array[0] << L"]." << endl;
		wcout << L"ARRAY 2 - VALUE [" << Array[1] << L"]." << endl;
		wcout << L"ARRAY 3 - VALUE [" << Array[2] << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CStructuredBindingCArrayValue							Array[]={100,200,300};

		// !!!!! ALIASES obsahuju KOPIE C-ARRAY ITEMS.
		auto													[Alias1,Alias2,Alias3]=Array;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2.GetValue() << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CStructuredBindingCArrayValue							Array[]={100,200,300};

		// !!!!! ALIASES obsahuju REFERENCES na C-ARRAY ITEMS.
		auto&													[Alias1,Alias2,Alias3]=Array;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2.GetValue() << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CStructuredBindingCArrayValue							Array[]={100,200,300};

		// !!!!! ALIASES obsahuju KOPIE C-ARRAY ITEMS, ktory vracia FUNCTION.
		// !!!!! C++ teda vytvara KOPIU C-ARRAY, ktoru vratila FUNCTION.
		auto													[Alias1,Alias2,Alias3]=StructuredBindingsCArraysFunction(Array);

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2.GetValue() << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3.GetValue() << L"]." << endl;

		Alias1.SetValue(1111);
		Alias2.SetValue(2222);
		Alias3.SetValue(3333);

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2.GetValue() << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3.GetValue() << L"]." << endl;

		wcout << L"ARRAY 1 - VALUE [" << Array[0].GetValue() << L"]." << endl;
		wcout << L"ARRAY 2 - VALUE [" << Array[1].GetValue() << L"]." << endl;
		wcout << L"ARRAY 3 - VALUE [" << Array[2].GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CStructuredBindingCArrayValue							Array[]={100,200,300};

		// !!!!! ALIASES obsahuju REFERENCES na C-ARRAY ITEMS.
		auto&													[Alias1,Alias2,Alias3]=StructuredBindingsCArraysFunction(Array);

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2.GetValue() << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3.GetValue() << L"]." << endl;

		Alias1.SetValue(1111);
		Alias2.SetValue(2222);
		Alias3.SetValue(3333);

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2.GetValue() << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3.GetValue() << L"]." << endl;

		wcout << L"ARRAY 1 - VALUE [" << Array[0].GetValue() << L"]." << endl;
		wcout << L"ARRAY 2 - VALUE [" << Array[1].GetValue() << L"]." << endl;
		wcout << L"ARRAY 3 - VALUE [" << Array[2].GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CStructuredBindingCArrayValue							Array[]={100,200,300};

		// !!!!! ALIASES obsahuju REFERENCES na C-ARRAY ITEMS.
		auto&&													[Alias1,Alias2,Alias3]=Array;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2.GetValue() << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestStructuredBindingsTuplesTuple(void)
{
	PrintLineSeparator();

	{
		tuple<CStructuredBindingCArrayValue,int,double>			Object(100,12,123.456);

		// !!! Na mapovanie ALIASES na TUPLE sa pouzije TUPLE PROTOCOL.
		auto													[Alias1,Alias2,Alias3]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		tuple<CStructuredBindingCArrayValue,int,double>			Object(100,12,123.456);

		// !!! Na mapovanie ALIASES na TUPLE sa pouzije TUPLE PROTOCOL.
		auto&													[Alias1,Alias2,Alias3]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;

		Alias1.SetValue(1111);
		Alias2+=1;
		Alias3+=1.1;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;

		wcout << L"TUPLE 1 - VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"TUPLE 2 - VALUE [" << Alias2 << L"]." << endl;
		wcout << L"TUPLE 3 - VALUE [" << Alias3 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		tuple<CStructuredBindingCArrayValue,int,double>			Object(100,12,123.456);

		// !!! Na mapovanie ALIASES na TUPLE sa pouzije TUPLE PROTOCOL.
		auto&&													[Alias1,Alias2,Alias3]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;

		Alias1.SetValue(1111);
		Alias2+=1;
		Alias3+=1.1;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;

		wcout << L"TUPLE 1 - VALUE [" << Alias1.GetValue() << L"]." << endl;
		wcout << L"TUPLE 2 - VALUE [" << Alias2 << L"]." << endl;
		wcout << L"TUPLE 3 - VALUE [" << Alias3 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestStructuredBindingsTuplesCustomClassFunctions(void)
{
	PrintLineSeparator();

	{
		CStructuredBindingTupleFunctions						Object(L"Timmy",12,123.456);

		auto													[Alias1,Alias2,Alias3]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
void TestStructuredBindingsTuplesCustomClassMethods(void)
{
	PrintLineSeparator();

	{
		CStructuredBindingTupleMethods							Object(L"Timmy",12,123.456);

		auto													[Alias1,Alias2,Alias3]=Object;

		wcout << L"ALIAS 1 - TYPE - [" << GetTypeInfoName<decltype(Alias1)>() << L"] VALUE [" << Alias1 << L"]." << endl;
		wcout << L"ALIAS 2 - TYPE - [" << GetTypeInfoName<decltype(Alias2)>() << L"] VALUE [" << Alias2 << L"]." << endl;
		wcout << L"ALIAS 3 - TYPE - [" << GetTypeInfoName<decltype(Alias3)>() << L"] VALUE [" << Alias3 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCallable, typename TType, size_t SIZE>
TType GenericLambdasTemplateFindFirst(TCallable Callable, TType(&Array)[SIZE], TType ToCompare)
{
	for(size_t Index=0;Index<SIZE;Index++)
	{
		const TType&											Item=Array[Index];

		if (Callable(Item,ToCompare)==true)
		{
			return(Item);
		}
	}

	throw(CException(L"NOT FOUND !"));
}
//----------------------------------------------------------------------------------------------------------------------
void TestGenericLambdas(void)
{
	PrintLineSeparator();

	{
		// !!!!! NON-GENERIC LAMBDA, pretoze NEPOUZIVA KEYWORD [auto].
		auto													Lambda=[] (int Value, int ToCompare) -> bool {return(Value==ToCompare);};

		int														Array[]={10,20,30};
		int														Result=GenericLambdasTemplateFindFirst(Lambda,Array,20);

		wcout << L"NON-GENERIC LAMBDA - LAMBDA TYPE [" << GetTypeInfoName<decltype(Lambda)>() << L"] RETURN TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] VALUE [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! GENERIC LAMBDA, pretoze POUZIVA KEYWORD [auto].
		// !!!!! Interne je LAMBDA EXPRESSION implementovana pomocou TEMPLATES a preto je ju mozne volat pre rozlicne TEMPLATE PARAMETERS.
		auto													Lambda=[] (auto Value, auto ToCompare) -> bool {return(Value==ToCompare);};

		int														Array1[]={10,20,30};
		int														Result1=GenericLambdasTemplateFindFirst(Lambda,Array1,20);

		wcout << L"GENERIC LAMBDA 1 - LAMBDA TYPE [" << GetTypeInfoName<decltype(Lambda)>() << L"] RETURN TYPE [" << GetTypeInfoName<decltype(Result1)>() << L"] VALUE [" << Result1 << L"]." << endl;

		double													Array2[]={10.1,20.2,30.3};
		double													Result2=GenericLambdasTemplateFindFirst(Lambda,Array2,20.2);

		wcout << L"GENERIC LAMBDA 2 - LAMBDA TYPE [" << GetTypeInfoName<decltype(Lambda)>() << L"] RETURN TYPE [" << GetTypeInfoName<decltype(Result2)>() << L"] VALUE [" << Result2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Definuje sa TEMPLATE ALIAS.
template<typename TType>
using															CTemplateAliasVector=CTemplateAlias<TType,vector<TType>>;
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TCollection>
void TemplateAliasesTemplate1(const CTemplateAlias<TType,TCollection>& Collection)
{
	wcout << L"TEMPLATE ALIAS 1 - TYPE [" << GetTypeInfoName<decltype(Collection)>() << L"]." << endl;

	for(typename CTemplateAlias<TType,TCollection>::SizeType Index=0;Index<Collection.GetSize();Index++)
	{
		const TType&											Item=Collection.GetItem(Index);

		wcout << L"\tITEM - TYPE [" << GetTypeInfoName<decltype(Item)>() << L"] VALUE [" << Item << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateAliasesTemplate2(const CTemplateAliasVector<TType>& Collection)
{
	wcout << L"TEMPLATE ALIAS 2 - TYPE [" << GetTypeInfoName<decltype(Collection)>() << L"]." << endl;

	for(typename CTemplateAliasVector<TType>::SizeType Index=0;Index<Collection.GetSize();Index++)
	{
		const TType&											Item=Collection.GetItem(Index);

		wcout << L"\tITEM - TYPE [" << GetTypeInfoName<decltype(Item)>() << L"] VALUE [" << Item << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateAliasesTemplate3(const CTemplateAlias<TType,vector<TType>>& Collection)
{
	wcout << L"TEMPLATE ALIAS 3 - TYPE [" << GetTypeInfoName<decltype(Collection)>() << L"]." << endl;

	for(typename CTemplateAlias<TType,vector<TType>>::SizeType Index=0;Index<Collection.GetSize();Index++)
	{
		const TType&											Item=Collection.GetItem(Index);

		wcout << L"\tITEM - TYPE [" << GetTypeInfoName<decltype(Item)>() << L"] VALUE [" << Item << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateAliases(void)
{
	PrintLineSeparator();

	{
		vector<int>												Vector={100,200,300};
		CTemplateAliasVector<int>								Object(Vector);

		// !!! ALIAS sa rozbali na TYPE a za potom sa robi DEDUCTION.
		TemplateAliasesTemplate1(Object);
	}

	PrintLineSeparator();

	{
		vector<int>												Vector={100,200,300};
		CTemplateAliasVector<int>								Object(Vector);

		// !!! ALIAS sa rozbali na TYPE a za potom sa robi DEDUCTION.
		TemplateAliasesTemplate2(Object);
	}

	PrintLineSeparator();

	{
		vector<int>												Vector={100,200,300};
		CTemplateAliasVector<int>								Object(Vector);

		// !!! ALIAS sa rozbali na TYPE a za potom sa robi DEDUCTION.
		TemplateAliasesTemplate3(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassDeductionDeductionGuidesImplicit(void)
{
	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z CONSTRUCTOR.
		CTemplateClassDeductionImplicitGuide					Object(CString(L"Timmy"),12);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z CONSTRUCTOR.
		CTemplateClassDeductionImplicitGuide					Object{CString(L"Timmy"),12};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z TEMPLATE CONSTRUCTOR.
		CTemplateClassDeductionImplicitGuide					Object(CString(L"Timmy"),12,123.456);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z TEMPLATE CONSTRUCTOR.
		CTemplateClassDeductionImplicitGuide					Object{CString(L"Timmy"),12,123.456};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z TEMPLATE CONSTRUCTOR.
		CTemplateClassDeductionImplicitGuide					Object1{CString(L"Timmy"),12,123.456};

		// !!!!! C++ vykona DEDUCTION TYPE [CTemplateClassDeductionImplicitGuide<CString,int>].
		CTemplateClassDeductionImplicitGuide					Object2{Object1};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object1)>() << L"] VALUE 1 [" << Object1.GetValue1() << L"] VALUE 2 [" << Object1.GetValue2() << L"]." << endl;
		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object2)>() << L"] VALUE 1 [" << Object2.GetValue1() << L"] VALUE 2 [" << Object2.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa NEVYKONAVA, lebo PARAMETERS su EXPLICITNE urcene.
		CTemplateClassDeductionImplicitGuideSupression<CString,int>	Object(CString(L"Timmy"),12);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze IMPLICIT DEDUCTION GUIDE je NEFUNKCNY. Je to preto, lebo CONSTRUCTOR z ktoreho je generovany pouziva CONSTRUCTOR PARAMETER TYPE [typename STemplateClassDeductionImplicitGuideSupressionValue<TType1>::Type] a CONSTRUCTOR PARAMETER TYPE [typename STemplateClassDeductionImplicitGuideSupressionValue<TType2>::Type] NIE su DEDUCTION CONTEXTS a pre ne sa TEMPLATE ARGUMENT DEDUCTION NEVYKONAVA.
		CTemplateClassDeductionImplicitGuideSupression			Object(CString(L"Timmy"),12);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze IMPLICIT DEDUCTION GUIDE je NEFUNKCNY. Je to preto, lebo CONSTRUCTOR z ktoreho je generovany pouziva CONSTRUCTOR PARAMETER TYPE [typename STemplateClassDeductionImplicitGuideSupressionValue<TType1>::Type] a CONSTRUCTOR PARAMETER TYPE [typename STemplateClassDeductionImplicitGuideSupressionValue<TType2>::Type] NIE su DEDUCTION CONTEXTS a pre ne sa TEMPLATE ARGUMENT DEDUCTION NEVYKONAVA.
		CTemplateClassDeductionImplicitGuideSupression			Object{CString(L"Timmy"),12};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassDeductionUserDefinedDeductionGuides(void)
{
	PrintLineSeparator();

	{
		// !!!!! C++ vykona DEDUCTION TEMPLATE PARAMETERS pomocou CONSTRUCTOR.
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1	Object(CString(L"Timmy"),12,123.456);
		CString													Text=Object.Print();

		wcout << L"DEDUCTION 1:" << endl << Text;
	}

	PrintLineSeparator();

	{
		// !!!!! C++ vykona DEDUCTION TEMPLATE PARAMETERS pomocou CONSTRUCTOR.
		// !!!!! DEDUCTION prebehne USPESNE, pretoze hoci TEMPLATE PARAMETER [TType3] nie je definovany, jeho DEFAULT VALUE je TEMPLATE PARAMETER [TType2] a v CONSTRUCTOR DEFAULT VALUE je EMPTY VALUE.
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1	Object(CString(L"Timmy"),12);
		CString													Text=Object.Print();

		wcout << L"DEDUCTION 2:" << endl << Text;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION sa NEVYKONAVA, pretoze vsetky TEMPLATE PARAMETERS su definovane EXPLICITNE.
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1<CString,long,long double>	Object(CString(L"Timmy"),12,123.456);
		CString													Text=Object.Print();

		wcout << L"NO DEDUCTION:" << endl << Text;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze DEDUCTION NIE je mozna iba pre cast TEMPLATE PARAMETERS, pricom ostatne by boli definovane EXPLICITNE.
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides1<CString>	Object(CString(L"Timmy"),12,123.456);
		CString													Text=Object.Print();

		wcout << L"DEDUCTION ERROR:" << endl << Text;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z CONSTRUCTOR.
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2	Object(CString(L"Timmy"),12);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z CONSTRUCTOR.
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2	Object{CString(L"Timmy"),12};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z CONSTRUCTOR.
		auto													Object=CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2{CString(L"Timmy"),12};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z CONSTRUCTOR.
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2	OriginalObject{CString(L"Timmy"),12};

		// !!!!! COMPILER hodi ERROR, pretoze medzi TEMPLATE CLASS NAME a VARIABLE NESMIE byt NIC. Ani POINTER IDENTIFIER [*].
		CTemplateClassDeductionUserDefinedGuideConstructorsNoGuides2*	Object=&OriginalObject;

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou IMPLICIT DEDUCTION GUIDE vytvoreneho z CONSTRUCTOR.
		CTemplateClassDeductionUserDefinedGuideConstructorsGuides	Object(CString(L"Timmy"),12);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou USER DEFINED DEDUCTION GUIDE.
		CTemplateClassDeductionUserDefinedGuideConstructorsGuides	Object(L"Timmy",12);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou USER DEFINED DEDUCTION GUIDE.
		CTemplateClassDeductionUserDefinedGuideConstructorsGuides	Object{L"Timmy",12};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou USER DEFINED DEDUCTION GUIDE.
		auto													Object=CTemplateClassDeductionUserDefinedGuideConstructorsGuides{L"Timmy",12};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION zbehne OK, pretoze obe OBJECT maju ROVNAKE TEMPLATE PARAMETERS.
		CTemplateClassDeductionUserDefinedGuideConstructorsGuides	Object1(L"Timmy",12),Object2(L"Jenny",13);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object1)>() << L"] VALUE 1 [" << Object1.GetValue1() << L"] VALUE 2 [" << Object1.GetValue2() << L"]." << endl;
		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object2)>() << L"] VALUE 1 [" << Object2.GetValue1() << L"] VALUE 2 [" << Object2.GetValue2() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze OBJECTS maju INE TEMPLATE PARAMETERS.
		CTemplateClassDeductionUserDefinedGuideConstructorsGuides	Object1(L"Timmy",12),Object2(123.456,12);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object1)>() << L"] VALUE 1 [" << Object1.GetValue1() << L"] VALUE 2 [" << Object1.GetValue2() << L"]." << endl;
		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object2)>() << L"] VALUE 1 [" << Object2.GetValue1() << L"] VALUE 2 [" << Object2.GetValue2() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou USER DEFINED DEDUCTION GUIDE.
		CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides	Object(L"Timmy",12);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou USER DEFINED DEDUCTION GUIDE.
		CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides	Object(CString(L"Timmy"),12);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION CLASS TEMPLATE PARAMETERS sa vykona pomocou USER DEFINED DEDUCTION GUIDE.
		CTemplateClassDeductionUserDefinedGuideNoConstructorsGuides	Object{CString(L"Timmy"),12};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassDeductionInjectedClassName(void)
{
	PrintLineSeparator();

	{
		CTemplateClassDeductionInjectedClassNames<int>			Object(100);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE [" << Object.GetValue() << L"]." << endl;

		Object.TestInjectedName(123.456);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateClassDeductionSubtletiesForwardingReferences(TType&& Value)
{
	std::wcout << L"TEMPLATE FUNCTION. TYPE 1 [" << GetTypeInfoName<TType>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassDeductionForwardingReferences(void)
{
	PrintLineSeparator();

	{
		int														Parameter=100;

		// !!!!! Vola sa IMPLICIT DEDUCTION GUIDE vytvoreny z CONSTRUCTOR, ktory ma ako PARAMETER TYPE [const TType&].
		CTemplateClassDeductionForwardingReferences				Object=Parameter;

		wcout << L"DEDUCTION PRIMITIVE TYPE - LVALUE - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Aj ked sa vola IMPLICIT DEDUCTION GUIDE vytvoreneho z CONSTRUCTOR, ktory ma ako PARAMETER FORWARDING REFERENCE, kedze pri DEDUCTION GUIDES sa specialna DEDUCTION pre FORWARDING REFERENCES NEAPLIKUJE, tak DEDUCED TYPE je TYPE [int], a NIE TYPE [int&].
		CTemplateClassDeductionForwardingReferences				Object(100);

		wcout << L"DEDUCTION PRIMITIVE TYPE - RVALUE - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CString													Parameter(L"Timmy");

		// !!!!! Vola sa IMPLICIT DEDUCTION GUIDE vytvoreny z CONSTRUCTOR, ktory ma ako PARAMETER TYPE [const TType&].
		CTemplateClassDeductionForwardingReferences				Object=Parameter;

		wcout << L"DEDUCTION OBJECT - LVALUE - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Aj ked sa vola IMPLICIT DEDUCTION GUIDE vytvoreneho z CONSTRUCTOR, ktory ma ako PARAMETER FORWARDING REFERENCE, kedze pri DEDUCTION GUIDES sa specialna DEDUCTION pre FORWARDING REFERENCES NEAPLIKUJE, tak DEDUCED TYPE je TYPE [CString], a NIE TYPE [CString&].
		CTemplateClassDeductionForwardingReferences				Object(CString(L"Timmy"));

		wcout << L"DEDUCTION OBJECT - RVALUE - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Parameter=100;

		// !!!!! V TEMPLATE FUNCTIONS sa specialny TEMPLATE ARGUMENT DEDUCTION pre FORWARDING REFERENCES APLIKUJE a teda DEDUCED TYPE je TYPE [int&] a NIE TYPE [int].
		TemplateClassDeductionSubtletiesForwardingReferences(Parameter);
	}

	PrintLineSeparator();

	{
		CString													Parameter(L"Timmy");

		// !!!!! V TEMPLATE FUNCTIONS sa specialny TEMPLATE ARGUMENT DEDUCTION pre FORWARDING REFERENCES APLIKUJE a teda DEDUCED TYPE je TYPE [CString&] a NIE TYPE [CString].
		TemplateClassDeductionSubtletiesForwardingReferences(Parameter);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassDeductionExplicit(void)
{
	PrintLineSeparator();

	{
		CTemplateClassDeductionUserDefinedGuideNoExplicit		Object=100;

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();

	{
		CTemplateClassDeductionUserDefinedGuideNoExplicit		Object{100};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();

	{
		// !!!!! EXPLICIT DEDUCTION GUIDE sa NEPOUZIJE, pretoze sa pouzila COPY INITIALIZATION a pre nu sa EXPLICIT DEDUCTION GUIDES NEPOUZIVAJU.
		CTemplateClassDeductionUserDefinedGuideExplicit			Object=100;

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();

	{
		// !!!!! EXPLICIT DEDUCTION GUIDE sa POUZIJE, pretoze sa NEPOUZILA COPY INITIALIZATION.
		CTemplateClassDeductionUserDefinedGuideExplicit			Object(100);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();

	{
		// !!!!! EXPLICIT DEDUCTION GUIDE sa POUZIJE, pretoze sa NEPOUZILA COPY INITIALIZATION.
		CTemplateClassDeductionUserDefinedGuideExplicit			Object{100};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassDeductionCopyConstruction(void)
{
	PrintLineSeparator();

	{
		auto													OriginalObject=CTemplateClassDeductionCopyConstruction{100,222.222};

		// !!! Pouzije sa DEDUCTION GUIDE [CTemplateClassDeductionCopyConstruction(TTypes...) -> CTemplateClassDeductionCopyConstruction<TTypes...>].
		CTemplateClassDeductionCopyConstruction					Object=OriginalObject;

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();

	{
		auto													OriginalObject=CTemplateClassDeductionCopyConstruction{100,222.222};

		// !!! Pouzije sa DEDUCTION GUIDE [CTemplateClassDeductionCopyConstruction(TTypes...) -> CTemplateClassDeductionCopyConstruction<TTypes...>].
		CTemplateClassDeductionCopyConstruction					Object(OriginalObject);

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();

	{
		auto													OriginalObject=CTemplateClassDeductionCopyConstruction{100,222.222};

		// !!!!! Pouzije sa DEDUCTION GUIDE [CTemplateClassDeductionCopyConstruction(const CTemplateClassDeductionCopyConstruction<TTypes...>&) -> CTemplateClassDeductionCopyConstruction<TTypes...>].
		CTemplateClassDeductionCopyConstruction					Object{OriginalObject,OriginalObject};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();

	{
		auto													OriginalObject=CTemplateClassDeductionCopyConstruction{100,222.222};

		// !!!!! Pouzije sa DEDUCTION GUIDE [CTemplateClassDeductionCopyConstruction(TTypes...) -> CTemplateClassDeductionCopyConstruction<TTypes...>] namiesto DEDUCTION GUIDE [CTemplateClassDeductionCopyConstruction(const CTemplateClassDeductionCopyConstruction<TTypes...>&) -> CTemplateClassDeductionCopyConstruction<TTypes...>].
		CTemplateClassDeductionCopyConstruction					Object{OriginalObject};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();

	{
		auto													OriginalObject=CTemplateClassDeductionCopyConstruction{100,222.222};

		// !!!!! Pouzije sa DEDUCTION GUIDE [CTemplateClassDeductionCopyConstruction(TTypes...) -> CTemplateClassDeductionCopyConstruction<TTypes...>] namiesto DEDUCTION GUIDE [CTemplateClassDeductionCopyConstruction(const CTemplateClassDeductionCopyConstruction<TTypes...>&) -> CTemplateClassDeductionCopyConstruction<TTypes...>].
		auto													Object=CTemplateClassDeductionCopyConstruction{OriginalObject};

		wcout << L"DEDUCTION - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"]." << endl;

		Object.PrintTypes();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassDeductionOverloadedConstructors(void)
{
	PrintLineSeparator();

	{
		CTemplateClassDeductionOverloadedConstructorsInner		InnerObject(100);

		// !!!!! DEDUCTION GUIDE je pouzity IBA na urcenie TEMPLATE PARAMETERS TEMPLATE CLASS. Ten je vdaka DEDUCTION GUIDERurceny ako TYPE [CTemplateClassDeductionOverloadedConstructorsOuter<int>] a NIE TYPE [CTemplateClassDeductionOverloadedConstructorsOuter<CTemplateClassDeductionOverloadedConstructorsInner<int>>].
		// !!!!! Po urceni TEMPLATE PARAMETERS TEMPLATE CLASS je vykonany OVERLOADING RESOLUTION pre vyber spravneho CONSTRUCTOR a je vybraty CONSTRUCTOR pre LVALUE PARAMETER [const CTemplateClassDeductionOverloadedConstructorsInner<TType>&].
		CTemplateClassDeductionOverloadedConstructorsOuter		OuterObject(InnerObject);

		wcout << L"INNER OBJECT - TYPE [" << GetTypeInfoName<decltype(InnerObject)>() << L"] VALUE [" << InnerObject.GetValue() << L"]." << endl;
		wcout << L"OUTER OBJECT - TYPE [" << GetTypeInfoName<decltype(OuterObject)>() << L"] VALUE [" << OuterObject.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCTION GUIDE je pouzity IBA na urcenie TEMPLATE PARAMETERS TEMPLATE CLASS. Ten je vdaka DEDUCTION GUIDERurceny ako TYPE [CTemplateClassDeductionOverloadedConstructorsOuter<int>] a NIE TYPE [CTemplateClassDeductionOverloadedConstructorsOuter<CTemplateClassDeductionOverloadedConstructorsInner<int>>].
		// !!!!! Po urceni TEMPLATE PARAMETERS TEMPLATE CLASS je vykonany OVERLOADING RESOLUTION pre vyber spravneho CONSTRUCTOR a je vybraty CONSTRUCTOR pre RVALUE PARAMETER [CTemplateClassDeductionOverloadedConstructorsInner<TType>&&].
		CTemplateClassDeductionOverloadedConstructorsOuter		OuterObject(CTemplateClassDeductionOverloadedConstructorsInner(100));

		wcout << L"OUTER OBJECT - TYPE [" << GetTypeInfoName<decltype(OuterObject)>() << L"] VALUE [" << OuterObject.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTemplateArgumentDeduction();
	//TestTemplateArgumentDeductionReferenceTypes();
	//TestTemplateArgumentDeductionDecay();
	//TestTemplateArgumentDeductionContext();
	//TestSpecialTemplateArgumentDeduction();
	//TestTemplateArgumentDeductionInitializerLists();
	//TestTemplateArgumentDeductionParameterPacks();
	//TestReferenceToReference();
	//TestReferenceCollapsingRules();
	//TestTemplateArgumentDeductionForwardingReference();
	//TestPerfectForwarding();
	//TestPerfectForwardingVariadic();
	//TestForwardingReferenceDeductionSurprises();
	//TestNonForwardingReferences();
	//TestSFINAE();
	//TestImmediateContexts();
	//TestTemplateArgumentDeductionAllowableConversions();
	//TestTemplateClassDeduction();
	//TestTemplateArgumentDeductionDefaultArguments();
	//TestTemplateArgumentDeductionExceptionSpecification();
	//TestExplicitTemplateArguments();
	//TestSpecifierAuto();
	//TestSpecifierAutoReturnValueType();
	//TestSpecifierAutoNonTypeTemplateParameter();
	//TestDecltypeKeywordEntity();
	//TestDecltypeKeywordValueCategory();
	//TestDecltypeAutoKeyword();
	//TestSpecialDeductionRules();
	//TestStructuredBindingsClasses();
	//TestStructuredBindingsCArrays();
	//TestStructuredBindingsTuplesTuple();
	//TestStructuredBindingsTuplesCustomClassFunctions();
	//TestStructuredBindingsTuplesCustomClassMethods();
	//TestGenericLambdas();
	//TestTemplateAliases();
	//TestTemplateClassDeductionDeductionGuidesImplicit();
	//TestTemplateClassDeductionUserDefinedDeductionGuides();
	//TestTemplateClassDeductionInjectedClassName();
	//TestTemplateClassDeductionForwardingReferences();
	//TestTemplateClassDeductionExplicit();
	//TestTemplateClassDeductionCopyConstruction();
	TestTemplateClassDeductionOverloadedConstructors();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------