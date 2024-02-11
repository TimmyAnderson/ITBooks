//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "SHybridMetaprogrammingUnitTypesRatio.h"
#include "SHybridMetaprogrammingUnitTypesRatioAdd.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TValueType, typename TRatio>
class SHybridMetaprogrammingUnitTypesDuration final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													ValueType=TValueType;
		using													UnitType=typename TRatio::TYPE;

	private:
		ValueType												MValue;

	public:
		constexpr ValueType GetValue(void) const;

	public:
		constexpr SHybridMetaprogrammingUnitTypesDuration(ValueType Value);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TValueType, typename TRatio>
constexpr SHybridMetaprogrammingUnitTypesDuration<TValueType,TRatio>::SHybridMetaprogrammingUnitTypesDuration(ValueType Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TValueType, typename TRatio>
constexpr typename SHybridMetaprogrammingUnitTypesDuration<TValueType,TRatio>::ValueType SHybridMetaprogrammingUnitTypesDuration<TValueType,TRatio>::GetValue(void) const
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TValueType1, typename TRatio1, typename TValueType2, typename TRatio2>
auto constexpr operator+(const SHybridMetaprogrammingUnitTypesDuration<TValueType1,TRatio1>& Value1, const SHybridMetaprogrammingUnitTypesDuration<TValueType2,TRatio2>& Value2)
{
	using														RATIO=SHybridMetaprogrammingUnitTypesRatio<1,SHybridMetaprogrammingUnitTypesRatioAddUsing<TRatio1,TRatio2>::Denominator>;

	auto														Value=((Value1.GetValue()*RATIO::Denominator/TRatio1::Denominator*TRatio1::Numerator)+(Value2.GetValue()*RATIO::Denominator/TRatio2::Denominator*TRatio2::Numerator));
	SHybridMetaprogrammingUnitTypesDuration<decltype(Value),RATIO>	Result(Value);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------