//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CNonVirtualInheritanceSuperBase
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		virtual void PrintValue(void) const
		{
			std::wcout << L"VALUE [" << MValue << L"] !" << std::endl;
		}

	public:
		CNonVirtualInheritanceSuperBase(const std::wstring& Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CNonVirtualInheritanceSuperBase - VALUE [" << MValue << L"] CALLED !" << std::endl;
		}

		virtual ~CNonVirtualInheritanceSuperBase(void)
		{
			std::wcout << L"DESTRUCTOR CNonVirtualInheritanceSuperBase CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------