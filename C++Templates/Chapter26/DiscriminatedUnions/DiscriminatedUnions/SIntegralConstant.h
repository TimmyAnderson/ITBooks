//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, TType CONSTANT_VALUE>
struct SIntegralConstant
{
//----------------------------------------------------------------------------------------------------------------------
	public:
	    using													TYPE=TType;

	public:
	    static constexpr TType									VALUE=CONSTANT_VALUE;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------