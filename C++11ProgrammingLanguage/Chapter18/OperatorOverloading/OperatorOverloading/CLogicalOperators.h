//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CLogicalOperators final
{
//-----------------------------------------------------------------------------
	private:
		bool													MValue;

	public:
		bool operator!(void)
		{
			std::wcout << "MEMBER OPERATOR! CALLED !" << std::endl;

			return(!MValue);
		}

		bool operator&&(const CLogicalOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR&& CALLED !" << std::endl;

			return(MValue && Value.MValue);
		}

		bool operator||(const CLogicalOperators& Value)
		{
			std::wcout << "MEMBER OPERATOR|| CALLED !" << std::endl;

			return(MValue || Value.MValue);
		}

	public:
		bool GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CLogicalOperators(bool Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline bool operator!(const CLogicalOperators& Value)
{
	std::wcout << "NON-MEMBER OPERATOR! CALLED !" << std::endl;

	return(!Value.GetValue());
}
//-----------------------------------------------------------------------------
inline bool operator&&(bool Left, const CLogicalOperators& Right)
{
	std::wcout << "NON-MEMBER OPERATOR&& CALLED !" << std::endl;

	return(Left && Right.GetValue());
}
//-----------------------------------------------------------------------------
inline bool operator||(bool Left, const CLogicalOperators& Right)
{
	std::wcout << "NON-MEMBER OPERATOR|| CALLED !" << std::endl;

	return(Left || Right.GetValue());
}
//-----------------------------------------------------------------------------