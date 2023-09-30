//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CExplicitInstantiationDeclaration final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		CExplicitInstantiationDeclaration(const TType& Value);
		virtual ~CExplicitInstantiationDeclaration(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CExplicitInstantiationDeclaration<TType>::CExplicitInstantiationDeclaration(const TType& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CExplicitInstantiationDeclaration<TType>::~CExplicitInstantiationDeclaration(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CExplicitInstantiationDeclaration<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void ExplicitInstantiationDeclarationFunction(const TType& Value)
{
	std::wcout << L"FUNCTION - TYPE [" << GetTypeInfoName<decltype(Value)>() <<"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Nasledujuci CODE obsahuje EXPLICIT INSTANTIATION DECLARATION pre TEMPLATE CLASS. EXPLICIT INSTANTIATION DECLARATION zabrani aby sa v TRANSLATION UNITS generoval CODE pre danu TEMPLATE s TEMPLATE ARGUMENTS.
extern template class CExplicitInstantiationDeclaration<int>;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Nasledujuci CODE obsahuje EXPLICIT INSTANTIATION DECLARATION pre TEMPLATE FUNCTION. EXPLICIT INSTANTIATION DECLARATION zabrani aby sa v TRANSLATION UNITS generoval CODE pre danu TEMPLATE s TEMPLATE ARGUMENTS.
extern template void ExplicitInstantiationDeclarationFunction<int>(const int& Value);
//----------------------------------------------------------------------------------------------------------------------