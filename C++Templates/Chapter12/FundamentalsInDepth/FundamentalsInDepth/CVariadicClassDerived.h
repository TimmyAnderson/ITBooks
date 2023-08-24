//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS ma lubovolny pocet BASE CLASSES.
template<typename... TBaseTypes>
class CVariadicClassDerived final : public TBaseTypes...
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CString													MFieldDerived;

	private:
		template<typename TLocalBaseType, typename... TLocalBaseTypes>
		void InternalToString(std::wstringstream& Stream, TLocalBaseType BaseValue, TLocalBaseTypes... BaseValues) const;

	public:
		const CString& GetFieldDerived(void) const noexcept;

	public:
		std::wstring ToString(void) const;

	public:
		CVariadicClassDerived(const CString FieldDerived, TBaseTypes... BaseValues);
		virtual ~CVariadicClassDerived(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR vola COPY CONSTRUCTORS jednotlivych BASE CLASSES.
template<typename... TBaseTypes>
CVariadicClassDerived<TBaseTypes...>::CVariadicClassDerived(const CString FieldDerived, TBaseTypes... BaseValues)
	: TBaseTypes(BaseValues)..., MFieldDerived(FieldDerived)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TBaseTypes>
CVariadicClassDerived<TBaseTypes...>::~CVariadicClassDerived(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TBaseTypes>
template<typename TLocalBaseType, typename... TLocalBaseTypes>
void CVariadicClassDerived<TBaseTypes...>::InternalToString(std::wstringstream& Stream, TLocalBaseType BaseValue, TLocalBaseTypes... BaseValues) const
{
	Stream << L" " << BaseValue.ToString();

	if constexpr (sizeof...(TLocalBaseTypes))
	{
		InternalToString(Stream,BaseValues...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TBaseTypes>
const CString& CVariadicClassDerived<TBaseTypes...>::GetFieldDerived(void) const noexcept
{
	return(MFieldDerived);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TBaseTypes>
std::wstring CVariadicClassDerived<TBaseTypes...>::ToString(void) const
{
	std::wstringstream											Stream;

	Stream << "DERIVED CLASS - FIELD DERIVED [" << MFieldDerived << L"].";

	if constexpr (sizeof...(TBaseTypes)>0)
	{
		// !!!!! Vola sa VARIADIC TEMPLATE METHOD, ktora ako PARAMETERS dostane REFERENCES na jednotlive BASE CLASSES.
		InternalToString(Stream,static_cast<TBaseTypes>(*this)...);
	}

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------