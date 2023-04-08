//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTION vyzaduje, aby mal TYPE [TIterator] definovany OPERATOR*, OPERATOR++ a OPERATOR!=.
// !!! TEMPLATE FUNCTION vyzaduje, aby TYPE [TOperation] bol FUNCTOR, ktory ma 2 PARAMETERS typu TValue.
template<typename TIterator, typename TValue, typename TOperation>
TValue Accumulate(TIterator Begin, TIterator End, TValue Value, TOperation Operation)
{
	while(Begin!=End)
	{
		Value=Operation(Value,*Begin);
		Begin++;
	}

	return(Value);
}
//-----------------------------------------------------------------------------