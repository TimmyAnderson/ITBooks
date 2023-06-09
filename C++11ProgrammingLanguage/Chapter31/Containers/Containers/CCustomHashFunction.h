//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <cstddef>
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class CCustomHashFunction
{
//-------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		std::size_t operator()(TType Value) const
		{
			std::size_t											Hash=(Value % 2);

			return(Hash);
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CCustomHashFunction(int Value)
			: MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------