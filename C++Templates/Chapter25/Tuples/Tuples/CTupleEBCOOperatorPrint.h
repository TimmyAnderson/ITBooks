//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
class CTupleEBCO;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintTuple(std::wostream& Stream, const CTupleEBCO<>&, bool);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
void PrintTuple(std::wostream& Stream, const CTupleEBCO<THead,TTail...>& Tuple, bool IsFirst)
{
	if (IsFirst==true)
	{
		Stream << L'(';
	}
	else
	{
		Stream << L',';
	}

	Stream << Tuple.GetHead();

	if constexpr (sizeof...(TTail)>0)
	{
		PrintTuple(Stream,Tuple.GetTail(),false);
	}
	else
	{
		Stream << L')';
	}
}
//----------------------------------------------------------------------------------------------------------------------