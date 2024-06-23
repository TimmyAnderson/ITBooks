//----------------------------------------------------------------------------------------------------------------------
#include "TestWorkItemsStatic.h"
#include "CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void WorkItemsStaticWorkItemRoutine(PVOID IoObject, PVOID Context, PIO_WORKITEM IoWorkItem)
{
	UNREFERENCED_PARAMETER(IoObject);
	UNREFERENCED_PARAMETER(Context);

	// !!!!! Po vybrati WORK ITEM z QUEUE je ho mozne uvolnit.
	IoFreeWorkItem(IoWorkItem);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! WORK ITEM ROUTINE [%s] - STARTED.\n",FunctionName));

	CHelpers::Sleep(100);

	KdPrint(("!!!!!!!!!! WORK ITEM ROUTINE [%s] - FINISHED.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestWorkItemsStatic(PDEVICE_OBJECT DeviceObject)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));
	
	// !!! Alokuje sa WORK ITEM.
	// !!! Pre KAZDY WORK ITEM v QUEUE sa MUSI alokovat nova instancia STRUCTURE [_IO_WORKITEM].
	PIO_WORKITEM												WorkItem=IoAllocateWorkItem(DeviceObject);

	if (WorkItem!=nullptr)
	{
		// !!! WORK ITEM sa zaradi do QUEUE.
		IoQueueWorkItemEx(WorkItem,WorkItemsStaticWorkItemRoutine,WORK_QUEUE_TYPE::DelayedWorkQueue,nullptr);
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - CAN NOT ALLOCATE WORK ITEM.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------