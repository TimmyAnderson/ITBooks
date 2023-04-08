//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CTemplateListItem.h"
//-------------------------------------------------------------------------------------------------------
template<typename TListValue>
class CTemplateList
{
//-------------------------------------------------------------------------------------------------------
	private:
		CTemplateListItem<TListValue>							MRoot;

	public:
		void Add(CTemplateListItem<TListValue>* Item)
		{
			MRoot.Add(Item);
		}

		void Remove(CTemplateListItem<TListValue>* Item)
		{
			MRoot.Remove(Item);
		}

		void Iterate(void (*Callback)(CTemplateListItem<TListValue>*))
		{
			MRoot.Iterate(Callback);
		}

		CTemplateListItem<TListValue>* GetFirstItemByValue(TListValue Value)
		{
			return(MRoot.GetFirstItemByValue(Value));
		}

	public:
		CTemplateList(void)
			: MRoot()
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------