//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
// !!! CLASS sluzi ako BASE pre CArrayTemplate<TArrayItemType>.
template<typename TArrayType, typename TArrayItemType>
class CArrayOperations
{
	private:
		// !!!!! Vratim SILNE TYPOVU DERIVED CLASS.
		const TArrayType& GetDerivedObject(void) const
		{
			return(static_cast<const TArrayType&>(*this));
		}

	public:
		// !!! Tato metoda predpoklada, ze DERIVED CLASS ma METODU GetSize() a OPERATOR[].
		void ExecuteAllItems(void (*Function)(const TArrayItemType&)) const
		{
			const TArrayType&									DerivedClass=GetDerivedObject();
			int													Size=DerivedClass.GetSize();

			for (int i=0;i<Size;i++)
			{
				const TArrayItemType&							Item=DerivedClass[i];

				Function(Item);
			}
		}

	public:
		CArrayOperations(void)
		{
		}

		virtual ~CArrayOperations(void)
		{
		}
};
//-------------------------------------------------------------------------------------------------------