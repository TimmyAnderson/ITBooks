//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CExplicitQualificationBase1
{
//-----------------------------------------------------------------------------
	public:
		virtual void Overridden(void) const
		{
			std::wcout << L"EXPLICIT QUALIFICATION CExplicitQualificationBase1::Overridden() CALLED !" << std::endl;
		}

		virtual void NonOverridden1(void) const
		{
			std::wcout << L"EXPLICIT QUALIFICATION CExplicitQualificationBase1::NonOverridden1() CALLED !" << std::endl;
		}

	public:
		CExplicitQualificationBase1(void)
		{
		}

		virtual ~CExplicitQualificationBase1(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
