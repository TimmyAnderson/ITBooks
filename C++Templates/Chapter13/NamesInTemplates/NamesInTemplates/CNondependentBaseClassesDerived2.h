//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNondependentBaseClassesBase.h"
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Nazov TEMPLATE PARAMETER sa ZHODUJE s TYPE definovanom pomocou USING v BASE CLASS.
template<typename SHARED_TYPE>
class CNondependentBaseClassesDerived2 final : public CNondependentBaseClassesBase<double>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Test(void);

	private:
		// !!!!! TYPE bude v skutocnosti zhodny s TYPE definovanom pomocou USING v BASE CLASS a NIE TYPE, ktory urcuje TEMPLATE PARAMETER.
		SHARED_TYPE												MValue;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename SHARED_TYPE>
void CNondependentBaseClassesDerived2<SHARED_TYPE>::Test(void)
{
	MBaseField=200;

	std::wcout << L"DERIVED 2 - BASE FIELD [" << MBaseField << L"]." << std::endl;

	// !!!!! NEPOUZIJE sa TYPE TEMPLATE PARAMETER, ale TYPE definovany v USING BASE CLASS co je TYPE [int].
	std::wcout << L"DERIVED 2 - TYPE SHARED_TYPE [" << GetTypeInfoName<SHARED_TYPE>() << L"]." << std::endl;

	std::wcout << L"DERIVED 2 - TYPE MValue [" << GetTypeInfoName<decltype(MValue)>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------