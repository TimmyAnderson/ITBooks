//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CDerivedResolution.h"
//-------------------------------------------------------------------------------------------------------
class CSuperDerivedResolution : public CDerivedResolution
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual void DoGrandchildResolution(void) const
		{
			std::wcout << L"SUPER DERIVED RESOLUTION - BEGIN !" << std::endl;
			
			// Vola sa METHOD z BASE CLASS 'CBaseResolution1'.
			// !!! Ako BASE CLASSS sa pouziva CLASS 'CDerivedResolution'. Ta vsak METHOD DoSomethingNonOverriden1() NEDEFINUJE a tak C++ hlada tuto METHOD v BASE CLASSES.
			CDerivedResolution::DoSomethingNonOverriden1();

			// Vola sa METHOD z BASE CLASS 'CBaseResolution2'.
			// !!! Ako BASE CLASSS sa pouziva CLASS 'CDerivedResolution'. Ta vsak METHOD DoSomethingNonOverriden2() NEDEFINUJE a tak C++ hlada tuto METHOD v BASE CLASSES.
			CDerivedResolution::DoSomethingNonOverriden2();

			std::wcout << L"SUPER DERIVED RESOLUTION - END !" << std::endl;
		}

	public:
		CSuperDerivedResolution(void)
		{
		}

		virtual ~CSuperDerivedResolution(void) override
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------