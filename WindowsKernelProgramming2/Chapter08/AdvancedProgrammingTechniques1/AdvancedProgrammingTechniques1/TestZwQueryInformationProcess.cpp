//----------------------------------------------------------------------------------------------------------------------
#include "TestZwQueryInformationProcess.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "FunctionsFromWinInternal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestZwQueryInformationProcess(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;
	PVOID														Buffer=nullptr;

	do
	{
		ULONG													BufferSize=0;
		HANDLE													ProcessHandle=NtCurrentProcess();

		Status=ZwQueryInformationProcess(ProcessHandle,EPROCESSINFOCLASS::ProcessBasicInformation,nullptr,0,&BufferSize);

		if (NT_SUCCESS(Status)==false)
		{
			if (Status!=STATUS_INFO_LENGTH_MISMATCH)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to GET BUFFER SIZE with ERROR CODE [%lX].\n",FunctionName,Status));
				break;
			}
		}

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - BUFFER SIZE [%lu].\n",FunctionName,BufferSize));

		// !!!!! Z neznameho dovodu FUNCTION [ZwQueryInformationProcess()] NEVRACIA POCET BYTES v PARAMETER [BufferSize].
		if (BufferSize==0)
		{
			BufferSize=sizeof(SPROCESS_BASIC_INFORMATION);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - HARD SET - BUFFER SIZE [%lu].\n",FunctionName,BufferSize));
		}

	    Buffer=ExAllocatePool2(POOL_FLAG_PAGED,BufferSize,MY_TAG);

		if (Buffer==nullptr)
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to ALLOCATE BUFFER.\n",FunctionName));

			Status=STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		Status=ZwQueryInformationProcess(ProcessHandle,EPROCESSINFOCLASS::ProcessBasicInformation,Buffer,BufferSize,nullptr);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to GET PROCESS INFORMATION with ERROR CODE [%lX].\n",FunctionName,Status));
			break;
		}

		SPROCESS_BASIC_INFORMATION*								TypedBuffer=static_cast<SPROCESS_BASIC_INFORMATION*>(Buffer);

		ULONG_PTR												ProcessID=TypedBuffer->UniqueProcessId;
		KPRIORITY												BasePriority=TypedBuffer->BasePriority;
		NTSTATUS												ExitStatus=TypedBuffer->ExitStatus;

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - PID [%I64u] BASE PRIORITY [%ld] EXIT STATUS [%lX].\n",FunctionName,ProcessID,BasePriority,ExitStatus));
	}
	while(false);

	if (Buffer!=nullptr)
	{
		ExFreePoolWithTag(Buffer,MY_TAG);
		Buffer=nullptr;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------