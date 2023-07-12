//-----------------------------------------------------------------------------
#include "CClass.h"
//-----------------------------------------------------------------------------
CClass::CClass(int Field)
	: MField(Field)
{
}

CClass::~CClass(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int CClass::GetField(void) const noexcept
{
	return(MField);
}
//-----------------------------------------------------------------------------
void CClass::SetField(int Value) noexcept
{
	MField=Value;
}
//-----------------------------------------------------------------------------