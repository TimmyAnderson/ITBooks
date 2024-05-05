//----------------------------------------------------------------------------------------------------------------------
#include "TestObjectAttributes.h"
#include "MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestsObjectAttributes1(ULONG ProcessID)
{
	const char*													FunctionName=__FUNCTION__;

	HANDLE														ProcessHandle;
	ACCESS_MASK													AccessMask=STANDARD_RIGHTS_READ;
	CLIENT_ID													ClientID;

	ClientID.UniqueProcess=ULongToHandle(ProcessID);
	ClientID.UniqueThread=nullptr;

	// !!! Inicializuju sa OBJECT ATTRIBUTES.
	// !!! PROCESS NEMA OBJECT NAME.
	OBJECT_ATTRIBUTES											ProcessAttributes=RTL_CONSTANT_OBJECT_ATTRIBUTES(nullptr,OBJ_KERNEL_HANDLE);
	NTSTATUS													Result1=ZwOpenProcess(&ProcessHandle,AccessMask,&ProcessAttributes,&ClientID);

	if (NT_SUCCESS(Result1)==false)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to CALL [ZwOpenProcess()] with ERROR CODE [%lX] !!!\n",FunctionName,Result1));

		return;
	}

	KdPrint(("!!!!! FUNCTION [%s] OPENED PROCESS with ID [%lu] !!!\n",FunctionName,ProcessID));

	NTSTATUS													Result2=ZwClose(ProcessHandle);

	if (NT_SUCCESS(Result2)==false)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to CALL [ZwClose()] with ERROR CODE [%lX] !!!\n",FunctionName,Result2));

		return;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestsObjectAttributes2(PCWSTR Path)
{
	const char*													FunctionName=__FUNCTION__;

	HANDLE														FileHandle;
	UNICODE_STRING												Name;

	RtlInitUnicodeString(&Name,Path);

	OBJECT_ATTRIBUTES											FileAttributes;

	// !!! Inicializuju sa OBJECT ATTRIBUTES.
	// !!! FILE NAME sa prenasa vo FIELD [OBJECT_ATTRIBUTES::ObjectName].
	InitializeObjectAttributes(&FileAttributes,&Name,OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,nullptr,nullptr);

	IO_STATUS_BLOCK												IOStatus;
	NTSTATUS													Result1=ZwOpenFile(&FileHandle,FILE_GENERIC_READ,&FileAttributes,&IOStatus,FILE_SHARE_READ,0);

	if (NT_SUCCESS(Result1)==false)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to CALL [ZwOpenFile()] with ERROR CODE [%lX] !!!\n",FunctionName,Result1));

		return;
	}

	KdPrint(("!!!!! FUNCTION [%s] OPENED FILE with NAME [%wZ] !!!\n",FunctionName,Name));

	NTSTATUS													Result2=ZwClose(FileHandle);

	if (NT_SUCCESS(Result2)==false)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to CALL [ZwClose()] with ERROR CODE [%lX] !!!\n",FunctionName,Result2));

		return;
	}
}
//----------------------------------------------------------------------------------------------------------------------