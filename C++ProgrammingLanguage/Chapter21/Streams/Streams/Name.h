//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <ios>
//-------------------------------------------------------------------------------------------------------
class CName
{
//-------------------------------------------------------------------------------------------------------
	public:
		std::wstring											MFirstName;
		std::wstring											MLastName;
		int														MAge;
//-------------------------------------------------------------------------------------------------------
	public:
		std::wstring& GetFirstName(void);
		std::wstring& GetLastName(void);
		int& GetAge(void);
//-------------------------------------------------------------------------------------------------------
	public:
		void SetFirstName(std::wstring& Value);
		void SetLastName(std::wstring& Value);
		void SetAge(int Value);
//-------------------------------------------------------------------------------------------------------
	public:
		void PrintFullName(void);
//-------------------------------------------------------------------------------------------------------
	public:
		CName(void);
		CName(const CName& Other);
		CName(std::wstring FirstName, std::wstring LastName, int Age);
		virtual ~CName(void);
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
// Pouziva sa pre COUT.
std::ostream& operator<<(std::ostream& Stream, CName& Name);
// Pouziva sa pre WCOUT.
std::wostream& operator<<(std::wostream& Stream, CName& Name);
// Pouziva sa pre WCOUT.
std::wistream& operator>>(std::wistream& Stream, CName& Name);
//-------------------------------------------------------------------------------------------------------