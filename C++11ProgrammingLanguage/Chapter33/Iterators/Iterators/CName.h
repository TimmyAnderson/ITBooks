//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
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
			wprintf_s(L"%ls NAME [%ls %ls], AGE [%d] %ls",Prefix.c_str(),MFirstName.c_str(),MLastName.c_str(),MAge,Postfix.c_str());
		}

	public:
		CName(std::wstring FirstName, std::wstring LastName, int Age)
			: MFirstName(FirstName), MLastName(LastName), MAge(Age)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------