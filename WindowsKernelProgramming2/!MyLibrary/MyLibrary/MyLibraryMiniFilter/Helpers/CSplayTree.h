//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CSplayTreeGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
class CSplayTree final : private CSplayTreeGlobal<TKey,TValue>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using CMemoryOperators::operator new;
		using CMemoryOperators::operator delete;

	public:
		using CSplayTreeGlobal<TKey,TValue>::InsertItem;
		using CSplayTreeGlobal<TKey,TValue>::DeleteItem;

	public:
		using CSplayTreeGlobal<TKey,TValue>::GetItemByKey;
		using CSplayTreeGlobal<TKey,TValue>::GetItemByIndex;
		using CSplayTreeGlobal<TKey,TValue>::GetNumberOfItems;
		using CSplayTreeGlobal<TKey,TValue>::IsEmpty;

	public:
		using CSplayTreeGlobal<TKey,TValue>::Enumerate;
		using CSplayTreeGlobal<TKey,TValue>::EnumerateWithoutSplaying;

	public:
		CSplayTree(EPoolFlags Pool);
		~CSplayTree(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
CSplayTree<TKey,TValue>::CSplayTree(EPoolFlags Pool)
{
	CSplayTreeGlobal<TKey,TValue>::Init(Pool);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptSplayTreeKey<TKey>
CSplayTree<TKey,TValue>::~CSplayTree(void) noexcept
{
	if (IsEmpty()==FALSE)
	{
		KdPrint(("!!!!!!!!!! TREE [%p] is NOT EMPTY in DESTRUCTOR. MEMORY LEAKS !!!!!!!!!!\n",this));
	}
}
//----------------------------------------------------------------------------------------------------------------------