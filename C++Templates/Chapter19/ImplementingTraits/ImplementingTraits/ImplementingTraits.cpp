//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <vector>
#include <list>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "CBigInt.h"
#include "SFixedTraitSumTraits.h"
#include "SValueTraitSum1.h"
#include "SValueTraitSum2.h"
#include "SParametrizedTraitSum.h"
#include "SPolicyTraitSum.h"
#include "SPolicySum.h"
#include "SPolicyMultiple.h"
#include "SPolicySumAsTemplateClass.h"
#include "STypeFunctionSizeof.h"
#include "STypeFunctionElementType.h"
#include "CElementTypeClass1.h"
#include "CElementTypeClass2.h"
#include "CElementTypeClass3.h"
#include "STypeFunctionAddLValueReference.h"
#include "STypeFunctionAddRValueReference.h"
#include "STypeFunctionRemoveReference.h"
#include "STypeFunctionRemoveConst.h"
#include "STypeFunctionRemoveVolatile.h"
#include "STypeFunctionRemoveConstVolatile.h"
#include "STypeFunctionDecay.h"
#include "STypeFunctionIsSame.h"
#include "STypeFunctionBoolConstant.h"
#include "STypeFunctionIsSameTagDispatching.h"
#include "STypeFunctionResultOperatorPlus.h"
#include "CHasDefaultConstructor.h"
#include "CNoDefaultConstructor.h"
#include "STypeFunctionResultOperatorPlusDeclval.h"
#include "SSFINAETraitIsDefaultConstructible.h"
#include "SSFINAETraitIsDefaultConstructiblePredicate.h"
#include "SSFINAETraitIsDefaultConstructibleSpecialization.h"
#include "SSFINAETraitFactoryGenericLambda.h"
#include "SSFINAETraitIsDefaultConstructibleLambda.h"
#include "CType1.h"
#include "CType2.h"
#include "CType3.h"
#include "CType4.h"
#include "CTypeNoMembers.h"
#include "CTypeWithMYTYPEMember1.h"
#include "CTypeWithMYTYPEMember2.h"
#include "CTypeWithMYTYPEMembers.h"
#include "CTypeWithMethods.h"
#include "CWrapperType.h"
#include "SHasFieldMyValue.h"
#include "STypeFunctionResultHasOperatorMinusDeclval.h"
#include "STypeFunctionResultOperatorMinusHasMinus.h"
#include "SSFINAETraitIsConvertible.h"
#include "SSFINAETraitIsConvertibleWithChecks.h"
#include "SDetectingMembersHasMemberType.h"
#include "MacroHasMemberType.h"
#include "MacroHasMemberNonType.h"
#include "STypeClassificationHasFunctionGetValue.h"
#include "STypeClassificationHasOperatorLess.h"
#include "STypeClassificationHasVariousMembers.h"
#include "SDetectingMembersTraitUsingGenericLambdas.h"
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
template<typename TType>
TType FixedTraitsSumNoTraits(const TType* Begin, const TType* End)
{
	// !!!!! Pouziva TYPE [TType] na scitanie VALUES.
	TType														Total{};

	while (Begin!=End)
	{
		Total+=*Begin;

		++Begin;
	}

	return(Total);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
auto FixedTraitsSumWithTraits(const TType* Begin, const TType* End)
{
	// !!!!! Pouziva TYPE [SFixedTraitSumTraits<TType>::TSum] na scitanie VALUES.
	typename SFixedTraitSumTraits<TType>::TSum					Total{};

	while (Begin!=End)
	{
		Total+=*Begin;

		++Begin;
	}

	return(Total);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFixedTraits(void)
{
	PrintLineSeparator();

	{
		int														Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		// !!! Vrati korektnu VALUE, ak ARRAY [Array] nie je extremne dlhe, aby presiahlo maximalnu VALUE TYPE [int].
		int														ReturnValue=FixedTraitsSumNoTraits(Array,(Array+Length));

		wcout << L"SUM - NO TRAITS <int> - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		char													Array[]={"Timmy Anderson"};
		size_t													Length=((sizeof(Array)/sizeof(Array[0]))-1);

		// !!!!! Vrati NESPRAVNU VALUE, lebo TYPE [char] ma prilis malu MAXIMALNU VALUE.
		int														ReturnValue=FixedTraitsSumNoTraits(Array,(Array+Length));

		wcout << L"SUM - NO TRAITS <char> - RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		// !!! Vrati korektnu VALUE. RETURN VALUE TYPE je urceny TEMPLATE CLASS SPECIALIZATION [SFixedTraitSumTraits<int>].
		auto													ReturnValue=FixedTraitsSumWithTraits(Array,(Array+Length));

		wcout << L"SUM - WITH TRAITS <int> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		short													Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		// !!! Vrati korektnu VALUE. RETURN VALUE TYPE je urceny PRIMARY TEMPLATE CLASS [SFixedTraitSumTraits].
		auto													ReturnValue=FixedTraitsSumWithTraits(Array,(Array+Length));

		wcout << L"SUM - WITH TRAITS <short> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		char													Array[]={"Timmy Anderson"};
		size_t													Length=((sizeof(Array)/sizeof(Array[0]))-1);

		// !!! Vrati korektnu VALUE. RETURN VALUE TYPE je urceny TEMPLATE CLASS SPECIALIZATION [SFixedTraitSumTraits<char>].
		auto													ReturnValue=FixedTraitsSumWithTraits(Array,(Array+Length));

		wcout << L"SUM - WITH TRAITS <char> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
auto ValueTraitsSum1(const TType* Begin, const TType* End)
{
	using														TResult=typename SValueTraitSum1<TType>::TSum;

	// !!!!! DEFAULT VALUE sa zoberie z TYPE TRAIT.
	TResult														Total=SValueTraitSum1<TType>::ZERO;

	while (Begin!=End)
	{
		Total+=*Begin;

		++Begin;
	}

	return(Total);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
auto ValueTraitsSum2(const TType* Begin, const TType* End)
{
	using														TResult=typename SValueTraitSum2<TType>::TSum;

	// !!!!! DEFAULT VALUE sa zoberie z TYPE TRAIT pomocou STATIC METHOD.
	TResult														Total=SValueTraitSum2<TType>::GetZero();

	while (Begin!=End)
	{
		Total+=*Begin;

		++Begin;
	}

	return(Total);
}
//----------------------------------------------------------------------------------------------------------------------
void TestValueTraits(void)
{
	PrintLineSeparator();

	{
		int														Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=ValueTraitsSum1(Array,(Array+Length));

		wcout << L"VALUE TRAITS 1 <int> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		char													Array[]={"Timmy Anderson"};
		size_t													Length=((sizeof(Array)/sizeof(Array[0]))-1);

		auto													ReturnValue=ValueTraitsSum1(Array,(Array+Length));

		wcout << L"VALUE TRAITS 1 <char> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		float													Array[]={1.1f,2.2f,3.3f,4.4f,5.5f};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		// !!! VALUE [ZERO] je deklarovana pomocou KEYWORD [constexpr].
		auto													ReturnValue=ValueTraitsSum1(Array,(Array+Length));

		wcout << L"VALUE TRAITS 1 <float> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		double													Array[]={1.1,2.2,3.3,4.4,5.5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		// !!! VALUE [ZERO] je DEFINED v SOURCE FILE [.CPP].
		auto													ReturnValue=ValueTraitsSum1(Array,(Array+Length));

		wcout << L"VALUE TRAITS 1 <double> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CBigInt													Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		// !!! VALUE [ZERO] je deklarovana pomocou KEYWORD [inline].
		auto													ReturnValue=ValueTraitsSum1(Array,(Array+Length));

		wcout << L"VALUE TRAITS 1 <CBigInt> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=ValueTraitsSum2(Array,(Array+Length));

		wcout << L"VALUE TRAITS 2 <int> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		char													Array[]={"Timmy Anderson"};
		size_t													Length=((sizeof(Array)/sizeof(Array[0]))-1);

		auto													ReturnValue=ValueTraitsSum2(Array,(Array+Length));

		wcout << L"VALUE TRAITS 2 <char> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		float													Array[]={1.1f,2.2f,3.3f,4.4f,5.5f};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=ValueTraitsSum2(Array,(Array+Length));

		wcout << L"VALUE TRAITS 2 <float> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		double													Array[]={1.1,2.2,3.3,4.4,5.5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=ValueTraitsSum2(Array,(Array+Length));

		wcout << L"VALUE TRAITS 2 <double> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CBigInt													Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=ValueTraitsSum2(Array,(Array+Length));

		wcout << L"VALUE TRAITS 2 <CBigInt> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TTrait=SParametrizedTraitSum<TType>>
auto ParametrizedTraitsSum(const TType* Begin, const TType* End)
{
	using														TResult=typename TTrait::TSum;

	// !!!!! DEFAULT VALUE sa zoberie z TYPE TRAIT pomocou STATIC METHOD.
	TResult														Total=TTrait::GetZero();

	while (Begin!=End)
	{
		Total+=*Begin;

		++Begin;
	}

	return(Total);
}
//----------------------------------------------------------------------------------------------------------------------
void TestParametrizedTraits(void)
{
	PrintLineSeparator();

	{
		int														Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=ParametrizedTraitsSum(Array,(Array+Length));

		wcout << L"PARAMETRIZED TRAITS <int> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		char													Array[]={"Timmy Anderson"};
		size_t													Length=((sizeof(Array)/sizeof(Array[0]))-1);

		auto													ReturnValue=ParametrizedTraitsSum(Array,(Array+Length));

		wcout << L"PARAMETRIZED TRAITS <char> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		float													Array[]={1.1f,2.2f,3.3f,4.4f,5.5f};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=ParametrizedTraitsSum(Array,(Array+Length));

		wcout << L"PARAMETRIZED TRAITS <float> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		double													Array[]={1.1,2.2,3.3,4.4,5.5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=ParametrizedTraitsSum(Array,(Array+Length));

		wcout << L"PARAMETRIZED TRAITS <double> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CBigInt													Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=ParametrizedTraitsSum(Array,(Array+Length));

		wcout << L"PARAMETRIZED TRAITS <CBigInt> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		short													Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		// !!! 2. TEMPLATE PARAMETER je urceny z DEFAULT TEMPLATE ARGUMENT.
		auto													ReturnValue=ParametrizedTraitsSum(Array,(Array+Length));

		wcout << L"PARAMETRIZED TRAITS <short> 1 - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		short													Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		// !!! TEMPLATE PARAMETERS su urcene EXPLICITNE.
		auto													ReturnValue=ParametrizedTraitsSum<short,SParametrizedTraitSum<long>>(Array,(Array+Length));

		wcout << L"PARAMETRIZED TRAITS <short> 2 - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! POLICY je zadana ako TEMPLATE TYPE PARAMETER.
template<typename TType, typename TPolicy=SPolicySum, typename TTrait=SParametrizedTraitSum<TType>>
auto TraitsWithPoliciesSum(const TType* Begin, const TType* End)
{
	using														TResult=typename TTrait::TSum;

	// !!!!! DEFAULT VALUE sa zoberie z TYPE TRAIT pomocou STATIC METHOD.
	TResult														Total=TTrait::GetZero();

	while (Begin!=End)
	{
		// !!!! Vola sa STATIC METHOD z POLICY CLASS.
		TPolicy::Execute(Total,*Begin);

		++Begin;
	}

	return(Total);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! POLICY je zadana ako TEMPLATE TEMPLATE PARAMETER.
template<typename TType, template<typename,typename> class TPolicy=SPolicySumAsTemplateClass, typename TTrait=SParametrizedTraitSum<TType>>
auto TraitsWithPoliciesSumAsTemplateClass(const TType* Begin, const TType* End)
{
	using														TResult=typename TTrait::TSum;

	// !!!!! DEFAULT VALUE sa zoberie z TYPE TRAIT pomocou STATIC METHOD.
	TResult														Total=TTrait::GetZero();

	while (Begin!=End)
	{
		// !!!! Vola sa STATIC METHOD z POLICY CLASS.
		TPolicy<TResult,TType>::Execute(Total,*Begin);

		++Begin;
	}

	return(Total);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTraitsWithPolicies(void)
{
	PrintLineSeparator();

	{
		int														Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=TraitsWithPoliciesSum(Array,(Array+Length));

		wcout << L"TRAITS WITH POLICIES <int> - DEFAULT POLICY - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		// !!!!! POLICY je EXPLICITNE definovana.
		auto													ReturnValue=TraitsWithPoliciesSum<int,SPolicyMultiple>(Array,(Array+Length));

		// !!!!! Vrati VALUE [0], pretoze sa vykonava NASOBENIE, pricom INITIAL VALUE je VALUE [0].
		wcout << L"TRAITS WITH POLICIES <int> - EXPLICIT POLICY - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=TraitsWithPoliciesSumAsTemplateClass(Array,(Array+Length));

		wcout << L"TRAITS WITH POLICIES <int> - AS TEMPLATE CLASS - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TIterator>
auto TraitsWithPoliciesSumAsTemplateClass(TIterator Begin, TIterator End)
{
	// !!!!! Pouziva sa STANDARD LIBRARY CLASS [iterator_traits<TYPE>].
	using														TResult=typename iterator_traits<TIterator>::value_type;

	TResult														Total{};

	while (Begin!=End)
	{
		Total+=*Begin;

		++Begin;
	}

	return(Total);
}
//----------------------------------------------------------------------------------------------------------------------
void TestIteratorTraits(void)
{
	PrintLineSeparator();

	{
		int														Array[]={1,2,3,4,5};
		size_t													Length=(sizeof(Array)/sizeof(Array[0]));

		auto													ReturnValue=TraitsWithPoliciesSumAsTemplateClass(Array,(Array+Length));

		wcout << L"ITERATOR TRAITS <int> - int[] - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		vector<int>												Vector({1,2,3,4,5});

		auto													ReturnValue=TraitsWithPoliciesSumAsTemplateClass(Vector.cbegin(),Vector.cend());

		wcout << L"ITERATOR TRAITS <int> - vector<int> - RETURN VALUE TYPE [" << GetTypeInfoName<decltype(ReturnValue)>() << L"] RETURN VALUE [" << ReturnValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctions(void)
{
	PrintLineSeparator();

	{
		size_t													Sizeof=STypeFunctionSizeof<int>::SIZEOF;

		wcout << L"TYPE FUNCTION <int> - SIZEOF VALUE [" << Sizeof << L"]." << endl;
	}

	PrintLineSeparator();

	{
		size_t													Sizeof=STypeFunctionSizeof<long double>::SIZEOF;

		wcout << L"TYPE FUNCTION <long double> - SIZEOF VALUE [" << Sizeof << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze CLASS [CElementTypeClass1] NEMA FIELD TYPE vystaveny pomocou USING, je nutne FIELD TYPE preniest ako TEMPLATE PARAMETER.
template<typename TField, typename TClass>
TField TemplateElementTypesNoUsing(const TClass& Object)
{
	TField														Value=Object.GetValue();

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze CLASS [CElementTypeClass2] MA FIELD TYPE vystaveny pomocou USING, tak ho NIE JE NUTNE preniest ako TEMPLATE PARAMETER.
template<typename TClass>
typename TClass::FieldType TemplateElementTypesWithUsing(const TClass& Object)
{
	typename TClass::FieldType									Value=Object.GetValue();

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze CLASS [CElementTypeClass3] MA FIELD TYPE vystaveny pomocou USING, tak ho NIE JE NUTNE preniest ako TEMPLATE PARAMETER. Zaroven ma GLOBALNY USING, ktory zjednodusuje implementaciu.
template<typename TClass>
ClassFieldType<TClass> TemplateElementTypesWithUsingAndGlobalUsing(const TClass& Object)
{
	ClassFieldType<TClass>										Value=Object.GetValue();

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionsElementTypes(void)
{
	PrintLineSeparator();

	{
		using													CollectionType=vector<int>;
		using													ElementType=STypeFunctionElementType<CollectionType>::ElementType;

		wcout << L"COLLECTION - COLLECTION TYPE [" << GetTypeInfoName<CollectionType>() << L"] ELEMENT TYPE [" << GetTypeInfoName<ElementType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													CollectionType=list<int>;
		using													ElementType=STypeFunctionElementType<CollectionType>::ElementType;

		wcout << L"COLLECTION - COLLECTION TYPE [" << GetTypeInfoName<CollectionType>() << L"] ELEMENT TYPE [" << GetTypeInfoName<ElementType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													CollectionType=int[10];
		using													ElementType=STypeFunctionElementType<CollectionType>::ElementType;

		wcout << L"COLLECTION - COLLECTION TYPE [" << GetTypeInfoName<CollectionType>() << L"] ELEMENT TYPE [" << GetTypeInfoName<ElementType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													CollectionType=int[];
		using													ElementType=STypeFunctionElementType<CollectionType>::ElementType;

		wcout << L"COLLECTION - COLLECTION TYPE [" << GetTypeInfoName<CollectionType>() << L"] ELEMENT TYPE [" << GetTypeInfoName<ElementType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CElementTypeClass1										Object(100);

		// !!!!! Kedze CLASS [CElementTypeClass1] NEMA FIELD TYPE vystaveny pomocou USING, je nutne FIELD TYPE preniest ako TEMPLATE PARAMETER.
		int														FieldValue=TemplateElementTypesNoUsing<int>(Object);

		wcout << L"CLASS - CLASS TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] FIELD TYPE [" << GetTypeInfoName<decltype(FieldValue)>() << L"] FIELD VALUE [" << FieldValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CElementTypeClass2										Object(100);

		// !!!!! Kedze CLASS [CElementTypeClass2] MA FIELD TYPE vystaveny pomocou USING, tak ho NIE JE NUTNE preniest ako TEMPLATE PARAMETER.
		CElementTypeClass2::FieldType							FieldValue=TemplateElementTypesWithUsing(Object);

		wcout << L"CLASS - CLASS TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] FIELD TYPE [" << GetTypeInfoName<decltype(FieldValue)>() << L"] FIELD VALUE [" << FieldValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CElementTypeClass3										Object(100);

		// !!!!! Kedze CLASS [CElementTypeClass3] MA FIELD TYPE vystaveny pomocou USING, tak ho NIE JE NUTNE preniest ako TEMPLATE PARAMETER. Zaroven ma GLOBALNY USING, ktory zjednodusuje implementaciu.
		ClassFieldType<CElementTypeClass3>						FieldValue=TemplateElementTypesWithUsingAndGlobalUsing(Object);

		wcout << L"CLASS - CLASS TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] FIELD TYPE [" << GetTypeInfoName<decltype(FieldValue)>() << L"] FIELD VALUE [" << FieldValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionsAddLReference(void)
{
	PrintLineSeparator();

	{
		using													OriginalType=int;
		using													ModifiedType=STypeFunctionAddLValueReference<OriginalType>::Type;

		wcout << L"ADD L REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int&;
		using													ModifiedType=STypeFunctionAddLValueReference<OriginalType>::Type;

		wcout << L"ADD L REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int&&;
		using													ModifiedType=STypeFunctionAddLValueReference<OriginalType>::Type;

		wcout << L"ADD L REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=void;
		using													ModifiedType=STypeFunctionAddLValueReference<OriginalType>::Type;

		wcout << L"ADD L REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionsAddRReference(void)
{
	PrintLineSeparator();

	{
		using													OriginalType=int;
		using													ModifiedType=STypeFunctionAddRValueReference<OriginalType>::Type;

		wcout << L"ADD R REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int&;
		using													ModifiedType=STypeFunctionAddRValueReference<OriginalType>::Type;

		wcout << L"ADD R REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int&&;
		using													ModifiedType=STypeFunctionAddRValueReference<OriginalType>::Type;

		wcout << L"ADD R REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=void;
		using													ModifiedType=STypeFunctionAddRValueReference<OriginalType>::Type;

		wcout << L"ADD R REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionsRemoveReference(void)
{
	PrintLineSeparator();

	{
		using													OriginalType=int;
		using													ModifiedType=STypeFunctionRemoveReference<OriginalType>::Type;

		wcout << L"REMOVE REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int&;
		using													ModifiedType=STypeFunctionRemoveReference<OriginalType>::Type;

		wcout << L"REMOVE REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int&&;
		using													ModifiedType=STypeFunctionRemoveReference<OriginalType>::Type;

		wcout << L"REMOVE REFERENCE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionsRemoveConstVolatile(void)
{
	PrintLineSeparator();

	{
		using													OriginalType=int;
		using													ModifiedType=STypeFunctionRemoveConst<OriginalType>::Type;

		wcout << L"REMOVE CONST - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=const int;
		using													ModifiedType=STypeFunctionRemoveConst<OriginalType>::Type;

		wcout << L"REMOVE CONST - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int;
		using													ModifiedType=STypeFunctionRemoveVolatile<OriginalType>::Type;

		wcout << L"REMOVE VOLATILE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=volatile int;
		using													ModifiedType=STypeFunctionRemoveVolatile<OriginalType>::Type;

		wcout << L"REMOVE VOLATILE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int;
		using													ModifiedType=STypeFunctionRemoveConstVolatile<OriginalType>::Type;

		wcout << L"REMOVE CONST VOLATILE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=const int;
		using													ModifiedType=STypeFunctionRemoveConstVolatile<OriginalType>::Type;

		wcout << L"REMOVE CONST VOLATILE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=volatile int;
		using													ModifiedType=STypeFunctionRemoveConstVolatile<OriginalType>::Type;

		wcout << L"REMOVE CONST VOLATILE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=const volatile int;
		using													ModifiedType=STypeFunctionRemoveConstVolatile<OriginalType>::Type;

		wcout << L"REMOVE CONST VOLATILE - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionSTypeFunctionDecay(void)
{
	PrintLineSeparator();

	{
		using													OriginalType=int;
		using													ModifiedType=STypeFunctionDecay<OriginalType>::Type;

		wcout << L"DECAY - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=const int;
		using													ModifiedType=STypeFunctionDecay<OriginalType>::Type;

		wcout << L"DECAY - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=volatile int;
		using													ModifiedType=STypeFunctionDecay<OriginalType>::Type;

		wcout << L"DECAY - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int[];
		using													ModifiedType=STypeFunctionDecay<OriginalType>::Type;

		wcout << L"DECAY - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=int[10];
		using													ModifiedType=STypeFunctionDecay<OriginalType>::Type;

		wcout << L"DECAY - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													OriginalType=void(int,double);
		using													ModifiedType=STypeFunctionDecay<OriginalType>::Type;

		wcout << L"DECAY - ORIGINAL TYPE [" << GetTypeInfoName<OriginalType>() << L"] MODIFIED TYPE [" << GetTypeInfoName<ModifiedType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionsIsSame(void)
{
	PrintLineSeparator();

	{
		using													Type1=int;
		using													Type2=int;

		// !!! Pouzije sa TYPE TRAIT.
		constexpr bool											IsSame=STypeFunctionIsSame<Type1,Type2>::VALUE;

		wcout << L"IS SAME - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] IS SAME [" << IsSame << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=double;
		using													Type2=int;

		// !!! Pouzije sa TYPE TRAIT.
		constexpr bool											IsSame=STypeFunctionIsSame<Type1,Type2>::VALUE;

		wcout << L"IS SAME - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] IS SAME [" << IsSame << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=const int;
		using													Type2=int;

		// !!! Pouzije sa TYPE TRAIT.
		constexpr bool											IsSame=STypeFunctionIsSame<Type1,Type2>::VALUE;

		wcout << L"IS SAME - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] IS SAME [" << IsSame << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=int;
		using													Type2=int;

		// !!! Pouzije sa TEMPLATE VARIABLE.
		constexpr bool											IsSame=TypeFunctionIsSame<Type1,Type2>;

		wcout << L"IS SAME (TEMPLATE VARIABLE) - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] IS SAME [" << IsSame << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void TemplateTypeFunctionsIsSameTagDispatching(TypeFunctionFalseType)
{
	wcout << L"IS SAME TAG DISPATCHING (FUNCTION) - TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"] IS SAME [FALSE]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void TemplateTypeFunctionsIsSameTagDispatching(TypeFunctionTrueType)
{
	wcout << L"IS SAME TAG DISPATCHING (FUNCTION) - TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"] IS SAME [TRUE]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionsIsSameTagDispatching(void)
{
	PrintLineSeparator();

	{
		using													Type1=int;
		using													Type2=int;

		// !!! Pouzije sa TYPE TRAIT.
		constexpr bool											IsSame=STypeFunctionIsSameTagDispatching<Type1,Type2>::VALUE;

		wcout << L"IS SAME TAG DISPATCHING - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] IS SAME [" << IsSame << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=double;
		using													Type2=int;

		// !!! Pouzije sa TYPE TRAIT.
		constexpr bool											IsSame=STypeFunctionIsSame<Type1,Type2>::VALUE;

		wcout << L"IS SAME TAG DISPATCHING - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] IS SAME [" << IsSame << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=const int;
		using													Type2=int;

		// !!! Pouzije sa TYPE TRAIT.
		constexpr bool											IsSame=STypeFunctionIsSameTagDispatching<Type1,Type2>::VALUE;

		wcout << L"IS SAME TAG DISPATCHING - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] IS SAME [" << IsSame << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=int;
		using													Type2=int;

		// !!! Pouzije sa TEMPLATE USING.
		constexpr bool											IsSame=TypeFunctionIsSameTagDispatching<Type1,Type2>::VALUE;

		wcout << L"IS SAME TAG DISPATCHING (TEMPLATE USING) - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] IS SAME [" << IsSame << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=int;
		using													Type2=int;

		// !!! Pouzije sa TYPE TRAIT.
		using													IsSameType=STypeFunctionIsSameTagDispatching<Type1,Type2>::Type;

		// !!!!! VDAKA pouzitiu TAG DISPATCHING je mozne vykonat FUNCTION OVERLOADING.
		TemplateTypeFunctionsIsSameTagDispatching<Type1,Type2>(IsSameType{});
	}

	PrintLineSeparator();

	{
		using													Type1=double;
		using													Type2=int;

		// !!! Pouzije sa TYPE TRAIT.
		using													IsSameType=STypeFunctionIsSameTagDispatching<Type1,Type2>::Type;

		// !!!!! VDAKA pouzitiu TAG DISPATCHING je mozne vykonat FUNCTION OVERLOADING.
		TemplateTypeFunctionsIsSameTagDispatching<Type1,Type2>(IsSameType{});
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Vzhladom na implementaciu TRAIT [STypeFunctionResultOperatorPlus] MUSI mat TYPE [TType1] a TYPE [TType2] DEFAULT CONSTRUCTOR.
template<typename TType1, typename TType2>
typename STypeFunctionResultOperatorPlus<TType1,TType2>::Type TemplateTypeFunctionsResultOperatorPlus(TType1 Value1, TType2 Value2)
{
	using														ResultType=typename STypeFunctionResultOperatorPlus<TType1,TType2>::Type;

	ResultType													Result=(Value1+Value2);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionsResultOperatorPlus(void)
{
	PrintLineSeparator();

	{
		int														Value1=100;
		int														Value2=200;

		auto													Result=TemplateTypeFunctionsResultOperatorPlus(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Value1=100;
		double													Value2=222.222;

		auto													Result=TemplateTypeFunctionsResultOperatorPlus(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Value1=100;
		const double											Value2=222.222;

		auto													Result=TemplateTypeFunctionsResultOperatorPlus(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CHasDefaultConstructor									Value1(100);
		int														Value2=200;

		auto													Result=TemplateTypeFunctionsResultOperatorPlus(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze TYPE [CNoDefaultConstructor] NEMA DEFAULT CONSTRUCTOR, ktory TRAIT [TemplateTypeFunctionsResultOperatorPlus] VYZADUJE.
		CNoDefaultConstructor									Value1(100);
		int														Value2=200;

		auto													Result=TemplateTypeFunctionsResultOperatorPlus(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Vzhladom na to, ze TRAIT [STypeFunctionResultOperatorPlusDeclval] pouziva TYPE TRAIT [declval<TType>] NIE JE NUTNE, aby TYPE [TType1] a TYPE [TType2] mali DEFAULT CONSTRUCTOR.
template<typename TType1, typename TType2>
typename STypeFunctionResultOperatorPlusDeclval<TType1,TType2>::Type TemplateTypeFunctionsResultOperatorPlusDeclval(TType1 Value1, TType2 Value2)
{
	using														ResultType=typename STypeFunctionResultOperatorPlusDeclval<TType1,TType2>::Type;

	ResultType													Result=(Value1+Value2);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeFunctionsResultOperatorPlusDeclval(void)
{
	PrintLineSeparator();

	{
		int														Value1=100;
		int														Value2=200;

		auto													Result=TemplateTypeFunctionsResultOperatorPlusDeclval(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Value1=100;
		double													Value2=222.222;

		auto													Result=TemplateTypeFunctionsResultOperatorPlusDeclval(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														Value1=100;
		const double											Value2=222.222;

		auto													Result=TemplateTypeFunctionsResultOperatorPlusDeclval(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CHasDefaultConstructor									Value1(100);
		int														Value2=200;

		auto													Result=TemplateTypeFunctionsResultOperatorPlusDeclval(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! CODE ZBEHNE OK, pretoze vdaka pouziti TYPE TRAIT [declval<TType>] NIE JE NUTNE, aby mal TYPE [CNoDefaultConstructor] DEFAULT CONSTRUCTOR.
		CNoDefaultConstructor									Value1(100);
		int														Value2=200;

		auto													Result=TemplateTypeFunctionsResultOperatorPlusDeclval(Value1,Value2);

		wcout << L"TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] RESULT TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] RESULT [" << Result.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAETraitIsDefaultConstructible(void)
{
	PrintLineSeparator();

	{
		using													Type=int;

		constexpr bool											Value=SSFINAETraitIsDefaultConstructible<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CHasDefaultConstructor;

		constexpr bool											Value=SSFINAETraitIsDefaultConstructible<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CNoDefaultConstructor;

		// !!! Vrati FALSE, lebo TYPE [CNoDefaultConstructor] NEMA DEFAULT CONSTRUCTOR.
		constexpr bool											Value=SSFINAETraitIsDefaultConstructible<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAETraitIsDefaultConstructiblePredicate(void)
{
	PrintLineSeparator();

	{
		using													Type=int;

		constexpr bool											Value=SSFINAETraitIsDefaultConstructiblePredicate<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - PREDICATE - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CHasDefaultConstructor;

		constexpr bool											Value=SSFINAETraitIsDefaultConstructiblePredicate<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - PREDICATE - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CNoDefaultConstructor;

		// !!! Vrati FALSE, lebo TYPE [CNoDefaultConstructor] NEMA DEFAULT CONSTRUCTOR.
		constexpr bool											Value=SSFINAETraitIsDefaultConstructiblePredicate<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - PREDICATE - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAETraitIsDefaultConstructibleSpecialization(void)
{
	PrintLineSeparator();

	{
		using													Type=int;

		constexpr bool											Value=SSFINAETraitIsDefaultConstructibleSpecialization<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - SPECIALIZATION - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CHasDefaultConstructor;

		constexpr bool											Value=SSFINAETraitIsDefaultConstructibleSpecialization<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - SPECIALIZATION - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CNoDefaultConstructor;

		// !!! Vrati FALSE, lebo TYPE [CNoDefaultConstructor] NEMA DEFAULT CONSTRUCTOR.
		constexpr bool											Value=SSFINAETraitIsDefaultConstructibleSpecialization<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - SPECIALIZATION - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAETraitIsDefaultConstructibleLambda(void)
{
	PrintLineSeparator();

	{
		using													Type=int;

		constexpr bool											Value=SSFINAETraitIsDefaultConstructibleLambda<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - LAMBDA - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CHasDefaultConstructor;

		constexpr bool											Value=SSFINAETraitIsDefaultConstructibleLambda<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - LAMBDA - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CNoDefaultConstructor;

		// !!! Vrati FALSE, lebo TYPE [CNoDefaultConstructor] NEMA DEFAULT CONSTRUCTOR.
		constexpr bool											Value=SSFINAETraitIsDefaultConstructibleLambda<Type>::VALUE;

		wcout << L"IS DEFAULT CONSTRUCTIBLE - LAMBDA - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CWrapperType<typename STypeFunctionResultOperatorPlusDeclval<TType1,TType2>::Type> operator+(const CWrapperType<TType1>& Value1, const CWrapperType<TType2>& Value2)
{
	const TType1&												InnerValue1=Value1.GetValue();
	const TType2&												InnerValue2=Value2.GetValue();
	typename STypeFunctionResultOperatorPlusDeclval<TType1,TType2>::Type	Result(InnerValue1+InnerValue2);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
CWrapperType<CType1> operator+(const CWrapperType<CType1>& Value1, const CWrapperType<CType2>& Value2)
{
	const CType1&												InnerValue1=Value1.GetValue();
	const CType2&												InnerValue2=Value2.GetValue();
	CType1														Result(InnerValue1.GetValue()+InnerValue2.GetValue());
	
	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TYPE TRAIT [STypeFunctionResultOperatorMinusHasMinus<TYPE_1,TYPE_2>] dokaze v pripade, ze medzi TYPE [TType1] a TYPE [TType2] NIE je definovany OPERATOR [OPERATOR-] zobrazit presnejsiu ERROR MESSAGE.
template<typename TType1, typename TType2>
CWrapperType<typename STypeFunctionResultOperatorMinusHasMinus<TType1,TType2>::Type> operator-(const CWrapperType<TType1>& Value1, const CWrapperType<TType2>& Value2)
{
	const TType1&												InnerValue1=Value1.GetValue();
	const TType2&												InnerValue2=Value2.GetValue();
	typename STypeFunctionResultOperatorMinusHasMinus<TType1,TType2>::Type	Result(InnerValue1-InnerValue2);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
CWrapperType<CType3> operator-(const CWrapperType<CType3>& Value1, const CWrapperType<CType4>& Value2)
{
	const CType3&												InnerValue1=Value1.GetValue();
	const CType4&												InnerValue2=Value2.GetValue();
	CType3														Result(InnerValue1.GetValue()-InnerValue2.GetValue());
	
	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAEFriendlyTrait(void)
{
	PrintLineSeparator();

	{
		CWrapperType<CType1>									Value1(100);
		CWrapperType<CType2>									Value2(200);
		auto													Result=(Value1+Value2);

		wcout << L"FRIENDLY TRAIT - OPERATOR+ - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] VALUE [" << Result.GetValue() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		CWrapperType<CType3>									Value1(100);
		CWrapperType<CType4>									Value2(200);

		// !!!!! COMPILER hodi ERROR, pretoze medzi TYPE [CType3] a TYPE [CType4] NIE je definovany OPERATOR [OPERATOR+].
		auto													Result=(Value1+Value2);

		wcout << L"FRIENDLY TRAIT - OPERATOR+ - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] VALUE [" << Result.GetValue() << L"]." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	{
		CWrapperType<CType1>									Value1(100);
		CWrapperType<CType2>									Value2(200);

		// !!!!! COMPILER hodi ERROR, pretoze medzi TYPE [CType1] a TYPE [CType2] NIE je definovany OPERATOR [OPERATOR-].
		auto													Result=(Value1-Value2);

		wcout << L"FRIENDLY TRAIT - OPERATOR- - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] VALUE [" << Result.GetValue() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		CWrapperType<CType3>									Value1(100);
		CWrapperType<CType4>									Value2(200);
		auto													Result=(Value1-Value2);

		wcout << L"FRIENDLY TRAIT - OPERATOR- - TYPE [" << GetTypeInfoName<decltype(Result)>() << L"] VALUE [" << Result.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSFINAETraitIsConvertible(void)
{
	PrintLineSeparator();

	{
		using													FromType=int;
		using													ToType=double;

		constexpr bool											Value=SSFINAETraitIsConvertible<FromType,ToType>::VALUE;

		wcout << L"IS CONVERTIBLE - FROM TYPE [" << GetTypeInfoName<FromType>() << L"] TO TYPE [" << GetTypeInfoName<ToType>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													FromType=double;
		using													ToType=int;

		constexpr bool											Value=SSFINAETraitIsConvertible<FromType,ToType>::VALUE;

		wcout << L"IS CONVERTIBLE - FROM TYPE [" << GetTypeInfoName<FromType>() << L"] TO TYPE [" << GetTypeInfoName<ToType>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													FromType=double;
		using													ToType=CString;

		constexpr bool											Value=SSFINAETraitIsConvertible<FromType,ToType>::VALUE;

		wcout << L"IS CONVERTIBLE - FROM TYPE [" << GetTypeInfoName<FromType>() << L"] TO TYPE [" << GetTypeInfoName<ToType>() << L"] VALUE [" << Value << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		using													FromType=CString;
		using													ToType=void;

		// !!!!! COMPILER hodi ERROR, pretoze TYPE [TTo] NEMOZE byt TYPE [void]. C++ hodi ERROR, ak sa pokusa CODE vytvorit instanciu z TYPE [void].
		constexpr bool											Value=SSFINAETraitIsConvertible<FromType,ToType>::VALUE;

		wcout << L"IS CONVERTIBLE - FROM TYPE [" << GetTypeInfoName<FromType>() << L"] TO TYPE [" << GetTypeInfoName<ToType>() << L"] VALUE [" << Value << L"]." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	{
		using													FromType=void;
		using													ToType=void;

		// !!!!! COMPILER hodi ERROR, pretoze TYPE [TTo] NEMOZE byt TYPE [void]. C++ hodi ERROR, ak sa pokusa CODE vytvorit instanciu z TYPE [void].
		constexpr bool											Value=SSFINAETraitIsConvertible<FromType,ToType>::VALUE;

		wcout << L"IS CONVERTIBLE - FROM TYPE [" << GetTypeInfoName<FromType>() << L"] TO TYPE [" << GetTypeInfoName<ToType>() << L"] VALUE [" << Value << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		using													FromType=int;
		using													ToType=double;

		constexpr bool											Value=SSFINAETraitIsConvertibleWithChecks<FromType,ToType>::VALUE;

		wcout << L"IS CONVERTIBLE WITH CHECKS - FROM TYPE [" << GetTypeInfoName<FromType>() << L"] TO TYPE [" << GetTypeInfoName<ToType>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													FromType=int;
		using													ToType=void;

		constexpr bool											Value=SSFINAETraitIsConvertibleWithChecks<FromType,ToType>::VALUE;

		wcout << L"IS CONVERTIBLE WITH CHECKS - FROM TYPE [" << GetTypeInfoName<FromType>() << L"] TO TYPE [" << GetTypeInfoName<ToType>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													FromType=void;
		using													ToType=void;

		constexpr bool											Value=SSFINAETraitIsConvertibleWithChecks<FromType,ToType>::VALUE;

		wcout << L"IS CONVERTIBLE WITH CHECKS - FROM TYPE [" << GetTypeInfoName<FromType>() << L"] TO TYPE [" << GetTypeInfoName<ToType>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDetectingMembersTraitHasMemberType(void)
{
	PrintLineSeparator();

	{
		using													Type=CTypeNoMembers;

		constexpr bool											Value=SDetectingMembersHasMemberType<Type>::VALUE;

		wcout << L"HAS MEMBER TYPE 'MY_TYPE' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMYTYPEMember1;

		constexpr bool											Value=SDetectingMembersHasMemberType<Type>::VALUE;

		wcout << L"HAS MEMBER TYPE 'MY_TYPE' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMYTYPEMember1&;

		// !!!!! Vdaka aplikovaniu TYPE TRAIT [STypeFunctionRemoveReference] je vratena VALUE [true], namiesto VALUE [false].
		constexpr bool											Value=SDetectingMembersHasMemberType<Type>::VALUE;

		wcout << L"HAS MEMBER TYPE 'MY_TYPE' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMYTYPEMember1&&;

		// !!!!! Vdaka aplikovaniu TYPE TRAIT [STypeFunctionRemoveReference] je vratena VALUE [true], namiesto VALUE [false].
		constexpr bool											Value=SDetectingMembersHasMemberType<Type>::VALUE;

		wcout << L"HAS MEMBER TYPE 'MY_TYPE' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMYTYPEMember2;

		// !!!!! TYPE TRAIT vrati VALUE [true], hoci TYPE [CTypeWithMYTYPEMember2] NEOBSAHUJE TYPE MEMBER [MY_TYPE]. Avsak TYPE [CTypeWithMYTYPEMember2] je DERIVED z TYPE [MY_TYPE] a tym padom do TYPE [CTypeWithMYTYPEMember2] je takto vlozeny TYPE [MY_TYPE].
		constexpr bool											Value=SDetectingMembersHasMemberType<Type>::VALUE;

		wcout << L"HAS MEMBER TYPE 'MY_TYPE' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MACRO vygeneruje TYPE TRAIT STRUCTURE na zistenie ci dany TYPE ma MEMBER TYPE [MY_TYPE_1].
DEFINE_HAS_TYPE(MY_TYPE_1);
// !!!!! MACRO vygeneruje TYPE TRAIT STRUCTURE na zistenie ci dany TYPE ma MEMBER TYPE [MY_TYPE_2].
DEFINE_HAS_TYPE(MY_TYPE_2);
//----------------------------------------------------------------------------------------------------------------------
void TestDetectingMembersTraitMacroHasMemberType(void)
{
	PrintLineSeparator();

	{
		using													Type=CTypeNoMembers;
		
		constexpr bool											Value=MacroHasMemberType_MY_TYPE_1<Type>::VALUE;

		wcout << L"MACRO - HAS MEMBER TYPE 'MY_TYPE_1' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeNoMembers;
		
		constexpr bool											Value=MacroHasMemberType_MY_TYPE_2<Type>::VALUE;

		wcout << L"MACRO - HAS MEMBER TYPE 'MY_TYPE_2' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMYTYPEMembers;
		
		constexpr bool											Value=MacroHasMemberType_MY_TYPE_1<Type>::VALUE;

		wcout << L"MACRO - HAS MEMBER TYPE 'MY_TYPE_1' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMYTYPEMembers;
		
		constexpr bool											Value=MacroHasMemberType_MY_TYPE_2<Type>::VALUE;

		wcout << L"MACRO - HAS MEMBER TYPE 'MY_TYPE_2' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MACRO vygeneruje TYPE TRAIT STRUCTURE na zistenie ci dany TYPE ma MEMBER METHOD [GetValue1].
DEFINE_HAS_MEMBER(GetValue1);
// !!!!! MACRO vygeneruje TYPE TRAIT STRUCTURE na zistenie ci dany TYPE ma MEMBER METHOD [GetValue2].
DEFINE_HAS_MEMBER(GetValue2);
//----------------------------------------------------------------------------------------------------------------------
void TestDetectingMembersTraitMacroHasNonMemberType(void)
{
	PrintLineSeparator();

	{
		using													Type=CTypeNoMembers;
		
		constexpr bool											Value=MacroHasMemberNonType_GetValue1<Type>::VALUE;

		wcout << L"MACRO - HAS MEMBER NON-TYPE 'GetValue1' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeNoMembers;
		
		constexpr bool											Value=MacroHasMemberNonType_GetValue2<Type>::VALUE;

		wcout << L"MACRO - HAS MEMBER NON-TYPE 'GetValue2' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMYTYPEMembers;
		
		constexpr bool											Value=MacroHasMemberNonType_GetValue1<Type>::VALUE;

		wcout << L"MACRO - HAS MEMBER NON-TYPE 'GetValue1' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMYTYPEMembers;
		
		constexpr bool											Value=MacroHasMemberNonType_GetValue2<Type>::VALUE;

		wcout << L"MACRO - HAS MEMBER NON-TYPE 'GetValue2' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDetectingMembersTraitHasFunctionGetValue(void)
{
	PrintLineSeparator();

	{
		using													Type=CTypeNoMembers;
		
		constexpr bool											Value=STypeClassificationHasFunctionGetValue<Type>::VALUE;

		wcout << L"MACRO - HAS METHOD 'GetValue' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMethods;
		
		constexpr bool											Value=STypeClassificationHasFunctionGetValue<Type>::VALUE;

		wcout << L"MACRO - HAS METHOD 'GetValue' - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool operator<(const CType1& Value1, const CType2& Value2)
{
	bool														Result=(Value1.GetValue()<Value2.GetValue());

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestDetectingMembersTraitHasOperatorLess(void)
{
	PrintLineSeparator();

	{
		using													Type1=CType1;
		using													Type2=CType2;
		
		constexpr bool											Value=STypeClassificationHasOperatorLess<Type1,Type2>::VALUE;

		wcout << L"MACRO - HAS OPERATOR [OPERATOR<] - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=CType3;
		using													Type2=CType4;
		
		constexpr bool											Value=STypeClassificationHasOperatorLess<Type1,Type2>::VALUE;

		wcout << L"MACRO - HAS OPERATOR [OPERATOR<] - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDetectingMembersTraitHasVariousMembers(void)
{
	PrintLineSeparator();

	{
		using													Type=CTypeNoMembers;
		
		constexpr bool											Value=STypeClassificationHasVariousMembers<Type>::VALUE;

		wcout << L"MACRO - HAS VARIOUS MEMBERS - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMethods;
		
		constexpr bool											Value=STypeClassificationHasVariousMembers<Type>::VALUE;

		wcout << L"MACRO - HAS VARIOUS MEMBERS - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDetectingMembersTraitUsingGenericLambdas(void)
{
	PrintLineSeparator();

	{
		using													Type=CTypeNoMembers;
		
		constexpr bool											Value1=DetectingMembersTraitHasField(SFINAETraitFactoryGenericLambdaType<Type>).VALUE;
		constexpr bool											Value2=DetectingMembersTraitHasFieldType<Type>::VALUE;

		wcout << L"HAS FIELD - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=SHasFieldMyValue;

		constexpr bool											Value1=DetectingMembersTraitHasField(SFINAETraitFactoryGenericLambdaType<Type>).VALUE;
		constexpr bool											Value2=DetectingMembersTraitHasFieldType<Type>::VALUE;

		wcout << L"HAS FIELD - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeNoMembers;
		
		constexpr bool											Value1=DetectingMembersTraitHasType(SFINAETraitFactoryGenericLambdaType<Type>).VALUE;
		constexpr bool											Value2=DetectingMembersTraitHasTypeType<Type>::VALUE;

		wcout << L"HAS TYPE - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type=CTypeWithMYTYPEMember1;

		constexpr bool											Value1=DetectingMembersTraitHasType(SFINAETraitFactoryGenericLambdaType<Type>).VALUE;
		constexpr bool											Value2=DetectingMembersTraitHasTypeType<Type>::VALUE;

		wcout << L"HAS TYPE - TYPE [" << GetTypeInfoName<Type>() << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													Type1=CType1;
		using													Type2=CType2;
		
		constexpr bool											Value1=DetectingMembersTraitHasTypeOperator(SFINAETraitFactoryGenericLambdaType<Type1>,SFINAETraitFactoryGenericLambdaType<Type2>).VALUE;
		constexpr bool											Value2=DetectingMembersTraitHasTypeOperatorType<Type1,Type2>::VALUE;

		wcout << L"HAS OPERATOR - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
	}
	
	PrintLineSeparator();

	{
		using													Type1=CType3;
		using													Type2=CType4;
		
		constexpr bool											Value1=DetectingMembersTraitHasTypeOperator(SFINAETraitFactoryGenericLambdaType<Type1>,SFINAETraitFactoryGenericLambdaType<Type2>).VALUE;
		constexpr bool											Value2=DetectingMembersTraitHasTypeOperatorType<Type1,Type2>::VALUE;

		wcout << L"HAS OPERATOR - TYPE 1 [" << GetTypeInfoName<Type1>() << L"] TYPE 2 [" << GetTypeInfoName<Type2>() << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestFixedTraits();
	//TestValueTraits();
	//TestParametrizedTraits();
	//TestTraitsWithPolicies();
	//TestIteratorTraits();
	//TestTypeFunctions();
	//TestTypeFunctionsElementTypes();
	//TestTypeFunctionsAddLReference();
	//TestTypeFunctionsAddRReference();
	//TestTypeFunctionsRemoveReference();
	//TestTypeFunctionsRemoveConstVolatile();
	//TestTypeFunctionSTypeFunctionDecay();
	//TestTypeFunctionsIsSame();
	//TestTypeFunctionsIsSameTagDispatching();
	//TestTypeFunctionsResultOperatorPlus();
	//TestTypeFunctionsResultOperatorPlusDeclval();
	//TestSFINAETraitIsDefaultConstructible();
	//TestSFINAETraitIsDefaultConstructiblePredicate();
	//TestSFINAETraitIsDefaultConstructibleSpecialization();
	//TestSFINAEFriendlyTrait();
	//TestSFINAETraitIsConvertible();
	//TestDetectingMembersTraitHasMemberType();
	//TestDetectingMembersTraitMacroHasMemberType();
	//TestDetectingMembersTraitMacroHasNonMemberType();
	//TestDetectingMembersTraitHasFunctionGetValue();
	//TestDetectingMembersTraitHasOperatorLess();
	//TestDetectingMembersTraitHasVariousMembers();
	TestDetectingMembersTraitUsingGenericLambdas();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------