//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <stdio.h>
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
			wprintf_s(L"CString COPY OPERATOR= CALLED !\n");

			MValue=Value.MValue;

			return(*this);
		}

		// Aj ked je to MOVE SEMANTICS OPERATOR=, robi pre jednoduchost kopirovanie FIELDS.
		CString& operator=(CString&& Value)
		{
			wprintf_s(L"CString MOVE OPERATOR= CALLED !\n");

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
			wprintf_s(L"CString COPY CONSTRUCTOR CALLED !\n");
		}

		// Aj ked je to MOVE SEMANTICS CONSTRUCTOR, robi pre jednoduchost kopiu.
		CString(CString&& Value)
			: MValue(Value.MValue)
		{
			wprintf_s(L"CString MOVE CONSTRUCTOR CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------