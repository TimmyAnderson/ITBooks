//----------------------------------------------------------------------------------------------------------------------
#include "TestSpecificTypeOperatorsNewDelete.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "CCustomNewDeleteOperators1.h"
#include "CCustomNewDeleteOperators2.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestSpecificTypeOperatorsNewDelete(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	// !!! Explicitne sa alokuje MEMORY.
	void*														Buffer=ExAllocatePool2(POOL_FLAG_NON_PAGED,sizeof(CCustomNewDeleteOperators1),MY_TAG);

	// !!!!! CUSTOM OPERATOR [OPERATOR new] NEALOKUJE MEMORY.
	CCustomNewDeleteOperators1*									Object1=new(Buffer) CCustomNewDeleteOperators1(100,1000000);

	if (Object1!=nullptr)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 1 - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,Object1->GetValue1(),Object1->GetValue2()));

		// !!!!! CUSTOM OPERATOR [OPERATOR delete] NEUVOLNUJE MEMORY.
		delete(Object1);
		Object1=nullptr;

		ExFreePoolWithTag(Buffer,MY_TAG);
		Buffer=nullptr;
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 1 - FAILED to ALLOCATE BUFFER.\n",FunctionName));
	}

	// !!!!! CUSTOM OPERATOR [OPERATOR new] alokuje MEMORY pomocou FUNCTION [ExAllocatePool2()].
	CCustomNewDeleteOperators2*									Object2=new(POOL_FLAG_NON_PAGED,MY_TAG) CCustomNewDeleteOperators2(100,1000000);

	if (Object2!=nullptr)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 2 - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,Object2->GetValue1(),Object2->GetValue2()));

		// !!!!! CUSTOM OPERATOR [OPERATOR delete] uvolnuje MEMORY pomocou FUNCTION [ExFreePool()].
		delete(Object2);
		Object2=nullptr;
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - OBJECT 2 - FAILED to ALLOCATE BUFFER.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------