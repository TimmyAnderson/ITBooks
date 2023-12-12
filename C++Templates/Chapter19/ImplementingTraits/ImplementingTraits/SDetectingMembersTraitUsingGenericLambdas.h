//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <utility>
#include "SSFINAETraitFactoryGenericLambda.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TYPE TRAIT testuje ci TYPE ma FIELD [MyValue].
constexpr auto													DetectingMembersTraitHasField=SFINAETraitFactoryGenericLambdaIsValid([](auto Parameter) -> decltype((void)SFINAETraitFactoryGenericLambdaGetValueType(Parameter).MyValue){});
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
using															DetectingMembersTraitHasFieldType=decltype(DetectingMembersTraitHasField(std::declval<SSFINAETraitFactoryGenericLambda<TType>>()));
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TYPE TRAIT testuje ci TYPE ma TYPE [MY_TYPE].
constexpr auto													DetectingMembersTraitHasType=SFINAETraitFactoryGenericLambdaIsValid([](auto Parameter) -> typename decltype(SFINAETraitFactoryGenericLambdaGetValueType(Parameter))::MY_TYPE {});
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
using															DetectingMembersTraitHasTypeType=decltype(DetectingMembersTraitHasType(std::declval<SSFINAETraitFactoryGenericLambda<TType>>()));
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TYPE TRAIT testuje ci TYPE [Type1] a TYPE [Type2] ma OPERATOR [OPERATOR<].
constexpr auto													DetectingMembersTraitHasTypeOperator=SFINAETraitFactoryGenericLambdaIsValid([](auto X, auto Y) -> decltype(SFINAETraitFactoryGenericLambdaGetValueType(X) < SFINAETraitFactoryGenericLambdaGetValueType(Y)) {});
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
using															DetectingMembersTraitHasTypeOperatorType=decltype(DetectingMembersTraitHasTypeOperator(std::declval<SSFINAETraitFactoryGenericLambda<TType1>>(),std::declval<SSFINAETraitFactoryGenericLambda<TType2>>()));
//----------------------------------------------------------------------------------------------------------------------