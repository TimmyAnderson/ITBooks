//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CCustomHashInStdNamespace
{
//-------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CCustomHashInStdNamespace& operator=(const CCustomHashInStdNamespace& Other)
		{
			wprintf_s(L"COPY OPERATOR= CALLED !\n");

			MValue=Other.MValue;

			return(*this);
		}

		CCustomHashInStdNamespace& operator=(CCustomHashInStdNamespace&& Other)
		{
			wprintf_s(L"MOVE OPERATOR= CALLED !\n");

			MValue=std::move(Other.MValue);

			return(*this);
		}

		bool operator<(const CCustomHashInStdNamespace& Other)
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
		CCustomHashInStdNamespace(void)
			: MValue(0)
		{
			wprintf_s(L"DEFAULT CONSTRUCTOR CALLED !\n");
		}

		CCustomHashInStdNamespace(int Value)
			: MValue(Value)
		{
			wprintf_s(L"CONSTRUCTOR CALLED !\n");
		}

		CCustomHashInStdNamespace(const CCustomHashInStdNamespace& Value)
			: MValue(Value.MValue)
		{
		}

		CCustomHashInStdNamespace(CCustomHashInStdNamespace&& Value)
			: MValue(std::move(Value.MValue))
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
inline std::wostream& operator<<(std::wostream& Stream, const CCustomHashInStdNamespace& Value)
{
	Stream << Value.GetValue();

	return(Stream);
}
//-------------------------------------------------------------------------------------------------------
inline bool operator==(const CCustomHashInStdNamespace& Value1, const CCustomHashInStdNamespace& Value2)
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
inline bool operator<(const CCustomHashInStdNamespace& Value1, const CCustomHashInStdNamespace& Value2)
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// HASH a EQUAL FUNCTIONS MUSIA byt definovane v NAMESPACE [std].
namespace std
{
//-------------------------------------------------------------------------------------------------------
	template<>
	struct hash<CCustomHashInStdNamespace>
	{
//-------------------------------------------------------------------------------------------------------
		bool operator()(const CCustomHashInStdNamespace& Value) const
		{
			wprintf_s(L"TEMPLATE SPECIALIZATION [hash<CCustomHashInStdNamespace>] CALLED !\n");

			return(Value.GetValue());
		}
//-------------------------------------------------------------------------------------------------------
	};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	template<>
	struct equal_to<CCustomHashInStdNamespace>
	{
//-------------------------------------------------------------------------------------------------------
		bool operator()(const CCustomHashInStdNamespace& Value1, const CCustomHashInStdNamespace& Value2) const
		{
			wprintf_s(L"TEMPLATE SPECIALIZATION [equal_to<CCustomHashInStdNamespace>] CALLED !\n");

			return(Value1.GetValue()==Value2.GetValue());
		}
//-------------------------------------------------------------------------------------------------------
	};
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------