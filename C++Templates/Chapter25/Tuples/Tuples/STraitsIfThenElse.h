//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PRIMARY TEMPLATE CLASS pre TRUE CASE.
template<bool CONDITION, typename TTrue, typename TFalse>
struct STraitsIfThenElseType
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
struct STraitsIfThenElseType<false,TTrue,TFalse>
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