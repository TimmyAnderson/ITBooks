//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CComparisonOperators final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		bool operator==(const CComparisonOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR== CALLED !" << std::endl;

			return(MValue==Value.MValue);
		}

		bool operator!=(const CComparisonOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR!= CALLED !" << std::endl;

			return(MValue!=Value.MValue);
		}

		bool operator<(const CComparisonOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR< CALLED !" << std::endl;

			return(MValue<Value.MValue);
		}

		bool operator>(const CComparisonOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR> CALLED !" << std::endl;

			return(MValue>Value.MValue);
		}

		bool operator<=(const CComparisonOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR<= CALLED !" << std::endl;

			return(MValue<=Value.MValue);
		}

		bool operator>=(const CComparisonOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR>= CALLED !" << std::endl;

			return(MValue>=Value.MValue);
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CComparisonOperators(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline bool operator==(int Left, const CComparisonOperators& Right)
{
	std::wcout << "NON-MEMBER OPERATOR== CALLED !" << std::endl;

	return(Left==Right.GetValue());
}
//-----------------------------------------------------------------------------
inline bool operator!=(int Left, const CComparisonOperators& Right)
{
	std::wcout << "NON-MEMBER OPERATOR!= CALLED !" << std::endl;

	return(Left!=Right.GetValue());
}
//-----------------------------------------------------------------------------
inline bool operator<(int Left, const CComparisonOperators& Right)
{
	std::wcout << "NON-MEMBER OPERATOR< CALLED !" << std::endl;

	return(Left<Right.GetValue());
}
//-----------------------------------------------------------------------------
inline bool operator>(int Left, const CComparisonOperators& Right)
{
	std::wcout << "NON-MEMBER OPERATOR> CALLED !" << std::endl;

	return(Left>Right.GetValue());
}
//-----------------------------------------------------------------------------
inline bool operator<=(int Left, const CComparisonOperators& Right)
{
	std::wcout << "NON-MEMBER OPERATOR<= CALLED !" << std::endl;

	return(Left<=Right.GetValue());
}
//-----------------------------------------------------------------------------
inline bool operator>=(int Left, const CComparisonOperators& Right)
{
	std::wcout << "NON-MEMBER OPERATOR>= CALLED !" << std::endl;

	return(Left>=Right.GetValue());
}
//-----------------------------------------------------------------------------