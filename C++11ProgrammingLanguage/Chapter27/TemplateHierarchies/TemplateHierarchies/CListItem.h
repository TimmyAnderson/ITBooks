//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! BASE CLASS reprezentuje LIST ITEM.
// !!!!! TYPE PARAMETER obsahuje DERIVED CLASS, ktora reprezentuje LIST ITEM s DATAMI.
template<typename TListItem>
class CListItem
{
//-------------------------------------------------------------------------------------------------------
	private:
		// FIELD [MNext] obsahuje POINTER na nasledujuci LIST ITEM.
		// !!! Kedze TYPE [TListItem] obsahuje DERIVED CLASS (CListItemWithValue), bude obsahovat aj DATA daneho LIST ITEM.
		TListItem*												MNext;

	public:
		void Add(TListItem* Item)
		{
			Item->MNext=nullptr;

			if (MNext==nullptr)
			{
				MNext=Item;
			}
			else
			{
				TListItem*										Current=MNext;

				while(Current->MNext!=nullptr)
				{
					Current=Current->MNext;
				}

				Current->MNext=Item;
			}
		}

		void Remove(TListItem* Item)
		{
			TListItem*											Current=MNext;
			TListItem*											Previous=nullptr;

			while(Current!=nullptr)
			{
				if (Current==Item)
				{
					if (Previous==nullptr)
					{
						MNext=Current->MNext;
					}
					else
					{
						Previous->MNext=Current->MNext;
					}
				}

				Previous=Current;
				Current=Current->MNext;
			}
		}

		void Iterate(void (*Callback)(TListItem*))
		{
			TListItem*											Current=MNext;

			while(Current!=nullptr)
			{
				Callback(Current);

				Current=Current->MNext;
			}
		}

		// !!! TEMPLATE METHOD vyuziva fakt, ze [TListItem] je DERIVED CLASS s DATAMI, ktora ma implementovanu METHOD GetValue() vracajucu DATA daneho LIST ITEM.
		template<typename TListItemValue>
		TListItem* GetFirstItemByValue(TListItemValue Value)
		{
			TListItem*											Current=MNext;

			while(Current!=nullptr)
			{
				// !!! DERIVED CLASS MUSI mat implementovanu METHOD GetValue().
				if (Current->GetValue()==Value)
				{
					return(Current);
				}

				Current=Current->MNext;
			}

			return(nullptr);
		}

	public:
		CListItem(void)
			:MNext(nullptr)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------