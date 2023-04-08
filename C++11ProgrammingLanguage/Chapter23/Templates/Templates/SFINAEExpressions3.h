//-------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
// !!!!! C++ (aspon G++) NEMUMOZNUJE pouzit FUNCTION s VARIABILNYM POCTOM PARAMETERS (...) pre CLASS [string]. COMPILER vyhlasi, ze tento TYPE je NON-TRIVIALLY COPYABLE a teda NEMOZE byt pouzity ako ARGUMENT pre FUNCTION s VARIABILNYM POCTOM PARAMETERS (...).
// !!!!! Riesenim ako implementovat FUNCTION TEMPLATE, ktora identifikuje ci pre TYPE je definovany dany OPERATOR je definovat TEMPLATE FUNCTION, ktora prenasa POINTER. Ten G++ dokaze preniest do FUNCTION s VARIABILNYM POCTOM PARAMETERS (...). Takto je mozne implementovat TEMPLATE FUNCTION, ktora otestuje ci TYPE preneseny ako POINTER ma, alebo nema definovany dany OPERATOR.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
auto HasOperatorPlusByPointer(TType1* Value1, TType2* Value2) -> decltype(*Value1+*Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasOperatorPlusByPointer(...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
auto HasOperatorMinusByPointer(TType1* Value1, TType2* Value2) -> decltype(*Value1-*Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasOperatorMinusByPointer(...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
auto HasOperatorMultipleByPointer(TType1* Value1, TType2* Value2) -> decltype(*Value1**Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasOperatorMultipleByPointer(...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
auto HasOperatorDivideByPointer(TType1* Value1, TType2* Value2) -> decltype(*Value1/ *Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasOperatorDivideByPointer(...)
{
	return(false);
}
//-----------------------------------------------------------------------------