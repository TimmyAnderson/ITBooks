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
		CName(std::wstring FirstName, std::wstring LastName, int Age)
			: MFirstName(FirstName), MLastName(LastName), MAge(Age)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------