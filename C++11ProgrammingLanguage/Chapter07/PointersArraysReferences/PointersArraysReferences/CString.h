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
		const std::wstring& GetValue(void) const
		{
			return(MValue);
		}

	public:
		CString& operator=(CString& Value)
		{
			std::wcout << L"CString COPY OPERATOR= CALLED !" << std::endl;

			MValue=Value.MValue;

			return(*this);
		}

		CString& operator=(CString&& Value)
		{
			std::wcout << L"CString MOVE OPERATOR= CALLED !" << std::endl;

			MValue=std::move(Value.MValue);

			return(*this);
		}

	public:
		CString(const std::wstring& Value)
			: MValue(Value)
		{
		}

		CString(const CString& Value)
			: MValue(Value.MValue)
		{
			std::wcout << L"CString COPY CONSTRUCTOR CALLED !" << std::endl;
		}

		CString(CString&& Value)
			: MValue(std::move(Value.MValue))
		{
			std::wcout << L"CString MOVE CONSTRUCTOR CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------