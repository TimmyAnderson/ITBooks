//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <vector>
#include <unordered_set>
#include "MyDebug.h"
#include "CVariadicTemplateClass1.h"
#include "CVariadicTemplateClass2.h"
#include "CVariadicClassNoFinalCase.h"
#include "SNode.h"
#include "CValue.h"
#include "CVariadicTemplateClassDeductionGuides.h"
#include "CVariadicClassUsing.h"
#include "CVariadicClassUsingEqual.h"
#include "CVariadicClassUsingHash.h"
#include "CVariadicClassUsingBaseClasses.h"
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
void TestVariadicClass(void)
{
	PrintLineSeparator();

	{
		CVariadicTemplateClass1<wstring,wstring,int>			Object(L"Timmy",L"Anderson",12);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		// !!!!! Pouzije sa TEMPLATE SPECIALIZATION s 1 TEMPLATE PARAMETER a TEMPLATE PARAMETER PACK.
		CVariadicTemplateClass2<wstring,wstring,int>			Object(L"Timmy",L"Anderson",12);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		// !!!!! Pouzije sa TEMPLATE SPECIALIZATION s 1 TEMPLATE PARAMETER.
		CVariadicTemplateClass2<wstring>						Object(L"Timmy Anderson");

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre FINAL RECURSION CASE.
void VariadicMethodPrint1(void)
{
	wcout << L"END of PRINT METHOD !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre RECURSION CASES.
template<typename TThis, typename... TTypes>
void VariadicMethodPrint1(TThis This, TTypes... Others)
{
	// !!! Vypise sa 1. PARAMETER.
	wcout << L"VALUE [" << This << L"] !" << endl;

	// !!!!! REKURZIVNE sa vola ta ista METHOD na vypisanie ostatnych PARAMETERS.
	VariadicMethodPrint1(Others...);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre FINAL RECURSION CASE.
template<typename TThis>
void VariadicMethodPrint2(TThis This)
{
	// !!! Vypise sa PARAMETER.
	wcout << L"VALUE [" << This << L"] !" << endl;

	wcout << L"END of PRINT METHOD !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre RECURSION CASES.
template<typename TThis, typename... TTypes>
void VariadicMethodPrint2(TThis This, TTypes... Others)
{
	// !!! Vypise sa 1. PARAMETER.
	wcout << L"VALUE [" << This << L"] !" << endl;

	// !!!!! REKURZIVNE sa vola ta ista METHOD na vypisanie ostatnych PARAMETERS.
	VariadicMethodPrint2(Others...);
}
//----------------------------------------------------------------------------------------------------------------------
void TestVariadicMethod(void)
{
	PrintLineSeparator();

	VariadicMethodPrint1(L"Timmy",L"Anderson",12);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	VariadicMethodPrint2(L"Timmy",L"Anderson",12);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void OperatorVariadicSizeof(TTypes... Parameters)
{
	wcout << L"NUMBER of TEMPLATE PARAMETERS [" << sizeof...(TTypes) << L"] !" << endl;
	wcout << L"NUMBER of TEMPLATE FUNCTION PARAMETERS [" << sizeof...(Parameters) << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestOperatorVariadicSizeof(void)
{
	PrintLineSeparator();

	OperatorVariadicSizeof(L"Timmy",L"Anderson",12);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariadicClassNoFinalCase(void)
{
	PrintLineSeparator();

	{
		CVariadicClassNoFinalCase<wstring,wstring,int>			Object(L"Timmy",L"Anderson",12);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD pouzivana pre RECURSION CASE aj FINAL CASE.
template<typename TThis, typename... TTypes>
void OperatorVariadicMethodNoFinalCase(TThis This, TTypes... Others)
{
	// !!! Vypise sa 1. PARAMETER.
	wcout << L"VALUE [" << This << L"] !" << endl;

	/*
	// !!!!! COMPILER hodi ERROR, pretoze pre ak VARIADIC TEMPLATE PACK obsahuje 0 TEMPLATE PARAMETERS, tak sice CODE v KEYWORD [if] sa NEVYKONA, no COMPILER ho MUSI skompilovat. A pri kompilacii CODE [OperatorVariadicMethodNoFinalCase(Others...)] sa konvertuje na volanie FUNCTION s 0 PARAMETERS, a preto COMPILER hodi ERROR.
	if (sizeof...(TTypes)>0)
	{
		// !!!!! REKURZIVNE sa vola ta ista METHOD na vypisanie ostatnych PARAMETERS.
		OperatorVariadicMethodNoFinalCase(Others...);
	}
	*/

	// !!!!! CODE zbehne OK, pretoze KEYWORD [if constexpr] znamena, ze CODE vo vnutri IF bude COMPILED IBA ak IF CONDITION je TRUE. Z toho vyplyva, ze ak VARIADIC TEMPLATE PACK obsahuje 0 TEMPLATE PARAMETERS, tak sa CODE vo vnutri IF VOBEC NEKOMPILUJE a COMPILER NEHODI ERROR, ze mu chyba FUNCTION 'OperatorVariadicMethodNoFinalCase' s 0 PARAMETERS.
	if constexpr (sizeof...(TTypes)>0)
	{
		// !!!!! REKURZIVNE sa vola ta ista METHOD na vypisanie ostatnych PARAMETERS.
		OperatorVariadicMethodNoFinalCase(Others...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestVariadicMethodNoFinalCase(void)
{
	PrintLineSeparator();

	OperatorVariadicMethodNoFinalCase(L"Timmy",L"Anderson",12);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType TemplateOperatorFoldExpressions1Add5(TType Value)
{
	return(Value+5);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
common_type_t<TTypes...> TemplateOperatorFoldExpressions1UnaryLeftFold(TTypes... Values)
{
	// !!!!! Pouziva sa UNARY LEFT FOLD OPERATOR.
	common_type_t<TTypes...>									Result=(... + Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
common_type_t<TTypes...> TemplateOperatorFoldExpressions1UnaryRightFold(TTypes... Values)
{
	// !!!!! Pouziva sa UNARY RIGHT FOLD OPERATOR.
	common_type_t<TTypes...>									Result=(Values + ...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1BinaryLeftFold(TType InitValue, TTypes... Values)
{
	// !!!!! Pouziva sa BINARY LEFT FOLD OPERATOR.
	common_type_t<TType,TTypes...>								Result=(InitValue + ... + Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1BinaryRightFold(TType InitValue, TTypes... Values)
{
	// !!!!! Pouziva sa BINARY RIGHT FOLD OPERATOR.
	common_type_t<TType,TTypes...>								Result=(Values + ... + InitValue);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1ComplexExpression(TType InitValue, TTypes... Values)
{
	// !!!!! Vo FOLD EXPRESSIONS je mozne pouzivat SUBEXPRESSIONS, ktore vsak musia byt uzatvorene v zatvorkach [()].
	common_type_t<TType,TTypes...>								Result=((Values+2) + ... + (InitValue+1));

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1UnaryFoldEmptyParameterPack(TType Value, TTypes... Values)
{
	// !!!!! UNARY FOLD OPERATOR NIE je mozne pouzit, aj ked je TEMPLATE PARAMETER PACK PRAZDNY. COMPILER hodi ERROR
	common_type_t<TType,TTypes...>								Result=(... + Values);

	Result+=Value;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1BinaryFoldEmptyParameterPack(TType Value, TTypes... Values)
{
	// !!!!! BINARY FOLD OPERATOR je mozne pouzit, aj ked je TEMPLATE PARAMETER PACK PRAZDNY.
	common_type_t<TType,TTypes...>								Result=(Value + ... + Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
common_type_t<TType,TTypes...> TemplateOperatorFoldExpressions1CallFunction(TType Value, TTypes... Values)
{
	// !!!!! Pre kazdy TEMPLATE PARAMETER sa vola FUNCTION [TType TemplateOperatorFoldExpressions1Add5(TType Value)].
	common_type_t<TType,TTypes...>								Result=(Value + ... + TemplateOperatorFoldExpressions1Add5(Values));

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressions1(void)
{
	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1UnaryLeftFold(10,20,30);

		wcout << L"UNARY LEFT FOLD [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1UnaryRightFold(10,20,30);

		wcout << L"UNARY RIGHT FOLD [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1BinaryLeftFold(100,10,20,30);

		wcout << L"BINARY LEFT FOLD [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1BinaryRightFold(100,10,20,30);

		wcout << L"BINARY RIGHT FOLD [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1ComplexExpression(100,10,20,30);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1UnaryFoldEmptyParameterPack(100,10,20,30);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1BinaryFoldEmptyParameterPack(100,10,20,30);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze UNARY FOLD OPERATOR NEMOZE byt volany, ak je VARIADIC TEMPLATE PACK je PRAZDNY.
	{
		int														Result=TemplateOperatorFoldExpressions1UnaryFoldEmptyParameterPack(100);

		wcout << L"UNARY FOLD RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	// !!!!! CODE zbehne OK, pretoze BINARY FOLD OPERATOR MOZE byt volany, ak je VARIADIC TEMPLATE PACK je PRAZDNY.
	{
		int														Result=TemplateOperatorFoldExpressions1BinaryFoldEmptyParameterPack(100);

		wcout << L"BINARY FOLD RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Result=TemplateOperatorFoldExpressions1CallFunction(100,10,20,30);

		wcout << L"CALL FUNCTION RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TNode, typename TRootNode, typename... TNodes>
TNode* TemplateFoldExpressions2OperatorPointerToMember(TRootNode RootNode, TNodes... Nodes)
{
	// !!!!! Pouziva sa OPERATOR->* pre pristup k MEMBERS.
	TNode*														Result=(RootNode ->* ... ->* Nodes);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressions2(void)
{
	PrintLineSeparator();

	{
		SNode													Node1(10);
		SNode													Node2(20);
		SNode													Node3(30);

		Node1.SetRightNode(&Node2);
		Node2.SetLeftNode(&Node1);
		Node2.SetRightNode(&Node3);
		Node3.SetLeftNode(&Node2);

		// !!! Ziskaju sa POINTERS na MEMBERS.
		SNode*													SNode::*Left=&SNode::MLeftNode;
		SNode*													SNode::*Right=&SNode::MRightNode;

		// !!!!! Ako PATH sa pouzivaju POINTERS na MEMBERS.
		SNode*													Result=TemplateFoldExpressions2OperatorPointerToMember<SNode>(&Node1,Right,Left,Right,Right);

		wcout << L"NODE RESULT [" << Result->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TValue>
wstring TemplateFoldExpressions3Format(TValue Value, size_t& Index, size_t Count)
{
	wstringstream												Stream;

	if (Index>1)
	{
		Stream << L" ";
	}

	Stream << L"[" << Value << L"]";

	if (Index==Count)
	{
		Stream << L" !";
	}

	Index++;

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TValues>
wstringstream TemplateFoldExpressions3(TValues... Values)
{
	wstringstream												Stream;
	size_t														Index=1;

	Stream << L"VALUES ";

	// !!!!! Pouziva sa OPERATOR<< pre vypis ITEMS.
	(Stream << ... << TemplateFoldExpressions3Format(Values,Index,sizeof...(Values)));

	Stream << endl;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressions3(void)
{
	PrintLineSeparator();

	wstringstream												Stream=TemplateFoldExpressions3(L"Timmy",L"Anderson",12);

	wcout << Stream.str();

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TValues>
bool TemplateUnaryFoldExpressionAnd(TValues... Values)
{
	// !!!!! UNARY FOLD EXPRESSION pre OPERATOR&& moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [true].
	bool														Result=(... && Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TValues>
bool TemplateUnaryFoldExpressionOr(TValues... Values)
{
	// !!!!! UNARY FOLD EXPRESSION pre OPERATOR|| moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [false].
	bool														Result=(... || Values);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressionsUnaryFoldExpressions(void)
{
	PrintLineSeparator();

	{
		bool													Result=TemplateUnaryFoldExpressionAnd(true,true,true);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		bool													Result=TemplateUnaryFoldExpressionAnd(true,false,true);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! UNARY FOLD EXPRESSION pre OPERATOR&& moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [true].
		bool													Result=TemplateUnaryFoldExpressionAnd();

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		bool													Result=TemplateUnaryFoldExpressionOr(true,true,true);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		bool													Result=TemplateUnaryFoldExpressionOr(false,false,false);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! UNARY FOLD EXPRESSION pre OPERATOR|| moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [false].
		bool													Result=TemplateUnaryFoldExpressionOr();

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TValues>
void TemplateFoldExpressionsOperatorComma(vector<TType>& Vector, TValues... Values)
{
	// !!!!! Pomocou FOLD EXPRESSION a OPERATOR, sa pridaju ITEMS do VECTOR.
	// !!!!! UNARY FOLD EXPRESSION pre OPERATOR, moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [void()].
    (Vector.push_back(Values) , ...);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFoldExpressionsOperatorComma(void)
{
	PrintLineSeparator();

	{
		vector<int>												Values;

		TemplateFoldExpressionsOperatorComma(Values,10,20,30);

		if (Values.size()>0)
		{
			for(int Value : Values)
			{
				wcout << L"VALUE [" << Value << L"] !" << endl;
			}
		}
		else
		{
			wcout << L"VECTOR is EMPTY !" << endl;
		}
	}

	PrintLineSeparator();

	{
		vector<int>												Values;

		// !!!!! UNARY FOLD EXPRESSION pre OPERATOR, moze mat aj 0 TEMPLATE PARAMETERS. V takom pripade je RESULT VALUE [void()].
		TemplateFoldExpressionsOperatorComma(Values);

		if (Values.size()>0)
		{
			for(int Value : Values)
			{
				wcout << L"VALUE [" << Value << L"] !" << endl;
			}
		}
		else
		{
			wcout << L"VECTOR is EMPTY !" << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TValues>
void TemplateVariadicFunctionParametersByValue(TType Value, TValues... Values)
{
	wcout << L"BY VALUE [" << Value << L"] !" << endl;

	if constexpr (sizeof...(Values)>0)
	{
		// !!!!! Kedze su TEMPLATE PARAMETERS prenasane BY VALUE, pre vsetky ARGUMENTS v TEMPLATE PARAMETER PACK je volany COPY CONSTRUCTOR.
		TemplateVariadicFunctionParametersByValue(Values...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TValues>
void TemplateVariadicFunctionParametersByLValueReference(const TType& Value, const TValues&... Values)
{
	wcout << L"BY LVALUE REFERENCE [" << Value << L"] !" << endl;

	if constexpr (sizeof...(Values)>0)
	{
		// !!!!! Kedze su TEMPLATE PARAMETERS prenasane BY LVALUE REFERENCE, COPY CONSTRUCTORS pre vsetky ARGUMENTS v TEMPLATE PARAMETER PACK NIE je volany.
		TemplateVariadicFunctionParametersByLValueReference(Values...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TValues>
void TemplateVariadicFunctionParametersByRValueReference(TType&& Value, TValues&&... Values)
{
	wcout << L"BY RVALUE REFERENCE [" << Value << L"] !" << endl;

	if constexpr (sizeof...(Values)>0)
	{
		// !!!!! Kedze su TEMPLATE PARAMETERS prenasane BY RVALUE REFERENCE, COPY a MOVE CONSTRUCTORS pre vsetky ARGUMENTS v TEMPLATE PARAMETER PACK NIE su volane.
		TemplateVariadicFunctionParametersByRValueReference(move(Values)...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestVariadicFunctionParameters(void)
{
	PrintLineSeparator();

	{
		CValue<wstring>											Value1(L"Timmy");
		CValue<wstring>											Value2(L"Anderson");
		CValue<int>												Value3(12);

		// !!!!! Kedze su TEMPLATE PARAMETERS prenasane BY VALUE, pre vsetky ARGUMENTS v TEMPLATE PARAMETER PACK je volany COPY CONSTRUCTOR.
		TemplateVariadicFunctionParametersByValue(Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		CValue<wstring>											Value1(L"Timmy");
		CValue<wstring>											Value2(L"Anderson");
		CValue<int>												Value3(12);

		// !!!!! Kedze su TEMPLATE PARAMETERS prenasane BY LVALUE REFERENCE, COPY CONSTRUCTORS pre vsetky ARGUMENTS v TEMPLATE PARAMETER PACK NIE je volany.
		TemplateVariadicFunctionParametersByLValueReference(Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		CValue<wstring>											Value1(L"Timmy");
		CValue<wstring>											Value2(L"Anderson");
		CValue<int>												Value3(12);

		// !!!!! Kedze su TEMPLATE PARAMETERS prenasane BY RVALUE REFERENCE, COPY a MOVE CONSTRUCTORS pre vsetky ARGUMENTS v TEMPLATE PARAMETER PACK NIE su volane.
		TemplateVariadicFunctionParametersByRValueReference(move(Value1),move(Value2),move(Value3));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
void TemplateVariadicExpressionsPrint(TThis This, TTypes... Others)
{
	wcout << L"VALUE [" << This << L"] !" << endl;

	if constexpr (sizeof...(Others)>0)
	{
		TemplateVariadicExpressionsPrint(Others...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void TemplateVariadicExpressionsExpression1(TTypes... Values)
{
	// !!!!! VARIADIC EXPRESSION sa prelozi na CODE [PARAMETER_1+PARAMETER_1,PARAMETER_2+PARAMETER_2,...,PARAMETER_N+PARAMETER_N].
	TemplateVariadicExpressionsPrint((Values+Values)...);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void TemplateVariadicExpressionsExpression2(TTypes... Values)
{
	// !!!!! VARIADIC EXPRESSION sa prelozi na CODE [PARAMETER_1+PARAMETER_1,PARAMETER_2+PARAMETER_2,...,PARAMETER_N+PARAMETER_N,"END !!!"].
	TemplateVariadicExpressionsPrint((Values+Values)...,L"END !!!");
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void TemplateVariadicExpressionsExpression3(TTypes... Values)
{
	// !!!!! VARIADIC EXPRESSION sa prelozi na CODE [PARAMETER_1+100,PARAMETER_2+100,...,PARAMETER_N+100].
	TemplateVariadicExpressionsPrint((Values+100)...);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCollection, typename... TIndices>
void TemplateVariadicExpressionsExpression4(const TCollection& Collection, TIndices... Values)
{
	// !!!!! VARIADIC EXPRESSION sa prelozi na CODE [Collection[PARAMETER_1],Collection[PARAMETER_2],...,Collection[PARAMETER_N]].
	TemplateVariadicExpressionsPrint(Collection[Values]...);
}
//----------------------------------------------------------------------------------------------------------------------
void TestVariadicExpressions(void)
{
	PrintLineSeparator();

	{
		wstring													Text=L"Timmy";

		TemplateVariadicExpressionsExpression1(10,Text,22.22);
	}

	PrintLineSeparator();

	{
		wstring													Text=L"Timmy";

		TemplateVariadicExpressionsExpression2(10,Text,22.22);
	}

	PrintLineSeparator();

	{
		TemplateVariadicExpressionsExpression3(10,45.54,22.22);
	}

	PrintLineSeparator();

	{
		vector<wstring>											Values;

		Values.push_back(L"Timmy");
		Values.push_back(L"Jenny");
		Values.push_back(L"Josh");
		Values.push_back(L"Lucas");

		TemplateVariadicExpressionsExpression4(Values,3,1,2,0);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
void TemplateNoTypeVariadicParametersPrint(TThis This, TTypes... Others)
{
	wcout << L"VALUE [" << This << L"] !" << endl;

	if constexpr (sizeof...(Others)>0)
	{
		TemplateNoTypeVariadicParametersPrint(Others...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! VARIADIC TEMPLATE METHOD pouziva NON-TYPE VARIADIC TEMPLATE PARAMETERS.
template<size_t... Indices, typename TCollection>
void TemplateNoTypeVariadicParameters(const TCollection& Collection)
{
	// !!!!! VARIADIC EXPRESSION sa prelozi na CODE [Collection[PARAMETER_1],Collection[PARAMETER_2],...,Collection[PARAMETER_N]].
	TemplateNoTypeVariadicParametersPrint(Collection[Indices]...);
}
//----------------------------------------------------------------------------------------------------------------------
void TestNoTypeVariadicParameters(void)
{
	PrintLineSeparator();

	vector<wstring>												Values;

	Values.push_back(L"Timmy");
	Values.push_back(L"Jenny");
	Values.push_back(L"Josh");
	Values.push_back(L"Lucas");

	TemplateNoTypeVariadicParameters<3,1,2,0>(Values);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariadicTemplateClassDeductionGuides(void)
{
	PrintLineSeparator();

	{
		// !!!!! NEPOUZIJE sa DEDUCTION GUIDE.
		CVariadicTemplateClassDeductionGuides<wstring,wstring,int>	Object(L"Timmy",L"Anderson",12);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// !!!!! POUZIJE sa DEDUCTION GUIDE.
		// !!!!! DEDUCTION GUIDE pre PARAMETER TYPE 'const wchar_t*' pouzije TYPE [wstring] a pre ostatne TYPES povodne TYPES.
		CVariadicTemplateClassDeductionGuides					Object(L"Timmy",L"Jenny",L"Josh");

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// !!!!! POUZIJE sa DEDUCTION GUIDE.
		// !!!!! DEDUCTION GUIDE pre PARAMETER TYPE 'const wchar_t*' pouzije TYPE [wstring] a pre ostatne TYPES povodne TYPES.
		CVariadicTemplateClassDeductionGuides					Object(L"Timmy",L"Anderson",12);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariadicUsing(void)
{
	PrintLineSeparator();

	{
		unordered_set<CVariadicClassUsing,CVariadicClassUsingHash,CVariadicClassUsingEqual>	Values;

		Values.insert(CVariadicClassUsing(L"Timmy"));
		Values.insert(CVariadicClassUsing(L"Jenny"));
		Values.insert(CVariadicClassUsing(L"Josh"));

		for(const CVariadicClassUsing& Value : Values)
		{
			wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
		}
	}

	PrintLineSeparator();

	// !!! Vytvori sa CLASS, ktora dedi z CLASS 'CVariadicClassUsingEqual' a CLASS 'CVariadicClassUsingHash'.
	using														CClassEqualAndHash=CVariadicClassUsingBaseClasses<CVariadicClassUsingEqual,CVariadicClassUsingHash>;

	{
		// !!!!! CLASS pouziva pre HASH FUNCTION OBJECT a EQUAL FUNCTION OBJECT tu istu CLASS, ktora dedi z HASH FUNCTION OBJECT a EQUAL FUNCTION OBJECT.
		unordered_set<CVariadicClassUsing,CClassEqualAndHash,CClassEqualAndHash>	Values;

		Values.insert(CVariadicClassUsing(L"Timmy"));
		Values.insert(CVariadicClassUsing(L"Jenny"));
		Values.insert(CVariadicClassUsing(L"Josh"));

		for(const CVariadicClassUsing& Value : Values)
		{
			wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestVariadicClass();
	//TestVariadicMethod();
	//TestOperatorVariadicSizeof();
	//TestVariadicClassNoFinalCase();
	//TestVariadicMethodNoFinalCase();
	//TestFoldExpressions1();
	//TestFoldExpressions2();
	//TestFoldExpressions3();
	//TestFoldExpressionsUnaryFoldExpressions();
	//TestFoldExpressionsOperatorComma();
	//TestVariadicFunctionParameters();
	//TestVariadicExpressions();
	//TestNoTypeVariadicParameters();
	//TestVariadicTemplateClassDeductionGuides();
	TestVariadicUsing();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------