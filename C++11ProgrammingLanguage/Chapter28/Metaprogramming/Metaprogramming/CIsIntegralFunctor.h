//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class CIsIntegralFunctor
{
//-------------------------------------------------------------------------------------------------------
	public:
		bool operator()(void)
		{
			bool												Result=std::is_integral<TType>::value;

			return(Result);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------