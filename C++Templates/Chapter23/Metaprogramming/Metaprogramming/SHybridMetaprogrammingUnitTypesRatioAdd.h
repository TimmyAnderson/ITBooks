//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "SHybridMetaprogrammingUnitTypesRatio.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS v COMPILE TIME vypocitava sucet dvoch TYPES [SHybridMetaprogrammingUnitTypesRatio<NUMERATOR,DENOMINATOR>].
template<typename TRatio1, typename TRatio2>
struct SHybridMetaprogrammingUnitTypesRatioAddType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		static constexpr unsigned int							Numerator=((TRatio1::Numerator*TRatio2::Denominator)+(TRatio2::Numerator*TRatio1::Denominator));
		static constexpr unsigned int							Denominator=(TRatio1::Denominator*TRatio2::Denominator);

	public:
		using													TYPE=SHybridMetaprogrammingUnitTypesRatio<Numerator,Denominator>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TRatio1, typename TRatio2>
using															SHybridMetaprogrammingUnitTypesRatioAddUsing=typename SHybridMetaprogrammingUnitTypesRatioAddType<TRatio1,TRatio2>::TYPE;
//----------------------------------------------------------------------------------------------------------------------