//----------------------------------------------------------------------------------------------------------------------
#include "CInstantiationSafeTemplatesTypesBoolConvertibleExplicit.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInstantiationSafeTemplatesTypesBoolConvertibleExplicit::CInstantiationSafeTemplatesTypesBoolConvertibleExplicit(bool Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CInstantiationSafeTemplatesTypesBoolConvertibleExplicit::~CInstantiationSafeTemplatesTypesBoolConvertibleExplicit(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInstantiationSafeTemplatesTypesBoolConvertibleExplicit::operator bool(void) const
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CInstantiationSafeTemplatesTypesBoolConvertibleExplicit::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------