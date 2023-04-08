//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <sstream>
//-----------------------------------------------------------------------------
class CPerson final
{
//-----------------------------------------------------------------------------
	friend inline std::wistream& operator>>(std::wistream& Stream, CPerson& Value);

	private:
		std::wstring											MName;
		int														MAge;

	public:
		std::wstring ToString(void) const noexcept
		{
			std::wstring										Text;

			Text+=L"{";
			Text+=MName;
			Text+=L" ";

			std::wstringstream									Stream;

			Stream << MAge;

			Text+=Stream.str();

			Text+=L"}";

			return(Text);
		}

	public:
		const std::wstring& GetName(void) const noexcept
		{
			return(MName);
		}

		int GetAge(void) const noexcept
		{
			return(MAge);
		}

	public:
		CPerson(void)
			: MName(), MAge(0)
		{
		}

		CPerson(const std::wstring& Name, int Age)
			: MName(Name), MAge(Age)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline std::wostream& operator<<(std::wostream& Stream, const CPerson& Value)
{
	Stream << L'{';
	Stream << Value.GetName().c_str();
	Stream << L' ';
	Stream << Value.GetAge();
	Stream << L'}';

	return(Stream);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline std::wistream& operator>>(std::wistream& Stream, CPerson& Value)
{
	if ((!Stream)==true)
	{
		return(Stream);
	}

	wchar_t														OpenBracket;

	Stream >> OpenBracket;

	if (OpenBracket!=L'{')
	{
		Stream.setstate(std::ios_base::badbit);
	}

	if ((!Stream)==true)
	{
		return(Stream);
	}

	Stream >> Value.MName;

	if ((!Stream)==true)
	{
		return(Stream);
	}

	Stream >> Value.MAge;

	if ((!Stream)==true)
	{
		return(Stream);
	}

	wchar_t														CloseBracket;

	Stream >> CloseBracket;

	if (CloseBracket!=L'}')
	{
		Stream.setstate(std::ios_base::badbit);
	}

	if ((!Stream)==true)
	{
		return(Stream);
	}

	return(Stream);
}
//-----------------------------------------------------------------------------