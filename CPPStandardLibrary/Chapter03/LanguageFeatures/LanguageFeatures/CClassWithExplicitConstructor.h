//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <vector>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CClassWithExplicitConstructor
{
//-------------------------------------------------------------------------------------------------------
	public:
		wstring													MFirstName;
		wstring													MLastName;
		int														MAge;

	public:
		inline explicit CClassWithExplicitConstructor(wstring FirstName, wstring LastName, int Age)
			: MFirstName(FirstName), MLastName(LastName), MAge(Age)
		{
			std::wcout << L"EXPLICIT CClassWithExplicitConstructor::CClassWithExplicitConstructor() CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------