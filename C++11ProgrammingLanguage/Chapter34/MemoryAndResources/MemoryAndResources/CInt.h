//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CInt
{
//-------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CInt& operator=(const CInt& Other)
		{
			wprintf_s(L"COPY OPERATOR= CALLED !\n");

			MValue=Other.MValue;

			return(*this);
		}

		CInt& operator=(CInt&& Other)
		{
			wprintf_s(L"MOVE OPERATOR= CALLED !\n");

			MValue=std::move(Other.MValue);

			return(*this);
		}

		bool operator<(const CInt& Other)
		{
			if (MValue<Other.MValue)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}

	public:
		int GetValue(void) const
		{
			return(MValue);
		}

	public:
		CInt(void)
			: MValue(0)
		{
			wprintf_s(L"DEFAULT CONSTRUCTOR CALLED !\n");
		}

		CInt(int Value)
			: MValue(Value)
		{
			wprintf_s(L"CONSTRUCTOR CALLED !\n");
		}

		CInt(const CInt& Value)
			: MValue(Value.MValue)
		{
		}

		CInt(CInt&& Value)
			: MValue(std::move(Value.MValue))
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
inline std::wostream& operator<<(std::wostream& Stream, const CInt& Value)
{
	Stream << Value.GetValue();

	return(Stream);
}
//-------------------------------------------------------------------------------------------------------
inline bool operator==(const CInt& Value1, const CInt& Value2)
{
	if (Value1.GetValue()==Value2.GetValue())
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------
inline bool operator<(const CInt& Value1, const CInt& Value2)
{
	if (Value1.GetValue()<Value2.GetValue())
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------