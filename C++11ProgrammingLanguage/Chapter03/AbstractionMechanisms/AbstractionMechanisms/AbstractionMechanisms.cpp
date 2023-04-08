//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include "MyDebug.h"
#include "CConcreteType.h"
#include "CConcreteCollectionType.h"
#include "CDerivedClass.h"
#include "CClassHierarchyDerived.h"
#include "CCopyOperations.h"
#include "CMoveOperations.h"
#include "CMoveOperationDerived.h"
#include "CDeletedDefaultOperations.h"
#include "CDeletedMethods.h"
#include "CClassTemplate.h"
#include "CComplexTemplate.h"
#include "CComplexTemplateComparer.h"
#include "CSimpleVariadicClassTemplate.h"
#include "CComplexVariadicClassTemplate.h"
#include "CBiggerTypeTypeFunction.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConcreteType(void)
{
	PrintLineSeparator();

	{
		CConcreteType											Value(356);

		wcout << L"VALUE [" << Value << L"] !" << endl;
		wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CConcreteCollectionType									Value;

		Value.Add(10);
		Value.Add(20);
		Value.Add(30);

		Value[2]++;

		for(size_t Index=0;Index<Value.GetSize();Index++)
		{
			wcout << L"INDEX [" << Index << L"] VALUE [" << Value[Index] << L"] !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAbstractType(void)
{
	PrintLineSeparator();

	{
		CDerivedClass											ValueDerived(100,200);
		CBaseClass&												ValueBase=ValueDerived;

		// !!! Vola sa VIRTUAL METHOD pomocou POLYMORPHISM.
		wcout << L"VALUE [" << ValueBase.Print() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClassHierarchy(void)
{
	PrintLineSeparator();

	{
		CClassHierarchyDerived									Object(10,110,120,130,210,220,230,300);

		PrintLineSeparator();

		wcout << L"VALUE VA [" << Object.GetValueVA() << L"] !" << endl;
		wcout << L"VALUE A via B1 [" << static_cast<CClassHierarchyBaseB1&>(Object).GetValueA() << L"] !" << endl;
		wcout << L"VALUE A via B2 [" << static_cast<CClassHierarchyBaseB2&>(Object).GetValueA() << L"] !" << endl;
		wcout << L"VALUE B1 [" << Object.GetValueB1() << L"] !" << endl;
		wcout << L"VALUE B2 [" << Object.GetValueB2() << L"] !" << endl;
		wcout << L"VALUE [" << Object.GetValue() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCopyOperations(void)
{
	PrintLineSeparator();

	{
		int														Array1[3]{10,20,30};
		int														Array2[5]{10,20,30,40,50};

		CCopyOperations											Object1(Array1,3);

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		// Vola sa COPY CONSTRUCTOR.
		CCopyOperations											Object2(Object1);

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		CCopyOperations											Object3(Array2,5);

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();

		// Vola sa COPY OPERATOR=.
		Object2=Object3;

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCopyOperationsClassHierarchy(void)
{
	PrintLineSeparator();

	{
		CClassHierarchyDerived									Object1(110,210,310,410,510,610,710,810);

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		// Vola sa COPY CONSTRUCTOR.
		CClassHierarchyDerived									Object2(Object1);

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		CClassHierarchyDerived									Object3(120,220,320,420,520,620,720,820);

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();

		// Vola sa COPY OPERATOR=.
		Object2=Object3;

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMoveOperations(void)
{
	PrintLineSeparator();

	{
		int														Array1[3]{10,20,30};
		int														Array2[5]{10,20,30,40,50};

		CMoveOperations											Object1(Array1,3);

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		// Vola sa MOVE CONSTRUCTOR.
		CMoveOperations											Object2(std::move(Object1));

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		CMoveOperations											Object3(Array2,5);

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();

		// Vola sa MOVE OPERATOR=.
		Object2=std::move(Object3);

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMoveOperationsClassHierarchy(void)
{
	PrintLineSeparator();

	wstring														StringA1(L"A A");
	wstring														StringA2(L"A BB");
	wstring														StringA3(L"A CCC");
	wstring														StringA4(L"A DDDD");
	wstring														StringA5(L"A EEEEE");
	wstring														StringA6(L"A FFFFFF");
	wstring														StringA7(L"A GGGGGGG");
	wstring														StringA8(L"A HHHHHHHH");

	wstring														StringB1(L"BB A");
	wstring														StringB2(L"BB BB");
	wstring														StringB3(L"BB CCC");
	wstring														StringB4(L"BB DDDD");
	wstring														StringB5(L"BB EEEEE");
	wstring														StringB6(L"BB FFFFFF");
	wstring														StringB7(L"BB GGGGGGG");
	wstring														StringB8(L"BB HHHHHHHH");

	{
		CMoveOperationDerived									Object1(StringA1.c_str(),StringA1.size(),StringA2.c_str(),StringA2.size(),StringA3.c_str(),StringA3.size(),StringA4.c_str(),StringA4.size(),StringA5.c_str(),StringA5.size(),StringA6.c_str(),StringA6.size(),StringA7.c_str(),StringA7.size(),StringA8.c_str(),StringA8.size());

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		// Vola sa MOVE CONSTRUCTOR.
		CMoveOperationDerived									Object2(std::move(Object1));

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		CMoveOperationDerived									Object3(StringB1.c_str(),StringB1.size(),StringB2.c_str(),StringB2.size(),StringB3.c_str(),StringB3.size(),StringB4.c_str(),StringB4.size(),StringB5.c_str(),StringB5.size(),StringB6.c_str(),StringB6.size(),StringB7.c_str(),StringB7.size(),StringB8.c_str(),StringB8.size());

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();

		// Vola sa MOVE OPERATOR=.
		Object2=std::move(Object3);

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDeletedDefaultOperations(void)
{
	PrintLineSeparator();

	CDeletedDefaultOperations									Object1(L"Timmy Anderson",12);

	Object1.Print(L"Object1");

	PrintLineSeparator();

	/*
	// !!! Vola sa DEFAULT GENERATED COPY CONSTRUCTOR.
	CDeletedDefaultOperations									Object2(Object1);

	Object2.Print(L"Object2");

	PrintLineSeparator();
	*/

	// !!! Vola sa DEFAULT GENERATED MOVE CONSTRUCTOR.
	CDeletedDefaultOperations									Object3(move(Object1));

	Object3.Print(L"Object3");
	Object1.Print(L"Object1");

	PrintLineSeparator();

	/*
	CDeletedDefaultOperations									Object4;

	// !!! Kedze DEFAULT COPY OPERATOR= bol DELETED, nasledujuci CODE hodi COMPILATION ERROR.
	Object4=Object3;

	Object4.Print(L"Object4");

	PrintLineSeparator();
	*/

	CDeletedDefaultOperations									Object5;

	// !!! Vola sa DEFAULT GENERATED MOVE OPERATOR=.
	Object5=move(Object3);

	Object5.Print(L"Object5");
	Object3.Print(L"Object3");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDeletedMethods(void)
{
	PrintLineSeparator();

	CDeletedMethods												Object;

	Object.Overload1(10);

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze METHOD Overload2() s INT PARAMETER je DELETED METHOD.
	//Object.Overload2(10);

	Object.Overload2(10.5);

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze OPERATOR() s INT PARAMETER je DELETED OPERATOR.
	//Object(10);

	Object(10.5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
TType TemplateFunction(TType Value)
{
	TType														NewValue=++Value;

	return(NewValue);
}
//-----------------------------------------------------------------------------
void TestTemplateClassTemplateMethodAndTemplateFunction(void)
{
	PrintLineSeparator();

	CClassTemplate<int>											Object(100);

	wcout << L"VALUE [" << Object.GetValue() << L"] !" << endl;
	wcout << L"CONVERTED VALUE [" << Object.Convert<double>() << L"] !" << endl;
	wcout << L"RETURNED VALUE [" << TemplateFunction(3.4) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
bool AreEqual(TType Value1, TType Value2)
{
	if (Value1==Value2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------
template<typename TType, typename TComparer>
bool AreEqual(TType Value1, TType Value2)
{
	TComparer													Comparer;

	if (Comparer(Value1,Value2)==true)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType2 operator*(TType1 Value1, TType1 Value2)
{
	wcout << L"CONVERSION OPERATOR CALLED !" << endl;

	TType2														ConvertedValue=Value1.size()*Value2.size();

	return(ConvertedValue);
}
//-----------------------------------------------------------------------------
void TestFunctionTemplateAndFunctionObject(void)
{
	PrintLineSeparator();

	wcout << L"AreEqual<int>(8,8) [" << ((AreEqual<int>(8,8)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"AreEqual<int>(8,2) [" << ((AreEqual<int>(8,2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Dedukcia TYPE PARAMETERS.
	wcout << L"AreEqual(8,8) [" << ((AreEqual(8,8)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"AreEqual(8,2) [" << ((AreEqual(8,2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	CComplexTemplate<int>										CT1;
	CComplexTemplate<int>										CT2;

	CT1.MVariable2=8;
	CT2.MVariable2=2;

	wcout << L"AreEqual<int,CComplexTemplateComparer>(CT1,CT1) [" << ((AreEqual<CComplexTemplate<int>,CComplexTemplateComparer>(CT1,CT1)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"AreEqual<int,CComplexTemplateComparer>(CT1,CT2) [" << ((AreEqual<CComplexTemplate<int>,CComplexTemplateComparer>(CT1,CT2)==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wstring														Value1=L"Timmy Anderson";
	wstring														Value2=L"Atreyu";
	size_t														ConvertedValue=operator*<wstring,size_t>(Value1,Value2);

	wcout << L"Value1.size() [" << Value1.size() << L"] !" << endl;
	wcout << L"Value2.size() [" << Value2.size() << L"] !" << endl;
	wcout << L"ConvertedValue [" << ConvertedValue << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! NON-TEMPLATE FUNCTION, ktora reprezentuje KONIEC REKURZIE.
void SimpleVariadicTemplateFunction(wstring* Prefix, wstring* Postfix)
{
	if (Prefix!=nullptr)
	{
		wcout << *Prefix;
	}

	if (Postfix!=nullptr)
	{
		wcout << *Postfix;
	}
}
//-----------------------------------------------------------------------------
// !!! Definicia VARIADIC TEMPLATES. PARAMETER [FirstTypeParameter] reprezentuje 1. TYPE PARAMETER. PARAMETER [OtherTypeParameters] reprezentuje 2. az N. PARAMETERS.
// !!!!! TYPE PARAMETER [TTypes] sa nazyva TEMPLATE PARAMETER PACK.
template<typename TType, typename... TTypes>
// !!!!! SYNTAX [TTypes...] rozbali vsetky ostatne TYPE PARAMETERS.
void SimpleVariadicTemplateFunction(wstring* Prefix, wstring* Postfix, TType FirstTypeParameter, TTypes... OtherTypeParameters)
{
	if (Prefix!=nullptr)
	{
		wcout << *Prefix;
	}

	wcout << L" [" << FirstTypeParameter << L"]";

	// !!! Rekurzivne sa vola VARIADIC TEMPLATE SimpleVariadicTemplateFunction().
	// !!!!! SYNTAX [OtherTypeParameters...] rozbali vsetky ostatne TYPE PARAMETERS.
	SimpleVariadicTemplateFunction(nullptr,Postfix,OtherTypeParameters...);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
size_t CountTypeParamaterInVariadicTemplateFunction(TTypes...)
{
	size_t														NumberOfTypeParameters=sizeof...(TTypes);

	return(NumberOfTypeParameters);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void PassTypeParamaterVariadicTemplateFunction(TTypes... TypeParameters)
{
	// !!!!! TEMPLATE PARAMETER PACKS ako [TypeParameters] je mozne prenasat ako normalne PARAMETERS.
	// !!! Pri prenose TEMPLATE PARAMETER PACKS je nutne vykonat PARAMETER PACK EXPANSION.
	size_t														NumberOfTypeParameters=CountTypeParamaterInVariadicTemplateFunction(TypeParameters...);

	wcout << L"NumberOfTypeParameters [" << NumberOfTypeParameters << L"] !\n";
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void FinishProcessing(TTypes...)
{
	wprintf_s(L"FinishProcessing() - PROCESSING FINISHED !\n");
}
//-----------------------------------------------------------------------------
template<typename TType>
TType ProcessItem(TType TypeParameter)
{
	wcout << L"ProcessItem() - PARAMETER [" << TypeParameter << L"] !\n";

	return(TypeParameter);
}
//-----------------------------------------------------------------------------
template<typename... TTypes>
void UnpackTypeParameterPack(TTypes... TypeParameters)
{
	wprintf_s(L"UnpackTypeParameterPack() - PROCESSING STARTED !\n");

	// !!!!! C++ pretavi toto volanie na CODE [ProcessItem(TYPE_PARAMETER_1),ProcessItem(TYPE_PARAMETER_2),...,ProcessItem(TYPE_PARAMETER_N)]. To znaci, ze sa zoberu RETURN VALUES z volanie TEMPLATE FUNCTION PrintItem() a tie sa rozbalia, aby mohli sluzit ako PARAMETERS do VARIADIC TEMPLATE FUNCTION FinishProcessing().
	// !!!!! TYPE PARAMETER PACK je mozne pouzit pri vykonavani CASTS ci specifikacii TYPE PARAMETER TEMPLATES.
	// !!!!! CODE sa transformuje na CODE [FinishProcessing(ProcessItem<TYPE_1>((TYPE_1)TypeParameter_1),ProcessItem<TYPE_2>((TYPE_2)TypeParameter_2),...,ProcessItem<TYPE_N>((TYPE_N)TypeParameter_N))].
	FinishProcessing(ProcessItem<TTypes>((TTypes)TypeParameters)...);
}
//-----------------------------------------------------------------------------
void TestVariadicTemplateFunction(void)
{
	PrintLineSeparator();

	wstring														Prefix1=wstring(L"0 PARAMETERS");
	wstring														Prefix2=wstring(L"1 PARAMETERS");
	wstring														Prefix3=wstring(L"2 PARAMETERS");
	wstring														Prefix4=wstring(L"3 PARAMETERS");
	wstring														Postfix=wstring(L" !\n");

	SimpleVariadicTemplateFunction(&Prefix1,&Postfix);
	SimpleVariadicTemplateFunction(&Prefix2,&Postfix,L"Timmy");
	SimpleVariadicTemplateFunction(&Prefix3,&Postfix,L"Timmy",L"Anderson");
	SimpleVariadicTemplateFunction(&Prefix4,&Postfix,L"Timmy",L"Anderson",12);

	PrintLineSeparator();

	PassTypeParamaterVariadicTemplateFunction("5",4,3.2,2.4F,false);

	PrintLineSeparator();

	UnpackTypeParameterPack(true,100,12.4,L"ABC");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVariadicTemplateClass(void)
{
	PrintLineSeparator();

	CSimpleVariadicClassTemplate<wstring,wstring,int>			SimpleClass(wstring(L"Timmy"),wstring(L"Anderson"),12);

	SimpleClass.PrintBuffer();

	PrintLineSeparator();

	CComplexVariadicClassTemplate<wstring,wstring,int>			ComplexClass(wstring(L"Timmy"),wstring(L"Anderson"),12);

	wcout << L"ComplexClass [" << ComplexClass.GetFirstItem() << L"] [" << ComplexClass.GetBase()->GetFirstItem() << L"] [" << ComplexClass.GetBase()->GetBase()->GetFirstItem() << L"] !" << endl;

	PrintLineSeparator();

	ComplexClass.DoRecursion();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// TYPE ALIAS.
template<typename TType1,typename TType2>
using															IsBigger=typename CBiggerTypeTypeFunction<int,int>::BiggerType;
//-----------------------------------------------------------------------------
// TYPE ALIAS.
template<typename TType>
using															IsBiggerAsInt=typename CBiggerTypeTypeFunction<int,TType>::BiggerType;
//-----------------------------------------------------------------------------
void TestAliases(void)
{
	PrintLineSeparator();

	wcout << "IsBigger<int,double>::Type [" << ConvertStringToWideString(typeid(IsBigger<int,double>).name()) << L"] !" << endl;
	wcout << "IsBiggerAsInt<double>::Type [" << ConvertStringToWideString(typeid(IsBiggerAsInt<double>).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestConcreteType();
	//TestAbstractType();
	//TestClassHierarchy();
	//TestCopyOperations();
	//TestCopyOperationsClassHierarchy();
	//TestMoveOperations();
	//TestMoveOperationsClassHierarchy();
	//TestDeletedDefaultOperations();
	//TestDeletedMethods();
	//TestTemplateClassTemplateMethodAndTemplateFunction();
	//TestFunctionTemplateAndFunctionObject();
	//TestVariadicTemplateFunction();
	//TestVariadicTemplateClass();
	TestAliases();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------