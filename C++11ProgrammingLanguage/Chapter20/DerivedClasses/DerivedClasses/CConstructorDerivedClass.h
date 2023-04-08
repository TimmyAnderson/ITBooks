//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CConstructorBaseClass1.h"
#include "CConstructorBaseClass2.h"
//-----------------------------------------------------------------------------
class CConstructorDerivedClass : public CConstructorBaseClass1, public CConstructorBaseClass2
{
//-----------------------------------------------------------------------------
	public:
		void DoSomething(void) const
		{
			std::wcout << L"METHOD CConstructorDerivedClass::DoSomething() CALLED !" << std::endl;
		}

	public:
		CConstructorDerivedClass(void)
		{
			std::wcout << L"CONSTRUCTOR CConstructorDerivedClass::CConstructorDerivedClass() CALLED !" << std::endl;
		}

		virtual ~CConstructorDerivedClass(void)
		{
			std::wcout << L"DESTRUCTOR CConstructorDerivedClass::CConstructorDerivedClass() CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------