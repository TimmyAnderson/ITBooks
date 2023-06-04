//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <deque>
#include "MyDebug.h"
#include "CException.h"
#include "CStack.h"
#include "CValue.h"
#include "CNonMemberOperator1.h"
#include "CNonMemberOperator2.h"
#include "CNonMemberOperator3.h"
#include "CTemplateSpecialization.h"
#include "CPartialTemplateSpecialization1.h"
#include "CPartialTemplateSpecialization2.h"
#include "CDefaultTemplateParameters.h"
#include "CMemberTypesAliases.h"
#include "CTemplateArgumentsDeduction.h"
#include "CTemplateArgumentsDeductionByValue.h"
#include "CTemplateArgumentsDeductionByReference.h"
#include "CTemplateDeductionGuides.h"
#include "SAggregrateTemplateStructure.h"
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
void TestStack1(void)
{
	PrintLineSeparator();

	CStack<wstring>												Stack;

	Stack.Push(L"Timmy");
	Stack.Push(L"Atreyu");
	Stack.Push(L"Jenny");

	wcout << L"NAME [" << Stack.Top() << L"] !" << endl;

	Stack.Pop();

	wcout << L"NAME [" << Stack.Top() << L"] !" << endl;

	Stack.Pop();

	wcout << L"NAME [" << Stack.Top() << L"] !" << endl;

	Stack.Pop();

	wcout << L"IS EMPTY [" << Stack.IsEmpty() << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestStack2(void)
{
	PrintLineSeparator();

	CStack<wstring>												Stack1;

	Stack1.Push(L"Timmy");
	Stack1.Push(L"Atreyu");
	Stack1.Push(L"Jenny");

	CStack<wstring>												Stack2;

	Stack2=Stack1;

	wcout << L"NAME [" << Stack2.Top() << L"] !" << endl;

	Stack2.Pop();

	wcout << L"NAME [" << Stack2.Top() << L"] !" << endl;

	Stack2.Pop();

	wcout << L"NAME [" << Stack2.Top() << L"] !" << endl;

	Stack2.Pop();

	wcout << L"IS EMPTY [" << Stack2.IsEmpty() << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestStack3(void)
{
	PrintLineSeparator();

	CStack<wstring>												Stack1;

	Stack1.Push(L"Timmy");
	Stack1.Push(L"Atreyu");
	Stack1.Push(L"Jenny");

	CStack<wstring>												Stack2;

	Stack2=move(Stack1);

	wcout << L"NAME [" << Stack2.Top() << L"] !" << endl;

	Stack2.Pop();

	wcout << L"NAME [" << Stack2.Top() << L"] !" << endl;

	Stack2.Pop();

	wcout << L"NAME [" << Stack2.Top() << L"] !" << endl;

	Stack2.Pop();

	wcout << L"IS EMPTY [" << Stack2.IsEmpty() << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPartialUsage(void)
{
	PrintLineSeparator();

	CValue<int>													ValueInt(10);

	wcout << L"VALUE INT [" << ValueInt.Get() << L"] !" << endl;

	ValueInt.Add(8);

	wcout << L"VALUE INT [" << ValueInt.Get() << L"] !" << endl;

	ValueInt.Subtract(5);

	wcout << L"VALUE INT [" << ValueInt.Get() << L"] !" << endl;

	PrintLineSeparator();

	CValue<wstring>												ValueWString(L"Timmy");

	wcout << L"VALUE WSTRING [" << ValueWString.Get() << L"] !" << endl;

	ValueWString.Add(L"Anderson");

	wcout << L"VALUE WSTRING [" << ValueWString.Get() << L"] !" << endl;

	/*
	// !!!!! COMPILER hodi ERROR, pretoze OPERATOR- NIE je pre TYPE [wstring] definovany.
	ValueWString.Subtract(L"Anderson");

	wcout << L"VALUE WSTRING [" << ValueWString.Get() << L"] !" << endl;
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestNonMemberOperators(void)
{
	PrintLineSeparator();

	{
		CNonMemberOperator1										Value(100);

		wcout << L"NON MEMBER OPERATOR 1 [" << Value << L"] !" << endl;
	}

	{
		CNonMemberOperator2										Value(100);

		wcout << L"NON MEMBER OPERATOR 2 [" << Value << L"] !" << endl;
	}

	{
		CNonMemberOperator3										Value(100);

		wcout << L"NON MEMBER OPERATOR 3 [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateSpecialization(void)
{
	PrintLineSeparator();

	{
		CTemplateSpecialization<int>							Value;

		Value.Set(100);

		wstringstream											Stream;

		Stream << L"VALUE [" << Value.Get() << L"] !" << endl;

		wcout << Stream.str();
	}

	PrintLineSeparator();

	{
		CTemplateSpecialization<wstring>						Value;

		Value.Set(L"Timmy Anderson");

		wstringstream											Stream1;

		Stream1 << L"VALUE [" << Value.Get() << L"] !" << endl;

		wcout << Stream1.str();

		wstringstream											Stream2;

		Stream2 << L"VALUE LENGTH [" << Value.GetLength() << L"] !" << endl;

		wcout << Stream2.str();
	}

	PrintLineSeparator();

	{
		CTemplateSpecialization<double>							Value;

		Value.Set(100.123);

		wstringstream											Stream;

		Stream << L"VALUE [" << Value.Get() << L"] !" << endl;

		wcout << Stream.str();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPartialTemplateSpecialization1(void)
{
	PrintLineSeparator();

	{
		CPartialTemplateSpecialization1<int>					Value;

		Value.Set(100);

		wstringstream											Stream;

		Stream << L"VALUE [" << Value.Get() << L"] !" << endl;

		wcout << Stream.str();
	}

	PrintLineSeparator();

	{
		CPartialTemplateSpecialization1<int*>					Value;

		int														IntValue=100;

		Value.Set(&IntValue);

		wstringstream											Stream;

		Stream << L"VALUE [" << Value.Get() << L"] !" << endl;
		Stream << L"DEREFERENCED VALUE [" << *(Value.Get()) << L"] !" << endl;

		wcout << Stream.str();
	}


	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPartialTemplateSpecialization2(void)
{
	PrintLineSeparator();

	{
		CPartialTemplateSpecialization2<wstring,int>			Value;

		Value.Set1(L"Timmy Anderson");
		Value.Set2(12);

		wstringstream											Stream;

		Stream << L"VALUE 1 [" << Value.Get1() << L"] !" << endl;
		Stream << L"VALUE 2 [" << Value.Get2() << L"] !" << endl;

		wcout << Stream.str();
	}

	PrintLineSeparator();

	{
		CPartialTemplateSpecialization2<wstring*,int*>			Value;

		wstring													WStringValue=L"Timmy Anderson";
		int														IntValue=12;

		Value.Set1(&WStringValue);
		Value.Set2(&IntValue);

		wstringstream											Stream;

		Stream << L"VALUE 1 [" << Value.Get1() << L"] !" << endl;
		Stream << L"VALUE 2 [" << Value.Get2() << L"] !" << endl;
		Stream << L"DEREFERENCED VALUE 1 [" << *(Value.Get1()) << L"] !" << endl;
		Stream << L"DEREFERENCED VALUE 2 [" << *(Value.Get2()) << L"] !" << endl;

		wcout << Stream.str();
	}

	PrintLineSeparator();

	{
		CPartialTemplateSpecialization2<wstring,double>			Value;

		Value.Set1(L"Timmy Anderson");
		Value.Set2(12.268);

		wstringstream											Stream;

		Stream << L"VALUE 1 [" << Value.Get1() << L"] !" << endl;
		Stream << L"VALUE 2 [" << Value.Get2() << L"] !" << endl;

		wcout << Stream.str();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDefaultTemplateParameters(void)
{
	PrintLineSeparator();

	{
		// !!! Pouzije sa DEFAULT TEMPLATE ARGUMENT pre 2. TEMPLATE PARAMETER.
		CDefaultTemplateParameters<wstring>						Collection;

		Collection.Push(L"Timmy");
		Collection.Push(L"Atreyu");
		Collection.Push(L"Jenny");

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"IS EMPTY [" << Collection.IsEmpty() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! EXPLICITNE sa definuju TEMPLATE ARGUMENTS sa oba TEMPLATE PARAMETERS.
		CDefaultTemplateParameters<wstring,deque<wstring>>		Collection;

		Collection.Push(L"Timmy");
		Collection.Push(L"Atreyu");
		Collection.Push(L"Jenny");

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"IS EMPTY [" << Collection.IsEmpty() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE ALIASES mozu byt definovane IBA v GLOBAL SCOPE, alebo NAMESPACE SCOPE.
template<typename TType>
using CMyTemplateAlias=CStack<TType*>;
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassAliases(void)
{
	PrintLineSeparator();

	// !!! ALIAS sa definuje pomocou KEYWORD [typedef].
	typedef CStack<wstring>										CMyAlias1;

	// !!! ALIAS sa definuje pomocou KEYWORD [using].
	using CMyAlias2=CStack<wstring>;

	// !!! ALIAS sa definuje pomocou KEYWORD [using].

	{
		CMyAlias1												Collection;

		Collection.Push(L"Timmy");
		Collection.Push(L"Atreyu");
		Collection.Push(L"Jenny");

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"IS EMPTY [" << Collection.IsEmpty() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CMyAlias2												Collection;

		Collection.Push(L"Timmy");
		Collection.Push(L"Atreyu");
		Collection.Push(L"Jenny");

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << Collection.Top() << L"] !" << endl;

		Collection.Pop();

		wcout << L"IS EMPTY [" << Collection.IsEmpty() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CMyTemplateAlias<wstring>								Collection;
		wstring													Value1=L"Timmy";
		wstring													Value2=L"Atreyu";
		wstring													Value3=L"Jenny";

		Collection.Push(&Value1);
		Collection.Push(&Value2);
		Collection.Push(&Value3);

		wcout << L"NAME [" << *(Collection.Top()) << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << *(Collection.Top()) << L"] !" << endl;

		Collection.Pop();

		wcout << L"NAME [" << *(Collection.Top()) << L"] !" << endl;

		Collection.Pop();

		wcout << L"IS EMPTY [" << Collection.IsEmpty() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassMemberAliases(void)
{
	PrintLineSeparator();

	CMemberTypesAliases<wstring>								Collection;

	Collection.Push(L"Timmy");
	Collection.Push(L"Atreyu");
	Collection.Push(L"Jenny");

	Collection.Print1();

	PrintLineSeparator();

	Collection.Print2();

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentsDeduction(void)
{
	PrintLineSeparator();

	CTemplateArgumentsDeduction<wstring,int>					Template1(L"Timmy",12);

	wcout << L"TEMPLATE 1 - VALUE 1 [" << Template1.Get1() << L"] VALUE 2 [" << Template1.Get2() << L"] !" << endl;

	// !!! Pouzije sa DEDUCTION TEMPLATE ARGUMENTS.
	CTemplateArgumentsDeduction									Template2=Template1;

	wcout << L"TEMPLATE 2 - VALUE 1 [" << Template2.Get1() << L"] VALUE 2 [" << Template2.Get2() << L"] !" << endl;

	// !!! Pouzije sa DEDUCTION TEMPLATE ARGUMENTS.
	CTemplateArgumentsDeduction									Template3(100,222.222);

	wcout << L"TEMPLATE 3 - VALUE 1 [" << Template3.Get1() << L"] VALUE 2 [" << Template3.Get2() << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateArgumentsDeductionByValueVsByReference(void)
{
	PrintLineSeparator();

	{
		// !!!!! DEDUCED TYPE je TYPE [CTemplateArgumentsDeductionByValue<const wchar_t*,int>].
		CTemplateArgumentsDeductionByValue						Template(L"Timmy",12);

		wcout << L"TEMPLATE - VALUE 1 [" << Template.Get1() << L"] VALUE 2 [" << Template.Get2() << L"] !" << endl;
		wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName(typeid(Template)) << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCED TYPE je TYPE [CTemplateArgumentsDeductionByReference<wchar_t[6],int>].
		CTemplateArgumentsDeductionByReference					Template(L"Timmy",12);

		wcout << L"TEMPLATE - VALUE 1 [" << Template.Get1() << L"] VALUE 2 [" << Template.Get2() << L"] !" << endl;
		wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName(typeid(Template)) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateDeductionGuides(void)
{
	PrintLineSeparator();

	{
		// !!!!! NEAPLIKUJE sa USER DEFINED DEDUCTION GUIDE.
		// !!!!! DEDUCED TYPE je TYPE [CTemplateDeductionGuides<char const*,char const*>].
		CTemplateDeductionGuides								Template("Timmy","Anderson");

		wcout << L"TEMPLATE - VALUE 1 [" << ConvertStringToWideString(Template.Get1()) << L"] VALUE 2 [" << ConvertStringToWideString(Template.Get2()) << L"] !" << endl;
		wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName(typeid(Template)) << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Aplikuje sa USER DEFINED DEDUCTION GUIDE.
		// !!!!! DEDUCED TYPE je TYPE [CTemplateDeductionGuides<wstring,wstring>].
		CTemplateDeductionGuides								Template(L"Timmy",L"Anderson");

		wcout << L"TEMPLATE - VALUE 1 [" << Template.Get1() << L"] VALUE 2 [" << Template.Get2() << L"] !" << endl;
		wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName(typeid(Template)) << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Aplikuje sa USER DEFINED DEDUCTION GUIDE.
		// !!!!! DEDUCED TYPE je TYPE [CTemplateDeductionGuides<wstring,int>].
		CTemplateDeductionGuides								Template(L"Timmy",12);

		wcout << L"TEMPLATE - VALUE 1 [" << Template.Get1() << L"] VALUE 2 [" << Template.Get2() << L"] !" << endl;
		wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName(typeid(Template)) << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Aplikuje sa USER DEFINED DEDUCTION GUIDE.
		// !!!!! DEDUCED TYPE je TYPE [CTemplateDeductionGuides<wstring,int>].
		CTemplateDeductionGuides<wstring,int>					Template(L"Timmy",12);

		wcout << L"TEMPLATE - VALUE 1 [" << Template.Get1() << L"] VALUE 2 [" << Template.Get2() << L"] !" << endl;
		wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName(typeid(Template)) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestAggregrateTemplateStructure(void)
{
	PrintLineSeparator();

	{
		SAggregrateTemplateStructure<int>						Template={12,L"Timmy"};

		wcout << L"TEMPLATE - VALUE [" << Template.MValue << L"] TEXT [" << Template.MText << L"] !" << endl;
		wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName(typeid(Template)) << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vykona sa TEMPLATE ARGUMENT DEDUCTION na zaklade DEDUCTION GUIDE.
		// !!!!! Na TEMPLATE ARGUMENT DEDUCTION  sa pouzije DEDUCTION GUIDE, ktory je definovany ako PSEUDO CONSTRUCTOR s 2 PARAMETERS.
		SAggregrateTemplateStructure							Template={L"Timmy",L"Anderson"};

		wcout << L"TEMPLATE - VALUE [" << Template.MValue << L"] TEXT [" << Template.MText << L"] !" << endl;
		wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName(typeid(Template)) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestStack1();
	//TestStack2();
	//TestStack3();
	//TestPartialUsage();
	//TestNonMemberOperators();
	//TestTemplateSpecialization();
	//TestPartialTemplateSpecialization1();
	//TestPartialTemplateSpecialization2();
	//TestDefaultTemplateParameters();
	//TestTemplateClassAliases();
	//TestTemplateClassMemberAliases();
	//TestTemplateArgumentsDeduction();
	//TestTemplateArgumentsDeductionByValueVsByReference();
	//TestTemplateDeductionGuides();
	TestAggregrateTemplateStructure();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------