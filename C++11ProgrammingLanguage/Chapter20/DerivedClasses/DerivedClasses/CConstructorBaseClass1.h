//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CConstructorBaseClass1
{
//-----------------------------------------------------------------------------
	public:
		void DoSomething(void) const
		{
			std::wcout << L"METHOD CConstructorBaseClass1::DoSomething() CALLED !" << std::endl;
		}

	public:
		CConstructorBaseClass1(void)
		{
			std::wcout << L"CONSTRUCTOR CConstructorBaseClass1::CConstructorBaseClass1() CALLED !" << std::endl;
		}

		virtual ~CConstructorBaseClass1(void)
		{
			std::wcout << L"DESTRUCTOR CConstructorBaseClass1::CConstructorBaseClass1() CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------