//----------------------------------------------------------------------------------------------------------------------
#include "CValue.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CValue::CValue(int Value)
	: MField(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CValue::~CValue(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CValue::GetValue(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------