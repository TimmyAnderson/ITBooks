//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!!!! Tento CODE funguje IBA vo VC++.
// !!!!! V G++ hodi pre PARAMETER typu [string] ERROR, pretoze TYPE [string] je NON-TRIVIALLY COPYABLE a teda NEMOZE byt pouzity ako ARGUMENT pre FUNCTION s VARIABILNYM POCTOM PARAMETERS (...).
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION TEMPLATE pouziva 2 TYPE PARAMETERS, vdaka comu aj pre ARGUMENTS (int,double) vrati TRUE.
template <typename TType1, typename TType2>
auto HasOperatorPlusVCPP(TType1 Value1, TType2 Value2) -> decltype(Value1+Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasOperatorPlusVCPP(...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION TEMPLATE pouziva 2 TYPE PARAMETERS, vdaka comu aj pre ARGUMENTS (int,double) vrati TRUE.
template <typename TType1, typename TType2>
auto HasOperatorMinusVCPP(TType1 Value1, TType2 Value2) -> decltype(Value1-Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasOperatorMinusVCPP(...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION TEMPLATE pouziva 2 TYPE PARAMETERS, vdaka comu aj pre ARGUMENTS (int,double) vrati TRUE.
template <typename TType1, typename TType2>
auto HasOperatorMultipleVCPP(TType1 Value1, TType2 Value2) -> decltype(Value1*Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasOperatorMultipleVCPP(...)
{
	return(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION TEMPLATE pouziva 2 TYPE PARAMETERS, vdaka comu aj pre ARGUMENTS (int,double) vrati TRUE.
template <typename TType1, typename TType2>
auto HasOperatorDivideVCPP(TType1 Value1, TType2 Value2) -> decltype(Value1/Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	return(true);
}
//-----------------------------------------------------------------------------
bool HasOperatorDivideVCPP(...)
{
	return(false);
}
//-------------------------------------------------------------------------------------------------------