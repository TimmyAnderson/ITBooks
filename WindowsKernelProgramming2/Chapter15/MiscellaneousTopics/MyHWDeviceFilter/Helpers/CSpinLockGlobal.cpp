//----------------------------------------------------------------------------------------------------------------------
#include "CSpinLockGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CSpinLockGlobal::Init(void)
{
	KeInitializeSpinLock(&MLock);
}
//----------------------------------------------------------------------------------------------------------------------
void CSpinLockGlobal::Lock(void)
{
	KeAcquireSpinLock(&MLock,&MOldIrql);
}
//----------------------------------------------------------------------------------------------------------------------
void CSpinLockGlobal::Unlock(void)
{
	KeReleaseSpinLock(&MLock,MOldIrql);
}
//----------------------------------------------------------------------------------------------------------------------