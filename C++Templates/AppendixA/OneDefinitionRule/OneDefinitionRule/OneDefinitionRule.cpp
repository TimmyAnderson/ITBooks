//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "COneDefinitionRule.h"
#include "CTranslationUnit1.h"
#include "CTranslationUnit2.h"
#include "CNonPolymorphicType.h"
#include "CPolymorphicType.h"
#include "CSingleTranslationUnit.h"
#include "CCrossTranslationUnitEquivalence1.h"
#include "CCrossTranslationUnitEquivalence2.h"
#include "CCrossTranslationUnitEquivalence.h"
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
void TestOneDefinitionRule(void)
{
	PrintLineSeparator();

	SomeFunction();

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestOnePerProgramConstraints(void)
{
	PrintLineSeparator();

	{
		wcout << L"VARIABLE [ExternVariable] - VALUE [" << ExternVariable << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"UNIT 1 - VARIABLE [StaticVariable] - VALUE [" << GetStaticVariable1() << L"] !" << endl;
		wcout << L"UNIT 2 - VARIABLE [StaticVariable] - VALUE [" << GetStaticVariable2() << L"] !" << endl;

		SetStaticVariable1(111);

		wcout << L"UNIT 1 - VARIABLE [StaticVariable] - VALUE [" << GetStaticVariable1() << L"] !" << endl;
		wcout << L"UNIT 2 - VARIABLE [StaticVariable] - VALUE [" << GetStaticVariable2() << L"] !" << endl;

		SetStaticVariable2(222);

		wcout << L"UNIT 1 - VARIABLE [StaticVariable] - VALUE [" << GetStaticVariable1() << L"] !" << endl;
		wcout << L"UNIT 2 - VARIABLE [StaticVariable] - VALUE [" << GetStaticVariable2() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"UNIT 1 - VARIABLE [NamespaceVariable] - VALUE [" << GetNamespaceVariable1() << L"] !" << endl;
		wcout << L"UNIT 2 - VARIABLE [NamespaceVariable] - VALUE [" << GetNamespaceVariable2() << L"] !" << endl;

		SetNamespaceVariable1(111);

		wcout << L"UNIT 1 - VARIABLE [NamespaceVariable] - VALUE [" << GetNamespaceVariable1() << L"] !" << endl;
		wcout << L"UNIT 2 - VARIABLE [NamespaceVariable] - VALUE [" << GetNamespaceVariable2() << L"] !" << endl;

		SetNamespaceVariable2(222);

		wcout << L"UNIT 1 - VARIABLE [NamespaceVariable] - VALUE [" << GetNamespaceVariable1() << L"] !" << endl;
		wcout << L"UNIT 2 - VARIABLE [NamespaceVariable] - VALUE [" << GetNamespaceVariable2() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CallNamespaceFunction1();
		CallNamespaceFunction2();
	}

	PrintLineSeparator();

	{
		extern CNonPolymorphicType								ExternNonPolymorphicType;
		extern CPolymorphicType									ExternPolymorphicType;

		size_t													SizeofNonPolymorphic=sizeof(ExternNonPolymorphicType);

		wcout << L"SIZEOF [SizeofNonPolymorphic] is [" << SizeofNonPolymorphic << L"] !" << endl;

		size_t													SizeofPolymorphic=sizeof(ExternPolymorphicType);

		wcout << L"SIZEOF [SizeofPolymorphic] is [" << SizeofPolymorphic << L"] !" << endl;

		const type_info&										TypeInfoNonPolymorphic=typeid(ExternNonPolymorphicType);

		wcout << L"OBJECT [TypeInfoNonPolymorphic] - TYPE [" << GetTypeInfoName<decltype(TypeInfoNonPolymorphic)>() << L"] !" << endl;

		// !!!!! Podla knihy by tento CODE mal hodit ERROR, ale NEHODI.
		const type_info&										TypeInfoPolymorphic=typeid(ExternPolymorphicType);

		wcout << L"OBJECT [TypeInfoPolymorphic] - TYPE [" << GetTypeInfoName<decltype(TypeInfoPolymorphic)>() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze v jednom TRANSLATION UNIT NESMIE byt dany ELEMENT definovany viackrat.
void SameFunction(void)
{
	wcout << L"FUNCTION 1 [void SameFunction(void)] CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void SameFunction(void)
{
	wcout << L"FUNCTION 2 [void SameFunction(void)] CALLED !" << endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION INLINE FUNCTION.
inline void MyInlineFunction(void);
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION NONINLINE FUNCTION.
void MyNonInlineFunction(void);
//----------------------------------------------------------------------------------------------------------------------
void TestOnePerTranslationUnitConstraints(void)
{
	PrintLineSeparator();

	/*
	{
		SameFunction();
	}

	PrintLineSeparator();
	*/

	{
		// !!! FUNCTIONS je mozne pouzit IBA na zaklade ich DECLARATION, a nie na zaklade ich DEFINITION.

		MyInlineFunction();
		MyNonInlineFunction();
	}

	PrintLineSeparator();

	{
		MyInlineFunctionInTranslationUnit();

		PrintLineSeparator();

		MyNonInlineFunctionInTranslationUnit();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION INLINE FUNCTION.
inline void MyInlineFunction(void)
{
	wcout << L"FUNCTION [inline void MyInlineFunction(void)] CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION NON-INLINE FUNCTION.
void MyNonInlineFunction(void)
{
	wcout << L"FUNCTION [void MyNonInlineFunction(void)] CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
inline void DifferentFunction(void)
{
	wcout << L"UNIT MAIN - FUNCTION [inline void DifferentFunction(void)] CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER hodi ERROR, pretoze FUNCTION je DECLARED vo viacerych TRANSLATION UNITS a v kazdom TRANSLATION UNIT ma iny DEFAULT ARGUMENT.
void FunctionWithDifferentDefaultArguments(int Value=300)
{
	wcout << L"UNIT MAIN - FUNCTION [void FunctionWithDifferentDefaultArguments(int Value=300)] CALLED with VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCrossTranslationUnitEquivalenceConstraints(void)
{
	PrintLineSeparator();

	// !!!!! Tento CODE je UNDEFINED, pretoze FUNCTION [inline void DifferentFunction(void)] je DEFINED vo viacerych TRANSLATION UNITS a v kazdom ma INY CODE.
	// !!!!! COMPILER vsak tento ERROR NEMUSI detekovat, kedze detekcia je zlozita.
	{
		CallDifferentFunctionInUnit1();
		CallDifferentFunctionInUnit2();
		DifferentFunction();
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze FUNCTION je DECLARED vo viacerych TRANSLATION UNITS a v kazdom TRANSLATION UNIT ma iny DEFAULT ARGUMENT.
	{
		FunctionWithDifferentDefaultArguments();
	}
	*/

	PrintLineSeparator();

	{
		// !!! COMPILER NEHODI ERROR, hoci VARIABLE 'LENGTH' je DEFINED vo VIACERYCH TRANSLATION UNITS.
		wcout << L"[SIZEOF(CCrossTranslationUnitEquivalence)] is [" << sizeof(CCrossTranslationUnitEquivalence) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestOneDefinitionRule();
	//TestOnePerProgramConstraints();
	//TestOnePerTranslationUnitConstraints();
	TestCrossTranslationUnitEquivalenceConstraints();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------