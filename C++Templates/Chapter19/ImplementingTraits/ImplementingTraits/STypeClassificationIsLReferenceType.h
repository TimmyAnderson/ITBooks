//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STypeFunctionBoolConstant.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PRIMARY TEMPLATE CLASS.
template<typename TType>
struct STypeClassificationIsLReferenceType : public TypeFunctionFalseType
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION CLASS.
template<typename TType>
struct STypeClassificationIsLReferenceType<TType&> : public TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													BASE=TType;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------