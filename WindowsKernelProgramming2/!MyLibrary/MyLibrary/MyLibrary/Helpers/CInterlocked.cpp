//----------------------------------------------------------------------------------------------------------------------
#include "CInterlocked.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CInterlocked<LONG64>::CInterlocked(void)
{
	SetValue(0);
}
//----------------------------------------------------------------------------------------------------------------------
CInterlocked<LONG64>::CInterlocked(LONG64 Variable)
{
	SetValue(Variable);
}
//----------------------------------------------------------------------------------------------------------------------
CInterlocked<LONG64>::~CInterlocked(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------