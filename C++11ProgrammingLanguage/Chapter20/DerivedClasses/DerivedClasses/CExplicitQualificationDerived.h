//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CExplicitQualificationBase1.h"
#include "CExplicitQualificationBase2.h"
//-----------------------------------------------------------------------------
class CExplicitQualificationDerived : public CExplicitQualificationBase1, public CExplicitQualificationBase2
{
//-----------------------------------------------------------------------------
	public:
		virtual void Overridden(void) const
		{
			std::wcout << L"EXPLICIT QUALIFICATION CExplicitQualificationDerived::Overridden() CALLED !" << std::endl;
		}

		void DoResolution(void) const
		{
			std::wcout << L"EXPLICIT QUALIFICATION CExplicitQualificationDerived::DoResolution() STARTED !" << std::endl;
			
			// Vola sa METHOD z BASE CLASS 'CExplicitQualificationBase1'.
			CExplicitQualificationBase1::Overridden();

			// Vola sa METHOD z BASE CLASS 'CExplicitQualificationBase2'.
			CExplicitQualificationBase2::Overridden();

			std::wcout << L"EXPLICIT QUALIFICATION CExplicitQualificationDerived::DoResolution() FINISHED !" << std::endl;
		}
		
	public:
		CExplicitQualificationDerived(void)
		{
		}

		virtual ~CExplicitQualificationDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
