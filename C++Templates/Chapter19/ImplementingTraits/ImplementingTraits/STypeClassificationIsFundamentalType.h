//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STypeFunctionBoolConstant.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PRIMARY TEMPLATE CLASS.
template<typename TType>
struct STypeClassificationIsFundamentalType final : public TypeFunctionFalseType
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MACRO na vytvorenie TEMPLATE SPECIALIZATION CLASS.
#define MAKE_FUNDAMENTAL_TYPE(TYPE) \
template<> struct STypeClassificationIsFundamentalType<TYPE> final : public TypeFunctionTrueType { \
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
MAKE_FUNDAMENTAL_TYPE(void)
MAKE_FUNDAMENTAL_TYPE(bool)
MAKE_FUNDAMENTAL_TYPE(char)
MAKE_FUNDAMENTAL_TYPE(signed char)
MAKE_FUNDAMENTAL_TYPE(unsigned char)
MAKE_FUNDAMENTAL_TYPE(wchar_t)
MAKE_FUNDAMENTAL_TYPE(char16_t)
MAKE_FUNDAMENTAL_TYPE(char32_t)
MAKE_FUNDAMENTAL_TYPE(signed short)
MAKE_FUNDAMENTAL_TYPE(unsigned short)
MAKE_FUNDAMENTAL_TYPE(signed int)
MAKE_FUNDAMENTAL_TYPE(unsigned int)
MAKE_FUNDAMENTAL_TYPE(signed long)
MAKE_FUNDAMENTAL_TYPE(unsigned long)
MAKE_FUNDAMENTAL_TYPE(signed long long)
MAKE_FUNDAMENTAL_TYPE(unsigned long long)
MAKE_FUNDAMENTAL_TYPE(float)
MAKE_FUNDAMENTAL_TYPE(double)
MAKE_FUNDAMENTAL_TYPE(long double)
MAKE_FUNDAMENTAL_TYPE(std::nullptr_t)
//----------------------------------------------------------------------------------------------------------------------
#undef MAKE_FUNDAMENTAL_TYPE
//----------------------------------------------------------------------------------------------------------------------