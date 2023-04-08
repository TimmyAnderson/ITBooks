//-------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
template <typename TType>
auto HasMethodXXX(TType Value) -> decltype(Value.XXX(),true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasMethodXXX(...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TType>
auto HasMethodXXXByPointer(TType* Value) -> decltype(Value->XXX(),true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasMethodXXXByPointer(...)
{
	return(false);
}
//-----------------------------------------------------------------------------