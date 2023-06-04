//----------------------------------------------------------------------------------------------------------------------
#include "CClassWithOperatorLowerAndMultipleException.h"
//----------------------------------------------------------------------------------------------------------------------
CClassWithOperatorLowerAndMultipleException::CClassWithOperatorLowerAndMultipleException(void)
	: MValue()
{
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithOperatorLowerAndMultipleException::CClassWithOperatorLowerAndMultipleException(int Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CClassWithOperatorLowerAndMultipleException::~CClassWithOperatorLowerAndMultipleException(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CClassWithOperatorLowerAndMultipleException::operator<(const CClassWithOperatorLowerAndMultipleException& Other) const
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
CClassWithOperatorLowerAndMultipleException& CClassWithOperatorLowerAndMultipleException::operator*(const CClassWithOperatorLowerAndMultipleException& Other)
{
	MValue*=Other.MValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CClassWithOperatorLowerAndMultipleException::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------