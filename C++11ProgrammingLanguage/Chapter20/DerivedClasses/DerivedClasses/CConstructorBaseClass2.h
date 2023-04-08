//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CConstructorBaseClass2
{
//-----------------------------------------------------------------------------
	public:
		void DoSomething(void) const
		{
			std::wcout << L"METHOD CConstructorBaseClass2::DoSomething() CALLED !" << std::endl;
		}

	public:
		CConstructorBaseClass2(void)
		{
			std::wcout << L"CONSTRUCTOR CConstructorBaseClass2::CConstructorBaseClass2() CALLED !" << std::endl;
		}

		virtual ~CConstructorBaseClass2(void)
		{
			std::wcout << L"DESTRUCTOR CConstructorBaseClass2::CConstructorBaseClass2() CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------