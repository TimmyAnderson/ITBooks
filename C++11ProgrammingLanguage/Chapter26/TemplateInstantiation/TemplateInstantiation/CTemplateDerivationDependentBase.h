//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
void DependentFunction11(void)
{
	wprintf_s(L"::DependentFunction11() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void DependentFunction12(void)
{
	wprintf_s(L"::DependentFunction12() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void DependentFunction21(void)
{
	wprintf_s(L"::DependentFunction21() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void DependentFunction22(void)
{
	wprintf_s(L"::DependentFunction22() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void DependentFunction3(void)
{
	wprintf_s(L"::DependentFunction3() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// TEMPLATE CLASS.
template<typename TType>
class CTemplateDerivationDependentBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		void MethodBase1(void)
		{
			wprintf_s(L"CTemplateDerivationDependentBase::MethodBase1() CALLED !\n");
		}

		void MethodBase2(void)
		{
			wprintf_s(L"CTemplateDerivationDependentBase::MethodBase2() CALLED !\n");
		}

		void DependentFunction11(void)
		{
			wprintf_s(L"CTemplateDerivationDependentBase::DependentFunction11() CALLED !\n");
		}

		void DependentFunction12(void)
		{
			wprintf_s(L"CTemplateDerivationDependentBase::DependentFunction12() CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------