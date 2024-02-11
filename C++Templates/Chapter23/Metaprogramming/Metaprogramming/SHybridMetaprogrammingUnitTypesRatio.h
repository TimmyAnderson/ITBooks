//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<unsigned int NUMERATOR, unsigned int DENOMINATOR>
struct SHybridMetaprogrammingUnitTypesRatio final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr unsigned int							Numerator=NUMERATOR;
		static constexpr unsigned int							Denominator=DENOMINATOR;

	public:
		using													TYPE=SHybridMetaprogrammingUnitTypesRatio<Numerator,Denominator>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------