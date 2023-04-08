//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "CBaseClass.h"
//-------------------------------------------------------------------------------------------------------
class CDerivedClass : public CBaseClass
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		virtual const std::wstring& GetValue(void) const
		{
			return(MValue);
		}

	public:
		CDerivedClass(std::wstring Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR [CDerivedClass] with VALUE [" << MValue << L"] CALLED !" << std::endl;
		}

		virtual ~CDerivedClass(void)
		{
			std::wcout << L"DESTRUCTOR [CDerivedClass] with VALUE [" << MValue << L"] CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------