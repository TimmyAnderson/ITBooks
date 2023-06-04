//----------------------------------------------------------------------------------------------------------------------
#include "CClassWithOperatorLowerAndMultiple.h"
//----------------------------------------------------------------------------------------------------------------------
CClassWithOperatorLowerAndMultiple::CClassWithOperatorLowerAndMultiple(void)
	: MValue()
{
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithOperatorLowerAndMultiple::CClassWithOperatorLowerAndMultiple(int Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithOperatorLowerAndMultiple::~CClassWithOperatorLowerAndMultiple(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CClassWithOperatorLowerAndMultiple::operator<(const CClassWithOperatorLowerAndMultiple& Other) const noexcept
{
	if (MValue<Other.MValue)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithOperatorLowerAndMultiple& CClassWithOperatorLowerAndMultiple::operator*(const CClassWithOperatorLowerAndMultiple& Other) noexcept
{
	MValue*=Other.MValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CClassWithOperatorLowerAndMultiple::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------