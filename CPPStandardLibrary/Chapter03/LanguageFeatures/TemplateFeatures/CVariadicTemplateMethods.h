//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CVariadicTemplateMethods
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! Definicia VARIADIC TEMPLATES. PARAMETER [FirstTypeParameter] reprezentuje 1. TYPE PARAMETER. PARAMETER [OtherTypeParameters] reprezentuje 2. az N. PARAMETERS.
		// !!!!! TYPE PARAMETER [TTypes] sa nazyva TEMPLATE PARAMETER PACK.
		template<typename TType, typename... TTypes>
		// !!!!! SYNTAX [TTypes...] rozbali vsetky ostatne TYPE PARAMETERS.
		void SimpleVariadicTemplateMethod(std::wstring* Prefix, std::wstring* Postfix, TType FirstTypeParameter, TTypes... OtherTypeParameters)
		{
			if (Prefix!=nullptr)
			{
				std::wcout << *Prefix;
			}

			std::wcout << L" [" << FirstTypeParameter << L"]";

			// !!! Rekurzivne sa vola VARIADIC TEMPLATE SimpleVariadicTemplateFunction().
			// !!!!! SYNTAX [OtherTypeParameters...] rozbali vsetky ostatne TYPE PARAMETERS.
			SimpleVariadicTemplateMethod(nullptr,Postfix,OtherTypeParameters...);
		}

		// !!!!! NON-TEMPLATE FUNCTION, ktora reprezentuje KONIEC REKURZIE.
		void SimpleVariadicTemplateMethod(std::wstring* Prefix, std::wstring* Postfix)
		{
			if (Prefix!=nullptr)
			{
				std::wcout << *Prefix;
			}

			if (Postfix!=nullptr)
			{
				std::wcout << *Postfix;
			}
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------