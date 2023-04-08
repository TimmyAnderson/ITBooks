//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CName
{
//-------------------------------------------------------------------------------------------------------
	private:
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
		void PrintFullName(void);
//-------------------------------------------------------------------------------------------------------
	public:
		CName(void);
		CName(std::wstring FirstName, std::wstring LastName, int Age);
		virtual ~CName(void);
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------