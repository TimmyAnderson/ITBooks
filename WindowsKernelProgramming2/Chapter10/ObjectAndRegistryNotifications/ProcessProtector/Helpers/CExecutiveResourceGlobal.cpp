//----------------------------------------------------------------------------------------------------------------------
#include "CExecutiveResourceGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CExecutiveResourceGlobal::Init(void)
{
	ExInitializeResourceLite(&MResource);
}
//----------------------------------------------------------------------------------------------------------------------
void CExecutiveResourceGlobal::Delete(void)
{
	ExDeleteResourceLite(&MResource);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CExecutiveResourceGlobal::Lock(void)
{
	MIsInCriticalRegion=KeAreApcsDisabled();

	if(MIsInCriticalRegion==true)
	{
		ExAcquireResourceExclusiveLite(&MResource,TRUE);
	}
	else
	{
		ExEnterCriticalRegionAndAcquireResourceExclusive(&MResource);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void CExecutiveResourceGlobal::Unlock(void)
{
	if (MIsInCriticalRegion==true)
	{
		ExReleaseResourceLite(&MResource);
	}
	else
	{
		ExReleaseResourceAndLeaveCriticalRegion(&MResource);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CExecutiveResourceGlobal::LockShared(void)
{
	MIsInCriticalRegion=KeAreApcsDisabled();

	if (MIsInCriticalRegion==true)
	{
		ExAcquireResourceSharedLite(&MResource,TRUE);
	}
	else
	{
		ExEnterCriticalRegionAndAcquireResourceShared(&MResource);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void CExecutiveResourceGlobal::UnlockShared(void)
{
	Unlock();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
ULONG CExecutiveResourceGlobal::GetSharedWaiterCount(void)
{
	ULONG													Count=ExGetSharedWaiterCount(&MResource);

	return(Count);
}
//----------------------------------------------------------------------------------------------------------------------
ULONG CExecutiveResourceGlobal::GetExclusiveWaiterCount(void)
{
	ULONG													Count=ExGetExclusiveWaiterCount(&MResource);

	return(Count);
}
//----------------------------------------------------------------------------------------------------------------------