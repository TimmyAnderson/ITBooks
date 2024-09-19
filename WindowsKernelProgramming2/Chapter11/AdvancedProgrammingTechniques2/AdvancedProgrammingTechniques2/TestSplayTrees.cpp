//----------------------------------------------------------------------------------------------------------------------
#include "TestSplayTrees.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "SMyTreeKey.h"
#include "SMyTreeItem.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//#define DUMP_ROUTINES
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION vykonava porovnanie KEYS.
RTL_GENERIC_COMPARE_RESULTS NTAPI SplayTreesCompareRoutine(_RTL_GENERIC_TABLE* Table, PVOID FirstStruct, PVOID SecondStruct)
{
	const SMyTreeKey*											FirstItem=static_cast<const SMyTreeItem*>(FirstStruct);
	const SMyTreeKey*											SecondItem=static_cast<const SMyTreeItem*>(SecondStruct);
	ULONG														FirstKey=FirstItem->GetKey();
	ULONG														SecondKey=SecondItem->GetKey();
	RTL_GENERIC_COMPARE_RESULTS									Result;
	const char*													TextResult;

	if (FirstKey<SecondKey)
	{
		Result=RTL_GENERIC_COMPARE_RESULTS::GenericLessThan;
		TextResult="LESS THAN";
	}
	else if (FirstKey>SecondKey)
	{
		Result=RTL_GENERIC_COMPARE_RESULTS::GenericGreaterThan;
		TextResult="GREATER THAN";
	}
	else
	{
		Result=RTL_GENERIC_COMPARE_RESULTS::GenericEqual;
		TextResult="EQUAL";
	}

#ifdef DUMP_ROUTINES
	const char*													TableContext=static_cast<const char*>(Table->TableContext);

	KdPrint(("!!!!!!!!!! TREE [%s] COMPARING ITEM [%lu] with ITEM [%lu]. RESULT [%s].\n",TableContext,FirstKey,SecondKey,TextResult));
#else
	UNREFERENCED_PARAMETER(Table);
#endif

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION vykonava alokaciu TREE ITEM, ktory obsahuje USER DATA a DATA potrebne na ulozenie TREE ITEM v TREE.
// !!!!! PARAMETER [CLONG ByteSize] obsahuje dlzku pre USER DATA a DATA potrebne na ulozenie TREE ITEM v TREE.
PVOID NTAPI SplayTreesAllocateRoutine(_RTL_GENERIC_TABLE* Table, CLONG ByteSize)
{
	void*														Buffer=ExAllocatePool2(POOL_FLAG_PAGED,ByteSize,MY_TAG);

#ifdef DUMP_ROUTINES
	const char*													TableContext=static_cast<const char*>(Table->TableContext);

	KdPrint(("!!!!!!!!!! TREE [%s] ALLOCATED ITEM [%p] with SIZE [%lu].\n",TableContext,Buffer,ByteSize));
#else
	UNREFERENCED_PARAMETER(Table);
#endif

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION vykonava uvolnenie TREE ITEM, ktory obsahuje USER DATA a DATA potrebne na ulozenie TREE ITEM v TREE.
// !!!!! PARAMETER [PVOID Buffer] obsahuje USER DATA a DATA potrebne na ulozenie TREE ITEM v TREE.
VOID NTAPI SplayTreesFreeRoutine(_RTL_GENERIC_TABLE* Table, PVOID Buffer)
{
#ifdef DUMP_ROUTINES
	const char*													TableContext=static_cast<const char*>(Table->TableContext);

	KdPrint(("!!!!!!!!!! TREE [%s] is DELETING ITEM [%p].\n",TableContext,Buffer));
#else
	UNREFERENCED_PARAMETER(Table);
#endif

	ExFreePoolWithTag(Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PVOID SplayTreesInsertItem(RTL_GENERIC_TABLE* Table, SMyTreeItem& TreeItem)
{
	const char*													TableContext=static_cast<const char*>(Table->TableContext);
	ULONG														Key=TreeItem.GetKey();
	ULONG														Value=TreeItem.GetValue();
	BOOLEAN														NewTreeItemAdded;
	PVOID														NewItem=RtlInsertElementGenericTable(Table,&TreeItem,sizeof(TreeItem),&NewTreeItemAdded);

	if (NewItem!=nullptr)
	{
		if (NewTreeItemAdded==TRUE)
		{
			KdPrint(("!!!!!!!!!! TREE [%s] INSERTED NEW TREE ITEM [%p]. ITEM KEY [%lu] ITEM VALUE [%lu].\n",TableContext,NewItem,Key,Value));
		}
		else
		{
			KdPrint(("!!!!!!!!!! TREE [%s] FAILED to INSERT EXISTING TREE ITEM [%p]. ITEM KEY [%lu] ITEM VALUE [%lu].\n",TableContext,NewItem,Key,Value));
		}
	}
	else
	{
		KdPrint(("!!!!!!!!!! TREE [%s] FAILED to INSERT NEW TREE ITEM [%p]. ITEM KEY [%lu] ITEM VALUE [%lu].\n",TableContext,NewItem,Key,Value));
	}

	return(NewItem);
}
//----------------------------------------------------------------------------------------------------------------------
void SplayTreesDeleteItem(RTL_GENERIC_TABLE* Table, SMyTreeKey& TreeKey)
{
	const char*													TableContext=static_cast<const char*>(Table->TableContext);
	ULONG														Key=TreeKey.GetKey();
	BOOLEAN														TreeItemDeleted=RtlDeleteElementGenericTable(Table,&TreeKey);

	if (TreeItemDeleted==TRUE)
	{
		KdPrint(("!!!!!!!!!! TREE [%s] DELETED EXISTING TREE ITEM. ITEM KEY [%lu].\n",TableContext,Key));
	}
	else
	{
		KdPrint(("!!!!!!!!!! TREE [%s] FAILED to DELETE NOT EXISTING TREE ITEM. ITEM KEY [%lu].\n",TableContext,Key));
	}
}
//----------------------------------------------------------------------------------------------------------------------
void SplayTreesGetItem(RTL_GENERIC_TABLE* Table, SMyTreeKey& TreeKey)
{
	const char*													TableContext=static_cast<const char*>(Table->TableContext);
	PVOID														RawTreeItem=RtlLookupElementGenericTable(Table,&TreeKey);
	const SMyTreeItem*											TreeItem=static_cast<const SMyTreeItem*>(RawTreeItem);
	ULONG														Key=TreeItem->GetKey();
	ULONG														Value=TreeItem->GetValue();

	KdPrint(("!!!!!!!!!! TREE [%s] ITEM RETRIEVED by KEY. TREE KEY [%lu] TREE VALUE [%lu].\n",TableContext,Key,Value));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestSplayTrees(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		const char*												TreeName="SPLAY TREE";
		SMyTreeItem												TreeItems[]{SMyTreeItem(1,101),SMyTreeItem(2,102),SMyTreeItem(3,103),SMyTreeItem(4,104),SMyTreeItem(5,105)};
		constexpr ULONG											TreeItemsCount=(sizeof(TreeItems)/sizeof(TreeItems[0]));

		RTL_GENERIC_TABLE										Tree;

		RtlInitializeGenericTable(&Tree,SplayTreesCompareRoutine,SplayTreesAllocateRoutine,SplayTreesFreeRoutine,PVOID(TreeName));

		do
		{
			bool												InsertsFailed=false;

			for(ULONG Index=0;Index<TreeItemsCount;Index++)
			{
				if (SplayTreesInsertItem(&Tree,TreeItems[Index])==nullptr)
				{
					InsertsFailed=true;
					break;
				}
			}

			if (InsertsFailed==true)
			{
				break;
			}

			KdPrint(("----------------------------------------------------------------------------------------------------\n"));

			// !!! VALUE [nullptr] znamena, ze sa spusta nova ENUMERATION.
			PVOID												RestartKey=nullptr;

			// !!! Vykona sa ENUMERATION pouzitim FUNCTION [RtlEnumerateGenericTableWithoutSplaying()].
			while(true)
			{
				PVOID											RawTreeItem=RtlEnumerateGenericTableWithoutSplaying(&Tree,&RestartKey);

				if (RawTreeItem!=nullptr)
				{
					const SMyTreeItem*							TreeItem=static_cast<const SMyTreeItem*>(RawTreeItem);
					ULONG										Key=TreeItem->GetKey();
					ULONG										Value=TreeItem->GetValue();

					KdPrint(("!!!!!!!!!! TREE [%s] ITEM RETRIEVED by ENUMERATION. TREE KEY [%lu] TREE VALUE [%lu].\n",TreeName,Key,Value));
				}
				else
				{
					break;
				}
			}

			KdPrint(("----------------------------------------------------------------------------------------------------\n"));

			// !!! Pokus o INSERT EXISTUJUCEHO ITEM. INSERT zlyha.
			SplayTreesInsertItem(&Tree,TreeItems[0]);

			// !!! DELETE existujuceho ITEM.
			SplayTreesDeleteItem(&Tree,TreeItems[3]);

			// !!! Pokus o DELETE EXISTUJUCEHO ITEM. DELETE zlyha.
			SplayTreesDeleteItem(&Tree,TreeItems[3]);

			// !!! Ziskanie ITEM podla KEY.
			SplayTreesGetItem(&Tree,TreeItems[1]);
			
			KdPrint(("----------------------------------------------------------------------------------------------------\n"));

			// !!! Vykona sa ENUMERATION pouzitim FUNCTION [RtlGetElementGenericTable()].
			for(ULONG Index=0;Index<RtlNumberGenericTableElements(&Tree);Index++)
			{
				PVOID											RawTreeItem=RtlGetElementGenericTable(&Tree,Index);

				if (RawTreeItem!=nullptr)
				{
					const SMyTreeItem*							TreeItem=static_cast<const SMyTreeItem*>(RawTreeItem);
					ULONG										Key=TreeItem->GetKey();
					ULONG										Value=TreeItem->GetValue();

					KdPrint(("!!!!!!!!!! TREE [%s] ITEM RETRIEVED by INDEX. TREE KEY [%lu] TREE VALUE [%lu].\n",TreeName,Key,Value));
				}
				else
				{
					KdPrint(("!!!!!!!!!! TREE [%s] ITEM RETRIEVED by INDEX FAILED. INDEX is OUT of BOUNDS.\n",TreeName));
				}
			}
			
			KdPrint(("----------------------------------------------------------------------------------------------------\n"));

			BOOLEAN												IsEmptyTree=RtlIsGenericTableEmpty(&Tree);

			if (IsEmptyTree==TRUE)
			{
				KdPrint(("!!!!!!!!!! TREE [%s] is EMPTY.\n",TreeName));
			}
			else
			{
				KdPrint(("!!!!!!!!!! TREE [%s] is NOT EMPTY.\n",TreeName));
			}

			KdPrint(("----------------------------------------------------------------------------------------------------\n"));

			// !!! VALUE [TRUE] znamena, ze sa spusta nova ENUMERATION.
			BOOLEAN												Restart=TRUE;

			// !!! Vykona sa ENUMERATION pouzitim FUNCTION [RtlEnumerateGenericTable()].
			while(true)
			{
				PVOID											RawTreeItem=RtlEnumerateGenericTable(&Tree,Restart);

				if (RawTreeItem!=nullptr)
				{
					const SMyTreeItem*							TreeItem=static_cast<const SMyTreeItem*>(RawTreeItem);
					ULONG										Key=TreeItem->GetKey();
					ULONG										Value=TreeItem->GetValue();

					KdPrint(("!!!!!!!!!! TREE [%s] ITEM RETRIEVED by ENUMERATION. TREE KEY [%lu] TREE VALUE [%lu].\n",TreeName,Key,Value));

					Restart=FALSE;
				}
				else
				{
					break;
				}
			}

			KdPrint(("----------------------------------------------------------------------------------------------------\n"));
		}
		while(false);

		// !!! Vykona sa ENUMERATION pouzitim FUNCTION [RtlEnumerateGenericTable()].
		// !!! Odstrania sa vsetky ITEMS v TREE, aby nedoslo k MEMORY LEAK.
		while(true)
		{
			SMyTreeKey*											ItemToRemove=((SMyTreeKey*)RtlGetElementGenericTable(&Tree,0));

			if (ItemToRemove!=nullptr)
			{
				SplayTreesDeleteItem(&Tree,*ItemToRemove);
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