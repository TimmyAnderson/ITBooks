//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CExplicitQualificationDerived.h"
//-----------------------------------------------------------------------------
class CExplicitQualificationSuperDerived : public CExplicitQualificationDerived
{
//-----------------------------------------------------------------------------
	public:
		virtual void DoGrandchildResolution(void) const
		{
			std::wcout << L"EXPLICIT QUALIFICATION CExplicitQualificationSuperDerived::DoGrandchildResolution() STARTED !" << std::endl;
			
			// Vola sa METHOD z BASE CLASS 'CExplicitQualificationBase1'.
			// !!! Ako BASE CLASSS sa pouziva CLASS 'CExplicitQualificationDerived'. Ta vsak METHOD NonOverridden1() NEDEFINUJE a tak C++ hlada tuto METHOD v BASE CLASSES.
			CExplicitQualificationDerived::NonOverridden1();

			// Vola sa METHOD z BASE CLASS 'CExplicitQualificationBase2'.
			// !!! Ako BASE CLASSS sa pouziva CLASS 'CExplicitQualificationDerived'. Ta vsak METHOD NonOverridden2() NEDEFINUJE a tak C++ hlada tuto METHOD v BASE CLASSES.
			CExplicitQualificationDerived::NonOverridden2();

			std::wcout << L"EXPLICIT QUALIFICATION CExplicitQualificationSuperDerived::DoGrandchildResolution() FINISHED !" << std::endl;
		}

	public:
		CExplicitQualificationSuperDerived(void)
		{
		}

		virtual ~CExplicitQualificationSuperDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
