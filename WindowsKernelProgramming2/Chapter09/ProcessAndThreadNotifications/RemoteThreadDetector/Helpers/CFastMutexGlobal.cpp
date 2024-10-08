//----------------------------------------------------------------------------------------------------------------------
#include "CFastMutexGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFastMutexGlobal::Init(void)
{
	ExInitializeFastMutex(&MMutex);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFastMutexGlobal::Lock(void)
{
	ExAcquireFastMutex(&MMutex);
}
//----------------------------------------------------------------------------------------------------------------------
void CFastMutexGlobal::Unlock(void)
{
	ExReleaseFastMutex(&MMutex);
}
//----------------------------------------------------------------------------------------------------------------------