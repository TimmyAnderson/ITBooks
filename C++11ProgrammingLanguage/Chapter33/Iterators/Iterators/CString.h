//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CString
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		CString& operator=(const CString& Other)
		{
			wprintf_s(L"COPY OPERATOR= CALLED !\n");

			MValue=Other.MValue;

			return(*this);
		}

		CString& operator=(CString&& Other)
		{
			wprintf_s(L"MOVE OPERATOR= CALLED !\n");

			MValue=std::move(Other.MValue);

			return(*this);
		}

		bool operator<(const CString& Other)
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
		const std::wstring& GetValue(void) const
		{
			return(MValue);
		}

	public:
		CString(void)
			: MValue(0)
		{
			wprintf_s(L"DEFAULT CONSTRUCTOR CALLED !\n");
		}

		CString(const std::wstring& Value)
			: MValue(Value)
		{
			wprintf_s(L"CONSTRUCTOR CALLED !\n");
		}

		CString(const CString& Value)
			: MValue(Value.MValue)
		{
			wprintf_s(L"COPY CONSTRUCTOR CALLED !\n");
		}

		CString(CString&& Value)
			: MValue(std::move(Value.MValue))
		{
			wprintf_s(L"MOVE CONSTRUCTOR CALLED !\n");
		}

		~CString(void)
		{
			wprintf_s(L"DESTRUCTOR CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
inline std::wostream& operator<<(std::wostream& Stream, const CString& Value)
{
	Stream << Value.GetValue();

	return(Stream);
}
//-------------------------------------------------------------------------------------------------------
inline bool operator==(const CString& Value1, const CString& Value2)
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
inline bool operator<(const CString& Value1, const CString& Value2)
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