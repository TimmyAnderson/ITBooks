//----------------------------------------------------------------------------------------------------------------------
#include "TestsReturnValues.h"
#include <wdm.h>
#include <ntstatus.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS FunctionReturnValues1(void)
{
	// !!!!! Je to NON-ERROR STATE.
	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
void TestsReturnValues1(void)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Result=FunctionReturnValues1();

	if (NT_SUCCESS(Result)==true)
	{
		KdPrint(("!!!!! FUNCTION [%s] SUCCEEDED with CODE [%lX] !!!\n",FunctionName,Result));
	}
	else
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED with ERROR CODE [%lX] !!!\n",FunctionName,Result));
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS FunctionReturnValues2(void)
{
	// !!!!! Je to NON-ERROR STATE.
	return(STATUS_SOME_NOT_MAPPED);
}
//----------------------------------------------------------------------------------------------------------------------
void TestsReturnValues2(void)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Result=FunctionReturnValues2();

	if (NT_SUCCESS(Result)==true)
	{
		KdPrint(("!!!!! FUNCTION [%s] SUCCEEDED with CODE [%lX] !!!\n",FunctionName,Result));
	}
	else
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED with ERROR CODE [%lX] !!!\n",FunctionName,Result));
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS FunctionReturnValues3(void)
{
	// !!!!! Je to ERROR STATE.
	return(STATUS_SPACES_REPAIR_IN_PROGRESS);
}
//----------------------------------------------------------------------------------------------------------------------
void TestsReturnValues3(void)
{
	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Result=FunctionReturnValues3();

	if (NT_SUCCESS(Result)==true)
	{
		KdPrint(("!!!!! FUNCTION [%s] SUCCEEDED with CODE [%lX] !!!\n",FunctionName,Result));
	}
	else
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED with ERROR CODE [%lX] !!!\n",FunctionName,Result));
	}
}
//----------------------------------------------------------------------------------------------------------------------