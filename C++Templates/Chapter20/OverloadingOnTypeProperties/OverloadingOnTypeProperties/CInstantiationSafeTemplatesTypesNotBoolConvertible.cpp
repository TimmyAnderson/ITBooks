//----------------------------------------------------------------------------------------------------------------------
#include "CInstantiationSafeTemplatesTypesNotBoolConvertible.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInstantiationSafeTemplatesTypesNotBoolConvertible::CInstantiationSafeTemplatesTypesNotBoolConvertible(bool Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CInstantiationSafeTemplatesTypesNotBoolConvertible::~CInstantiationSafeTemplatesTypesNotBoolConvertible(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CInstantiationSafeTemplatesTypesNotBoolConvertible::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------