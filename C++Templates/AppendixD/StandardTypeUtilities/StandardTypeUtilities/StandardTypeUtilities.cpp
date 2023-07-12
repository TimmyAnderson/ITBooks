//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CClass.h"
#include "EEnum.h"
#include "EEnumClass.h"
#include "SStruct.h"
#include "UUnion.h"
#include "UUnionTemplate.h"
#include "CAggregateClass.h"
#include "CNonAggregateClass.h"
#include "CAggregateStruct.h"
#include "CNonAggregateStruct.h"
#include "CNonAggregateStruct.h"
#include "CTrivial.h"
#include "CNonTrivial.h"
#include "CTriviallyCopyable.h"
#include "CNonTriviallyCopyable.h"
#include "CStandardLayout.h"
#include "CNonStandardLayout.h"
#include "CEmpty.h"
#include "CNonEmpty.h"
#include "CUniqueObjectRepresentations.h"
#include "CNonUniqueObjectRepresentations.h"
#include "CPolymorphic.h"
#include "CNonPolymorphic.h"
#include "CAbstract.h"
#include "CNonAbstract.h"
#include "CFinal.h"
#include "CNonFinal.h"
#include "CVirtualDestructor.h"
#include "CNonVirtualDestructor.h"
#include "EEnumInt.h"
#include "EEnumLong.h"
#include "EEnumLong.h"
#include "CInvocable.h"
#include "CInvokeResult.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4180 )
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
void TestTypeTraitsValues(void)
{
	PrintLineSeparator();

	// !!! Ziskanie TYPE TRAIT TYPE pomocou USING [type].
	conditional<true,int,double>::type							Value1;

	wcout << L"VALUE 1 - TYPE [" << GetTypeInfoName(typeid(Value1)) << L"]." << endl;

	// !!! Ziskanie TYPE TRAIT TYPE pomocou USING [TYPE_TRAIT_t<>].
	conditional_t<true,int,double>								Value2;

	wcout << L"VALUE 2 - TYPE [" << GetTypeInfoName(typeid(Value2)) << L"]." << endl;

	PrintLineSeparator();

	// !!! Ziskanie TYPE TRAIT VALUE pomocou STATIC FIELD [value].
	bool														Value3=is_floating_point<double>::value;

	wcout << L"VALUE 3 - VALUE [" << Value3 << L"]." << endl;

	// !!! Ziskanie TYPE TRAIT VALUE pomocou USING [TYPE_TRAIT_v<>].
	bool														Value4=is_floating_point_v<double>;

	wcout << L"VALUE 4 - VALUE [" << Value4 << L"]." << endl;

	// !!! Ziskanie TYPE TRAIT VALUE pomocou volania CONVERSION OPERATOR [OPERATOR bool()].
	// !!! CODE [is_floating_point<double>{}] vytvori instanciu TYPE [is_floating_point<double>] pre ktoru je volany CONVERSION OPERATOR [OPERATOR bool()].
	bool														Value5=is_floating_point<double>{};

	wcout << L"VALUE 5 - VALUE [" << Value5 << L"]." << endl;

	// !!! Ziskanie TYPE TRAIT VALUE pomocou volania OPERATOR [OPERATOR()].
	bool														Value6=is_floating_point<double>();

	wcout << L"VALUE 6 - VALUE [" << Value6 << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitsIntegralConstant(void)
{
	PrintLineSeparator();

	// !!! Vracia TYPE [integral_constant<bool,true>].
	using														Type1=is_floating_point<double>::type;

	wcout << L"TYPE 1 [" << GetTypeInfoName(typeid(Type1)) << L"]." << endl;

	// !!! Vracia TYPE [integral_constant<bool,false>].
	using														Type2=is_floating_point<int>::type;

	wcout << L"TYPE 2 [" << GetTypeInfoName(typeid(Type2)) << L"]." << endl;

	// !!! Vracia TYPE [bool].
	using														ValueType=is_floating_point<double>::value_type;

	wcout << L"VALUE TYPE [" << GetTypeInfoName(typeid(ValueType)) << L"]." << endl;

	PrintLineSeparator();

	// !!! VALUE TYPE TRAIT vracia STATIC CONSTEXPR FIELD [value].
	bool														Value1=is_floating_point<double>::value;
	bool														Value2=is_floating_point<int>::value;

	wcout << L"VALUE 1 [" << Value1 << L"]." << endl;
	wcout << L"VALUE 2 [" << Value2 << L"]." << endl;

	PrintLineSeparator();

	// !!! VALUE TYPE TRAIT vracia CONSTEXPR CONVERSION OPERATOR [constexpr operator value_type() const noexcept], ktory sa vola pri konverzii VALUE [is_floating_point<double>] na TYPE [bool].
	bool														ConversionOperatorValue1=is_floating_point<double>{};

	// !!! VALUE TYPE TRAIT vracia CONSTEXPR CONVERSION OPERATOR [constexpr operator value_type() const noexcept], ktory sa vola pri konverzii VALUE [is_floating_point<int>] na TYPE [bool].
	bool														ConversionOperatorValue2=is_floating_point<int>{};

	wcout << L"CONVERSION OPERATOR [OPERATOR bool()] VALUE 1 [" << ConversionOperatorValue1 << L"]." << endl;
	wcout << L"CONVERSION OPERATOR [OPERATOR bool()] VALUE 2 [" << ConversionOperatorValue2 << L"]." << endl;

	PrintLineSeparator();

	// !!! VALUE TYPE TRAIT vracia CONSTEXPR CONVERSION OPERATOR [constexpr value_type operator()() const noexcept].
	bool														FunctionOperatorValue1=is_floating_point<double>{};

	// !!! VALUE TYPE TRAIT vracia CONSTEXPR CONVERSION OPERATOR [constexpr value_type operator()() const noexcept].
	bool														FunctionOperatorValue2=is_floating_point<int>{};

	wcout << L"FUNCTION OPERATOR [OPERATOR()] VALUE 1 [" << FunctionOperatorValue1 << L"]." << endl;
	wcout << L"FUNCTION OPERATOR [OPERATOR()] VALUE 2 [" << FunctionOperatorValue2 << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitsAndDeclType(void)
{
	PrintLineSeparator();

	int															Value=100;
	int&&														Reference=move(Value);

	// !!! Vracia VALUE [false], pretoze sa vyhodnocuje samotna ENTITY 'Reference'. A ENTITY ma TYPE [int&&], teda sa jedna o RVALUE REFERENCE.
	bool														IsLValueReferenceEntity=is_lvalue_reference<decltype(Reference)>::value;

	wcout << L"IS LVALUE REFERENCE - ENTITY [" << IsLValueReferenceEntity << L"]." << endl;

	// !!! Vracia VALUE [true], pretoze sa vyhodnocuje samotna ENTITY 'Reference'. A ENTITY ma TYPE [int&&], teda sa jedna o RVALUE REFERENCE.
	bool														IsRValueReferenceEntity=is_rvalue_reference<decltype(Reference)>::value;

	wcout << L"IS RVALUE REFERENCE - ENTITY [" << IsRValueReferenceEntity << L"]." << endl;

	PrintLineSeparator();

	// !!! Vracia VALUE [true], pretoze pri pouziti ZATVORIEK [()] sa vyhodnocuje NIE ENTITY 'Reference', ale jej VALUE CATEGORY. A kedze VALUE CATEGORY EXPRESSION [(Reference)] je LVALUE, tak OPERATOR [decltype(Reference)] vrati TYPE [int&] co je LVALUE REFERENCE.
	bool														IsLValueReferenceExpression=is_lvalue_reference<decltype((Reference))>::value;

	wcout << L"IS LVALUE REFERENCE - EXPRESSION [" << IsLValueReferenceExpression << L"]." << endl;

	// !!! Vracia VALUE [false], pretoze pri pouziti ZATVORIEK [()] sa vyhodnocuje NIE ENTITY 'Reference', ale jej VALUE CATEGORY. A kedze VALUE CATEGORY EXPRESSION [(Reference)] je LVALUE, tak OPERATOR [decltype(Reference)] vrati TYPE [int&] co je LVALUE REFERENCE.
	bool														IsRValueReferenceExpression=is_rvalue_reference<decltype((Reference))>::value;

	wcout << L"IS RVALUE REFERENCE - EXPRESSION [" << IsRValueReferenceExpression << L"]." << endl;

	PrintLineSeparator();

	// !!! Vracia VALUE [false], pretoze pri pouziti ZATVORIEK [()] sa vyhodnocuje NIE ENTITY 'Reference', ale jej VALUE CATEGORY. A kedze VALUE CATEGORY EXPRESSION [(move(Reference))] je RVALUE, tak OPERATOR [decltype(Reference)] vrati TYPE [int&&] co je RVALUE REFERENCE.
	bool														IsLValueReferenceExpressionMove=is_lvalue_reference<decltype((move(Reference)))>::value;

	wcout << L"IS LVALUE REFERENCE - EXPRESSION MOVE [" << IsLValueReferenceExpressionMove << L"]." << endl;

	// !!! Vracia VALUE [true], pretoze pri pouziti ZATVORIEK [()] sa vyhodnocuje NIE ENTITY 'Reference', ale jej VALUE CATEGORY. A kedze VALUE CATEGORY EXPRESSION [(move(Reference))] je RVALUE, tak OPERATOR [decltype(Reference)] vrati TYPE [int&&] co je RVALUE REFERENCE.
	bool														IsRValueReferenceExpressionMove=is_rvalue_reference<decltype((move(Reference)))>::value;

	wcout << L"IS RVALUE REFERENCE - EXPRESSION MOVE [" << IsRValueReferenceExpressionMove << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsVoid(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_void<void>::value;

		wcout << L"TYPE TRAIT [is_void<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_void<const void>::value;

		wcout << L"TYPE TRAIT [is_void<const void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_void<volatile void>::value;

		wcout << L"TYPE TRAIT [is_void<volatile void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_void<int>::value;

		wcout << L"TYPE TRAIT [is_void<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze TYPE je TYPE samotnej FUNCTION.
		bool													Value=is_void<decltype(TestTypeTraitIsVoid)>::value;

		wcout << L"TYPE TRAIT [is_void<decltype(TestTypeTraitIsVoid)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze TYPE je RETURN TYPE danej FUNCTION, ktory je TYPE [void].
		bool													Value=is_void<decltype(TestTypeTraitIsVoid())>::value;

		wcout << L"TYPE TRAIT [is_void<decltype(TestTypeTraitIsVoid())>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsIntegral(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_integral<int>::value;

		wcout << L"TYPE TRAIT [is_integral<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_integral<const int>::value;

		wcout << L"TYPE TRAIT [is_integral<const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_integral<volatile int>::value;

		wcout << L"TYPE TRAIT [is_integral<volatile int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_integral<float>::value;

		wcout << L"TYPE TRAIT [is_integral<float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_integral<char>::value;

		wcout << L"TYPE TRAIT [is_integral<char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_integral<wchar_t>::value;

		wcout << L"TYPE TRAIT [is_integral<wchar_t>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_integral<bool>::value;

		wcout << L"TYPE TRAIT [is_integral<bool>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsFloatingPoint(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_floating_point<float>::value;

		wcout << L"TYPE TRAIT [is_floating_point<float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_floating_point<const float>::value;

		wcout << L"TYPE TRAIT [is_floating_point<const float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_floating_point<volatile float>::value;

		wcout << L"TYPE TRAIT [is_floating_point<volatile float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_floating_point<int>::value;

		wcout << L"TYPE TRAIT [is_floating_point<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_floating_point<double>::value;

		wcout << L"TYPE TRAIT [is_floating_point<double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_floating_point<long double>::value;

		wcout << L"TYPE TRAIT [is_floating_point<long double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionTypeTraitIsArray(double Array1[10], double Array2[], double* Array3)
{
	{
		// !!! Vracia FALSE, pretoze pri prenose C-ARRAYS do FUNCTIONS sa robi DECAY na POINTERS.
		bool													Value=is_array<decltype(Array1)>::value;

		wcout << L"TYPE TRAIT [PARAMETER is_array<decltype(Array1)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vracia FALSE, pretoze pri prenose C-ARRAYS do FUNCTIONS sa robi DECAY na POINTERS.
		bool													Value=is_array<decltype(Array2)>::value;

		wcout << L"TYPE TRAIT [PARAMETER is_array<decltype(Array2)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vracia FALSE, pretoze pri prenose C-ARRAYS do FUNCTIONS sa robi DECAY na POINTERS.
		bool													Value=is_array<decltype(Array3)>::value;

		wcout << L"TYPE TRAIT [PARAMETER is_array<decltype(Array3)>::value] - VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsArray(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_array<double[10]>::value;

		wcout << L"TYPE TRAIT [is_array<double[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_array<double[]>::value;

		wcout << L"TYPE TRAIT [is_array<double[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_array<const double[10]>::value;

		wcout << L"TYPE TRAIT [is_array<const double[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_array<double*>::value;

		wcout << L"TYPE TRAIT [is_array<double*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		double													Array[10]{};

		FunctionTypeTraitIsArray(Array,Array,Array);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int* FunctionTypeTraitIsPointer1(void)
{
	return(nullptr);
}
//----------------------------------------------------------------------------------------------------------------------
void FunctionTypeTraitIsPointer2(double Array1[10], double Array2[], double* Array3, void (Function)())
{
	{
		// !!! Vracia TRUE, pretoze pri prenose C-ARRAYS do FUNCTIONS sa robi DECAY na POINTERS.
		bool													Value=is_pointer<decltype(Array1)>::value;

		wcout << L"TYPE TRAIT [PARAMETER is_pointer<decltype(Array1)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vracia TRUE, pretoze pri prenose C-ARRAYS do FUNCTIONS sa robi DECAY na POINTERS.
		bool													Value=is_pointer<decltype(Array2)>::value;

		wcout << L"TYPE TRAIT [PARAMETER is_pointer<decltype(Array2)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vracia TRUE, pretoze pri prenose C-ARRAYS do FUNCTIONS sa robi DECAY na POINTERS.
		bool													Value=is_pointer<decltype(Array3)>::value;

		wcout << L"TYPE TRAIT [PARAMETER is_pointer<decltype(Array3)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vracia TRUE, pretoze sa jedna o POINTER na FUNCTION.
		bool													Value=is_pointer<decltype(Function)>::value;

		wcout << L"TYPE TRAIT [PARAMETER is_pointer<decltype(Function)>::value] - VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsPointer(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_pointer<double*>::value;

		wcout << L"TYPE TRAIT [is_pointer<double*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_pointer<const double*>::value;

		wcout << L"TYPE TRAIT [is_pointer<const double*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE. C-ARRAYS nie su povazovane za POINTERS.
		bool													Value=is_pointer<double[10]>::value;

		wcout << L"TYPE TRAIT [is_pointer<double[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE. C-ARRAYS nie su povazovane za POINTERS.
		bool													Value=is_pointer<double[]>::value;

		wcout << L"TYPE TRAIT [is_pointer<double[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze sa jedna o REFERENCE na POINTER.
		bool													Value=is_pointer<double*&>::value;

		wcout << L"TYPE TRAIT [is_pointer<const double*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze sa jedna o POINTER na FUNCTION.
		bool													Value=is_pointer<decltype(&TestTypeTraitIsPointer)>::value;

		wcout << L"TYPE TRAIT [is_pointer<decltype(&TestTypeTraitIsPointer)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze sa jedna o FUNCTION TYPE, a nie POINTER.
		bool													Value=is_pointer<decltype(TestTypeTraitIsPointer)>::value;

		wcout << L"TYPE TRAIT [is_pointer<decltype(TestTypeTraitIsPointer)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze RETURN TYPE FUNCTION je POINTER.
		bool													Value=is_pointer<decltype(FunctionTypeTraitIsPointer1())>::value;

		wcout << L"TYPE TRAIT [is_pointer<decltype(FunctionTypeTraitIsPointer1())>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze TYPE [nullptr_t] NIE je POINTER.
		bool													Value=is_pointer<decltype(nullptr)>::value;

		wcout << L"TYPE TRAIT [is_pointer<decltype(nullptr)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		double													Array[10]{};

		FunctionTypeTraitIsPointer2(Array,Array,Array,TestTypeTraitIsPointer);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNullPointer(void)
{
	PrintLineSeparator();

	{
		// !!! Vracia TRUE.
		bool													Value=is_null_pointer<decltype(nullptr)>::value;

		wcout << L"TYPE TRAIT [is_null_pointer<decltype(nullptr)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vracia TRUE.
		bool													Value=is_null_pointer<const decltype(nullptr)>::value;

		wcout << L"TYPE TRAIT [is_null_pointer<const decltype(nullptr)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		nullptr_t												Pointer=nullptr;

		// !!! Vracia TRUE, pretoze sa JEDNA o TYPE [nullptr_t].
		bool													Value=is_null_pointer<decltype(Pointer)>::value;

		wcout << L"TYPE TRAIT [is_null_pointer<decltype(Pointer)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void*													Pointer=nullptr;

		// !!! Vracia FALSE, pretoze sa NEJEDNA o TYPE [nullptr_t].
		bool													Value=is_null_pointer<decltype(Pointer)>::value;

		wcout << L"TYPE TRAIT [is_null_pointer<decltype(Pointer)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsMemberObjectPointer(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_member_object_pointer<int CClass::*>::value;

		wcout << L"TYPE TRAIT [is_member_object_pointer<int CClass::*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_object_pointer<int CClass::* const>::value;

		wcout << L"TYPE TRAIT [is_member_object_pointer<int CClass::* const>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														CClass::*Field=&CClass::MField;

		// !!! CODE zbehne OK, pretoze POINTER je NON-CONST.
		Field=&CClass::MField;

		bool													Value=is_member_object_pointer<decltype(Field)>::value;

		wcout << L"TYPE TRAIT [is_member_object_pointer<decltype(Field)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														CClass::* const Field=&CClass::MField;

		// !!! COMPILER hodi ERROR, pretoze POINTER je CONST.
		//Field=&CClass::MField;

		bool													Value=is_member_object_pointer<decltype(Field)>::value;

		wcout << L"TYPE TRAIT [CONST is_member_object_pointer<decltype(Field)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_object_pointer<int>::value;

		wcout << L"TYPE TRAIT [is_member_object_pointer<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsMemberFunctionPointer(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_member_function_pointer<int (CClass::*)(void)>::value;

		wcout << L"TYPE TRAIT [is_member_function_pointer<int (CClass::*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_function_pointer<int (CClass::*)(void) const>::value;

		wcout << L"TYPE TRAIT [is_member_function_pointer<int (CClass::*)(void) const>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_function_pointer<int (CClass::* const)(void)>::value;

		wcout << L"TYPE TRAIT [is_member_function_pointer<int (CClass::* const)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_function_pointer<int (CClass::* const)(void) const>::value;

		wcout << L"TYPE TRAIT [is_member_function_pointer<int (CClass::* const)(void) const>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(CClass::*Method)(void)=&CClass::Method;
		CClass													Object{};

		(Object.*Method)();

		// !!! CODE zbehne OK, pretoze POINTER je NON-CONST.
		Method=&CClass::Method;

		bool													Value=is_member_function_pointer<decltype(Method)>::value;

		wcout << L"TYPE TRAIT [is_member_function_pointer<decltype(Method)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(CClass::*Method)(void) const=&CClass::Method;
		CClass													Object{};

		(Object.*Method)();

		// !!! CODE zbehne OK, pretoze POINTER je NON-CONST.
		Method=&CClass::Method;

		bool													Value=is_member_function_pointer<decltype(Method)>::value;

		wcout << L"TYPE TRAIT [is_member_function_pointer<decltype(Method) CONST>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(CClass::* const Method)(void)=&CClass::Method;
		CClass													Object{};

		(Object.*Method)();

		// !!! COMPILER hodi ERROR, pretoze POINTER je CONST.
		//Method=&CClass::Method;

		bool													Value=is_member_function_pointer<decltype(Method)>::value;

		wcout << L"TYPE TRAIT [CONST is_member_function_pointer<decltype(Method)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(CClass::* const Method)(void) const=&CClass::Method;
		CClass													Object{};

		(Object.*Method)();

		// !!! COMPILER hodi ERROR, pretoze POINTER je CONST.
		//Method=&CClass::Method;

		bool													Value=is_member_function_pointer<decltype(Method)>::value;

		wcout << L"TYPE TRAIT [CONST is_member_function_pointer<decltype(Method) CONST>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_function_pointer<int>::value;

		wcout << L"TYPE TRAIT [is_member_function_pointer<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsLValueReference(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_lvalue_reference<int&>::value;

		wcout << L"TYPE TRAIT [is_lvalue_reference<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_lvalue_reference<const int&>::value;

		wcout << L"TYPE TRAIT [is_lvalue_reference<const int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_lvalue_reference<int&&>::value;

		wcout << L"TYPE TRAIT [is_lvalue_reference<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_lvalue_reference<int>::value;

		wcout << L"TYPE TRAIT [is_lvalue_reference<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_lvalue_reference<void>::value;

		wcout << L"TYPE TRAIT [is_lvalue_reference<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsRValueReference(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_rvalue_reference<int&>::value;

		wcout << L"TYPE TRAIT [is_rvalue_reference<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_rvalue_reference<int&&>::value;

		wcout << L"TYPE TRAIT [is_rvalue_reference<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_rvalue_reference<const int&&>::value;

		wcout << L"TYPE TRAIT [is_rvalue_reference<const int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_rvalue_reference<int>::value;

		wcout << L"TYPE TRAIT [is_rvalue_reference<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_rvalue_reference<void>::value;

		wcout << L"TYPE TRAIT [is_rvalue_reference<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsEnum(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_enum<EEnum>::value;

		wcout << L"TYPE TRAIT [is_enum<EEnum>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_enum<const EEnum>::value;

		wcout << L"TYPE TRAIT [is_enum<const EEnum>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_enum<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_enum<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_enum<const EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_enum<const EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_enum<int>::value;

		wcout << L"TYPE TRAIT [is_enum<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsClass(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_class<CClass>::value;

		wcout << L"TYPE TRAIT [is_class<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_class<const CClass>::value;

		wcout << L"TYPE TRAIT [is_class<const CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_class<SStruct>::value;

		wcout << L"TYPE TRAIT [is_class<SStruct>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_class<CClass&>::value;

		wcout << L"TYPE TRAIT [is_class<CClass&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_class<EEnum>::value;

		wcout << L"TYPE TRAIT [is_class<EEnum>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_class<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_class<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_class<int>::value;

		wcout << L"TYPE TRAIT [is_class<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	// !!! Interne tu LAMBDA EXPRESSIONS realizovane ako CLASSES.
	auto														Lambda=[](int Value1, int Value2) -> int
	{
		return(Value1+Value2);
	};

	{
		// !!!!! Vrati TRUE, pretoze LAMBDA EXPRESSIONS us INTERNE realizovane ako CLASSES.
		bool													Value=is_class<decltype(Lambda)>::value;

		wcout << L"TYPE TRAIT [is_class<decltype(Lambda)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsUnion(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_union<UUnion>::value;

		wcout << L"TYPE TRAIT [is_union<UUnion>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_union<const UUnion>::value;

		wcout << L"TYPE TRAIT [is_union<const UUnion>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_union<UUnionTemplate<int,double>>::value;

		wcout << L"TYPE TRAIT [is_union<UUnionTemplate<int,double>>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_union<const UUnionTemplate<int,double>>::value;

		wcout << L"TYPE TRAIT [is_union<const UUnionTemplate<int,double>>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_union<CClass>::value;

		wcout << L"TYPE TRAIT [is_union<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_union<int>::value;

		wcout << L"TYPE TRAIT [is_union<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionTypeTraitIsFunction(void(Parameter)(void))
{
	{
		// !!! Vrati FALSE, pretoze PARAMETER je POINTER na FUNCTION, a NIE FUNCTION TYPE.
		bool													Value=is_function<decltype(Parameter)>::value;

		wcout << L"TYPE TRAIT [is_function<decltype(Parameter)>::value] - VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsFunction(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_function<decltype(TestTypeTraitIsFunction)>::value;

		wcout << L"TYPE TRAIT [is_function<decltype(TestTypeTraitIsFunction)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_function<const decltype(TestTypeTraitIsFunction)>::value;

		wcout << L"TYPE TRAIT [is_function<const decltype(TestTypeTraitIsFunction)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_function<decltype(CClass::StaticMethod)>::value;

		wcout << L"TYPE TRAIT [is_function<decltype(CClass::StaticMethod)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo sa jedna o POINTER na FUNCTION a NIE FUNCTION TYPE.
		bool													Value=is_function<decltype(&TestTypeTraitIsFunction)>::value;

		wcout << L"TYPE TRAIT [is_function<decltype(TestTypeTraitIsFunction)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo sa jedna o POINTER na FUNCTION a NIE FUNCTION TYPE.
		bool													Value=is_function<void(*)(void)>::value;

		wcout << L"TYPE TRAIT [is_function<void(*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo FUNCTION RETURN TYPE je TYPE [void] a NIE FUNCTION TYPE.
		bool													Value=is_function<decltype(TestTypeTraitIsFunction())>::value;

		wcout << L"TYPE TRAIT [is_function<decltype(TestTypeTraitIsFunction())>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		FunctionTypeTraitIsFunction(TestTypeTraitIsFunction);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsReference(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_reference<int&>::value;

		wcout << L"TYPE TRAIT [is_reference<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_reference<const int&>::value;

		wcout << L"TYPE TRAIT [is_reference<const int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_reference<int&&>::value;

		wcout << L"TYPE TRAIT [is_reference<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_reference<const int&&>::value;

		wcout << L"TYPE TRAIT [is_reference<const int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_reference<int>::value;

		wcout << L"TYPE TRAIT [is_reference<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_reference<void>::value;

		wcout << L"TYPE TRAIT [is_reference<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsMemberPointer(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_member_pointer<int CClass::*>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<int CClass::*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_pointer<int CClass::* const>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<int CClass::* const>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														CClass::*Field=&CClass::MField;

		// !!! CODE zbehne OK, pretoze POINTER je NON-CONST.
		Field=&CClass::MField;

		bool													Value=is_member_pointer<decltype(Field)>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<decltype(Field)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														CClass::* const Field=&CClass::MField;

		// !!! COMPILER hodi ERROR, pretoze POINTER je CONST.
		//Field=&CClass::MField;

		bool													Value=is_member_pointer<decltype(Field)>::value;

		wcout << L"TYPE TRAIT [CONST is_member_pointer<decltype(Field)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_pointer<int (CClass::*)(void)>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<int (CClass::*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_pointer<int (CClass::*)(void) const>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<int (CClass::*)(void) const>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_pointer<int (CClass::* const)(void)>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<int (CClass::* const)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_pointer<int (CClass::* const)(void) const>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<int (CClass::* const)(void) const>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(CClass::*Method)(void)=&CClass::Method;
		CClass													Object{};

		(Object.*Method)();

		// !!! CODE zbehne OK, pretoze POINTER je NON-CONST.
		Method=&CClass::Method;

		bool													Value=is_member_pointer<decltype(Method)>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<decltype(Method)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(CClass::*Method)(void) const=&CClass::Method;
		CClass													Object{};

		(Object.*Method)();

		// !!! CODE zbehne OK, pretoze POINTER je NON-CONST.
		Method=&CClass::Method;

		bool													Value=is_member_pointer<decltype(Method)>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<decltype(Method) CONST>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(CClass::* const Method)(void)=&CClass::Method;
		CClass													Object{};

		(Object.*Method)();

		// !!! COMPILER hodi ERROR, pretoze POINTER je CONST.
		//Method=&CClass::Method;

		bool													Value=is_member_pointer<decltype(Method)>::value;

		wcout << L"TYPE TRAIT [CONST is_member_pointer<decltype(Method)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(CClass::* const Method)(void) const=&CClass::Method;
		CClass													Object{};

		(Object.*Method)();

		// !!! COMPILER hodi ERROR, pretoze POINTER je CONST.
		//Method=&CClass::Method;

		bool													Value=is_member_pointer<decltype(Method)>::value;

		wcout << L"TYPE TRAIT [CONST is_member_pointer<decltype(Method) CONST>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_member_pointer<int>::value;

		wcout << L"TYPE TRAIT [is_member_pointer<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsArithmetic(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_arithmetic<int>::value;

		wcout << L"TYPE TRAIT [is_arithmetic<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_arithmetic<const int>::value;

		wcout << L"TYPE TRAIT [is_arithmetic<const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_arithmetic<volatile int>::value;

		wcout << L"TYPE TRAIT [is_arithmetic<volatile int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_arithmetic<float>::value;

		wcout << L"TYPE TRAIT [is_arithmetic<float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_arithmetic<const float>::value;

		wcout << L"TYPE TRAIT [is_arithmetic<const float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_arithmetic<char>::value;

		wcout << L"TYPE TRAIT [is_arithmetic<char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_arithmetic<wchar_t>::value;

		wcout << L"TYPE TRAIT [is_arithmetic<wchar_t>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_arithmetic<bool>::value;

		wcout << L"TYPE TRAIT [is_arithmetic<bool>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_arithmetic<CClass>::value;

		wcout << L"TYPE TRAIT [is_arithmetic<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsFundamental(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_fundamental<int>::value;

		wcout << L"TYPE TRAIT [is_fundamental<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_fundamental<const int>::value;

		wcout << L"TYPE TRAIT [is_fundamental<const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_fundamental<volatile int>::value;

		wcout << L"TYPE TRAIT [is_fundamental<volatile int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_fundamental<float>::value;

		wcout << L"TYPE TRAIT [is_fundamental<float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_fundamental<const float>::value;

		wcout << L"TYPE TRAIT [is_fundamental<const float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_fundamental<char>::value;

		wcout << L"TYPE TRAIT [is_fundamental<char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_fundamental<wchar_t>::value;

		wcout << L"TYPE TRAIT [is_fundamental<wchar_t>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_fundamental<bool>::value;

		wcout << L"TYPE TRAIT [is_fundamental<bool>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_fundamental<void>::value;

		wcout << L"TYPE TRAIT [is_fundamental<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_fundamental<nullptr_t>::value;

		wcout << L"TYPE TRAIT [is_fundamental<nullptr_t>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_fundamental<void*>::value;

		wcout << L"TYPE TRAIT [is_fundamental<void*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_fundamental<CClass>::value;

		wcout << L"TYPE TRAIT [is_fundamental<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsScalar(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_scalar<int>::value;

		wcout << L"TYPE TRAIT [is_scalar<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_scalar<const int>::value;

		wcout << L"TYPE TRAIT [is_scalar<const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_scalar<volatile int>::value;

		wcout << L"TYPE TRAIT [is_scalar<volatile int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_scalar<float>::value;

		wcout << L"TYPE TRAIT [is_scalar<float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_scalar<const float>::value;

		wcout << L"TYPE TRAIT [is_scalar<const float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_scalar<char>::value;

		wcout << L"TYPE TRAIT [is_scalar<char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_scalar<wchar_t>::value;

		wcout << L"TYPE TRAIT [is_scalar<wchar_t>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_scalar<bool>::value;

		wcout << L"TYPE TRAIT [is_scalar<bool>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_scalar<void>::value;

		wcout << L"TYPE TRAIT [is_scalar<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_scalar<nullptr_t>::value;

		wcout << L"TYPE TRAIT [is_scalar<nullptr_t>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_scalar<void*>::value;

		wcout << L"TYPE TRAIT [is_scalar<void*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_scalar<CClass>::value;

		wcout << L"TYPE TRAIT [is_scalar<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_scalar<int CClass::*>::value;

		wcout << L"TYPE TRAIT [is_scalar<int CClass::*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_scalar<int (CClass::*)(void)>::value;

		wcout << L"TYPE TRAIT [is_scalar<int (CClass::*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_scalar<EEnum>::value;

		wcout << L"TYPE TRAIT [is_scalar<EEnum>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_scalar<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_scalar<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsObject(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_object<int>::value;

		wcout << L"TYPE TRAIT [is_object<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_object<const int>::value;

		wcout << L"TYPE TRAIT [is_object<const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_object<volatile int>::value;

		wcout << L"TYPE TRAIT [is_object<volatile int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_object<float>::value;

		wcout << L"TYPE TRAIT [is_object<float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_object<const float>::value;

		wcout << L"TYPE TRAIT [is_object<const float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_object<char>::value;

		wcout << L"TYPE TRAIT [is_object<char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_object<wchar_t>::value;

		wcout << L"TYPE TRAIT [is_object<wchar_t>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_object<bool>::value;

		wcout << L"TYPE TRAIT [is_object<bool>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<void>::value;

		wcout << L"TYPE TRAIT [is_object<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_object<nullptr_t>::value;

		wcout << L"TYPE TRAIT [is_object<nullptr_t>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<void*>::value;

		wcout << L"TYPE TRAIT [is_object<void*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<CClass>::value;

		wcout << L"TYPE TRAIT [is_object<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<SStruct>::value;

		wcout << L"TYPE TRAIT [is_object<SStruct>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<int CClass::*>::value;

		wcout << L"TYPE TRAIT [is_object<int CClass::*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<int (CClass::*)(void)>::value;

		wcout << L"TYPE TRAIT [is_object<int (CClass::*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<EEnum>::value;

		wcout << L"TYPE TRAIT [is_object<EEnum>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_object<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<double[10]>::value;

		wcout << L"TYPE TRAIT [is_object<double[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<UUnion>::value;

		wcout << L"TYPE TRAIT [is_object<UUnion>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_object<const UUnion>::value;

		wcout << L"TYPE TRAIT [is_object<const UUnion>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsCompound(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_compound<CClass>::value;

		wcout << L"TYPE TRAIT [is_compound<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_compound<const CClass>::value;

		wcout << L"TYPE TRAIT [is_compound<const CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_compound<SStruct>::value;

		wcout << L"TYPE TRAIT [is_compound<SStruct>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Interne tu LAMBDA EXPRESSIONS realizovane ako CLASSES.
		auto													Lambda=[](int Value1, int Value2) -> int
		{
			return(Value1+Value2);
		};

		// !!!!! Vrati TRUE, pretoze LAMBDA EXPRESSIONS us INTERNE realizovane ako CLASSES.
		bool													Value=is_compound<decltype(Lambda)>::value;

		wcout << L"TYPE TRAIT [is_compound<decltype(Lambda)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Vrati TRUE.
		bool													Value=is_compound<double[10]>::value;

		wcout << L"TYPE TRAIT [is_compound<double[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Vrati TRUE, pretoze sa jedna o FUNCTION TYPE.
		bool													Value=is_compound<decltype(TestTypeTraitIsCompound)>::value;

		wcout << L"TYPE TRAIT [is_compound<decltype(TestTypeTraitIsCompound)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Vrati TRUE.
		bool													Value=is_compound<double*>::value;

		wcout << L"TYPE TRAIT [is_compound<double*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_compound<int CClass::*>::value;

		wcout << L"TYPE TRAIT [is_compound<int CClass::*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_compound<int (CClass::*)(void)>::value;

		wcout << L"TYPE TRAIT [is_compound<int (CClass::*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_compound<int&>::value;

		wcout << L"TYPE TRAIT [is_compound<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_compound<int&&>::value;

		wcout << L"TYPE TRAIT [is_compound<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_compound<EEnum>::value;

		wcout << L"TYPE TRAIT [is_compound<EEnum>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_compound<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_compound<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_compound<UUnion>::value;

		wcout << L"TYPE TRAIT [is_compound<UUnion>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_compound<UUnionTemplate<int,double>>::value;

		wcout << L"TYPE TRAIT [is_compound<UUnionTemplate<int,double>>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati false.
		bool													Value=is_compound<void>::value;

		wcout << L"TYPE TRAIT [is_compound<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsSigned(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_signed<int>::value;

		wcout << L"TYPE TRAIT [is_signed<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_signed<signed int>::value;

		wcout << L"TYPE TRAIT [is_signed<signed int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_signed<unsigned int>::value;

		wcout << L"TYPE TRAIT [is_signed<unsigned int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_signed<const signed int>::value;

		wcout << L"TYPE TRAIT [is_signed<const signed int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_signed<float>::value;

		wcout << L"TYPE TRAIT [is_signed<float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! PLATFORM DEFINED VALUE.
		bool													Value=is_signed<char>::value;

		wcout << L"TYPE TRAIT [is_signed<char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_signed<signed char>::value;

		wcout << L"TYPE TRAIT [is_signed<signed char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_signed<unsigned char>::value;

		wcout << L"TYPE TRAIT [is_signed<unsigned char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// Vrati FALSE.
		bool													Value=is_signed<bool>::value;

		wcout << L"TYPE TRAIT [is_signed<bool>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// Vrati FALSE.
		bool													Value=is_signed<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_signed<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// Vrati FALSE.
		bool													Value=is_signed<CClass>::value;

		wcout << L"TYPE TRAIT [is_signed<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsUnsigned(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_unsigned<int>::value;

		wcout << L"TYPE TRAIT [is_unsigned<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_unsigned<signed int>::value;

		wcout << L"TYPE TRAIT [is_unsigned<signed int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_unsigned<unsigned int>::value;

		wcout << L"TYPE TRAIT [is_unsigned<unsigned int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_unsigned<const unsigned int>::value;

		wcout << L"TYPE TRAIT [is_unsigned<const unsigned int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_unsigned<float>::value;

		wcout << L"TYPE TRAIT [is_unsigned<float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! PLATFORM DEFINED VALUE.
		bool													Value=is_unsigned<char>::value;

		wcout << L"TYPE TRAIT [is_unsigned<char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_unsigned<signed char>::value;

		wcout << L"TYPE TRAIT [is_unsigned<signed char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_unsigned<unsigned char>::value;

		wcout << L"TYPE TRAIT [is_unsigned<unsigned char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// Vrati FALSE.
		bool													Value=is_unsigned<bool>::value;

		wcout << L"TYPE TRAIT [is_unsigned<bool>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// Vrati FALSE.
		bool													Value=is_unsigned<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_unsigned<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// Vrati FALSE.
		bool													Value=is_unsigned<CClass>::value;

		wcout << L"TYPE TRAIT [is_unsigned<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsConst(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_const<int>::value;

		wcout << L"TYPE TRAIT [is_const<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_const<const int>::value;

		wcout << L"TYPE TRAIT [is_const<const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre CONST POINTER na NON-CONST VALUE vrati TRUE.
		bool													Value=is_const<int* const>::value;

		wcout << L"TYPE TRAIT [is_const<int* const>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre POINTER na CONSTANT vrati FALSE.
		bool													Value=is_const<const int*>::value;

		wcout << L"TYPE TRAIT [is_const<const int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre REFERENCE na CONSTANT vrati FALSE.
		bool													Value=is_const<const int&>::value;

		wcout << L"TYPE TRAIT [is_const<const int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre ARRAY obsahujuci NON-CONST VALUES vrati FALSE.
		bool													Value=is_const<int[10]>::value;

		wcout << L"TYPE TRAIT [is_const<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre ARRAY obsahujuci CONST VALUES vrati TRUE.
		bool													Value=is_const<int const[10]>::value;

		wcout << L"TYPE TRAIT [is_const<int const[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre ARRAY obsahujuci NON-CONST VALUES vrati FALSE.
		bool													Value=is_const<int[]>::value;

		wcout << L"TYPE TRAIT [is_const<int[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre ARRAY obsahujuci CONST VALUES vrati TRUE.
		bool													Value=is_const<int const[]>::value;

		wcout << L"TYPE TRAIT [is_const<int const[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsVolatile(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_volatile<int>::value;

		wcout << L"TYPE TRAIT [is_volatile<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_volatile<volatile int>::value;

		wcout << L"TYPE TRAIT [is_volatile<volatile int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre VOLATILE POINTER na NON-VOLATILE VALUE vrati TRUE.
		bool													Value=is_volatile<int* volatile>::value;

		wcout << L"TYPE TRAIT [is_volatile<int* volatile>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre POINTER na VOLATILE vrati FALSE.
		bool													Value=is_volatile<volatile int*>::value;

		wcout << L"TYPE TRAIT [is_volatile<volatile int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre REFERENCE na VOLATILE vrati FALSE.
		bool													Value=is_volatile<volatile int&>::value;

		wcout << L"TYPE TRAIT [is_volatile<volatile int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre ARRAY obsahujuci NON-VOLATILE VALUES vrati FALSE.
		bool													Value=is_volatile<int[10]>::value;

		wcout << L"TYPE TRAIT [is_volatile<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre ARRAY obsahujuci VOLATILE VALUES vrati TRUE.
		bool													Value=is_volatile<int volatile[10]>::value;

		wcout << L"TYPE TRAIT [is_volatile<int volatile[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre ARRAY obsahujuci NON-VOLATILE VALUES vrati FALSE.
		bool													Value=is_volatile<int[]>::value;

		wcout << L"TYPE TRAIT [is_volatile<int[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pre ARRAY obsahujuci VOLATILE VALUES vrati TRUE.
		bool													Value=is_volatile<int volatile[]>::value;

		wcout << L"TYPE TRAIT [is_volatile<int volatile[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsAggregate(void)
{
	PrintLineSeparator();

	{
		bool													Value=is_aggregate<CAggregateClass>::value;

		wcout << L"TYPE TRAIT [is_aggregate<CAggregateClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_aggregate<CNonAggregateClass>::value;

		wcout << L"TYPE TRAIT [is_aggregate<CNonAggregateClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		bool													Value=is_aggregate<const CAggregateClass>::value;

		wcout << L"TYPE TRAIT [is_aggregate<const CAggregateClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_aggregate<int>::value;

		wcout << L"TYPE TRAIT [is_aggregate<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo C-ARRAYS su AGGREGATE TYPES.
		bool													Value=is_aggregate<int[10]>::value;

		wcout << L"TYPE TRAIT [is_aggregate<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_aggregate<void>::value;

		wcout << L"TYPE TRAIT [is_aggregate<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_aggregate<CAggregateStruct>::value;

		wcout << L"TYPE TRAIT [is_aggregate<CAggregateStruct>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_aggregate<CNonAggregateStruct>::value;

		wcout << L"TYPE TRAIT [is_aggregate<CNonAggregateStruct>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_aggregate<UUnion>::value;

		wcout << L"TYPE TRAIT [is_aggregate<UUnion>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTrivial(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivial<int>::value;

		wcout << L"TYPE TRAIT [is_trivial<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivial<const int>::value;

		wcout << L"TYPE TRAIT [is_trivial<const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivial<int[10]>::value;

		wcout << L"TYPE TRAIT [is_trivial<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivial<EEnum>::value;

		wcout << L"TYPE TRAIT [is_trivial<EEnum>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivial<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_trivial<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivial<CClass*>::value;

		wcout << L"TYPE TRAIT [is_trivial<CClass*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivial<CClass&>::value;

		wcout << L"TYPE TRAIT [is_trivial<CClass&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivial<CTrivial>::value;

		wcout << L"TYPE TRAIT [is_trivial<CTrivial>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivial<CNonTrivial>::value;

		wcout << L"TYPE TRAIT [is_trivial<CNonTrivial>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivial<CTrivial[10]>::value;

		wcout << L"TYPE TRAIT [is_trivial<CTrivial[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivial<CNonTrivial[10]>::value;

		wcout << L"TYPE TRAIT [is_trivial<CNonTrivial[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTriviallyCopiable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copyable<int>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copyable<const int>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copyable<int[10]>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copyable<EEnum>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<EEnum>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copyable<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copyable<CClass*>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<CClass*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivially_copyable<CClass&>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<CClass&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copyable<CTriviallyCopyable>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<CTriviallyCopyable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivially_copyable<CNonTriviallyCopyable>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<CNonTriviallyCopyable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copyable<CTriviallyCopyable[10]>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<CTriviallyCopyable[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivially_copyable<CNonTriviallyCopyable[10]>::value;

		wcout << L"TYPE TRAIT [is_trivially_copyable<CNonTriviallyCopyable[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsStandardLayout(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_standard_layout<int>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_standard_layout<const int>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_standard_layout<int[10]>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_standard_layout<EEnum>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<EEnum>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_standard_layout<EEnumClass>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<EEnumClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_standard_layout<CClass*>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<CClass*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_standard_layout<CClass&>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<CClass&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_standard_layout<CStandardLayout>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<CStandardLayout>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_standard_layout<CNonStandardLayout>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<CNonStandardLayout>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_standard_layout<CStandardLayout[10]>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<CStandardLayout[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_standard_layout<CNonStandardLayout[10]>::value;

		wcout << L"TYPE TRAIT [is_standard_layout<CNonStandardLayout[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsEmpty(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_empty<CEmpty>::value;

		wcout << L"TYPE TRAIT [is_empty<CEmpty>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_empty<const CEmpty>::value;

		wcout << L"TYPE TRAIT [is_empty<const CEmpty>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_empty<CNonEmpty>::value;

		wcout << L"TYPE TRAIT [is_empty<CNonEmpty>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_empty<int>::value;

		wcout << L"TYPE TRAIT [is_empty<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_empty<CEmpty[10]>::value;

		wcout << L"TYPE TRAIT [is_empty<CEmpty[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsPolymorphic(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_polymorphic<CPolymorphic>::value;

		wcout << L"TYPE TRAIT [is_polymorphic<CPolymorphic>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_polymorphic<const CPolymorphic>::value;

		wcout << L"TYPE TRAIT [is_polymorphic<const CPolymorphic>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_polymorphic<CNonPolymorphic>::value;

		wcout << L"TYPE TRAIT [is_polymorphic<CNonPolymorphic>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsAbstract(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_abstract<CAbstract>::value;

		wcout << L"TYPE TRAIT [is_abstract<CAbstract>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_abstract<const CAbstract>::value;

		wcout << L"TYPE TRAIT [is_abstract<const CAbstract>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_abstract<CNonAbstract>::value;

		wcout << L"TYPE TRAIT [is_abstract<CNonAbstract>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsFinal(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_final<CFinal>::value;

		wcout << L"TYPE TRAIT [is_final<CFinal>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_final<const CFinal>::value;

		wcout << L"TYPE TRAIT [is_final<const CFinal>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_final<CNonFinal>::value;

		wcout << L"TYPE TRAIT [is_final<CNonFinal>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitHasVirtualDestructor(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=has_virtual_destructor<CVirtualDestructor>::value;

		wcout << L"TYPE TRAIT [has_virtual_destructor<CVirtualDestructor>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=has_virtual_destructor<const CVirtualDestructor>::value;

		wcout << L"TYPE TRAIT [has_virtual_destructor<const CVirtualDestructor>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=has_virtual_destructor<CNonVirtualDestructor>::value;

		wcout << L"TYPE TRAIT [has_virtual_destructor<CNonVirtualDestructor>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitHasUniqueObjectRepresentations(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati IMPLEMENTATION DEFINED VALUE.
		bool													Value=has_unique_object_representations<int>::value;

		wcout << L"TYPE TRAIT [has_unique_object_representations<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati IMPLEMENTATION DEFINED VALUE.
		bool													Value=has_unique_object_representations<char>::value;

		wcout << L"TYPE TRAIT [has_unique_object_representations<char>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati IMPLEMENTATION DEFINED VALUE.
		bool													Value=has_unique_object_representations<float>::value;

		wcout << L"TYPE TRAIT [has_unique_object_representations<float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati IMPLEMENTATION DEFINED VALUE.
		bool													Value=has_unique_object_representations<double>::value;

		wcout << L"TYPE TRAIT [has_unique_object_representations<double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati IMPLEMENTATION DEFINED VALUE.
		bool													Value=has_unique_object_representations<bool>::value;

		wcout << L"TYPE TRAIT [has_unique_object_representations<bool>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=has_unique_object_representations<CUniqueObjectRepresentations>::value;

		wcout << L"TYPE TRAIT [has_unique_object_representations<CUniqueObjectRepresentations>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=has_unique_object_representations<const CUniqueObjectRepresentations>::value;

		wcout << L"TYPE TRAIT [has_unique_object_representations<const CUniqueObjectRepresentations>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=has_unique_object_representations<CNonUniqueObjectRepresentations>::value;

		wcout << L"TYPE TRAIT [has_unique_object_representations<CNonUniqueObjectRepresentations>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitAlignmentOf(void)
{
	PrintLineSeparator();

	{
		size_t													Value=alignment_of<CClass>::value;
		size_t													Size=sizeof(CClass);

		wcout << L"TYPE TRAIT [alignment_of<CClass>::value] - VALUE [" << Value << L"] SIZE [" << Size << L"]." << endl;
	}

	PrintLineSeparator();

	{
		size_t													Value=alignment_of<CUniqueObjectRepresentations>::value;
		size_t													Size=sizeof(CUniqueObjectRepresentations);

		wcout << L"TYPE TRAIT [alignment_of<CUniqueObjectRepresentations>::value] - VALUE [" << Value << L"] SIZE [" << Size << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitRank(void)
{
	PrintLineSeparator();

	{
		size_t													Value=rank<int[10][20]>::value;

		wcout << L"TYPE TRAIT [rank<int[10][20]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		size_t													Value=rank<int[10][20][30]>::value;

		wcout << L"TYPE TRAIT [rank<int[10][20][30]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		size_t													Value=rank<int[]>::value;

		wcout << L"TYPE TRAIT [rank<int[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		size_t													Value=rank<int[][10]>::value;

		wcout << L"TYPE TRAIT [rank<int[][10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati VALUE [0].
		size_t													Value=rank<int*>::value;

		wcout << L"TYPE TRAIT [rank<int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati VALUE [0], pretoze TYPE NIE JE C-ARRAY.
		size_t													Value=rank<CClass>::value;

		wcout << L"TYPE TRAIT [rank<CClass>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitExtent(void)
{
	PrintLineSeparator();

	{
		size_t													Value=extent<int[10][20][30],0>::value;

		wcout << L"TYPE TRAIT [extent<int[10][20][30],0>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		size_t													Value=extent<int[10][20][30],1>::value;

		wcout << L"TYPE TRAIT [extent<int[10][20][30],1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		size_t													Value=extent<int[10][20][30],2>::value;

		wcout << L"TYPE TRAIT [extent<int[10][20][30],2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati VALUE [0], pretoze DIMENSION s INDEX 3 NEEXISTUJE.
		size_t													Value=extent<int[10][20][30],3>::value;

		wcout << L"TYPE TRAIT [extent<int[10][20][30],3>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati VALUE [0], pretoze DIMENSION nema specifikovany SIZE.
		size_t													Value=extent<int[][20],0>::value;

		wcout << L"TYPE TRAIT [extent<int[][20],0>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati VALUE [20], pretoze DIMENSION nema specifikovany SIZE.
		size_t													Value=extent<int[][20],1>::value;

		wcout << L"TYPE TRAIT [extent<int[][20],1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati VALUE [0], pretoze TYPE NIE JE C-ARRAY.
		size_t													Value=extent<CClass,0>::value;

		wcout << L"TYPE TRAIT [extent<CClass,0>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati VALUE [0], pretoze TYPE NIE JE C-ARRAY.
		size_t													Value=extent<CClass,2>::value;

		wcout << L"TYPE TRAIT [extent<CClass,2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitUnderlyingType(void)
{
	PrintLineSeparator();

	{
		wstring													Value=GetTypeInfoName(typeid(underlying_type<EEnumInt>::type));

		wcout << L"TYPE TRAIT [underlying_type<EEnumInt>::type] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wstring													Value=GetTypeInfoName(typeid(underlying_type<EEnumLong>::type));

		wcout << L"TYPE TRAIT [underlying_type<EEnumLong>::type] - VALUE [" << Value << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!! COMPILER hodi ERROR, pretoze TYPE [CClass] nie je ENUM a pre NON-ENUM CLASSES TYPE [type] nie je definovany.
		wstring													Value=GetTypeInfoName(typeid(underlying_type<CClass>::type));

		wcout << L"TYPE TRAIT [underlying_type<CClass>::type] - VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsInvocable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_invocable<int(*)(void)>::value;

		wcout << L"TYPE TRAIT [is_invocable<int(*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_invocable<int(*)(void),double>::value;

		wcout << L"TYPE TRAIT [is_invocable<int(*)(void),double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_invocable<int(*)(double),double>::value;

		wcout << L"TYPE TRAIT [is_invocable<int(*)(double),double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(*FUNCTION)(double) noexcept=nullptr;

		// !!! Vrati TRUE, lebo hoci FUNCTION ma PARAMETER TYPE [double], tak ARGUMENT [int] je CONVERTIBLE na TYPE [double].
		bool													Value=is_invocable<decltype(FUNCTION),int>::value;

		wcout << L"TYPE TRAIT [is_invocable<void(*)(double) noexcept,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS 'CInvocable' ma OPERATOR [OPERATOR()] s PARAMETERS [double,double].
		bool													Value=is_invocable<CInvocable,double,double>::value;

		wcout << L"TYPE TRAIT [is_invocable<CInvocable,double,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS 'CInvocable' NEMA OPERATOR [OPERATOR()] s PARAMETERS [double].
		bool													Value=is_invocable<CInvocable,double>::value;

		wcout << L"TYPE TRAIT [is_invocable<CInvocable,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowInvocable(void)
{
	PrintLineSeparator();

	{
		void													(*FUNCTION)(void) noexcept=nullptr;

		// !!! Vrati TRUE.
		bool													Value=is_nothrow_invocable<decltype(FUNCTION)>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable<void(*)(void) noexcept>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(*FUNCTION)(void)=nullptr;

		// !!! Vrati FALSE, pretoze FUNCTION MOZE hodit EXCEPTIONS.
		bool													Value=is_nothrow_invocable<decltype(FUNCTION)>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable<void(*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(*FUNCTION)(void) noexcept=nullptr;

		// !!! Vrati FALSE.
		bool													Value=is_nothrow_invocable<decltype(FUNCTION),double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable<void(*)(void) noexcept,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(*FUNCTION)(double) noexcept=nullptr;

		// !!! Vrati TRUE.
		bool													Value=is_nothrow_invocable<decltype(FUNCTION),double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable<void(*)(double) noexcept,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(*FUNCTION)(double) noexcept=nullptr;

		// !!! Vrati TRUE, lebo hoci FUNCTION ma PARAMETER TYPE [double], tak ARGUMENT [int] je CONVERTIBLE na TYPE [double].
		bool													Value=is_nothrow_invocable<decltype(FUNCTION),int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable<void(*)(double) noexcept,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS 'CInvocable' ma OPERATOR [OPERATOR()] s PARAMETERS [double,double,double], ktory JE oznaceny KEYWORD [noexcept].
		bool													Value=is_nothrow_invocable<CInvocable,double,double,double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable<CInvocable,double,double,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS 'CInvocable' NEMA OPERATOR [OPERATOR()] s PARAMETERS [double], ktory JE oznaceny KEYWORD [noexcept].
		bool													Value=is_nothrow_invocable<CInvocable,double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable<CInvocable,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS 'CInvocable' MA OPERATOR [OPERATOR()] s PARAMETERS [double], ale ten NIE JE oznaceny KEYWORD [noexcept].
		bool													Value=is_nothrow_invocable<CInvocable,double,double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable<CInvocable,double,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsInvocableR(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_invocable_r<int,int(*)(void)>::value;

		wcout << L"TYPE TRAIT [is_invocable_r<int,int(*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze TYPE [wstring] nie je CONVERTIBLE na RETURN VALUE TYPE [int].
		bool													Value=is_invocable_r<wstring,int(*)(void)>::value;

		wcout << L"TYPE TRAIT [is_invocable_r<wstring,int(*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}


	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze TYPE [short] je CONVERTIBLE na RETURN VALUE TYPE [int].
		bool													Value=is_invocable_r<short,int(*)(void)>::value;

		wcout << L"TYPE TRAIT [is_invocable_r<short,int(*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo FUNCTION NEMA PARAMETER TYPE [double].
		bool													Value=is_invocable_r<int,int(*)(void),double>::value;

		wcout << L"TYPE TRAIT [is_invocable_r<int,int(*)(void),double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_invocable_r<int,int(*)(double),double>::value;

		wcout << L"TYPE TRAIT [is_invocable_r<int,int(*)(double),double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(*FUNCTION)(double) noexcept=nullptr;

		// !!! Vrati TRUE, lebo hoci FUNCTION ma PARAMETER TYPE [double], tak ARGUMENT [int] je CONVERTIBLE na TYPE [double].
		bool													Value=is_invocable_r<void,decltype(FUNCTION),int>::value;

		wcout << L"TYPE TRAIT [is_invocable_r<void,void(*)(double) noexcept,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS 'CInvocable' ma OPERATOR [OPERATOR()] s PARAMETERS [double,double] a RETURN VALUE TYPE [void].
		bool													Value=is_invocable_r<void,CInvocable,double,double>::value;

		wcout << L"TYPE TRAIT [is_invocable_r<void,CInvocable,double,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS 'CInvocable' NEMA OPERATOR [OPERATOR()] s PARAMETERS [double] a RETURN VALUE TYPE [void].
		bool													Value=is_invocable_r<void,CInvocable,double>::value;

		wcout << L"TYPE TRAIT [is_invocable_r<void,CInvocable,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS 'CInvocable' NEMA OPERATOR [OPERATOR()] s PARAMETERS [double,double] a RETURN VALUE TYPE [int].
		bool													Value=is_invocable_r<int,CInvocable,double,double>::value;

		wcout << L"TYPE TRAIT [is_invocable_r<int,CInvocable,double,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowInvocableR(void)
{
	PrintLineSeparator();

	{
		void													(*FUNCTION)(void) noexcept=nullptr;

		// !!! Vrati TRUE.
		bool													Value=is_nothrow_invocable_r<void,decltype(FUNCTION)>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<void,void(*)(void) noexcept>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														(*FUNCTION)(void) noexcept=nullptr;

		// !!! Vrati FALSE, pretoze TYPE [wstring] nie je CONVERTIBLE na RETURN VALUE TYPE [int].
		bool													Value=is_nothrow_invocable_r<wstring,decltype(FUNCTION)>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<wstring,int(*)(void) noexcept>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		double													(*FUNCTION)(void) noexcept=nullptr;

		// !!! Vrati TRUE, pretoze TYPE [double] je CONVERTIBLE na RETURN VALUE TYPE [int].
		bool													Value=is_nothrow_invocable_r<int,decltype(FUNCTION)>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<int,double(*)(void) noexcept>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(*FUNCTION)(void)=nullptr;

		// !!! Vrati TRUE, lebo FUNCTION NIE je oznacena pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_invocable_r<void,decltype(FUNCTION)>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<void,void(*)(void)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														(*FUNCTION)(void) noexcept=nullptr;

		// !!! Vrati TRUE, pretoze TYPE [short] je CONVERTIBLE na RETURN VALUE TYPE [int].
		bool													Value=is_nothrow_invocable_r<short,decltype(FUNCTION)>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<short,int(*)(void) noexcept>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														(*FUNCTION)(void) noexcept=nullptr;

		// !!! Vrati FALSE, lebo FUNCTION NEMA PARAMETER TYPE [double].
		bool													Value=is_nothrow_invocable_r<int,decltype(FUNCTION),double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<int,int(*)(void) noexcept,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														(*FUNCTION)(double) noexcept=nullptr;

		// !!! Vrati TRUE.
		bool													Value=is_nothrow_invocable_r<int,decltype(FUNCTION),double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<int,int(*)(double) noexcept,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(*FUNCTION)(double) noexcept=nullptr;

		// !!! Vrati TRUE, lebo hoci FUNCTION ma PARAMETER TYPE [double], tak ARGUMENT [int] je CONVERTIBLE na TYPE [double].
		bool													Value=is_nothrow_invocable_r<void,decltype(FUNCTION),int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<void,void(*)(double) noexcept,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS 'CInvocable' ma OPERATOR [OPERATOR()] s PARAMETERS [double,double,double], ktory JE oznaceny KEYWORD [noexcept].
		bool													Value=is_nothrow_invocable_r<void,CInvocable,double,double,double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<void,CInvocable,double,double,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS 'CInvocable' NEMA OPERATOR [OPERATOR()] s PARAMETERS [double], ktory JE oznaceny KEYWORD [noexcept].
		bool													Value=is_nothrow_invocable_r<void,CInvocable,double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<void,CInvocable,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS 'CInvocable' MA OPERATOR [OPERATOR()] s PARAMETERS [double], ale ten NIE JE oznaceny KEYWORD [noexcept].
		bool													Value=is_nothrow_invocable<void,CInvocable,double,double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_invocable_r<void,CInvocable,double,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitInvokeResult(void)
{
	PrintLineSeparator();

	{
		int														(*FUNCTION)(int,double) noexcept=nullptr;
		wstring													Value=GetTypeInfoName(typeid(invoke_result<decltype(FUNCTION),int,double>::type));

		wcout << L"TYPE TRAIT [invoke_result<int(*)(int,double) noexcept,int,double>::type] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		void													(*FUNCTION)(int,double) noexcept=nullptr;
		wstring													Value=GetTypeInfoName(typeid(invoke_result<decltype(FUNCTION),int,double>::type));

		wcout << L"TYPE TRAIT [invoke_result<void(*)(int,double) noexcept,int,double>::type] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wstring													Value=GetTypeInfoName(typeid(invoke_result<CInvokeResult,int,double>::type));

		wcout << L"TYPE TRAIT [invoke_result<CInvokeResult,int,double>::type] - VALUE [" << Value << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze FUNCTION 'FUNCTION' NEMA 3 PARAMETERS.
	{
		void													(*FUNCTION)(int,double) noexcept=nullptr;
		wstring													Value=GetTypeInfoName(typeid(invoke_result<decltype(FUNCTION),int,double,double>::type));

		wcout << L"TYPE TRAIT [invoke_result<void(*)(int,double) noexcept,int,double,double>::type] - VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTypeTraitsValues();
	//TestTypeTraitsIntegralConstant();
	//TestTypeTraitsAndDeclType();
	//TestTypeTraitIsVoid();
	//TestTypeTraitIsIntegral();
	//TestTypeTraitIsFloatingPoint();
	//TestTypeTraitIsArray();
	//TestTypeTraitIsPointer();
	//TestTypeTraitIsNullPointer();
	//TestTypeTraitIsMemberObjectPointer();
	//TestTypeTraitIsMemberFunctionPointer();
	//TestTypeTraitIsLValueReference();
	//TestTypeTraitIsRValueReference();
	//TestTypeTraitIsEnum();
	//TestTypeTraitIsClass();
	//TestTypeTraitIsUnion();
	//TestTypeTraitIsFunction();
	//TestTypeTraitIsReference();
	//TestTypeTraitIsMemberPointer();
	//TestTypeTraitIsArithmetic();
	//TestTypeTraitIsFundamental();
	//TestTypeTraitIsScalar();
	//TestTypeTraitIsObject();
	//TestTypeTraitIsCompound();
	//TestTypeTraitIsSigned();
	//TestTypeTraitIsUnsigned();
	//TestTypeTraitIsConst();
	//TestTypeTraitIsVolatile();
	//TestTypeTraitIsAggregate();
	//TestTypeTraitIsTrivial();
	//TestTypeTraitIsTriviallyCopiable();
	//TestTypeTraitIsStandardLayout();
	//TestTypeTraitIsEmpty();
	//TestTypeTraitIsPolymorphic();
	//TestTypeTraitIsAbstract();
	//TestTypeTraitIsFinal();
	//TestTypeTraitHasVirtualDestructor();
	//TestTypeTraitHasUniqueObjectRepresentations();
	//TestTypeTraitAlignmentOf();
	//TestTypeTraitRank();
	//TestTypeTraitExtent();
	//TestTypeTraitUnderlyingType();
	//TestTypeTraitIsInvocable();
	//TestTypeTraitIsNoThrowInvocable();
	//TestTypeTraitIsInvocableR();
	//TestTypeTraitIsNoThrowInvocableR();
	TestTypeTraitInvokeResult();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------