//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CVirtualInheritanceSuperBase
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
		CVirtualInheritanceSuperBase(const std::wstring& Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CVirtualInheritanceSuperBase - VALUE [" << MValue << L"] CALLED !" << std::endl;
		}

		virtual ~CVirtualInheritanceSuperBase(void)
		{
			std::wcout << L"DESTRUCTOR CVirtualInheritanceSuperBase CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------