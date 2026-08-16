#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ranges>
#include <concepts>
#include <optional>
#include <iostream>
#include <vector>
#include <thread>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
class CLINQLikeViewIterator final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													iterator_category=std::input_iterator_tag;
		using													value_type=std::ranges::range_value_t<TRange>;
		using													difference_type=std::ptrdiff_t;

	private:
		std::ranges::iterator_t<const TRange>					MCurrent;
		std::ranges::sentinel_t<const TRange>					MEnd;
		TPredicate*												MPredicate;

	private:
		void MoveNext(void);

	public:
		bool operator==(const CLINQLikeViewIterator& Other) const;
		bool operator==(std::ranges::sentinel_t<const TRange> Sentinel) const;

	public:
		CLINQLikeViewIterator<TRange,TPredicate>& operator++(void);
		void operator++(int);

	public:
		auto operator*(void) const;

	public:
		CLINQLikeViewIterator(void);
		CLINQLikeViewIterator(std::ranges::iterator_t<const TRange> Start, std::ranges::sentinel_t<const TRange> End, TPredicate& Predicate);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
CLINQLikeViewIterator<TRange,TPredicate>::CLINQLikeViewIterator(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
CLINQLikeViewIterator<TRange,TPredicate>::CLINQLikeViewIterator(std::ranges::iterator_t<const TRange> Start, std::ranges::sentinel_t<const TRange> End, TPredicate& Predicate)
	: MCurrent(Start), MEnd(End), MPredicate(&Predicate)
{
	MoveNext();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
void CLINQLikeViewIterator<TRange,TPredicate>::MoveNext(void)
{
	while(MCurrent!=MEnd && (*MPredicate)(*MCurrent)==false)
	{
		++MCurrent;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
bool CLINQLikeViewIterator<TRange,TPredicate>::operator==(const CLINQLikeViewIterator& Other) const
{
	if (MCurrent==Other.MCurrent)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
bool CLINQLikeViewIterator<TRange,TPredicate>::operator==(std::ranges::sentinel_t<const TRange> Sentinel) const
{
	if (MCurrent==Sentinel)
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
template<std::ranges::input_range TRange, typename TPredicate>
auto CLINQLikeViewIterator<TRange,TPredicate>::operator*(void) const
{
	return(*MCurrent);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
CLINQLikeViewIterator<TRange,TPredicate>& CLINQLikeViewIterator<TRange,TPredicate>::operator++(void)
{
	++MCurrent;

	MoveNext();

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
void CLINQLikeViewIterator<TRange,TPredicate>::operator++(int)
{
	++*this;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! VIEW NEPOUZIVA CACHING.
template<std::ranges::input_range TRange, typename TPredicate>
class CLINQLikeView final : public std::ranges::view_interface<CLINQLikeView<TRange,TPredicate>>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		const TRange&											MRange;
		TPredicate												MPredicate;

	public:
		CLINQLikeViewIterator<TRange,TPredicate> begin(void) const; 
	    auto end(void) const;

	public:
		CLINQLikeView(const TRange&, TPredicate MPredicate);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
CLINQLikeView<TRange,TPredicate>::CLINQLikeView(const TRange& Range, TPredicate Predicate)
	: MRange(Range), MPredicate(std::move(Predicate))
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
CLINQLikeViewIterator<TRange,TPredicate> CLINQLikeView<TRange,TPredicate>::begin(void) const
{
	CLINQLikeViewIterator<TRange,TPredicate>					Iterator(std::ranges::begin(MRange),std::ranges::end(MRange),const_cast<TPredicate&>(MPredicate));

    return(Iterator);
}
//----------------------------------------------------------------------------------------------------------------------
template<std::ranges::input_range TRange, typename TPredicate>
auto CLINQLikeView<TRange,TPredicate>::end(void) const
{ 
	auto														Iterator=std::ranges::end(MRange);

    return(Iterator);
}
//----------------------------------------------------------------------------------------------------------------------