//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS implementuje RESTRICTED TEMPLATE EXPANSION PATTERN.
template<typename TType>
class CRestrictedTemplateExpansion final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! FRIEND FUNCTION bude viditelna aj na PARENT SCOPE, co je v tomto pripade NAMESPACE SCOPE.
		// !!!!! FRIEND FUNCTION vsak MUSI mat aspon 1 FUNCTION PARAMETER TYPE TEMPLATE CLASS [CRestrictedTemplateExpansion<TType>], aby vdaka ARGUMENT DEPENDENT LOOKUP bola v NAMESPACE SCOPE viditelna.
		friend void RestrictedTemplateExpansionFriendFunction(const CRestrictedTemplateExpansion<TType>& Value)
		{
			std::wcout << L"RESTRICTED TEMPLATE EXPANSION - FRIEND FUNCTION - VALUE [" << Value.MObject << L"]." << std::endl;
		}

	private:
		TType													MObject;

	public:
		CRestrictedTemplateExpansion(TType Object);
		virtual ~CRestrictedTemplateExpansion(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CRestrictedTemplateExpansion<TType>::CRestrictedTemplateExpansion(TType Object)
	: MObject(Object)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CRestrictedTemplateExpansion<TType>::~CRestrictedTemplateExpansion(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------