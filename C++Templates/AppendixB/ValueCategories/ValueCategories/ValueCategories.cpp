//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CValue.h"
#include "CValueWithConstructors.h"
#include "CValueNoConstructors.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26800 )
#pragma warning( disable : 4172 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestValueCategories1(void)
{
	PrintLineSeparator();

	int															Result=0;

	// !!! EXPRESSION je LVALUE.
	SHOW_VALUE_CATEGORY(Result);

	// !!! EXPRESSION je PRVALUE.
	SHOW_VALUE_CATEGORY(3+4);

	// !!! EXPRESSION je XVALUE.
	SHOW_VALUE_CATEGORY(move(Result));

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SStruct
{
//----------------------------------------------------------------------------------------------------------------------
	int															Value=0;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) Function1(int Value)
{
	// !!!!! ZATVORKY okolo KEYWORD [return] MUSIA byt VYNECHANE.
	// !!!!! Je to PRVALUE pretoze sa vracia VARIABLE BY VALUE.
	// !!!!! RETURN VALUE je TYPE [int].
	return Value;
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) Function2(int Value)
{
	// !!!!! Je to LVALUE pretoze sa vracia VARIABLE BY REFERENCE.
	// !!!!! RETURN VALUE je TYPE [int&].
	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) Function3(int Value)
{
	// !!!!! Je to PRVALUE, pretoze sa pouziva OPERATOR+.
	return(Value+1);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) Function4(int Value)
{
	// !!!!! Je to PRVALUE, pretoze sa pouziva POSTFIX OPERATOR++.
	return(Value++);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) Function5(int Value)
{
	// !!!!! Je to LVALUE, pretoze sa pouziva PREFIX OPERATOR++.
	return(++Value);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) Function6(int Value)
{
	// !!!!! Je to PRVALUE, pretoze EXPRESSION 'Value1' je LVALUE a EXPRESSION 'Value2' je PRVALUE.
	return((Value>=0) ? Value : 0);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) Function7(int Value1, int Value2)
{
	// !!!!! Je to LVALUE, pretoze EXPRESSION 'Value1' je LVALUUE aj EXPRESSION 'Value2' je LVALUE.
	return((Value1>=Value2) ? Value1 : Value2);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) Function8(void)
{
	// !!!!! Je to PRVALUE.
	return(SStruct{});
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) Function9(void)
{
	// !!!!! Je to XVALUE, pretoze EXPRESSION 'SStruct{}' je RVALUE a EXPRESSION 'Value' je DATA MEMBER.
	return(SStruct{}.Value);
}
//----------------------------------------------------------------------------------------------------------------------
void TestValueCategories2(void)
{
	PrintLineSeparator();

	// !!! EXPRESSION je PRVALUE.
	SHOW_VALUE_CATEGORY(Function1(0));

	// !!! EXPRESSION je LVALUE.
	SHOW_VALUE_CATEGORY(Function2(0));

	// !!! EXPRESSION je PRVALUE.
	SHOW_VALUE_CATEGORY(Function3(0));

	// !!! EXPRESSION je PRVALUE.
	SHOW_VALUE_CATEGORY(Function4(0));

	// !!! EXPRESSION je LVALUE.
	SHOW_VALUE_CATEGORY(Function5(0));

	// !!! EXPRESSION je PRVALUE.
	SHOW_VALUE_CATEGORY(Function6(0));

	// !!! EXPRESSION je LVALUE.
	SHOW_VALUE_CATEGORY(Function7(1,2));

	// !!! EXPRESSION je PRVALUE.
	SHOW_VALUE_CATEGORY(Function8());

	// !!! EXPRESSION je XVALUE.
	SHOW_VALUE_CATEGORY(Function9());

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int TemporaryMaterialization(const int& Value)
{
	return(Value+100);
}
//----------------------------------------------------------------------------------------------------------------------
int TemporaryMaterialization(const CValueWithConstructors& Value)
{
	return(Value.GetValue()+100);
}
//----------------------------------------------------------------------------------------------------------------------
CValueNoConstructors TemporaryMaterializationCreateObject(void)
{
	// !!!!! Od verzie C++17 sa NEVYTVARA TEMPORARY VARIABLE, ktory by bol nasledne skopirovany ako RETURN VALUE, ale vytvoreny OBJECT sa priamo pouzije na naplnenie VARIABLE do ktorej sa priradzuje RETURN VALUE.
	// !!!!! Ak sa COMPILER prepne na verziu pred verziou C++17, COMPILER hodi ERROR.

	return(CValueNoConstructors(10));
}
//----------------------------------------------------------------------------------------------------------------------
void TemporaryMaterialization(const CValue& Value)
{
	wcout << L"COPY PARAMETER - VALUE [" << Value.GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TemporaryMaterialization(CValue&& Value)
{
	wcout << L"MOVE PARAMETER - VALUE [" << Value.GetValue() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemporaryMaterialization(void)
{
	PrintLineSeparator();

	{
		// !!!!! Pretoze FUNCTION ocakava REFERENCE VALUE, ocakava GLVALUE. Avsak EXPRESSION '8' je PRVALUE. Preto dojde k TEMPORARY MATERIALIZATION, kedy je vytvorena TEMPORARY VARIABLE a inicializovana z PRVALUE '8' a nasledne tato TEMPORARY VARIABLE, ktora je XVALUE sa pouzije ako PARAMETER volania FUNCTION.
		int														Result=TemporaryMaterialization(8);

		wcout << L"RESULT [" << Result << L"] !" << endl;

		SHOW_VALUE_CATEGORY(Result);
		SHOW_VALUE_CATEGORY(8);
	}

	PrintLineSeparator();

	{
		// !!!!! Tu sa TEMPORARY OBJECT NEVYTVORI.
		int														Result=TemporaryMaterialization(CValueWithConstructors(8));

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Tu sa TEMPORARY OBJECT NEVYTVORI.
		auto													Result=TemporaryMaterializationCreateObject();

		wcout << L"RESULT [" << Result.GetValue() << L"] !" << endl;
		wcout << L"RESULT TYPE [" << GetTypeInfoName(typeid(Result)) << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CValue													Value(100);

		// !!! Zavola sa COPY VERZIA.
		TemporaryMaterialization(Value);
	}

	PrintLineSeparator();

	{
		const CValue											Value(100);

		// !!! Zavola sa COPY VERZIA.
		TemporaryMaterialization(Value);
	}

	PrintLineSeparator();

	{
		// !!! Zavola sa MOVE VERZIA.
		TemporaryMaterialization(CValue(100));
	}

	PrintLineSeparator();

	{
		CValue													Value(100);

		// !!! Zavola sa MOVE VERZIA.
		TemporaryMaterialization(move(Value));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! EXPRESSION 'EXPRESSION' MUSI byt v ZATVORKACH, aby KEYWORD [decltype((EXPRESSION)] vyhodnotil EXPRESSION 'EXPRESSION' ako EXPRESSION, a NIE ako ENTITY a vratil TYPE zodpovedajuci VALUE CATEGORY.
#define MACRO_VALUE_CATEGORY_DETECTION(EXPRESSION)\
	if constexpr (std::is_lvalue_reference<decltype((EXPRESSION))>::value==true)\
	{\
		wcout << L"EXPRESSION " << #EXPRESSION << L" is LVALUE." << endl;\
	}\
	else if constexpr (std::is_rvalue_reference<decltype((EXPRESSION))>::value==true)\
	{\
		wcout << L"EXPRESSION [" << #EXPRESSION << L"] is XVALUE." << endl;\
	}\
	else\
	{\
		wcout << L"EXPRESSION [" << #EXPRESSION << L"] is PRVALUE." << endl;\
	}\
//----------------------------------------------------------------------------------------------------------------------
// !!!!! EXPRESSION 'EXPRESSION' NIE JE v ZATVORKACH [()]. Vysledok je taky, ze MACRO NEFUNGUJE. Je to preto, lebo EXPRESSION [decltype(EXPRESSION)] vyhodnoti EXPRESSION 'EXPRESSION' ako ENTITY, a NIE ako EXPRESSION. V takom pripade NEVRACIA TYPE zodpovedajuci VALUE CATEGORY, ale vracia TYPE ENTITY.
#define MACRO_VALUE_CATEGORY_DETECTION_ERROR(EXPRESSION)\
	if constexpr (std::is_lvalue_reference<decltype(EXPRESSION)>::value==true)\
	{\
		wcout << L"ERROR - EXPRESSION [" << #EXPRESSION << L"] is LVALUE." << endl;\
	}\
	else if constexpr (std::is_rvalue_reference<decltype(EXPRESSION)>::value==true)\
	{\
		wcout << L"ERROR - EXPRESSION [" << #EXPRESSION << L"] is XVALUE." << endl;\
	}\
	else\
	{\
		wcout << L"ERROR - EXPRESSION [" << #EXPRESSION << L"] is PRVALUE." << endl;\
	}\
//----------------------------------------------------------------------------------------------------------------------
void TestValueCategoryDetection(void)
{
	PrintLineSeparator();

	{
		int												Value=100;

		(void) Value;

		// !!!!! EXPRESSION je LVALUE.
		MACRO_VALUE_CATEGORY_DETECTION(Value)
	}

	PrintLineSeparator();

	{
		// !!!!! EXPRESSION je PRVALUE.
		MACRO_VALUE_CATEGORY_DETECTION(100)
	}

	PrintLineSeparator();

	{
		int												Value=100;

		// !!!!! EXPRESSION je XVALUE.
		MACRO_VALUE_CATEGORY_DETECTION(move(Value))
	}

	PrintLineSeparator();

	{
		int												Value=100;

		// !!!!! EXPRESSION je LVALUE, no kedze sa v EXPRESSION [decltype(EXPRESSION)] NEPOUZILI ZATOVRKY [()], tak EXPRESSION [decltype(EXPRESSION)] vracia TYPE PRVALUE, a NIE LVALUE.
		MACRO_VALUE_CATEGORY_DETECTION_ERROR(Value)
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int																GlobalVariable=100;
//----------------------------------------------------------------------------------------------------------------------
// !!! Vracia PRVALUE.
int ValueCategoryForReferencesPRVALUE(void)
{
	return(GlobalVariable);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Vracia LVALUE.
int& ValueCategoryForReferencesLVALUE(void)
{
	return(GlobalVariable);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Vracia XVALUE.
int&& ValueCategoryForReferencesXVALUE(void)
{
	return(move(GlobalVariable));
}
//----------------------------------------------------------------------------------------------------------------------
void TestValueCategoryForReferences(void)
{
	PrintLineSeparator();

	{
		bool													IsPRVALUE=is_same_v<decltype(ValueCategoryForReferencesPRVALUE()),int>;

		wcout << L"IsPRVALUE [" << IsPRVALUE << L"] !" << endl;

		bool													IsLVALUE=is_same_v<decltype(ValueCategoryForReferencesLVALUE()),int&>;

		wcout << L"IsLVALUE [" << IsLVALUE << L"] !" << endl;

		bool													IsXVALUE=is_same_v<decltype(ValueCategoryForReferencesXVALUE()),int&&>;

		wcout << L"IsXVALUE [" << IsXVALUE << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! CODE zbehne, pretoze sa do LVALUE uklada LVALUE.
	{
		int&													Value=ValueCategoryForReferencesLVALUE();

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze do LVAULE nie je mozne ulozit PRVALUE.
	{
		int&													Value=ValueCategoryForReferencesPRVALUE();

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}
	*/

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze do LVAULE nie je mozne ulozit XVALUE.
	{
		int&													Value=ValueCategoryForReferencesXVALUE();

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}
	*/

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze do RVAULE nie je mozne ulozit LVALUE.
	{
		int&&													Value=ValueCategoryForReferencesLVALUE();

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	// !!! CODE zbehne, pretoze sa do RVALUE uklada PRVALUE.
	{
		int&&													Value=ValueCategoryForReferencesPRVALUE();

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! CODE zbehne, pretoze sa do RVALUE uklada XVALUE.
	{
		int&&													Value=ValueCategoryForReferencesXVALUE();

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestValueCategories1();
	//TestValueCategories2();
	//TestTemporaryMaterialization();
	//TestValueCategoryDetection();
	TestValueCategoryForReferences();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------