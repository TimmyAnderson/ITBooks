//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CConstructorInheritanceBase.h"
//-----------------------------------------------------------------------------
class CConstructorInheritanceDerived : public CConstructorInheritanceBase
{
//-----------------------------------------------------------------------------
	public:
		// !!! VSETKY CONSTRUCTORS z CLASS 'CConstructorInheritanceBase' su INHERITED do CLASS 'CConstructorInheritanceDerived'.
		using													CConstructorInheritanceBase::CConstructorInheritanceBase;

	public:
		CConstructorInheritanceDerived(int,int,int)
			: CConstructorInheritanceBase(100,200)
		{
			std::wcout << L"CONSTRUCTOR CConstructorInheritanceDerived::CConstructorInheritanceDerived(INT,INT,INT) CALLED !" << std::endl;
		}

		virtual ~CConstructorInheritanceDerived(void) override
		{
			std::wcout << L"DESTRUCTOR CConstructorInheritanceDerived::CConstructorInheritanceDerived() CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------