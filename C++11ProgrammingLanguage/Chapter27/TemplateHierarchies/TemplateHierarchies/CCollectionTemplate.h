//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <vector>
#include "CException.h"
//-------------------------------------------------------------------------------------------------------
template<typename TItemType>
class CCollectionTemplate
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::vector<TItemType>									MCollection;

	public:
		TItemType operator[](size_t Index)
		{
			if (Index>=0 && Index<MCollection.size())
			{
				TItemType										Item=MCollection[Index];

				return(Item);
			}
			else
			{
				throw(CException(L"INDEX is OUT OF BOUNDS !"));
			}
		}

		template<typename TDestinationItemType>
		operator CCollectionTemplate<TDestinationItemType>(void)
		{
			wprintf_s(L"CUSTOM CONVERSION OPERATOR CALLED !\n");

			CCollectionTemplate<TDestinationItemType>			Result;

			for(TItemType Item : *this)
			{
				// !!! COMPILER tento CODE umozni IBA ak existuje konverzia z TYPE [TItemType] na TYPE [TDestinationItemType].
				Result.AddItem(Item);
			}

			return(Result);
		}

	public:
		void AddItem(const TItemType& Item)
		{
			MCollection.push_back(Item);
		}

		TItemType RemoveItem(size_t Index)
		{
			TItemType											Item=(*this)[Index];

			MCollection.erase(MCollection.cbegin() + Index);

			return(Item);
		}

		size_t GetNumberOfItems(void) const
		{
			return(MCollection.size());
		}

		typename std::vector<TItemType>::iterator begin(void)
		{
			return(MCollection.begin());
		}

		typename std::vector<TItemType>::iterator end(void)
		{
			return(MCollection.end());
		}

	public:
		CCollectionTemplate(void)
			: MCollection()
		{
		}

		inline CCollectionTemplate(std::initializer_list<TItemType> Data)
		{
			MCollection=Data;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------