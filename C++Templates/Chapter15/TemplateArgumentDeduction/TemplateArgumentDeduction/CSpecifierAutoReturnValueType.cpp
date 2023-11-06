//----------------------------------------------------------------------------------------------------------------------
#include "CSpecifierAutoReturnValueType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CSpecifierAutoReturnValueType::CSpecifierAutoReturnValueType(double Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CSpecifierAutoReturnValueType::~CSpecifierAutoReturnValueType(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ vykona DEDUCTION RETURN VALUE TYPE.
auto CSpecifierAutoReturnValueType::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------