//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include "MyDebug.h"
#include "CString.h"
#include "CLookUpQualifiedNamesBase.h"
#include "CLookUpQualifiedNamesDerived.h"
#include "CLookUpUnQualifiedNamesBase.h"
#include "CLookUpUnQualifiedNamesDerived.h"
#include "CLookUpArgumentDependent1.h"
#include "CLookUpArgumentDependent2.h"
#include "CLookUpArgumentDependentFriend.h"
#include "CInjectedClassNamesClass.h"
#include "CInjectedClassNamesTemplateClass.h"
#include "CInjectedClassNamesVariadicTemplateClass.h"
#include "CCurrentInstantiationClass.h"
#include "CCurrentInstantiationNestedClass.h"
#include "CParsingContextSensitivity1.h"
#include "CParsingContextSensitivity2.h"
#include "CParsingContextSensitivity3.h"
#include "CParsingDependentNamesTypes.h"
#include "CParsingDependentNamesTemplates.h"
#include "CParsingDependentNamesUsingBase.h"
#include "CParsingDependentNamesUsingDerived1.h"
#include "CParsingDependentNamesUsingDerived2.h"
#include "CParsingADL.h"
#include "CParsingDependentExpressions.h"
#include "CNondependentBaseClassesBase.h"
#include "CNondependentBaseClassesDerived1.h"
#include "CNondependentBaseClassesDerived2.h"
#include "CDependentBaseClassesCaseABase.h"
#include "CDependentBaseClassesCaseABaseSpecialization.h"
#include "CDependentBaseClassesCaseADerived.h"
#include "CDependentBaseClassesCaseBBase.h"
#include "CDependentBaseClassesCaseBDerived1.h"
#include "CDependentBaseClassesCaseBDerived2.h"
#include "CDependentBaseClassesCaseCBase.h"
#include "CDependentBaseClassesCaseCDerived.h"
#include "CDependentBaseClassesCaseDBaseNonDependent.h"
#include "CDependentBaseClassesCaseDBaseDependent.h"
#include "CDependentBaseClassesCaseDDerived.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
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
int																LookUpQualifiedNamesVariableGlobalNamespace=100;
//----------------------------------------------------------------------------------------------------------------------
namespace LookUpQualifiedNamesGlobalNamespace
{
//----------------------------------------------------------------------------------------------------------------------
	int															LookUpQualifiedNamesVariableNamedNamespace=100;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
void TestLookUpQualifiedNames(void)
{
	PrintLineSeparator();

	{
		// !!! Robi sa QUALIFIED NAME LOOKUP, pretoze je pouzity OPERATOR [OPERATOR::].
		int														Value=LookUpQualifiedNamesGlobalNamespace::LookUpQualifiedNamesVariableNamedNamespace;

		wcout << L"OPERATOR [OPERATOR::] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Robi sa QUALIFIED NAME LOOKUP, pretoze je pouzity OPERATOR [OPERATOR::].
		int														Value=::LookUpQualifiedNamesVariableGlobalNamespace;

		wcout << L"OPERATOR [OPERATOR::] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CLookUpQualifiedNamesDerived							Object(L"Timmy",L"Jenny");

		// !!! Robi sa QUALIFIED NAME LOOKUP, pretoze je pouzity OPERATOR [OPERATOR.].
		const CString&											Value=Object.GetField();

		wcout << L"OPERATOR [OPERATOR.] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CLookUpQualifiedNamesDerived							Object(L"Timmy",L"Jenny");
		const CLookUpQualifiedNamesDerived*						Pointer=&Object;

		// !!! Robi sa QUALIFIED NAME LOOKUP, pretoze je pouzity OPERATOR [OPERATOR->].
		const CString&											Value=Pointer->GetField();

		wcout << L"OPERATOR [OPERATOR->] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CLookUpQualifiedNamesDerived							Object(L"Timmy",L"Jenny");

		const CString&											ValueBaseField=Object.GetBaseField();
		const CString&											ValueDerivedField=Object.GetDerivedField();

		wcout << L"OPERATOR [OPERATOR::] - VALUE BASE FIELD [" << ValueBaseField << L"]." << endl;
		wcout << L"OPERATOR [OPERATOR::] - VALUE DERIVED FIELD [" << ValueDerivedField << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CString															LookUpUnQualifiedNamesVariable(L"GLOBAL - GLOBAL VARIABLE 1");
CString															LookUpUnQualifiedNamesGlobalVariable(L"GLOBAL - GLOBAL VARIABLE 2");
//----------------------------------------------------------------------------------------------------------------------
void TestFunctionLookUpUnQualifiedNames1(void)
{
	{
		CString													LookUpUnQualifiedNamesVariable(L"LOCAL");

		// !!!!! Pristupuje sa k LOCAL VARIABLE 'LookUpUnQualifiedNamesVariable'.
		wcout << L"IN LOCAL SCOPE - LookUpUnQualifiedNamesVariable [" << LookUpUnQualifiedNamesVariable << L"]." << endl;
	}

	PrintLineSeparator();

	// !!!!! Pristupuje sa ku GLOBAL VARIABLE 'LookUpUnQualifiedNamesVariable'.
	wcout << L"IN METHOD SCOPE - LookUpUnQualifiedNamesVariable [" << LookUpUnQualifiedNamesVariable << L"]." << endl;

	// !!!!! Pristupuje sa ku GLOBAL VARIABLE 'LookUpUnQualifiedNamesGlobalVariable'.
	wcout << L"IN METHOD SCOPE - GlobalVariable [" << LookUpUnQualifiedNamesGlobalVariable << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestFunctionLookUpUnQualifiedNames2(const CString& LookUpUnQualifiedNamesVariable)
{
	{
		CString													LookUpUnQualifiedNamesVariable(L"LOCAL");

		// !!!!! Pristupuje sa k LOCAL VARIABLE 'LookUpUnQualifiedNamesVariable'.
		wcout << L"IN LOCAL SCOPE - LookUpUnQualifiedNamesVariable [" << LookUpUnQualifiedNamesVariable << L"]." << endl;
	}

	PrintLineSeparator();

	// !!!!! Pristupuje sa k FUNCTION PARAMETER 'LookUpUnQualifiedNamesVariable'.
	wcout << L"IN METHOD SCOPE - LookUpUnQualifiedNamesVariable [" << LookUpUnQualifiedNamesVariable << L"]." << endl;

	// !!!!! Pristupuje sa ku GLOBAL VARIABLE 'LookUpUnQualifiedNamesGlobalVariable'.
	wcout << L"IN METHOD SCOPE - GlobalVariable [" << LookUpUnQualifiedNamesGlobalVariable << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestLookUpUnQualifiedNames(void)
{
	PrintLineSeparator();

	{
		TestFunctionLookUpUnQualifiedNames1();
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		TestFunctionLookUpUnQualifiedNames2(L"PARAMETER");
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CLookUpUnQualifiedNamesDerived							Object(L"FIELD - BASE FIELD",L"FIELD - SHARED FIELD BASE",L"FIELD - DERIVED FIELD",L"FIELD - SHARED FIELD DERIVED");

		Object.TestClassMethodLookUpUnQualifiedNames1();
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CLookUpUnQualifiedNamesDerived							Object(L"FIELD - BASE FIELD",L"FIELD - SHARED FIELD BASE",L"FIELD - DERIVED FIELD",L"FIELD - SHARED FIELD DERIVED");

		Object.TestClassMethodLookUpUnQualifiedNames2(L"PARAMETER - BASE FIELD",L"PARAMETER - DERIVED FIELD",L"PARAMETER - SHARED FIELD");
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template <typename TType>
TType TemplateLookUpArgumentDependentMax(TType Value1, TType Value2)
{
	// !!!!! Pouzije sa OPERATOR [OPERATOR<], ktory je definovany v NAMESPACE [LookUpArgumentDependent1Namespace].
	// !!!!! Vdaka ARGUMENT DEPENDENT LOOKUP je OPERATOR [OPERATOR<] viditelny, aj ked je v NAMESPACE [LookUpArgumentDependent1Namespace].
	bool														IsLower=(Value1<Value2);

	if (IsLower==false)
	{
		return(Value1);
	}
	else
	{
		return(Value2);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Vykona sa USING NAMESPACE.
using namespace LookUpArgumentDependent1Namespace;
//----------------------------------------------------------------------------------------------------------------------
void TestLookUpArgumentDependent(void)
{
	PrintLineSeparator();

	{
		CLookUpArgumentDependent1								Object1(100);
		CLookUpArgumentDependent1								Object2(200);

		// !!!!! Vdaka ARGUMENT DEPENDENT LOOKUP je v TEMPLATE [TType TemplateLookUpArgumentDependentMax(TType Value1, TType Value2)] OPERATOR [OPERATOR<] viditelny, aj ked je v NAMESPACE [LookUpArgumentDependent1Namespace].
		CLookUpArgumentDependent1								ObjectMax=TemplateLookUpArgumentDependentMax(Object1,Object2);

		wcout << L"ARGUMENT DEPENDENT LOOKUP 1 - MAX OBJECT [" << ObjectMax.GetField() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Kedze je pouzity SCOPE RESOLUTION OPERATOR [::], je volana FUNCTION [void LookUpArgumentDependent2Function(int Value)] na GLOBAL NAMESPACE SCOPE.
		::LookUpArgumentDependent2Function(CLookUpArgumentDependent2Namespace2::E_VALUE_1);
	}

	PrintLineSeparator();

	{
		// !!!!! C++ LOOKUP vyberie ako vhodneho kandidata GLOBAL FUNCTION [void LookUpArgumentDependent2Function(int Value)]. Nasledne sa vsak aplikuje ARGUMENT DEPENDENT LOOKUP, ktory najde vhodnejsiu FUNCTION [void LookUpArgumentDependent2Function(LookUpArgumentDependent2Enum Value)] v NAMESPACE [CLookUpArgumentDependent2Namespace2].
		// !!!!! ARGUMENT DEPENDENT LOOKUP sa robi preto, lebo ENUM [LookUpArgumentDependent2Enum] sa nachadza v NAMESPACE [CLookUpArgumentDependent2Namespace2] a preto sa LOOKUP robi aj v tomto NAMESPACE.
		LookUpArgumentDependent2Function(CLookUpArgumentDependent2Namespace2::E_VALUE_2);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestLookUpArgumentDependentFriend(void)
{
	PrintLineSeparator();

	{
		// !!!!! COMPILER najde FUNCTION, pretoze FUNCTION je bola DECLARED aj osobitne a NIE iba cez FRIEND DECLARATION.
		LookUpArgumentDependentFriendFunction1();
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze FUNCTION, ktora bola DECLARED IBA cez FRIEND DECLARATION NENAJDE.
		LookUpArgumentDependentFriendFunction2();
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! COMPILER najde FUNCTION, aj ked FUNCTION je DECLARED IBA cez FRIEND DECLARATION. Je to preto, lebo sa aplikuje ARGUMENT DEPENDENT LOOKUP a kedze FUNCTION ma ako PARAMETER TYPE [CLookUpArgumentDependentFriend<TType>], tak COMPILER povazuje danu FUNCTION, ako keby bola DECLARED aj na GLOBAL NAMESPACE SCOPE, a preto ju najde.
		CLookUpArgumentDependentFriend<CString>					Object(L"Timmy");

		LookUpArgumentDependentFriendFunction3(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestInjectedClassNames(void)
{
	PrintLineSeparator();

	{
		// !!! Vdaka CLASS NAME INJECTION METHOD vracia SIZEOF CLASS.
		wcout << L"STATIC METHOD - SIZEOF [" << CInjectedClassNamesClass::GetSizeof() << L"]." << endl;
		
		// !!! Vracia SIZEOF VARIABLE.
		wcout << L"FUNCTION - SIZEOF [" << GetSizeof() << L"]." << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CInjectedClassNamesTemplateClass<CString>				Object;

		Object.PrintInjectedClassNames();
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CInjectedClassNamesVariadicTemplateClass<CString,int,double>	Object;

		Object.PrintInjectedClassNames();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCurrentInstantiationVsUnknownSpecialization(void)
{
	PrintLineSeparator();

	{
		CCurrentInstantiationClass<int>							Field1(L"FIELD 1");
		CCurrentInstantiationClass<int>							Field2(L"FIELD 2");

		// !!! Vytvori sa instancia PARTIAL TEMPLATE SPECIALIZATION.
		CCurrentInstantiationClass<int*>						Field3(L"FIELD 3");
		CCurrentInstantiationClass<int>							Object(L"OBJECT");

		Object.SetFields(&Field1,&Field2,&Field3);

		Object.Print();

		Object.GetField1()->Print();
		Object.GetField2()->Print();
		Object.GetField3()->Print();
	}

	PrintLineSeparator();

	{
		// !!! Pouzije sa PRIMARY TEMPLATE.
		CCurrentInstantiationNestedClassOuter<double>			OuterObject(L"OUTER OBJECT");
		CCurrentInstantiationNestedClassOuter<double>::CCurrentInstantiationNestedClassInner1	InnerObject1(L"INNER OBJECT 1");
		CCurrentInstantiationNestedClassOuter<double>::CCurrentInstantiationNestedClassInner2	InnerObject2(L"INNER OBJECT 2");

		InnerObject1.SetFields(&OuterObject,&OuterObject,&InnerObject1);
		InnerObject2.SetFields(&OuterObject,&OuterObject,&InnerObject2,&InnerObject1);

		OuterObject.Print();

		InnerObject1.GetField1()->Print();
		InnerObject1.GetField2()->Print();
		InnerObject1.GetField3()->Print();

		InnerObject2.GetField1()->Print();
		InnerObject2.GetField2()->Print();
		InnerObject2.GetField3()->Print();
		InnerObject2.GetField4()->Print();
	}


	PrintLineSeparator();

	{
		// !!! Pouzije sa FULL TEMPLATE SPECIALIZATION.
		CCurrentInstantiationNestedClassOuter<int>				OuterObject(L"OUTER OBJECT");
		CCurrentInstantiationNestedClassOuter<int>::CCurrentInstantiationNestedClassInner1	InnerObject1(L"INNER OBJECT 1");
		CCurrentInstantiationNestedClassOuter<int>::CCurrentInstantiationNestedClassInner2	InnerObject2(L"INNER OBJECT 2");

		InnerObject2.SetFields(&OuterObject,&OuterObject,&InnerObject2,&InnerObject1);

		OuterObject.Print();

		InnerObject2.GetField1()->Print();
		InnerObject2.GetField2()->Print();
		InnerObject2.GetField3()->Print();
		InnerObject2.GetField4()->Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int																ParsingContextSensitivityArray[]={1,2,3};
//----------------------------------------------------------------------------------------------------------------------
int																ParsingContextSensitivityIndex=1;
//----------------------------------------------------------------------------------------------------------------------
void TestParsingContextSensitivity(void)
{
	PrintLineSeparator();

	{
		bool													Result=CParsingContextSensitivity1<(1>0)>::RESULT;

		wcout << L"RESULT [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Result=CParsingContextSensitivity1<(0>1)>::RESULT;

		wcout << L"RESULT [" << Result << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!! Bez pouzitia ZATVORIEK [()] COMPILER hodi ERROR.
		bool													Result=CParsingContextSensitivity1<1>0>::RESULT;

		wcout << L"RESULT [" << Result << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!! V C++ 98 CODE vracia VALUE [0].
		int														Result1=(CParsingContextSensitivity2<CParsingContextSensitivity2Inner<1> >::CONSTANT >::CONSTANT>::CONSTANT);
		// !!! V C++ 98 CODE vracia VALUE [3].
		int														Result2=(CParsingContextSensitivity2<CParsingContextSensitivity2Inner< 1>>::CONSTANT >::CONSTANT>::CONSTANT);

		wcout << L"RESULT 1 [" << Result1 << L"]." << endl;
		wcout << L"RESULT 2 [" << Result2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Pred C++ 11 nasledujuci CODE hodi ERROR.
		CParsingContextSensitivity3A<::CParsingContextSensitivity3B>	Object;

		wcout << L"Object.CONSTANT [" << Object.CONSTANT << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		#define	MACRO_TEST(Parameter) Parameter ## :

		// !!! C++ od verzie 11 hodi ERROR.
		int														Value=ParsingContextSensitivityArray MACRO_TEST(<::)ParsingContextSensitivityIndex];
		
		wcout << L"VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestParsingDependentNamesTypes(void)
{
	PrintLineSeparator();

	{
		CParsingDependentNamesTypes2<int>						Object(200);

		Object.Test();
	}

	PrintLineSeparator();

	{
		CParsingDependentNamesTypes2<void>						Object(200);

		Object.Test();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestParsingDependentNamesTemplates(void)
{
	PrintLineSeparator();

	{
		CParsingDependentNamesTemplatesLevelTest<int,100,200>	Object;

		Object.Test1();
	}

	PrintLineSeparator();

	{
		CParsingDependentNamesTemplatesLevelTest<int,100,200>	Object;

		Object.Test2();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestParsingDependentNamesUsing(void)
{
	PrintLineSeparator();

	{
		CParsingDependentNamesUsingDerived1<CString>			Object(L"DERIVED 1");

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CParsingDependentNamesUsingDerived2<CString>::InnerClass<CString>	InnerObject(L"INNER - DERIVED 2");
		CParsingDependentNamesUsingDerived2<CString>			Object(InnerObject);

		wcout << L"VALUE [" << Object.GetValue().GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestParsingADL(void)
{
	PrintLineSeparator();

	using namespace ParsingADL;

	{
		CParsingADL												Value(L"TIMMY");

		ParsingADLTemplateFunction1<100>(Value);
	}

	PrintLineSeparator();

	{
		CParsingADL												Value(L"TIMMY");

		// !!!!! Podla knihy by tento CODE mal sposobit COMPILATION ERROR.
		ParsingADLTemplateFunction2<100>(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestParsingDependentExpressions(void)
{
	PrintLineSeparator();

	{
		DependentExpressionsTypeDependent(CString(L"TYPE DEPENDENT"));
	}

	PrintLineSeparator();

	{
		DependentExpressionsValueDependent1<100>();
	}

	PrintLineSeparator();

	{
		DependentExpressionsValueDependent2(CString(L"TYPE DEPENDENT"));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestInheritanceNonDependentBaseClasses(void)
{
	PrintLineSeparator();

	{
		CNondependentBaseClassesDerived1						Object;

		Object.Test();
	}

	PrintLineSeparator();

	{
		CNondependentBaseClassesDerived2<CString>				Object;

		Object.Test();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestInheritanceDependentBaseClasses(void)
{
	PrintLineSeparator();

	{
		CDependentBaseClassesCaseADerived<int>					Object;

		Object.Test();
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze METHOD [void CDependentBaseClassesCaseADerived<TType>::Test(void)] sa pokusa modifikovat NAME [MBaseField]. Lenze ten je v TEMPLATE SPECIALIZATION [CDependentBaseClassesCaseABase<bool>] definovany ako ENUM, ktoreho VALUES NEMOZU byt MODIFIKOVANE.
	{
		CDependentBaseClassesCaseADerived<bool>					Object;

		Object.Test();
	}
	*/

	PrintLineSeparator();

	{
		CDependentBaseClassesCaseBDerived1<int>					Object;

		Object.Test1();
		Object.Test2();
	}

	PrintLineSeparator();

	{
		CDependentBaseClassesCaseBDerived2<int>					Object;

		Object.Test();
	}

	PrintLineSeparator();

	{
		CDependentBaseClassesCaseCDerived<int>					Object;

		Object.Test();
	}

	PrintLineSeparator();

	{
		CDependentBaseClassesCaseDDerived<double>				Object;
		double													Value=123.456;

		Object.Test(100,&Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestLookUpQualifiedNames();
	//TestLookUpUnQualifiedNames();
	//TestLookUpArgumentDependent();
	//TestLookUpArgumentDependentFriend();
	//TestInjectedClassNames();
	//TestCurrentInstantiationVsUnknownSpecialization();
	//TestParsingContextSensitivity();
	//TestParsingDependentNamesTypes();
	//TestParsingDependentNamesTemplates();
	//TestParsingDependentNamesUsing();
	//TestParsingADL();
	//TestParsingDependentExpressions();
	//TestInheritanceNonDependentBaseClasses();
	TestInheritanceDependentBaseClasses();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------