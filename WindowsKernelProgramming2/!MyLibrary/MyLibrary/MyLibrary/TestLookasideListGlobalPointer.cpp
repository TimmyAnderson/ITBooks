//----------------------------------------------------------------------------------------------------------------------
#include "TestLookasideListGlobalPointer.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CLookasideListGlobal.h"
#include "CLookasideEntry.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER ide spustit na WINDOWS 10, IBA ak je CONFIGURATION [Configuration Properties->Driver Settings->General->_NT_TARGET_VERSION] nastaveny na VALUE [Windows 10.0.22000], alebo menej. Vyssia VALUE sposobi, ze DRIVER na WINDOWS 10 sa NEBUDE dat SPUSTIT.
// !!!!! Toto nastavenie sa da je ulozene v .CSPROJ ako VALUE [<_NT_TARGET_VERSION>0xA00000B</_NT_TARGET_VERSION>].
#if (NTDDI_VERSION <= NTDDI_WIN10_CO)
#define USE_LOOKSIDE_LISTS
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CLookasideListGlobal<CLookasideEntry>*							LookasideListGlobalPointer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestLookasideListGlobalPointer(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

#ifdef USE_LOOKSIDE_LISTS	
	LookasideListGlobalPointer=new (EPoolFlags::E_POOL_FLAG_PAGED) CLookasideListGlobal<CLookasideEntry>();

	if (LookasideListGlobalPointer!=nullptr)
	{
		Status=LookasideListGlobalPointer->Init(POOL_TYPE::PagedPool,MY_TAG);

		if (NT_SUCCESS(Status)!=false)
		{
			const char*												FunctionName=__FUNCTION__;

			// !!! Alokuje sa MEMORY BLOCK z LOOKASIDE LIST.
			CLookasideEntry*										Object1=static_cast<CLookasideEntry*>(LookasideListGlobalPointer->Alloc());
		
			if (Object1!=nullptr)
			{
				Object1->SetValue1(100);
				Object1->SetValue2(1000000);

				KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 1 - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,Object1->GetValue1(),Object1->GetValue2()));

				// !!! Alokuje sa MEMORY BLOCK z LOOKASIDE LIST.
				CLookasideEntry*									Object2=static_cast<CLookasideEntry*>(LookasideListGlobalPointer->Alloc());

				if (Object2!=nullptr)
				{
					Object2->SetValue1(200);
					Object2->SetValue2(2000000);

					KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 2 - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,Object2->GetValue1(),Object2->GetValue2()));

					// !!! Uvolni MEMORY BLOCK v LOOKASIDE LIST.
					LookasideListGlobalPointer->Free(Object2);
				}
				else
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 2 - FAILED to ALLOCATE BUFFER.\n",FunctionName));
				}

				// !!! Uvolni MEMORY BLOCK v LOOKASIDE LIST.
				LookasideListGlobalPointer->Free(Object1);
			}
			else
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 1 - FAILED to ALLOCATE BUFFER.\n",FunctionName));
			}

			LookasideListGlobalPointer->Delete();
		}
		else
		{
			KdPrint(("!!!!! LOOKASIDE INITIALIZATION FAILED with ERROR CODE [%lX] !!!\n",Status));
		}
	}
	else
	{
		KdPrint(("!!!!! LOOKASIDE ALLOCATION FAILED !!!\n"));
	}
#endif

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------