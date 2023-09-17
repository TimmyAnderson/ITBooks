//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void DependentExpressionsPrint(TType Value)
{
	std::wcout << L"TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void DependentExpressionsTypeDependent(TType Value)
{
	// !!!!! EXPRESSION je TYPE DEPENDENT, pretoze je zavisla na TEMPLATE TYPE PARAMETER.
	DependentExpressionsPrint(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<int VALUE>
void DependentExpressionsValueDependent1(void)
{
	// !!!!! EXPRESSION je VALUE DEPENDENT, pretoze je zavisla na TEMPLATE NON-TYPE PARAMETER.
	DependentExpressionsPrint(VALUE);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void DependentExpressionsValueDependent2(TType Value)
{
	// !!!!! EXPRESSION je VALUE DEPENDENT, pretoze je zavisla na SIZEOF TEMPLATE TYPE PARAMETER.
	DependentExpressionsPrint(sizeof(Value));
}
//----------------------------------------------------------------------------------------------------------------------