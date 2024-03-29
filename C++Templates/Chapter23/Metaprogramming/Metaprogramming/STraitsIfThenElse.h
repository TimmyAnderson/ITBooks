//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PRIMARY TEMPLATE CLASS pre TRUE CASE.
template<bool CONDITION, typename TTrue, typename TFalse>
struct STraitsIfThenElseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=TTrue;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS SPECIALIZATION pre FALSE CASE.
template<typename TTrue, typename TFalse>
struct STraitsIfThenElseType<false,TTrue,TFalse> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=TFalse;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<bool CONDITION, typename TTrue, typename TFalse>
using															STraitsIfThenElseUsing=typename STraitsIfThenElseType<CONDITION,TTrue,TFalse>::TYPE;
//----------------------------------------------------------------------------------------------------------------------