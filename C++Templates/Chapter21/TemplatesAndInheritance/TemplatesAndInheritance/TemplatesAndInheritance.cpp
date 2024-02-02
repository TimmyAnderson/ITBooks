//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "CEmptyClass.h"
#include "CEmptyBaseClassOptimization.h"
#include "CEmptyBaseClassOptimizationMember1.h"
#include "CEmptyBaseClassOptimizationMember2.h"
#include "CCRTPObjectCounterBase.h"
#include "CCRTPObjectCounterDerived.h"
#include "CRestrictedTemplateExpansion.h"
#include "CCRTPAndRestrictedTemplateExpansionBase.h"
#include "CCRTPAndRestrictedTemplateExpansionDerived.h"
#include "CNonFriendFunctionClass.h"
#include "CCRTPFacadePatternBase.h"
#include "CCRTPFacadePatternDerived.h"
#include "CCRTPFacadePatternHiddenInterfaceInterface.h"
#include "CCRTPFacadePatternHiddenInterfaceBase.h"
#include "CCRTPFacadePatternHiddenInterfaceDerived.h"
#include "CCRTPFacadePatternAdapterInterface.h"
#include "CCRTPFacadePatternAdapterBase.h"
#include "CCRTPFacadePatternAdapterDerived.h"
#include "CMixinClassMixins.h"
#include "CMixinClassMixinsAdditionalData1.h"
#include "CMixinClassMixinsAdditionalData2.h"
#include "CMixinClassMixinsWithCRTP.h"
#include "CMixinClassMixinsWithCRTPAdditionalData1.h"
#include "CMixinClassMixinsWithCRTPAdditionalData2.h"
#include "CMixinVirtualityClassVirtual.h"
#include "CMixinVirtualityClassNonVirtual.h"
#include "CMixinVirtualityMixinBase.h"
#include "CMixinVirtualityMixinDerived.h"
#include "CTemplateClassInheritanceBase.h"
#include "CTemplateClassInheritanceDerived.h"
#include "CNamedTemplateArgumentsTest.h"
#include "CNamedTemplateArgumentsUsePolicies.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestEmptyClass(void)
{
	PrintLineSeparator();

	wcout << L"TYPE [" << GetTypeInfoName<CEmptyClass>() << L"] SIZEOF [" << sizeof(CEmptyClass) << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestEmptyBaseClassOptimization(void)
{
	PrintLineSeparator();

	{
		using													Type=CEmptyBaseClassOptimizationEmpty1;

		wcout << L"TYPE [" << GetTypeInfoName<Type>() << L"] SIZEOF [" << sizeof(Type) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CEmptyBaseClassOptimizationEmpty2;

		wcout << L"TYPE [" << GetTypeInfoName<Type>() << L"] SIZEOF [" << sizeof(Type) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CEmptyBaseClassOptimizationEmpty3;

		wcout << L"TYPE [" << GetTypeInfoName<Type>() << L"] SIZEOF [" << sizeof(Type) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CEmptyBaseClassOptimizationEmpty4;

		wcout << L"TYPE [" << GetTypeInfoName<Type>() << L"] SIZEOF [" << sizeof(Type) << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestEmptyBaseClassOptimizationForMembers(void)
{
	PrintLineSeparator();

	{
		using													Type=CEmptyBaseClassOptimizationMember1Empty;

		wcout << L"TYPE [" << GetTypeInfoName<Type>() << L"] SIZEOF [" << sizeof(Type) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CEmptyBaseClassOptimizationMember1NonTemplate;

		// !!!!! EMPTY BASE CLASS OPTIMIZATION sa na FIELDS NEAPLIKUJE.
		wcout << L"TYPE [" << GetTypeInfoName<Type>() << L"] SIZEOF [" << sizeof(Type) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CEmptyBaseClassOptimizationMember1Template<CEmptyBaseClassOptimizationMember1Empty>;

		// !!!!! EMPTY BASE CLASS OPTIMIZATION sa na FIELDS NEAPLIKUJE.
		wcout << L"TYPE [" << GetTypeInfoName<Type>() << L"] SIZEOF [" << sizeof(Type) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CEmptyBaseClassOptimizationMember2<CEmptyBaseClassOptimizationMember2Empty,CEmptyBaseClassOptimizationMember2Empty>;

		// !!!!! EMPTY BASE CLASS OPTIMIZATION sa sa APLIKUJE, aj ked CLASS ma FIELDS.
		// !!!!! VC++ ho aplikuje, ale GCC nie.
		wcout << L"TYPE [" << GetTypeInfoName<Type>() << L"] SIZEOF [" << sizeof(Type) << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCuriouslyRecurringTemplatePattern(void)
{
	PrintLineSeparator();

	{
		size_t													NumberOfObject1=CCRTPObjectCounterDerived<int>::GetCounter();
		size_t													NumberOfObject2=CCRTPObjectCounterDerived<double>::GetCounter();

		wcout << L"TYPE [" << GetTypeInfoName<CCRTPObjectCounterDerived<int>>() << L"] NUMBER OF OBJECTS [" << NumberOfObject1 << L"]." << endl;
		wcout << L"TYPE [" << GetTypeInfoName<CCRTPObjectCounterDerived<double>>() << L"] NUMBER OF OBJECTS [" << NumberOfObject2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CCRTPObjectCounterDerived<int>							ObjectA1(100);
		CCRTPObjectCounterDerived<int>							ObjectA2(200);
		CCRTPObjectCounterDerived<int>							ObjectA3(300);

		CCRTPObjectCounterDerived<double>						ObjectB1(111.111);
		CCRTPObjectCounterDerived<double>						ObjectB2(222.222);
		CCRTPObjectCounterDerived<double>						ObjectB3(333.333);
		CCRTPObjectCounterDerived<double>						ObjectB4(444.444);

		size_t													NumberOfObject1=CCRTPObjectCounterDerived<int>::GetCounter();
		size_t													NumberOfObject2=CCRTPObjectCounterDerived<double>::GetCounter();

		wcout << L"TYPE [" << GetTypeInfoName<CCRTPObjectCounterDerived<int>>() << L"] NUMBER OF OBJECTS [" << NumberOfObject1 << L"]." << endl;
		wcout << L"TYPE [" << GetTypeInfoName<CCRTPObjectCounterDerived<double>>() << L"] NUMBER OF OBJECTS [" << NumberOfObject2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		size_t													NumberOfObject1=CCRTPObjectCounterDerived<int>::GetCounter();
		size_t													NumberOfObject2=CCRTPObjectCounterDerived<double>::GetCounter();

		wcout << L"TYPE [" << GetTypeInfoName<CCRTPObjectCounterDerived<int>>() << L"] NUMBER OF OBJECTS [" << NumberOfObject1 << L"]." << endl;
		wcout << L"TYPE [" << GetTypeInfoName<CCRTPObjectCounterDerived<double>>() << L"] NUMBER OF OBJECTS [" << NumberOfObject2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestRestrictedTemplateExpansion(void)
{
	PrintLineSeparator();

	{
		CNonFriendFunctionClass									InnerObject(L"Timmy");
		CRestrictedTemplateExpansion<CNonFriendFunctionClass>	Object(InnerObject);

		// !!!!! Vola sa FRIEND FUNCTION.
		// !!!!! C++ najde FRIEND FUNCTION DEFINED v CLASS [CRestrictedTemplateExpansion<CNonFriendFunctionClass>].
		// !!!!! C++ pri hladani FRIEND FUNCTIONS aplikuje ARGUMENT DEPENDENT LOOKUP. ARGUMENT DEPENDENT LOOKUP berie vsetky FUNCTION PARAMETER TYPES a v ich SCOPES hlada ci sa dana FRIEND FUNCTION nachadza.
		// !!!!! FRIEND FUNCTION [friend void RestrictedTemplateExpansionFriendFunction(const CRestrictedTemplateExpansion<TType>& Value)] ma PARAMETER TYPE [CRestrictedTemplateExpansion<TType>]. C++ aplikovanim ARGUMENT DEPENDENT LOOKUP sa pozrie do CLASS [CRestrictedTemplateExpansion<TType>] ci ona neobsahuje FRIEND FUNCTION s NAME [RestrictedTemplateExpansionFriendFunction]. Kedze CLASS [CRestrictedTemplateExpansion<TType>] takuto FRIEND FUNCTION OBSAHUJE, tak C++ najde FRIEND FUNCTION a zavola ju.
		RestrictedTemplateExpansionFriendFunction(Object);

		// !!!!! COMPILER hodi ERROR, predoze NENAJDE FRIEND FUNCTION s NAME [RestrictedTemplateExpansionFriendFunction].
		// !!!!! Pri hladani FRIEND FUNCTION s NAME [RestrictedTemplateExpansionFriendFunction] C++ aplikuje ARGUMENT DEPENDENT LOOKUP. C++ zoberie vsetky FUNCTION PARAMETERS FUNCTION s NAME [RestrictedTemplateExpansionFriendFunction] a ich TYPES hlada FRIEND FUNCTION s NAME [RestrictedTemplateExpansionFriendFunction].
		// !!!!! Kedze FRIEND FUNCTION s NAME [RestrictedTemplateExpansionFriendFunction] ma ARGUMENT TYPE [CNonFriendFunctionClass], tak C++ v CLASS [CNonFriendFunctionClass] hlada ci sa tam nenechadza FRIEND FUNCTION s NAME [RestrictedTemplateExpansionFriendFunction]. Kedze taka FUNCTION sa tam NENACHADZA, tak COMPILER hodi ERROR, kedze nedokazal najst FRIEND FUNCTION s NAME [RestrictedTemplateExpansionFriendFunction].
		// !!!!! Keby sa vsak ODKOMENTOVALA FRIEND FUNCTION [friend void RestrictedTemplateExpansionFriendFunction(const CNonFriendFunctionClass& Value)] v CLASS [CNonFriendFunctionClass], tak COMPILER pomocou ARGUMENT DEPENDENT LOOKUP najde FRIEND FUNCTION s NAME [RestrictedTemplateExpansionFriendFunction] v CLASS [CNonFriendFunctionClass] a COMPILER NEHODI ERROR, ale FRIEND FUNCTION zavola.
		//RestrictedTemplateExpansionFriendFunction(InnerObject);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCuriouslyRecurringTemplatePatternAndRestrictedTemplateExpansion(void)
{
	PrintLineSeparator();

	{
		// !!!!! CLASS [CCRTPAndRestrictedTemplateExpansionDerived] FRIEND OPERATOR [OPERATOR==] a PARENT CLASS [CCRTPAndRestrictedTemplateExpansionBase<TDerivedObject>] definovanim FRIEND OPERATOR [OPERATOR!=] aplikuju RESTRICTED TEMPLATE EXPANSION PATTERN.
		CCRTPAndRestrictedTemplateExpansionDerived				Value1(100);
		CCRTPAndRestrictedTemplateExpansionDerived				Value2(100);

		// !!!!! Vola sa FRIEND OPERATOR [OPERATOR==] DEFINED v CLASS [CCRTPAndRestrictedTemplateExpansionDerived], ktory je vdaka ARGUMENT DEPENDENT LOOKUP viditelny aj na NAMESPACE SCOPE.
		bool													ResultEqual=(Value1==Value2);

		// !!!!! Vola sa FRIEND OPERATOR [OPERATOR!=] DEFINED v CLASS [CCRTPAndRestrictedTemplateExpansionBase<TDerivedObject>], ktory je vdaka ARGUMENT DEPENDENT LOOKUP viditelny aj na NAMESPACE SCOPE.
		bool													ResultNotEqual=(Value1!=Value2);

		wcout << L"VALUE 1 [" << Value1.GetValue() << L"] VALUE 2 [" << Value2.GetValue() << L"] EQUAL [" << ResultEqual << L"]." << endl;
		wcout << L"VALUE 1 [" << Value1.GetValue() << L"] VALUE 2 [" << Value2.GetValue() << L"] NOT EQUAL [" << ResultNotEqual << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CCRTPAndRestrictedTemplateExpansionDerived				Value1(100);
		CCRTPAndRestrictedTemplateExpansionDerived				Value2(200);

		// !!!!! Vola sa FRIEND OPERATOR [OPERATOR==] DEFINED v CLASS [CCRTPAndRestrictedTemplateExpansionDerived], ktory je vdaka ARGUMENT DEPENDENT LOOKUP viditelny aj na NAMESPACE SCOPE.
		bool													ResultEqual=(Value1==Value2);

		// !!!!! Vola sa FRIEND OPERATOR [OPERATOR!=] DEFINED v CLASS [CCRTPAndRestrictedTemplateExpansionBase<TDerivedObject>], ktory je vdaka ARGUMENT DEPENDENT LOOKUP viditelny aj na NAMESPACE SCOPE.
		bool													ResultNotEqual=(Value1!=Value2);

		wcout << L"VALUE 1 [" << Value1.GetValue() << L"] VALUE 2 [" << Value2.GetValue() << L"] EQUAL [" << ResultEqual << L"]." << endl;
		wcout << L"VALUE 1 [" << Value1.GetValue() << L"] VALUE 2 [" << Value2.GetValue() << L"] NOT EQUAL [" << ResultNotEqual << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCuriouslyRecurringTemplatePatternAndFacadePattern(void)
{
	PrintLineSeparator();

	{
		CCRTPFacadePatternDerived								Object(L"CONST OBJECT",L"VALUE 1");
		const CCRTPFacadePatternDerived&						Reference=Object;

		Reference.PrintConst();
	}

	PrintLineSeparator();

	{
		CCRTPFacadePatternDerived								Object(L"NON-CONST OBJECT",L"VALUE 2");
		CCRTPFacadePatternDerived&								Reference=Object;

		Reference.PrintNonConst();
	}

	PrintLineSeparator();

	{
		CCRTPFacadePatternHiddenInterfaceDerived				Object(L"HIDDEN INTERFACE OBJECT",L"Some VALUE !!!");
		const CCRTPFacadePatternHiddenInterfaceDerived&			Reference=Object;

		Reference.Print();
	}

	PrintLineSeparator();

	{
		CCRTPFacadePatternAdapterDerived						Object(L"ADAPTER OBJECT",L"STRING VALUE",100);
		const CCRTPFacadePatternAdapterDerived&					Reference=Object;

		Reference.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestMixins(void)
{
	PrintLineSeparator();

	{
		CMixinClassMixins<CMixinClassMixinsAdditionalData1>		Object;

		Object.SetValueInt(100);
		Object.SetValueString1(L"Timmy");
		Object.SetValueString2(L"Anderson");

		wcout << L"MIXINS - VALUE INT [" << Object.GetValueInt() << L"] VALUE STRING 1 [" << Object.GetValueString1() << L"] VALUE STRING 2 [" << Object.GetValueString2() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CMixinClassMixins<CMixinClassMixinsAdditionalData1,CMixinClassMixinsAdditionalData2>	Object;

		Object.SetValueInt(100);
		Object.SetValueString1(L"Timmy");
		Object.SetValueString2(L"Anderson");
		Object.SetValueDouble(123.456);

		wcout << L"MIXINS - VALUE INT [" << Object.GetValueInt() << L"] VALUE STRING 1 [" << Object.GetValueString1() << L"] VALUE STRING 2 [" << Object.GetValueString2() << L"] VALUE DOUBLE [" << Object.GetValueDouble() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestMixinsWithCRTP(void)
{
	PrintLineSeparator();

	{
		CMixinClassMixinsWithCRTP<CMixinClassMixinsWithCRTPAdditionalData1>		Object;

		Object.SetValueInt(100);
		Object.SetValueString1(L"Timmy");
		Object.SetValueString2(L"Anderson");

		wcout << L"MIXINS WITH CRTP - VALUE INT [" << Object.GetValueInt() << L"] VALUE STRING 1 [" << Object.GetValueString1() << L"] VALUE STRING 2 [" << Object.GetValueString2() << L"]." << endl;
		wcout << L"MIXINS WITH CRTP - VALUE INT VIA CRTP [" << Object.GetValueFromMixinViaCRTPData1() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CMixinClassMixinsWithCRTP<CMixinClassMixinsWithCRTPAdditionalData1,CMixinClassMixinsWithCRTPAdditionalData2>	Object;

		Object.SetValueInt(100);
		Object.SetValueString1(L"Timmy");
		Object.SetValueString2(L"Anderson");
		Object.SetValueDouble(123.456);

		wcout << L"MIXINS WITH CRTP - VALUE INT [" << Object.GetValueInt() << L"] VALUE STRING 1 [" << Object.GetValueString1() << L"] VALUE STRING 2 [" << Object.GetValueString2() << L"] VALUE DOUBLE [" << Object.GetValueDouble() << L"]." << endl;
		wcout << L"MIXINS WITH CRTP - VALUE INT VIA CRTP - DATA 1 [" << Object.GetValueFromMixinViaCRTPData1() << L"]." << endl;
		wcout << L"MIXINS WITH CRTP - VALUE INT VIA CRTP - DATA 2 [" << Object.GetValueFromMixinViaCRTPData2() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestMixinsVirtuality(void)
{
	PrintLineSeparator();

	{
		CMixinVirtualityMixinDerived<CMixinVirtualityClassVirtual>	Object;
		CMixinVirtualityMixinBase<CMixinVirtualityClassVirtual>&	Reference=Object;

		// !!!!! METHOD je volana ako VIRTUAL, pretoze v CLASS [CMixinVirtualityClassVirtual] je oznacena pomocou KEYWORD [virtual].
		Reference.SomeVirtualMethod();
	}

	PrintLineSeparator();

	{
		CMixinVirtualityMixinDerived<CMixinVirtualityClassNonVirtual>	Object;
		CMixinVirtualityMixinBase<CMixinVirtualityClassNonVirtual>&	Reference=Object;

		// !!!!! METHOD je volana ako NON-VIRTUAL, pretoze v CLASS [CMixinVirtualityClassNonVirtual] NIE JE DEFINED a ani v CLASS [CMixinVirtualityMixinBase<>] ani v CLASS [CMixinVirtualityMixinDerived<>] nie je oznacena pomocou KEYWORD [virtual]
		Reference.SomeVirtualMethod();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassInheritance(void)
{
	PrintLineSeparator();

	{
		CTemplateClassInheritanceDerived						Object;

		Object.DoSomething();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestNamedTemplateArguments(void)
{
	PrintLineSeparator();

	{
		CNamedTemplateArgumentsTest<>							Object;

		Object.Print1();
		Object.Print2();
		Object.Print3();
		Object.Print4();
	}

	PrintLineSeparator();

	{
		// !!! Zmeni sa POLICY 3 a POLICY 4.
		CNamedTemplateArgumentsTest<CNamedTemplateArgumentsUsePolicy4<CNamedTemplateArgumentsPolicyCustom1>,CNamedTemplateArgumentsUsePolicy3<CNamedTemplateArgumentsPolicyCustom2>>	Object;

		Object.Print1();
		Object.Print2();
		Object.Print3();
		Object.Print4();
	}

	PrintLineSeparator();

	{
		// !!! Zmeni sa POLICY 1, POLICY 2, POLICY 3 a POLICY 4.
		CNamedTemplateArgumentsTest<CNamedTemplateArgumentsUsePolicy1<CNamedTemplateArgumentsPolicyCustom1>,CNamedTemplateArgumentsUsePolicy2<CNamedTemplateArgumentsPolicyCustom2>,CNamedTemplateArgumentsUsePolicy3<CNamedTemplateArgumentsPolicyCustom3>,CNamedTemplateArgumentsUsePolicy4<CNamedTemplateArgumentsPolicyCustom4>>	Object;

		Object.Print1();
		Object.Print2();
		Object.Print3();
		Object.Print4();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestEmptyClass();
	//TestEmptyBaseClassOptimization();
	//TestEmptyBaseClassOptimizationForMembers();
	//TestCuriouslyRecurringTemplatePattern();
	//TestRestrictedTemplateExpansion();
	//TestCuriouslyRecurringTemplatePatternAndRestrictedTemplateExpansion();
	//TestCuriouslyRecurringTemplatePatternAndFacadePattern();
	//TestMixins();
	//TestMixinsWithCRTP();
	//TestMixinsVirtuality();
	//TestTemplateClassInheritance();
	TestNamedTemplateArguments();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------