//------------------------------------------------------------------------------------------------------
#include "Lock.h"
//------------------------------------------------------------------------------------------------------
CLock::CLock(CCriticalSectionWrapper& CriticalSectionWrapper)
	: MCriticalSectionWrapper(CriticalSectionWrapper)
{
	EnterCriticalSection(MCriticalSectionWrapper.GetCriticalSectionPointer());
}
//------------------------------------------------------------------------------------------------------
CLock::~CLock(void)
{
	LeaveCriticalSection(MCriticalSectionWrapper.GetCriticalSectionPointer());
}
//------------------------------------------------------------------------------------------------------