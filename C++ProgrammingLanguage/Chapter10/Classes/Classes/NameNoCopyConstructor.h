//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CNameNoCopyConstructor
{
	private:
		std::wstring											MFirstName;
		std::wstring											MLastName;
		int														MAge;

	public:
		void PrintNameToConsole(void);

	public:
		CNameNoCopyConstructor(void);
		CNameNoCopyConstructor(std::wstring FirstName, std::wstring LastName, int Age);
		virtual ~CNameNoCopyConstructor(void);
};
//-------------------------------------------------------------------------------------------------------