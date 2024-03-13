//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CExpressionTemplateScalar
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		const TType&											MValue;

	public:
		constexpr size_t Size(void) const
		{
			return(0);
		};

	public:
		constexpr const TType& operator[](size_t) const
		{
			return(MValue);
		}

public:
	constexpr CExpressionTemplateScalar(const TType& Value)
		: MValue(Value)
	{
	}

	constexpr virtual ~CExpressionTemplateScalar(void) noexcept
	{
	}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------