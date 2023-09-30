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
#include "SCalculatePrimeNoConstExpr.h"
#include "CException.h"
#include "CCompileTimePartialSpecializations.h"
#include "CClassNoUsingTypeNoMethodSize.h"
#include "CClassWithUsingTypeNoMethodSize.h"
#include "CClassWithUsingTypeWithMethodSize.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
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
void TestCompileProgrammingNoConstExpr(void)
{
	PrintLineSeparator();

	wcout << L"IS PRIME 11 - VALUE [" << SCalculatePrimeNoConstExpr<11>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 10 - VALUE [" << SCalculatePrimeNoConstExpr<10>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 9 - VALUE [" << SCalculatePrimeNoConstExpr<9>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 8 - VALUE [" << SCalculatePrimeNoConstExpr<8>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 7 - VALUE [" << SCalculatePrimeNoConstExpr<7>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 6 - VALUE [" << SCalculatePrimeNoConstExpr<6>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 5 - VALUE [" << SCalculatePrimeNoConstExpr<5>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 4 - VALUE [" << SCalculatePrimeNoConstExpr<4>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 3 - VALUE [" << SCalculatePrimeNoConstExpr<3>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 2 - VALUE [" << SCalculatePrimeNoConstExpr<2>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 1 - VALUE [" << SCalculatePrimeNoConstExpr<1>::IS_PRIME << L"]." << endl;

	wcout << L"IS PRIME 0 - VALUE [" << SCalculatePrimeNoConstExpr<0>::IS_PRIME << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
constexpr bool IsPrime(unsigned int Number)
{
	for (unsigned int Divisor=2;Divisor<=(Number/2);++Divisor)
	{
		if ((Number % Divisor)==0)
		{
			return(false);
		}
	}

	return(Number>1);
}
//----------------------------------------------------------------------------------------------------------------------
void TestCompileProgrammingConstExpr(void)
{
	PrintLineSeparator();

	wcout << L"IS PRIME 11 - VALUE [" << IsPrime(11) << L"]." << endl;

	wcout << L"IS PRIME 10 - VALUE [" << IsPrime(10) << L"]." << endl;

	wcout << L"IS PRIME 9 - VALUE [" << IsPrime(9) << L"]." << endl;

	wcout << L"IS PRIME 8 - VALUE [" << IsPrime(8) << L"]." << endl;

	wcout << L"IS PRIME 7 - VALUE [" << IsPrime(7) << L"]." << endl;

	wcout << L"IS PRIME 6 - VALUE [" << IsPrime(6) << L"]." << endl;

	wcout << L"IS PRIME 5 - VALUE [" << IsPrime(5) << L"]." << endl;

	wcout << L"IS PRIME 4 - VALUE [" << IsPrime(4) << L"]." << endl;

	wcout << L"IS PRIME 3 - VALUE [" << IsPrime(3) << L"]." << endl;

	wcout << L"IS PRIME 2 - VALUE [" << IsPrime(2) << L"]." << endl;

	wcout << L"IS PRIME 1 - VALUE [" << IsPrime(1) << L"]." << endl;

	wcout << L"IS PRIME 0 - VALUE [" << IsPrime(0) << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
constexpr int CalculateValue(int Value1, int Value2)
{
	if (Value2==0)
	{
		throw(CException(L"VALUE [Value2] MUST NOT be 0."));
	}

	int															Result=(Value1/Value2);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
constexpr int													VALUE_1=CalculateValue(50,10);
constexpr int													VALUE_2=CalculateValue(50,5);
// !!!!! COMPILER hodi ERROR, pretoze FUNCTION s KEYWORD [constexpr] hodila EXCEPTION.
//constexpr int													VALUE_3=CalculateValue(50,0);
//----------------------------------------------------------------------------------------------------------------------
void TestConstExprFunctionThrowingExceptions(void)
{
	PrintLineSeparator();

	wcout << L"VALUE 1 - VALUE [" << VALUE_1 << L"]." << endl;

	wcout << L"VALUE 2 - VALUE [" << VALUE_2 << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCompileTimePartialSpecializations(void)
{
	PrintLineSeparator();

	{
		CCompileTimePartialSpecializations<10>					Value;

		Value.Print();
	}

	PrintLineSeparator();

	{
		CCompileTimePartialSpecializations<11>					Value;

		Value.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, unsigned int SIZE>
size_t FunctionSFINAE1(TType(&)[SIZE])
{
	wcout << L"METHOD [size_t FunctionSFINAE1(TType(&)[SIZE])] is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] and SIZE [" << SIZE << L"] !" << endl;

	return(SIZE);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
typename TType::TYPE FunctionSFINAE1(const TType& Value)
{
	typename TType::TYPE										Result=Value.Size();

	wcout << L"METHOD [typename TType::TYPE FunctionSFINAE1(const TType& Value)] is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] !" << endl;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAE1(void)
{
	PrintLineSeparator();

	{
		int														Array[10];

		// !!!!! FUNCTION [size_t FunctionSFINAE1(TType(&)[SIZE])] VYHOVUJE.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE1(const TType& Value)] NEVYHOVUJE, lebo TYPE [int] NEMA TYPE [TYPE]. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		FunctionSFINAE1(Array);
	}

	PrintLineSeparator();

	{
		// !!!!! FUNCTION [size_t FunctionSFINAE1(TType(&)[SIZE])] VYHOVUJE.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE1(const TType& Value)] NEVYHOVUJE, lebo TYPE [wchar_t] NEMA TYPE [TYPE]. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		FunctionSFINAE1(L"Timmy");
	}

	PrintLineSeparator();

	{
		CClassWithUsingTypeWithMethodSize						Object;

		// !!!!! FUNCTION [size_t FunctionSFINAE1(TType(&)[SIZE])] NEVYHOVUJE, pretoze sa NEJEDNA o C-ARRAY. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE1(const TType& Value)] VYHOVUJE, lebo TYPE [CClassWithUsingTypeWithMethodSize] MA TYPE [TYPE].
		// !!!!! COMPILER NEHODI ERROR, pretoze TYPE [CClassWithUsingTypeWithMethodSize] ma aj METHOD [size_t Size(void) const], ktora sa vola v BODY TEMPLATE METHOD.
		FunctionSFINAE1(Object);
	}

	/*
	PrintLineSeparator();

	{
		CClassNoUsingTypeNoMethodSize							Object;

		// !!!!! FUNCTION [size_t FunctionSFINAE1(TType(&)[SIZE])] NEVYHOVUJE, pretoze sa NEJEDNA o C-ARRAY. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE1(const TType& Value)] NEVYHOVUJE, lebo TYPE [CClassNoUsingTypeNoMethodSize] NEMA TYPE [TYPE]. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! COMPILER hodi ERROR, pretoze sa NENASLA vhodna OVERLOADED FUNCTION.
		FunctionSFINAE1(Object);
	}
	*/

	/*
	PrintLineSeparator();

	{
		CClassWithUsingTypeNoMethodSize							Object;

		// !!!!! FUNCTION [size_t FunctionSFINAE1(TType(&)[SIZE])] NEVYHOVUJE, pretoze sa NEJEDNA o C-ARRAY. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE1(const TType& Value)] VYHOVUJE, lebo TYPE [CClassWithUsingTypeNoMethodSize] MA TYPE [TYPE].
		// !!!!! COMPILER HODI ERROR, pretoze TYPE [CClassWithUsingTypeNoMethodSize] NEMA METHOD [size_t Size(void) const], ktora sa vola v BODY TEMPLATE METHOD.
		FunctionSFINAE1(Object);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, unsigned int SIZE>
size_t FunctionSFINAE2(TType(&)[SIZE])
{
	wcout << L"METHOD [size_t FunctionSFINAE2(TType(&)[SIZE])] is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] and SIZE [" << SIZE << L"] !" << endl;

	return(SIZE);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
typename TType::TYPE FunctionSFINAE2(const TType& Value)
{
	typename TType::TYPE										Result=Value.Size();

	wcout << L"METHOD [typename TType::TYPE FunctionSFINAE2(const TType& Value)] is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] !" << endl;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FALLBACK FUNCTION, ktora moze byt volana pre lubovolne PARAMETERS.
size_t FunctionSFINAE2(...)
{
	wcout << L"METHOD [size_t FunctionSFINAE2(...)] is CALLED !" << endl;

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAE2(void)
{
	PrintLineSeparator();

	{
		int														Array[10];

		// !!!!! FUNCTION [size_t FunctionSFINAE2(TType(&)[SIZE])] VYHOVUJE.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE2(const TType& Value)] NEVYHOVUJE, lebo TYPE [int] NEMA TYPE [TYPE]. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! FUNCTION [size_t FunctionSFINAE2(...)] VYHOVUJE.
		// !!!!! COMPILER vyberie FUNCTION [size_t FunctionSFINAE2(TType(&)[SIZE])], pretoze je lepsi MATCH ako FUNCTION [size_t FunctionSFINAE2(...)].
		FunctionSFINAE2(Array);
	}

	PrintLineSeparator();

	{
		// !!!!! FUNCTION [size_t FunctionSFINAE2(TType(&)[SIZE])] VYHOVUJE.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE2(const TType& Value)] NEVYHOVUJE, lebo TYPE [wchar_t] NEMA TYPE [TYPE]. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! FUNCTION [size_t FunctionSFINAE2(...)] VYHOVUJE.
		// !!!!! COMPILER vyberie FUNCTION [size_t FunctionSFINAE2(TType(&)[SIZE])], pretoze je lepsi MATCH ako FUNCTION [size_t FunctionSFINAE2(...)].
		FunctionSFINAE2(L"Timmy");
	}

	PrintLineSeparator();

	{
		CClassWithUsingTypeWithMethodSize						Object;

		// !!!!! FUNCTION [size_t FunctionSFINAE2(TType(&)[SIZE])] NEVYHOVUJE, pretoze sa NEJEDNA o C-ARRAY. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE2(const TType& Value)] VYHOVUJE, lebo TYPE [CClassWithUsingTypeWithMethodSize] MA TYPE [TYPE].
		// !!!!! FUNCTION [size_t FunctionSFINAE2(...)] VYHOVUJE.
		// !!!!! COMPILER vyberie FUNCTION [typename TType::size_type FunctionSFINAE2(const TType& Value)], pretoze je lepsi MATCH ako FUNCTION [size_t FunctionSFINAE2(...)].
		// !!!!! COMPILER NEHODI ERROR, pretoze TYPE [CClassWithUsingTypeWithMethodSize] ma aj METHOD [size_t Size(void) const], ktora sa vola v BODY TEMPLATE METHOD.
		FunctionSFINAE2(Object);
	}

	PrintLineSeparator();

	{
		CClassNoUsingTypeNoMethodSize							Object;

		// !!!!! FUNCTION [size_t FunctionSFINAE2(TType(&)[SIZE])] NEVYHOVUJE, pretoze sa NEJEDNA o C-ARRAY. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE2(const TType& Value)] NEVYHOVUJE, lebo TYPE [CClassNoUsingTypeNoMethodSize] NEMA TYPE [TYPE]. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! FUNCTION [size_t FunctionSFINAE2(...)] VYHOVUJE.
		// !!!!! COMPILER vyberie FUNCTION [size_t FunctionSFINAE2(...)], kedze je to jediny MATCH.
		FunctionSFINAE2(Object);
	}

	/*
	PrintLineSeparator();

	{
		CClassWithUsingTypeNoMethodSize							Object;

		// !!!!! FUNCTION [size_t FunctionSFINAE2(TType(&)[SIZE])] NEVYHOVUJE, pretoze sa NEJEDNA o C-ARRAY. Vdaka SFINAE COMPILER NEGENERUJE ERROR.
		// !!!!! FUNCTION [typename TType::size_type FunctionSFINAE2(const TType& Value)] VYHOVUJE, lebo TYPE [CClassWithUsingTypeNoMethodSize] MA TYPE [TYPE].
		// !!!!! FUNCTION [size_t FunctionSFINAE2(...)] VYHOVUJE.
		// !!!!! COMPILER vyberie FUNCTION [typename TType::size_type FunctionSFINAE2(const TType& Value)], pretoze je lepsi MATCH ako FUNCTION [size_t FunctionSFINAE2(...)].
		// !!!!! COMPILER HODI ERROR, pretoze TYPE [CClassWithUsingTypeNoMethodSize] NEMA METHOD [size_t Size(void) const], ktora sa vola v BODY TEMPLATE METHOD.
		FunctionSFINAE2(Object);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!! FUNCTION je mozne volat IBA pre TYPE [int].
template<typename TType,typename=enable_if<(is_same<TType,int>::value==true),void>::type>
void FunctionSFINAEAndOverloadError(TType Value)
{
	wcout << L"METHOD [void FunctionSFINAEAndOverloadError(TType Value)] with (ENABLE_IF for TYPE [int]) is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] and VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION je mozne volat IBA pre lubovolny TYPE okrem TYPE [int].
// !!!!! COMPILER hodi ERROR, pretoze ako sa 2 TEMPLATE FUNCTIONS lisia iba v ine DEFAULT VALUE TEMPLATE PARAMETER, tak 2. DEFINITION TEMPLATE FUNCTION povazovana za REDEFINITION.
template<typename TType,typename=enable_if<!is_same<TType,int>::value,void>::type>
void FunctionSFINAEAndOverloadError(TType Value)
{
	wcout << L"METHOD [void FunctionSFINAEAndOverloadError(TType Value)] with (ENABLE_IF for OTHER than TYPE [int]) is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] and VALUE [" << Value << L"] !" << endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION je mozne volat IBA pre TYPE [int].
template<typename TType,typename=enable_if<(is_same<TType,int>::value==true),void>::type>
void FunctionSFINAEAndOverload1(TType Value)
{
	wcout << L"METHOD [void FunctionSFINAEAndOverload1(TType Value)] with (ENABLE_IF for TYPE [int]) is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] and VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION je mozne volat IBA pre lubovolny TYPE okrem TYPE [int].
// !!!!! COMPILER NEHODI ERROR, pretoze tato verzia TEMPLATE FUNCTION ma 3 TEMPLATE PARAMETERS, kym predosla len 2 TEMPLATE PARAMETERS, a tak ich COMPILER povazuje za rozdielne.
template<typename TType,typename=void,typename=enable_if<!is_same<TType,int>::value,void>::type>
void FunctionSFINAEAndOverload1(TType Value)
{
	wcout << L"METHOD [void FunctionSFINAEAndOverload1(TType Value)] with (ENABLE_IF for OTHER than TYPE [int]) is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] and VALUE [" << Value << L"] !" << endl;
}

//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION je mozne volat IBA pre TYPE [int].
// !!!!! COMPILER NEHODI ERROR.
template<typename TType,enable_if<(is_same<TType,int>::value==true),bool>::type = true>
void FunctionSFINAEAndOverload2(TType Value)
{
	wcout << L"METHOD [void FunctionSFINAEAndOverload2(TType Value)] with (ENABLE_IF for TYPE [int]) is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] and VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION je mozne volat IBA pre lubovolny TYPE okrem TYPE [int].
// !!!!! COMPILER NEHODI ERROR.
template<typename TType,enable_if<(is_same<TType,int>::value==false),bool>::type = true>
void FunctionSFINAEAndOverload2(TType Value)
{
	wcout << L"METHOD [void FunctionSFINAEAndOverload2(TType Value)] with (ENABLE_IF for OTHER than TYPE [int]) is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] and VALUE [" << Value << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAEAndOverload(void)
{
	PrintLineSeparator();

	/*
	// !!!!! COMPILER hodi ERROR, pretoze 2 DEFINITIONS FUNCTION [void FunctionSFINAEAndOverloadError(TType Value)] sa lisia iba v DEFAULT VALUE TEMPLATE PARAMETER a tak 2. DEFINITION tejto FUNCTION povazuje COMPILER za jej REDEFINITION a hodi ERROR.
	{
		int														Value=10;

		FunctionSFINAEAndOverloadError(Value);
	}

	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze 2 DEFINITIONS FUNCTION [void FunctionSFINAEAndOverloadError(TType Value)] sa lisia iba v DEFAULT VALUE TEMPLATE PARAMETER a tak 2. DEFINITION tejto FUNCTION povazuje COMPILER za jej REDEFINITION a hodi ERROR.
	{
		double													Value=10.22;

		FunctionSFINAEAndOverloadError(Value);
	}

	PrintLineSeparator();
	*/

	// !!!!! COMPILER zbehne OK, pretoze 2 DEFINITIONS FUNCTION [void FunctionSFINAEAndOverloadError(TType Value)] sa lisia v pocte TEMPLATE PARAMETERS.
	{
		int														Value=10;

		FunctionSFINAEAndOverload1(Value);
	}

	PrintLineSeparator();

	// !!!!! COMPILER zbehne OK, pretoze 2 DEFINITIONS FUNCTION [void FunctionSFINAEAndOverloadError(TType Value)] sa lisia v pocte TEMPLATE PARAMETERS.
	{
		double													Value=10.22;

		FunctionSFINAEAndOverload1(Value);
	}

	PrintLineSeparator();

	// !!!!! COMPILER zbehne OK.
	{
		int														Value=10;

		FunctionSFINAEAndOverload2(Value);
	}

	PrintLineSeparator();

	// !!!!! COMPILER zbehne OK.
	{
		double													Value=10.22;

		FunctionSFINAEAndOverload2(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION je volana iba pre TYPES, ktore maju definovany TYPE [TYPE] a zaroven maju definovanu METHOD [size_t Size(void) const].
template<typename TType>
// !!!!! V KEYWORD [decltype] su pred OPERATOR [OPERATOR,] definovane CONSTRAINTS, ktore musi TYPE [TType] splnat.
// !!!!! V KEYWORD [decltype] ZA OPERATOR [OPERATOR,] je definovany EXPRESSION (nie TYPE), ktoreho TYPE sa stane RETURN VALUE TYPE.
// !!!!! CONVERSION na TYPE [void] pre EXPRESSIONS na LAVEJ strane OPERATOR [OPERATOR,] sa robi preto, aby sa nevolal USER DEFINED OPERATOR [OPERATOR,], ak by nahodou bolo definovany.
auto FunctionSFINAEConditionsTesting1(TType Value) -> decltype((void)(Value.Size()),typename TType::TYPE())
{
	typename TType::TYPE										Result=Value.Size();

	wcout << L"METHOD [auto FunctionSFINAEConditionsTesting1(TType Value) -> decltype((void)(Value.Size()),TType::TYPE())] is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] !" << endl;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION je volana iba pre TYPES, ktore maju definovany TYPE [TYPE] a zaroven maju definovanu METHOD [size_t Size(void) const].
template<typename TType>
// !!!!! V KEYWORD [decltype] su pred OPERATOR [OPERATOR,] definovane CONSTRAINTS, ktore musi TYPE [TType] splnat.
// !!!!! V KEYWORD [decltype] ZA OPERATOR [OPERATOR,] je definovany EXPRESSION (nie TYPE), ktoreho TYPE sa stane RETURN VALUE TYPE.
// !!!!! CONVERSION na TYPE [void] pre EXPRESSIONS na LAVEJ strane OPERATOR [OPERATOR,] sa robi preto, aby sa nevolal USER DEFINED OPERATOR [OPERATOR,], ak by nahodou bolo definovany.
auto FunctionSFINAEConditionsTesting2(TType Value) -> decltype((void)(TType{}.Size()),typename TType::TYPE())
{
	typename TType::TYPE										Result=Value.Size();

	wcout << L"METHOD [auto FunctionSFINAEConditionsTesting2(TType Value) -> decltype((void)(TType{}.Size()),TType::TYPE())] is CALLED for TYPE [" << GetTypeInfoName<TType>() << L"] !" << endl;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAEConditionsTesting(void)
{
	PrintLineSeparator();

	{
		CClassWithUsingTypeWithMethodSize						Object;

		FunctionSFINAEConditionsTesting1(Object);
	}

	PrintLineSeparator();

	{
		CClassWithUsingTypeWithMethodSize						Object;

		FunctionSFINAEConditionsTesting2(Object);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TThis, typename... TTypes>
void TemplateTestConstExprIfInVariadicTemplates(TThis This, TTypes... Others)
{
	wcout << L"VALUE [" << This << L"] !" << endl;

	// !!!!! Ak EXPRESSION je TRUE, tak sa SKOMPILUJE IBA IF BRANCH a ak FALSE, tak sa SKOMPILUJE IBA ELSE BRANCH.
	if constexpr (sizeof...(TTypes)>0)
	{
		TemplateTestConstExprIfInVariadicTemplates(Others...);
	}
	else
	{
		wcout << L"END of RECURSION !" << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestConstExprIfInVariadicTemplates(void)
{
	PrintLineSeparator();

	TemplateTestConstExprIfInVariadicTemplates(L"Timmy",L"Anderson",12);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestConstExprIfChecks(void)
{
	PrintLineSeparator();

	if constexpr (true)
	{
		wcout << L"HELLO !" << endl;
	}
	else
	{
		/*
		// !!! COMPILER hodi ERROR, pretoze aj ked ELSE BLOCK je VYHODENY z PROGRAMU, tak sa vykonava SYNTAX a SEMANTIC CHECK.
		{
			CNotDefinedType										Object;

			Object.Print();
		}
		*/

		static_assert(true,"There is some ERROR 1 !");

		/*
		// !!! COMPILER hodi ERROR, pretoze aj ked ELSE BLOCK je VYHODENY, KEYWORD [static_assert] sa aj v tomto BLOCK kontroluje.
		static_assert(false,"There is some ERROR 2 !");
		*/
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
constexpr bool FunctionConstExprIfInNonTemplateFunction(unsigned int Number)
{
	for (unsigned int Divisor=2;Divisor<=(Number/2);++Divisor)
	{
		if ((Number % Divisor)==0)
		{
			return(false);
		}
	}

	return(Number>1);
}
//----------------------------------------------------------------------------------------------------------------------
void TestConstExprIfInNonTemplateFunction(void)
{
	PrintLineSeparator();

	{
		// !!! Kedze FUNCTION [constexpr bool FunctionConstExprIfInNonTemplateFunction(unsigned int Number)] je oznacena pomocou KEYWORD [constexpr] je ju mozne pouzit v CONSTEXPRESSION IF.
		if constexpr (FunctionConstExprIfInNonTemplateFunction(11)==true)
		{
			wcout << L"NUMBER 11 is a PRIME." << endl;
		}
		else
		{
			wcout << L"NUMBER 11 is NOT a PRIME." << endl;
		}
	}

	PrintLineSeparator();

	{
		// !!! Kedze FUNCTION [constexpr bool FunctionConstExprIfInNonTemplateFunction(unsigned int Number)] je oznacena pomocou KEYWORD [constexpr] je ju mozne pouzit v CONSTEXPRESSION IF.
		if constexpr (FunctionConstExprIfInNonTemplateFunction(10)==true)
		{
			wcout << L"NUMBER 10 is a PRIME." << endl;
		}
		else
		{
			wcout << L"NUMBER 10 is NOT a PRIME." << endl;
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

	//TestCompileProgrammingNoConstExpr();
	//TestCompileProgrammingConstExpr();
	//TestConstExprFunctionThrowingExceptions();
	//TestCompileTimePartialSpecializations();
	//TestSFINAE1();
	//TestSFINAE2();
	//TestSFINAEAndOverload();
	TestSFINAEConditionsTesting();
	//TestConstExprIfInVariadicTemplates();
	//TestConstExprIfChecks();
	//TestConstExprIfInNonTemplateFunction();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------