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

		// Aj ked je to MOVE SEMANTICS OPERATOR=, robi pre jednoduchost kopirovanie FIELDS.
		CString& operator=(CString&& Value)
		{
			std::wcout << L"CString MOVE OPERATOR= CALLED !" << std::endl;

			MValue=Value.MValue;

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

		// Aj ked je to MOVE SEMANTICS CONSTRUCTOR, robi pre jednoduchost kopiu.
		CString(CString&& Value)
			: MValue(Value.MValue)
		{
			std::wcout << L"CString MOVE CONSTRUCTOR CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------