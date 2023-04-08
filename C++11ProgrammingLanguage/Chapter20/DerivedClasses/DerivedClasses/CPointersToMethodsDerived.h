//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CPointersToMethodsBase.h"
//-----------------------------------------------------------------------------
class CPointersToMethodsDerived : public CPointersToMethodsBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void VirtualMethod1(void) const override
		{
			std::wcout << L"FIELD [" << GetField() << L"] - METHOD CPointersToMethodsDerived::VirtualMethod1() CALLED !" << std::endl;
		}

		virtual void VirtualMethod1(const std::wstring& Value) const override
		{
			std::wcout << L"FIELD [" << GetField() << L"] - METHOD CPointersToMethodsDerived::VirtualMethod1(" << Value << L") CALLED !" << std::endl;
		}

		virtual void VirtualMethod1(const std::wstring& Value1, int Value2) const override
		{
			std::wcout << L"FIELD [" << GetField() << L"] - METHOD CPointersToMethodsDerived::VirtualMethod1(" << Value1 << L"," << Value2 << L") CALLED !" << std::endl;
		}

		virtual void VirtualMethod2(void) const override
		{
			std::wcout << L"FIELD [" << GetField() << L"] - METHOD CPointersToMethodsDerived::VirtualMethod2() CALLED !" << std::endl;
		}

		virtual void VirtualMethod2(const std::wstring& Value) const override
		{
			std::wcout << L"FIELD [" << GetField() << L"] - METHOD CPointersToMethodsDerived::VirtualMethod2(" << Value << L") CALLED !" << std::endl;
		}

		virtual void VirtualMethod2(const std::wstring& Value1, int Value2) const override
		{
			std::wcout << L"FIELD [" << GetField() << L"] - METHOD CPointersToMethodsDerived::VirtualMethod2(" << Value1 << L"," << Value2 << L") CALLED !" << std::endl;
		}

	public:
		CPointersToMethodsDerived(const std::wstring& Field)
			: CPointersToMethodsBase(Field)
		{
		}

		virtual ~CPointersToMethodsDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------