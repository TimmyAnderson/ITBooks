//----------------------------------------------------------------------------------------------------------------------
#include "TestAvlTreesGlobal.h"
#include "Helpers\CHelpers.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CAvlTreeGlobal.h"
#include "SMyTreeKey.h"
#include "SMyTreeItem.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CAvlTreeGlobal<SMyTreeKey,SMyTreeItem>							AvlTreesGlobalTree;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PVOID AvlTreesGlobalInsertItem(CAvlTreeGlobal<SMyTreeKey,SMyTreeItem>& Tree, SMyTreeItem& TreeItem)
{
	ULONG														Key=TreeItem.GetKey();
	ULONG														Value=TreeItem.GetValue();
	BOOLEAN														NewTreeItemAdded;
	SMyTreeItem*												NewItem=Tree.InsertItem(TreeItem,NewTreeItemAdded);

	if (NewItem!=nullptr)
	{
		ULONG													NewItemKey=NewItem->GetKey();
		ULONG													NewItemValue=NewItem->GetValue();

		if (NewTreeItemAdded==TRUE)
		{
			KdPrint(("!!!!!!!!!! TREE [%p] INSERTED NEW TREE ITEM [%p]. ITEM KEY [%lu] ITEM VALUE [%lu] NEW ITEM KEY [%lu] NEW ITEM VALUE [%lu].\n",&Tree,NewItem,Key,Value,NewItemKey,NewItemValue));
		}
		else
		{
			KdPrint(("!!!!!!!!!! TREE [%p] FAILED to INSERT EXISTING TREE ITEM [%p]. ITEM KEY [%lu] ITEM VALUE [%lu] NEW ITEM KEY [%lu] NEW ITEM VALUE [%lu].\n",&Tree,NewItem,Key,Value,NewItemKey,NewItemValue));
		}
	}
	else
	{
		KdPrint(("!!!!!!!!!! TREE [%p] FAILED to INSERT NEW TREE ITEM [%p]. ITEM KEY [%lu] ITEM VALUE [%lu].\n",&Tree,NewItem,Key,Value));
	}

	return(NewItem);
}
//----------------------------------------------------------------------------------------------------------------------
void AvlTreesGlobalDeleteItem(CAvlTreeGlobal<SMyTreeKey,SMyTreeItem>& Tree, SMyTreeKey& TreeKey)
{
	ULONG														Key=TreeKey.GetKey();
	BOOLEAN														TreeItemDeleted=Tree.DeleteItem(TreeKey);

	if (TreeItemDeleted==TRUE)
	{
		KdPrint(("!!!!!!!!!! TREE [%p] DELETED EXISTING TREE ITEM. ITEM KEY [%lu].\n",&Tree,Key));
	}
	else
	{
		KdPrint(("!!!!!!!!!! TREE [%p] FAILED to DELETE NOT EXISTING TREE ITEM. ITEM KEY [%lu].\n",&Tree,Key));
	}
}
//----------------------------------------------------------------------------------------------------------------------
void AvlTreesGlobalGetItem(CAvlTreeGlobal<SMyTreeKey,SMyTreeItem>& Tree, SMyTreeKey& TreeKey)
{
	PVOID														RawTreeItem=Tree.GetItemByKey(TreeKey);
	const SMyTreeItem*											TreeItem=static_cast<const SMyTreeItem*>(RawTreeItem);
	ULONG														Key=TreeItem->GetKey();
	ULONG														Value=TreeItem->GetValue();

	KdPrint(("!!!!!!!!!! TREE [%p] ITEM RETRIEVED by KEY. TREE KEY [%lu] TREE VALUE [%lu].\n",&Tree,Key,Value));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestAvlTreesGlobal(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

		SMyTreeItem												TreeItems[]{SMyTreeItem(1,101),SMyTreeItem(2,102),SMyTreeItem(3,103),SMyTreeItem(4,104),SMyTreeItem(5,105)};
		constexpr ULONG											TreeItemsCount=(sizeof(TreeItems)/sizeof(TreeItems[0]));

		AvlTreesGlobalTree.Init(EPoolFlags::E_POOL_FLAG_PAGED);

		do
		{
			bool												InsertsFailed=false;

			for(ULONG Index=0;Index<TreeItemsCount;Index++)
			{
				if (AvlTreesGlobalInsertItem(AvlTreesGlobalTree,TreeItems[Index])==nullptr)
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

			while(true)
			{
				PVOID											RawTreeItem=AvlTreesGlobalTree.EnumerateWithoutSplaying(RestartKey);

				if (RawTreeItem!=nullptr)
				{
					const SMyTreeItem*							TreeItem=static_cast<const SMyTreeItem*>(RawTreeItem);
					ULONG										Key=TreeItem->GetKey();
					ULONG										Value=TreeItem->GetValue();

					KdPrint(("!!!!!!!!!! TREE [%p] ITEM RETRIEVED by ENUMERATION. TREE KEY [%lu] TREE VALUE [%lu].\n",&AvlTreesGlobalTree,Key,Value));
				}
				else
				{
					break;
				}
			}

			KdPrint(("----------------------------------------------------------------------------------------------------\n"));

			// !!! Pokus o INSERT EXISTUJUCEHO ITEM. INSERT zlyha.
			AvlTreesGlobalInsertItem(AvlTreesGlobalTree,TreeItems[0]);

			// !!! DELETE existujuceho ITEM.
			AvlTreesGlobalDeleteItem(AvlTreesGlobalTree,TreeItems[3]);

			// !!! Pokus o DELETE EXISTUJUCEHO ITEM. DELETE zlyha.
			AvlTreesGlobalDeleteItem(AvlTreesGlobalTree,TreeItems[3]);

			// !!! Ziskanie ITEM podla KEY.
			AvlTreesGlobalGetItem(AvlTreesGlobalTree,TreeItems[1]);

			KdPrint(("----------------------------------------------------------------------------------------------------\n"));

			for(ULONG Index=0;Index<AvlTreesGlobalTree.GetNumberOfItems();Index++)
			{
				PVOID											RawTreeItem=AvlTreesGlobalTree.GetItemByIndex(Index);

				if (RawTreeItem!=nullptr)
				{
					const SMyTreeItem*							TreeItem=static_cast<const SMyTreeItem*>(RawTreeItem);
					ULONG										Key=TreeItem->GetKey();
					ULONG										Value=TreeItem->GetValue();

					KdPrint(("!!!!!!!!!! TREE [%p] ITEM RETRIEVED by INDEX. TREE KEY [%lu] TREE VALUE [%lu].\n",&AvlTreesGlobalTree,Key,Value));
				}
				else
				{
					KdPrint(("!!!!!!!!!! TREE [%p] ITEM RETRIEVED by INDEX FAILED. INDEX is OUT of BOUNDS.\n",&AvlTreesGlobalTree));
				}
			}
			
			KdPrint(("----------------------------------------------------------------------------------------------------\n"));

			BOOLEAN												IsEmptyTree=AvlTreesGlobalTree.IsEmpty();

			if (IsEmptyTree==TRUE)
			{
				KdPrint(("!!!!!!!!!! TREE [%p] is EMPTY.\n",&AvlTreesGlobalTree));
			}
			else
			{
				KdPrint(("!!!!!!!!!! TREE [%p] is NOT EMPTY.\n",&AvlTreesGlobalTree));
			}

			KdPrint(("----------------------------------------------------------------------------------------------------\n"));

			// !!! VALUE [TRUE] znamena, ze sa spusta nova ENUMERATION.
			BOOLEAN												Restart=TRUE;

			while(true)
			{
				PVOID											RawTreeItem=AvlTreesGlobalTree.Enumerate(Restart);

				if (RawTreeItem!=nullptr)
				{
					const SMyTreeItem*							TreeItem=static_cast<const SMyTreeItem*>(RawTreeItem);
					ULONG										Key=TreeItem->GetKey();
					ULONG										Value=TreeItem->GetValue();

					KdPrint(("!!!!!!!!!! TREE [%p] ITEM RETRIEVED by ENUMERATION. TREE KEY [%lu] TREE VALUE [%lu].\n",&AvlTreesGlobalTree,Key,Value));

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

		// !!! Odstrania sa vsetky ITEMS v TREE, aby nedoslo k MEMORY LEAK.
		while(true)
		{
			SMyTreeKey*											ItemToRemove=AvlTreesGlobalTree.GetItemByIndex(0);

			if (ItemToRemove!=nullptr)
			{
				AvlTreesGlobalDeleteItem(AvlTreesGlobalTree,*ItemToRemove);
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