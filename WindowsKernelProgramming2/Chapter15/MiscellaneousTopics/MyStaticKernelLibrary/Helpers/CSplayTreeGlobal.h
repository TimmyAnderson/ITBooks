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
concept CConceptSplayTreeKey=requires(TKey Value1, TKey Value2)
{
	Value1<Value2;
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
class CSplayTreeGlobal : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		RTL_GENERIC_TABLE										MTree;
		EPoolFlags												MPool;

	private:
		static RTL_GENERIC_COMPARE_RESULTS NTAPI StaticTreeCompareRoutine(_RTL_GENERIC_TABLE* Table, PVOID FirstStruct, PVOID SecondStruct);
		static PVOID NTAPI StaticTreeAllocateRoutine(_RTL_GENERIC_TABLE* Table, CLONG ByteSize);
		static VOID NTAPI StaticTreeFreeRoutine(_RTL_GENERIC_TABLE* Table, PVOID Buffer);

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
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
RTL_GENERIC_COMPARE_RESULTS NTAPI CSplayTreeGlobal<TKey,TValue>::StaticTreeCompareRoutine(_RTL_GENERIC_TABLE* Table, PVOID FirstStruct, PVOID SecondStruct)
{
	CSplayTreeGlobal*											This=static_cast<CSplayTreeGlobal*>(Table->TableContext);
	RTL_GENERIC_COMPARE_RESULTS									Result=This->TreeCompareRoutine(FirstStruct,SecondStruct);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
PVOID NTAPI CSplayTreeGlobal<TKey,TValue>::StaticTreeAllocateRoutine(_RTL_GENERIC_TABLE* Table, CLONG ByteSize)
{
	CSplayTreeGlobal*											This=static_cast<CSplayTreeGlobal*>(Table->TableContext);
	PVOID														Result=This->TreeAllocateRoutine(ByteSize);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
VOID NTAPI CSplayTreeGlobal<TKey,TValue>::StaticTreeFreeRoutine(_RTL_GENERIC_TABLE* Table, PVOID Buffer)
{
	CSplayTreeGlobal*											This=static_cast<CSplayTreeGlobal*>(Table->TableContext);

	This->TreeFreeRoutine(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
RTL_GENERIC_COMPARE_RESULTS NTAPI CSplayTreeGlobal<TKey,TValue>::TreeCompareRoutine(PVOID FirstStruct, PVOID SecondStruct)
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
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
PVOID NTAPI CSplayTreeGlobal<TKey,TValue>::TreeAllocateRoutine(CLONG ByteSize)
{
	void*														Buffer=ExAllocatePool2(static_cast<POOL_FLAGS>(MPool),ByteSize,MY_TAG);

#ifdef DUMP_ROUTINES
	KdPrint(("!!!!!!!!!! TREE [%p] ALLOCATED ITEM [%p] with SIZE [%lu].\n",this,Buffer,ByteSize));
#endif

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
VOID NTAPI CSplayTreeGlobal<TKey,TValue>::TreeFreeRoutine(PVOID Buffer)
{
#ifdef DUMP_ROUTINES
	KdPrint(("!!!!!!!!!! TREE [%p] is DELETING ITEM [%p].\n",this,Buffer));
#endif

	ExFreePoolWithTag(Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
TValue* CSplayTreeGlobal<TKey,TValue>::InsertItem(const TValue& Value, BOOLEAN& ItemInserted)
{
	TValue*														NewItem=static_cast<TValue*>(RtlInsertElementGenericTable(&MTree,PVOID(&Value),sizeof(Value),&ItemInserted));

	return(NewItem);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
BOOLEAN CSplayTreeGlobal<TKey,TValue>::DeleteItem(const TKey& Key)
{
	BOOLEAN														TreeItemDeleted=RtlDeleteElementGenericTable(&MTree,PVOID(&Key));

	return(TreeItemDeleted);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
TValue* CSplayTreeGlobal<TKey,TValue>::GetItemByKey(const TKey& Key)
{
	TValue*														NewItem=static_cast<TValue*>(RtlLookupElementGenericTable(&MTree,PVOID(&Key)));

	return(NewItem);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
TValue* CSplayTreeGlobal<TKey,TValue>::GetItemByIndex(ULONG Index)
{
	TValue*														Item=static_cast<TValue*>(RtlGetElementGenericTable(&MTree,Index));

	return(Item);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
ULONG CSplayTreeGlobal<TKey,TValue>::GetNumberOfItems(void)
{
	ULONG														NumberOfItems=RtlNumberGenericTableElements(&MTree);

	return(NumberOfItems);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
BOOLEAN CSplayTreeGlobal<TKey,TValue>::IsEmpty(void)
{
	BOOLEAN														IsEmpty=RtlIsGenericTableEmpty(&MTree);

	return(IsEmpty);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
TValue* CSplayTreeGlobal<TKey,TValue>::Enumerate(BOOLEAN Restart)
{
	TValue*														Item=static_cast<TValue*>(RtlEnumerateGenericTable(&MTree,Restart));

	return(Item);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
TValue* CSplayTreeGlobal<TKey,TValue>::EnumerateWithoutSplaying(PVOID& RestartKey)
{
	TValue*														Item=static_cast<TValue*>(RtlEnumerateGenericTableWithoutSplaying(&MTree,&RestartKey));

	return(Item);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
void CSplayTreeGlobal<TKey,TValue>::Init(EPoolFlags Pool)
{
	MPool=Pool;

	RtlInitializeGenericTable(&MTree,StaticTreeCompareRoutine,StaticTreeAllocateRoutine,StaticTreeFreeRoutine,this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//#undef DUMP_ROUTINES
//----------------------------------------------------------------------------------------------------------------------