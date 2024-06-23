//----------------------------------------------------------------------------------------------------------------------
#include "TestWorkItemsDynamic.h"
#include "CHelpers.h"
#include "MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void WorkItemsDynamicWorkItemRoutine(PVOID IoObject, PVOID Context, PIO_WORKITEM IoWorkItem)
{
	UNREFERENCED_PARAMETER(IoObject);
	UNREFERENCED_PARAMETER(Context);

	// !!!!! Po vybrati WORK ITEM z QUEUE je ho mozne uvolnit.
	IoUninitializeWorkItem(IoWorkItem);

	// !!! Uvolni sa MEMORY WORK ITEM.
	ExFreePoolWithTag(IoWorkItem,MY_TAG);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! WORK ITEM ROUTINE [%s] - STARTED.\n",FunctionName));

	CHelpers::Sleep(100);

	KdPrint(("!!!!!!!!!! WORK ITEM ROUTINE [%s] - FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestWorkItemsDynamic(PDEVICE_OBJECT DeviceObject)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	// !!! Ziska sa dlzka WORK ITEM.
	ULONG														WorkItemSize=IoSizeofWorkItem();

	// !!! Alokuje sa WORK ITEM.
	// !!! Pre KAZDY WORK ITEM v QUEUE sa MUSI alokovat nova instancia STRUCTURE [_IO_WORKITEM].
	PIO_WORKITEM												WorkItem=(PIO_WORKITEM)ExAllocatePool2(POOL_FLAG_NON_PAGED,WorkItemSize,MY_TAG);

	if (WorkItem!=nullptr)
	{
		// !!! Incializuje sa WORK ITEM.
		IoInitializeWorkItem(DeviceObject,WorkItem);

		// !!! WORK ITEM sa zaradi do QUEUE.
		IoQueueWorkItemEx(WorkItem,WorkItemsDynamicWorkItemRoutine,WORK_QUEUE_TYPE::DelayedWorkQueue,nullptr);
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - CAN NOT ALLOCATE WORK ITEM.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------