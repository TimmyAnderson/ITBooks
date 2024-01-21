//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "CAlgorithmSpecializationValue.h"
#include "CTagDisptachingAlgorithmValue1.h"
#include "CTagDisptachingAlgorithmValue2.h"
#include "CTagDisptachingAlgorithmTypeGeneric.h"
#include "CTagDisptachingAlgorithmTypeSpecialized.h"
#include "STypeTraitEnableIfType.h"
#include "SClassTemplateEnableDisable.h"
#include "CClassTagDisptaching1.h"
#include "CClassTagDisptaching2.h"
#include "CClassTagDisptaching3.h"
#include "CClassTagDisptachingValue1.h"
#include "CClassTagDisptachingValue2.h"
#include "CClassTagDisptachingValue3.h"
#include "SClassTemplateTagDispatching1.h"
#include "SClassTemplateTagDispatching2.h"
#include "SSFINAETraitIsConvertible.h"
#include "SSFINAETraitHasLess.h"
#include "CInstantiationSafeTemplatesTypes1.h"
#include "CInstantiationSafeTemplatesTypes2.h"
#include "CInstantiationSafeTemplatesTypes3.h"
#include "CInstantiationSafeTemplatesTypes4.h"
#include "CInstantiationSafeTemplatesTypes5.h"
#include "CInstantiationSafeTemplatesTypes6.h"
#include "CInstantiationSafeTemplatesTypes7.h"
#include "SSFINAETraitIsContextualBool.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Genericka verzia ALGORITHM.
template<typename TType>
void AlgorithmSpecializationFunction(const TType& Value)
{
	wcout << L"GENERIC ALGORITHM FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Specializovana verzia ALGORITHM pre MORE SPECIALIZED TYPES.
template<typename TType>
void AlgorithmSpecializationFunction(const CAlgorithmSpecializationValue<TType>& Value)
{
	wcout << L"SPECIALIZED ALGORITHM FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestAlgorithmSpecialization(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		AlgorithmSpecializationFunction(Value);
	}

	PrintLineSeparator();

	{
		CAlgorithmSpecializationValue<int>												Value=100;

		AlgorithmSpecializationFunction(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION pre TAG DISPATCHING TYPE [CTagDisptachingAlgorithmTypeGeneric].
template<typename TType>
void TagDisptachingFunction(TType Value, CTagDisptachingAlgorithmTypeGeneric)
{
	wcout << L"TAG DISPATCHING FUNCTION 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue1() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION pre TAG DISPATCHING TYPE [CTagDisptachingAlgorithmTypeSpecialized].
template<typename TType>
void TagDisptachingFunction(TType Value, CTagDisptachingAlgorithmTypeSpecialized)
{
	wcout << L"TAG DISPATCHING FUNCTION 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value.GetValue2() << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTagDisptaching(void)
{
	PrintLineSeparator();

	{
		CTagDisptachingAlgorithmValue1							Value(100);
		CTagDisptachingAlgorithmTypeGeneric						TagDisptaching;

		TagDisptachingFunction(Value,TagDisptaching);
	}

	PrintLineSeparator();

	{
		CTagDisptachingAlgorithmValue2							Value(123.456);
		CTagDisptachingAlgorithmTypeSpecialized					TagDisptaching;

		TagDisptachingFunction(Value,TagDisptaching);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! 1. OVERLOADED TEMPLATE FUNCTION.
// !!!!! Ak CONDITION ZLYHA, OVERLOADED FUNCTION je VYRADENA z CANDIDATE SET.
template<typename TType>
STypeTraitEnableIfAlias<is_integral<TType>::value==true,TType> TestEnablingFunctionTemplatesFunction(TType Value)
{
	wcout << L"ENABLING FUNCTION TEMPLATES 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! 2. OVERLOADED TEMPLATE FUNCTION.
// !!!!! Ak CONDITION ZLYHA, OVERLOADED FUNCTION je VYRADENA z CANDIDATE SET.
template<typename TType>
STypeTraitEnableIfAlias<is_integral<TType>::value==false,void> TestEnablingFunctionTemplatesFunction(TType Value)
{
	wcout << L"ENABLING FUNCTION TEMPLATES 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestEnablingFunctionTemplates(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! Vola sa 1. OVERLOADED VERSION TEMPLATE FUNCTION.
		int														ReturnValue=TestEnablingFunctionTemplatesFunction(Value);

		wcout << L"RETURN VALUE - TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CString													Value=L"Timmy";

		// !!!!! Vola sa 2. OVERLOADED VERSION TEMPLATE FUNCTION.
		TestEnablingFunctionTemplatesFunction(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! 1. OVERLOADED TEMPLATE FUNCTION.
// !!!!! Ak CONDITION ZLYHA, OVERLOADED FUNCTION je VYRADENA z CANDIDATE SET.
template<typename TType>
STypeTraitEnableIfAlias<is_integral<TType>::value==true,TType> TestEnablingFunctionTemplatesMultipleSpecializationsFunction(TType Value)
{
	wcout << L"ENABLING FUNCTION TEMPLATES MULTIPLE SPECIALIZATIONS 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! 2. OVERLOADED TEMPLATE FUNCTION.
// !!!!! Ak CONDITION ZLYHA, OVERLOADED FUNCTION je VYRADENA z CANDIDATE SET.
template<typename TType>
STypeTraitEnableIfAlias<is_floating_point<TType>::value==true,TType> TestEnablingFunctionTemplatesMultipleSpecializationsFunction(TType Value)
{
	wcout << L"ENABLING FUNCTION TEMPLATES MULTIPLE SPECIALIZATIONS 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! 3. OVERLOADED TEMPLATE FUNCTION.
// !!!!! Ak CONDITION ZLYHA, OVERLOADED FUNCTION je VYRADENA z CANDIDATE SET.
template<typename TType>
STypeTraitEnableIfAlias<is_integral<TType>::value==false && is_floating_point<TType>::value==false,TType> TestEnablingFunctionTemplatesMultipleSpecializationsFunction(TType Value)
{
	wcout << L"ENABLING FUNCTION TEMPLATES MULTIPLE SPECIALIZATIONS 3 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestEnablingFunctionTemplatesMultipleSpecializations(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! Vola sa 1. OVERLOADED VERSION TEMPLATE FUNCTION.
		int														ReturnValue=TestEnablingFunctionTemplatesMultipleSpecializationsFunction(Value);

		wcout << L"RETURN VALUE - TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		double													Value=123.456;

		// !!!!! Vola sa 2. OVERLOADED VERSION TEMPLATE FUNCTION.
		double													ReturnValue=TestEnablingFunctionTemplatesMultipleSpecializationsFunction(Value);

		wcout << L"RETURN VALUE - TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CString													Value=L"Timmy";

		// !!!!! Vola sa 3. OVERLOADED VERSION TEMPLATE FUNCTION.
		TestEnablingFunctionTemplatesMultipleSpecializationsFunction(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! 1. OVERLOADED TEMPLATE FUNCTION.
// !!!!! V pripade, ze CONDITION [is_integral<TType>::value==true] vrati VALUE [false], TYPE TRAIT ALIAS [STypeTraitEnableIfAlias<>] sposobi ERROR, pretoze sa odkazuje na TYPE [TYPE], ktory vsak TYPE TRAIT [STypeTraitEnableIfType<false,TYPE>] NEMA IMPLEMENTOVANY. V takom pripade COMPILER na zaklade SFINAE VYRADI danu OVERLOADED TEMPLATE FUNCTION z CANDIDATE SET.
template<typename TType, typename=STypeTraitEnableIfAlias<is_integral<TType>::value==true,TType>>
void TestEnablingFunctionTemplatesInTemplateParameterListFunction(TType Value)
{
	wcout << L"ENABLING FUNCTION TEMPLATES IN TEMPLATE PARAMETER LIST 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! 2. OVERLOADED TEMPLATE FUNCTION.
// !!!!! V pripade, ze CONDITION [is_integral<TType>::value==false] vrati VALUE [false], TYPE TRAIT ALIAS [STypeTraitEnableIfAlias<>] sposobi ERROR, pretoze sa odkazuje na TYPE [TYPE], ktory vsak TYPE TRAIT [STypeTraitEnableIfType<false,TYPE>] NEMA IMPLEMENTOVANY. V takom pripade COMPILER na zaklade SFINAE VYRADI danu OVERLOADED TEMPLATE FUNCTION z CANDIDATE SET.
// !!!!! Kedze obe OVERLOADED TEMPLATE FUNCTIONS maju ROVNAKE PARAMETER TYPES, ROVNAKE RETURN VALUE TYPES a VSETKY TEMPLATE PARAMETERS v TEMPLATE PARAMETER LISTS su TYPE TYPE PARAMETERS, MUSIA sa LISIT v POCTE TEMPLATE PARAMETERS v TEMPLATE PARAMETER LISTS.
template<typename TType, typename=STypeTraitEnableIfAlias<is_integral<TType>::value==false,TType>, typename=void>
void TestEnablingFunctionTemplatesInTemplateParameterListFunction(TType Value)
{
	wcout << L"ENABLING FUNCTION TEMPLATES IN TEMPLATE PARAMETER LIST 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestEnablingFunctionTemplatesInTemplateParameterList(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		// !!!!! Vola sa 1. OVERLOADED VERSION TEMPLATE FUNCTION.
		TestEnablingFunctionTemplatesInTemplateParameterListFunction(Value);
	}

	PrintLineSeparator();

	{
		CString													Value=L"Timmy";

		// !!!!! Vola sa 2. OVERLOADED VERSION TEMPLATE FUNCTION.
		TestEnablingFunctionTemplatesInTemplateParameterListFunction(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CompileTimeIfFunction(TType Value)
{
	if constexpr (is_integral<TType>::value==true)
	{
		wcout << L"COMPILE TIME IF 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
	}
	else
	{
		if constexpr (is_floating_point<TType>::value==true)
		{
			wcout << L"COMPILE TIME IF 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
		}
		else
		{
			wcout << L"COMPILE TIME IF 3 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestCompileTimeIf(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		CompileTimeIfFunction(Value);
	}

	PrintLineSeparator();

	{
		double													Value=123.456;

		CompileTimeIfFunction(Value);
	}

	PrintLineSeparator();

	{
		CString													Value=L"Timmy";

		CompileTimeIfFunction(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
requires (is_integral<TType>::value==true)
void ConceptsFunction(TType Value)
{
	wcout << L"CONCEPTS 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
requires (is_floating_point<TType>::value==true)
void ConceptsFunction(TType Value)
{
	wcout << L"CONCEPTS 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
requires (is_integral<TType>::value==false && is_floating_point<TType>::value==false)
void ConceptsFunction(TType Value)
{
	wcout << L"CONCEPTS 3 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestConcepts(void)
{
	PrintLineSeparator();

	{
		int														Value=100;

		ConceptsFunction(Value);
	}

	PrintLineSeparator();

	{
		double													Value=123.456;

		ConceptsFunction(Value);
	}

	PrintLineSeparator();

	{
		CString													Value=L"Timmy";

		ConceptsFunction(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestClassEnableDisable(void)
{
	PrintLineSeparator();

	{
		CString													Value=L"Timmy";
		SClassTemplateEnableDisable<CString>					Object(Value);

		Object.Print();
	}

	PrintLineSeparator();

	{
		int														Value=100;
		SClassTemplateEnableDisable<int>						Object(Value);

		Object.Print();
	}

	PrintLineSeparator();

	{
		double													Value=123.456;
		SClassTemplateEnableDisable<double>						Object(Value);

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestClassTagDisptaching(void)
{
	PrintLineSeparator();

	{
		using													Type=CClassTagDisptachingValue1;

		Type													Value(100);

		// !!!!! TAG DISPATCHING CLASS je nutne explicitne definovat.
		SClassTemplateTagDispatching1<Type,Type::TAG>			Object;

		Object.Print(Value);
	}

	PrintLineSeparator();

	{
		using													Type=CClassTagDisptachingValue2;

		Type													Value(123.456);

		// !!!!! TAG DISPATCHING CLASS je nutne explicitne definovat.
		SClassTemplateTagDispatching1<Type,Type::TAG>			Object;

		Object.Print(Value);
	}

	PrintLineSeparator();

	{
		using													Type=CClassTagDisptachingValue3;

		Type													Value(L"Timmy");

		// !!!!! TAG DISPATCHING CLASS je nutne explicitne definovat.
		SClassTemplateTagDispatching1<Type,Type::TAG>			Object;

		Object.Print(Value);
	}

	PrintLineSeparator();

	{
		using													Type=CClassTagDisptachingValue1;

		Type													Value(100);

		// !!!!! TAG DISPATCHING CLASS NIE je nutne explicitne definovat, pretoze sa vypocita ako DEFAULT ARGUMENT TEMPLATE PARAMETER.
		SClassTemplateTagDispatching2<Type>						Object;

		Object.Print(Value);
	}

	PrintLineSeparator();

	{
		using													Type=CClassTagDisptachingValue2;

		Type													Value(123.456);

		// !!!!! TAG DISPATCHING CLASS NIE je nutne explicitne definovat, pretoze sa vypocita ako DEFAULT ARGUMENT TEMPLATE PARAMETER.
		SClassTemplateTagDispatching2<Type>						Object;

		Object.Print(Value);
	}

	PrintLineSeparator();

	{
		using													Type=CClassTagDisptachingValue3;

		Type													Value(L"Timmy");

		// !!!!! TAG DISPATCHING CLASS NIE je nutne explicitne definovat, pretoze sa vypocita ako DEFAULT ARGUMENT TEMPLATE PARAMETER.
		SClassTemplateTagDispatching2<Type>						Object;

		Object.Print(Value);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
STypeTraitEnableIfAlias<SFINAETraitIsConvertibleValue<SSFINAETraitHasLessAlias<const TType&,const TType&>,bool>,const TType&> InstantiationSafeTemplatesFunction1(const TType& Value1, const TType& Value2)
{
	if (Value2<Value1)
	{
		return(Value2);
	}
	else
	{
		return(Value1);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
STypeTraitEnableIfAlias<SSFINAETraitIsContextualBoolAlias<SSFINAETraitHasLessAlias<const TType&,const TType&>>,const TType&> InstantiationSafeTemplatesFunction2(const TType& Value1, const TType& Value2)
{
	if (Value2<Value1)
	{
		return(Value2);
	}
	else
	{
		return(Value1);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestInstantiationSafeTemplates(void)
{
	PrintLineSeparator();

	{
		CInstantiationSafeTemplatesTypes1						Value1(100);
		CInstantiationSafeTemplatesTypes1						Value2(200);

		// !!!!! COMPILER akceptuje CODE, pretoze TYPE [CInstantiationSafeTemplatesTypes1] MA definovany CONVERSION OPERATOR [OPERATOR bool()], ktory akceptuje PARAMETER TYPE [const CInstantiationSafeTemplatesTypes1&].
		CInstantiationSafeTemplatesTypes1						Result=InstantiationSafeTemplatesFunction1(Value1,Value2);

		wcout << L"1 - INSTANTIATION SAFE TEMPLATES 1A - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CInstantiationSafeTemplatesTypes1						Value1(200);
		CInstantiationSafeTemplatesTypes1						Value2(100);

		// !!!!! COMPILER akceptuje CODE, pretoze TYPE [CInstantiationSafeTemplatesTypes1] MA definovany CONVERSION OPERATOR [OPERATOR bool()], ktory akceptuje PARAMETER TYPE [const CInstantiationSafeTemplatesTypes1&].
		CInstantiationSafeTemplatesTypes1						Result=InstantiationSafeTemplatesFunction1(Value1,Value2);

		wcout << L"1 - INSTANTIATION SAFE TEMPLATES 1B - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CInstantiationSafeTemplatesTypes2						Value1(100);
		CInstantiationSafeTemplatesTypes2						Value2(200);

		// !!!!! COMPILER akceptuje CODE, pretoze TYPE [CInstantiationSafeTemplatesTypes2] MA definovany CONVERSION OPERATOR [OPERATOR bool()], ktory akceptuje PARAMETER TYPE [CInstantiationSafeTemplatesTypes2].
		CInstantiationSafeTemplatesTypes2						Result=InstantiationSafeTemplatesFunction1(Value1,Value2);

		wcout << L"1 - INSTANTIATION SAFE TEMPLATES 2 - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CInstantiationSafeTemplatesTypes3						Value1(100);
		CInstantiationSafeTemplatesTypes3						Value2(200);

		// !!!!! COMPILER hodi ERROR, pretoze TYPE [CInstantiationSafeTemplatesTypes3] MA definovany CONVERSION OPERATOR [OPERATOR bool()], ale ten vyzaduje ako PARAMETER TYPE [CInstantiationSafeTemplatesTypes3&] a NIE TYPE [const CInstantiationSafeTemplatesTypes3&].
		CInstantiationSafeTemplatesTypes3						Result=InstantiationSafeTemplatesFunction1(Value1,Value2);

		wcout << L"1 - INSTANTIATION SAFE TEMPLATES 3 - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	{
		CInstantiationSafeTemplatesTypes4						Value1(100);
		CInstantiationSafeTemplatesTypes4						Value2(200);

		// !!!!! COMPILER hodi ERROR, pretoze TYPE [CInstantiationSafeTemplatesTypes4] NEMA definovany CONVERSION OPERATOR [OPERATOR bool()].
		CInstantiationSafeTemplatesTypes4						Result=InstantiationSafeTemplatesFunction1(Value1,Value2);

		wcout << L"1 - INSTANTIATION SAFE TEMPLATES 4 - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		CInstantiationSafeTemplatesTypes5						Value1(100);
		CInstantiationSafeTemplatesTypes5						Value2(200);

		// !!!!! COMPILER akceptuje CODE, pretoze TYPE [CInstantiationSafeTemplatesTypes5] vracia vo svojom CONVERSION OPERATOR [OPERATOR bool()] RETURN VALUE TYPE [CInstantiationSafeTemplatesTypesBoolConvertibleImplicit], ktory MA CONVERATION OPERATOR na TYPE [bool].
		CInstantiationSafeTemplatesTypes5						Result=InstantiationSafeTemplatesFunction1(Value1,Value2);

		wcout << L"1 - INSTANTIATION SAFE TEMPLATES 5 - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CInstantiationSafeTemplatesTypes6						Value1(100);
		CInstantiationSafeTemplatesTypes6						Value2(200);

		// !!!!! COMPILER hodi ERROR, pretoze TYPE [CInstantiationSafeTemplatesTypes6] vracia vo svojom CONVERSION OPERATOR [OPERATOR bool()] RETURN VALUE TYPE [CInstantiationSafeTemplatesTypesNotBoolConvertible], ktory NEMA CONVERATION OPERATOR na TYPE [bool].
		CInstantiationSafeTemplatesTypes6						Result=InstantiationSafeTemplatesFunction1(Value1,Value2);

		wcout << L"1 - INSTANTIATION SAFE TEMPLATES 6 - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	{
		CInstantiationSafeTemplatesTypes7						Value1(100);
		CInstantiationSafeTemplatesTypes7						Value2(200);

		// !!!!! COMPILER hodi ERROR, pretoze TYPE [CInstantiationSafeTemplatesTypes7] vracia vo svojom CONVERSION OPERATOR [OPERATOR bool()] RETURN VALUE TYPE [CInstantiationSafeTemplatesTypesBoolConvertibleExplicit], ktory ma IBA EXPLICIT CONVERATION OPERATOR na TYPE [bool].
		CInstantiationSafeTemplatesTypes7						Result=InstantiationSafeTemplatesFunction1(Value1,Value2);

		wcout << L"1 - INSTANTIATION SAFE TEMPLATES 7 - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		CInstantiationSafeTemplatesTypes7						Value1(100);
		CInstantiationSafeTemplatesTypes7						Value2(200);

		// !!!!! COMPILER akcpetuje CODE, pretoze pouzitim TYPE TRAIT [SSFINAETraitIsContextualBoolAlias] akceptuje aj to, ze TYPE [CInstantiationSafeTemplatesTypes7] vracia vo svojom CONVERSION OPERATOR [OPERATOR bool()] RETURN VALUE TYPE [CInstantiationSafeTemplatesTypesBoolConvertibleExplicit], ktory ma EXPLICIT CONVERATION OPERATOR na TYPE [bool].
		CInstantiationSafeTemplatesTypes7						Result=InstantiationSafeTemplatesFunction2(Value1,Value2);

		wcout << L"2 - INSTANTIATION SAFE TEMPLATES 7 - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestAlgorithmSpecialization();
	//TestTagDisptaching();
	//TestEnablingFunctionTemplates();
	//TestEnablingFunctionTemplatesMultipleSpecializations();
	//TestEnablingFunctionTemplatesInTemplateParameterList();
	//TestCompileTimeIf();
	//TestConcepts();
	//TestClassEnableDisable();
	//TestClassTagDisptaching();
	TestInstantiationSafeTemplates();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------