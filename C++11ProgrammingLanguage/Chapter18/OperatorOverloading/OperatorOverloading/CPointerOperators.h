//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CPointerOperators final
{
//-----------------------------------------------------------------------------
	friend int& operator*(const CPointerOperators& Value);
	friend int* operator&(const CPointerOperators& Value);

	private:
		int*													MValue;

	public:
		int& operator*(void)
		{
			std::wcout << "MEMBER OPERATOR* CALLED !" << std::endl;

			return(*MValue);
		}

		int* operator&(void)
		{
			std::wcout << "MEMBER OPERATOR& CALLED !" << std::endl;

			return(MValue);
		}

	public:
		CPointerOperators(int* Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int& operator*(const CPointerOperators& Value)
{
	std::wcout << "NON-MEMBER OPERATOR* CALLED !" << std::endl;

	return(*Value.MValue);
}
//-----------------------------------------------------------------------------
int* operator&(const CPointerOperators& Value)
{
	std::wcout << "NON-MEMBER OPERATOR& CALLED !" << std::endl;

	return(Value.MValue);
}
//-----------------------------------------------------------------------------