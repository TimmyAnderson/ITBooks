#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline unsigned long long int operator""_THOUSANDS(unsigned long long int Value)
{
	std::wcout << "MEMBER OPERATOR\"\" CALLED !" << std::endl;

    return(Value*1000);
}
//-----------------------------------------------------------------------------
inline long double operator""_DOUBLE_THOUSANDS(long double Value)
{
	std::wcout << "MEMBER OPERATOR\"\" CALLED !" << std::endl;

    return(Value*1000.0);
}
//-----------------------------------------------------------------------------