//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <cassert>
#include <cstddef>
#include "CCompileTimeValue.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
constexpr size_t ConvertToSize(char Character)
{
	if (Character>='A' && Character<='F')
	{
		size_t													Result=(static_cast<int>(Character)-static_cast<int>('A')+10);

		return(Result);
	}
	else if (Character>='a' && Character<='f')
	{
		size_t													Result=(static_cast<int>(Character)-static_cast<int>('a')+10);

		return(Result);
	}
	else
	{
		assert(Character>='0' && Character<='9');

		size_t													Result=(static_cast<int>(Character)-static_cast<int>('0'));

		return(Result);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t SIZE>
constexpr size_t ParseSize(char const (&Array)[SIZE])
{
	int															Base=10;
	int															Offset=0;

	if (SIZE>2 && Array[0]=='0')
	{
		switch(Array[1])
		{
			case 'x':
			case 'X':
			{
				Base=16;
				Offset=2;
			}
			break;

			case 'b':
			case 'B':
			{
				Base=2;
				Offset=2;
			}
			break;

			default:
			{
				Base=8;
				Offset=1;
			}

			break;
		}
	}

	size_t														Value=0;
	size_t														Multiplier=1;

	for (size_t Index=0;Index<(SIZE-Offset);++Index)
	{
		if (Array[SIZE-1-Index]!='\'')
		{
			Value+=(ConvertToSize(Array[SIZE-1-Index])*Multiplier);
			Multiplier*=Base;
		}
	}

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<char... CHARACTERS>
constexpr auto operator"" _c()
{
	auto														Result=CCompileTimeValue<size_t,ParseSize<sizeof...(CHARACTERS)>({CHARACTERS...})>{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------