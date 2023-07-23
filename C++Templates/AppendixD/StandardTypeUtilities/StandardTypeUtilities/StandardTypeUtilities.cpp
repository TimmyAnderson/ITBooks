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
#include "CIsConstructible.h"
#include "CNonIsConstructible.h"
#include "CIsTriviallyConstructible.h"
#include "CNonIsTriviallyConstructible1.h"
#include "CNonIsTriviallyConstructible2.h"
#include "CNonIsTriviallyConstructible3.h"
#include "CIsNoThrowConstructible.h"
#include "CNonIsNoThrowConstructible.h"
#include "CIsDefaultConstructible.h"
#include "CNonIsDefaultConstructible.h"
#include "CIsTriviallyDefaultConstructible.h"
#include "CNonIsTriviallyDefaultConstructible.h"
#include "CIsNoThrowDefaultConstructible.h"
#include "CNonIsNoThrowDefaultConstructible1.h"
#include "CNonIsNoThrowDefaultConstructible2.h"
#include "CIsCopyConstructible1.h"
#include "CIsCopyConstructible2.h"
#include "CNonIsCopyConstructible.h"
#include "CIsTriviallyCopyConstructible.h"
#include "CNonIsTriviallyCopyConstructible.h"
#include "CIsNoThrowCopyConstructible.h"
#include "CNonIsNoThrowCopyConstructible.h"
#include "CIsMoveConstructible1.h"
#include "CIsMoveConstructible2.h"
#include "CNonIsMoveConstructible.h"
#include "CIsTriviallyMoveConstructible.h"
#include "CNonIsTriviallyMoveConstructible.h"
#include "CIsNoThrowMoveConstructible.h"
#include "CNonIsNoThrowMoveConstructible.h"
#include "CIsAssignable.h"
#include "CNonIsAssignable.h"
#include "CIsTriviallyAssignable.h"
#include "CNonIsTriviallyAssignable.h"
#include "CIsNoThrowAssignable.h"
#include "CNonIsNoThrowAssignable.h"
#include "CIsCopyAssignable1.h"
#include "CIsCopyAssignable2.h"
#include "CNonIsCopyAssignable.h"
#include "CIsTriviallyCopyAssignable.h"
#include "CNonIsTriviallyCopyAssignable.h"
#include "CIsNoThrowCopyAssignable.h"
#include "CNonIsNoThrowCopyAssignable.h"
#include "CIsMoveAssignable1.h"
#include "CIsMoveAssignable2.h"
#include "CNonIsMoveAssignable.h"
#include "CIsTriviallyMoveAssignable.h"
#include "CNonIsTriviallyMoveAssignable.h"
#include "CIsNoThrowMoveAssignable.h"
#include "CNonIsNoThrowMoveAssignable.h"
#include "CIsDestructible1.h"
#include "CIsDestructible2.h"
#include "CNonIsDestructible.h"
#include "CIsTriviallyDestructible.h"
#include "CNonIsTriviallyDestructible.h"
#include "CIsNoThrowDestructible.h"
#include "CNonIsNoThrowDestructible.h"
#include "CIsSwappableWith.h"
#include "CNonIsSwappableWith.h"
#include "CIsNoThrowSwappableWith.h"
#include "CNonIsNoThrowSwappableWith.h"
#include "CIsSwappable.h"
#include "CNonIsSwappable.h"
#include "CIsNoThrowSwappable.h"
#include "CNonIsNoThrowSwappable.h"
#include "CIsBaseOfBase.h"
#include "CIsBaseOfDerived1.h"
#include "CIsBaseOfDerived2.h"
#include "CIsBaseOfSuperDerived.h"
#include "CIsConvertible.h"
#include "CNonIsConvertible.h"
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
		int														(*FUNCTION)(int,double) noexcept=nullptr;
		wstring													Value=GetTypeInfoName(typeid(invoke_result<decltype(FUNCTION),int,float>::type));

		wcout << L"TYPE TRAIT [invoke_result<int(*)(int,double) noexcept,int,float>::type] - VALUE [" << Value << L"]." << endl;
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
void TestTypeTraitIsConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_constructible<CIsConstructible,int,double>::value;

		wcout << L"TYPE TRAIT [is_constructible<CIsConstructible,int,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo 2. ARGUMENT TYPE [float] je CONVERTIBLE na 2. PARAMETER TYPE [double].
		bool													Value=is_constructible<CIsConstructible,int,float>::value;

		wcout << L"TYPE TRAIT [is_constructible<CIsConstructible,int,float>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CONSTRUCTOR s 3 PARAMETERS NEEXISTUJE.
		bool													Value=is_constructible<CIsConstructible,int,double,int>::value;

		wcout << L"TYPE TRAIT [is_constructible<CIsConstructible,int,double,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CONSTRUCTOR s 2 PARAMETERS NEEXISTUJE.
		bool													Value=is_constructible<CNonIsConstructible,int,double>::value;

		wcout << L"TYPE TRAIT [is_constructible<CNonIsConstructible,int,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CONSTRUCTOR s 0 PARAMETERS existuje.
		bool													Value=is_constructible<CNonIsConstructible>::value;

		wcout << L"TYPE TRAIT [is_constructible<CNonIsConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTriviallyConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS NEMA ziaden CONSTRUCTOR a tak C++ generuje DEFAULT CONSTRUCTOR.
		bool													Value=is_trivially_constructible<CIsTriviallyConstructible>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CIsTriviallyConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS NEMA ziaden COPY CONSTRUCTOR a tak C++ generuje DEFAULT COPY CONSTRUCTOR.
		bool													Value=is_trivially_constructible<CIsTriviallyConstructible,const CIsTriviallyConstructible&>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CIsTriviallyConstructible,const CIsTriviallyConstructible&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS NEMA ziaden MOVE CONSTRUCTOR a tak C++ generuje DEFAULT MOVE CONSTRUCTOR.
		bool													Value=is_trivially_constructible<CIsTriviallyConstructible,CIsTriviallyConstructible&&>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CIsTriviallyConstructible,CIsTriviallyConstructible&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS NEMA ziaden CONSTRUCTOR a C++ NEGENERUJE DEFULAT (TRIVIAL) CONSTRUCTORS s PARAMETERS.
		bool													Value=is_trivially_constructible<CIsTriviallyConstructible,int,double>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CIsTriviallyConstructible,int,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoTriviallyConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS ma FIELD, ktory NIE JE TRIVIALLY CONSTRUCTIBLE.
		bool													Value=is_trivially_constructible<CNonIsTriviallyConstructible1>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CNonIsTriviallyConstructible1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS MA definovany CONSTRUCTOR s 0 PARAMETERS a tym padom NIE JE TRIVIALLY CONSTRUCTIBLE.
		bool													Value=is_trivially_constructible<CNonIsTriviallyConstructible2>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CNonIsTriviallyConstructible2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS MA definovany CONSTRUCTOR s 0 PARAMETERS a tym padom NIE JE TRIVIALLY CONSTRUCTIBLE.
		bool													Value=is_trivially_constructible<CNonIsTriviallyConstructible2,int,double>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CNonIsTriviallyConstructible2,int,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS NEMA definovany COPY CONSTRUCTOR a tak je vygenerovany IMPLICIT (TRIVIAL) COPY CONSTRUCTOR.
		bool													Value=is_trivially_constructible<CNonIsTriviallyConstructible2,const CNonIsTriviallyConstructible2&>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CNonIsTriviallyConstructible2,const CNonIsTriviallyConstructible2&>::value] - VALUE [" << Value << L"]." << endl;
	}


	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS NEMA definovany MOVE CONSTRUCTOR a tak je vygenerovany IMPLICIT (TRIVIAL) MOVE CONSTRUCTOR.
		bool													Value=is_trivially_constructible<CNonIsTriviallyConstructible2,CNonIsTriviallyConstructible2&&>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CNonIsTriviallyConstructible2,CNonIsTriviallyConstructible2&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS MA definovany DESTRUCTOR a tym padom NIE JE TRIVIALLY CONSTRUCTIBLE.
		bool													Value=is_trivially_constructible<CNonIsTriviallyConstructible3>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CNonIsTriviallyConstructible3>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS MA definovany DESTRUCTOR a tym padom NIE JE TRIVIALLY CONSTRUCTIBLE.
		bool													Value=is_trivially_constructible<CNonIsTriviallyConstructible3,const CNonIsTriviallyConstructible3&>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CNonIsTriviallyConstructible3,const CNonIsTriviallyConstructible3&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS MA definovany DESTRUCTOR a tym padom NIE JE TRIVIALLY CONSTRUCTIBLE.
		bool													Value=is_trivially_constructible<CNonIsTriviallyConstructible3,CNonIsTriviallyConstructible3&&>::value;

		wcout << L"TYPE TRAIT [is_trivially_constructible<CNonIsTriviallyConstructible3,CNonIsTriviallyConstructible3&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CONSTRUCTOR s 2 PARAMETERS je DEFINED a je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_constructible<CIsNoThrowConstructible,int,double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_constructible<CIsNoThrowConstructible,int,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CONSTRUCTOR s 3 PARAMETERS NIE je DEFINED.
		bool													Value=is_nothrow_constructible<CIsNoThrowConstructible,int,double,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_constructible<CIsNoThrowConstructible,int,double,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CONSTRUCTOR s 1 PARAMETER je DEFINED, ale NIE je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_constructible<CIsNoThrowConstructible,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_constructible<CIsNoThrowConstructible,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CONSTRUCTOR s 2 PARAMETERS je DEFINED, ale NIE je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_constructible<CNonIsNoThrowConstructible,int,double>::value;

		wcout << L"TYPE TRAIT [is_nothrow_constructible<CNonIsNoThrowConstructible,int,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CONSTRUCTOR s 3 PARAMETERS NIE je DEFINED.
		bool													Value=is_nothrow_constructible<CNonIsNoThrowConstructible,int,double,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_constructible<CNonIsNoThrowConstructible,int,double,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CONSTRUCTOR s 1 PARAMETER je DEFINED a je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_constructible<CNonIsNoThrowConstructible,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_constructible<CNonIsNoThrowConstructible,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsDefaultConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo je definovany DEFAULT CONSTRUCTOR.
		bool													Value=is_default_constructible<CIsDefaultConstructible>::value;

		wcout << L"TYPE TRAIT [is_default_constructible<CIsDefaultConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_default_constructible<int>::value;

		wcout << L"TYPE TRAIT [is_default_constructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoDefaultConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo je definovany CONSTRUCTOR s PARAMETERS a tym padom nie je definovany DEFAULT CONSTRUCTOR.
		bool													Value=is_default_constructible<CNonIsDefaultConstructible>::value;

		wcout << L"TYPE TRAIT [is_default_constructible<CNonIsDefaultConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTriviallyDefaultConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo NIE je definovany DEFAULT CONSTRUCTOR a C++ vygeneruje TRIVIAL DEFAULT CONSTRUCTOR.
		bool													Value=is_trivially_default_constructible<CIsTriviallyDefaultConstructible>::value;

		wcout << L"TYPE TRAIT [is_trivially_default_constructible<CIsTriviallyDefaultConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_default_constructible<int>::value;

		wcout << L"TYPE TRAIT [is_trivially_default_constructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoTriviallyDefaultConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo je definovany DEFAULT CONSTRUCTOR a tym padom sa nejedna o TRIVIAL DEFAULT CONSTRUCTOR.
		bool													Value=is_trivially_default_constructible<CNonIsTriviallyDefaultConstructible>::value;

		wcout << L"TYPE TRAIT [is_trivially_default_constructible<CNonIsTriviallyDefaultConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowDefaultConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo je definovany DEFAULT CONSTRUCTOR a oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_default_constructible<CIsNoThrowDefaultConstructible>::value;

		wcout << L"TYPE TRAIT [is_nothrow_default_constructible<CIsNoThrowDefaultConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_default_constructible<int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_default_constructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowDefaultConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo je NIE JE definovany DEFAULT CONSTRUCTOR.
		bool													Value=is_nothrow_default_constructible<CNonIsNoThrowDefaultConstructible1>::value;

		wcout << L"TYPE TRAIT [is_nothrow_default_constructible<CNonIsNoThrowDefaultConstructible1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo je JE definovany DEFAULT CONSTRUCTOR, ale NIE JE oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_default_constructible<CNonIsNoThrowDefaultConstructible2>::value;

		wcout << L"TYPE TRAIT [is_nothrow_default_constructible<CNonIsNoThrowDefaultConstructible2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsCopyConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo je definovany COPY CONSTRUCTOR.
		bool													Value=is_copy_constructible<CIsCopyConstructible1>::value;

		wcout << L"TYPE TRAIT [is_copy_constructible<CIsCopyConstructible1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo je GENEROVANY DEFAULT COPY CONSTRUCTOR.
		bool													Value=is_copy_constructible<CIsCopyConstructible2>::value;

		wcout << L"TYPE TRAIT [is_copy_constructible<CIsCopyConstructible2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_copy_constructible<int>::value;

		wcout << L"TYPE TRAIT [is_copy_constructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_copy_constructible<int&>::value;

		wcout << L"TYPE TRAIT [is_copy_constructible<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_copy_constructible<int&&>::value;

		wcout << L"TYPE TRAIT [is_copy_constructible<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_copy_constructible<int*>::value;

		wcout << L"TYPE TRAIT [is_copy_constructible<int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoCopyConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo COPY CONSTRUCTOR NIE je definovany a DEFUALT COPY CONSTRUCTOR je DELETED.
		bool													Value=is_copy_constructible<CNonIsCopyConstructible>::value;

		wcout << L"TYPE TRAIT [is_copy_constructible<CNonIsCopyConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo hoci COPY CONSTRUCTOR NIE JE DEFINOVANY, C++ vygeneruje DEFUALT COPY CONSTRUCTOR.
		bool													Value=is_copy_constructible<CIsCopyConstructible2>::value;

		wcout << L"TYPE TRAIT [is_copy_constructible<CIsCopyConstructible2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTriviallyCopyConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo NIE je definovany COPY CONSTRUCTOR a C++ vygeneruje DEFAULT (TRIVIAL) COPY CONSTRUCTOR.
		bool													Value=is_trivially_copy_constructible<CIsTriviallyCopyConstructible>::value;

		wcout << L"TYPE TRAIT [is_trivially_copy_constructible<CIsTriviallyCopyConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copy_constructible<int>::value;

		wcout << L"TYPE TRAIT [is_trivially_copy_constructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoTriviallyCopyConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo je definovany COPY CONSTRUCTOR a tym padom sa nejedna o TRIVIAL COPY CONSTRUCTOR.
		bool													Value=is_trivially_copy_constructible<CNonIsTriviallyCopyConstructible>::value;

		wcout << L"TYPE TRAIT [is_trivially_copy_constructible<CNonIsTriviallyCopyConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowCopyConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo COPY CONSTRUCTOR je definovany a je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_copy_constructible<CIsNoThrowCopyConstructible>::value;

		wcout << L"TYPE TRAIT [is_nothrow_copy_constructible<CIsNoThrowCopyConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_copy_constructible<int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_copy_constructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowCopyConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo COPY CONSTRUCTOR je definovany ale NIE je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_copy_constructible<CNonIsNoThrowCopyConstructible>::value;

		wcout << L"TYPE TRAIT [is_nothrow_copy_constructible<CNonIsNoThrowCopyConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsMoveConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo je definovany MOVE CONSTRUCTOR.
		bool													Value=is_move_constructible<CIsMoveConstructible1>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<CIsMoveConstructible1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo MOVE CONSTRUCTOR NIE JE definovany, ale C++ vygeneruje DEFAULT (TRIVIAL) MOVE CONSTRUCTOR. .
		bool													Value=is_move_constructible<CIsMoveConstructible2>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<CIsMoveConstructible2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_move_constructible<int>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_move_constructible<int&>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_move_constructible<int&&>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_move_constructible<int*>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_move_constructible<void>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo MOVE CONSTRUCTOR NIE JE definovany, ale C++ vygeneruje DEFAULT (TRIVIAL) MOVE CONSTRUCTOR. .
		bool													Value=is_move_constructible<CIsMoveConstructible2>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<CIsMoveConstructible2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoMoveConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo MOVE CONSTRUCTOR NIE je definovany a DEFUALT MOVE CONSTRUCTOR je DELETED.
		bool													Value=is_move_constructible<CNonIsMoveConstructible>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<CNonIsMoveConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo MOVE CONSTRUCTOR NIE JE definovany, ale C++ vygeneruje DEFAULT (TRIVIAL) MOVE CONSTRUCTOR. .
		bool													Value=is_move_constructible<CIsMoveConstructible2>::value;

		wcout << L"TYPE TRAIT [is_move_constructible<CIsMoveConstructible2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTriviallyMoveConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo NIE je definovany MOVE CONSTRUCTOR a C++ vygeneruje DEFAULT (TRIVIAL) MOVE CONSTRUCTOR.
		bool													Value=is_trivially_move_constructible<CIsTriviallyMoveConstructible>::value;

		wcout << L"TYPE TRAIT [is_trivially_move_constructible<CIsTriviallyMoveConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_move_constructible<int>::value;

		wcout << L"TYPE TRAIT [is_trivially_move_constructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoTriviallyMoveConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo je definovany MOVE CONSTRUCTOR a tym padom sa nejedna o TRIVIAL MOVE CONSTRUCTOR.
		bool													Value=is_trivially_move_constructible<CNonIsTriviallyMoveConstructible>::value;

		wcout << L"TYPE TRAIT [is_trivially_move_constructible<CNonIsTriviallyMoveConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowMoveConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo MOVE CONSTRUCTOR je definovany a je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_move_constructible<CIsNoThrowMoveConstructible>::value;

		wcout << L"TYPE TRAIT [is_nothrow_move_constructible<CIsNoThrowMoveConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_move_constructible<int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_move_constructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowMoveConstructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo MOVE CONSTRUCTOR je definovany ale NIE je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_move_constructible<CNonIsNoThrowMoveConstructible>::value;

		wcout << L"TYPE TRAIT [is_nothrow_move_constructible<CNonIsNoThrowMoveConstructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsAssignable(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vrati FALSE, lebo TYPE [int] je NON-REFERENCE, NON-CLASS TYPE.
		bool													Value=is_assignable<int,int>::value;

		wcout << L"TYPE TRAIT [is_assignable<int,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_assignable<int&,int>::value;

		wcout << L"TYPE TRAIT [is_assignable<int&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_assignable<int&&,int>::value;

		wcout << L"TYPE TRAIT [is_assignable<int&&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_assignable<int&,int&>::value;

		wcout << L"TYPE TRAIT [is_assignable<int&,int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_assignable<int&&,int&>::value;

		wcout << L"TYPE TRAIT [is_assignable<int&&,int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_assignable<int&&,int&&>::value;

		wcout << L"TYPE TRAIT [is_assignable<int&&,int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [double] je mozne priradit do VARIABLE TYPE [int].
		bool													Value=is_assignable<int&,double>::value;

		wcout << L"TYPE TRAIT [is_assignable<int&,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [CIsAssignable] ma definovany OPERATOR [OPERATOR=] pre TYPE [CNonTrivialType].
		bool													Value=is_assignable<CIsAssignable,CNonTrivialType>::value;

		wcout << L"TYPE TRAIT [is_assignable<CIsAssignable,CNonTrivialType>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [CIsAssignable] ma definovany OPERATOR [OPERATOR=] pre TYPE [CNonTrivialType].
		bool													Value=is_assignable<CIsAssignable&,CNonTrivialType>::value;

		wcout << L"TYPE TRAIT [is_assignable<CIsAssignable&,CNonTrivialType>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [CIsAssignable] ma definovany OPERATOR [OPERATOR=] pre TYPE [CNonTrivialType].
		bool													Value=is_assignable<CIsAssignable&&,CNonTrivialType>::value;

		wcout << L"TYPE TRAIT [is_assignable<CIsAssignable&&,CNonTrivialType>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [CNonIsAssignable] NEMA definovany OPERATOR [OPERATOR=] pre TYPE [CNonTrivialType].
		bool													Value=is_assignable<CNonIsAssignable,CNonTrivialType>::value;

		wcout << L"TYPE TRAIT [is_assignable<CNonIsAssignable,CNonTrivialType>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [CNonIsAssignable] sice NEMA definovany COPY OPERATOR [OPERATOR=], ale ten je vygenerovany C++.
		bool													Value=is_assignable<CNonIsAssignable,const CNonIsAssignable&>::value;

		wcout << L"TYPE TRAIT [is_assignable<CNonIsAssignable,const CNonIsAssignable&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [void] nie je REFERENCABLE.
		bool													Value=is_assignable<void,void*>::value;

		wcout << L"TYPE TRAIT [is_assignable<void,void*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTriviallyAssignable(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vrati FALSE, lebo TYPE [int] je NON-REFERENCE, NON-CLASS TYPE.
		bool													Value=is_trivially_assignable<int,int>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<int,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_assignable<int&,int>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<int&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivially_assignable<int&&,int>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<int&&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_assignable<int&,int&>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<int&,int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivially_assignable<int&&,int&>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<int&&,int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivially_assignable<int&&,int&&>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<int&&,int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [double] je mozne priradit do VARIABLE TYPE [int].
		bool													Value=is_trivially_assignable<int&,double>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<int&,double>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [CIsTriviallyAssignable] NEMA definovany COPY OPERATOR [OPERATOR=], ale C++ vygeneruje DEFAULT (TRIVIAL) COPY OPERATOR [OPERATOR=].
		bool													Value=is_trivially_assignable<CIsTriviallyAssignable,const CIsTriviallyAssignable&>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<CIsTriviallyAssignable,const CIsTriviallyAssignable&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [CIsTriviallyAssignable] NEMA definovany MOVE OPERATOR [OPERATOR=], ale C++ vygeneruje DEFAULT (TRIVIAL) MOVE OPERATOR [OPERATOR=].
		bool													Value=is_trivially_assignable<CIsTriviallyAssignable,CIsTriviallyAssignable&&>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<CIsTriviallyAssignable,CIsTriviallyAssignable&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoTriviallyAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [CNonIsTriviallyAssignable] NEMA definovany COPY OPERATOR [OPERATOR=], a DEFAULT COPY OPERATOR [OPERATOR=] je DELETED.
		bool													Value=is_trivially_assignable<CNonIsTriviallyAssignable,const CNonIsTriviallyAssignable&>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<CNonIsTriviallyAssignable,const CNonIsTriviallyAssignable&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [CNonIsTriviallyAssignable] NEMA definovany MOVE OPERATOR [OPERATOR=], a DEFAULT MOVE OPERATOR [OPERATOR=] je DELETED.
		bool													Value=is_trivially_assignable<CNonIsTriviallyAssignable,CNonIsTriviallyAssignable&&>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<CNonIsTriviallyAssignable,CNonIsTriviallyAssignable&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [void] nie je REFERENCABLE.
		bool													Value=is_trivially_assignable<void,void*>::value;

		wcout << L"TYPE TRAIT [is_trivially_assignable<void,void*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo TYPE [CIsNoThrowAssignable] ma definovany OPERATOR [OPERATOR=] pre TYPE [CNonTrivialType], ktory je zaroven oznaceny KEYWORD [noexcept].
		bool													Value=is_nothrow_assignable<CIsNoThrowAssignable&,CNonTrivialType>::value;

		wcout << L"TYPE TRAIT [is_nothrow_assignable<CIsNoThrowAssignable&,CNonTrivialType>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_assignable<int,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_assignable<int,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_assignable<int&,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_assignable<int&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_assignable<int&&,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_assignable<int&&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [CNonIsNoThrowAssignable] ma definovany OPERATOR [OPERATOR=] pre TYPE [CNonTrivialType], ale NIE JE oznaceny KEYWORD [noexcept].
		bool													Value=is_nothrow_assignable<CNonIsNoThrowAssignable&,CNonTrivialType>::value;

		wcout << L"TYPE TRAIT [is_nothrow_assignable<CNonIsNoThrowAssignable&,CNonTrivialType>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [void] nie je REFERENCABLE.
		bool													Value=is_nothrow_assignable<void,void*>::value;

		wcout << L"TYPE TRAIT [is_nothrow_assignable<void,void*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsCopyAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo je definovany COPY OPERATOR [OPERATOR=].
		bool													Value=is_copy_assignable<CIsCopyAssignable1>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<CIsCopyAssignable1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo je GENEROVANY DEFAULT COPY OPERATOR [OPERATOR=].
		bool													Value=is_copy_assignable<CIsCopyAssignable2>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<CIsCopyAssignable2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_copy_assignable<int>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_copy_assignable<int&>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_copy_assignable<int&&>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_copy_assignable<int*>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoCopyAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo COPY OPERATOR [OPERATOR=] NIE je definovany a DEFUALT COPY OPERATOR [OPERATOR=] je DELETED.
		bool													Value=is_copy_assignable<CNonIsCopyAssignable>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<CNonIsCopyAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo hoci COPY OPERATOR [OPERATOR=] NIE JE DEFINOVANY, C++ vygeneruje DEFUALT COPY OPERATOR [OPERATOR=].
		bool													Value=is_copy_assignable<CIsCopyAssignable2>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<CIsCopyAssignable2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [void] nie je REFERENCABLE.
		bool													Value=is_copy_assignable<void>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [int[10]] je C-ARRAY.
		bool													Value=is_copy_assignable<int[10]>::value;

		wcout << L"TYPE TRAIT [is_copy_assignable<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTriviallyCopyAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo NIE je definovany COPY OPERATOR [OPERATOR=] a C++ vygeneruje DEFAULT (TRIVIAL) COPY OPERATOR [OPERATOR=].
		bool													Value=is_trivially_copy_assignable<CIsTriviallyCopyAssignable>::value;

		wcout << L"TYPE TRAIT [is_trivially_copy_assignable<CIsTriviallyCopyAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_copy_assignable<int>::value;

		wcout << L"TYPE TRAIT [is_trivially_copy_assignable<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoTriviallyCopyAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo je definovany COPY OPERATOR [OPERATOR=] a tym padom sa nejedna o TRIVIAL COPY OPERATOR [OPERATOR=].
		bool													Value=is_trivially_copy_assignable<CNonIsTriviallyCopyAssignable>::value;

		wcout << L"TYPE TRAIT [is_trivially_copy_assignable<CNonIsTriviallyCopyAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [void] nie je REFERENCABLE.
		bool													Value=is_trivially_copy_assignable<void>::value;

		wcout << L"TYPE TRAIT [is_trivially_copy_assignable<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [int[10]] je C-ARRAY.
		bool													Value=is_trivially_copy_assignable<int[10]>::value;

		wcout << L"TYPE TRAIT [is_trivially_copy_assignable<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowCopyAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo COPY OPERATOR [OPERATOR=] je definovany a je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_copy_assignable<CIsNoThrowCopyAssignable>::value;

		wcout << L"TYPE TRAIT [is_nothrow_copy_assignable<CIsNoThrowCopyAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_copy_assignable<int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_copy_assignable<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowCopyAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo COPY OPERATOR [OPERATOR=] je definovany ale NIE je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_copy_assignable<CNonIsNoThrowCopyAssignable>::value;

		wcout << L"TYPE TRAIT [is_nothrow_copy_assignable<CNonIsNoThrowCopyAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [void] nie je REFERENCABLE.
		bool													Value=is_nothrow_copy_assignable<void>::value;

		wcout << L"TYPE TRAIT [is_nothrow_copy_assignable<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [int[10]] je C-ARRAY.
		bool													Value=is_nothrow_copy_assignable<int[10]>::value;

		wcout << L"TYPE TRAIT [is_nothrow_copy_assignable<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsMoveAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo je definovany MOVE OPERATOR [OPERATOR=].
		bool													Value=is_move_assignable<CIsMoveAssignable1>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<CIsMoveAssignable1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo MOVE OPERATOR [OPERATOR=] NIE JE definovany, ale C++ vygeneruje DEFAULT (TRIVIAL) MOVE OPERATOR [OPERATOR=]. .
		bool													Value=is_move_assignable<CIsMoveAssignable2>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<CIsMoveAssignable2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_move_assignable<int>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_move_assignable<int&>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_move_assignable<int&&>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_move_assignable<int*>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_move_assignable<void>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo MOVE OPERATOR [OPERATOR=] NIE JE definovany, ale C++ vygeneruje DEFAULT (TRIVIAL) MOVE OPERATOR [OPERATOR=]. .
		bool													Value=is_move_assignable<CIsMoveAssignable2>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<CIsMoveAssignable2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoMoveAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo MOVE OPERATOR [OPERATOR=] NIE je definovany a DEFUALT MOVE OPERATOR [OPERATOR=] je DELETED.
		bool													Value=is_move_assignable<CNonIsMoveAssignable>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<CNonIsMoveAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo MOVE OPERATOR [OPERATOR=] NIE JE definovany, ale C++ vygeneruje DEFAULT (TRIVIAL) MOVE OPERATOR [OPERATOR=]. .
		bool													Value=is_move_assignable<CIsMoveAssignable2>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<CIsMoveAssignable2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [void] nie je REFERENCABLE.
		bool													Value=is_move_assignable<void>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [int[10]] je C-ARRAY.
		bool													Value=is_move_assignable<int[10]>::value;

		wcout << L"TYPE TRAIT [is_move_assignable<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTriviallyMoveAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo NIE je definovany MOVE OPERATOR [OPERATOR=] a C++ vygeneruje DEFAULT (TRIVIAL) MOVE OPERATOR [OPERATOR=].
		bool													Value=is_trivially_move_assignable<CIsTriviallyMoveAssignable>::value;

		wcout << L"TYPE TRAIT [is_trivially_move_assignable<CIsTriviallyMoveAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_move_assignable<int>::value;

		wcout << L"TYPE TRAIT [is_trivially_move_assignable<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoTriviallyMoveAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo je definovany MOVE OPERATOR [OPERATOR=] a tym padom sa nejedna o TRIVIAL MOVE OPERATOR [OPERATOR=].
		bool													Value=is_trivially_move_assignable<CNonIsTriviallyMoveAssignable>::value;

		wcout << L"TYPE TRAIT [is_trivially_move_assignable<CNonIsTriviallyMoveAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [void] nie je REFERENCABLE.
		bool													Value=is_trivially_move_assignable<void>::value;

		wcout << L"TYPE TRAIT [is_trivially_move_assignable<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [int[10]] je C-ARRAY.
		bool													Value=is_trivially_move_assignable<int[10]>::value;

		wcout << L"TYPE TRAIT [is_trivially_move_assignable<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowMoveAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo MOVE OPERATOR [OPERATOR=] je definovany a je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_move_assignable<CIsNoThrowMoveAssignable>::value;

		wcout << L"TYPE TRAIT [is_nothrow_move_assignable<CIsNoThrowMoveAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_move_assignable<int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_move_assignable<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowMoveAssignable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo MOVE OPERATOR [OPERATOR=] je definovany ale NIE je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_move_assignable<CNonIsNoThrowMoveAssignable>::value;

		wcout << L"TYPE TRAIT [is_nothrow_move_assignable<CNonIsNoThrowMoveAssignable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [void] nie je REFERENCABLE.
		bool													Value=is_nothrow_move_assignable<void>::value;

		wcout << L"TYPE TRAIT [is_nothrow_move_assignable<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE [int[10]] je C-ARRAY.
		bool													Value=is_nothrow_move_assignable<int[10]>::value;

		wcout << L"TYPE TRAIT [is_nothrow_move_assignable<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsDestructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo DESTRUCTOR je definovany.
		bool													Value=is_destructible<CIsDestructible1>::value;

		wcout << L"TYPE TRAIT [is_destructible<CIsDestructible1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo hoci DESTRUCTOR NIE je definovany, C++ definuje DEFAULT (TRIVIAL) DESTRUCTOR.
		bool													Value=is_destructible<CIsDestructible2>::value;

		wcout << L"TYPE TRAIT [is_destructible<CIsDestructible2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_destructible<int>::value;

		wcout << L"TYPE TRAIT [is_destructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_destructible<int&>::value;

		wcout << L"TYPE TRAIT [is_destructible<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_destructible<int&&>::value;

		wcout << L"TYPE TRAIT [is_destructible<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_destructible<int*>::value;

		wcout << L"TYPE TRAIT [is_destructible<int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_destructible<int[10]>::value;

		wcout << L"TYPE TRAIT [is_destructible<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoDestructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo DESTRUCTOR NIE je definovany a DEFUALT DESTRUCTOR je DELETED.
		bool													Value=is_destructible<CNonIsDestructible>::value;

		wcout << L"TYPE TRAIT [is_destructible<CNonIsDestructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_destructible<void>::value;

		wcout << L"TYPE TRAIT [is_destructible<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE je UNBOUNDED C-ARRAY.
		bool													Value=is_destructible<int[]>::value;

		wcout << L"TYPE TRAIT [is_destructible<int[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsTriviallyDestructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo CLASS NEMA ziaden DESTRUCTOR a tak C++ generuje DEFAULT DESTRUCTOR.
		bool													Value=is_trivially_destructible<CIsTriviallyDestructible>::value;

		wcout << L"TYPE TRAIT [is_trivially_destructible<CIsTriviallyDestructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_destructible<int>::value;

		wcout << L"TYPE TRAIT [is_trivially_destructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_destructible<int&>::value;

		wcout << L"TYPE TRAIT [is_trivially_destructible<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_destructible<int&&>::value;

		wcout << L"TYPE TRAIT [is_trivially_destructible<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_destructible<int*>::value;

		wcout << L"TYPE TRAIT [is_trivially_destructible<int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_trivially_destructible<int[10]>::value;

		wcout << L"TYPE TRAIT [is_trivially_destructible<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoTriviallyDestructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo CLASS ma FIELD, ktory NIE JE TRIVIALLY DESTRUCTIBLE.
		bool													Value=is_trivially_destructible<CNonIsTriviallyDestructible>::value;

		wcout << L"TYPE TRAIT [is_trivially_destructible<CNonIsTriviallyDestructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_trivially_destructible<void>::value;

		wcout << L"TYPE TRAIT [is_trivially_destructible<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE je UNBOUNDED C-ARRAY.
		bool													Value=is_trivially_destructible<int[]>::value;

		wcout << L"TYPE TRAIT [is_trivially_destructible<int[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowDestructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, lebo DESTRUCTOR je DEFINED a je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_destructible<CIsNoThrowDestructible>::value;

		wcout << L"TYPE TRAIT [is_nothrow_destructible<CIsNoThrowDestructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_destructible<int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_destructible<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_destructible<int&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_destructible<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_destructible<int&&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_destructible<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_destructible<int*>::value;

		wcout << L"TYPE TRAIT [is_nothrow_destructible<int*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_destructible<int[10]>::value;

		wcout << L"TYPE TRAIT [is_nothrow_destructible<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowDestructible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, hoci DESTRUCTOR je DEFINED, ale NIE je oznaceny pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_destructible<CNonIsNoThrowDestructible>::value;

		wcout << L"TYPE TRAIT [is_nothrow_destructible<CNonIsNoThrowDestructible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_destructible<void>::value;

		wcout << L"TYPE TRAIT [is_nothrow_destructible<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, lebo TYPE je UNBOUNDED C-ARRAY.
		bool													Value=is_nothrow_destructible<int[]>::value;

		wcout << L"TYPE TRAIT [is_nothrow_destructible<int[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsSwappableWith(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<CIsSwappableWith,CIsSwappableWith>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<CIsSwappableWith,CIsSwappableWith>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze TYPE [CIsSwappableWith] DEFINUJE FUNCTION [swap()].
		bool													Value=is_swappable_with<CIsSwappableWith&,CIsSwappableWith&>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<CIsSwappableWith&,CIsSwappableWith&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<CIsSwappableWith&&,CIsSwappableWith&&>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<CIsSwappableWith&&,CIsSwappableWith&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<int,int>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<int,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<int&,int>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<int&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<int&&,int>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<int&&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_swappable_with<int&,int&>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<int&,int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<int&&,int&&>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<int&&,int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<int&,long&>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<int&,long&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoSwappableWith(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<CNonIsSwappableWith,CNonIsSwappableWith>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<CNonIsSwappableWith,CNonIsSwappableWith>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze hoci TYPE [CNonIsSwappableWith] NEDEFINUJE FUNCTION [swap()], tak ju definuje C++ STANDARD LIBRARY.
		bool													Value=is_swappable_with<CNonIsSwappableWith&,CNonIsSwappableWith&>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<CNonIsSwappableWith&,CNonIsSwappableWith&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<CNonIsSwappableWith&&,CNonIsSwappableWith&&>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<CNonIsSwappableWith&&,CNonIsSwappableWith&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable_with<void,void>::value;

		wcout << L"TYPE TRAIT [is_swappable_with<void,void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowSwappableWith(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<CIsNoThrowSwappableWith,CIsNoThrowSwappableWith>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<CIsNoThrowSwappableWith,CIsNoThrowSwappableWith>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze TYPE [CIsNoThrowSwappableWith] DEFINUJE FUNCTION [swap()] a ta JE oznacena pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_swappable_with<CIsNoThrowSwappableWith&,CIsNoThrowSwappableWith&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<CIsNoThrowSwappableWith&,CIsNoThrowSwappableWith&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<CIsNoThrowSwappableWith&&,CIsNoThrowSwappableWith&&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<CIsNoThrowSwappableWith&&,CIsNoThrowSwappableWith&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<int,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<int,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<int&,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<int&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<int&&,int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<int&&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_swappable_with<int&,int&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<int&,int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<int&&,int&&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<int&&,int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<int&,long&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<int&,long&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowSwappableWith(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<CNonIsNoThrowSwappableWith,CNonIsNoThrowSwappableWith>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<CNonIsNoThrowSwappableWith,CNonIsNoThrowSwappableWith>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze TYPE [CNonIsNoThrowSwappableWith] DEFINUJE FUNCTION [swap()], ale ta NIE JE oznacena pomocou KEYWORD [noexcept].
		bool													Value=is_nothrow_swappable_with<CNonIsNoThrowSwappableWith&,CNonIsNoThrowSwappableWith&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<CNonIsNoThrowSwappableWith&,CNonIsNoThrowSwappableWith&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<CNonIsNoThrowSwappableWith&&,CNonIsNoThrowSwappableWith&&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<CNonIsNoThrowSwappableWith&&,CNonIsNoThrowSwappableWith&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable_with<void,void>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable_with<void,void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsSwappable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze TYPE [CIsSwappable] DEFINUJE FUNCTION [swap()].
		bool													Value=is_swappable<CIsSwappable>::value;

		wcout << L"TYPE TRAIT [is_swappable<CIsSwappable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_swappable<CIsSwappable&>::value;

		wcout << L"TYPE TRAIT [is_swappable<CIsSwappable&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_swappable<CIsSwappable&&>::value;

		wcout << L"TYPE TRAIT [is_swappable<CIsSwappable&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_swappable<int>::value;

		wcout << L"TYPE TRAIT [is_swappable<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_swappable<int&>::value;

		wcout << L"TYPE TRAIT [is_swappable<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_swappable<int&&>::value;

		wcout << L"TYPE TRAIT [is_swappable<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_swappable<int[10]>::value;

		wcout << L"TYPE TRAIT [is_swappable<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoSwappable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze hoci TYPE [CNonIsSwappable] NEDEFINUJE FUNCTION [swap()], definuje ju C++ STANDARD LIBRARY.
		bool													Value=is_swappable<CNonIsSwappable>::value;

		wcout << L"TYPE TRAIT [is_swappable<CNonIsSwappable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_swappable<CNonIsSwappable&>::value;

		wcout << L"TYPE TRAIT [is_swappable<CNonIsSwappable&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_swappable<CNonIsSwappable&&>::value;

		wcout << L"TYPE TRAIT [is_swappable<CNonIsSwappable&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable<void>::value;

		wcout << L"TYPE TRAIT [is_swappable<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_swappable<int[]>::value;

		wcout << L"TYPE TRAIT [is_swappable<int[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoThrowSwappable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze TYPE [CIsNoThrowSwappable] DEFINUJE FUNCTION [swap()] a ta je oznacena KEYWORD [noexcept].
		bool													Value=is_nothrow_swappable<CIsNoThrowSwappable>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<CIsNoThrowSwappable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_swappable<CIsNoThrowSwappable&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<CIsNoThrowSwappable&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_swappable<CIsNoThrowSwappable&&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<CIsNoThrowSwappable&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_swappable<int>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_swappable<int&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_swappable<int&&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_nothrow_swappable<int[10]>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoNoThrowSwappable(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze hoci TYPE [CNonIsNoThrowSwappable] DEFINUJE FUNCTION [swap()] NIE JE oznacena KEYWORD [noexcept].
		bool													Value=is_nothrow_swappable<CNonIsNoThrowSwappable>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<CNonIsNoThrowSwappable>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze hoci TYPE [CNonIsNoThrowSwappable] DEFINUJE FUNCTION [swap()] NIE JE oznacena KEYWORD [noexcept].
		bool													Value=is_nothrow_swappable<CNonIsNoThrowSwappable&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<CNonIsNoThrowSwappable&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze hoci TYPE [CNonIsNoThrowSwappable] DEFINUJE FUNCTION [swap()] NIE JE oznacena KEYWORD [noexcept].
		bool													Value=is_nothrow_swappable<CNonIsNoThrowSwappable&&>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<CNonIsNoThrowSwappable&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable<void>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<void>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_nothrow_swappable<int[]>::value;

		wcout << L"TYPE TRAIT [is_nothrow_swappable<int[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsSame(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_same<int,int>::value;

		wcout << L"TYPE TRAIT [is_same<int,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_same<int&,int>::value;

		wcout << L"TYPE TRAIT [is_same<int&,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_same<int&,int&>::value;

		wcout << L"TYPE TRAIT [is_same<int&,int&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_same<int&&,int&&>::value;

		wcout << L"TYPE TRAIT [is_same<int&&,int&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_same<int[10],int[10]>::value;

		wcout << L"TYPE TRAIT [is_same<int[10],int[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_same<int[10],int[5]>::value;

		wcout << L"TYPE TRAIT [is_same<int[10],int[5]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_same<int[],int[]>::value;

		wcout << L"TYPE TRAIT [is_same<int[],int[]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_same<const int,const int>::value;

		wcout << L"TYPE TRAIT [is_same<const int,const int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_same<const int,int>::value;

		wcout << L"TYPE TRAIT [is_same<const int,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													INT=int;

		// !!! Vrati TRUE.
		bool													Value=is_same<int,INT>::value;

		wcout << L"TYPE TRAIT [is_same<int,INT>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		auto													Closure1=[](int){};
		auto													Closure2=[](int){};

		// !!! Vrati FALSE.
		bool													Value=is_same<decltype(Closure1),decltype(Closure2)>::value;

		wcout << L"TYPE TRAIT [is_same<decltype(Closure1),decltype(Closure2)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		auto													Closure1=[](int){};
		auto													Closure2=Closure1;

		// !!! Vrati TRUE.
		bool													Value=is_same<decltype(Closure1),decltype(Closure2)>::value;

		wcout << L"TYPE TRAIT [is_same<decltype(Closure1),decltype(Closure2)>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Je TYPE [nullptr_t].
		auto													Type1=nullptr;
		auto													Type2=nullptr;

		// !!! Vrati TRUE.
		bool													Value=is_same<decltype(Type1),decltype(Type2)>::value;

		wcout << L"TYPE TRAIT [is_same<decltype(Type1),decltype(Type2)>::value] - VALUE [" << Value << L"] TYPE 1 [" << GetTypeInfoName(typeid(Type1)) << L"] TYPE 2 [" << GetTypeInfoName(typeid(Type2)) << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsBaseOf(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_base_of<CIsBaseOfBase,CIsBaseOfBase>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfBase,CIsBaseOfBase>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_base_of<CIsBaseOfBase,CIsBaseOfDerived1>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfBase,CIsBaseOfDerived1>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_base_of<CIsBaseOfBase,CIsBaseOfDerived2>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfBase,CIsBaseOfDerived2>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_base_of<CIsBaseOfBase,CIsBaseOfSuperDerived>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfBase,CIsBaseOfSuperDerived>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_base_of<CIsBaseOfDerived1,CIsBaseOfSuperDerived>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfDerived1,CIsBaseOfSuperDerived>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_base_of<CIsBaseOfDerived2,CIsBaseOfSuperDerived>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfDerived2,CIsBaseOfSuperDerived>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_base_of<CIsBaseOfDerived2,const CIsBaseOfSuperDerived>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfDerived2,const CIsBaseOfSuperDerived>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE.
		bool													Value=is_base_of<const CIsBaseOfDerived2,CIsBaseOfSuperDerived>::value;

		wcout << L"TYPE TRAIT [is_base_of<const CIsBaseOfDerived2,CIsBaseOfSuperDerived>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_base_of<CIsBaseOfDerived2&,CIsBaseOfSuperDerived&>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfDerived2&,CIsBaseOfSuperDerived&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_base_of<CIsBaseOfDerived2&&,CIsBaseOfSuperDerived&&>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfDerived2&&,CIsBaseOfSuperDerived&&>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_base_of<CIsBaseOfDerived2*,CIsBaseOfSuperDerived*>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfDerived2*,CIsBaseOfSuperDerived*>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_base_of<CIsBaseOfDerived2[10],CIsBaseOfSuperDerived[10]>::value;

		wcout << L"TYPE TRAIT [is_base_of<CIsBaseOfDerived2[10],CIsBaseOfSuperDerived[10]>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE.
		bool													Value=is_base_of<int,int>::value;

		wcout << L"TYPE TRAIT [is_base_of<int,int>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsConvertible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze je definovany CONSTRUCTOR, ktory ma ako PARAMETER TYPE [int].
		bool													Value=is_convertible<int,CIsConvertible>::value;

		wcout << L"TYPE TRAIT [is_convertible<int,CIsConvertible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze je definovany CONSTRUCTOR, ktory ma ako PARAMETER TYPE [int].
		bool													Value=is_convertible<int,const CIsConvertible>::value;

		wcout << L"TYPE TRAIT [is_convertible<int,const CIsConvertible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati TRUE, pretoze je definovany CONSTRUCTOR, ktory ma ako PARAMETER TYPE [int].
		bool													Value=is_convertible<const int,CIsConvertible>::value;

		wcout << L"TYPE TRAIT [is_convertible<const int,CIsConvertible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeTraitIsNoConvertible(void)
{
	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze NIE je definovany CONSTRUCTOR, ktory ma ako PARAMETER TYPE [int].
		bool													Value=is_convertible<int,CNonIsConvertible>::value;

		wcout << L"TYPE TRAIT [is_convertible<int,CNonIsConvertible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze NIE je definovany CONSTRUCTOR, ktory ma ako PARAMETER TYPE [int].
		bool													Value=is_convertible<int,const CNonIsConvertible>::value;

		wcout << L"TYPE TRAIT [is_convertible<int,const CNonIsConvertible>::value] - VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Vrati FALSE, pretoze NIE je definovany CONSTRUCTOR, ktory ma ako PARAMETER TYPE [int].
		bool													Value=is_convertible<const int,CNonIsConvertible>::value;

		wcout << L"TYPE TRAIT [is_convertible<const int,CNonIsConvertible>::value] - VALUE [" << Value << L"]." << endl;
	}

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
	//TestTypeTraitInvokeResult();
	//TestTypeTraitIsConstructible();
	//TestTypeTraitIsNoConstructible();
	//TestTypeTraitIsTriviallyConstructible();
	//TestTypeTraitIsNoTriviallyConstructible();
	//TestTypeTraitIsNoThrowConstructible();
	//TestTypeTraitIsNoNoThrowConstructible();
	//TestTypeTraitIsDefaultConstructible();
	//TestTypeTraitIsNoDefaultConstructible();
	//TestTypeTraitIsTriviallyDefaultConstructible();
	//TestTypeTraitIsNoTriviallyDefaultConstructible();
	//TestTypeTraitIsNoThrowDefaultConstructible();
	//TestTypeTraitIsNoNoThrowDefaultConstructible();
	//TestTypeTraitIsCopyConstructible();
	//TestTypeTraitIsNoCopyConstructible();
	//TestTypeTraitIsTriviallyCopyConstructible();
	//TestTypeTraitIsNoTriviallyCopyConstructible();
	//TestTypeTraitIsNoThrowCopyConstructible();
	//TestTypeTraitIsNoNoThrowCopyConstructible();
	//TestTypeTraitIsMoveConstructible();
	//TestTypeTraitIsNoMoveConstructible();
	//TestTypeTraitIsTriviallyMoveConstructible();
	//TestTypeTraitIsNoTriviallyMoveConstructible();
	//TestTypeTraitIsNoThrowMoveConstructible();
	//TestTypeTraitIsNoNoThrowMoveConstructible();
	//TestTypeTraitIsAssignable();
	//TestTypeTraitIsNoAssignable();
	//TestTypeTraitIsTriviallyAssignable();
	//TestTypeTraitIsNoTriviallyAssignable();
	//TestTypeTraitIsNoThrowAssignable();
	//TestTypeTraitIsNoNoThrowAssignable();
	//TestTypeTraitIsCopyAssignable();
	//TestTypeTraitIsNoCopyAssignable();
	//TestTypeTraitIsTriviallyCopyAssignable();
	//TestTypeTraitIsNoTriviallyCopyAssignable();
	//TestTypeTraitIsNoThrowCopyAssignable();
	//TestTypeTraitIsNoNoThrowCopyAssignable();
	//TestTypeTraitIsMoveAssignable();
	//TestTypeTraitIsNoMoveAssignable();
	//TestTypeTraitIsTriviallyMoveAssignable();
	//TestTypeTraitIsNoTriviallyMoveAssignable();
	//TestTypeTraitIsNoThrowMoveAssignable();
	//TestTypeTraitIsNoNoThrowMoveAssignable();
	//TestTypeTraitIsDestructible();
	//TestTypeTraitIsNoDestructible();
	//TestTypeTraitIsTriviallyDestructible();
	//TestTypeTraitIsNoTriviallyDestructible();
	//TestTypeTraitIsNoThrowDestructible();
	//TestTypeTraitIsNoNoThrowDestructible();
	//TestTypeTraitIsSwappableWith();
	//TestTypeTraitIsNoSwappableWith();
	//TestTypeTraitIsNoThrowSwappableWith();
	//TestTypeTraitIsNoNoThrowSwappableWith();
	//TestTypeTraitIsSwappable();
	//TestTypeTraitIsNoSwappable();
	//TestTypeTraitIsNoThrowSwappable();
	//TestTypeTraitIsNoNoThrowSwappable();
	//TestTypeTraitIsSame();
	//TestTypeTraitIsBaseOf();
	//TestTypeTraitIsConvertible();
	TestTypeTraitIsNoConvertible();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------