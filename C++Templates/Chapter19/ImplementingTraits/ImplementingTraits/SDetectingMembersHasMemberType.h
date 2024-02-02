//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STypeFunctionBoolConstant.h"
#include "SVoidType.h"
#include "STypeFunctionRemoveReference.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PRIMARY TEMPLATE CLASS pre FALSE CASE.
template<typename, typename=SVoidType<>>
struct SDetectingMembersHasMemberType final : TypeFunctionFalseType
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS SPECIALIZATION pre TRUE CASE.
// !!!!! TYPE TRAIT testuje ci TYPE [TType] ma PUBLIC TYPE [MY_TYPE].
template<typename TType>
struct SDetectingMembersHasMemberType<TType,SVoidType<typename STypeFunctionRemoveReference<TType>::Type::MY_TYPE>> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------