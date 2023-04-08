//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdarg>
#include "MyDebug.h"
#include "CFunctions.h"
#include "CSomeClass.h"
#include "CConstExprFunctions.h"
#include "CConstExprClass.h"
#include "CSimpleClass.h"
#include "EParameterType.h"
#include "CBase.h"
#include "CDerived.h"
#include "COverloadedFunctionScopeBase.h"
#include "COverloadedFunctionScopeDerived.h"
#include "CDouble.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning (disable : 4005)
#pragma warning (disable : 4244)
#else
// IGNORUJE WARNING, ktory hadze GCC pri konverzii POINTERS na FUNCTIONS.
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFunctions(void)
{
	PrintLineSeparator();

	Function1();

	PrintLineSeparator();

	Function2(CSomeClass(L"Some VALUE 1 !"),CSomeClass(L"Some VALUE 2 !"));

	PrintLineSeparator();

	CSomeClass													ReturnValue1=Function3(CSomeClass(L"Some VALUE 1 !"),CSomeClass(L"Some VALUE 2 !"));

	wcout << L"RETURN VALUE 1 [" << ReturnValue1.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CSomeClass													ReturnValue2=Function4(CSomeClass(L"Some VALUE 1 !"),CSomeClass(L"Some VALUE 2 !"));

	wcout << L"RETURN VALUE 2 [" << ReturnValue2.GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFunctionTypes(void)
{
	PrintLineSeparator();

	wcout << L"TYPEID Function1() [" << ConvertStringToWideString(typeid(Function1).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID Function2() [" << ConvertStringToWideString(typeid(Function2).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID Function3() [" << ConvertStringToWideString(typeid(Function3).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID Function4() [" << ConvertStringToWideString(typeid(Function4).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::GetValue() [" << ConvertStringToWideString(typeid(&CSomeClass::GetValue).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test1() [" << ConvertStringToWideString(typeid(&CSomeClass::Test1).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test2() [" << ConvertStringToWideString(typeid(&CSomeClass::Test2).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test3() [" << ConvertStringToWideString(typeid(&CSomeClass::Test3).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstParameterFunctionTypes(void)
{
	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test1() [" << ConvertStringToWideString(typeid(&CSomeClass::Test1).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test2() [" << ConvertStringToWideString(typeid(&CSomeClass::Test2).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test3() [" << ConvertStringToWideString(typeid(&CSomeClass::Test3).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test4() [" << ConvertStringToWideString(typeid(&CSomeClass::Test4).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test5() [" << ConvertStringToWideString(typeid(&CSomeClass::Test5).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test6() [" << ConvertStringToWideString(typeid(&CSomeClass::Test6).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test7() [" << ConvertStringToWideString(typeid(&CSomeClass::Test7).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test8() [" << ConvertStringToWideString(typeid(&CSomeClass::Test8).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test9() [" << ConvertStringToWideString(typeid(&CSomeClass::Test9).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID CSomeClass::Test10() [" << ConvertStringToWideString(typeid(&CSomeClass::Test10).name()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"METHOD CSomeClass::Test1() and METHOD CSomeClass::Test2() have [" << (typeid(&CSomeClass::Test1)==typeid(&CSomeClass::Test2) ? L"SAME" : L"DIFFERENT" )  << L"] TYPES !" << endl;

	PrintLineSeparator();

	wcout << L"METHOD CSomeClass::Test2() and METHOD CSomeClass::Test3() have [" << (typeid(&CSomeClass::Test2)==typeid(&CSomeClass::Test3) ? L"SAME" : L"DIFFERENT" )  << L"] TYPES !" << endl;

	PrintLineSeparator();

	wcout << L"METHOD CSomeClass::Test3() and METHOD CSomeClass::Test4() have [" << (typeid(&CSomeClass::Test3)==typeid(&CSomeClass::Test4) ? L"SAME" : L"DIFFERENT" )  << L"] TYPES !" << endl;

	PrintLineSeparator();

	wcout << L"METHOD CSomeClass::Test5() and METHOD CSomeClass::Test6() have [" << (typeid(&CSomeClass::Test5)==typeid(&CSomeClass::Test6) ? L"SAME" : L"DIFFERENT" )  << L"] TYPES !" << endl;

	PrintLineSeparator();

	wcout << L"METHOD CSomeClass::Test7() and METHOD CSomeClass::Test8() have [" << (typeid(&CSomeClass::Test7)==typeid(&CSomeClass::Test8) ? L"SAME" : L"DIFFERENT" )  << L"] TYPES !" << endl;

	PrintLineSeparator();

	wcout << L"METHOD CSomeClass::Test8() and METHOD CSomeClass::Test9() have [" << (typeid(&CSomeClass::Test8)==typeid(&CSomeClass::Test9) ? L"SAME" : L"DIFFERENT" )  << L"] TYPES !" << endl;

	PrintLineSeparator();

	wcout << L"METHOD CSomeClass::Test8() and METHOD CSomeClass::Test10() have [" << (typeid(&CSomeClass::Test8)==typeid(&CSomeClass::Test10) ? L"SAME" : L"DIFFERENT" )  << L"] TYPES !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReturnValue(void)
{
	PrintLineSeparator();

	int															Value1=NormalReturnValueSyntax(100,200);

	wcout << L"METHOD NormalReturnValueSyntax() [" << Value1 << L"] !" << endl;

	PrintLineSeparator();

	int															Value2=NewReturnValueSyntax(100,200);

	wcout << L"METHOD NewReturnValueSyntax() [" << Value2 << L"] !" << endl;
	
	PrintLineSeparator();

	VoidReturnValue1(100,200);

	PrintLineSeparator();

	VoidReturnValue2(100,200);

	PrintLineSeparator();

	VoidReturnValue3(100,200);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInlineFunctions(void)
{
	PrintLineSeparator();

	int															Value1=FunctionInline(100,200);

	wcout << L"METHOD FunctionInline() [" << Value1 << L"] !" << endl;

	PrintLineSeparator();

	using														FuctionPointer=int (*)(int,int);
	FuctionPointer												PointerToInlineFunction=FunctionInline;

	wcout << L"POINTER to INLINE FUNCTION [" << PointerToInlineFunction << L"] !" << endl;

	int															Value2=PointerToInlineFunction(100,200);

	wcout << L"METHOD FunctionInline() BY POINTER [" << Value2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstexprFunctions1(void)
{
	PrintLineSeparator();

	// CONSTEXPR FUNCTION je mozne pouzit na inicializaciu CONST VARIABLES.
	const int													CONSTANT_1=FunctionConstExpr1(100,200);
	constexpr int												CONSTEXPR_1=FunctionConstExpr1(100,200);

	wcout << L"CONSTANT_1 [" << CONSTANT_1 << L"] !" << endl;
	wcout << L"CONSTEXPR_1 [" << CONSTEXPR_1 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'CONSTANT_1' je COMPILE TIME CONSTANT.
		int														Array[CONSTANT_1];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	const int													CONSTANT_2=FunctionConstExpr1(300,CONSTANT_1);
	constexpr int												CONSTEXPR_2=FunctionConstExpr1(300,CONSTANT_1);

	wcout << L"CONSTANT_2 [" << CONSTANT_2 << L"] !" << endl;
	wcout << L"CONSTEXPR_2 [" << CONSTEXPR_2 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'CONSTANT_2' je COMPILE TIME CONSTANT.
		int														Array[CONSTANT_2];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	const int													CONSTANT_3=FunctionConstExpr2(false,500,200);
	constexpr int												CONSTEXPR_3=FunctionConstExpr2(false,500,200);

	wcout << L"CONSTANT_3 [" << CONSTANT_3 << L"] !" << endl;
	wcout << L"CONSTEXPR_3 [" << CONSTEXPR_3 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'CONSTANT_3' je COMPILE TIME CONSTANT.
		int														Array[CONSTANT_3];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	const int													CONSTANT_4=FunctionConstExpr2(true,300,CONSTANT_3);
	constexpr int												CONSTEXPR_4=FunctionConstExpr2(true,300,CONSTANT_3);

	wcout << L"CONSTANT_4 [" << CONSTANT_4 << L"] !" << endl;
	wcout << L"CONSTEXPR_4 [" << CONSTEXPR_4 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'CONSTANT_4' je COMPILE TIME CONSTANT.
		int														Array[CONSTANT_4];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	const int													CONSTANT_5=FunctionConstExprWithConditions(false,500,200);
	constexpr int												CONSTEXPR_5=FunctionConstExprWithConditions(false,500,200);

	wcout << L"CONSTANT_5 [" << CONSTANT_5 << L"] !" << endl;
	wcout << L"CONSTEXPR_5 [" << CONSTEXPR_5 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'CONSTANT_5' je COMPILE TIME CONSTANT.
		int														Array[CONSTANT_5];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	const int													CONSTANT_6=FunctionConstExprWithConditions(true,300,CONSTANT_5);
	constexpr int												CONSTEXPR_6=FunctionConstExprWithConditions(true,300,CONSTANT_5);

	wcout << L"CONSTANT_6 [" << CONSTANT_6 << L"] !" << endl;
	wcout << L"CONSTEXPR_6 [" << CONSTEXPR_6 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'CONSTANT_6' je COMPILE TIME CONSTANT.
		int														Array[CONSTANT_6];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	const int													CONSTANT_7=FunctionConstExprWithCycles(true,100,50);
	constexpr int												CONSTEXPR_7=FunctionConstExprWithCycles(true,100,50);

	wcout << L"CONSTANT_7 [" << CONSTANT_7 << L"] !" << endl;
	wcout << L"CONSTEXPR_7 [" << CONSTEXPR_7 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'CONSTANT_7' je COMPILE TIME CONSTANT.
		int														Array[CONSTANT_7];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	const int													CONSTANT_8=FunctionConstExprWithCycles(false,100,50);
	constexpr int												CONSTEXPR_8=FunctionConstExprWithCycles(false,100,50);

	wcout << L"CONSTANT_8 [" << CONSTANT_8 << L"] !" << endl;
	wcout << L"CONSTEXPR_8 [" << CONSTEXPR_8 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'CONSTANT_8' je COMPILE TIME CONSTANT.
		int														Array[CONSTANT_8];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	PrintLineSeparator();

	// Volaju sa CONSTEXPR CONSTRUCTORS.
	// !!!!!! CONSTANT 'CONSTANT_9' je sice CONSTANT, ale jej METHODS NEGENERUJU COMPILE TIME CONSTANTS, ale iba RUN TIME CONSTANTS.
	// !!!!!! To, ze CONSTANT 'CONSTANT_9' je definovana ako CONSTANT znamena, ze VALUE 'CONSTANT_9' sa NEMOZE MENIT, no NEZNAMENA to, ze definouje COMPILE TIME CONSTANT.
	const CLiteralType											CONSTANT_9=FunctionConstExprReferenceParameters(CLiteralType(100),CLiteralType(200));
	const int													TEMP_CONSTANT_1=CONSTANT_9.GetValue();

	// !!! Vola sa CONSTEXPR METHOD.
	wcout << L"CONSTANT_9 by CONSTEXPR METHOD CALL [" << TEMP_CONSTANT_1 << L"] !" << endl;

	/*
	{
		// !!! COMPILER hodi ERROR, pretoze CONSTANT 'TEMP_CONSTANT_1' je iba RUN TIME CONSTANT.
		int														Array[TEMP_CONSTANT_1];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	{
		// !!! COMPILER hodi ERROR, pretoze z CONSTANT 'CONSTANT_9' NIE JE mozne ziskat COMPILE TIME CONSTANTS, ktore su potrebne pre inicializaciu CONSTEXPR VARIABLES.
		constexpr int											TEMP_CONSTEXPR_1=CONSTANT_9.GetValue();

		wcout << L"TEMP_CONSTEXPR_1 [" << TEMP_CONSTEXPR_1 << L"] !" << endl;
	}
	*/

	const int													TEMP_CONSTANT_2=CONSTANT_9.operator int();

	// !!! Vola sa CONSTEXPR OPERATOR().
	wcout << L"CONSTANT_9 by CONSTEXPR OPERATOR CALL [" << TEMP_CONSTANT_2 << L"] !" << endl;

	/*
	{
		// !!! COMPILER hodi ERROR, pretoze CONSTANT 'TEMP_CONSTANT_2' je iba RUN TIME CONSTANT.
		int														Array[TEMP_CONSTANT_2];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	{
		// !!! COMPILER hodi ERROR, pretoze z CONSTANT 'CONSTANT_9' NIE JE mozne ziskat COMPILE TIME CONSTANTS, ktore su potrebne pre inicializaciu CONSTEXPR VARIABLES.
		constexpr int											TEMP_CONSTEXPR_2=CONSTANT_9.operator int();

		wcout << L"TEMP_CONSTEXPR_2 [" << TEMP_CONSTEXPR_2 << L"] !" << endl;
	}
	*/

	wcout << L"CONSTANT_9 by NON-CONSTEXPR METHOD CALL [" << CONSTANT_9.GetValueNonConstExpr() << L"] !" << endl;

	PrintLineSeparator();

	// !!!!!! CONSTEXPR 'CONSTANT_10' je CONSTEXPR a preto jej METHODS GENERUJU COMPILE TIME CONSTANTS.
	// !!!!!! To, ze CONSTEXPR 'CONSTANT_10' je definovana ako CONSTEXPR znamena, ze je COMPILE TIME CONSTANT a jej CONSTEXP METHODS vracaju COMPILE TIME CONSTANTS.
	constexpr CLiteralType										CONSTANT_10=FunctionConstExprReferenceParameters(CLiteralType(100),CLiteralType(200));
	const int													TEMP_CONSTANT_3=CONSTANT_10.GetValue();

	// !!! Vola sa CONSTEXPR METHOD.
	wcout << L"CONSTANT_10 by CONSTEXPR METHOD CALL [" << TEMP_CONSTANT_3 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'TEMP_CONSTANT_3' je iba COMPILE TIME CONSTANT.
		int														Array[TEMP_CONSTANT_3];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	{
		// !!! COMPILER vypocita COMPILE TIME CONSTANT, pretoze CONSTEXPR 'CONSTANT_10' je CONSTEXPR, ktora generuje COMPILE TIME CONSTANTS.
		constexpr int											TEMP_CONSTEXPR_3=CONSTANT_10.GetValue();

		wcout << L"TEMP_CONSTEXPR_3 [" << TEMP_CONSTEXPR_3 << L"] !" << endl;
	}

	const int													TEMP_CONSTANT_4=CONSTANT_10.operator int();

	// !!! Vola sa CONSTEXPR OPERATOR().
	wcout << L"CONSTANT_10 by CONSTEXPR OPERATOR CALL [" << TEMP_CONSTANT_4 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'TEMP_CONSTANT_3' je iba COMPILE TIME CONSTANT.
		int														Array[TEMP_CONSTANT_4];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}

	{
		// !!! COMPILER vypocita COMPILE TIME CONSTANT, pretoze CONSTEXPR 'CONSTANT_10' je CONSTEXPR, ktora generuje COMPILE TIME CONSTANTS.
		constexpr int											TEMP_CONSTEXPR_4=CONSTANT_10.operator int();

		wcout << L"TEMP_CONSTEXPR_4 [" << TEMP_CONSTEXPR_4 << L"] !" << endl;
	}

	wcout << L"CONSTANT_10 by NON-CONSTEXPR METHOD CALL [" << CONSTANT_10.GetValueNonConstExpr() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstexprFunctions2(void)
{
	PrintLineSeparator();

	try
	{
		const int												CONSTANT_1=FunctionConstExprThrowingException(false);
	
		wcout << L"CONSTANT_1 [" << CONSTANT_1 << L"] !" << endl;

		// CONSTEXPR moze byt EVALUATED.
		constexpr int											CONSTEXPR_1=FunctionConstExprThrowingException(false);

		wcout << L"CONSTEXPR_1 [" << CONSTEXPR_1 << L"] !" << endl;

		// !!! COMPILER vytvori ARRAY, pretoze CONSTANT 'CONSTANT_1' je COMPILE TIME CONSTANT.
		int														Array[CONSTANT_1];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"CONSTANT_1 FAILED to EVALUATE - EXCEPTION [" << E.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		const int												CONSTANT_2=FunctionConstExprThrowingException(true);
	
		wcout << L"CONSTANT_2 [" << CONSTANT_2 << L"] !" << endl;

		/*
		// CONSTEXPR moze byt EVALUATED, pretoze FUNCTION FunctionConstExprThrowingException() s PARAMETER TRUE hodi EXCEPTION a tym padom CONSTANT NEMOZE byt EVALUATED.
		constexpr int											CONSTEXPR_2=FunctionConstExprThrowingException(true);

		wcout << L"CONSTEXPR_2 [" << CONSTEXPR_2 << L"] !" << endl;

		// !!! COMPILER HODI ERROR, pretoze CONSTANT 'CONSTANT_2' je RUN TIME CONSTANT a NIE COMPILE CONSTANT. Dovodom je fakt, ze CONST FUNCTION FunctionConstExprThrowingException() pri zadanom PARAMETRI hodi EXCEPTION a tym padom CONSTANT nebude EVALUATED.
		int														Array[CONSTANT_2];

		wcout << L"SIZEOF(ARRAY) [" << sizeof(Array) << L"] !" << endl;
		*/
	}
	catch(const CException& E)
	{
		wcout << L"CONSTANT_2 FAILED to EVALUATE - EXCEPTION [" << E.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstexprFunctions3(void)
{
	PrintLineSeparator();

	// !!! Kedze CONSTEXPR FUNCTION pouziva CONSTEXPR GLOBAL VARIABLE, FUNCTION generuje COMPILE TIME CONSTANT.
	const int													CONSTANT_1=FunctionConstExprUsingOutsideData_ConstExprVariable(100);

	wcout << L"CONSTANT_1 [" << CONSTANT_1 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze 'CONSTANT_1' JE COMPILE TIME CONSTANT.
		int														Array[CONSTANT_1];

		wcout << L"SIZEOF(Array) [" << sizeof(Array) << L"] !" << endl;
	}

	constexpr int												CONSTEXPR_1=FunctionConstExprUsingOutsideData_ConstExprVariable(100);

	wcout << L"CONSTEXPR_1 [" << CONSTEXPR_1 << L"] !" << endl;

	PrintLineSeparator();

	// !!! Kedze CONSTEXPR FUNCTION pouziva CONST GLOBAL VARIABLE, ktora MA DEFINOVANU VALUE, FUNCTION generuje COMPILE TIME CONSTANT.
	const int													CONSTANT_2=FunctionConstExprUsingOutsideData_ConstGlobalVariable(100);

	wcout << L"CONSTANT_2 [" << CONSTANT_2 << L"] !" << endl;

	constexpr int												CONSTEXPR_2=FunctionConstExprUsingOutsideData_ConstGlobalVariable(100);

	wcout << L"CONSTEXPR_2 [" << CONSTEXPR_2 << L"] !" << endl;

	{
		// !!! COMPILER vytvori ARRAY, pretoze 'CONSTANT_2' JE COMPILE TIME CONSTANT.
		int														Array[CONSTANT_2];

		wcout << L"SIZEOF(Array) [" << sizeof(Array) << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! Aj ked CONSTEXPR FUNCTION pouziva CONST GLOBAL VARIABLE, kedze ta je EXTERN a NEMA definovanu VALUE, tak FUNCTION generuje RUN TIME CONSTANT.
	const int													CONSTANT_3=FunctionConstExprUsingOutsideData_ConstExternGlobalVariable(100);

	wcout << L"CONSTANT_3 [" << CONSTANT_3 << L"] !" << endl;

	/*
	// !!! CONSTEXPR FUNCTION FunctionConstExprUsingOutsideData_ConstExternGlobalVariable() NEGENERUJE COMPILE TIME CONSTANT, a preto NEMOZE byt pouzita na definovanie CONSTEXPR VARIABLE.
	constexpr int												CONSTEXPR_3=FunctionConstExprUsingOutsideData_ConstExternGlobalVariable(100);

	wcout << L"CONSTEXPR_3 [" << CONSTEXPR_3 << L"] !" << endl;

	{
		// !!! COMPILER hodi ERROR, pretoze 'CONSTANT_3' NIE JE COMPILE TIME CONSTANT.
		int														Array[CONSTANT_3];

		wcout << L"SIZEOF(Array) [" << sizeof(Array) << L"] !" << endl;
	}
	*/

#ifdef _MSC_VER
	PrintLineSeparator();

	// !!! Kedze CONSTEXPR FUNCTION pouziva NON-CONST GLOBAL VARIABLE, generuje iba RUN TIME a NIE COMPILE TIME CONSTANTS.
	const int													CONSTANT_4=FunctionConstExprUsingOutsideData_NonConstGlobalVariable(100);

	wcout << L"CONSTANT_4 [" << CONSTANT_4 << L"] !" << endl;

	/*
	// !!! CONSTEXPR FUNCTION FunctionConstExprUsingOutsideData_NonConstGlobalVariable() NEGENERUJE COMPILE TIME CONSTANT, a preto NEMOZE byt pouzita na definovanie CONSTEXPR VARIABLE.
	constexpr int												CONSTEXPR_4=FunctionConstExprUsingOutsideData_NonConstGlobalVariable(100);

	wcout << L"CONSTEXPR_4 [" << CONSTEXPR_4 << L"] !" << endl;

	{
		// !!! COMPILER hodi ERROR, pretoze 'CONSTANT_4' NIE JE COMPILE TIME CONSTANT.
		int														Array[CONSTANT_4];

		wcout << L"SIZEOF(Array) [" << sizeof(Array) << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	wcout << L"GlobalVariable [" << GlobalVariable << L"] !" << endl;

	int															Value1=FunctionConstExprUsingOutsideData_NonConstGlobalVariable(22);

	wcout << L"Value1 [" << Value1 << L"] !" << endl;

	wcout << L"GlobalVariable [" << GlobalVariable << L"] !" << endl;

	GlobalVariable+=15;

	wcout << L"GlobalVariable [" << GlobalVariable << L"] !" << endl;

	int															Value2=FunctionConstExprUsingOutsideData_NonConstGlobalVariable(22);

	wcout << L"Value2 [" << Value2 << L"] !" << endl;

	wcout << L"GlobalVariable [" << GlobalVariable << L"] !" << endl;

	GlobalVariable+=15;

	wcout << L"GlobalVariable [" << GlobalVariable << L"] !" << endl;
#endif

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstexprMethods(void)
{
	PrintLineSeparator();

	// OBJECT NIE JE CONSTEXPR OBJECT.
	CConstExprClass												NonConstExprObject(100);

	wcout << L"METHOD NonConstExprObject.ConstExprFunction1() CALLED [" << NonConstExprObject.ConstExprFunction1() << L"] !" << endl;

	wcout << L"METHOD NonConstExprObject.ConstExprFunction2() CALLED [" << NonConstExprObject.ConstExprFunction2() << L"] !" << endl;

	// !!! Meni VALUE interneho FIELD.
	wcout << L"METHOD NonConstExprObject.ConstExprFunctionChangingValue() CALLED [" << NonConstExprObject.ConstExprFunctionChangingValue() << L"] !" << endl;

	wcout << L"METHOD NonConstExprObject.operator int() CALLED [" << NonConstExprObject.operator int() << L"] !" << endl;

	/*
	{
		// !!! COMPILER hodi ERROR, pretoze 'NonConstExprObject' NIE JE COMPILE TIME CONSTANT.
		int														Array[NonConstExprObject.ConstExprFunction1()];

		wcout << L"SIZEOF(Array) [" << sizeof(Array) << L"] !" << endl;
	}

	{
		// !!! COMPILER hodi ERROR, pretoze 'NonConstExprObject' NIE JE COMPILE TIME CONSTANT.
		int														Array[NonConstExprObject.ConstExprFunction2()];

		wcout << L"SIZEOF(Array) [" << sizeof(Array) << L"] !" << endl;
	}

	{
		// !!! COMPILER hodi ERROR, pretoze 'NonConstExprObject' NIE JE COMPILE TIME CONSTANT.
		int														Array[NonConstExprObject.operator int()];

		wcout << L"SIZEOF(Array) [" << sizeof(Array) << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	// !!! OBJECT JE CONSTEXPR OBJECT, pretoze jeho CONSTRUCTOR je CONSTEXPR.
	constexpr CConstExprClass									ConstExprObject(100);

	// !!!!! Hodi COMPILATION ERROR, pretoze METHOD ConstExprFunction1() NIE JE CONST METHOD.
	//wcout << L"METHOD ConstExprObject.ConstExprFunction1() CALLED [" << ConstExprObject.ConstExprFunction1() << L"] !" << endl;

	wcout << L"METHOD ConstExprObject.ConstExprFunction2() CALLED [" << ConstExprObject.ConstExprFunction2() << L"] !" << endl;

	wcout << L"METHOD ConstExprObject.operator int() CALLED [" << ConstExprObject.operator int() << L"] !" << endl;

	// !!!!! Hodi COMPILATION ERROR, pretoze METHOD ConstExprFunctionChangingValue() NIE JE CONST METHOD.
	//wcout << L"METHOD ConstExprObject.ConstExprFunctionChangingValue() CALLED [" << ConstExprObject.ConstExprFunctionChangingValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNoReturnFunction(void)
{
	PrintLineSeparator();

	try
	{
		NoReturnFunction(100,200);

		// !!! CODE po NO RETURN FUNCTION sa NIKDY NEVYKONA.
		wcout << L"AFTER FUNCTION CALL NoReturnFunction() !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"NO RETURN FUNCTION has THROWN EXCEPTION [" << E.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLocalVariables(void)
{
	PrintLineSeparator();

	UseStaticLocalVariable(33);

	PrintLineSeparator();

	UseStaticLocalVariable(33);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PassByValue(CSimpleClass Value)
{
	wcout << L"FUNCTION PassByValue() CALLED with VALUE [" << Value.GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void PassByPointer(const CSimpleClass* Value)
{
	wcout << L"FUNCTION PassByPointer() CALLED with VALUE [" << Value->GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void PassByNonConstReference(CSimpleClass& Value)
{
	wstring														NewValue(L"BBB");

	wcout << L"FUNCTION PassByNonConstReference() CALLED with VALUE [" << Value.GetValue() << L"] ! VALUE will be MODIFIED to ["<< NewValue << L"] !" << endl;

	Value.SetValue(NewValue);
}
//-----------------------------------------------------------------------------
void PassByConstReference(const CSimpleClass& Value)
{
	wcout << L"FUNCTION PassByConstReference() CALLED with VALUE [" << Value.GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void PassByNonConstReference(double& Value)
{
	double														NewValue=Value*2;

	wcout << L"FUNCTION PassByNonConstReference() CALLED with VALUE [" << Value << L"] ! VALUE will be MODIFIED to ["<< NewValue << L"] !" << endl;

	Value=NewValue;
}
//-----------------------------------------------------------------------------
void PassByConstReference(const double& Value)
{
	wcout << L"FUNCTION PassByConstReference() CALLED with VALUE [" << Value << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestArgumentPassing(void)
{
	PrintLineSeparator();

	{
		CSimpleClass												Value(L"AAA");

		{
			PassByValue(Value);

			PrintLineSeparator();

			PassByPointer(&Value);

			PrintLineSeparator();

			// !!! VALUE prenesena BY-REFERENCE je MODIFIKOVANA aj v CALLED FUNCTION.
			PassByNonConstReference(Value);

			wcout << L"FUNCTION TestArgumentPassing() VALUE [" << Value.GetValue() << L"] !" << endl;

			/*
			PrintLineSeparator();

			// !!!!! C++ NEUMOZNUJE do PARAMETERS typu NON-CONST REFERENCE prenasat R-VALUE REFERENCES.
			PassByNonConstReference(CSimpleClass(L"CCC"));
			*/

			PrintLineSeparator();

			PassByConstReference(Value);

			PrintLineSeparator();

			// !!! C++ UMOZNUJE zaslat aj R-VALUE REFERENCES do L-VALUE REFERENCE PARAMETERS.
			PassByConstReference(CSimpleClass(L"CCC"));
		}
	}

	PrintLineSeparator();

	double														DoubleValue=123.45;

	PassByConstReference(DoubleValue);

	PassByNonConstReference(DoubleValue);

	wcout << L"FUNCTION TestArgumentPassing() VALUE [" << DoubleValue << L"] !" << endl;

	PrintLineSeparator();

	float														FloatValue=123.45f;

	PassByConstReference(FloatValue);

	/*
	// !!!!! C++ NEUMOZNUJE zaslat ARGUMENT BY-REFERENCE, ktory je INEHO TYPE ako PARAMETER TYPE. To by vyzadovalo vytvorenie TEMPORARY OBJECT, ktory by bol hned po skonceni CALLED FUNCTION zlikvidovany a tak modifikacia VALUE v CALLED FUNCTION by sa NEPREJAVILA. Aby CODE NEBOL NECITATELNY, tak C++ ZNEMOZNUJE zasielanie ARGUMENT BY-REFERENCE, ktory je INEHO TYPE ako PARAMETER TYPE.
	PassByNonConstReference(FloatValue);

	wcout << L"FUNCTION TestArgumentPassing() VALUE [" << FloatValue << L"] !" << endl;
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ArrayParameterFunction1(int* Array, int ArraySize)
{
	wstringstream												ArrayStream1;

	for(int Index=0;Index<ArraySize;Index++)
	{
		if (Index>0)
		{
			ArrayStream1 << L" ";
		}

		ArrayStream1 << Array[Index];

		Array[Index]*=2;
	}

	wcout << L"FUNCTION ArrayParameterFunction1() VALUE [" << ArrayStream1.str() << L"] ! BEFORE CHANGE !" << endl;

	wstringstream												ArrayStream2;

	for(int Index=0;Index<ArraySize;Index++)
	{
		if (Index>0)
		{
			ArrayStream2 << L" ";
		}

		ArrayStream2 << Array[Index];
	}

	wcout << L"FUNCTION ArrayParameterFunction1() VALUE [" << ArrayStream2.str() << L"] ! AFTER CHANGE !" << endl;
}
//-----------------------------------------------------------------------------
// !!! FUNCTION ma IDENTICKY PROTOTYPE ako FUNCTION ArrayParameterFunction1().
void ArrayParameterFunction2(int Array[], int ArraySize)
{
	wstringstream												ArrayStream1;

	for(int Index=0;Index<ArraySize;Index++)
	{
		if (Index>0)
		{
			ArrayStream1 << L" ";
		}

		ArrayStream1 << Array[Index];

		Array[Index]*=2;
	}

	wcout << L"FUNCTION ArrayParameterFunction2() VALUE [" << ArrayStream1.str() << L"] ! BEFORE CHANGE !" << endl;

	wstringstream												ArrayStream2;

	for(int Index=0;Index<ArraySize;Index++)
	{
		if (Index>0)
		{
			ArrayStream2 << L" ";
		}

		ArrayStream2 << Array[Index];
	}

	wcout << L"FUNCTION ArrayParameterFunction2() VALUE [" << ArrayStream2.str() << L"] ! AFTER CHANGE !" << endl;
}
//-----------------------------------------------------------------------------
// !!! FUNCTION ma IDENTICKY PROTOTYPE ako FUNCTION ArrayParameterFunction1().
void ArrayParameterFunction3(int Array[100], int ArraySize)
{
	wstringstream												ArrayStream1;

	for(int Index=0;Index<ArraySize;Index++)
	{
		if (Index>0)
		{
			ArrayStream1 << L" ";
		}

		ArrayStream1 << Array[Index];

		Array[Index]*=2;
	}

	wcout << L"FUNCTION ArrayParameterFunction3() VALUE [" << ArrayStream1.str() << L"] ! BEFORE CHANGE !" << endl;

	wstringstream												ArrayStream2;

	for(int Index=0;Index<ArraySize;Index++)
	{
		if (Index>0)
		{
			ArrayStream2 << L" ";
		}

		ArrayStream2 << Array[Index];
	}

	wcout << L"FUNCTION ArrayParameterFunction3() VALUE [" << ArrayStream2.str() << L"] ! AFTER CHANGE !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! FUNCTION prenasa ARRAY PARAMETER BY-REFERENCE.
void ArrayParameterFunctionByReference(int (&Array)[3])
{
	wstringstream												ArrayStream1;

	for(int Index=0;Index<3;Index++)
	{
		if (Index>0)
		{
			ArrayStream1 << L" ";
		}

		ArrayStream1 << Array[Index];

		Array[Index]*=2;
	}

	wcout << L"FUNCTION ArrayParameterFunctionByReference(int (&Array)[3]) VALUE [" << ArrayStream1.str() << L"] ! BEFORE CHANGE !" << endl;

	wstringstream												ArrayStream2;

	for(int Index=0;Index<3;Index++)
	{
		if (Index>0)
		{
			ArrayStream2 << L" ";
		}

		ArrayStream2 << Array[Index];
	}

	wcout << L"FUNCTION ArrayParameterFunctionByReference(int (&Array)[3]) VALUE [" << ArrayStream2.str() << L"] ! AFTER CHANGE !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! FUNCTION prenasa ARRAY PARAMETER BY-REFERENCE.
void ArrayParameterFunctionByReference(int (&Array)[5])
{
	wstringstream												ArrayStream1;

	for(int Index=0;Index<3;Index++)
	{
		if (Index>0)
		{
			ArrayStream1 << L" ";
		}

		ArrayStream1 << Array[Index];

		Array[Index]*=2;
	}

	wcout << L"FUNCTION ArrayParameterFunctionByReference(int (&Array)[5]) VALUE [" << ArrayStream1.str() << L"] ! BEFORE CHANGE !" << endl;

	wstringstream												ArrayStream2;

	for(int Index=0;Index<3;Index++)
	{
		if (Index>0)
		{
			ArrayStream2 << L" ";
		}

		ArrayStream2 << Array[Index];
	}

	wcout << L"FUNCTION ArrayParameterFunctionByReference(int (&Array)[5]) VALUE [" << ArrayStream2.str() << L"] ! AFTER CHANGE !" << endl;
}
//-----------------------------------------------------------------------------
void TestArrayArgument(void)
{
	PrintLineSeparator();

	const int													SIZE_1=5;
	int															Array1[SIZE_1]{10,20,30,40,50};

	{
		ArrayParameterFunction1(Array1,SIZE_1);

		wstringstream											ArrayStream;

		for(int Index=0;Index<SIZE_1;Index++)
		{
			if (Index>0)
			{
				ArrayStream << L" ";
			}

			ArrayStream << Array1[Index];
		}

		wcout << L"FUNCTION TestArrayArgument() VALUE [" << ArrayStream.str() << L"] ! AFTER CHANGE !" << endl;
	}

	PrintLineSeparator();

	{
		ArrayParameterFunction2(Array1,SIZE_1);

		wstringstream											ArrayStream;

		for(int Index=0;Index<SIZE_1;Index++)
		{
			if (Index>0)
			{
				ArrayStream << L" ";
			}

			ArrayStream << Array1[Index];
		}

		wcout << L"FUNCTION TestArrayArgument() VALUE [" << ArrayStream.str() << L"] ! AFTER CHANGE !" << endl;
	}

	PrintLineSeparator();

	{
		ArrayParameterFunction3(Array1,SIZE_1);

		wstringstream											ArrayStream;

		for(int Index=0;Index<SIZE_1;Index++)
		{
			if (Index>0)
			{
				ArrayStream << L" ";
			}

			ArrayStream << Array1[Index];
		}

		wcout << L"FUNCTION TestArrayArgument() VALUE [" << ArrayStream.str() << L"] ! AFTER CHANGE !" << endl;
	}

	PrintLineSeparator();

	const int													SIZE_2=3;
	int															Array2[SIZE_2]{11,22,33};

	{
		ArrayParameterFunctionByReference(Array1);

		wstringstream											ArrayStream;

		for(int Index=0;Index<SIZE_1;Index++)
		{
			if (Index>0)
			{
				ArrayStream << L" ";
			}

			ArrayStream << Array1[Index];
		}

		wcout << L"FUNCTION TestArrayArgument() VALUE [" << ArrayStream.str() << L"] ! AFTER CHANGE !" << endl;
	}

	PrintLineSeparator();

	{
		ArrayParameterFunctionByReference(Array2);

		wstringstream											ArrayStream;

		for(int Index=0;Index<SIZE_2;Index++)
		{
			if (Index>0)
			{
				ArrayStream << L" ";
			}

			ArrayStream << Array2[Index];
		}

		wcout << L"FUNCTION TestArrayArgument() VALUE [" << ArrayStream.str() << L"] ! AFTER CHANGE !" << endl;
	}

	/*
	PrintLineSeparator();

	const int													SIZE_3=4;
	int															Array3[SIZE_3]{111,222,333,444};

	{
		// !!!!! COMPILER hodi ERROR, pretoze ARRAY ma 4 ELEMENTS, zatial co FUNCTION ArrayParameterFunctionByReference() je definovana PRE ARRAYS s 3 a 5 ELEMENTS.
		ArrayParameterFunctionByReference(Array3);

		wstringstream											ArrayStream;

		for(int Index=0;Index<SIZE_3;Index++)
		{
			if (Index>0)
			{
				ArrayStream << L" ";
			}

			ArrayStream << Array3[Index];
		}

		wcout << L"FUNCTION TestArrayArgument() VALUE [" << ArrayStream.str() << L"] ! AFTER CHANGE !" << endl;
	}
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UniformInitializationFunction(const CLiteralType& Value)
{
	wcout << L"FUNCTION UniformInitializationFunction(const CLiteralType&) VALUE [" << Value.GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void UniformInitializationFunction(const vector<int>& Value)
{
	wstringstream												Stream;

	for(size_t Index=0;Index<Value.size();Index++)
	{
		if (Index>0)
		{
			Stream << L" ";
		}

		Stream << Value[Index];
	}

	wcout << L"FUNCTION UniformInitializationFunction(const vector<int>&) VALUE [" << Stream.str() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
/*
// !!!!! Ak by FUNCTION bola DEFINED, sposobovala by AMBIGUITY s ostatnymi OVERLOADED FUNCTIONS.
void UniformInitializationFunction(const initializer_list<int>& Value)
{
	wstringstream												Stream;

	for(size_t Index=0;Index<Value.size();Index++)
	{
		if (Index>0)
		{
			Stream << L" ";
		}
		
		Stream << Value.begin()[Index];
	}

	wcout << L"FUNCTION UniformInitializationFunction(const initializer_list<int>&) VALUE [" << Stream.str() << L"] !" << endl;
}
*/
//-----------------------------------------------------------------------------
void UniformInitializationFunction(initializer_list<int> Value)
{
	wstringstream												Stream;

	for(size_t Index=0;Index<Value.size();Index++)
	{
		if (Index>0)
		{
			Stream << L" ";
		}
		
		Stream << Value.begin()[Index];
	}

	wcout << L"FUNCTION UniformInitializationFunction(initializer_list<int>) VALUE [" << Stream.str() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestUniformInitializationArgument(void)
{
	PrintLineSeparator();

	UniformInitializationFunction(CLiteralType{100});

	PrintLineSeparator();

	// !!! Vola sa FUNCTION UniformInitializationFunction(initializer_list<int>), pretoze PARAMETER TYPE [initializer_list] ma PREDNOST v pripade AMBIGUITY.
	UniformInitializationFunction({100});

	PrintLineSeparator();

	UniformInitializationFunction({100,200});

	PrintLineSeparator();

	UniformInitializationFunction(vector<int>{100,200});

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void EllipseParameterFunction(vector<EParameterType> ParameterTypes, ...)
{
	// !!! Reprezentuje LIST zaslanych ARGUMENTS.
	va_list														ArgumentList;

	// !!! LIST ARGUMENTS je NUTNE inicializovat.
	// !!! 1. PARAMETER je VARIABLE reprezentujuca ARGUMENT LIST.
	// !!! 2. PARAMETER je POSLEDNY PARAMETER pre ELLIPSE PARAMETER.
	va_start(ArgumentList,ParameterTypes);

	for(EParameterType ParameterType : ParameterTypes)
	{
		if (ParameterType==EParameterType::E_INTEGER)
		{
			// !!! Ziska sa ARGUMENT TYPE 'int'.
			// !!! 1. PARAMETER je VARIABLE reprezentujuca ARGUMENT LIST.
			// !!! 2. PARAMETER je ARGUMENT TYPE.
			int													Argument=va_arg(ArgumentList,int);

			wcout << L"INT PARAMETER VALUE [" << Argument << L"] !" << endl;
		}
		else if (ParameterType==EParameterType::E_DOUBLE)
		{
			// !!! Ziska sa ARGUMENT TYPE 'double'.
			// !!! 1. PARAMETER je VARIABLE reprezentujuca ARGUMENT LIST.
			// !!! 2. PARAMETER je ARGUMENT TYPE.
			double												Argument=va_arg(ArgumentList,double);

			wcout << L"DOUBLE PARAMETER VALUE [" << Argument << L"] !" << endl;
		}
		else
		{
			// !!! Ziska sa ARGUMENT TYPE 'wstring'.
			// !!! 1. PARAMETER je VARIABLE reprezentujuca ARGUMENT LIST.
			// !!! 2. PARAMETER je ARGUMENT TYPE.
			wstring												Argument=va_arg(ArgumentList,wstring);

			wcout << L"STRING PARAMETER VALUE [" << Argument << L"] !" << endl;
		}
	}

	// !!! Na konci iterovania ARGUMENTS je NUTNE uvolnit ARGUMENT LIST a vratit STACK do validnej pozicie.
	// !!! PARAMETER je VARIABLE reprezentujuca ARGUMENT LIST.
	va_end(ArgumentList);
}
//-----------------------------------------------------------------------------
void TestEllipseArgument(void)
{
	PrintLineSeparator();

	vector<EParameterType>										ParameterTypes1({EParameterType::E_DOUBLE,EParameterType::E_INTEGER,EParameterType::E_STRING});

	EllipseParameterFunction(ParameterTypes1,33.44,-158,wstring(L"Timmy Anderson"));

	PrintLineSeparator();

	vector<EParameterType>										ParameterTypes2({EParameterType::E_STRING,EParameterType::E_STRING});

	EllipseParameterFunction(ParameterTypes2,wstring(L"Timmy"),wstring(L"Anderson"));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DefaultArgumentsFunction(int Parameter1, CSimpleClass Parameter2=CSimpleClass(L"DEFAULT"), int Parameter3=100)
{
	wcout << L"FUNCTION DefaultArgumentsFunction() - Parameter1 [" << Parameter1 << L"] Parameter2 [" << Parameter2.GetValue() << L"] Parameter3 [" << Parameter3 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestDefaultArguments(void)
{
	PrintLineSeparator();

	DefaultArgumentsFunction(33,CSimpleClass(L"AAA"),66);

	PrintLineSeparator();

	DefaultArgumentsFunction(33,CSimpleClass(L"AAA"));

	PrintLineSeparator();

	DefaultArgumentsFunction(33);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void OverloadedFunctionExactMatch(char Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionExactMatch(CHAR) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionExactMatch(int Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionExactMatch(CHAR) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionExactMatch(long Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionExactMatch(LONG) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionExactMatch(unsigned int Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionExactMatch(UNSIGNED INT) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionExactMatch(float Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionExactMatch(FLOAT) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionExactMatch(double Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionExactMatch(DOUBLE) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestOverloadedFunctionsExactMatch(void)
{
	PrintLineSeparator();

	char														Char='A';
	int															Integer=-100;
	long														Long=999999999L;
	unsigned int												UnsignedInteger=100;
	float														Float=123.456F;
	double														Double=123.456789987;

	// EXACT MATCH.
	OverloadedFunctionExactMatch(Char);

	// EXACT MATCH.
	OverloadedFunctionExactMatch(Integer);

	// EXACT MATCH.
	OverloadedFunctionExactMatch(Long);

	// EXACT MATCH.
	OverloadedFunctionExactMatch(UnsignedInteger);

	// EXACT MATCH.
	OverloadedFunctionExactMatch(Float);

	// EXACT MATCH.
	OverloadedFunctionExactMatch(Double);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void OverloadedFunctionPromotions(int Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionPromotions(INT) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionPromotions(unsigned int Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionPromotions(UNSIGNED INT) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionPromotions(double Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionPromotions(DOUBLE) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOverloadedFunctionsPromotions(void)
{
	PrintLineSeparator();

	short														Short=-100;
	unsigned short												UnsignedShort=100;
	float														Float=123.456F;

	// PROMOTIONS.
	OverloadedFunctionPromotions(Short);

	// PROMOTIONS.
	// !!! Vola verziu INT a NIE UNSIGNED INT.
	OverloadedFunctionPromotions(UnsignedShort);

	// PROMOTIONS.
	OverloadedFunctionPromotions(Float);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void OverloadedFunctionStandardConversions1(wstring Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionStandardConversions1(WSTRING) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionStandardConversions1(double Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionStandardConversions1(DOUBLE) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionStandardConversions2(wstring Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionStandardConversions2(WSTRING) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionStandardConversions2(int Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionStandardConversions2(INT) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionStandardConversions2(const CBase& Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionStandardConversions2(CONST CBase&) CALLED with Parameter [" << Parameter.GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestOverloadedFunctionsStandardConversions(void)
{
	PrintLineSeparator();

	int															Integer=100;
	double														Double=123.456789987;
	CDerived													Derived(L"ABC");

	// STANDARD CONVERSION INT na DOUBLE.
	OverloadedFunctionStandardConversions1(Integer);

	// STANDARD CONVERSION DOUBLE na INT.
	// !!! COMPILER standardne hodi WARNING.
	OverloadedFunctionStandardConversions2(Double);

	// STANDARD CONVERSION CDerived& na CBase&.
	OverloadedFunctionStandardConversions2(Derived);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void OverloadedFunctionUserDefinedConversions(int Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionUserDefinedConversions(INT) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionUserDefinedConversions(const CBase& Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionUserDefinedConversions(CONST CBase&) CALLED with Parameter [" << Parameter.GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestOverloadedFunctionsUserDefinedConversions(void)
{
	PrintLineSeparator();

	wstring														String(L"ABC");

	// !!! Vykona sa USER DEFINED CONVERSION volanim CONSTRUCTOR CLASS CBase.
	OverloadedFunctionUserDefinedConversions(String);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
float OverloadedFunctionReturnValues(float Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionReturnValues(FLOAT) CALLED with Parameter [" << Parameter << L"] !" << endl;

	return(Parameter);
}
//-----------------------------------------------------------------------------
double OverloadedFunctionReturnValues(double Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionReturnValues(DOUBLE) CALLED with Parameter [" << Parameter << L"] !" << endl;

	return(Parameter);
}
//-----------------------------------------------------------------------------
void TestOverloadedFunctionsReturnValues(void)
{
	PrintLineSeparator();

	float														Float=123.456F;
	double														Double=123.456789987;

	float														ReturnValue1=OverloadedFunctionReturnValues(Float);

	wcout << L"RETURN VALUE [" << ReturnValue1 << L"] !" << endl;

	PrintLineSeparator();

	double														ReturnValue2=OverloadedFunctionReturnValues(Double);

	wcout << L"RETURN VALUE [" << ReturnValue2 << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vola sa FUNCTION s PARAMETER FLOAT, aj ked RETURN VALUE je DOUBLE, pretoze RETURN VALUES sa pri OVERLOADED FUNCTION RESOULTION IGNORUJU.
	double														ReturnValue3=OverloadedFunctionReturnValues(Float);

	wcout << L"RETURN VALUE [" << ReturnValue3 << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vola sa FUNCTION s PARAMETER DOUBLE, aj ked RETURN VALUE je FLOAT, pretoze RETURN VALUES sa pri OVERLOADED FUNCTION RESOULTION IGNORUJU.
	float														ReturnValue4=OverloadedFunctionReturnValues(Double);

	wcout << L"RETURN VALUE [" << ReturnValue4 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void OverloadedFunctionScope1(int Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionScope1(INT) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionScope1(double Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionScope1(DOUBLE) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionScope2(int Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionScope2(INT) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionScope2(double Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionScope2(DOUBLE) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
namespace MY
{
//-----------------------------------------------------------------------------
	void OverloadedFunctionScope2(int Parameter)
	{
		wcout << L"FUNCTION OverloadedFunctionScope2(INT) CALLED with Parameter [" << Parameter << L"] !" << endl;
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
void OverloadedFunctionScope3(double Parameter)
{
	wcout << L"FUNCTION OverloadedFunctionScope3(DOUBLE) CALLED with Parameter [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestOverloadedFunctionsScopes(void)
{
	PrintLineSeparator();

	int															Integer=100;
	double														Double=123.456789987;

	// EXACT MATCH.
	OverloadedFunctionScope1(Integer);

	// EXACT MATCH.
	OverloadedFunctionScope1(Double);

	PrintLineSeparator();

	// !!! DECLRATION FUNCTION na LOCAL SCOPE.
	void OverloadedFunctionScope2(double Parameter);

	// !!!!! Zavola sa FUNCTION OverloadedFunctionScope2(DOUBLE), pretoze IBA TATO je DECLARED na LOCAL SCOPE.
	// !!!!! FUNCTION OverloadedFunctionScope2(INT) sa IGNORUJE pri OVERLOADED FUNCTION RESOLUTION, pretoze je deklarovana v GLOBAL SCOPE, zatial co FUNCTION OverloadedFunctionScope2(DOUBLE) je deklarovana v LOCAL SCOPE.
	OverloadedFunctionScope2(Integer);

	OverloadedFunctionScope2(Double);

	PrintLineSeparator();

	COverloadedFunctionScopeDerived								Object;

	Object.TestOverloadedFunction();

	// !!!!! Zavola sa METHOD COverloadedFunctionScopeDerived::OverloadedMethod(DOUBLE), pretoze METHOD COverloadedFunctionScopeBase::OverloadedMethod(INT) je definovana v PARENT CLASS, ktory NIE JE v CURRENT SCOPE a tym padom sa IGNORUJE pri OVERLOADED FUNCTION RESOLUTION.
	Object.OverloadedMethod(Integer);

	Object.OverloadedMethod(Double);

	PrintLineSeparator();

	using namespace MY;

	// !!!!! Zavola sa FUNCTION OverloadedFunctionScope3(DOUBLE), pretoze IBA TATO je DECLARED na LOCAL SCOPE.
	// !!!!! FUNCTION OverloadedFunctionScope3(INT) sa IGNORUJE pri OVERLOADED FUNCTION RESOLUTION, pretoze je v INOM NAMESPACE.
	// !!!!! Ani pouzitie USING NAMESPACE 'MY' neprenesie FUNCTION OverloadedFunctionScope3(INT) do CURRENT SCOPE.
	OverloadedFunctionScope3(Integer);

	OverloadedFunctionScope3(Double);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void OverloadedFunctionMultiArguments(int Parameter1, int Parameter2)
{
	wcout << L"FUNCTION OverloadedFunctionMultiArguments(INT,INT) CALLED with PARAMETER 1 [" << Parameter1 << L"] and PARAMETER 2 [" << Parameter2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionMultiArguments(double Parameter1, double Parameter2)
{
	wcout << L"FUNCTION OverloadedFunctionMultiArguments(DOUBLE,DOUBLE) CALLED with PARAMETER 1 [" << Parameter1 << L"] and PARAMETER 2 [" << Parameter2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionMultiArguments(double Parameter1, CDouble Parameter2)
{
	wcout << L"FUNCTION OverloadedFunctionMultiArguments(DOUBLE,CDouble) CALLED with PARAMETER 1 [" << Parameter1 << L"] and PARAMETER 2 [" << Parameter2.GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionMultiArguments(CDouble Parameter1, int Parameter2)
{
	wcout << L"FUNCTION OverloadedFunctionMultiArguments(CDouble,INT) CALLED with PARAMETER 1 [" << Parameter1.GetValue() << L"] and PARAMETER 2 [" << Parameter2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void OverloadedFunctionMultiArguments(CDouble Parameter1, CDouble Parameter2)
{
	wcout << L"FUNCTION OverloadedFunctionMultiArguments(CDouble,CDouble) CALLED with PARAMETER 1 [" << Parameter1.GetValue() << L"] and PARAMETER 2 [" << Parameter2.GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestOverloadedFunctionsMultiArguments(void)
{
	PrintLineSeparator();

	CDouble														Double(12.22);

	// !!! Vola sa FUNCTION OverloadedFunctionMultiArguments(INT,INT).
	OverloadedFunctionMultiArguments(2,2);

	// !!! Vola sa FUNCTION OverloadedFunctionMultiArguments(DOUBLE,DOUBLE).
	OverloadedFunctionMultiArguments(2.0,2.0);

	// !!! Vola sa FUNCTION OverloadedFunctionMultiArguments(DOUBLE,CDouble).
	OverloadedFunctionMultiArguments(2,Double);

	// !!! Vola sa FUNCTION OverloadedFunctionMultiArguments(CDouble,INT).
	OverloadedFunctionMultiArguments(Double,2);

	// !!! Vola sa FUNCTION OverloadedFunctionMultiArguments(CDouble,CDouble).
	OverloadedFunctionMultiArguments(Double,Double);

	// !!!!! COMPILER hodi ERROR, pretoze FUNCTION OverloadedFunctionMultiArguments(INT,INT) aj FUNCTION OverloadedFunctionMultiArguments(DOUBLE,DOUBLE) sa zhoduju podla RULE EXACT MATCH a tym padom COMPILER NEVIE rozhodnut, ktoru FUNCTION ma pouzit.
	//OverloadedFunctionMultiArguments(2.0,2);

	// !!! Vola sa FUNCTION OverloadedFunctionMultiArguments(DOUBLE,DOUBLE).
	// !!!!! FUNCTION OverloadedFunctionMultiArguments(INT,INT) sa NEPOUZIJE, pretoze sa zhoduje podla RULE 'MATCH USING STANDARD CONVERSIONS', ktora ma NIZSIU PRIORITU ako RULE 'MATCH USING PROMOTIONS'.
	OverloadedFunctionMultiArguments(2.0,static_cast<long long>(2));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
size_t SomeFunction1(wstring Parameter)
{
	wcout << L"FUNCTION SomeFunction1(WSTRING) CALLED with PARAMETER [" << Parameter << L"] !" << endl;

	return(Parameter.size());
}
//-----------------------------------------------------------------------------
size_t SomeFunction2(wstring Parameter)
{
	wcout << L"FUNCTION SomeFunction2(WSTRING) CALLED with PARAMETER [" << Parameter << L"] !" << endl;

	return(Parameter.size());
}
//-----------------------------------------------------------------------------
void SomeFunction3(wstring Parameter)
{
	wcout << L"FUNCTION SomeFunction3(WSTRING) CALLED with PARAMETER [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TwoParametersOverloaded(int Value1, int Value2)
{
	wcout << L"FUNCTION TwoParametersOverloaded(INT,INT) CALLED with PARAMETER 1 [" << Value1 << L"] and PARAMETER 2 [" << Value2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TwoParametersOverloaded(int Value1, long Value2)
{
	wcout << L"FUNCTION TwoParametersOverloaded(INT,LONG) CALLED with PARAMETER 1 [" << Value1 << L"] and PARAMETER 2 [" << Value2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void ReinterpretCast(char Value1, char Value2)
{
	wcout << L"FUNCTION ReinterpretCast(CHAR,CHAR) CALLED with PARAMETER 1 [" << Value1 << L"] and PARAMETER 2 [" << Value2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void ExceptFunction(int Value)
{
	try
	{
		wcout << L"FUNCTION ExceptFunction(INT) CALLED with PARAMETER [" << Value << L"] !" << endl;
	}
	catch(...)
	{
	}
}
//-----------------------------------------------------------------------------
void NoExceptFunction(int Value) noexcept
{
	try
	{
		wcout << L"FUNCTION NoExceptFunction(INT) CALLED with PARAMETER [" << Value << L"] !" << endl;
	}
	catch(...)
	{
	}
}
//-----------------------------------------------------------------------------
void TestPointersToFunctions(void)
{
	PrintLineSeparator();

	// Definuje sa POINTER na FUNCTION.
	size_t														(*PointerToFunction1)(wstring)=nullptr;

	// !!! Do POINTER na FUNCTION sa prideli ADDRESS na FUNCTION.
	PointerToFunction1=&SomeFunction1;

	// !!! FUNCTION sa vola pomocou POINTER na FUNCTION.
	size_t														Length1=(*PointerToFunction1)(L"ABCDEF");

	wcout << L"LENGTH 1 [" << Length1 << L"] !" << endl;

	PrintLineSeparator();

	size_t														(*PointerToFunction2)(wstring)=nullptr;

	// !!! Do POINTER na FUNCTION sa prideli ADDRESS na FUNCTION.
	// !!!!! NEPOUZIVA sa OPERATOR&, pretoze C++ to NEVYZADUJE.
	PointerToFunction2=SomeFunction2;

	// !!! FUNCTION sa vola pomocou POINTER na FUNCTION.
	// !!!!! NEPOUZIVA sa OPERATOR*, pretoze to C++ NEVYZADUJE.
	size_t														Length2=PointerToFunction2(L"Delta MK3");

	wcout << L"LENGTH 2 [" << Length2 << L"] !" << endl;

	/*
	// !!!!! COMPILER hodi ERROR, pretoze FUNCTION SomeFunction3() ma RETURN VALUE TYPE VOID, zatial co POINTER na FUNCTION 'PointerToFunction2' ocakava RETURN VALUE TYPE [size_t].
	PointerToFunction2=SomeFunction3;

	size_t														Length3=PointerToFunction2(L"Delta MK3");

	wcout << L"LENGTH 3 [" << Length3 << L"] !" << endl;
	*/

	PrintLineSeparator();

	// !!! Priradi sa FUNCTION TwoParametersOverloaded(INT,INT).
	void														(*PointerToFunction3)(int,int)=&TwoParametersOverloaded;

	PointerToFunction3(100,200);

	// !!! Priradi sa FUNCTION TwoParametersOverloaded(INT,LONG).
	void														(*PointerToFunction4)(int,long)=&TwoParametersOverloaded;

	PointerToFunction4(100,200);

	/*
	// !!! COMPILER hodi ERROR, pretoze FUNCTION TwoParametersOverloaded(INT,SHORT) NEEXISTUJE.
	void														(*PointerToFunction5)(int,short)=&TwoParametersOverloaded;

	PointerToFunction5(100,200);
	*/

	PrintLineSeparator();

	using														NormalFunction=void (*)(char,char);
	using														RCFunction=void (*)(int,int);

	NormalFunction												PointerToFunctionRC1=&ReinterpretCast;

	PointerToFunctionRC1('A','Z');

	// !!!!! EXTREMNE NEBEZPECNA CONVERSION na INY TYPE POINTER TO FUNCTION.
	RCFunction													PointerToFunctionTemp=reinterpret_cast<RCFunction>(PointerToFunctionRC1);

	// !!!!! Tento CODE moze sposobit PROGRAM CRASH, pretoze STACK NEZODPOVEDA tomu co FUNCTION OCAKAVA.
	//PointerToFunctionTemp(100,200);

	// !!!!! Spatna CONVERSION na povodny TYPE POINTER to FUNCTION.
	NormalFunction												PointerToFunctionRC2=reinterpret_cast<NormalFunction>(PointerToFunctionTemp);

	// !!!!! FUNCTION sa NORMALNE zavola, pretoze FUNCTION PROTOTYPE a POINTER na FUNCTION PROTOTYPE su ZHODNE.
	PointerToFunctionRC2('B','Y');

	PrintLineSeparator();

	void														(*ExceptPointerToFunction)(int);
	void														(*NoExceptPointerToFunction)(int) noexcept;

	ExceptPointerToFunction=&ExceptFunction;

	ExceptPointerToFunction(100);

	// !!!!! C++ UMOZNUJE do POINTER na FUNCTION, ktoreho PROTOTYPE NEOBSAHUJE KEYWORD [noexcept] priradit FUNCTION, ktorej PROTOTYPE OBSAHUJE KEYWORD [noexcept].
	// !!!!! GCC hodi WARNING.
	ExceptPointerToFunction=&NoExceptFunction;

	ExceptPointerToFunction(100);

	// !!!!! C++ NEUMOZNUJE do POINTER na FUNCTION, ktoreho PROTOTYPE OBSAHUJE KEYWORD [noexcept] priradit FUNCTION, ktorej PROTOTYPE NEOBSAHUJE KEYWORD [noexcept].
	/*
	NoExceptPointerToFunction=&ExceptFunction;

	NoExceptPointerToFunction(100);
	*/

	NoExceptPointerToFunction=&NoExceptFunction;

	NoExceptPointerToFunction(100);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MyFunctionAAA(void)
{
	wcout << "FUNCTION MyFunctionAAA() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
void MyFunctionBBB(void)
{
	wcout << "FUNCTION MyFunctionBBB() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
void TestMacros(void)
{
	PrintLineSeparator();

#define XXX L"aaa"

	wcout << "MACRO XXX contains VALUE [" << XXX << L"] !" << endl;

	// !!! Povodne MACRO 'XXX' je HIDDEN.
#define XXX(Param1,Param2) (Param1+Param2)

	// COMPILER hodi ERROR.
	//wcout << "MACRO XXX contains VALUE [" << XXX << L"] !" << endl;

	wcout << "MACRO XXX contains VALUE [" << XXX(100,200) << L"] !" << endl;

	// !!! MACRO XXX(Param1,Param2) je HIDDEN.
#define XXX(Param1,Param2,Param3) (Param1+Param2+Param3)

	// COMPILER hodi ERROR.
	//wcout << "MACRO XXX contains VALUE [" << XXX(100,200) << L"] !" << endl;

	wcout << "MACRO XXX contains VALUE [" << XXX(100,200,300) << L"] !" << endl;

	// MACRO XXX(Param1,Param2,Param3) je UNDEFINED.
#undef XXX

	// COMPILER hodi ERROR.
	//wcout << "MACRO XXX contains VALUE [" << XXX(100,200,300) << L"] !" << endl;

	PrintLineSeparator();

	wchar_t														MyArray[100];

#define VARIADIC(Array,Size,Format,...) swprintf(Array,Size,Format,__VA_ARGS__)

	VARIADIC(MyArray,sizeof(MyArray)/sizeof(MyArray[0]),L"%ls %ls",L"AAA",L"BBB");

	wcout << "MY ARRAY [" << MyArray << L"] !" << endl;

	PrintLineSeparator();

#define TO_STRING(Param) #Param << L" [" << Param << L"]"

	const char													MyText[]{"ABCDEFG"};

	wcout << TO_STRING(MyText) << " !" << endl;

	PrintLineSeparator();

#define CONCATENATE_STRING(BaseName,Postfix) BaseName##Postfix

	// Zavola FUNCTION MyFunctionAAA().
	CONCATENATE_STRING(MyFunction,AAA)();

	// Zavola FUNCTION MyFunctionBBB().
	CONCATENATE_STRING(MyFunction,BBB)();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConditionalCompilation(void)
{
	PrintLineSeparator();

#define VALUE 1

#if VALUE==1
	wcout << "VALUE is SET to 1 !" << endl;
#elif VALUE==2
	wcout << "VALUE is SET to 2 !" << endl;
#else
	wcout << "VALUE is SET to SOMETHING ELSE !" << endl;
#endif

#define VALUE 2

#if VALUE==1
	wcout << "VALUE is SET to 1 !" << endl;
#elif VALUE==2
	wcout << "VALUE is SET to 2 !" << endl;
#else
	wcout << "VALUE is SET to SOMETHING ELSE !" << endl;
#endif

#define VALUE 5

#if VALUE==1
	wcout << "VALUE is SET to 1 !" << endl;
#elif VALUE==2
	wcout << "VALUE is SET to 2 !" << endl;
#else
	wcout << "VALUE is SET to SOMETHING ELSE !" << endl;
#endif

	PrintLineSeparator();

#if defined(VALUE)
	wcout << "VALUE is DEFINED !" << endl;
#endif

#ifdef VALUE
	wcout << "VALUE is DEFINED !" << endl;
#endif

#undef VALUE

#ifndef VALUE
	wcout << "VALUE is UNDEFINED !" << endl;
#endif

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStandardMacros(void)
{
	PrintLineSeparator();

	wcout << "MACRO __cplusplus [" << __cplusplus << L"] !" << endl;
	wcout << "MACRO __FILE__ [" << __FILE__ << L"] !" << endl;
	wcout << "MACRO __LINE__ [" << __LINE__ << L"] !" << endl;
	wcout << "MACRO __FUNCTION__ [" << __FUNCTION__ << L"] !" << endl;
	wcout << "MACRO __DATE__ [" << __DATE__ << L"] !" << endl;
	wcout << "MACRO __TIME__ [" << __TIME__ << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestFunctions();
	//TestFunctionTypes();
	//TestConstParameterFunctionTypes();
	//TestReturnValue();
	//TestInlineFunctions();
	//TestConstexprFunctions1();
	//TestConstexprFunctions2();
	//TestConstexprFunctions3();
	//TestConstexprMethods();
	//TestNoReturnFunction();
	//TestLocalVariables();
	//TestArgumentPassing();
	//TestArrayArgument();
	//TestUniformInitializationArgument();
	//TestEllipseArgument();
	//TestDefaultArguments();
	//TestOverloadedFunctionsExactMatch();
	//TestOverloadedFunctionsPromotions();
	//TestOverloadedFunctionsStandardConversions();
	//TestOverloadedFunctionsUserDefinedConversions();
	//TestOverloadedFunctionsReturnValues();
	//TestOverloadedFunctionsScopes();
	//TestOverloadedFunctionsMultiArguments();
	//TestPointersToFunctions();
	//TestMacros();
	//TestConditionalCompilation();
	TestStandardMacros();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------