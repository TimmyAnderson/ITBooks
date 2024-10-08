//----------------------------------------------------------------------------------------------------------------------
#include "CMutexGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CMutexGlobal::Init(void)
{
	KeInitializeMutex(&MMutex,0);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CMutexGlobal::Lock(void)
{
	KeWaitForSingleObject(&MMutex,KWAIT_REASON::Executive,MODE::KernelMode,FALSE,nullptr);
}
//----------------------------------------------------------------------------------------------------------------------
void CMutexGlobal::Unlock(void)
{
	KeReleaseMutex(&MMutex,FALSE);
}
//----------------------------------------------------------------------------------------------------------------------