//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STypeFunctionBoolConstant.h"
#include "SVoidType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename,typename=SVoidType<>>
struct SSFINAETraitIsDefaultConstructibleSpecialization final : public TypeFunctionFalseType
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Ak TYPE [TType] NEMA DEFAULT CONSTRUCTOR, tak cela TEMPLATE CLASS SPECIALIZATION je odstranena na zaklade pravidla SFINAE.
template<typename TType>
struct SSFINAETraitIsDefaultConstructibleSpecialization<TType,SVoidType<decltype(TType())>> final : public TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------