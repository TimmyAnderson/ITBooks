//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CIncrementDecrementOperators final
{
//-----------------------------------------------------------------------------
	friend CIncrementDecrementOperators& operator++(CIncrementDecrementOperators&);
	friend CIncrementDecrementOperators operator++(CIncrementDecrementOperators& Value, int);
	friend CIncrementDecrementOperators& operator--(CIncrementDecrementOperators& Value);
	friend CIncrementDecrementOperators operator--(CIncrementDecrementOperators& Value, int);

	private:
		int														MValue;

	public:
		CIncrementDecrementOperators& operator++(void)
		{
			std::wcout << "MEMBER UNARY PREFIX OPERATOR++ CALLED !" << std::endl;

			MValue++;

			return(*this);
		}

		CIncrementDecrementOperators operator++(int)
		{
			std::wcout << "MEMBER UNARY POSTFIX OPERATOR++ CALLED !" << std::endl;

			return(MValue++);
		}

		CIncrementDecrementOperators& operator--(void)
		{
			std::wcout << "MEMBER UNARY PREFIX OPERATOR-- CALLED !" << std::endl;

			MValue--;

			return(*this);
		}

		CIncrementDecrementOperators operator--(int)
		{
			std::wcout << "MEMBER UNARY POSTFIX OPERATOR-- CALLED !" << std::endl;

			return(MValue--);
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CIncrementDecrementOperators(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline CIncrementDecrementOperators& operator++(CIncrementDecrementOperators& Value)
{
	std::wcout << "NON-MEMBER UNARY PREFIX OPERATOR++ CALLED !" << std::endl;

	Value.MValue++;

	return(Value);
}
//-----------------------------------------------------------------------------
inline CIncrementDecrementOperators operator++(CIncrementDecrementOperators& Value, int)
{
	std::wcout << "NON-MEMBER UNARY POSTFIX OPERATOR++ CALLED !" << std::endl;

	return(Value.MValue++);
}
//-----------------------------------------------------------------------------
inline CIncrementDecrementOperators& operator--(CIncrementDecrementOperators& Value)
{
	std::wcout << "NON-MEMBER UNARY PREFIX OPERATOR-- CALLED !" << std::endl;

	Value.MValue--;

	return(Value);
}
//-----------------------------------------------------------------------------
inline CIncrementDecrementOperators operator--(CIncrementDecrementOperators& Value, int)
{
	std::wcout << "NON-MEMBER UNARY POSTFIX OPERATOR-- CALLED !" << std::endl;

	return(Value.MValue--);
}
//-----------------------------------------------------------------------------