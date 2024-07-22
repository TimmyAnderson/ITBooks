//----------------------------------------------------------------------------------------------------------------------
#include "TestExAllocatePool3.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "MyDefines.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CODE NEBOL OTESTOVANY, pretoze sa mi na VIRTUAL MACHINE nepodarilo rozbehat VIRTUALIZATION BASED SECURITY, ktora vyzaduje zmmenu nastavenia WINDOWS.
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SStructSecurePool final
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
PVOID AllocateSecurePoolBuffer(HANDLE SecurePoolHandle, ULONG_PTR Cookie, SIZE_T SecureBufferSize, PVOID SecureBufferContent)
{
	POOL_EXTENDED_PARAMETER										ExtendedParameters;

	RtlZeroMemory(&ExtendedParameters,sizeof(ExtendedParameters));

	POOL_EXTENDED_PARAMS_SECURE_POOL							SecurePoolParams;

	RtlZeroMemory(&SecurePoolParams,sizeof(SecurePoolParams));

	// !!! Nastavi sa EXTENDED PARAMETER TYPE na SECURE POOL.
	ExtendedParameters.Type=POOL_EXTENDED_PARAMETER_TYPE::PoolExtendedParameterSecurePool;
	
	// !!! Nastavi sa EXTENDED PARAMETER NEMA byt OPTIONAL.
	ExtendedParameters.Optional=0;

	// !!! Nastavi sa VALUE EXTENDED PARAMETER.
	ExtendedParameters.SecurePoolParams=&SecurePoolParams;

	// !!!!! Obsahuje BUFFER CONTENT, ktorym sa SECURE BUFFER pri inicializacii naplni.
	SecurePoolParams.Buffer=SecureBufferContent;

	SecurePoolParams.Cookie=Cookie;

	// !!! Nastavi sa, aby BUFFER CONTENT bolo mozne menit volanim FUNCTION [ExSecurePoolUpdate()].
	SecurePoolParams.SecurePoolFlags=(SECURE_POOL_FLAGS_FREEABLE | SECURE_POOL_FLAGS_MODIFIABLE);

	// !!! Pri uvolnovani MEMORY sa nastavuje iba SECURE POOL HANDLE.
	SecurePoolParams.SecurePoolHandle=SecurePoolHandle;

	// !!!!! Obsahuje POINTER na SECURE BUFFER, ktoreho CONTENT bude naplneny obsahom FIELD [SecurePoolParams.Buffer].
    PVOID														SecureBuffer=ExAllocatePool3(POOL_FLAG_NON_PAGED,SecureBufferSize,MY_TAG,&ExtendedParameters,1);

	return(SecureBuffer);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS UpdateSecurePoolBuffer(HANDLE SecurePoolHandle, ULONG_PTR Cookie, PVOID SecureBuffer, SIZE_T SecureBufferSize, PVOID SecureBufferContent)
{
	// !!!!! Kazda zmena SECURE BUFFER sa MUSI robit volanim FUNCTION [ExSecurePoolUpdate()].
    NTSTATUS													Status=ExSecurePoolUpdate(SecurePoolHandle,MY_TAG,SecureBuffer,Cookie,0,SecureBufferSize,SecureBufferContent);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
void FreeSecurePoolBuffer(HANDLE SecurePoolHandle, ULONG_PTR Cookie, PVOID SecureBuffer)
{
	POOL_EXTENDED_PARAMETER										ExtendedParameters;

	RtlZeroMemory(&ExtendedParameters,sizeof(ExtendedParameters));

	POOL_EXTENDED_PARAMS_SECURE_POOL							SecurePoolParams;

	RtlZeroMemory(&SecurePoolParams,sizeof(SecurePoolParams));

	// !!! Nastavi sa EXTENDED PARAMETER TYPE na SECURE POOL.
	ExtendedParameters.Type=POOL_EXTENDED_PARAMETER_TYPE::PoolExtendedParameterSecurePool;
	
	// !!! Nastavi sa EXTENDED PARAMETER NEMA byt OPTIONAL.
	ExtendedParameters.Optional=0;

	// !!! Nastavi sa VALUE EXTENDED PARAMETER.
	ExtendedParameters.SecurePoolParams=&SecurePoolParams;

	// !!!!! Kedze sa BUFFER odstranuje, tak BUFFER CONTENT sa nemeni a FIELD sa nastavi na NULL.
	SecurePoolParams.Buffer=nullptr;

	SecurePoolParams.Cookie=Cookie;

	SecurePoolParams.SecurePoolFlags=0;

	// !!! Pri uvolnovani MEMORY sa nastavuje iba SECURE POOL HANDLE.
	SecurePoolParams.SecurePoolHandle=SecurePoolHandle;

	// !!!!! SECURE POOL BUFFER MUSI by uvolneny volanim FUNCTION [ExFreePool2()].
	ExFreePool2(SecureBuffer,MY_TAG,&ExtendedParameters,1);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestSecurePool(DEVICE_OBJECT* DeviceObject, IRP* Irp, HANDLE SecurePoolHandle)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

#ifdef USE_SECURE_POOL
	const char*													FunctionName=__FUNCTION__;

	constexpr SIZE_T											SecureBufferSize=sizeof(SStructSecurePool);

	// !!! STRUCTURE obsahuje CONTENT pre SECURE BUFFER.
	SStructSecurePool											SecureBufferContent1;

	SecureBufferContent1.Value1=100;
	SecureBufferContent1.Value2=1000000;

	// !!! STRUCTURE obsahuje UPDATED CONTENT pre SECURE BUFFER.
	SStructSecurePool											SecureBufferContent2;

	SecureBufferContent2.Value1=200;
	SecureBufferContent2.Value2=2000000;

	ULONG_PTR													Cookie=0x1234;

	PVOID														RawSecureBuffer=AllocateSecurePoolBuffer(SecurePoolHandle,Cookie,SecureBufferSize,&SecureBufferContent1);

	if (RawSecureBuffer!=nullptr)
	{
		SStructSecurePool*										TypedSecureBuffer=reinterpret_cast<SStructSecurePool*>(RawSecureBuffer);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - SECURE BUFFER - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,TypedSecureBuffer->Value1,TypedSecureBuffer->Value2));

		// !!!!! Kazdy WRITE to SECURE BUFFER MUSI byt vykonany volanim FUNCTION [ExSecurePoolUpdate()].
		Status=UpdateSecurePoolBuffer(SecurePoolHandle,Cookie,RawSecureBuffer,SecureBufferSize,&SecureBufferContent2);

		if (NT_SUCCESS(Status)==true)
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - SECURE BUFFER - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,TypedSecureBuffer->Value1,TypedSecureBuffer->Value2));
		}
		else
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to UPDATE SECURE BUFFER with ERROR CODE [%lX].\n",FunctionName,Status));
		}

		FreeSecurePoolBuffer(SecurePoolHandle,Cookie,RawSecureBuffer);
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to ALLOCATE SECURE BUFFER.\n",FunctionName));
	}
#else
	UNREFERENCED_PARAMETER(SecurePoolHandle);
#endif

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------