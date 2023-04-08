//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
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
			std::wcout << L"COPY OPERATOR= CALLED !" << std::endl;

			MValue=Other.MValue;

			return(*this);
		}

		CInt& operator=(CInt&& Other)
		{
			std::wcout << L"MOVE OPERATOR= CALLED !" << std::endl;

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
			std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
		}

		CInt(int Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CALLED !" << std::endl;
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