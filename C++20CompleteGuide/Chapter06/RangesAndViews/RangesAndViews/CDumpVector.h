//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
class CDumpVectorIterator final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
        using													iterator_concept=std::random_access_iterator_tag;
		using													iterator_category=std::random_access_iterator_tag;
		using													value_type=TItem;
		using													difference_type=std::ptrdiff_t;
		using													const_pointer=const TItem*;
		using													reference=const TItem&;

	private:
		const_pointer											MIterator;

	public:
		reference operator*(void) const;
		CDumpVectorIterator<TItem>& operator++(void);
		CDumpVectorIterator<TItem> operator++(int);
        bool operator==(const CDumpVectorIterator<TItem>& Other) const;

	public:
		CDumpVectorIterator(void);
		CDumpVectorIterator(const_pointer Iterator);
		~CDumpVectorIterator(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVectorIterator<TItem>::CDumpVectorIterator(void)
	: MIterator(nullptr)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVectorIterator<TItem>::CDumpVectorIterator(const_pointer Iterator)
	: MIterator(Iterator)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVectorIterator<TItem>::~CDumpVectorIterator(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVectorIterator<TItem>::reference CDumpVectorIterator<TItem>::operator*(void) const
{
	std::wcout << L"ITERATOR OPERATOR [OPERATOR*] CALLED." << std::endl;

	reference													Value=*MIterator;

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVectorIterator<TItem>& CDumpVectorIterator<TItem>::operator++(void)
{
	std::wcout << L"ITERATOR OPERATOR [OPERATOR++] CALLED." << std::endl;

	MIterator++;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVectorIterator<TItem> CDumpVectorIterator<TItem>::operator++(int)
{
	std::wcout << L"ITERATOR OPERATOR [OPERATOR++(int)] CALLED." << std::endl;

	MIterator++;

	return(this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
bool CDumpVectorIterator<TItem>::operator==(const CDumpVectorIterator<TItem>& Other) const
{
	if (MIterator==Other.MIterator)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
class CDumpVector final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::vector<TItem>										MCollection;

	public:
		CDumpVectorIterator<TItem> begin(void) const noexcept;
		CDumpVectorIterator<TItem> end(void) const noexcept;

	public:
		CDumpVector(std::initializer_list<TItem> Values);
		~CDumpVector(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVector<TItem>::CDumpVector(std::initializer_list<TItem> Values)
	: MCollection(Values)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVector<TItem>::~CDumpVector(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVectorIterator<TItem> CDumpVector<TItem>::begin(void) const noexcept
{
	//std::wcout << L"BEGIN ITERATOR CALLED." << std::endl;

	typename std::vector<TItem>::const_pointer					VectorIterator=(MCollection.data());
	CDumpVectorIterator<TItem>									Iterator(VectorIterator);

	return(Iterator);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TItem>
CDumpVectorIterator<TItem> CDumpVector<TItem>::end(void) const noexcept
{
	//std::wcout << L"END ITERATOR CALLED." << std::endl;

	typename std::vector<TItem>::const_pointer					VectorIterator=(MCollection.data()+MCollection.size());
	CDumpVectorIterator<TItem>									Iterator(VectorIterator);

	return(Iterator);
}
//----------------------------------------------------------------------------------------------------------------------