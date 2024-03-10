//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <utility>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CCommonType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=decltype(true ? std::declval<TType1>() : std::declval<TType2>());
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
using															CommonType=typename CCommonType<TType1,TType2>::TYPE;
//----------------------------------------------------------------------------------------------------------------------