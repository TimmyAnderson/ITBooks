//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template <typename TType>
auto HasOperatorPlus(TType Value1, TType Value2) -> decltype(Value1+Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
bool HasOperatorPlus(TType1, TType2)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TType>
auto HasOperatorMinus(TType Value1, TType Value2) -> decltype(Value1-Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
bool HasOperatorMinus(TType1, TType2)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TType>
auto HasOperatorMultiple(TType Value1, TType Value2) -> decltype(Value1*Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
bool HasOperatorMultiple(TType1, TType2)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TType>
auto HasOperatorDivide(TType Value1, TType Value2) -> decltype(Value1/Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
bool HasOperatorDivide(TType1, TType2)
{
	return(false);
}
//-------------------------------------------------------------------------------------------------------