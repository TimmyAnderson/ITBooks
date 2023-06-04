//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CDummyClass.h"
#include "CClassWithMethodGetValue.h"
#include "CTemplateClassWithConcept.h"
#include "CTemplateClassMethodWithConcept.h"
#include "CClassWithOperatorLower.h"
#include "CClassWithOperatorLowerAndMultiple.h"
#include "CClassWithOperatorLowerAndMultipleException.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26800 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Definuje sa NAMED CONCEPT, ktory vyzaduje, aby TYPE PARAMETER 'TType' mal definovany OPERATOR<, ktory vracia TYPE, ktory je konvertovatelny na TYPE [bool].
template<typename TType>
concept ConceptTemplateFunctionConcept=requires(TType A, TType B)
{
	// !!!!! CODE ELEMENT 'convertible_to<bool>' je CONCEPT definovany C++ STANDARD LIBRARY.
	{A<B} -> convertible_to<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
// !!! CONCEPT sa aplikuje na TEMPLATE FUNCTION.
template<typename TType> requires ConceptTemplateFunctionConcept<TType>
TType TemplateTemplateFunctionConcept(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionConcept(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateTemplateFunctionConcept(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!!!! COMPILER NEHODI ERROR, pretoze CLASS 'CClassWithOperatorLower' MA definovany OPERATOR<.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateTemplateFunctionConcept(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CDummyClass' NEMA definovany OPERATOR<.
	{
		CDummyClass												Value1=10;
		CDummyClass												Value2=20;
		CDummyClass												Result=TemplateTemplateFunctionConcept(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassConcept(void)
{
	PrintLineSeparator();

	// !!! CODE zbehne, pretoze CLASS 'CClassWithMethodGetValue' ma METHOD [const wstring& GetValue(void) const], ktoru vyzaduje METHOD [wstring Print(void) const].
	{
		CClassWithMethodGetValue								Value1(L"Timmy");
		CClassWithMethodGetValue								Value2(L"Anderson");
		CTemplateClassWithConcept<CClassWithMethodGetValue>		Template(Value1,Value2);

		wcout << L"VALUE 1 [" << Template.GetValue1().GetValue() << L"]" << L" VALUE 2 [" << Template.GetValue2().GetValue() << L"] !" << endl;

		wcout << L"TEMPLATE [" << Template.Print() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze TEMPLATE ARGUMENT TYPE [int] NEMA METHOD [const wstring& GetValue(void) const], ktoru vyzaduje CLASS REQUIREMENT.
	{
		int														Value1(10);
		int														Value2(20);
		CTemplateClassWithConcept<int>							Template(Value1,Value2);

		wcout << L"VALUE 1 [" << Template.GetValue1() << L"]" << L" VALUE 2 [" << Template.GetValue2() << L"] !" << endl;

		wcout << L"TEMPLATE [" << Template.Print() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassMethodConcept(void)
{
	PrintLineSeparator();

	// !!! CODE zbehne, pretoze CLASS 'CClassWithMethodGetValue' ma METHOD [const wstring& GetValue(void) const], ktoru vyzaduje METHOD [wstring Print(void) const].
	{
		CClassWithMethodGetValue								Value1(L"Timmy");
		CClassWithMethodGetValue								Value2(L"Anderson");
		CTemplateClassMethodWithConcept<CClassWithMethodGetValue>	Template(Value1,Value2);

		wcout << L"VALUE 1 [" << Template.GetValue1().GetValue() << L"]" << L" VALUE 2 [" << Template.GetValue2().GetValue() << L"] !" << endl;

		wcout << L"TEMPLATE [" << Template.Print() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Value1(10);
		int														Value2(20);
		CTemplateClassMethodWithConcept<int>					Template(Value1,Value2);

		wcout << L"VALUE 1 [" << Template.GetValue1() << L"]" << L" VALUE 2 [" << Template.GetValue2() << L"] !" << endl;

		// !!! COMPILER hodi ERROR, pretoze TEMPLATE ARGUMENT TYPE [int] NEMA METHOD [const wstring& GetValue(void) const], ktoru vyzaduje CLASS METHOD REQUIREMENT.
		
		//wcout << L"TEMPLATE [" << Template.Print() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Ako REQUIREMENT je mozne pouzit aj CONSTEXPR FUNCTION.
template<typename TType>
constexpr bool FunctionRequirementsPrimaryExpression(void)
{
	bool														IsInteger=is_integral_v<TType>;

	return(IsInteger);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! REQUIREMENT CONSTEXPR FUNCTION sa aplikuje na TEMPLATE FUNCTION.
// !!!!! Kedze CONSTEXPR FUNCTION NIE JE PRIMARY EXPRESSION, je NUTNE obalit jej volanie pomocou ZATVORIEK [()], aby z neho vznikol PRIMARY EXPRESSION.
template<typename TType> requires (FunctionRequirementsPrimaryExpression<TType>())
TType TemplateRequirementsPrimaryExpression(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequirementsPrimaryExpression(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateRequirementsPrimaryExpression(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TYPE [double] NIE JE INTEGER TYPE.
	{
		double													Value1=10;
		double													Value2=20;
		double													Result=TemplateRequirementsPrimaryExpression(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Definuje sa TEMPLATE FUNCTION, ktora pouziva 2 TYPE TRAITS ako REQUIREMENTS.
// !!!!! TYPE PARAMETER 'TType' musi byt bud INTEGER TYPE, alebo FLOATING POINT TYPE.
// !!!!! Medzera v CODE 'is_integral_v<TType> ==true' je NUTNA, aby to akceptoval COMPILER.
// !!!!! CODE [is_integral_v<TType>] a CODE [is_floating_point_v<TType>] su TYPE TRAITS, a NIE CONCEPTS.
template<typename TType> requires (is_integral_v<TType> ==true || is_floating_point_v<TType> ==true)
TType TemplateRequirementsTypeTraits(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequirementsTypeTraits(void)
{
	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT je INTEGER TYPE.
	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateRequirementsTypeTraits(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT je FLOATING POINT TYPE.
	{
		double													Value1=10.1;
		double													Value2=20.2;
		double													Result=TemplateRequirementsTypeTraits(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, lebo TYPE 'CClassWithOperatorLower' NIE JE INTEGER TYPE, ani FLOATING POINT TYPE.
	{
		CClassWithOperatorLower									Value1=10.1;
		CClassWithOperatorLower									Value2=20.2;
		CClassWithOperatorLower									Result=TemplateRequirementsTypeTraits(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Definuje sa CONCEPT.
template<typename TType>
concept ConceptRequirementsConcept=requires(TType A, TType B)
{
	// !!!!! CODE ELEMENT 'convertible_to<bool>' je CONCEPT definovany C++ STANDARD LIBRARY.
	{A<B} -> convertible_to<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
// !!! Definuje sa TEMPLATE, ktora ma CONCEPT REQUIREMENT.
template<typename TType> requires ConceptRequirementsConcept<TType>
TType TemplateRequirementsConcept(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequirementsConcept(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateRequirementsConcept(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!!!! COMPILER NEHODI ERROR, pretoze CLASS 'CClassWithOperatorLower' MA definovany OPERATOR<.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateRequirementsConcept(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CDummyClass' NEMA definovany OPERATOR<.
	{
		CDummyClass												Value1=10;
		CDummyClass												Value2=20;
		CDummyClass												Result=TemplateRequirementsConcept(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONCEPT vyzaduje, aby TYPE PARAMETER 'TType' mal definovany OPERATOR<, ktory vracia TYPE, ktory je konvertovatelny na TYPE [bool].
template<typename TType>
concept ConceptMultipleRequirementsAnd=requires(TType A, TType B)
{
	{A<B} -> convertible_to<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Na TEMPLATE PARAMETERS v TEMPLATE FUNCTIONS je mozne aplikovat VIACERO REQUIREMENTS pomocou OPERATOR&&.
// !!!!! OPERATOR&& NIE JE aplikovany priamo v CONCEPT, ale na TEMPLATE PARAMETER TEMPLATE FUNCTION.
// !!!!! TEMPLATE FUNCTION vyzaduje, aby TEMPLATE PARAMETER splnal 2 REQUIREMENTS.
// !!!!! 1. TEMPLATE PARAMETER MUSI byt INTEGER TYPE.
// !!!!! 2. TEMPLATE PARAMETER MUSI splnat CONCEPT 'ConceptMultipleRequirementsAnd<TType>'.
template<typename TType> requires (is_integral_v<TType> ==true && ConceptMultipleRequirementsAnd<TType>)
TType TemplateMultipleRequirementsAnd(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestMultipleRequirementsAnd(void)
{
	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT je INTEGER TYPE a MA definovany OPERATOR<.
	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateMultipleRequirementsAnd(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze hoci TYPE ARGUMENT MA definovany OPERATOR<, NIE je to INTEGER TYPE.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateMultipleRequirementsAnd(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Na TEMPLATE PARAMETERS v TEMPLATE FUNCTIONS je mozne aplikovat VIACERO REQUIREMENTS pomocou OPERATOR||.
// !!!!! OPERATOR|| NIE JE aplikovany priamo v CONCEPT, ale na TEMPLATE PARAMETER TEMPLATE FUNCTION.
// !!!!! TEMPLATE FUNCTION vyzaduje, aby TEMPLATE PARAMETER splnal aspon 1 z 2 REQUIREMENTS.
// !!!!! 1. TEMPLATE PARAMETER MUSI byt INTEGER TYPE.
// !!!!! 2. TEMPLATE PARAMETER MUSI byt FLOATINT POINT TYPE.
template<typename TType> requires (is_integral_v<TType> ==true || is_floating_point_v<TType> ==true)
TType TemplateMultipleRequirementsOr(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestMultipleRequirementsOr(void)
{
	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT je INTEGER TYPE.
	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateMultipleRequirementsOr(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT je FLOATING POINT TYPE.
	{
		double													Value1=10.1;
		double													Value2=20.2;
		double													Result=TemplateMultipleRequirementsOr(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, lebo TYPE 'CClassWithOperatorLower' NIE JE INTEGER TYPE, ani FLOATING POINT TYPE.
	{
		CClassWithOperatorLower									Value1=10.1;
		CClassWithOperatorLower									Value2=20.2;
		CClassWithOperatorLower									Result=TemplateMultipleRequirementsOr(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION vyzaduje, aby TEMPLATE PARAMETERS splnali jednu z nasledujucich podmienok.
// !!!!! 1. TEMPLATE PARAMETER 'TType1' je identicky s TEMPLATE PARAMETER 'TType2'.
// !!!!! 2. TEMPLATE PARAMETER 'TType2' je IMPLICITNE KONVERTOVATELNY na TEMPLATE PARAMETER 'TType2'.
template<typename TType1, typename TType2> requires (is_same_v<TType1,TType2> ==true || is_convertible_v<TType2,TType1> ==true)
TType1 TemplateMultipleTemplateParametersRequirements(TType1 A, TType2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestMultipleTemplateParametersRequirements(void)
{
	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT 'TType1' je IDENTICKY s TYPE ARGUMENT 'TType2'.
	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateMultipleTemplateParametersRequirements(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT 'TType2' je IMPLICITNE KONVERTOVATELNY na TYPE ARGUMENT 'TType1'.
	{
		int														Value1=10;
		double													Value2=20.2;
		int														Result=TemplateMultipleTemplateParametersRequirements(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TYPE ARGUMENT 'TType1' je NIE je IDENTICKY s TYPE ARGUMENT 'TType2' a zaroven, TYPE ARGUMENT 'TType2' NIE je IMPLICITNE KONVERTOVATELNY na TYPE ARGUMENT 'TType1'.
	{
		int														Value1=10;
		CClassWithOperatorLower									Value2=20.2;
		int														Result=TemplateMultipleTemplateParametersRequirements(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ CLAUSE sa aplikuje ZA KEYWORD [template<>].
template<typename TType> requires is_integral_v<TType>
TType TemplateRequiresClauseAfterTemplateKeyword(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequiresClauseAfterTemplateKeyword(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateRequiresClauseAfterTemplateKeyword(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TYPE [double] NIE JE INTEGER TYPE.
	{
		double													Value1=10;
		double													Value2=20;
		double													Result=TemplateRequiresClauseAfterTemplateKeyword(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ CLAUSE sa aplikuje ZA FUNCTION PARAMETERS.
template<typename TType>
TType TemplateRequiresClauseAfterFunctionParameters(TType A, TType B) requires is_integral_v<TType>
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequiresClauseAfterFunctionParameters(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateRequiresClauseAfterFunctionParameters(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TYPE [double] NIE JE INTEGER TYPE.
	{
		double													Value1=10;
		double													Value2=20;
		double													Result=TemplateRequiresClauseAfterFunctionParameters(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptShorthandRequirementNotation1=requires(TType A, TType B)
{
	{A<B} -> convertible_to<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
// !!! Na definovanie REQUIREMENT sa pouziva SHORTHAND SYNTAX.
template<ConceptShorthandRequirementNotation1 TType>
TType TemplateShorthandRequirementNotation1(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestShorthandRequirementNotation1(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateShorthandRequirementNotation1(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CDummyClass' NEMA definovany OPERATOR<.
	{
		CDummyClass												Value1=10;
		CDummyClass												Value2=20;
		CDummyClass												Result=TemplateShorthandRequirementNotation1(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptShorthandRequirementNotation2A=requires(TType A, TType B)
{
	{A<B} -> convertible_to<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptShorthandRequirementNotation2B=is_class_v<TType> ==false;
//----------------------------------------------------------------------------------------------------------------------
// !!! Na definovanie REQUIREMENT sa pouziva SHORTHAND SYNTAX.
template<ConceptShorthandRequirementNotation2A TType> requires ConceptShorthandRequirementNotation2B<TType>
TType TemplateShorthandRequirementNotation2(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestShorthandRequirementNotation2(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateShorthandRequirementNotation2(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CDummyClass' NEMA definovany OPERATOR< a je to CLASS.
	{
		CDummyClass												Value1=10;
		CDummyClass												Value2=20;
		CDummyClass												Result=TemplateShorthandRequirementNotation2(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/
	
	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CClassWithOperatorLower' sice MA definovany OPERATOR<, ale je to CLASS.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateShorthandRequirementNotation2(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! V CONCEPTS je mozne aplikovat VIACERO REQUIREMENTS pomocou OPERATOR&&.
// !!!!! OPERATOR&& JE aplikovany priamo v CONCEPT.
// !!!!! CONCEPT vyzaduje, aby TEMPLATE PARAMETER splnal 2 REQUIREMENTS.
// !!!!! 1. TEMPLATE PARAMETER MUSI byt INTEGER TYPE.
// !!!!! 2. TEMPLATE PARAMETER MUSI mat definovany OPERATOR<.
template<typename TType>
concept ConceptWithMultipleRequirementsAnd=is_integral_v<TType> ==true && requires(TType A, TType B)
{
	{A<B} -> convertible_to<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType> requires (ConceptWithMultipleRequirementsAnd<TType>)
TType TemplateFunctionConceptWithMultipleRequirementsAnd(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestConceptWithMultipleRequirementsAnd(void)
{
	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT je INTEGER TYPE a MA definovany OPERATOR<.
	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateFunctionConceptWithMultipleRequirementsAnd(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze hoci TYPE ARGUMENT MA definovany OPERATOR<, NIE je to INTEGER TYPE.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateFunctionConceptWithMultipleRequirementsAnd(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! V CONCEPTS je mozne aplikovat VIACERO REQUIREMENTS pomocou OPERATOR||.
// !!!!! OPERATOR&& JE aplikovany priamo v CONCEPT.
// !!!!! CONCEPT vyzaduje, aby TEMPLATE PARAMETER splnal aspon 1 z 2 REQUIREMENTS.
// !!!!! 1. TEMPLATE PARAMETER MUSI byt INTEGER TYPE.
// !!!!! 2. TEMPLATE PARAMETER MUSI mat definovany OPERATOR<.
template<typename TType>
concept ConceptWithMultipleRequirementsOr=is_integral_v<TType> ==true || requires(TType A, TType B)
{
	{A<B} -> convertible_to<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType> requires (ConceptWithMultipleRequirementsOr<TType>)
TType TemplateFunctionConceptWithMultipleRequirementsOr(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestConceptWithMultipleRequirementsOr(void)
{
	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT je INTEGER TYPE a MA definovany OPERATOR<.
	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateFunctionConceptWithMultipleRequirementsOr(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! COMPILER CODE akceptuje lebo TYPE ARGUMENT sice NIE JE INTEGER TYPE, ale MA definovany OPERATOR<.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateFunctionConceptWithMultipleRequirementsOr(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, lebo CODE TYPE ARGUMENT NIE JE INTEGER TYPE a ani nema definovany OPERATOR<.
	{
		CDummyClass												Value1=10;
		CDummyClass												Value2=20;
		CDummyClass												Result=TemplateFunctionConceptWithMultipleRequirementsOr(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptRequirementsSimple=requires(TType A, TType B)
{
	// !!! SIMPLE REQUIREMENT vyzaduje, aby bol nasledujuci EXPRESSION COMPILOVATELNY.
	A<B;

	// !!! SIMPLE REQUIREMENT vyzaduje, aby bol nasledujuci EXPRESSION COMPILOVATELNY.
	A*B;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType> requires ConceptRequirementsSimple<TType>
TType TemplateFunctionRequirementsSimple(TType A, TType B)
{
	if (A<B)
	{
		TType													Result=(B*B);

		return(Result);
	}
	else
	{
		TType													Result=(A*A);

		return(Result);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequirementsSimple(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateFunctionRequirementsSimple(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
	 
	// !!!!! CODE zbehne, pretoze CLASS 'CClassWithOperatorLowerAndMultiple' MA definovany OPERATOR< a MA definovany aj OPERATOR*.
	{
		CClassWithOperatorLowerAndMultiple						Value1=10;
		CClassWithOperatorLowerAndMultiple						Value2=20;
		CClassWithOperatorLowerAndMultiple						Result=TemplateFunctionRequirementsSimple(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CClassWithOperatorLower' MA definovany OPERATOR<, ale NEMA definovany OPERATOR*.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateFunctionRequirementsSimple(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptRequirementsType=requires(TType A, TType B)
{
	// !!!!! TYPE REQUIREMENT, aby existoval pre danu EXPRESSION TYPE.
	typename TType::TInnerType;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType> requires ConceptRequirementsType<TType>
TType TemplateFunctionRequirementsType(TType A, TType B)
{
	if (A<B)
	{
		TType													Result=(B*B);

		return(Result);
	}
	else
	{
		TType													Result=(A*A);

		return(Result);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequirementsType(void)
{
	PrintLineSeparator();
	 
	// !!!!! CODE zbehne, pretoze CLASS 'CClassWithOperatorLowerAndMultiple' MA USING 'TInnerType'.
	{
		CClassWithOperatorLowerAndMultiple						Value1=10;
		CClassWithOperatorLowerAndMultiple						Value2=20;
		CClassWithOperatorLowerAndMultiple						Result=TemplateFunctionRequirementsType(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze CLASS [int] nema USING 'TInnerType'.
	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateFunctionRequirementsType(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptRequirementsCompound=requires(TType A, TType B)
{
	// !!!!! COMPOUND REQUIREMENT umoznuje definovat okrem EXPRESSION aj to aky CONCEPT ma EXPRESSION splnat a to ci moze, ale nemoze hodit EXCEPTION.
	// !!!!! COMPOUND REQUIREMENT vyzaduje splnenie nasledujucich podmienok.
	// 1. Aby bol EXPRESSION COMPILOVATELNY.
	// 2. Aby EXPRESSION splnal CONCEPT [same_as<TType>], ktory urcuje, ze EXPRESSION ma vracat TYPE rovnaky ako TYPE [bool].
	// 3. Aby EXPRESSION nahodil EXCEPTION.
	{A<B} noexcept -> same_as<bool>;

	// !!!!! COMPOUND REQUIREMENT umoznuje definovat okrem EXPRESSION aj to aky CONCEPT ma EXPRESSION splnat a to ci moze, ale nemoze hodit EXCEPTION.
	// !!!!! COMPOUND REQUIREMENT vyzaduje splnenie nasledujucich podmienok.
	// 1. Aby bol EXPRESSION COMPILOVATELNY.
	// 2. Aby EXPRESSION splnal CONCEPT [same_as<TType>], ktory urcuje, ze EXPRESSION ma byt CONVERTIBLE na TYPE 'TType'.
	// 3. Aby EXPRESSION nahodil EXCEPTION.
	{A*B} noexcept -> convertible_to<TType>;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType> requires ConceptRequirementsCompound<TType>
TType TemplateFunctionRequirementsCompound(TType A, TType B)
{
	if (A<B)
	{
		TType													Result=(B*B);

		return(Result);
	}
	else
	{
		TType													Result=(A*A);

		return(Result);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequirementsCompound(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateFunctionRequirementsCompound(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
	 
	// !!!!! CODE zbehne, pretoze CLASS 'CClassWithOperatorLowerAndMultiple' MA definovany OPERATOR< a MA definovany aj OPERATOR*.
	{
		CClassWithOperatorLowerAndMultiple						Value1=10;
		CClassWithOperatorLowerAndMultiple						Value2=20;
		CClassWithOperatorLowerAndMultiple						Result=TemplateFunctionRequirementsCompound(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CClassWithOperatorLower' MA definovany OPERATOR<, ale NEMA definovany OPERATOR*.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateFunctionRequirementsCompound(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CClassWithOperatorLowerAndMultipleException' MA definovany OPERATOR< a MA definovany OPERATOR*, ale ANI JEDEN z NICH NIE JE oznaceny pomocou KEYWORD [noexcept].
	{
		CClassWithOperatorLowerAndMultipleException				Value1=10;
		CClassWithOperatorLowerAndMultipleException				Value2=20;
		CClassWithOperatorLowerAndMultipleException				Result=TemplateFunctionRequirementsCompound(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptRequirementsCompoundReferenced=requires(TType A, TType B)
{
	// !!!!! COMPOUND REQUIREMENT umoznuje definovat okrem EXPRESSION aj to aky CONCEPT ma EXPRESSION splnat a to ci moze, ale nemoze hodit EXCEPTION.
	// !!!!! COMPOUND REQUIREMENT vyzaduje splnenie nasledujucich podmienok.
	// 1. Aby bol EXPRESSION COMPILOVATELNY.
	// 2. Aby EXPRESSION splnal CONCEPT [same_as<TType>], ktory urcuje, ze EXPRESSION ma vracat TYPE rovnaky ako TYPE [bool].
	// 3. Aby EXPRESSION nahodil EXCEPTION.
	{A<B} noexcept -> same_as<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NESTED COMPOIN
template<typename TType>
concept ConceptRequirementsNested=requires(TType A, TType B)
{
	// !!!!! Toto je NESTED REQUIREMENT.
	// !!!!! NESTED REQUIREMENT umoznuje vyzadovat platnost ineho REQUIREMENT.
	requires ConceptRequirementsCompoundReferenced<TType>;

	// !!!!! Toto je COMPOUND REQUIREMENT.
	{A*B} noexcept -> convertible_to<TType>;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType> requires ConceptRequirementsNested<TType>
TType TemplateFunctionRequirementsNested(TType A, TType B)
{
	if (A<B)
	{
		TType													Result=(B*B);

		return(Result);
	}
	else
	{
		TType													Result=(A*A);

		return(Result);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequirementsNested(void)
{
	PrintLineSeparator();

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateFunctionRequirementsNested(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
	 
	// !!!!! CODE zbehne, pretoze CLASS 'CClassWithOperatorLowerAndMultiple' MA definovany OPERATOR< a MA definovany aj OPERATOR*.
	{
		CClassWithOperatorLowerAndMultiple						Value1=10;
		CClassWithOperatorLowerAndMultiple						Value2=20;
		CClassWithOperatorLowerAndMultiple						Result=TemplateFunctionRequirementsNested(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CClassWithOperatorLower' MA definovany OPERATOR<, ale NEMA definovany OPERATOR*.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateFunctionRequirementsNested(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CClassWithOperatorLowerAndMultipleException' MA definovany OPERATOR< a MA definovany OPERATOR*, ale ANI JEDEN z NICH NIE JE oznaceny pomocou KEYWORD [noexcept].
	{
		CClassWithOperatorLowerAndMultipleException				Value1=10;
		CClassWithOperatorLowerAndMultipleException				Value2=20;
		CClassWithOperatorLowerAndMultipleException				Result=TemplateFunctionRequirementsNested(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptTemplateOverload1=is_integral_v<TType>;
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptTemplateOverload2=is_floating_point_v<TType>;
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE je OVERLOADED, kde sa lisi iba v REQUIREMENTS.
template<typename TType> requires ConceptTemplateOverload1<TType>
TType TemplateTemplateOverload(TType A, TType B)
{
	wcout << L"FUNCTION TemplateTemplateOverload() with ConceptTemplateOverload1 REUIREMENT is CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE je OVERLOADED, kde sa lisi iba v REQUIREMENTS.
template<typename TType> requires ConceptTemplateOverload2<TType>
TType TemplateTemplateOverload(TType A, TType B)
{
	wcout << L"FUNCTION TemplateTemplateOverload() with ConceptTemplateOverload2 REUIREMENT is CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateOverload(void)
{
	PrintLineSeparator();

	// !!! Vola sa 1. OVERLOADED VERSION.
	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateTemplateOverload(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! Vola sa 2. OVERLOADED VERSION.
	{
		double													Value1=10.1;
		double													Value2=20.2;
		double													Result=TemplateTemplateOverload(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! CODE hodi ERROR, pretoze CLASS 'CClassWithOperatorLowerAndMultiple' nie je INTEGER, ani FLOATING POINT TYPE.
	{
		CClassWithOperatorLowerAndMultiple						Value1=10;
		CClassWithOperatorLowerAndMultiple						Value2=20;
		CClassWithOperatorLowerAndMultiple						Result=TemplateTemplateOverload(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptRequirementSubsumption1=requires(TType A, TType B)
{
	{A<B} noexcept -> convertible_to<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONCEPT 'ConceptRequirementSubsumption2' SUBSUMES CONCEPT 'ConceptRequirementSubsumption1', lebo v CONCEPT 'ConceptRequirementSubsumption2' sa nachadza CONCEPT 'ConceptRequirementSubsumption1' spojeny pomocou OPERATOR&&.
template<typename TType>
concept ConceptRequirementSubsumption2=ConceptRequirementSubsumption1<TType> && is_class_v<TType>;
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE je OVERLOADED, kde sa lisi iba v REQUIREMENTS.
template<typename TType> requires ConceptRequirementSubsumption1<TType>
TType TemplateRequirementSubsumption(TType A, TType B)
{
	wcout << L"FUNCTION TemplateRequirementSubsumption() with ConceptRequirementSubsumption1 REUIREMENT is CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE je OVERLOADED, kde sa lisi iba v REQUIREMENTS.
template<typename TType> requires ConceptRequirementSubsumption2<TType>
TType TemplateRequirementSubsumption(TType A, TType B)
{
	wcout << L"FUNCTION TemplateRequirementSubsumption() with ConceptRequirementSubsumption2 REUIREMENT is CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRequirementSubsumption(void)
{
	PrintLineSeparator();

	// !!!!! Vola sa 1. OVERLOADED VERSION, pretoze TYPE [double] ma OPERATOR<, ale NIE JE CLASS ako to vyzaduje CONCEPT 'ConceptRequirementSubsumption2'.
	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateRequirementSubsumption(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!!!! Vola sa 1. OVERLOADED VERSION, pretoze TYPE [double] ma OPERATOR<, ale NIE JE CLASS ako to vyzaduje CONCEPT 'ConceptRequirementSubsumption2'.
	{
		double													Value1=10.1;
		double													Value2=20.2;
		double													Result=TemplateRequirementSubsumption(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!!!! Vola sa 2. OVERLOADED VERSION, pretoze CLASS 'CClassWithOperatorLowerAndMultiple' ma OPERATOR<, a zaroven je CLASS ako to vyzaduje CONCEPT 'ConceptRequirementSubsumption2'. CONCEPT 'ConceptRequirementSubsumption1' tiez vyhovuje REQUIREMENTS, kedze CLASS 'CClassWithOperatorLowerAndMultiple' ma OPERATOR<, ale kedze CONCEPT 'ConceptRequirementSubsumption2' SUBSUMES CONCEPT 'ConceptRequirementSubsumption1', pouzije sa TEMPLATE, ktora pouziva CONCEPT 'ConceptRequirementSubsumption2'.
	{
		CClassWithOperatorLowerAndMultiple						Value1=10;
		CClassWithOperatorLowerAndMultiple						Value2=20;
		CClassWithOperatorLowerAndMultiple						Result=TemplateRequirementSubsumption(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
concept ConceptTestingConcept=requires(TType A, TType B)
{
	{A<B} -> convertible_to<bool>;
};
//----------------------------------------------------------------------------------------------------------------------
template<typename TType> requires ConceptTestingConcept<TType>
TType TemplateTestingConcept(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTestingConcept(void)
{
	PrintLineSeparator();

	// !!!!! TESTOVANIE CONCEPTS.
	static_assert(ConceptTestingConcept<int>,"TEST 1 FAILED !");
	static_assert(ConceptTestingConcept<CClassWithOperatorLower>,"TEST 2 FAILED !");

	// !!!! TEST ZLYHA, pretoze CLASS 'CDummyClass' NEMA definovany OPERATOR<.
	//static_assert(ConceptTestingConcept<CDummyClass>,"TEST 3 FAILED !");

	{
		int														Value1=10;
		int														Value2=20;
		int														Result=TemplateTestingConcept(Value1,Value2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!!!! COMPILER NEHODI ERROR, pretoze CLASS 'CClassWithOperatorLower' MA definovany OPERATOR<.
	{
		CClassWithOperatorLower									Value1=10;
		CClassWithOperatorLower									Value2=20;
		CClassWithOperatorLower									Result=TemplateTestingConcept(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}

	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze CLASS 'CDummyClass' NEMA definovany OPERATOR<.
	{
		CDummyClass												Value1=10;
		CDummyClass												Value2=20;
		CDummyClass												Result=TemplateTestingConcept(Value1,Value2);

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTemplateFunctionConcept();
	//TestTemplateClassConcept();
	//TestTemplateClassMethodConcept();
	//TestRequirementsPrimaryExpression();
	//TestRequirementsTypeTraits();
	//TestRequirementsConcept();
	//TestMultipleRequirementsAnd();
	//TestMultipleRequirementsOr();
	//TestMultipleTemplateParametersRequirements();
	//TestRequiresClauseAfterTemplateKeyword();
	//TestRequiresClauseAfterFunctionParameters();
	//TestShorthandRequirementNotation1();
	//TestShorthandRequirementNotation2();
	//TestConceptWithMultipleRequirementsAnd();
	//TestConceptWithMultipleRequirementsOr();
	//TestRequirementsSimple();
	//TestRequirementsType();
	//TestRequirementsCompound();
	//TestRequirementsNested();
	//TestTemplateOverload();
	//TestRequirementSubsumption();
	TestTestingConcept();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------