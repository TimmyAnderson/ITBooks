//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CExplicitQualificationBase2
{
//-----------------------------------------------------------------------------
	public:
		virtual void Overridden(void) const
		{
			std::wcout << L"EXPLICIT QUALIFICATION CExplicitQualificationBase2::Overridden() CALLED !" << std::endl;
		}

		virtual void NonOverridden2(void) const
		{
			std::wcout << L"EXPLICIT QUALIFICATION CExplicitQualificationBase2::NonOverridden2() CALLED !" << std::endl;
		}

	public:
		CExplicitQualificationBase2(void)
		{
		}

		virtual ~CExplicitQualificationBase2(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
