//----------------------------------------------------------------------------------------------------------------------
#include "TestSinglyLinkedLists.h"
#include "Helpers\CHelpers.h"
#include "SSinglyListItem.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestSinglyLinkedLists(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		SSinglyListItem											Item1{100,nullptr};
		SSinglyListItem											Item2{200,nullptr};
		SSinglyListItem											Item3{300,nullptr};

		SINGLE_LIST_ENTRY										Head;

		Head.Next=nullptr;

		PushEntryList(&Head,&Item1.MEntry);
		PushEntryList(&Head,&Item2.MEntry);
		PushEntryList(&Head,&Item3.MEntry);

		while(true)
		{
			PSINGLE_LIST_ENTRY									Entry=PopEntryList(&Head);

			if (Entry!=nullptr)
			{
				SSinglyListItem*								Item=CONTAINING_RECORD(Entry,SSinglyListItem,MEntry);

				KdPrint(("!!!!!!!!!! ITEM VALUE [%lu].\n",Item->MValue));
			}
			else
			{
				break;
			}
		}

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------