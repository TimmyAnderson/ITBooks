//----------------------------------------------------------------------------------------------------------------------
#include "CPointerToMember.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CPointerToMember::CPointerToMember(int Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CPointerToMember::~CPointerToMember(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CPointerToMember::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------