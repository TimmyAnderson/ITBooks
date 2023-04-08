//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CName
{
//-------------------------------------------------------------------------------------------------------
	public:
		std::wstring											MFirstName;
		std::wstring											MLastName;
		int														MAge;

	public:
		void PrintName(std::wstring Prefix, std::wstring Postfix)
		{
			std::wcout << Prefix << L" NAME ["<< MFirstName << L" "<< MLastName << L"], AGE [" << MAge << L"] " << Postfix;
		}

	public:
		CName(std::wstring FirstName, std::wstring LastName, int Age)
			: MFirstName(FirstName), MLastName(LastName), MAge(Age)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------