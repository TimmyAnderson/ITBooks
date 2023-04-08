//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CException.h"
//-------------------------------------------------------------------------------------------------------
class CCustomClass
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const
		{
			return(MValue);
		}

	public:
		CCustomClass(void)
			: MValue(L"")
		{
			std::wcout << L"CONSTRUCTOR [CCustomClass] with VALUE [" << MValue << L"] CALLED !" << std::endl;
		}

		CCustomClass(std::wstring Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR [CCustomClass] with VALUE [" << MValue << L"] CALLED !" << std::endl;
		}

		CCustomClass(std::wstring Value, bool)
			: MValue(Value)
		{
			std::wcout << L"!!!!! CONSTRUCTOR [CCustomClass] with VALUE [" << MValue << L"] will THROW EXCEPTION !" << std::endl;

			throw(CException(L"CONSTRUCTOR [CCustomClass] has THROWN EXCEPTION !"));
		}

		~CCustomClass(void)
		{
			std::wcout << L"DESTRUCTOR [CCustomClass] with VALUE [" << MValue << L"] CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------