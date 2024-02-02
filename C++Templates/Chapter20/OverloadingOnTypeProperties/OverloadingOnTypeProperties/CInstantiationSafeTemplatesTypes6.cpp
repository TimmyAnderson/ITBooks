//----------------------------------------------------------------------------------------------------------------------
#include "CInstantiationSafeTemplatesTypes6.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInstantiationSafeTemplatesTypes6::CInstantiationSafeTemplatesTypes6(int Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CInstantiationSafeTemplatesTypes6::~CInstantiationSafeTemplatesTypes6(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CInstantiationSafeTemplatesTypes6::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInstantiationSafeTemplatesTypesNotBoolConvertible operator<(const CInstantiationSafeTemplatesTypes6& Value1, const CInstantiationSafeTemplatesTypes6& Value2)
{
	if (Value1.GetValue()<Value2.GetValue())
	{
		CInstantiationSafeTemplatesTypesNotBoolConvertible		Value(true);

		return(Value);
	}
	else
	{
		CInstantiationSafeTemplatesTypesNotBoolConvertible		Value(false);

		return(Value);
	}
}
//----------------------------------------------------------------------------------------------------------------------