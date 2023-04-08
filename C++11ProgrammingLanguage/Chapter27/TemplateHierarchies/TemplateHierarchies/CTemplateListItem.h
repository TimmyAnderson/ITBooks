//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template<typename TListValue>
class CTemplateListItem
{
//-------------------------------------------------------------------------------------------------------
	private:
		CTemplateListItem*										MNext;
		TListValue												MValue;

	public:
		TListValue GetValue(void)
		{
			return(MValue);
		}

		void Add(CTemplateListItem<TListValue>* Item)
		{
			Item->MNext=nullptr;

			if (MNext==nullptr)
			{
				MNext=Item;
			}
			else
			{
				CTemplateListItem<TListValue>*					Current=MNext;

				while(Current->MNext!=nullptr)
				{
					Current=Current->MNext;
				}

				Current->MNext=Item;
			}
		}

		void Remove(CTemplateListItem<TListValue>* Item)
		{
			CTemplateListItem<TListValue>*						Current=MNext;
			CTemplateListItem<TListValue>*						Previous=nullptr;

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

		void Iterate(void (*Callback)(CTemplateListItem<TListValue>*))
		{
			CTemplateListItem<TListValue>*						Current=MNext;

			while(Current!=nullptr)
			{
				Callback(Current);

				Current=Current->MNext;
			}
		}

		CTemplateListItem* GetFirstItemByValue(TListValue Value)
		{
			CTemplateListItem*									Current=MNext;

			while(Current!=nullptr)
			{
				if (Current->GetValue()==Value)
				{
					return(Current);
				}

				Current=Current->MNext;
			}

			return(nullptr);
		}

	public:
		CTemplateListItem(void)
			:MNext(nullptr)
		{
		}

		CTemplateListItem(TListValue Value)
			:MNext(nullptr), MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------