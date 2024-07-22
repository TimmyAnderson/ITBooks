//----------------------------------------------------------------------------------------------------------------------
#include "TestExAllocatePool3.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SStructExAllocatePool3 final
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
NTSTATUS TestExAllocatePool3(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	POOL_EXTENDED_PARAMETER										ExtendedParameters;

	RtlZeroMemory(&ExtendedParameters,sizeof(ExtendedParameters));

	// !!! Nastavi sa TYPE EXTENDED PARAMETER na PRIORITY.
	ExtendedParameters.Type=POOL_EXTENDED_PARAMETER_TYPE::PoolExtendedParameterPriority;
	
	// !!! Nastavi sa EXTENDED PARAMETER NEMA byt OPTIONAL.
	ExtendedParameters.Optional=0;

	// !!! Nastavi sa VALUE EXTENDED PARAMETER.
	ExtendedParameters.Priority=EX_POOL_PRIORITY::NormalPoolPriority;

	PVOID														RawBuffer=ExAllocatePool3(POOL_FLAG_NON_PAGED,sizeof(SStructExAllocatePool3),MY_TAG,&ExtendedParameters,1);

	if (RawBuffer!=nullptr)
	{
		SStructExAllocatePool3*									TypedBuffer=reinterpret_cast<SStructExAllocatePool3*>(RawBuffer);

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