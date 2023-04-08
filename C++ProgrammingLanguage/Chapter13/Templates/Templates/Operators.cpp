//-------------------------------------------------------------------------------------------------------
#include "Operators.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
template<typename TType>
COperators<typename TType>::COperators(TType Value)
	: MValue(Value)
{
}
//-------------------------------------------------------------------------------------------------------
template<typename TType>
COperators<typename TType>::~COperators(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
TType COperators<typename TType>::GetValue(void)
{
	return(MValue);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! CLASS TEMPLATE PARAMETERS a METHOD TEMPLATE FUNCTIONS PARAMETERS musia byt v ODDELENYCH RIADKOCH.
template<typename TType>
template<typename TConvertedType>
COperators<typename TType>::operator COperators<TConvertedType>(void)
{
	wprintf_s(L"CONVERSION OPERATOR CALLED !\n");

	return(TConvertedType(MValue));
}
//-------------------------------------------------------------------------------------------------------