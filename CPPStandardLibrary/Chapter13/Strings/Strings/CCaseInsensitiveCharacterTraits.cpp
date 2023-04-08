//-------------------------------------------------------------------------------------------------------
#include "CCaseInsensitiveCharacterTraits.h"
#include <cctype>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
wostream& operator<<(wostream& Stream, const CWideStringCaseInsensitive& String)
{
	Stream << wstring(String.data(),String.length());

	return(Stream);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
bool CCaseInsensitiveCharacterTraits::eq(const wchar_t& Character1, const wchar_t& Character2)
{
	return(toupper(Character1)==toupper(Character2));
}
//-------------------------------------------------------------------------------------------------------
bool CCaseInsensitiveCharacterTraits::lt(const wchar_t& Character1, const wchar_t& Character2)
{
	return(toupper(Character1)<toupper(Character2));
}
//-------------------------------------------------------------------------------------------------------
int CCaseInsensitiveCharacterTraits::compare(const wchar_t* String1, const wchar_t* String2, size_t Count)
{
	for(size_t Index=0;Index<Count;++Index)
	{
		if (eq(String1[Index],String2[Index])==false)
		{
			return(lt(String1[Index],String2[Index]) ? -1 : 1);
		}
	}

	return(0);
}
//-------------------------------------------------------------------------------------------------------
const wchar_t* CCaseInsensitiveCharacterTraits::find(const wchar_t* String, size_t Count, const wchar_t& Character)
{
	for(size_t Index=0;Index<Count;++Index)
	{
		if (eq(String[Index],Character)!=0)
		{
			return&(String[Index]);
		}
	}

	return(0);
}
//-------------------------------------------------------------------------------------------------------