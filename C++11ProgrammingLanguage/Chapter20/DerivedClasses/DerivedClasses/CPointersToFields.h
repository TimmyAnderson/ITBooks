//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CPointersToFields
{
//-----------------------------------------------------------------------------
	public:
		static std::wstring										MStatic;

	private:
		std::wstring											MPrivate;

	public:
		std::wstring											MString1;
		std::wstring											MString2;
		int														MInt1;
		int														MInt2;

	public:
		const std::wstring& GetPrivate(void) const noexcept
		{
			return(MPrivate);
		}

		const std::wstring& GetString1(void) const noexcept
		{
			return(MString1);
		}

		const std::wstring& GetString2(void) const noexcept
		{
			return(MString2);
		}

		int GetInt1(void) const noexcept
		{
			return(MInt1);
		}

		int GetInt2(void) const noexcept
		{
			return(MInt2);
		}

	public:
		void Print(void) const
		{
			std::wcout << L"FIELDS - MPrivate [" << MPrivate << L"] MString1 [" << MString1 << L"] MString2 [" << MString2 << L"] MInt1 [" << MInt1 << L"] MInt2 [" << MInt2 << L"] !" << std::endl;
		}

	public:
		CPointersToFields(void)
			: MPrivate(), MString1(), MString2(), MInt1(0), MInt2(0)
		{
		}

		~CPointersToFields(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------