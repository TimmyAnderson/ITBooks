//----------------------------------------------------------------------------------------------------------------------
#include "CNoDefaultConstructor.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CNoDefaultConstructor::CNoDefaultConstructor(int Value)
	: MField(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CNoDefaultConstructor::~CNoDefaultConstructor(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CNoDefaultConstructor::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
std::wostream& operator<<(std::wostream& Stream, const CNoDefaultConstructor& Value)
{
	Stream << Value.MField;

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------