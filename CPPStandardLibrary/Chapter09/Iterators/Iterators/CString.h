//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
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
			std::wcout << L"COPY OPERATOR= CALLED !" << std::endl;

			MValue=Other.MValue;

			return(*this);
		}

		CString& operator=(CString&& Other)
		{
			std::wcout << L"MOVE OPERATOR= CALLED !" << std::endl;

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
			std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
		}

		CString(const std::wstring& Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CALLED !" << std::endl;
		}

		CString(const CString& Value)
			: MValue(Value.MValue)
		{
			std::wcout << L"COPY CONSTRUCTOR CALLED !" << std::endl;
		}

		CString(CString&& Value)
			: MValue(std::move(Value.MValue))
		{
			std::wcout << L"MOVE CONSTRUCTOR CALLED !" << std::endl;
		}

		~CString(void)
		{
			std::wcout << L"DESTRUCTOR CALLED !" << std::endl;
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