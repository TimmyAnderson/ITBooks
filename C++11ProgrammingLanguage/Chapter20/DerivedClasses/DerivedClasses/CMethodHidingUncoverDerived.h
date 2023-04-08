//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CMethodHidingUncoverBase.h"
//-----------------------------------------------------------------------------
class CMethodHidingUncoverDerived : public CMethodHidingUncoverBase
{
//-----------------------------------------------------------------------------
	private:
		// Vytiahnu sa HIDEN METHODS z CLASS 'CMethodHidingBase'.
		using													CMethodHidingUncoverBase::PublicMethod;

	public:
		// Vytiahnu sa HIDEN METHODS z CLASS 'CMethodHidingBase'.
		using													CMethodHidingUncoverBase::Method1;
		using													CMethodHidingUncoverBase::Method2;
		using													CMethodHidingUncoverBase::ProtectedMethod;

	public:
		void Method1(double) const
		{
			std::wcout << L"METHOD CMethodHidingUncoverDerived::Method1(DOUBLE) CALLED !" << std::endl;
		}

		void Method2(double) const
		{
			std::wcout << L"METHOD CMethodHidingUncoverDerived::Method2(DOUBLE) CALLED !" << std::endl;
		}

		void ProtectedMethod(double) const
		{
			std::wcout << L"METHOD CMethodHidingUncoverDerived::ProtectedMethod(DOUBLE) CALLED !" << std::endl;
		}

		void PublicMethod(double) const
		{
			std::wcout << L"METHOD CMethodHidingUncoverDerived::PublicMethod(DOUBLE) CALLED !" << std::endl;
		}

	public:
		CMethodHidingUncoverDerived(void)
		{
		}

		virtual ~CMethodHidingUncoverDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------