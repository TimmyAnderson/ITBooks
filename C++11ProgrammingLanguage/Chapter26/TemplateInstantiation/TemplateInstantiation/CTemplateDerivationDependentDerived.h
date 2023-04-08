//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CTemplateDerivationDependentBase.h"
//-------------------------------------------------------------------------------------------------------
template<typename TType>
// BASE CLASS je TEMPLATE CLASS.
class CTemplateDerivationDependentDerived : public CTemplateDerivationDependentBase<TType>
{
//-------------------------------------------------------------------------------------------------------
	public:
		void MethodBase2(void)
		{
			wprintf_s(L"CTemplateDerivationDependentDerived::MethodBase2() CALLED !\n");
		}

		void DependentFunction12(void)
		{
			wprintf_s(L"CTemplateDerivationDependentDerived::DependentFunction12() CALLED !\n");
		}

		void DependentFunction22(void)
		{
			wprintf_s(L"CTemplateDerivationDependentDerived::DependentFunction22() CALLED !\n");
		}

	public:
		void Test(void)
		{
			// !!! Vola sa METHOD z BASE CLASS.
			// !!!!! G++ hodi ERROR, pretoze C++ vyzaduje EXPLICITNE volanie pre METHODS BASE TEMPLATE CLASS.
			//MethodBase1();

			// !!! EXPLICITNE volanie METHOD z BASE CLASS.
			this->MethodBase1();

			// !!! EXPLICITNE volanie METHOD z BASE CLASS.
			CTemplateDerivationDependentBase<TType>::MethodBase1();

			// !!!!! Vola sa METHOD z DERIVED CLASS, pretoze METHOD CTemplateDerivationDependentDerived::MethodBase2() pretazuje METHOD CTemplateDerivationNonDependentBase::MethodBase2().
			MethodBase2();

			// !!!!! NEZAVOLA sa METHOD BASE CLASS, ale GLOBAL FUNCTION. Dovodom je to, ze volanie FUNCTION DependentFunction11() NEZAVISI na TYPE PARAMETERS a tym padom RESOLVING je realizovany v DEFINITION TIME a NIE INSTANTION TIME. A kedze v DEFINITION TIME je pristupna IBA GLOBAL FUNCTION a NIE FUNCTION z BASE CLASS CTemplateDerivationDependentBase<>, zavola sa GLOBAL FUNCTION.
			// !!!!! VC++ NESPRAVNE vola METHOD BASE CLASS.
			DependentFunction11();

			// !!!!! ZAVOLA sa METHOD z BASE CLASS, pretoze tato bola EXPLICITNE volana.
			this->DependentFunction11();

			// !!!!! ZAVOLA sa METHOD z BASE CLASS, pretoze tato bola EXPLICITNE volana.
			CTemplateDerivationDependentBase<TType>::DependentFunction11();

			// Vola sa METHOD DERIVED CLASS.
			DependentFunction12();

			// Vola sa GLOBAL FUNCTION.
			DependentFunction21();

			// Vola sa METHOD DERIVED CLASS.
			DependentFunction22();

			// Vola sa GLOBAL FUNCTION.
			DependentFunction3();
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------