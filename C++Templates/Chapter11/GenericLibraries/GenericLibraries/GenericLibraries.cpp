//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include <utility>
#include <type_traits>
#include <vector>
#include "MyDebug.h"
#include "CFunctionObjectTypeOperator.h"
#include "CFunctionObjectTypeConversionToReferenceToFunction.h"
#include "CFunctionObjectTypeConversionToPointerToFunction.h"
#include "CFunctionObjectTypeNonStaticMethod.h"
#include "CClassWithCopyAndMoveSemantics.h"
#include "CAddressOf.h"
#include "CDeclvalConstructible.h"
#include "CDeclvalNonConstructible.h"
#include "CDeferEvalution.h"
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
// !!! TEMPLATE prijima ako 2. TEMPLATE PARAMETER CALLABLE OBJECT.
template<typename TIterator, typename TCallable>
void TemplateCallableObjects(TIterator Begin, TIterator End, TCallable Callable)
{
	wcout << "CALLABLE TYPE [" << GetTypeInfoName<TCallable>() << L"]." << endl;

	size_t														Index=1;

	for(TIterator Iterator=Begin;Iterator!=End;++Iterator,++Index)
	{
		// !!! Vola sa CALLABLE OBJECT s 2 PARAMETERS.
		Callable(Index,*Iterator);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void FunctionObjectTypeFunction(size_t Index, double Value)
{
	wcout << L"FUNCTION - INDEX [" << Index << "] VALUE [" << Value << "]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCallableObjects(void)
{
	PrintLineSeparator();

	vector<double>												Numbers({11.11,22.22,33.33});

	{
		// !!! CALLABLE TYPE NIE JE POINTER na FUNCTION TYPE, ani REFERENCE na FUNCTION TYPE, ale FUNCTION TYPE.
		wcout << "MAIN - CALLABLE TYPE [" << GetTypeInfoName<decltype(FunctionObjectTypeFunction)>() << L"]." << endl;

		// !!! Ako FUNCTION OBJECT je pouzity FUNCTION TYPE.
		// !!!!! FUNCTION TYPE je AUTOMATICKY DECAYED na POINTER NA FUNCTION TYPE.
		TemplateCallableObjects(Numbers.cbegin(),Numbers.cend(),FunctionObjectTypeFunction);
	}

	PrintLineSeparator();

	{
		// !!! CALLABLE TYPE JE POINTER na FUNCTION TYPE.
		wcout << "MAIN - CALLABLE TYPE [" << GetTypeInfoName<decltype(&FunctionObjectTypeFunction)>() << L"]." << endl;

		// !!! Ako FUNCTION OBJECT je pouzity POINTER na FUNCTION TYPE.
		TemplateCallableObjects(Numbers.cbegin(),Numbers.cend(),&FunctionObjectTypeFunction);
	}

	PrintLineSeparator();

	{
		using													CallableType=void(&)(size_t Index, double Value);

		CallableType											Callback=FunctionObjectTypeFunction;

		wcout << "MAIN - CALLABLE TYPE [" << GetTypeInfoName<CallableType>() << L"]." << endl;

		// !!! Ako FUNCTION OBJECT je pouzity REFERENCE na FUNCTION TYPE.
		// !!!!! REFERENCE na FUNCTION TYPE je AUTOMATICKY DECAYED na POINTER NA FUNCTION TYPE.
		TemplateCallableObjects(Numbers.cbegin(),Numbers.cend(),Callback);
	}

	PrintLineSeparator();

	{
		CFunctionObjectTypeOperator								Callback;

		// !!! Ako FUNCTION OBJECT je pouzity FUNCTION OBJECT implementujuci OPERATOR [OPERATOR()].
		TemplateCallableObjects(Numbers.cbegin(),Numbers.cend(),Callback);
	}

	PrintLineSeparator();

	{
		CFunctionObjectTypeConversionToReferenceToFunction		Callback;

		// !!! Ako FUNCTION OBJECT je pouzity FUNCTION OBJECT implementujuci CONVERSION OPERATOR TO REFERENCE TO FUNCTION.
		TemplateCallableObjects(Numbers.cbegin(),Numbers.cend(),Callback);
	}

	PrintLineSeparator();

	{
		CFunctionObjectTypeConversionToPointerToFunction		Callback;

		// !!! Ako FUNCTION OBJECT je pouzity FUNCTION OBJECT implementujuci CONVERSION OPERATOR TO POINTER TO FUNCTION.
		TemplateCallableObjects(Numbers.cbegin(),Numbers.cend(),Callback);
	}

	PrintLineSeparator();

	{
		auto													Callback=[](size_t Index, double Value)
		{
			wcout << L"LAMBDA FUNCTION - INDEX [" << Index << "] VALUE [" << Value << "]." << endl;
		};

		// !!! Ako FUNCTION OBJECT je pouzita LAMBDA FUNCTION.
		TemplateCallableObjects(Numbers.cbegin(),Numbers.cend(),Callback);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE prijima ako 2. TEMPLATE PARAMETER CALLABLE OBJECT.
// !!!!! Ak je CALLABLE OBJECT NON-STATIC METHOD, tak 1. PARAMETER v TEMPLATE PARAMETER 'TArguments' musi byt THIS POINTER.
template<typename TIterator, typename TCallable, typename... TArguments>
void TemplateCallableObjectsNonStaticMethods1(TIterator Begin, TIterator End, TCallable Callable, TArguments... Arguments)
{
	wcout << "CALLABLE TYPE [" << GetTypeInfoName<TCallable>() << L"]." << endl;

	size_t														Index=1;

	for(TIterator Iterator=Begin;Iterator!=End;++Iterator,++Index)
	{
		// !!!!! Pomocou TEMPLATE FUNCTION [invoke()] sa vola CALLABLE OBJECT, ktory moze byt bud NON-STATIC METHOD, alebo aj lubovolny iny CALLABLE OBJECT.
		int														Result=invoke(Callable,Arguments...,Index,*Iterator);

		wcout << "RESULT - INDEX [" << Index << L"] RETURN VALUE [" << Result << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE prijima ako 2. TEMPLATE PARAMETER CALLABLE OBJECT.
// !!!!! Ak je CALLABLE OBJECT NON-STATIC METHOD, tak 1. PARAMETER v TEMPLATE PARAMETER 'TArguments' musi byt THIS POINTER.
template<typename TIterator, typename TCallable, typename... TArguments>
void TemplateCallableObjectsNonStaticMethods2(TIterator Begin, TIterator End, TCallable Callable, TArguments... Arguments)
{
	wcout << "CALLABLE TYPE [" << GetTypeInfoName<TCallable>() << L"]." << endl;

	size_t														Index=1;

	for(TIterator Iterator=Begin;Iterator!=End;++Iterator,++Index)
	{
		// !!!!! Pomocou TEMPLATE FUNCTION [invoke_r()] sa vola CALLABLE OBJECT, ktory moze byt bud NON-STATIC METHOD, alebo aj lubovolny iny CALLABLE OBJECT.
		double													Result=invoke_r<double>(Callable,Arguments...,Index,*Iterator);

		wcout << "RESULT - INDEX [" << Index << L"] RETURN VALUE [" << Result << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
int FunctionObjectCallableObjectsNonStaticMethods(wstring Value1, wstring Value2, size_t Index, double Value)
{
	wcout << L"FUNCTION - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] INDEX [" << Index << "] VALUE [" << Value << "]." << endl;

	return(300);
}
//----------------------------------------------------------------------------------------------------------------------
void TestCallableObjectsNonStaticMethods(void)
{
	PrintLineSeparator();

	vector<double>												Numbers({11.11,22.22,33.33});

	{
		// !!!!! Ako FUNCTION OBJECT je pouzita FUNCTION.
		TemplateCallableObjectsNonStaticMethods1(Numbers.cbegin(),Numbers.cend(),FunctionObjectCallableObjectsNonStaticMethods,L"Timmy",L"Anderson");
	}

	PrintLineSeparator();

	{
		CFunctionObjectTypeNonStaticMethod						Callback(888);

		// !!!!! Ako FUNCTION OBJECT je pouzita NON-STATIC METHOD.
		// !!!!! Ako 1. PARAMETER v TEMPLATE PARAMETER 'TArguments' MUSI byt pouziti THIS OBJECT 'Callback'.
		TemplateCallableObjectsNonStaticMethods1(Numbers.cbegin(),Numbers.cend(),&CFunctionObjectTypeNonStaticMethod::NonStaticMethod,&Callback,L"Timmy",L"Anderson");
	}

	PrintLineSeparator();

	{
		// !!!!! Ako FUNCTION OBJECT je pouzita FUNCTION.
		TemplateCallableObjectsNonStaticMethods2(Numbers.cbegin(),Numbers.cend(),FunctionObjectCallableObjectsNonStaticMethods,L"Timmy",L"Anderson");
	}

	PrintLineSeparator();

	{
		CFunctionObjectTypeNonStaticMethod						Callback(999);

		// !!!!! Ako FUNCTION OBJECT je pouzita NON-STATIC METHOD.
		// !!!!! Ako 1. PARAMETER v TEMPLATE PARAMETER 'TArguments' MUSI byt pouziti THIS OBJECT 'Callback'.
		TemplateCallableObjectsNonStaticMethods2(Numbers.cbegin(),Numbers.cend(),&CFunctionObjectTypeNonStaticMethod::NonStaticMethod,&Callback,L"Timmy",L"Anderson");
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION vola CALLABLE OBJECT, pricom NEVYKONAVA PERFECT FORWARDING.
template<typename TCallable, typename... TArguments>
decltype(auto) TemplateCallableObjectsWithNoPerfectForwarding1(TCallable Callable, TArguments... Arguments)
{
	return(invoke(Callable,Arguments...));
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION vola CALLABLE OBJECT, pricom NEVYKONAVA PERFECT FORWARDING.
template<typename TCallable, typename... TArguments>
decltype(auto) TemplateCallableObjectsWithNoPerfectForwarding2(TCallable Callable, TArguments... Arguments)
{
	// !!! Vykona sa TEST ci CALLABLE OBJECT vracia RETURN VALUE.
	if constexpr ((is_same<typename invoke_result<TCallable,TArguments...>::type,void>::value)==false)
	{
		decltype(auto)											ReturnValue=invoke(Callable,Arguments...);

		wcout << L"TEMPLATE FUNCTION - RETURN VALUE [" << ReturnValue << L"]." << endl;

		// !!!!! KEYWORD [return ReturnValue] NESMIE byt OBALENY ZATVORKAMI [()].
		return ReturnValue;

		// !!!!! Ak by sa pouzil CODE [return(ReturnValue)], tak KEYWORD [decltype(auto)] vykona CODE [decltype((TYPE))] co vedie k vrateniu nie TYPE EXPRESSION 'ReturnValue', ale VALUE CATEGORY. No a kedze VALUE CATEGORY pre CODE [decltype((TYPE))] je TYPE [TYPE&], tak FUNCTION by NESPRAVNE vracala REFERENCE na LOCAL VARIABLE.
		//return(ReturnValue);
	}
	else
	{
		invoke(Callable,Arguments...);

		wcout << L"TEMPLATE FUNCTION - NO RETURN VALUE." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void FunctionCallableObjectsWithNoPerfectForwarding1(const CClassWithCopyAndMoveSemantics& Value1, const CClassWithCopyAndMoveSemantics& Value2)
{
	wcout << L"FUNCTION - VALUE 1->FIELD 1 [" << Value1.GetField1() << L"] VALUE 1->FIELD 2 [" << Value2.GetField2() << L"] VALUE 2->FIELD 1 [" << Value1.GetField1() << "] VALUE 2->FIELD 2 [" << Value2.GetField2() << "]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
int FunctionCallableObjectsWithNoPerfectForwarding2(const CClassWithCopyAndMoveSemantics& Value1, const CClassWithCopyAndMoveSemantics& Value2)
{
	wcout << L"FUNCTION - VALUE 1->FIELD 1 [" << Value1.GetField1() << L"] VALUE 1->FIELD 2 [" << Value2.GetField2() << L"] VALUE 2->FIELD 1 [" << Value1.GetField1() << "] VALUE 2->FIELD 2 [" << Value2.GetField2() << "]." << endl;

	return(999);
}
//----------------------------------------------------------------------------------------------------------------------
void TestCallableObjectsWithNoPerfectForwarding(void)
{
	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		TemplateCallableObjectsWithNoPerfectForwarding1(&FunctionCallableObjectsWithNoPerfectForwarding1,Object1,Object2);
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		int														ReturnValue=TemplateCallableObjectsWithNoPerfectForwarding1(&FunctionCallableObjectsWithNoPerfectForwarding2,Object1,Object2);

		wcout << L"MAIN - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		TemplateCallableObjectsWithNoPerfectForwarding2(&FunctionCallableObjectsWithNoPerfectForwarding1,Object1,Object2);
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		int														ReturnValue=TemplateCallableObjectsWithNoPerfectForwarding2(&FunctionCallableObjectsWithNoPerfectForwarding2,Object1,Object2);

		wcout << L"MAIN - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION vola CALLABLE OBJECT, pricom vykonava PERFECT FORWARDING.
template<typename TCallable, typename... TArguments>
decltype(auto) TemplateCallableObjectsWithPerfectForwardingInvoke1(TCallable&& Callable, TArguments&&... Arguments)
{
	return(invoke(forward<TCallable>(Callable),forward<TArguments>(Arguments)...));
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION vola CALLABLE OBJECT, pricom vykonava PERFECT FORWARDING.
template<typename TCallable, typename... TArguments>
decltype(auto) TemplateCallableObjectsWithPerfectForwardingInvoke2(TCallable&& Callable, TArguments&&... Arguments)
{
	// !!! Vykona sa TEST ci CALLABLE OBJECT vracia RETURN VALUE.
	if constexpr ((is_same<typename invoke_result<TCallable,TArguments...>::type,void>::value)==false)
	{
		decltype(auto)											ReturnValue=invoke(forward<TCallable>(Callable),forward<TArguments>(Arguments)...);

		wcout << L"TEMPLATE FUNCTION - RETURN VALUE [" << ReturnValue << L"]." << endl;

		// !!!!! KEYWORD [return ReturnValue] NESMIE byt OBALENY ZATVORKAMI [()].
		return ReturnValue;

		// !!!!! Ak by sa pouzil CODE [return(ReturnValue)], tak KEYWORD [decltype(auto)] vykona CODE [decltype((TYPE))] co vedie k vrateniu nie TYPE EXPRESSION 'ReturnValue', ale VALUE CATEGORY. No a kedze VALUE CATEGORY pre CODE [decltype((TYPE))] je TYPE [TYPE&], tak FUNCTION by NESPRAVNE vracala REFERENCE na LOCAL VARIABLE.
		//return(ReturnValue);
	}
	else
	{
		invoke(forward<TCallable>(Callable),forward<TArguments>(Arguments)...);

		wcout << L"TEMPLATE FUNCTION - NO RETURN VALUE." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void FunctionCallableObjectsWithPerfectForwardingInvoke1(const CClassWithCopyAndMoveSemantics& Value1, const CClassWithCopyAndMoveSemantics& Value2)
{
	wcout << L"FUNCTION - VALUE 1->FIELD 1 [" << Value1.GetField1() << L"] VALUE 1->FIELD 2 [" << Value2.GetField2() << L"] VALUE 2->FIELD 1 [" << Value1.GetField1() << "] VALUE 2->FIELD 2 [" << Value2.GetField2() << "]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
int FunctionCallableObjectsWithPerfectForwardingInvoke2(const CClassWithCopyAndMoveSemantics& Value1, const CClassWithCopyAndMoveSemantics& Value2)
{
	wcout << L"FUNCTION - VALUE 1->FIELD 1 [" << Value1.GetField1() << L"] VALUE 1->FIELD 2 [" << Value2.GetField2() << L"] VALUE 2->FIELD 1 [" << Value1.GetField1() << "] VALUE 2->FIELD 2 [" << Value2.GetField2() << "]." << endl;

	return(999);
}
//----------------------------------------------------------------------------------------------------------------------
void TestCallableObjectsWithPerfectForwardingInvoke(void)
{
	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		TemplateCallableObjectsWithPerfectForwardingInvoke1(&FunctionCallableObjectsWithPerfectForwardingInvoke1,Object1,Object2);
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		int														ReturnValue=TemplateCallableObjectsWithPerfectForwardingInvoke1(&FunctionCallableObjectsWithPerfectForwardingInvoke2,Object1,Object2);

		wcout << L"MAIN - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		TemplateCallableObjectsWithPerfectForwardingInvoke2(&FunctionCallableObjectsWithPerfectForwardingInvoke1,Object1,Object2);
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		int														ReturnValue=TemplateCallableObjectsWithPerfectForwardingInvoke2(&FunctionCallableObjectsWithPerfectForwardingInvoke2,Object1,Object2);

		wcout << L"MAIN - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION vola CALLABLE OBJECT, pricom vykonava PERFECT FORWARDING.
template<typename TReturnValue, typename TCallable, typename... TArguments>
TReturnValue TemplateCallableObjectsWithPerfectForwardingInvokeReturnValue1(TCallable&& Callable, TArguments&&... Arguments)
{
	return(invoke_r<TReturnValue>(forward<TCallable>(Callable),forward<TArguments>(Arguments)...));
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION vola CALLABLE OBJECT, pricom vykonava PERFECT FORWARDING.
template<typename TReturnValue, typename TCallable, typename... TArguments>
TReturnValue TemplateCallableObjectsWithPerfectForwardingInvokeReturnValue2(TCallable&& Callable, TArguments&&... Arguments)
{
	// !!! Vykona sa TEST ci CALLABLE OBJECT vracia RETURN VALUE.
	if constexpr ((is_same<TReturnValue,void>::value)==false)
	{
		TReturnValue											ReturnValue=invoke_r<TReturnValue>(forward<TCallable>(Callable),forward<TArguments>(Arguments)...);

		wcout << L"TEMPLATE FUNCTION - RETURN VALUE [" << ReturnValue << L"]." << endl;

		return(ReturnValue);
	}
	else
	{
		invoke_r<TReturnValue>(forward<TCallable>(Callable),forward<TArguments>(Arguments)...);

		wcout << L"TEMPLATE FUNCTION - NO RETURN VALUE." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void FunctionCallableObjectsWithPerfectForwardingInvokeReturnValue1(const CClassWithCopyAndMoveSemantics& Value1, const CClassWithCopyAndMoveSemantics& Value2)
{
	wcout << L"FUNCTION - VALUE 1->FIELD 1 [" << Value1.GetField1() << L"] VALUE 1->FIELD 2 [" << Value2.GetField2() << L"] VALUE 2->FIELD 1 [" << Value1.GetField1() << "] VALUE 2->FIELD 2 [" << Value2.GetField2() << "]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
int FunctionCallableObjectsWithPerfectForwardingInvokeReturnValue2(const CClassWithCopyAndMoveSemantics& Value1, const CClassWithCopyAndMoveSemantics& Value2)
{
	wcout << L"FUNCTION - VALUE 1->FIELD 1 [" << Value1.GetField1() << L"] VALUE 1->FIELD 2 [" << Value2.GetField2() << L"] VALUE 2->FIELD 1 [" << Value1.GetField1() << "] VALUE 2->FIELD 2 [" << Value2.GetField2() << "]." << endl;

	return(999);
}
//----------------------------------------------------------------------------------------------------------------------
void TestCallableObjectsWithPerfectForwardingInvokeReturnValue(void)
{
	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		TemplateCallableObjectsWithPerfectForwardingInvokeReturnValue1<void>(&FunctionCallableObjectsWithPerfectForwardingInvokeReturnValue1,Object1,Object2);
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		int														ReturnValue=TemplateCallableObjectsWithPerfectForwardingInvokeReturnValue1<int>(&FunctionCallableObjectsWithPerfectForwardingInvokeReturnValue2,Object1,Object2);

		wcout << L"MAIN - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		TemplateCallableObjectsWithPerfectForwardingInvokeReturnValue2<void>(&FunctionCallableObjectsWithPerfectForwardingInvokeReturnValue1,Object1,Object2);
	}

	PrintLineSeparator();

	{
		CClassWithCopyAndMoveSemantics							Object1(100,111.111);
		CClassWithCopyAndMoveSemantics							Object2(200,222.222);

		int														ReturnValue=TemplateCallableObjectsWithPerfectForwardingInvokeReturnValue2<int>(&FunctionCallableObjectsWithPerfectForwardingInvokeReturnValue2,Object1,Object2);

		wcout << L"MAIN - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPlaceholderTypeSpecifiersInitializers(void)
{
	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE Value=100

		auto													MACRO_VALUE;

		wcout << L"CODE [auto " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE Value=(100+200)

		auto													MACRO_VALUE;

		wcout << L"CODE [auto " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE Value{100}

		auto													MACRO_VALUE;

		wcout << L"CODE [auto " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE Value{100}

		auto													MACRO_VALUE;

		wcout << L"CODE [auto " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [initializer_list<int>].
		#define													MACRO_VALUE Value={100}

		auto													MACRO_VALUE;

		wcout << L"CODE [auto " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE.SIZE [" << Value.size() << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE Value=(OriginalValue)

		auto													MACRO_VALUE;

		wcout << L"CODE [auto " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE Value=100

		decltype(auto)											MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!!!! COMPILER vrati TYPE [int], pretoze v skutocnosti nie je vrateny TYPE EXPRESSION [100], ale pri pouziti zatvoriek je pre EXPRESSION [(100)] vratena VALUE CATEGORY EXPRESSION [10], co je TYPE [int] reprezentujuci PRVALUE REFERENCE.
		#define													MACRO_VALUE Value=(100)

		decltype(auto)											MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE Value(100)

		decltype(auto)											MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE Value=OriginalValue

		decltype(auto)											MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!!!! COMPILER vrati TYPE [int&], pretoze v skutocnosti nie je vrateny TYPE EXPRESSION [OriginalValue], ale pri pouziti zatvoriek je pre EXPRESSION [(OriginalValue)] vratena VALUE CATEGORY EXPRESSION [OriginalValue], co je TYPE [int&] reprezentujuci LVALUE REFERENCE.
		#define													MACRO_VALUE Value=(OriginalValue)

		decltype(auto)											MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!!!! COMPILER vrati TYPE [int&&].
		#define													MACRO_VALUE Value=move(OriginalValue)

		decltype(auto)											MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!!!! COMPILER vrati TYPE [int&&], pretoze v skutocnosti nie je vrateny TYPE EXPRESSION [move(OriginalValue)], ale pri pouziti zatvoriek je pre EXPRESSION [(move(OriginalValue))] vratena VALUE CATEGORY EXPRESSION [move(OriginalValue)], co je TYPE [int&&] reprezentujuci RVALUE REFERENCE.
		#define													MACRO_VALUE Value=(move(OriginalValue))

		decltype(auto)											MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(Value)>() << "] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
auto FunctionPlaceholderTypeSpecifiersReturnValuesAuto1(void)
{
	// !!!!! RETURN VALUE TYPE sa urci z TYPE EXPRESSION, ktora nasleduje za KEYWORD [return], teda EXPRESSION [(100)].
	return(100);
}
//----------------------------------------------------------------------------------------------------------------------
auto FunctionPlaceholderTypeSpecifiersReturnValuesAuto2(bool Value)
{
	// !!!!! EXPRESSIONS po vsetkych vyskytoch KEYWORDS [return], vracaju ten isty TYPE [int].

	if (Value==true)
	{
		return(100);
	}
	else
	{
		return(200);
	}
}
//----------------------------------------------------------------------------------------------------------------------
/*
auto FunctionPlaceholderTypeSpecifiersReturnValuesAuto3(bool Value)
{
	// !!!!! COMPILER hodi ERROR, pretoze EXPRESSIONS po roznych vyskytoch KEYWORDS [return] vracaju INE TYPES.

	if (Value==true)
	{
		return(100);
	}
	else
	{
		return(222.222);
	}
}
*/
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto1(void)
{
	// !!!!! RETURN VALUE TYPE sa urci z EXPRESSION [decltype(EXPRESSION)], ktora nasleduje za KEYWORD [return], teda EXPRESSION [decltype(100)].
	// !!! COMPILER vrati TYPE [int].
	// !!!!! POZOR - NESMU sa pouzit ZATOVRKY [()].
	return 100;
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto2(bool Value)
{
	// !!!!! EXPRESSIONS po vsetkych vyskytoch KEYWORDS [return], vracaju ten isty TYPE [int].
	// !!! COMPILER vrati TYPE [int].

	if (Value==true)
	{
		// !!!!! POZOR - NESMU sa pouzit ZATOVRKY [()].
		return 100;
	}
	else
	{
		// !!!!! POZOR - NESMU sa pouzit ZATOVRKY [()].
		return 200;
	}
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto3()
{
	// !!!!! RETURN VALUE TYPE sa urci z EXPRESSION [decltype(EXPRESSION)], ktora nasleduje za KEYWORD [return], teda EXPRESSION [decltype((100))].
	// !!! COMPILER vrati TYPE [int].
	// !!!!! Pretoze sa pouzili ZATOVRKY [()], tak sa vyhodnocuje EXPRESSION [decltype((100))], ktora nevracia TYPE EXPRESSION [100], ale VALUE CATEGORY EXPRESSION [100] co je TYPE [int], pretoze LITERAL VALUE je PRVALUE.
	return(100);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto4(int& Value)
{
	// !!!!! RETURN VALUE TYPE sa urci z EXPRESSION [decltype(EXPRESSION)], ktora nasleduje za KEYWORD [return], teda EXPRESSION [decltype((Value))].
	// !!! COMPILER vrati TYPE [int&].
	// !!!!! Pretoze sa pouzili ZATOVRKY [()], tak sa vyhodnocuje EXPRESSION [decltype((Value))], ktora nevracia TYPE EXPRESSION [Value], ale VALUE CATEGORY EXPRESSION [Value] co je TYPE [int&].
	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
decltype(auto) FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto5(int& Value)
{
	// !!!!! RETURN VALUE TYPE sa urci z EXPRESSION [decltype(EXPRESSION)], ktora nasleduje za KEYWORD [return], teda EXPRESSION [decltype((move(Value)))].
	// !!! COMPILER vrati TYPE [int&&].
	// !!!!! Pretoze sa pouzili ZATOVRKY [()], tak sa vyhodnocuje EXPRESSION [decltype((move(Value)))], ktora nevracia TYPE EXPRESSION [move(Value)], ale VALUE CATEGORY EXPRESSION [move(Value)] co je TYPE [int&&].
	return(move(Value));
}
//----------------------------------------------------------------------------------------------------------------------
/*
decltype(auto) FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto6(int Value)
{
	// !!!!! RETURN VALUE TYPE sa urci z EXPRESSION [decltype(EXPRESSION)], ktora nasleduje za KEYWORD [return], teda EXPRESSION [decltype((Value))].
	// !!! COMPILER vrati TYPE [int&].
	// !!!!! Pretoze sa pouzili ZATOVRKY [()], tak sa vyhodnocuje EXPRESSION [decltype((Value))], ktora nevracia TYPE EXPRESSION [Value], ale VALUE CATEGORY EXPRESSION [Value] co je TYPE [int&].
	// !!!!! COMPILER hodi ERROR, pretoze NIE JE mozne vracat REFERENCE na NON-REFERENCE PARAMETER.
	return(Value);
}
*/
//----------------------------------------------------------------------------------------------------------------------
void TestPlaceholderTypeSpecifiersReturnValues(void)
{
	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE FunctionPlaceholderTypeSpecifiersReturnValuesAuto1()

		auto													ReturnValue=MACRO_VALUE;

		wcout << L"CODE [auto " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(MACRO_VALUE)>() << "] VALUE [" << ReturnValue << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE FunctionPlaceholderTypeSpecifiersReturnValuesAuto2(true)

		auto													ReturnValue=MACRO_VALUE;

		wcout << L"CODE [auto " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(MACRO_VALUE)>() << "] VALUE [" << ReturnValue << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE FunctionPlaceholderTypeSpecifiersReturnValuesAuto2(false)

		auto													ReturnValue=MACRO_VALUE;

		wcout << L"CODE [auto " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(MACRO_VALUE)>() << "] VALUE [" << ReturnValue << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto1()

		auto													ReturnValue=MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(MACRO_VALUE)>() << "] VALUE [" << ReturnValue << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto2(true)

		auto													ReturnValue=MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(MACRO_VALUE)>() << "] VALUE [" << ReturnValue << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto2(false)

		auto													ReturnValue=MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(MACRO_VALUE)>() << "] VALUE [" << ReturnValue << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		// !!! COMPILER vrati TYPE [int].
		#define													MACRO_VALUE FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto3()

		auto													ReturnValue=MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(MACRO_VALUE)>() << "] VALUE [" << ReturnValue << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!! COMPILER vrati TYPE [int&].
		#define													MACRO_VALUE FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto4(OriginalValue)

		auto													ReturnValue=MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(MACRO_VALUE)>() << "] VALUE [" << ReturnValue << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		int														OriginalValue=100;

		// !!! COMPILER vrati TYPE [int&&].
		#define													MACRO_VALUE FunctionPlaceholderTypeSpecifiersReturnValuesDecltypeAuto5(OriginalValue)

		auto													ReturnValue=MACRO_VALUE;

		wcout << L"CODE [decltype(auto) " << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<decltype(MACRO_VALUE)>() << "] VALUE [" << ReturnValue << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraits(void)
{
	PrintLineSeparator();

	{
		#define													MACRO_VALUE is_integral<int>::value

		bool													Value=MACRO_VALUE;

		wcout << L"CODE [" << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		#define													MACRO_VALUE is_integral<double>::value

		bool													Value=MACRO_VALUE;

		wcout << L"CODE [" << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		#define													MACRO_VALUE is_floating_point<int>::value

		bool													Value=MACRO_VALUE;

		wcout << L"CODE [" << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		#define													MACRO_VALUE is_floating_point<double>::value

		bool													Value=MACRO_VALUE;

		wcout << L"CODE [" << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] VALUE [" << Value << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		#define													MACRO_VALUE add_lvalue_reference<int>::type

		using													Type=MACRO_VALUE;

		wcout << L"CODE [" << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<Type>() << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();

	{
		#define													MACRO_VALUE add_rvalue_reference<int>::type

		using													Type=MACRO_VALUE;

		wcout << L"CODE [" << MACRO_STRINGIFY_TO_WIDE_STRING(MACRO_VALUE) << L"] TYPE [" << GetTypeInfoName<Type>() << L"]." << endl;

		#undef MACRO_VALUE
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitAddressOf(void)
{
	PrintLineSeparator();

	{
		CAddressOf												Object(new int(100));

		PrintLineSeparator();

		// !!! Vola sa CUSTOM OPERATOR [OPERATOR&].
		int**													Pointer1=&Object;

		PrintLineSeparator();

		wcout << "OBJECT [" << *(Object.GetData()) << L"]." << endl;

		wcout << "POINTER 1 [" << Pointer1 << L"]." << endl;

		PrintLineSeparator();

		// !!! NEVOLA sa CUSTOM OPERATOR [OPERATOR&].
		CAddressOf*												Pointer2=addressof(Object);

		wcout << "POINTER 2 [" << Pointer2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitDeclval(void)
{
	PrintLineSeparator();

	{
		// !!! EXPRESSION [CDeclvalConstructible().GetField1()] vola v COMPILE TIME DEFAULT CONSTRUCTOR.
		decltype(CDeclvalConstructible().GetField1())			Variable=100;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Variable)>() << L"] - VALUE [" << Variable << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! EXPRESSION [CDeclvalConstructible().GetField2()] vola v COMPILE TIME DEFAULT CONSTRUCTOR.
		decltype(CDeclvalConstructible().GetField2())			Variable=123.456;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Variable)>() << L"] - VALUE [" << Variable << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!! COMPILER hodi ERROR, pretoze TYPE [CDeclvalNonConstructible] ma DELETED DEFAULT CONSTRUCTOR.
		decltype(CDeclvalNonConstructible().GetField2())		Variable=123.456;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Variable)>() << L"] - VALUE [" << Variable << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!! COMPILER prebehne OK, pretoze TYPE TRAIT [declval<TType>] NEVYZADUJE volanie DEFAULT CONSTRUCTOR, ktory ma TYPE [CDeclvalNonConstructible] DELETED.
		decltype(declval<CDeclvalNonConstructible>().GetField2())		Variable=123.456;

		wcout << L"TYPE [" << GetTypeInfoName<decltype(Variable)>() << L"] - VALUE [" << Variable << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CClassWithCopyAndMoveSemantics FunctionPerfectForwardingTemporariesGet(void)
{
	CClassWithCopyAndMoveSemantics								ReturnValue(100,123.456);

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void FunctionPerfectForwardingTemporariesSet(TType Value)
{
	wcout << L"FUNCTION - FIELD 1 [" << Value.GetField1() << L"] FIELD 2 [" << Value.GetField2() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplatePerfectForwardingTemporaries1(void)
{
	// !!! Vytvori sa TEMPORARY VARIABLE ako RVALUE REFERENCE.
	auto&&														Temp=FunctionPerfectForwardingTemporariesGet();

	wcout << L"FORWARDER FUNCTION - FIELD 1 [" << Temp.GetField1() << L"] FIELD 2 [" << Temp.GetField2() << L"]." << endl;

	// !!!!! NEVYKONA sa PERFECT FORWARDING do cielovej FUNCTION.
	FunctionPerfectForwardingTemporariesSet(Temp);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplatePerfectForwardingTemporaries2(void)
{
	// !!! Vytvori sa TEMPORARY VARIABLE ako RVALUE REFERENCE.
	auto&&														Temp=FunctionPerfectForwardingTemporariesGet();

	wcout << L"FORWARDER FUNCTION - FIELD 1 [" << Temp.GetField1() << L"] FIELD 2 [" << Temp.GetField2() << L"]." << endl;

	// !!!!! VYKONA sa PERFECT FORWARDING do cielovej FUNCTION.
	FunctionPerfectForwardingTemporariesSet(forward<decltype(Temp)>(Temp));
}
//----------------------------------------------------------------------------------------------------------------------
void TestPerfectForwardingTemporaries(void)
{
	PrintLineSeparator();

	TemplatePerfectForwardingTemporaries1<CClassWithCopyAndMoveSemantics>();

	PrintLineSeparator();

	TemplatePerfectForwardingTemporaries2<CClassWithCopyAndMoveSemantics>();

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ReferenceTemplateParametersIsReference(TType)
{
	wcout << L"TYPE [" << GetTypeInfoName<TType>() << L"] IS REFERENCE [" << is_reference<TType>::value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestReferenceTemplateParameters(void)
{
	PrintLineSeparator();

	int															NonReferenceVariable=100;
	int&														ReferenceVariable=NonReferenceVariable;

	{
		// !!! DEDUCED TYPE je TYPE [int].
		ReferenceTemplateParametersIsReference(NonReferenceVariable);
	}

	PrintLineSeparator();

	{
		// !!!!! DEDUCED TYPE je TYPE [int] namiesto TYPE [int&].
		ReferenceTemplateParametersIsReference(ReferenceVariable);
	}

	PrintLineSeparator();

	{
		// !!! DEDUCED TYPE je TYPE [int&].
		ReferenceTemplateParametersIsReference<int&>(NonReferenceVariable);
	}

	PrintLineSeparator();

	{
		// !!! DEDUCED TYPE je TYPE [int&].
		ReferenceTemplateParametersIsReference<int&>(ReferenceVariable);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TYPE [CValue] je v tomto mieste INCOMPLETE TYPE, pretoze je iba DECLARED, ale NIE DEFINED.
class CValue;
//----------------------------------------------------------------------------------------------------------------------
void DeferEvalutionPrintValue(const CValue* Value);
void DeferEvalutionPrintObject(const CDeferEvalution<CValue>& Object);
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION moze pouzit aj INCOMPLETE TYPE [CValue].
void FunctionDeferEvalution(CValue* Parameter)
{
	CDeferEvalution<CValue>										Object(Parameter);
	const CValue*												Field=Object.GetField();

	DeferEvalutionPrintValue(Field);

	DeferEvalutionPrintObject(Object);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TYPE [CValue] je v tomto mieste COMPLETE TYPE, pretoze je nielen DECLARED, ale aj DEFINED.
#include "CValue.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void DeferEvalutionPrintValue(const CValue* Value)
{
	wcout << L"VALUE [" << Value->GetValue() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void DeferEvalutionPrintObject(const CDeferEvalution<CValue>& Object)
{
	wcout << L"OBJECT [" << Object.GetField()->GetValue() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestDeferEvalution(void)
{
	PrintLineSeparator();

	{
		CValue													Object(100);
		CValue*													Value=&Object;

		FunctionDeferEvalution(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestCallableObjects();
	//TestCallableObjectsNonStaticMethods();
	//TestCallableObjectsWithNoPerfectForwarding();
	//TestCallableObjectsWithPerfectForwardingInvoke();
	//TestCallableObjectsWithPerfectForwardingInvokeReturnValue();
	//TestPlaceholderTypeSpecifiersInitializers();
	//TestPlaceholderTypeSpecifiersReturnValues();
	//TestTypeTraits();
	//TestTypeTraitAddressOf();
	//TestTypeTraitDeclval();
	//TestPerfectForwardingTemporaries();
	//TestReferenceTemplateParameters();
	TestDeferEvalution();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------