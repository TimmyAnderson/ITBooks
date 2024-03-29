//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TRAIT vracia RESULT TYPE pouzitia OPERATOR [OPERATOR+].
template<typename TType1, typename TType2>
struct STypeFunctionResultOperatorPlus final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! NEVYHODOU je, ze TYPE TRAIT vyzaduje, aby mali TYPE [TType1] a TYPE [TType2] DEFAULT CONSTRUCTOR.
		using													Type=decltype(TType1()+TType2());
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
using															TypeFunctionResultOperatorPlus=typename STypeFunctionResultOperatorPlus<TType1,TType2>::Type;
//----------------------------------------------------------------------------------------------------------------------