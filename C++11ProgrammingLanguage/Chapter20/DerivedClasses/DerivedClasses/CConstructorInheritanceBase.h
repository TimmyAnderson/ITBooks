//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CConstructorInheritanceBase
{
//-----------------------------------------------------------------------------
	public:
		void DoSomething(void)
		{
			std::wcout << L"METHOD CConstructorInheritanceBase::DoSomething() CALLED !" << std::endl;
		}

	public:
		CConstructorInheritanceBase(int)
		{
			std::wcout << L"CONSTRUCTOR CConstructorInheritanceBase::CConstructorInheritanceBase(INT) CALLED !" << std::endl;
		}

		CConstructorInheritanceBase(int,int)
		{
			std::wcout << L"CONSTRUCTOR CConstructorInheritanceBase::CConstructorInheritanceBase(INT,INT) CALLED !" << std::endl;
		}

		virtual ~CConstructorInheritanceBase(void)
		{
			std::wcout << L"DESTRUCTOR CConstructorInheritanceBase::CConstructorInheritanceBase() CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------