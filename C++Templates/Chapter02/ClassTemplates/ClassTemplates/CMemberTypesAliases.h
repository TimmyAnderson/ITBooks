//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CMemberTypesAliases
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! TEMPLATE CLASS MEMBER ALIAS pomocou KEYWORD [typedef].
		typedef typename std::vector<TType>::const_iterator CMyTypeIterator1;

		// !!! TEMPLATE CLASS MEMBER ALIAS pomocou KEYWORD [using].
		template<typename TTypeLocal>
		using CMyTypeIterator2=typename std::vector<TTypeLocal>::const_iterator;

	private:
		std::vector<TType>										MElements;

	public:
		void Push(const TType& Element);
		void Pop(void);
		const TType& Top(void) const;
		void Print1(void) const;
		void Print2(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CMemberTypesAliases<TType>::Push(const TType& Element)
{
	MElements.push_back(Element);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CMemberTypesAliases<TType>::Pop(void)
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
const TType& CMemberTypesAliases<TType>::Top(void) const
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
template<typename TType>
void CMemberTypesAliases<TType>::Print1(void) const
{
	for(CMyTypeIterator1 Iterator=MElements.begin();Iterator!=MElements.end();++Iterator)
	{
		std::wcout << L"VALUE [" << *Iterator << L"] !" << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CMemberTypesAliases<TType>::Print2(void) const
{
	for(CMyTypeIterator2<TType> Iterator=MElements.begin();Iterator!=MElements.end();++Iterator)
	{
		std::wcout << L"VALUE [" << *Iterator << L"] !" << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------