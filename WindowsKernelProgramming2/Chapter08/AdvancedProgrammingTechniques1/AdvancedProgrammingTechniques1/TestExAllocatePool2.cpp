//----------------------------------------------------------------------------------------------------------------------
#include "TestExAllocatePool2.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SStructExAllocatePool2 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		SHORT													Value1;
		LONG													Value2;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestExAllocatePool2(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	PVOID														RawBuffer=ExAllocatePool2(POOL_FLAG_NON_PAGED,sizeof(SStructExAllocatePool2),MY_TAG);

	if (RawBuffer!=nullptr)
	{
		SStructExAllocatePool2*									TypedBuffer=reinterpret_cast<SStructExAllocatePool2*>(RawBuffer);

		TypedBuffer->Value1=100;
		TypedBuffer->Value2=1000000;

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,TypedBuffer->Value1,TypedBuffer->Value2));

		ExFreePoolWithTag(TypedBuffer,MY_TAG);
		RawBuffer=nullptr;
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to ALLOCATE BUFFER.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------