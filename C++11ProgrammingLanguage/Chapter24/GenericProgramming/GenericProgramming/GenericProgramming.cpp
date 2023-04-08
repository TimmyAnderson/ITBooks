//-------------------------------------------------------------------------------------------------------
#include <functional>
#include <type_traits>
#include <string>
#include <iostream>
#include "MyDebug.h"
#include "Accumulate.h"
#include "CPlusFunctor.h"
#include "CType1.h"
#include "CType2.h"
#include "CStaticAssert1.h"
#include "CStaticAssert2.h"
#include "CCallback.h"
#include "IEquatable.h"
#include "CEquatableClass1.h"
#include "CEquatableClass2.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void TestAccumulate(void)
{
	PrintLineSeparator();

	int															Array1[]{1,2,3,4};
	int															Result1=Accumulate(Array1,Array1+CountOf(Array1),0,plus<int>());

	wprintf_s(L"Result1 [%d] !\n",Result1);

	double														Array2[]{1.1,2.2,3.3,4.5};
	double														Result2=Accumulate(Array2,Array2+CountOf(Array2),0.0,plus<double>());

	wprintf_s(L"Result2 [%f] !\n",Result2);

	double														Array3[]{1.1,2.2,3.3,4.5};
	double														Result3=Accumulate(Array3,Array3+CountOf(Array3),1.2,CPlusFunctor<double>());

	wprintf_s(L"Result3 [%f] !\n",Result3);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TypeTraits(void)
{
	PrintLineSeparator();

	wprintf_s(L"IS_CLASS<int> [%d] !\n",is_class<int>::value);
	wprintf_s(L"IS_CLASS<wstring> [%d] !\n",is_class<wstring>::value);
	wprintf_s(L"IS_CLASS<CType1> [%d] !\n",is_class<CType1>::value);
	wprintf_s(L"IS_ABSTRACT<int> [%d] !\n",is_abstract<int>::value);
	wprintf_s(L"IS_ABSTRACT<wstring> [%d] !\n",is_abstract<wstring>::value);
	wprintf_s(L"IS_ABSTRACT<CType1> [%d] !\n",is_abstract<CType1>::value);
	wprintf_s(L"IS_TRIVIALLY_DESTRUCTIBLE<CType1> [%d] !\n",is_trivially_destructible<CType1>::value);
	wprintf_s(L"IS_TRIVIALLY_DESTRUCTIBLE<CType2> [%d] !\n",is_trivially_destructible<CType2>::value);
	wprintf_s(L"IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE<CType1> [%d] !\n",is_trivially_default_constructible<CType1>::value);
	wprintf_s(L"IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE<CType2> [%d] !\n",is_trivially_default_constructible<CType2>::value);
	wprintf_s(L"IS_FUNCTION<CType2> [%d] !\n",is_function<CType2>::value);
	wprintf_s(L"IS_FUNCTION<decltype(TypeTraits)> [%d] !\n",is_function<decltype(TypeTraits)>::value);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void PrintString(wstring Value)
{
	wprintf_s(L"Value [%ls] !\n",Value.c_str());
}
//-------------------------------------------------------------------------------------------------------
void TestDeclTypeFunction(void)
{
	PrintLineSeparator();

	PrintString(L"Timmy Anderson 1");

	// !!! Deklaruje TYPE ako POINTER na FUNCTION.
	decltype(PrintString)*										Function1=PrintString;

	Function1(L"Timmy Anderson 2");

	// !!! Deklaruje TYPE ako POINTER na FUNCTION.
	decltype(PrintString)&										Function2=PrintString;

	Function2(L"Timmy Anderson 3");

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CallbackFunction1(wstring Value)
{
	wcout << L"CallbackFunction1 CALLBACK [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void TestStaticAssert1(void)
{
	PrintLineSeparator();

	CStaticAssert1<wstring,CCallback<wstring>>					StaticAssert1(CCallback<wstring>(),L"TEST 1");

	StaticAssert1.CallCallback();

	CStaticAssert1<wstring,decltype(CallbackFunction1)*>		StaticAssert2(CallbackFunction1,L"TEST 2");

	StaticAssert2.CallCallback();

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CallbackFunction2(wstring Value)
{
	wcout << L"CallbackFunction2 CALLBACK [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void TestStaticAssert2(void)
{
	PrintLineSeparator();

	CStaticAssert2<wstring,CCallback<wstring>>					StaticAssert1(CCallback<wstring>(),L"TEST 1");

	StaticAssert1.CallCallback();

	/*
	// !!!!! STATIC ASSERT hodi COMPILER ERROR, pretoze vyzaduje, aby bol TEMPLATE PARAMETER [TCallback] CLASS.
	CStaticAssert2<wstring,decltype(CallbackFunction2)*>		StaticAssert2(CallbackFunction2,L"TEST 2");

	StaticAssert2.CallCallback();
	*/

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CompareMultipleArguments(TType1 Value1, TType2 Value2)
{
	static_assert(is_same<TType1,TType2>::value,"TYPES [TType1] and [TType2] are NOT the SAME !");

	if (Value1==Value2)
	{
		wprintf_s(L"VALUES are EQUAL !\n");
	}
	else
	{
		wprintf_s(L"VALUES are DIFFERENT !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void InterfaceParameters(TType1 Value1, TType2 Value2)
{
#ifdef _MSC_VER
	// !!! VC++ umoznuje, aby TYPES boli VALUES aj POINTERS.
	static_assert(is_convertible<TType1,IEquatable>::value,"TYPE [TType1] does NOT implement INTERFACE [IEquatable] !");
	static_assert(is_convertible<TType2,IEquatable>::value,"TYPE [TType2] does NOT implement INTERFACE [IEquatable] !");
#else
	// !!! G++ vyzaduje, aby TYPES boli POINTERS.
	static_assert(is_convertible<TType1*,IEquatable*>::value,"TYPE [TType1] does NOT implement INTERFACE [IEquatable] !");
	static_assert(is_convertible<TType2*,IEquatable*>::value,"TYPE [TType2] does NOT implement INTERFACE [IEquatable] !");
#endif

	if (Value1.Equals(Value2)==true)
	{
		wprintf_s(L"VALUES are EQUAL !\n");
	}
	else
	{
		wprintf_s(L"VALUES are DIFFERENT !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void TestMultipleArguments(void)
{
	PrintLineSeparator();

	CompareMultipleArguments(100,100);
	CompareMultipleArguments(100,200);
	CompareMultipleArguments("aaa","aaa");
	CompareMultipleArguments("aaa","bbb");

	// !!! Hodi COMPILER ERROR, pretoze TYPES NIE su rovnake.
	//CompareMultipleArguments(10,10.5);

	PrintLineSeparator();

	InterfaceParameters(CEquatableClass1(L"111"),CEquatableClass1(L"111"));
	InterfaceParameters(CEquatableClass1(L"111"),CEquatableClass1(L"222"));

	PrintLineSeparator();

	InterfaceParameters(CEquatableClass1(L"111"),CEquatableClass2(L"111"));

	// !!! Hodi COMPILER ERROR, pretoze INT neimplementuje INTERFACE [IEquatable].
	//InterfaceParameters(CEquatableClass1(L"111"),111);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
void ValueParameter(TType)
{
	static_assert(sizeof(TType)<=4,"TYPE [TType] is TOO BIG !");

	wprintf_s(L"FUNCTION ValueParameter() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void TestValueTemplate(void)
{
	PrintLineSeparator();

	ValueParameter(100);

	// COMPILER hodi ERROR, pretoze DOUBLE ma viac ako 4 BYTES.
	//ValueParameter(100.4);

	// COMPILER hodi ERROR, pretoze WSTRING ma viac ako 4 BYTES.
	//ValueParameter(wstring(L"AAA"));

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestAccumulate();
	//TypeTraits();
	//TestDeclTypeFunction();
	//TestStaticAssert1();
	//TestStaticAssert2();
	TestMultipleArguments();

	ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------