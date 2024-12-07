#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "ELogLevel.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define MY_TAG 'XGAT'
#define COMPONENT_ID DPFLTR_IHVDRIVER_ID
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#if !defined(MACRO_VARIABLE_TO_STRING)
#define MACRO_VARIABLE_TO_STRING(Variable) (void(Variable),#Variable)
#endif
//----------------------------------------------------------------------------------------------------------------------
#if !defined(MACRO_FUNCTION_TO_STRING)
#define MACRO_FUNCTION_TO_STRING(Function) (void(&Function),#Function)
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
ULONG Log(ULONG ComponentID, ELogLevel Level, PCSTR Format, TTypes... Values)
{
	ULONG														Result=DbgPrintEx(ComponentID,static_cast<ULONG>(Level),Format,Values...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
ULONG Log(ELogLevel Level, PCSTR Format, TTypes... Values)
{
	ULONG														Result=DbgPrintEx(COMPONENT_ID,static_cast<ULONG>(Level),Format,Values...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
ULONG LogError(PCSTR Format, TTypes... Values)
{
	ULONG														Result=Log(ELogLevel::E_ERROR,Format,Values...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
ULONG LogWarning(PCSTR Format, TTypes... Values)
{
	ULONG														Result=Log(ELogLevel::E_WARNING,Format,Values...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
ULONG LogInformation(PCSTR Format, TTypes... Values)
{
	ULONG														Result=Log(ELogLevel::E_INFORMATION,Format,Values...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
ULONG LogDebug(PCSTR Format, TTypes... Values)
{
	ULONG														Result=Log(ELogLevel::E_DEBUG,Format,Values...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
ULONG LogVerbose(PCSTR Format, TTypes... Values)
{
	ULONG														Result=Log(ELogLevel::E_VERBOSE,Format,Values...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------