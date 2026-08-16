//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
class CMoveableRangeVector final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::vector<TItem>										MCollection;

	public:
		CMoveableRangeVector<TItem>& operator=(const CMoveableRangeVector<TItem>& Other) noexcept;
		CMoveableRangeVector<TItem>& operator=(CMoveableRangeVector<TItem>&& Other) noexcept;

	public:
		std::vector<TItem>::const_iterator begin(void) const;
		std::vector<TItem>::const_iterator end(void) const;

	public:
		CMoveableRangeVector(std::initializer_list<TItem> Values);
		CMoveableRangeVector(const CMoveableRangeVector<TItem>& Other) noexcept;
		CMoveableRangeVector(CMoveableRangeVector<TItem>&& Other) noexcept;
		~CMoveableRangeVector(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CMoveableRangeVector<TItem>::CMoveableRangeVector(std::initializer_list<TItem> Values)
	: MCollection(Values)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CMoveableRangeVector<TItem>::CMoveableRangeVector(const CMoveableRangeVector<TItem>& Other) noexcept
	: MCollection(Other.MCollection)
{
	std::wcout << L"COPY CONSTRUCTOR CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CMoveableRangeVector<TItem>::CMoveableRangeVector(CMoveableRangeVector<TItem>&& Other) noexcept
	: MCollection(std::move(Other.MCollection))
{
	std::wcout << L"MOVE CONSTRUCTOR CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CMoveableRangeVector<TItem>::~CMoveableRangeVector(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CMoveableRangeVector<TItem>& CMoveableRangeVector<TItem>::operator=(const CMoveableRangeVector<TItem>& Other) noexcept
{
	std::wcout << L"COPY OPERATOR= CALLED." << std::endl;

	if (this!=&Other)
	{
		MCollection=Other.MCollection;
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CMoveableRangeVector<TItem>& CMoveableRangeVector<TItem>::operator=(CMoveableRangeVector<TItem>&& Other) noexcept
{
	std::wcout << L"MOVE OPERATOR= CALLED." << std::endl;

	if (this!=&Other)
	{
		MCollection=std::move(Other.MCollection);
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
std::vector<TItem>::const_iterator CMoveableRangeVector<TItem>::begin(void) const
{
	typename std::vector<TItem>::const_iterator					Iterator=MCollection.begin();

	return(Iterator);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
std::vector<TItem>::const_iterator CMoveableRangeVector<TItem>::end(void) const
{
	typename std::vector<TItem>::const_iterator					Iterator=MCollection.end();

	return(Iterator);
}
//----------------------------------------------------------------------------------------------------------------------