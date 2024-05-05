//----------------------------------------------------------------------------------------------------------------------
#include "TestsMemoryAllocation.h"
#include <wdm.h>
#include "MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestsMemoryAllocation1(void)
{
	const char*													FunctionName=__FUNCTION__;
	constexpr SIZE_T											MY_BUFFER_SIZE=200;

	// !!! Alokuje sa MEMORY BUFFER, ktora vdaka pouzitiu FLAG [POOL_FLAG_UNINITIALIZED] bude UNINITIALIZED.
	PCHAR														Buffer=(PCHAR)ExAllocatePool2(POOL_FLAG_PAGED | POOL_FLAG_UNINITIALIZED,MY_BUFFER_SIZE,MY_TAG);

	if (Buffer==nullptr)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE BUFFER !!!\n",FunctionName));
		return;
	}

	CHAR														Char0=Buffer[0];
	CHAR														Char99=Buffer[99];
	CHAR														Char199=Buffer[199];

	KdPrint(("!!!!! FUNCTION [%s] CHAR_0 [%hhu] CHAR_99 [%hhu] CHAR_199 [%hhu] BUFFER [%p] !!!\n",FunctionName,Char0,Char99,Char199,Buffer));

	// !!! Uvolni sa MEMORY BUFFER.
	ExFreePoolWithTag(Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestsMemoryAllocation2(void)
{
	const char*													FunctionName=__FUNCTION__;
	constexpr SIZE_T											MY_BUFFER_SIZE=200;

	// !!! Alokuje sa MEMORY BUFFER a ZAROVEN sa nastavi MEMORY na VALUES [0].
	PCHAR														Buffer=(PCHAR)ExAllocatePoolQuotaZero(POOL_TYPE::PagedPool,MY_BUFFER_SIZE,MY_TAG);

	if (Buffer==nullptr)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE BUFFER !!!\n",FunctionName));
		return;
	}

	CHAR														Char0=Buffer[0];
	CHAR														Char99=Buffer[99];
	CHAR														Char199=Buffer[199];

	KdPrint(("!!!!! FUNCTION [%s] CHAR_0 [%hhu] CHAR_99 [%hhu] CHAR_199 [%hhu] BUFFER [%p] !!!\n",FunctionName,Char0,Char99,Char199,Buffer));

	// !!! Uvolni sa MEMORY BUFFER.
	ExFreePoolWithTag(Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------