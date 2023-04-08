//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "ArrayOperations.h"
//-------------------------------------------------------------------------------------------------------
template<typename TArrayItemType>
// !!! TEMPLATE dedi z TEMPLATE a SAM SEBA zasiela ako TEMPLATE PARAMETER.
class CArrayTemplate : public CArrayOperations<CArrayTemplate<TArrayItemType>,TArrayItemType>
{
	private:
		int														MSize;
		TArrayItemType*											MArray;

	public:
		int GetSize(void) const
		{
			return(MSize);
		}

	public:
		const TArrayItemType& operator[](int Index) const
		{
			if (Index<0 || Index>=MSize)
			{
				throw(L"Index OUT of BOUNDS !");
			}

			return(MArray[Index]);
		}

	public:
		void SetValue(int Index, const TArrayItemType& Value)
		{
			if (Index<0 || Index>=MSize)
			{
				throw(L"Index OUT of BOUNDS !");
			}

			MArray[Index]=Value;
		}

	public:
		CArrayTemplate(int Size)
			: MSize(Size), MArray(NULL)
		{
			MArray=new TArrayItemType[Size];
		}

		virtual ~CArrayTemplate(void)
		{
			delete[](MArray);
			MArray=NULL;
		}
};
//-------------------------------------------------------------------------------------------------------