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
			std::wcout << L"COPY OPERATOR= for VALUE [" << Other.MValue << L"] CALLED !" << std::endl;

			MValue=Other.MValue;

			return(*this);
		}

		CInt& operator=(CInt&& Other)
		{
			std::wcout << L"MOVE OPERATOR= for VALUE [" << Other.MValue << L"] CALLED !" << std::endl;

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
		}

		CInt(int Value)
			: MValue(Value)
		{
		}

		CInt(const CInt& Value)
			: MValue(Value.MValue)
		{
			std::wcout << L"COPY CONSTRUCTOR for VALUE [" << Value.MValue << L"] CALLED !" << std::endl;
		}

		CInt(CInt&& Value)
			: MValue(std::move(Value.MValue))
		{
			std::wcout << L"MOVE CONSTRUCTOR for VALUE [" << Value.MValue << L"] CALLED !" << std::endl;
		}

		~CInt(void)
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