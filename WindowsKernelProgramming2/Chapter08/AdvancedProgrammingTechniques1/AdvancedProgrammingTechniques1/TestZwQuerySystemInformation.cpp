//----------------------------------------------------------------------------------------------------------------------
#include "TestZwQuerySystemInformation.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "FunctionsFromWinInternal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestZwQuerySystemInformation(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	do
	{
		bool													AreDataRead=false;
		PVOID													Buffer=nullptr;
		ULONG													BufferSize=0;

		// !!!!! Robi sa CYKLUS, pretoze medzi 1. a 2. VOLANIM FUNCTION [NtQuerySystemInformation()] mohlo dojst k vzniku dalsich PROCESSES a tak BUFFER uz nemusi postacovat.
		while(true)
		{
			// !!!!! MUSI sa pouzit FUNCTION [ZwQuerySystemInformation()], a NIE FUNCTION [NtQuerySystemInformation()], pretoze FUNCTION [NtQuerySystemInformation()] robi kontrolu INPUT PARAMETERS a vrati ERROR, ak je PARAMETER [Buffer] nastaveny na VALUE [nullptr], pricom nenastavi PARAMETER [BufferSize].
			Status=ZwQuerySystemInformation(ESYSTEM_INFORMATION_CLASS::SystemProcessInformation,Buffer,BufferSize,&BufferSize);

			if (NT_SUCCESS(Status)!=false)
			{
				AreDataRead=true;
				break;
			}
			else
			{
				if (Status!=STATUS_INFO_LENGTH_MISMATCH)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to GET SYSTEM PROCESS INFORMATION with ERROR CODE [%lX].\n",FunctionName,Status));
					break;
				}
			}

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - BUFFER SIZE [%lu].\n",FunctionName,BufferSize));

			if (Buffer!=nullptr)
			{
			    ExFreePoolWithTag(Buffer,MY_TAG);
				Buffer=nullptr;
			}

		    Buffer=ExAllocatePool2(POOL_FLAG_PAGED,BufferSize,MY_TAG);

			if (Buffer==nullptr)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to ALLOCATE BUFFER.\n",FunctionName));

				Status=STATUS_INSUFFICIENT_RESOURCES;
				break;
			}
		}

		if (AreDataRead==true)
		{
	        ULONG												TotalProcesses=0;
			SSYSTEM_PROCESS_INFORMATION*						TypedBuffer=static_cast<SSYSTEM_PROCESS_INFORMATION*>(Buffer);

			while(true)
			{
                ULONG											ProcessIDAsULong=HandleToULong(TypedBuffer->UniqueProcessId);
				ULONG											SessionID=TypedBuffer->SessionId;
				ULONG											HandleCount=TypedBuffer->HandleCount;
                ULONG											NumberOfThreads=TypedBuffer->NumberOfThreads;
				UNICODE_STRING&									ImageName=TypedBuffer->ImageName;

				KdPrint(("!!!!!!!!!! ROUTINE [%s] - PID [%lu] SESSION ID [%lu] HANDLES [%lu] THREADS [%lu] IMAGE NAME [%wZ].\n",FunctionName,ProcessIDAsULong,SessionID,HandleCount,NumberOfThreads,ImageName));

				++TotalProcesses;

				if (TypedBuffer->NextEntryOffset==0)
				{
					break;
				}

				TypedBuffer=(reinterpret_cast<SSYSTEM_PROCESS_INFORMATION*>((reinterpret_cast<PUCHAR>(TypedBuffer)+TypedBuffer->NextEntryOffset)));
			}

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - TOTAL PROCESSES [%lu].\n",FunctionName,TotalProcesses));
		}

		if (Buffer!=nullptr)
		{
		    ExFreePoolWithTag(Buffer,MY_TAG);
			Buffer=nullptr;
		}
	}
	while(false);

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------