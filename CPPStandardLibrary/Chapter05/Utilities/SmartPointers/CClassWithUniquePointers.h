//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <memory>
#include <iostream>
#include "CCustomClass.h"
//-------------------------------------------------------------------------------------------------------
class CClassWithUniquePointers
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::unique_ptr<CCustomClass>							MFirstName;
		std::unique_ptr<CCustomClass>							MLastName;
		std::unique_ptr<int>									MAge;

	public:
		void Print(void)
		{
			std::wcout << L"FIRST NAME [" << MFirstName->GetValue() << L"], LAST NAME [" << MLastName->GetValue() << L"], AGE [" << *MAge << "] !\n" << std::endl;
		}

	public:
		CClassWithUniquePointers(std::wstring FirstName, std::wstring LastName, int Age)
			: MFirstName(new CCustomClass(FirstName)), MLastName(new CCustomClass(LastName)), MAge(new int(Age))
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------