//----------------------------------------------------------------------------------------------------------------------
#include "CFastMutex.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFastMutex::CFastMutex(void)
	: MMutex()
{
	ExInitializeFastMutex(&MMutex);
}
//----------------------------------------------------------------------------------------------------------------------
CFastMutex::~CFastMutex(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFastMutex::Lock(void)
{
	ExAcquireFastMutex(&MMutex);
}
//----------------------------------------------------------------------------------------------------------------------
void CFastMutex::Unlock(void)
{
	ExReleaseFastMutex(&MMutex);
}
//----------------------------------------------------------------------------------------------------------------------