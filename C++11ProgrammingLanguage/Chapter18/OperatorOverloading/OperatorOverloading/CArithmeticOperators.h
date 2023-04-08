//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CArithmeticOperators final
{
//-----------------------------------------------------------------------------
	friend CArithmeticOperators& operator++(CArithmeticOperators&);
	friend CArithmeticOperators operator++(CArithmeticOperators& Value, int);
	friend CArithmeticOperators& operator--(CArithmeticOperators& Value);
	friend CArithmeticOperators operator--(CArithmeticOperators& Value, int);

	private:
		int														MValue;

	public:
		CArithmeticOperators& operator=(const CArithmeticOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR= CALLED !" << std::endl;

			MValue=Value.MValue;

			return(*this);
		}

	public:
		CArithmeticOperators operator+(void) const
		{
			std::wcout << "MEMBER UNARY OPERATOR+ CALLED !" << std::endl;

			return(MValue);
		}

		CArithmeticOperators operator-(void) const
		{
			std::wcout << "MEMBER UNARY OPERATOR- CALLED !" << std::endl;

			return(-MValue);
		}

	public:
		CArithmeticOperators operator+(const CArithmeticOperators& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR+ CALLED !" << std::endl;

			return(MValue+Value.MValue);
		}

		CArithmeticOperators operator-(const CArithmeticOperators& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR- CALLED !" << std::endl;

			return(MValue-Value.MValue);
		}

		CArithmeticOperators operator*(const CArithmeticOperators& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR* CALLED !" << std::endl;

			return(MValue*Value.MValue);
		}

		CArithmeticOperators operator/(const CArithmeticOperators& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR/ CALLED !" << std::endl;

			return(MValue/Value.MValue);
		}

		CArithmeticOperators operator%(const CArithmeticOperators& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR% CALLED !" << std::endl;

			return(MValue%Value.MValue);
		}

	public:
		CArithmeticOperators& operator++(void)
		{
			std::wcout << "MEMBER UNARY PREFIX OPERATOR++ CALLED !" << std::endl;

			MValue++;

			return(*this);
		}

		CArithmeticOperators operator++(int)
		{
			std::wcout << "MEMBER UNARY POSTFIX OPERATOR++ CALLED !" << std::endl;

			return(MValue++);
		}

		CArithmeticOperators& operator--(void)
		{
			std::wcout << "MEMBER UNARY PREFIX OPERATOR-- CALLED !" << std::endl;

			MValue--;

			return(*this);
		}

		CArithmeticOperators operator--(int)
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
		CArithmeticOperators(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// FUNCTION je UMYSELNE ZAKOMENTOVANA, pretoze inak by doslo ku kolizii s METHOD.
/*
inline CArithmeticOperators operator+(const CArithmeticOperators& Value)
{
	std::wcout << "NON-MEMBER UNARY OPERATOR+ CALLED !" << std::endl;

	return(Value.GetValue());
}
*/
//-----------------------------------------------------------------------------
// FUNCTION je UMYSELNE ZAKOMENTOVANA, pretoze inak by doslo ku kolizii s METHOD.
/*
inline CArithmeticOperators operator-(const CArithmeticOperators& Value)
{
	std::wcout << "NON-MEMBER UNARY OPERATOR- CALLED !" << std::endl;

	return(-Value.GetValue());
}
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline CArithmeticOperators operator+(int Left, const CArithmeticOperators& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR+ CALLED !" << std::endl;

	return(Left+Right.GetValue());
}
//-----------------------------------------------------------------------------
inline CArithmeticOperators operator-(int Left, const CArithmeticOperators& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR- CALLED !" << std::endl;

	return(Left-Right.GetValue());
}
//-----------------------------------------------------------------------------
inline CArithmeticOperators operator*(int Left, const CArithmeticOperators& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR* CALLED !" << std::endl;

	return(Left*Right.GetValue());
}
//-----------------------------------------------------------------------------
inline CArithmeticOperators operator/(int Left, const CArithmeticOperators& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR/ CALLED !" << std::endl;

	return(Left/Right.GetValue());
}
//-----------------------------------------------------------------------------
inline CArithmeticOperators operator%(int Left, const CArithmeticOperators& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR% CALLED !" << std::endl;

	return(Left%Right.GetValue());
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline CArithmeticOperators& operator++(CArithmeticOperators& Value)
{
	std::wcout << "NON-MEMBER UNARY PREFIX OPERATOR++ CALLED !" << std::endl;

	Value.MValue++;

	return(Value);
}
//-----------------------------------------------------------------------------
inline CArithmeticOperators operator++(CArithmeticOperators& Value, int)
{
	std::wcout << "NON-MEMBER UNARY POSTFIX OPERATOR++ CALLED !" << std::endl;

	return(Value.MValue++);
}
//-----------------------------------------------------------------------------
inline CArithmeticOperators& operator--(CArithmeticOperators& Value)
{
	std::wcout << "NON-MEMBER UNARY PREFIX OPERATOR-- CALLED !" << std::endl;

	Value.MValue--;

	return(Value);
}
//-----------------------------------------------------------------------------
inline CArithmeticOperators operator--(CArithmeticOperators& Value, int)
{
	std::wcout << "NON-MEMBER UNARY POSTFIX OPERATOR-- CALLED !" << std::endl;

	return(Value.MValue--);
}
//-----------------------------------------------------------------------------