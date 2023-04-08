//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CListItem.h"
//-------------------------------------------------------------------------------------------------------
// !!! CLASS dedi z CLASS [CListItem<>] pricom zaroven ako TYPE PARAMETER dava SAM SEBA. Je to preto, lebo TYPE PARAMTER CLASS [CListItem] reprezentuje LIST NODE.
// !!!!! CLASS reprezentuje LIST NODE s DATAMI typu [TListItemValue].
// !!!!! Kedze CLASS [CListItemWithValue] reprezentuje LIST ITEM s DATAMI MUSI dedi z BASE CLASS TEMPLATE [CListItem].
// !!!!! Zaroven plati, ze kedze CLASS [CListItem] potrebuje pracovat s DATAMI LIST ITEM, ako TYPE PARAMETER je pouzita DERIVED CLASS [CListItemWithValue].
template<typename TListItemValue>
class CListItemWithValue : public CListItem<CListItemWithValue<TListItemValue>>
{
//-------------------------------------------------------------------------------------------------------
	private:
		TListItemValue											MValue;

	public:
		TListItemValue GetValue(void)
		{
			return(MValue);
		}

	public:
		CListItemWithValue(void)
		{
		}

		CListItemWithValue(TListItemValue Value)
			: MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------