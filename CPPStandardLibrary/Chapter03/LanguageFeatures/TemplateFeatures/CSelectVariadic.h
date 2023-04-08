//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! VARIADIC TEMPLATE.
template<int Count, typename... TCases>
class CSelectVariadic
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<int Count, typename TType, typename... TCases>
class CSelectVariadic<Count,TType,TCases...> : public CSelectVariadic<Count-1,TCases...>
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType, typename... TCases>
class CSelectVariadic<0,TType,TCases...>
{
//-------------------------------------------------------------------------------------------------------
	public:
		using TYPE=TType;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------