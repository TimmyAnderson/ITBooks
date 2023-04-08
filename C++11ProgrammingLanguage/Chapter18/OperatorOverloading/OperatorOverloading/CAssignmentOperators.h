//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CAssignmentOperators final
{
//-----------------------------------------------------------------------------
	friend CAssignmentOperators& operator+=(CAssignmentOperators& Left, int Right);
	friend CAssignmentOperators& operator-=(CAssignmentOperators& Left, int Right);
	friend CAssignmentOperators& operator*=(CAssignmentOperators& Left, int Right);
	friend CAssignmentOperators& operator/=(CAssignmentOperators& Left, int Right);
	friend CAssignmentOperators& operator%=(CAssignmentOperators& Left, int Right);
	friend CAssignmentOperators& operator&=(CAssignmentOperators& Left, int Right);
	friend CAssignmentOperators& operator|=(CAssignmentOperators& Left, int Right);
	friend CAssignmentOperators& operator^=(CAssignmentOperators& Left, int Right);
	friend CAssignmentOperators& operator<<=(CAssignmentOperators& Left, int Right);
	friend CAssignmentOperators& operator>>=(CAssignmentOperators& Left, int Right);

	private:
		int														MValue;

	public:
		CAssignmentOperators& operator+=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR+= CALLED !" << std::endl;

			MValue+=Value.GetValue();

			return(*this);
		}

		CAssignmentOperators& operator-=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR-= CALLED !" << std::endl;

			MValue-=Value.GetValue();

			return(*this);
		}

		CAssignmentOperators& operator*=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR*= CALLED !" << std::endl;

			MValue*=Value.GetValue();

			return(*this);
		}

		CAssignmentOperators& operator/=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR/= CALLED !" << std::endl;

			MValue/=Value.GetValue();

			return(*this);
		}

		CAssignmentOperators& operator%=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR%= CALLED !" << std::endl;

			MValue%=Value.GetValue();

			return(*this);
		}

		CAssignmentOperators& operator&=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR&= CALLED !" << std::endl;

			MValue%=Value.GetValue();

			return(*this);
		}

		CAssignmentOperators& operator|=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR|= CALLED !" << std::endl;

			MValue|=Value.GetValue();

			return(*this);
		}

		CAssignmentOperators& operator^=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR^= CALLED !" << std::endl;

			MValue^=Value.GetValue();

			return(*this);
		}

		CAssignmentOperators& operator<<=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR<< CALLED !" << std::endl;

			MValue<<=Value.GetValue();

			return(*this);
		}

		CAssignmentOperators& operator>>=(const CAssignmentOperators& Value)
		{
			std::wcout << "MEMBER BINARY OPERATOR>>= CALLED !" << std::endl;

			MValue>>=Value.GetValue();

			return(*this);
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		explicit CAssignmentOperators(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator+=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR+= CALLED !" << std::endl;

	Left.MValue+=Right;

	return(Left);
}
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator-=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR-= CALLED !" << std::endl;

	Left.MValue-=Right;

	return(Left);
}
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator*=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR*= CALLED !" << std::endl;

	Left.MValue*=Right;

	return(Left);
}
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator/=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR/= CALLED !" << std::endl;

	Left.MValue/=Right;

	return(Left);
}
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator%=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR%= CALLED !" << std::endl;

	Left.MValue%=Right;

	return(Left);
}
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator&=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR&= CALLED !" << std::endl;

	Left.MValue&=Right;

	return(Left);
}
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator|=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR|= CALLED !" << std::endl;

	Left.MValue|=Right;

	return(Left);
}
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator^=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR^= CALLED !" << std::endl;

	Left.MValue^=Right;

	return(Left);
}
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator<<=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR<< CALLED !" << std::endl;

	Left.MValue<<=Right;

	return(Left);
}
//-----------------------------------------------------------------------------
inline CAssignmentOperators& operator>>=(CAssignmentOperators& Left, int Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR>>= CALLED !" << std::endl;

	Left.MValue>>=Right;

	return(Left);
}
//-----------------------------------------------------------------------------