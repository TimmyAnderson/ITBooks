//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class COperatorOverloading final
{
//-----------------------------------------------------------------------------
	friend COperatorOverloading& operator++(COperatorOverloading&);
	friend COperatorOverloading operator++(COperatorOverloading& Value, int);
	friend COperatorOverloading& operator--(COperatorOverloading& Value);
	friend COperatorOverloading operator--(COperatorOverloading& Value, int);

	private:
		int														MValue;

	public:
		COperatorOverloading& operator=(const COperatorOverloading& Value)
		{
			std::wcout << "MEMBER OPERATOR= CALLED !" << std::endl;

			MValue=Value.MValue;

			return(*this);
		}

	public:
		COperatorOverloading operator+(void) const
		{
			std::wcout << "MEMBER UNARY OPERATOR+ CALLED !" << std::endl;

			return(MValue);
		}

		COperatorOverloading operator-(void) const
		{
			std::wcout << "MEMBER UNARY OPERATOR- CALLED !" << std::endl;

			return(-MValue);
		}

	public:
		COperatorOverloading operator+(const COperatorOverloading& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR+ CALLED !" << std::endl;

			return(MValue+Value.MValue);
		}

		COperatorOverloading operator-(const COperatorOverloading& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR- CALLED !" << std::endl;

			return(MValue-Value.MValue);
		}

		COperatorOverloading operator*(const COperatorOverloading& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR* CALLED !" << std::endl;

			return(MValue*Value.MValue);
		}

		COperatorOverloading operator/(const COperatorOverloading& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR/ CALLED !" << std::endl;

			return(MValue/Value.MValue);
		}

		COperatorOverloading operator%(const COperatorOverloading& Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR% CALLED !" << std::endl;

			return(MValue%Value.MValue);
		}

	public:
		COperatorOverloading& operator++(void)
		{
			std::wcout << "MEMBER UNARY PREFIX OPERATOR++ CALLED !" << std::endl;

			MValue++;

			return(*this);
		}

		COperatorOverloading operator++(int)
		{
			std::wcout << "MEMBER UNARY POSTFIX OPERATOR++ CALLED !" << std::endl;

			return(MValue++);
		}

		COperatorOverloading& operator--(void)
		{
			std::wcout << "MEMBER UNARY PREFIX OPERATOR-- CALLED !" << std::endl;

			MValue--;

			return(*this);
		}

		COperatorOverloading operator--(int)
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
		COperatorOverloading(int Value)
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
inline COperatorOverloading operator+(const COperatorOverloading& Value)
{
	std::wcout << "NON-MEMBER UNARY OPERATOR+ CALLED !" << std::endl;

	return(Value.GetValue());
}
*/
//-----------------------------------------------------------------------------
// FUNCTION je UMYSELNE ZAKOMENTOVANA, pretoze inak by doslo ku kolizii s METHOD.
/*
inline COperatorOverloading operator-(const COperatorOverloading& Value)
{
	std::wcout << "NON-MEMBER UNARY OPERATOR- CALLED !" << std::endl;

	return(-Value.GetValue());
}
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline COperatorOverloading operator+(int Left, const COperatorOverloading& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR+ CALLED !" << std::endl;

	return(Left+Right.GetValue());
}
//-----------------------------------------------------------------------------
inline COperatorOverloading operator-(int Left, const COperatorOverloading& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR- CALLED !" << std::endl;

	return(Left-Right.GetValue());
}
//-----------------------------------------------------------------------------
inline COperatorOverloading operator*(int Left, const COperatorOverloading& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR* CALLED !" << std::endl;

	return(Left*Right.GetValue());
}
//-----------------------------------------------------------------------------
inline COperatorOverloading operator/(int Left, const COperatorOverloading& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR/ CALLED !" << std::endl;

	return(Left/Right.GetValue());
}
//-----------------------------------------------------------------------------
inline COperatorOverloading operator%(int Left, const COperatorOverloading& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR% CALLED !" << std::endl;

	return(Left%Right.GetValue());
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline COperatorOverloading& operator++(COperatorOverloading& Value)
{
	std::wcout << "NON-MEMBER UNARY PREFIX OPERATOR++ CALLED !" << std::endl;

	Value.MValue++;

	return(Value);
}
//-----------------------------------------------------------------------------
inline COperatorOverloading operator++(COperatorOverloading& Value, int)
{
	std::wcout << "NON-MEMBER UNARY POSTFIX OPERATOR++ CALLED !" << std::endl;

	return(Value.MValue++);
}
//-----------------------------------------------------------------------------
inline COperatorOverloading& operator--(COperatorOverloading& Value)
{
	std::wcout << "NON-MEMBER UNARY PREFIX OPERATOR-- CALLED !" << std::endl;

	Value.MValue--;

	return(Value);
}
//-----------------------------------------------------------------------------
inline COperatorOverloading operator--(COperatorOverloading& Value, int)
{
	std::wcout << "NON-MEMBER UNARY POSTFIX OPERATOR-- CALLED !" << std::endl;

	return(Value.MValue--);
}
//-----------------------------------------------------------------------------