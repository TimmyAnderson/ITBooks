//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <iterator>
//-----------------------------------------------------------------------------
template<typename TContainer>
class CCustomIterator : public std::iterator<std::forward_iterator_tag,typename TContainer::value_type,typename TContainer::difference_type,typename TContainer::pointer,typename TContainer::reference>
{
//-----------------------------------------------------------------------------
	public:
		using													TIterator=typename TContainer::iterator;

	private:
		TContainer&												MContainer;
		TIterator												MIterator;

	public:
		CCustomIterator& operator=(const CCustomIterator& Iterator)
		{
			MContainer=Iterator.MContainer;
			MIterator=Iterator.MIterator;

			return(*this);
		}

		typename TContainer::reference operator*(void) const
		{
			return(*MIterator);
		}

		typename TContainer::pointer operator->(void) const
		{
			return(MIterator.operator->());
		}

		bool operator==(const CCustomIterator& Iterator)
		{
			return(MIterator==Iterator.MIterator);
		}

		bool operator!=(const CCustomIterator& Iterator)
		{
			return(MIterator!=Iterator.MIterator);
		}

		TIterator& operator++(void)
		{
			++MIterator;

			return(MIterator);
		}

		TIterator operator++(int)
		{
			TIterator											Iterator=MIterator;

			++MIterator;

			return(Iterator);
		}


	public:
		CCustomIterator(TContainer& Container, TIterator Iterator)
			: MContainer(Container), MIterator(Iterator)
		{
		}

		CCustomIterator(const CCustomIterator& Iterator)
			: MContainer(Iterator.MContainer), MIterator(Iterator.MIterator)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------