//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
// !!! CLASS je VIRTUAL, lebo ma VIRTUAL DESTRUCTOR.
class CVirtualBase
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
		CVirtualBase(const std::wstring& Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CVirtualBase - VALUE [" << MValue << L"] CALLED !" << std::endl;
		}

		virtual ~CVirtualBase(void)
		{
			std::wcout << L"DESTRUCTOR CVirtualBase CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------