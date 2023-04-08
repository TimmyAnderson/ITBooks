//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CNameWithCopyConstructor
{
	private:
		std::wstring											MFirstName;
		std::wstring											MLastName;
		int														MAge;

	public:
		void PrintNameToConsole(void);

	public:
		CNameWithCopyConstructor(void);
		CNameWithCopyConstructor(std::wstring FirstName, std::wstring LastName, int Age);
		CNameWithCopyConstructor(const CNameWithCopyConstructor& Original);
		virtual ~CNameWithCopyConstructor(void);
};
//-------------------------------------------------------------------------------------------------------