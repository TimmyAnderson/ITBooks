//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CUnorderedInt
{
//-------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CUnorderedInt& operator=(const CUnorderedInt& Other)
		{
			std::wcout << L"COPY OPERATOR= CALLED !" << std::endl;

			MValue=Other.MValue;

			return(*this);
		}

		CUnorderedInt& operator=(CUnorderedInt&& Other)
		{
			std::wcout << L"MOVE OPERATOR= CALLED !" << std::endl;

			MValue=std::move(Other.MValue);

			return(*this);
		}

	public:
		int GetValue(void) const
		{
			return(MValue);
		}

	public:
		CUnorderedInt(void)
			: MValue(0)
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
		}

		CUnorderedInt(int Value)
			: MValue(Value)
		{
		}

		CUnorderedInt(const CUnorderedInt& Value)
			: MValue(Value.MValue)
		{
		}

		CUnorderedInt(CUnorderedInt&& Value)
			: MValue(std::move(Value.MValue))
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
inline std::wostream& operator<<(std::wostream& Stream, CUnorderedInt Value)
{
	Stream << Value.GetValue();

	return(Stream);
}
//-------------------------------------------------------------------------------------------------------
inline bool operator==(const CUnorderedInt& Object1, const CUnorderedInt& Object2)
{
	if (Object1.GetValue()==Object2.GetValue())
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------