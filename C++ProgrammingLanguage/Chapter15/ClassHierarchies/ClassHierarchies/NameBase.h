//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CNameBase
{
	public:
		// !!! FIELDS su PUBLIC, aby som k nim mohol pristupovat cez POINTER na MEMBER.
		std::wstring											MFirstName;
		std::wstring											MLastName;
		int														MAge;

	public:
		static std::wstring CNameBase::StaticMethod(void);

	public:
		std::wstring GetFirstName(void);
		std::wstring GetLastName(void);
		int GetAge(void);

	public:
		virtual void PrintFullName(void);
		std::wstring GetFullName(void);

	public:
		virtual std::wstring VirtualMethod(void);

	public:
		CNameBase(std::wstring FirstName, std::wstring LastName, int Age);
		virtual ~CNameBase(void);
};
//-------------------------------------------------------------------------------------------------------