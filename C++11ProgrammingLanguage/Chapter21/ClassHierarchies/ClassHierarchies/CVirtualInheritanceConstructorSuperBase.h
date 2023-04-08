//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CVirtualInheritanceConstructorSuperBase
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
		CVirtualInheritanceConstructorSuperBase(const std::wstring& Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CVirtualInheritanceConstructorSuperBase - VALUE [" << MValue << L"] CALLED !" << std::endl;
		}

		virtual ~CVirtualInheritanceConstructorSuperBase(void)
		{
			std::wcout << L"DESTRUCTOR CVirtualInheritanceConstructorSuperBase CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------