//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "SVoidType.h"
#include "STypeFunctionBoolConstant.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MACRO generuje TYPE TRAIT, ktory kontroluje ci dany TYPE ma MEMBER NON-TYPE [Member].
// !!!!! MACRO NIE JE mozne pouzit na detekciu OVERLOADED METHODS.
#define DEFINE_HAS_MEMBER(Member) \
  template<typename, typename=SVoidType<>> \
  struct MacroHasMemberNonType_##Member : public TypeFunctionFalseType \
  { \
  }; \
  template<typename TType> \
  struct MacroHasMemberNonType_##Member<TType, SVoidType<decltype(&TType::Member)>> : public TypeFunctionTrueType \
  { \
  }
//----------------------------------------------------------------------------------------------------------------------