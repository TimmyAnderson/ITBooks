//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CTemplateDerivationNonDependentBase.h"
//-------------------------------------------------------------------------------------------------------
template<typename TType>
// BASE CLASS je NON-TEMPLATE CLASS.
class CTemplateDerivationNonDependentDerived : public CTemplateDerivationNonDependentBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		void MethodBase2(void)
		{
			wprintf_s(L"CTemplateDerivationNonDependentDerived::MethodBase2() CALLED !\n");
		}

		void NonDependentFunction12(void)
		{
			wprintf_s(L"CTemplateDerivationNonDependentDerived::NonDependentFunction12() CALLED !\n");
		}

		void NonDependentFunction22(void)
		{
			wprintf_s(L"CTemplateDerivationNonDependentDerived::NonDependentFunction22() CALLED !\n");
		}

	public:
		void Test(void)
		{
			// !!! Vola sa METHOD z BASE CLASS.
			MethodBase1();

			// !!!!! Vola sa METHOD z DERIVED CLASS, pretoze METHOD CTemplateDerivationNonDependentDerived::MethodBase2() pretazuje METHOD CTemplateDerivationNonDependentBase::MethodBase2().
			MethodBase2();

			// Vola sa METHOD BASE CLASS.
			NonDependentFunction11();

			// Vola sa METHOD DERIVED CLASS.
			NonDependentFunction12();

			// Vola sa GLOBAL FUNCTION.
			NonDependentFunction21();

			// Vola sa METHOD DERIVED CLASS.
			NonDependentFunction22();

			// Vola sa GLOBAL FUNCTION.
			NonDependentFunction3();
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------