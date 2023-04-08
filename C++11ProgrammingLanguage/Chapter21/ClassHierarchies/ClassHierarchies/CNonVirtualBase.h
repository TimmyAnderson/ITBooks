//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
// !!! CLASS je VIRTUAL, lebo ma NEMA VIRTUAL METHODS, ani VIRTUAL DESTRUCTOR.
class CNonVirtualBase
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		void PrintValue(void) const
		{
			std::wcout << L"VALUE [" << MValue << L"] !" << std::endl;
		}

	public:
		CNonVirtualBase(const std::wstring& Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CNonVirtualBase - VALUE [" << MValue << L"] CALLED !" << std::endl;
		}

		~CNonVirtualBase(void)
		{
			std::wcout << L"DESTRUCTOR CNonVirtualBase CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------