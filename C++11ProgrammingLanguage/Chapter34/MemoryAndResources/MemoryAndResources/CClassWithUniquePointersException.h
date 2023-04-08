//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <memory>
#include <iostream>
#include "CCustomClass.h"
//-------------------------------------------------------------------------------------------------------
class CClassWithUniquePointersException
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::unique_ptr<CCustomClass>							MFirstName;
		std::unique_ptr<CCustomClass>							MLastName;
		std::unique_ptr<int>									MAge;

	public:
		void Print(void)
		{
			std::wcout << L"FIRST NAME [" << MFirstName->GetValue() << L"], LAST NAME [" << MLastName->GetValue() << L"], AGE [" << *MAge << "] !\n";
		}

	public:
		// !!! Pri inicializacii FIELD 'MLastName' sa hodi EXCEPTION. Vdaka pouzitiu CLASS [unique_ptr<T>] dojde k UVOLNENIU OBJECT vo FIELD 'MFirstName'. Pri pouziti klasickych POINTERS by k uvolneniu NEDOSLO a DOSLO by k MEMORY LEAK.
		CClassWithUniquePointersException(std::wstring FirstName, std::wstring LastName, int Age)
			: MFirstName(new CCustomClass(FirstName)), MLastName(new CCustomClass(LastName,true)), MAge(new int(Age))
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------