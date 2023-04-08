//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CVirtualBaseClass1.h"
#include "CNonVirtualBaseClass.h"
#include "CPrivateBaseClass.h"
//-----------------------------------------------------------------------------
class CDerivedClass : public CVirtualBaseClass1, public CNonVirtualBaseClass, private CPrivateBaseClass
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MDerivedField;

	public:
		void MethodInDerivedClass(void) const
		{
			std::wcout << L"FIELD [" << MDerivedField.c_str() << L"] LENGTH [" << MDerivedField.length() << L"] - METHOD CDerivedClass::MethodInDerivedClass() CALLED !" << std::endl;
		}

	public:
		virtual void VirtualMethod(void) const override
		{
			std::wcout << L"METHOD CDerivedClass::VirtualMethod() CALLED !" << std::endl;
		}

	public:
		CDerivedClass(void)
			: MDerivedField(L"TIMMY ANDERSON")
		{
		}

		virtual ~CDerivedClass(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------