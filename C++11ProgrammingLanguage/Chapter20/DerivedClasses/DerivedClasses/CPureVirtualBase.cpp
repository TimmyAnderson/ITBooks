//-----------------------------------------------------------------------------
#include "CPureVirtualBase.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! GCC podporuje METHOD BODY pre PURE VIRTUAL METHODS IBA v .CPP FILES.
void CPureVirtualBase::PureVirtualMethodWithDefinition(void) const
{
	std::wcout << L"METHOD CPureVirtualBase::PureVirtualMethodWithDefinition() CALLED !" << std::endl;
}
//-----------------------------------------------------------------------------