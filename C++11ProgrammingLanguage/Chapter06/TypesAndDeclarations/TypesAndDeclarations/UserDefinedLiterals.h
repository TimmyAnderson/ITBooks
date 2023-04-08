//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int operator""_I1(unsigned long long int Value)
{
	//std::wcout << "OPERATOR\"\"_I1 with PARAMETER [unsigned long long int] CALLED !" << std::endl;

	return(static_cast<int>(Value));
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Pretoze sa NENASIEL LITERAL OPERATOR s PARAMETER [unsigned long long int], pouzil sa FALLBACK LITERAL OPERATOR s PARAMETER [const char*].
int operator""_I2(const char* Value)
{
	//std::wcout << "OPERATOR\"\"_I2 with PARAMETER [const char* Value] CALLED !" << std::endl;

	return(std::stoi(Value));
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int ConvertToInt(char Character)
{
	int															Value=static_cast<int>(Character-'0');

	return(Value);
}
//-----------------------------------------------------------------------------
template<typename... TCharacters>
int ConvertToInt(char Character, TCharacters... Characters)
{
	int															Value=static_cast<int>(Character-'0');
	int															TailValue=ConvertToInt(Characters...);
	int															Multiplier=1;
	std::size_t													Size=sizeof...(Characters);
	
	for(std::size_t Index=0;Index<Size;Index++)
	{
		Multiplier*=10;
	}

	int															Result=Multiplier*Value+TailValue;

	return(Result);
}
//-----------------------------------------------------------------------------
// !!! Pretoze sa NENASIEL LITERAL OPERATOR s PARAMETER [unsigned long long int], pouzil sa FALLBACK LITERAL OPERATOR TEMPLATE FUNCTION.
// !!! LITERAL OPERATOR TEMPLATE FUNCTION NESMIE mat ZIADNE PARAMETERS a moze mat iba 1 TYPE PARAMETER [char...].
template<char... TCharacters>
int operator""_I3(void)
{
	//std::wcout << "TEMPLATE OPERATOR\"\"_I3 CALLED !" << std::endl;

	return(ConvertToInt(TCharacters...));
}
//-----------------------------------------------------------------------------
// !!! Pretoze sa NENASIEL LITERAL OPERATOR s PARAMETER [unsigned long long int], pouzil sa FALLBACK LITERAL OPERATOR TEMPLATE FUNCTION.
// !!! LITERAL OPERATOR TEMPLATE FUNCTION NESMIE mat ZIADNE PARAMETERS a moze mat iba 1 TYPE PARAMETER [char...].
template<char... TCharacters>
int operator"" _i4(void)
{
	//std::wcout << "TEMPLATE OPERATOR\"\" _i4 CALLED !" << std::endl;

	return(ConvertToInt(TCharacters...));
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
double operator""_F(long double Value)
{
	//std::wcout << "OPERATOR\"\"_F with PARAMETER [long double] CALLED !" << std::endl;

	return(static_cast<double>(Value));
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wchar_t operator""_C(wchar_t Value)
{
	//std::wcout << "OPERATOR\"\"_C with PARAMETER [wchar_t] CALLED !" << std::endl;

	return(Value);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::wstring operator""_S(const wchar_t* Value, std::size_t Size)
{
	std::wcout << "OPERATOR\"\"_S with PARAMETERS [const wchar_t* Value, size_t Size] CALLED ! VALUE [" << Value << L"] SIZE [" << Size << L"] !" << std::endl;

	return(Value);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Ak sa MEDZI KEYWORD [operator""] a IDENTIFIER nachadza MEDZERA, potom IDENTIFIER NEMOZE za znakom '_' obsahovat VELKE PISMENO.
int operator"" _i(unsigned long long int Value)
{
	//std::wcout << "OPERATOR\"\" _i with PARAMETER [unsigned long long int] CALLED !" << std::endl;

	return(static_cast<int>(Value));
}
//-----------------------------------------------------------------------------