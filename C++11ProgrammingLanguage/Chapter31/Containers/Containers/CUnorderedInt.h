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
			wprintf_s(L"COPY OPERATOR= CALLED !\n");

			MValue=Other.MValue;

			return(*this);
		}

		CUnorderedInt& operator=(CUnorderedInt&& Other)
		{
			wprintf_s(L"MOVE OPERATOR= CALLED !\n");

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
			wprintf_s(L"DEFAULT CONSTRUCTOR CALLED !\n");
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