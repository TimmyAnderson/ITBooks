//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CStack
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::vector<TType>										MElements;

	public:
		// !!! V ramci DECLARATION a DEFINITION TEMPLATE CLASS pri pouziti TEMPLATE TYPE NIE JE NUTNE definovat TEMPLATE PARAMETERS.
		CStack& operator=(const CStack& Other);

		// !!! V ramci DECLARATION a DEFINITION TEMPLATE CLASS pri pouziti TEMPLATE TYPE JE MOZNE definovat TEMPLATE PARAMETERS.
		CStack<TType>& operator=(CStack<TType>&& Other) noexcept;

	public:
		void Push(const TType& Element);
		void Pop(void);
		const TType& Top(void) const;

		// !!! METHOD je definovana INLINE.
		bool IsEmpty(void) const
		{
			bool												IsEmpty=MElements.empty();

			return(IsEmpty);
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! MIMO DECLARATION a DEFINITION TEMPLATE CLASS pri pouziti TEMPLATE TYPE JE NUTNE definovat TEMPLATE PARAMETERS.
template<typename TType>
CStack<TType>& CStack<TType>::operator=(const CStack& Other)
{
	std::wcout << L"COPY CONSTRUCTOR CALLED !" << std::endl;

	MElements=Other.MElements;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! MIMO DECLARATION a DEFINITION TEMPLATE CLASS pri pouziti TEMPLATE TYPE JE NUTNE definovat TEMPLATE PARAMETERS.
template<typename TType>
CStack<TType>& CStack<TType>::operator=(CStack<TType>&& Other) noexcept
{
	std::wcout << L"MOVE CONSTRUCTOR CALLED !" << std::endl;

	MElements=std::move(Other.MElements);

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CStack<TType>::Push(const TType& Element)
{
	MElements.push_back(Element);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CStack<TType>::Pop(void)
{
	if (MElements.empty()==false)
	{
		MElements.pop_back();
	}
	else
	{
		throw(CException(L"COLLECTION is EMPTY !"));
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CStack<TType>::Top(void) const
{
	if (MElements.empty()==false)
	{
		const TType&											Element=MElements.back();

		return(Element);
	}
	else
	{
		throw(CException(L"COLLECTION is EMPTY !"));
	}
}
//----------------------------------------------------------------------------------------------------------------------