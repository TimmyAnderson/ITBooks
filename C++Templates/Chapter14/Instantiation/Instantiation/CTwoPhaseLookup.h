//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace TwoPhaseLookupNamespace
{
//----------------------------------------------------------------------------------------------------------------------
	enum ETwoPhaseLookup
	{
//----------------------------------------------------------------------------------------------------------------------
		E_VALUE=100
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	void TwoPhaseLookupFunctionInNamespace(TType Value)
	{
		std::wcout << L"FUNCTION in NAMESPACE CALLED. VALUE [" << Value << L"]." << std::endl;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TwoPhaseLookupFunctionOutsideOfNamespace(TType Value)
{
	std::wcout << L"FUNCTION outside of NAMESPACE CALLED. VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TwoPhaseLookupTest(TType Parameter)
{
	// !!! PARSING sa vykona uz vo FIRST PHASE, kde sa urci, ze CODE [TwoPhaseLookupFunctionOutsideOfNamespace] reprezentuje TEMPLATE.
	TwoPhaseLookupFunctionOutsideOfNamespace<int>(Parameter);

	// !!! PARSING vo FIRST PHASE NEZBEHNE USPESNE, pretoze NEDOKAZE urcit ci CODE [TwoPhaseLookupFunctionInNamespace] reprezentuje TEMPLATE. Je to preto, lebo LOOKUP vyzaduje ARGUMENT DEPENDENT LOOKUP, kedze PARAMETER je definovany v separatnom NAMESPACE. A ARGUMENT DEPENDENT LOOKUP pre UNQUALIFIED DEPENDENT NAMES sa robi az v SECOND PHASE TWO PHASE LOOKUP.
	TwoPhaseLookupFunctionInNamespace<int>(Parameter);
}
//----------------------------------------------------------------------------------------------------------------------