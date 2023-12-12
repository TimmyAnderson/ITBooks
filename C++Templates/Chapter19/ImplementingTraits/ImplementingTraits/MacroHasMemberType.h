//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "SVoidType.h"
#include "STypeFunctionBoolConstant.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MACRO generuje TYPE TRAIT, ktory kontroluje ci dany TYPE ma MEMBER TYPE [MemType].
#define DEFINE_HAS_TYPE(MemType) \
  template<typename, typename=SVoidType<>> \
  struct MacroHasMemberType_##MemType : public TypeFunctionFalseType \
  { \
  }; \
  template<typename TType> \
  struct MacroHasMemberType_##MemType<TType, SVoidType<typename TType::MemType>> : public TypeFunctionTrueType \
  { \
  }
//----------------------------------------------------------------------------------------------------------------------