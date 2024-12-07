//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CAvlTreeGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
class CAvlTree final : private CAvlTreeGlobal<TKey,TValue>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using CMemoryOperators::operator new;
		using CMemoryOperators::operator delete;

	public:
		using CAvlTreeGlobal<TKey,TValue>::InsertItem;
		using CAvlTreeGlobal<TKey,TValue>::DeleteItem;

	public:
		using CAvlTreeGlobal<TKey,TValue>::GetItemByKey;
		using CAvlTreeGlobal<TKey,TValue>::GetItemByIndex;
		using CAvlTreeGlobal<TKey,TValue>::GetNumberOfItems;
		using CAvlTreeGlobal<TKey,TValue>::IsEmpty;

	public:
		using CAvlTreeGlobal<TKey,TValue>::Enumerate;
		using CAvlTreeGlobal<TKey,TValue>::EnumerateWithoutSplaying;

	public:
		CAvlTree(EPoolFlags Pool);
		~CAvlTree(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
CAvlTree<TKey,TValue>::CAvlTree(EPoolFlags Pool)
{
	CAvlTreeGlobal<TKey,TValue>::Init(Pool);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TKey, typename TValue> requires CConceptAvlTreeKey<TKey>
CAvlTree<TKey,TValue>::~CAvlTree(void) noexcept
{
	if (IsEmpty()==FALSE)
	{
		KdPrint(("!!!!!!!!!! TREE [%p] is NOT EMPTY in DESTRUCTOR. MEMORY LEAKS !!!!!!!!!!\n",this));
	}
}
//----------------------------------------------------------------------------------------------------------------------