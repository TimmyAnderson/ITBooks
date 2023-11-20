//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
class CPartialSpecializationTemplateClassLimitsVariadic final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void CPartialSpecializationTemplateClassLimitsVariadic<TTypes...>::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE CLASS [<TTypes...>] - TYPE [" << GetTypeInfoName<decltype(*this)>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTail, typename... TTypes>
class CPartialSpecializationTemplateClassLimitsVariadic<TTail,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTail, typename... TTypes>
void CPartialSpecializationTemplateClassLimitsVariadic<TTail,TTypes...>::Print(void) const
{
	std::wcout << L"TEMPLATE CLASS PARTIAL SPECIALIZATION [<TTail,TTypes...>] - TYPE [" << GetTypeInfoName<decltype(*this)>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER hodi ERROR, pretoze ak ma PARTIAL EXPLICIT SPECIALIZATION EXPANSION PACK, tak MUSI byt aplikovany ako POSLEDNY TEMPLATE ARGUMENT. A tu NIE JE.
/*
template<typename TTail, typename... TTypes>
class CPartialSpecializationTemplateClassLimitsVariadic<TTypes...,TTail> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTail, typename... TTypes>
void CPartialSpecializationTemplateClassLimitsVariadic<TTypes...,TTail>::Print(void) const
{
	std::wcout << L"TEMPLATE CLASS PARTIAL SPECIALIZATION [<TTypes...,TTail>] - TYPE [" << GetTypeInfoName<decltype(*this)>() << L"]." << std::endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTail, typename... TTypes>
class CPartialSpecializationTemplateClassLimitsVariadic<CPartialSpecializationTemplateClassLimitsVariadic<TTypes...>,TTail> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTail, typename... TTypes>
void CPartialSpecializationTemplateClassLimitsVariadic<CPartialSpecializationTemplateClassLimitsVariadic<TTypes...>,TTail>::Print(void) const
{
	std::wcout << L"TEMPLATE CLASS PARTIAL SPECIALIZATION [<CPartialSpecializationTemplateClassLimitsVariadic<TTypes...>,TTail>] - TYPE [" << GetTypeInfoName<decltype(*this)>() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------