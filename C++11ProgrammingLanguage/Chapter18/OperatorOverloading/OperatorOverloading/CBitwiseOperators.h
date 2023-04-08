//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CBitwiseOperators final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CBitwiseOperators operator~(void)
		{
			std::wcout << "MEMBER OPERATOR~ CALLED !" << std::endl;

			return(CBitwiseOperators(~MValue));
		}

		CBitwiseOperators operator&(const CBitwiseOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR& CALLED !" << std::endl;

			return(CBitwiseOperators(MValue & Value.GetValue()));
		}

		CBitwiseOperators operator|(const CBitwiseOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR| CALLED !" << std::endl;

			return(CBitwiseOperators(MValue | Value.GetValue()));
		}

		CBitwiseOperators operator^(const CBitwiseOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR^ CALLED !" << std::endl;

			return(CBitwiseOperators(MValue ^ Value.GetValue()));
		}

		CBitwiseOperators operator<<(const CBitwiseOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR<< CALLED !" << std::endl;

			return(CBitwiseOperators(MValue << Value.GetValue()));
		}

		CBitwiseOperators operator>>(const CBitwiseOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR>> CALLED !" << std::endl;

			return(CBitwiseOperators(MValue >> Value.GetValue()));
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		explicit CBitwiseOperators(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline CBitwiseOperators operator~(const CBitwiseOperators& Value)
{
	std::wcout << "NON-MEMBER OPERATOR~ CALLED !" << std::endl;

	return(CBitwiseOperators(~Value.GetValue()));
}
//-----------------------------------------------------------------------------
inline CBitwiseOperators operator&(const CBitwiseOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER OPERATOR& CALLED !" << std::endl;

	return(CBitwiseOperators(Left.GetValue() & Right));
}
//-----------------------------------------------------------------------------
inline CBitwiseOperators operator|(const CBitwiseOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER OPERATOR| CALLED !" << std::endl;

	return(CBitwiseOperators(Left.GetValue() | Right));
}
//-----------------------------------------------------------------------------
inline CBitwiseOperators operator^(const CBitwiseOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER OPERATOR^ CALLED !" << std::endl;

	return(CBitwiseOperators(Left.GetValue() ^ Right));
}
//-----------------------------------------------------------------------------
inline CBitwiseOperators operator<<(const CBitwiseOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER OPERATOR<< CALLED !" << std::endl;

	return(CBitwiseOperators(Left.GetValue() << Right));
}
//-----------------------------------------------------------------------------
inline CBitwiseOperators operator>>(const CBitwiseOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER OPERATOR>> CALLED !" << std::endl;

	return(CBitwiseOperators(Left.GetValue() >> Right));
}
//-----------------------------------------------------------------------------