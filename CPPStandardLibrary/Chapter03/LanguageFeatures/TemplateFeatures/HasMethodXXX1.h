//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <utility>
//-----------------------------------------------------------------------------
template <typename TType>
auto HasMethodXXX(TType Value) -> decltype(Value.XXX(),true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value;

	return(true);
}
//-----------------------------------------------------------------------------
// !!!!! Tu sa NESMIE pouzit NON-TEMPLATE FUNCTION [bool HasMethodXXX(...)], pretoze pre NON-COPYABLE TYPES (napriklad [string]) hodi GCC 4.9.3. ERROR. Preto sa pouziva VARIADIC TEMPLATE.
template <typename... TTypes>
bool HasMethodXXX(TTypes...)
{
	return(false);
}
//-----------------------------------------------------------------------------