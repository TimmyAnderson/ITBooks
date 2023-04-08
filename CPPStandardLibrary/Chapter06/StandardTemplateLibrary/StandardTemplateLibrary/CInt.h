//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <utility>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CInt final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CInt& operator=(CInt& Value)
		{
			MValue=Value.MValue;

			std::wcout << L"COPY OPERATOR= for VALUE [" << MValue << L"] CALLED !" << std::endl;

			return(*this);
		}

		CInt& operator=(CInt&& Value)
		{
			MValue=std::move(Value.MValue);

			std::wcout << L"MOVE OPERATOR= for VALUE [" << MValue << L"] CALLED !" << std::endl;

			return(*this);
		}

		bool operator==(const CInt& Value) const
		{
			if (Value.MValue==MValue)
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
		{
		}

		CInt(int Value)
			: MValue(Value)
		{
		}

		CInt(CInt& Value)
			: MValue(Value.MValue)
		{
			std::wcout << L"COPY CONSTRUCTOR for VALUE [" << MValue << L"] CALLED !" << std::endl;
		}

		CInt(CInt&& Value)
			: MValue(std::move(Value.MValue))
		{
			std::wcout << L"MOVE CONSTRUCTOR for VALUE [" << MValue << L"] CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------