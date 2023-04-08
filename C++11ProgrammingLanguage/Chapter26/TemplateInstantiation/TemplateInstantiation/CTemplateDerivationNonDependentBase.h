//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
void NonDependentFunction11(void)
{
	wprintf_s(L"::NonDependentFunction11() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void NonDependentFunction12(void)
{
	wprintf_s(L"::NonDependentFunction12() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void NonDependentFunction21(void)
{
	wprintf_s(L"::NonDependentFunction21() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void NonDependentFunction22(void)
{
	wprintf_s(L"::NonDependentFunction22() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void NonDependentFunction3(void)
{
	wprintf_s(L"::NonDependentFunction3() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// NON-TEMPLATE CLASS.
class CTemplateDerivationNonDependentBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		void MethodBase1(void)
		{
			wprintf_s(L"CTemplateDerivationNonDependentBase::MethodBase1() CALLED !\n");
		}

		void MethodBase2(void)
		{
			wprintf_s(L"CTemplateDerivationNonDependentBase::MethodBase2() CALLED !\n");
		}

		void NonDependentFunction11(void)
		{
			wprintf_s(L"CTemplateDerivationNonDependentBase::NonDependentFunction11() CALLED !\n");
		}

		void NonDependentFunction12(void)
		{
			wprintf_s(L"CTemplateDerivationNonDependentBase::NonDependentFunction12() CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------