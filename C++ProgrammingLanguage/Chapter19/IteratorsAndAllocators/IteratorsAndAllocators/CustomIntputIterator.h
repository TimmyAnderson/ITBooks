//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iterator>
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class CCustomIntputIterator : public std::iterator<std::forward_iterator_tag,TType>
{
	private:
		TType*													MActualPosition;

	public:
		/*
		// !!! Ak chcem STANDARDNY ITERATOR musim definovant nasledujuce TYPEDEFS. Alternativou je pouzit CLASS iterator<> ako BASE CLASS.
		typedef std::forward_iterator_tag						iterator_category;
		typedef TType											value_type;
		typedef size_t											difference_type;
		typedef difference_type									distance_type;
		typedef TType*											pointer;
		typedef TType&											reference;
		*/

	public:
		TType* GetActualPosition(void);
		void SetActualPosition(TType* ActualPosition);

	public:
		CCustomIntputIterator(TType* ActualPosition);
		~CCustomIntputIterator(void);
};
//-------------------------------------------------------------------------------------------------------
// !!! Toto su OPERATORS, ktore INPUT ITERATOR MUSI PODPOROVAT.
template<typename TType>
TType& operator*(CCustomIntputIterator<TType>& Iterator);
//-------------------------------------------------------------------------------------------------------
template<typename TType>
CCustomIntputIterator<TType>& operator++(CCustomIntputIterator<TType>& Iterator);
//-------------------------------------------------------------------------------------------------------
template<typename TType>
bool operator==(CCustomIntputIterator<TType>& Iterator1, CCustomIntputIterator<TType>& Iterator2);
//-------------------------------------------------------------------------------------------------------
template<typename TType>
bool operator!=(CCustomIntputIterator<TType>& Iterator1, CCustomIntputIterator<TType>& Iterator2);
//-------------------------------------------------------------------------------------------------------
// !!! OPERATOR-> SOM NEIMPLEMENTOVAL, kedze ho for_each() NEPOTREBUJE.
//-------------------------------------------------------------------------------------------------------