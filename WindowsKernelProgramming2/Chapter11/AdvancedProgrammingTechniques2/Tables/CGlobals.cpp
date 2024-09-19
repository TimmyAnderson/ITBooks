//----------------------------------------------------------------------------------------------------------------------
#include "CGlobals.h"
#include "Helpers/MyKernelHelpers.h"
#include "SProcessData.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
RTL_GENERIC_COMPARE_RESULTS CGlobals::CompareProcesses(PRTL_GENERIC_TABLE, PVOID First, PVOID Second)
{
	SProcessData*												Value1=(SProcessData*)First;
	SProcessData*												Value2=(SProcessData*)Second;

	if (Value1->MID<Value2->MID)
	{
		return(GenericLessThan);
	}
	else if (Value1->MID>Value2->MID)
	{
		return(GenericGreaterThan);
	}
	else
	{
		return(GenericEqual);
	}
}
//----------------------------------------------------------------------------------------------------------------------
PVOID CGlobals::AllocateProcess(PRTL_GENERIC_TABLE, CLONG Bytes)
{
	PVOID														Buffer=ExAllocatePool2(POOL_FLAG_PAGED | POOL_FLAG_UNINITIALIZED,Bytes,MY_TAG);

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
void CGlobals::FreeProcess(PRTL_GENERIC_TABLE, PVOID Buffer)
{
	ExFreePoolWithTag(Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CGlobals::Init(void)
{
	MLock.Init();

	RtlInitializeGenericTable(&MProcessTable,CompareProcesses,AllocateProcess,FreeProcess,nullptr);
}
//----------------------------------------------------------------------------------------------------------------------