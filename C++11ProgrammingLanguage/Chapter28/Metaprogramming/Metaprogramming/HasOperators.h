//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!!!! C++ vygeneruje FUNCTION IBA AK OPERACIA [Value1+Value2] je VALIDNA. Ak nie je, tak COMPILER hodi ERROR, ale kedze sa aplikuje princip SFINAE, tak C++ tuto chybu IGNORUJE a hlada inu OVERLOADED VERZIU tejto FUNCTION.
template <typename TType1, typename TType2>
auto HasOperatorPlus(TType1 Value1, TType2 Value2) -> decltype(Value1+Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
// !!! CATCH-ALL FUNCTION. Tuto FUNCTION COMPILER pouzije IBA vtedy, ak 1. OVERLOADED VERZIU tejto FUNCTION NEMOZE POUZIT.
// !!!!! Tu sa NESMIE pouzit NON-TEMPLATE FUNCTION [bool HasOperatorPlus(...)], pretoze pre NON-COPYABLE TYPES (napriklad [string]) hodi GCC 4.9.3. ERROR. Preto sa pouziva VARIADIC TEMPLATE.
template <typename ...TTypes>
bool HasOperatorPlus(TTypes...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! C++ vygeneruje FUNCTION IBA AK OPERACIA [Value1-Value2] je VALIDNA. Ak nie je, tak COMPILER hodi ERROR, ale kedze sa aplikuje princip SFINAE, tak C++ tuto chybu IGNORUJE a hlada inu OVERLOADED VERZIU tejto FUNCTION.
template <typename TType1, typename TType2>
auto HasOperatorMinus(TType1 Value1, TType2 Value2) -> decltype(Value1-Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
// !!! CATCH-ALL FUNCTION. Tuto FUNCTION COMPILER pouzije IBA vtedy, ak 1. OVERLOADED VERZIU tejto FUNCTION NEMOZE POUZIT.
// !!!!! Tu sa NESMIE pouzit NON-TEMPLATE FUNCTION [bool HasOperatorMinus(...)], pretoze pre NON-COPYABLE TYPES (napriklad [string]) hodi GCC 4.9.3. ERROR. Preto sa pouziva VARIADIC TEMPLATE.
template <typename ...TTypes>
bool HasOperatorMinus(TTypes...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! C++ vygeneruje FUNCTION IBA AK OPERACIA [Value1*Value2] je VALIDNA. Ak nie je, tak COMPILER hodi ERROR, ale kedze sa aplikuje princip SFINAE, tak C++ tuto chybu IGNORUJE a hlada inu OVERLOADED VERZIU tejto FUNCTION.
template <typename TType1, typename TType2>
auto HasOperatorMultiple(TType1 Value1, TType2 Value2) -> decltype(Value1*Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
// !!! CATCH-ALL FUNCTION. Tuto FUNCTION COMPILER pouzije IBA vtedy, ak 1. OVERLOADED VERZIU tejto FUNCTION NEMOZE POUZIT.
// !!!!! Tu sa NESMIE pouzit NON-TEMPLATE FUNCTION [bool HasOperatorMultiple(...)], pretoze pre NON-COPYABLE TYPES (napriklad [string]) hodi GCC 4.9.3. ERROR. Preto sa pouziva VARIADIC TEMPLATE.
template <typename ...TTypes>
bool HasOperatorMultiple(TTypes...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! C++ vygeneruje FUNCTION IBA AK OPERACIA [Value1/Value2] je VALIDNA. Ak nie je, tak COMPILER hodi ERROR, ale kedze sa aplikuje princip SFINAE, tak C++ tuto chybu IGNORUJE a hlada inu OVERLOADED VERZIU tejto FUNCTION.
template <typename TType1, typename TType2>
auto HasOperatorDivide(TType1 Value1, TType2 Value2) -> decltype(Value1/Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
// !!! CATCH-ALL FUNCTION. Tuto FUNCTION COMPILER pouzije IBA vtedy, ak 1. OVERLOADED VERZIU tejto FUNCTION NEMOZE POUZIT.
// !!!!! Tu sa NESMIE pouzit NON-TEMPLATE FUNCTION [bool HasOperatorDivide(...)], pretoze pre NON-COPYABLE TYPES (napriklad [string]) hodi GCC 4.9.3. ERROR. Preto sa pouziva VARIADIC TEMPLATE.
template <typename ...TTypes>
bool HasOperatorDivide(TTypes...)
{
	return(false);
}
//-------------------------------------------------------------------------------------------------------