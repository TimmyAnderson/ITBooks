//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CCaseInsensitiveCharacterTraits : public std::char_traits<wchar_t>
{
//-----------------------------------------------------------------------------
	public:
		static bool eq(const wchar_t& Character1, const wchar_t& Character2);
		static bool lt(const wchar_t& Character1, const wchar_t& Character2);
		static int compare(const wchar_t* String1, const wchar_t* String2, std::size_t Count);
		static const wchar_t* find(const wchar_t* String, std::size_t Count, const wchar_t& Character);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using															CWideStringCaseInsensitive=std::basic_string<wchar_t,CCaseInsensitiveCharacterTraits>;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::wostream& operator<<(std::wostream& Stream, const CWideStringCaseInsensitive& String);
//-----------------------------------------------------------------------------