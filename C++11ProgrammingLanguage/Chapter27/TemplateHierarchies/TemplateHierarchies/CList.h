//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CListItemWithValue.h"
//-------------------------------------------------------------------------------------------------------
template<typename TListItemValue>
class CList
{
//-------------------------------------------------------------------------------------------------------
	private:
		CListItemWithValue<TListItemValue>						MRoot;

	public:
		void Add(CListItemWithValue<TListItemValue>* Item)
		{
			MRoot.Add(Item);
		}

		void Remove(CListItemWithValue<TListItemValue>* Item)
		{
			MRoot.Remove(Item);
		}

		void Iterate(void (*Callback)(CListItemWithValue<TListItemValue>*))
		{
			MRoot.Iterate(Callback);
		}

		CListItemWithValue<TListItemValue>* GetFirstItemByValue(TListItemValue Value)
		{
			return(MRoot.GetFirstItemByValue(Value));
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------