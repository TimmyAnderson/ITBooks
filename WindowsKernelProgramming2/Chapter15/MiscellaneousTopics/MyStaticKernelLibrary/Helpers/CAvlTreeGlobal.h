//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CMemoryOperators.h"
#include "MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//#define DUMP_ROUTINES
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey>
concept CConceptAvlTreeKey=requires(TKey Value1, TKey Value2)
{
	Value1<Value2;
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
class CAvlTreeGlobal : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		RTL_AVL_TABLE											MTree;
		EPoolFlags												MPool;

	private:
		static RTL_GENERIC_COMPARE_RESULTS NTAPI StaticTreeCompareRoutine(_RTL_AVL_TABLE* Table, PVOID FirstStruct, PVOID SecondStruct);
		static PVOID NTAPI StaticTreeAllocateRoutine(_RTL_AVL_TABLE* Table, CLONG ByteSize);
		static VOID NTAPI StaticTreeFreeRoutine(_RTL_AVL_TABLE* Table, PVOID Buffer);

	private:
		RTL_GENERIC_COMPARE_RESULTS NTAPI TreeCompareRoutine(PVOID FirstStruct, PVOID SecondStruct);
		PVOID NTAPI TreeAllocateRoutine(CLONG ByteSize);
		VOID NTAPI TreeFreeRoutine(PVOID Buffer);

	public:
		TValue* InsertItem(const TValue& Value, BOOLEAN& ItemInserted);
		BOOLEAN DeleteItem(const TKey& Key);

	public:
		TValue* GetItemByKey(const TKey& Key);
		TValue* GetItemByIndex(ULONG Index);
		ULONG GetNumberOfItems(void);
		BOOLEAN IsEmpty(void);

	public:
		TValue* Enumerate(BOOLEAN Restart);
		TValue* EnumerateWithoutSplaying(PVOID& RestartKey);

	public:
		void Init(EPoolFlags Pool);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
RTL_GENERIC_COMPARE_RESULTS NTAPI CAvlTreeGlobal<TKey,TValue>::StaticTreeCompareRoutine(_RTL_AVL_TABLE* Table, PVOID FirstStruct, PVOID SecondStruct)
{
	CAvlTreeGlobal*												This=static_cast<CAvlTreeGlobal*>(Table->TableContext);
	RTL_GENERIC_COMPARE_RESULTS									Result=This->TreeCompareRoutine(FirstStruct,SecondStruct);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
PVOID NTAPI CAvlTreeGlobal<TKey,TValue>::StaticTreeAllocateRoutine(_RTL_AVL_TABLE* Table, CLONG ByteSize)
{
	CAvlTreeGlobal*												This=static_cast<CAvlTreeGlobal*>(Table->TableContext);
	PVOID														Result=This->TreeAllocateRoutine(ByteSize);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
VOID NTAPI CAvlTreeGlobal<TKey,TValue>::StaticTreeFreeRoutine(_RTL_AVL_TABLE* Table, PVOID Buffer)
{
	CAvlTreeGlobal*												This=static_cast<CAvlTreeGlobal*>(Table->TableContext);

	This->TreeFreeRoutine(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
RTL_GENERIC_COMPARE_RESULTS NTAPI CAvlTreeGlobal<TKey,TValue>::TreeCompareRoutine(PVOID FirstStruct, PVOID SecondStruct)
{
	const TKey*													FirstKeyPointer=static_cast<const TKey*>(FirstStruct);
	const TKey*													SecondKeyPointer=static_cast<const TKey*>(SecondStruct);
	const TKey&													FirstKey=*FirstKeyPointer;
	const TKey&													SecondKey=*SecondKeyPointer;
	RTL_GENERIC_COMPARE_RESULTS									Result;
	const char*													TextResult;

	if (FirstKey<SecondKey)
	{
		Result=RTL_GENERIC_COMPARE_RESULTS::GenericLessThan;
		TextResult="LESS THAN";
	}
	else if (SecondKey<FirstKey)
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
	KdPrint(("!!!!!!!!!! TREE [%p] COMPARING ITEMS. RESULT [%s].\n",this,TextResult));
#endif

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
PVOID NTAPI CAvlTreeGlobal<TKey,TValue>::TreeAllocateRoutine(CLONG ByteSize)
{
	void*														Buffer=ExAllocatePool2(static_cast<POOL_FLAGS>(MPool),ByteSize,MY_TAG);

#ifdef DUMP_ROUTINES
	KdPrint(("!!!!!!!!!! TREE [%p] ALLOCATED ITEM [%p] with SIZE [%lu].\n",this,Buffer,ByteSize));
#endif

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
VOID NTAPI CAvlTreeGlobal<TKey,TValue>::TreeFreeRoutine(PVOID Buffer)
{
#ifdef DUMP_ROUTINES
	KdPrint(("!!!!!!!!!! TREE [%p] is DELETING ITEM [%p].\n",this,Buffer));
#endif

	ExFreePoolWithTag(Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
TValue* CAvlTreeGlobal<TKey,TValue>::InsertItem(const TValue& Value, BOOLEAN& ItemInserted)
{
	TValue*														NewItem=static_cast<TValue*>(RtlInsertElementGenericTableAvl(&MTree,PVOID(&Value),sizeof(Value),&ItemInserted));

	return(NewItem);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
BOOLEAN CAvlTreeGlobal<TKey,TValue>::DeleteItem(const TKey& Key)
{
	BOOLEAN														TreeItemDeleted=RtlDeleteElementGenericTableAvl(&MTree,PVOID(&Key));

	return(TreeItemDeleted);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
TValue* CAvlTreeGlobal<TKey,TValue>::GetItemByKey(const TKey& Key)
{
	TValue*														NewItem=static_cast<TValue*>(RtlLookupElementGenericTableAvl(&MTree,PVOID(&Key)));

	return(NewItem);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
TValue* CAvlTreeGlobal<TKey,TValue>::GetItemByIndex(ULONG Index)
{
	TValue*														Item=static_cast<TValue*>(RtlGetElementGenericTableAvl(&MTree,Index));

	return(Item);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
ULONG CAvlTreeGlobal<TKey,TValue>::GetNumberOfItems(void)
{
	ULONG														NumberOfItems=RtlNumberGenericTableElementsAvl(&MTree);

	return(NumberOfItems);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
BOOLEAN CAvlTreeGlobal<TKey,TValue>::IsEmpty(void)
{
	BOOLEAN														IsEmpty=RtlIsGenericTableEmptyAvl(&MTree);

	return(IsEmpty);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
TValue* CAvlTreeGlobal<TKey,TValue>::Enumerate(BOOLEAN Restart)
{
	TValue*														Item=static_cast<TValue*>(RtlEnumerateGenericTableAvl(&MTree,Restart));

	return(Item);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
TValue* CAvlTreeGlobal<TKey,TValue>::EnumerateWithoutSplaying(PVOID& RestartKey)
{
	TValue*														Item=static_cast<TValue*>(RtlEnumerateGenericTableWithoutSplayingAvl(&MTree,&RestartKey));

	return(Item);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
void CAvlTreeGlobal<TKey,TValue>::Init(EPoolFlags Pool)
{
	MPool=Pool;

	RtlInitializeGenericTableAvl(&MTree,StaticTreeCompareRoutine,StaticTreeAllocateRoutine,StaticTreeFreeRoutine,this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//#undef DUMP_ROUTINES
//----------------------------------------------------------------------------------------------------------------------