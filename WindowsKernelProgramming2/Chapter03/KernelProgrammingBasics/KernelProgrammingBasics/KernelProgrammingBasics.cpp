//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "MyKernelHelpers.h"
#include "TestsReturnValues.h"
#include "TestsStringOperations.h"
#include "TestsMemoryAllocation.h"
#include "TestsListOperations.h"
#include "TestObjectAttributes.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
UNICODE_STRING													MyRegistryPath;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	ExFreePool(MyRegistryPath.Buffer);

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload=FunctionDriverUnload;

	KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));

	MyRegistryPath.Buffer=(WCHAR*)ExAllocatePool2(POOL_FLAG_PAGED,RegistryPath->Length, MY_TAG);

	if (MyRegistryPath.Buffer!=nullptr)
	{
		MyRegistryPath.MaximumLength=RegistryPath->Length;

		RtlCopyUnicodeString(&MyRegistryPath,(PCUNICODE_STRING)RegistryPath);

		KdPrint(("!!!!! DRIVER [%wZ] REGISTRY PATH [%wZ] !!!\n",DriverObject->DriverName,MyRegistryPath));
	}
	else
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to ALLOCATE MEMORY !!!\n",DriverObject->DriverName));

		return(STATUS_INSUFFICIENT_RESOURCES);
	}

	//TestsReturnValues1();
	//TestsReturnValues2();
	//TestsReturnValues3();

	//TestsUnicodeString1();
	//TestsUnicodeString2();
	//TestsUnicodeString3();
	//TestsUnicodeString4();
	//TestsUnicodeString5();
	//TestsUnicodeString6();

	//TestsMemoryAllocation1();
	//TestsMemoryAllocation2();

	//TestsListOperations();

	// !!! PARAMETER musi obsahovat PID existujuceho PROCESSU.
	//TestsObjectAttributes1(1234);

	// !!! PARAMETER musi obsahovat FILE NAME existujuceho FILE.
	// !!!!! FILE NAME MUSI byt v tvare NT PATH, ked je PATH PREFIXED VALUE [\??\].
	//TestsObjectAttributes2(L"\\??\\C:\\Drivers\\TestFile.txt");

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------