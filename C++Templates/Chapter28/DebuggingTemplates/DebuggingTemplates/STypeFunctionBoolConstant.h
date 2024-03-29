//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<bool BOOL_VALUE>
struct STypeFunctionBoolConstant
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													Type=STypeFunctionBoolConstant<BOOL_VALUE>;

	public:
		static constexpr bool									VALUE=BOOL_VALUE;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using															TypeFunctionTrueType=STypeFunctionBoolConstant<true>;
//----------------------------------------------------------------------------------------------------------------------
using															TypeFunctionFalseType=STypeFunctionBoolConstant<false>;
//----------------------------------------------------------------------------------------------------------------------