//----------------------------------------------------------------------------------------------------------------------
#include "TestNewLookasideList.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "CLookasideEntry.h"
#include "MyDefines.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestNewLookasideList(DEVICE_OBJECT* DeviceObject, IRP* Irp, LOOKASIDE_LIST_EX* Lookaside)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

#ifdef USE_LOOKSIDE_LISTS
	const char*													FunctionName=__FUNCTION__;

	// !!! Alokuje sa MEMORY BLOCK z LOOKASIDE LIST.
	CLookasideEntry*											Object1=static_cast<CLookasideEntry*>(ExAllocateFromLookasideListEx(Lookaside));

	if (Object1!=nullptr)
	{
		Object1->SetValue1(100);
		Object1->SetValue2(1000000);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 1 - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,Object1->GetValue1(),Object1->GetValue2()));

		// !!! Alokuje sa MEMORY BLOCK z LOOKASIDE LIST.
		CLookasideEntry*										Object2=static_cast<CLookasideEntry*>(ExAllocateFromLookasideListEx(Lookaside));

		if (Object2!=nullptr)
		{
			Object2->SetValue1(200);
			Object2->SetValue2(2000000);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 2 - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,Object2->GetValue1(),Object2->GetValue2()));

			// !!! Uvolni MEMORY BLOCK v LOOKASIDE LIST.
			ExFreeToLookasideListEx(Lookaside,Object2);
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 2 - FAILED to ALLOCATE BUFFER.\n",FunctionName));
		}

		// !!! Uvolni MEMORY BLOCK v LOOKASIDE LIST.
		ExFreeToLookasideListEx(Lookaside,Object1);
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 1 - FAILED to ALLOCATE BUFFER.\n",FunctionName));
	}
#else
	UNREFERENCED_PARAMETER(Lookaside);
#endif

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------