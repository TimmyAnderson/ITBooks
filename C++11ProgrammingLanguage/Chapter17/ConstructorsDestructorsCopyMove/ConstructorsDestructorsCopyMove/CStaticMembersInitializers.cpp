//-----------------------------------------------------------------------------
#include "CStaticMembersInitializers.h"
//-----------------------------------------------------------------------------
// STATIC NON-INTEGER CONST VARIABLES NIE je mozne inicializovat pri DEFINICII FIELDS.
const double													CStaticMembersInitializers::MValue3=33.44;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int CStaticMembersInitializers::GetValue1(void) noexcept
{
	return(MValue1);
}
//-----------------------------------------------------------------------------
EEnum CStaticMembersInitializers::GetValue2(void) noexcept
{
	return(MValue2);
}
//-----------------------------------------------------------------------------
double CStaticMembersInitializers::GetValue3(void) noexcept
{
	return(MValue3);
}
//-----------------------------------------------------------------------------