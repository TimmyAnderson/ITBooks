//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <string>
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class CMethodSpecializations
{
//-------------------------------------------------------------------------------------------------------
	public:
		// PRIMARY TEMPLATE.
		template<typename TType>
		TType TemplateMethod(TType Value)
		{
			wprintf_s(L"TEMPLATE METHOD [template<typename TType> TType TemplateMethod(TType Value)] CALLED !\n");

			return(Value);
		}
		
#ifdef _MSC_VER
		// TEMPLATE SPECIALIZATION.
		template<>
		std::wstring TemplateMethod<std::wstring>(std::wstring Value)
		{
			wprintf_s(L"TEMPLATE SPECIALIZATION [template<> wstring TemplateMethod<wstring>(wstring Value)] CALLED !\n");

			return(Value);
		}
		
		// TEMPLATE SPECIALIZATION.
		// !!! SYNTAX [<int>] je mozne odstranit.
		template<>
		int TemplateMethod(int Value)
		{
			wprintf_s(L"TEMPLATE SPECIALIZATION [template<> int TemplateMethod(int Value)] CALLED !\n");

			return(Value);
		}
#endif
		
		// !!! OVERLOADED METHOD. Toto NIE JE TEMPLATE SPECIALIZATION, pretoze CHYBA PREFIX [template<>].
		double TemplateMethod(double Value)
		{
			wprintf_s(L"OVERLOADED METHOD [double TemplateMethod(double Value)] CALLED !\n");

			return(Value);
		}
		
		// PRIMARY TEMPLATE.
		template<typename TType>
		TType OverloadedVSSpecialization(TType Value)
		{
			wprintf_s(L"TEMPLATE METHOD [template<typename TType> TType OverloadedVSSpecialization(TType Value)] CALLED !\n");

			return(Value);
		}
		
#ifdef _MSC_VER
		// TEMPLATE SPECIALIZATION.
		template<>
		int OverloadedVSSpecialization(int Value)
		{
			wprintf_s(L"TEMPLATE SPECIALIZATION [template<> int OverloadedVSSpecialization(int Value)] CALLED !\n");

			return(Value);
		}
#endif
		
		// !!! OVERLOADED METHOD. Toto NIE JE TEMPLATE SPECIALIZATION, pretoze CHYBA PREFIX [template<>].
		int OverloadedVSSpecialization(int Value)
		{
			wprintf_s(L"OVERLOADED METHOD [int OverloadedVSSpecialization(int Value)] CALLED !\n");

			return(Value);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! V G++ MUSIA byt METHOD SPECIALIZATIONS definovane VZDY v NON-CLASS SCOPE. To znaci, ze METHOD SPECIALIZATIONS MUSIA byt definovane MIMO BODY CLASS.
#ifndef _MSC_VER
//-------------------------------------------------------------------------------------------------------		
// TEMPLATE SPECIALIZATION.
template<>
std::wstring CMethodSpecializations::TemplateMethod<std::wstring>(std::wstring Value)
{
	wprintf_s(L"TEMPLATE SPECIALIZATION [template<> wstring TemplateMethod<wstring>(wstring Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------		
// TEMPLATE SPECIALIZATION.
// !!! SYNTAX [<int>] je mozne odstranit.
template<>
int CMethodSpecializations::TemplateMethod(int Value)
{
	wprintf_s(L"TEMPLATE SPECIALIZATION [template<> int TemplateMethod(int Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
// TEMPLATE SPECIALIZATION.
template<>
int CMethodSpecializations::OverloadedVSSpecialization(int Value)
{
	wprintf_s(L"TEMPLATE SPECIALIZATION [template<> int OverloadedVSSpecialization(int Value)] CALLED !\n");

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------------