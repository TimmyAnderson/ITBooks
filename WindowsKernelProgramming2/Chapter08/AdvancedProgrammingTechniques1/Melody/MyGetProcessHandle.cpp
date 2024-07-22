//----------------------------------------------------------------------------------------------------------------------
#include "MyGetProcessHandle.h"
#include "Defines.h"
#include "FunctionsFromWinInternal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
HANDLE MyGetProcessID(ULONG SessionID, const UNICODE_STRING& ProcessName)
{
	const char*													FunctionName=__FUNCTION__;

	HANDLE														UniqueProcessId=nullptr;
	NTSTATUS													Status=STATUS_SUCCESS;

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
			    ExFreePoolWithTag(Buffer,DRIVER_TAG);
				Buffer=nullptr;
			}

		    Buffer=ExAllocatePool2(POOL_FLAG_PAGED,BufferSize,DRIVER_TAG);

			if (Buffer==nullptr)
			{
				KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to ALLOCATE BUFFER.\n",FunctionName));

				Status=STATUS_INSUFFICIENT_RESOURCES;
				break;
			}
		}

		if (AreDataRead==true)
		{
			SSYSTEM_PROCESS_INFORMATION*						TypedBuffer=static_cast<SSYSTEM_PROCESS_INFORMATION*>(Buffer);

			while(true)
			{
                ULONG											ProcessIDAsULong=HandleToULong(TypedBuffer->UniqueProcessId);
				ULONG											LocalSessionID=TypedBuffer->SessionId;
				ULONG											HandleCount=TypedBuffer->HandleCount;
                ULONG											NumberOfThreads=TypedBuffer->NumberOfThreads;
				UNICODE_STRING&									ImageName=TypedBuffer->ImageName;

				if (SessionID==LocalSessionID && RtlEqualUnicodeString(&ProcessName,&ImageName,TRUE)!=FALSE)
				{
					KdPrint(("!!!!!!!!!! ROUTINE [%s] - PID [%lu] SESSION ID [%lu] HANDLES [%lu] THREADS [%lu] IMAGE NAME [%wZ].\n",FunctionName,ProcessIDAsULong,LocalSessionID,HandleCount,NumberOfThreads,ImageName));

					UniqueProcessId=TypedBuffer->UniqueProcessId;
					break;
				}

				if (TypedBuffer->NextEntryOffset==0)
				{
					break;
				}

				TypedBuffer=(reinterpret_cast<SSYSTEM_PROCESS_INFORMATION*>((reinterpret_cast<PUCHAR>(TypedBuffer)+TypedBuffer->NextEntryOffset)));
			}
		}

		if (Buffer!=nullptr)
		{
		    ExFreePoolWithTag(Buffer,DRIVER_TAG);
			Buffer=nullptr;
		}
	}
	while(false);

	return(UniqueProcessId);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Vykonava konverziu PROCESS ID na PROCESS HANDLE.
HANDLE MyGetProcessHandle(HANDLE ProcessID)
{
	const char*													FunctionName=__FUNCTION__;

	OBJECT_ATTRIBUTES											ObjectAttributes;
	HANDLE														ProcessHandle=nullptr;

	InitializeObjectAttributes(&ObjectAttributes,nullptr,0,nullptr,nullptr);

	CLIENT_ID													ClientID;

	ClientID.UniqueProcess=ProcessID;
	ClientID.UniqueThread=nullptr;

	NTSTATUS													Status=ZwOpenProcess(&ProcessHandle,PROCESS_ALL_ACCESS,&ObjectAttributes,&ClientID);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - FAILED to OPEN PROCESS with ERROR CODE [%lX].\n",FunctionName,Status));
	}

	return(ProcessHandle);
}
//----------------------------------------------------------------------------------------------------------------------