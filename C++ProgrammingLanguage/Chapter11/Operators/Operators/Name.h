//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "NameOperations.h"
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
		void PrintFullName(void);
		std::wstring GetFullName(void);
//-------------------------------------------------------------------------------------------------------
	public:
		CName(void);
		CName(std::wstring FirstName, std::wstring LastName, int Age);
		virtual ~CName(void);
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------