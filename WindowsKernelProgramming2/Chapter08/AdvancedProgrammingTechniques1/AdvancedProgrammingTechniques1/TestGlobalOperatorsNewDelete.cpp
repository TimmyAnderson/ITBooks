//----------------------------------------------------------------------------------------------------------------------
#include "TestGlobalOperatorsNewDelete.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "CNoCustomNewDeleteOperators.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void* operator new(size_t Size, POOL_FLAGS Pool, ULONG Tag)
{
	KdPrint(("!!!!! OPERATOR [OPERATOR GLOBAL::new(size_t Size, POOL_TYPE Pool, ULONG Tag)] CALLED !!!\n"));

	void*														Buffer=ExAllocatePool2(Pool,Size,Tag);

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PARAMETER [size_t] je POVINNY, inak sa OPERATOR [OPERATOR delete] NEZAVOLA.
void operator delete(void* Buffer, size_t)
{
	KdPrint(("!!!!! OPERATOR [OPERATOR GLOBAL::delete(void* Buffer)] CALLED !!!\n"));

	ExFreePool(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestGlobalOperatorsNewDelete(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	// !!!!! GLOBAL CUSTOM OPERATOR [OPERATOR new] alokuje MEMORY pomocou FUNCTION [ExAllocatePool2()].
	CNoCustomNewDeleteOperators*								Object=new(POOL_FLAG_NON_PAGED,MY_TAG) CNoCustomNewDeleteOperators(100,1000000);

	if (Object!=nullptr)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,Object->GetValue1(),Object->GetValue2()));

		// !!!!! GLOBAL CUSTOM OPERATOR [OPERATOR delete] uvolnuje MEMORY pomocou FUNCTION [ExFreePool()].
		delete(Object);
		Object=nullptr;
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to ALLOCATE BUFFER.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------