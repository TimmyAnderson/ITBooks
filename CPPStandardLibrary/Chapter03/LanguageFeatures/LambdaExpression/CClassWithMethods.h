//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
//-------------------------------------------------------------------------------------------------------
class CClassWithMethods
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		void NonConstMethod(void)
		{
			std::wcout << L"NON CONST METHOD CALLED with VALUE [" << MValue << L"] !" << std::endl;

			MValue=L"CHANGED in NON-CONST METHOD";
		}

		void ConstMethod(void) const
		{
			std::wcout << L"CONST METHOD CALLED !" << std::endl;
		}

		void PrintValue(void)
		{
			std::wcout << L"VALUE [" << MValue << L"] !" << std::endl;
		}

	public:
		CClassWithMethods(void)
		{
			MValue=L"DEFAULT";
		}

		CClassWithMethods(const CClassWithMethods&)
		{
			std::wcout << L"COPY CONSTRUCTOR CALLED !" << std::endl;

			MValue=L"DEFAULT set in COPY CONSTRUCTOR";
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------