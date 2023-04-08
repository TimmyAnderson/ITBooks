//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CBaseResolution1.h"
#include "CBaseResolution2.h"
//-------------------------------------------------------------------------------------------------------
class CDerivedResolution : public CBaseResolution1, public CBaseResolution2
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual void DoSomething(void) const override
		{
			std::wcout << L"DERIVED RESOLUTION CALLED !" << std::endl;
		}

		void DoResolution(void) const
		{
			std::wcout << L"DERIVED RESOLUTION - BEGIN !" << std::endl;
			
			// Vola sa METHOD z BASE CLASS 'CBaseResolution1'.
			CBaseResolution1::DoSomething();

			// Vola sa METHOD z BASE CLASS 'CBaseResolution2'.
			CBaseResolution2::DoSomething();

			std::wcout << L"DERIVED RESOLUTION - END !" << std::endl;
		}
		
	public:
		CDerivedResolution(void)
		{
		}

		virtual ~CDerivedResolution(void) override
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------