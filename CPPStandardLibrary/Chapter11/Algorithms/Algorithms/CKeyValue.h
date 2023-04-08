//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CKeyValue
{
//-------------------------------------------------------------------------------------------------------
	private:
		int														MKey;
		int														MValue;

	public:
		bool operator<(const CKeyValue& Other)
		{
			if (MKey<Other.MKey)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}

	public:
		int GetKey(void) const
		{
			return(MKey);
		}

		int GetValue(void) const
		{
			return(MValue);
		}

	public:
		CKeyValue(void)
			: MKey(0), MValue(0)
		{
		}

		CKeyValue(int Key, int Value)
			: MKey(Key), MValue(Value)
		{
		}

		~CKeyValue(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
inline std::wostream& operator<<(std::wostream& Stream, const CKeyValue& Value)
{
	Stream << L"(";
	Stream << Value.GetKey();
	Stream << L",";
	Stream << Value.GetValue();
	Stream << L")";

	return(Stream);
}
//-------------------------------------------------------------------------------------------------------
inline bool operator==(const CKeyValue& Value1, const CKeyValue& Value2)
{
	if (Value1.GetKey()==Value2.GetKey())
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------
inline bool operator<(const CKeyValue& Value1, const CKeyValue& Value2)
{
	if (Value1.GetKey()<Value2.GetKey())
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------