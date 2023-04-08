//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CSubscriptOperators final
{
//-----------------------------------------------------------------------------
	private:
		std::vector<std::wstring>								MValue;

	public:
		std::wstring& operator[](size_t Index)
		{
			std::wcout << "MEMBER OPERATOR[] CALLED !" << std::endl;

			if (Index<MValue.size())
			{
				return(MValue[Index]);
			}
			else
			{
				throw(std::wstring(L"INDEX is OUT of BOUNDS !"));
			}
		}

		const std::wstring& operator[](size_t Index) const
		{
			std::wcout << "MEMBER OPERATOR[] CONST CALLED !" << std::endl;

			if (Index<MValue.size())
			{
				return(MValue[Index]);
			}
			else
			{
				throw(std::wstring(L"INDEX is OUT of BOUNDS !"));
			}
		}

	public:
		CSubscriptOperators(size_t Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------