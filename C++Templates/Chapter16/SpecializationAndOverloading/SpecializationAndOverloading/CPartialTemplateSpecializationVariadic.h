//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <sstream>
#include "MyDebug.h"
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DECLARATION PRIMARY TEMPLATE CLASS.
template<typename... TTypes>
class CPartialTemplateSpecializationVariadic;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<>
class CPartialTemplateSpecializationVariadic<> final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEFINITION TEMPLATE CLASS SPECIALIZATION.
template<typename TType, typename... TTypes>
// !!!!! Pocet TEMPLATE PARAMETERS v TEMPLATE CLASS SPECIALIZATION je rozdielny ako pocet TEMPLATE PARAMETERS v PRIMARY TEMPLATE.
class CPartialTemplateSpecializationVariadic<TType,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
	template<typename... TLocalTypes>
	friend class CPartialTemplateSpecializationVariadic;
#else
	template<typename... TLocalTypes>
	friend void CPartialTemplateSpecializationVariadic<TLocalTypes...>::PrintInternal(size_t Index, std::wstringstream& Stream) const;
#endif

	private:
		TType													MValue;
		CPartialTemplateSpecializationVariadic<TTypes...>										MValues;

	private:
		void PrintInternal(size_t Index, std::wstringstream& Stream) const;

	public:
		const TType& GetValue(void) const noexcept;
		const CPartialTemplateSpecializationVariadic<TTypes...>& GetValues(void) const noexcept;

	public:
		CString Print(const CString& Value) const;
		

	public:
		CPartialTemplateSpecializationVariadic(TType Value, TTypes... Values);
		virtual ~CPartialTemplateSpecializationVariadic(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CPartialTemplateSpecializationVariadic<TType,TTypes...>::CPartialTemplateSpecializationVariadic(TType Value, TTypes... Values)
	: MValue(Value), MValues(Values...)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CPartialTemplateSpecializationVariadic<TType,TTypes...>::~CPartialTemplateSpecializationVariadic(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void CPartialTemplateSpecializationVariadic<TType,TTypes...>::PrintInternal(size_t Index, std::wstringstream& Stream) const
{
	Stream << L"\tINDEX [" << Index << L"] TYPE [" << GetTypeInfoName<decltype(MValue)>() << L"] VALUE [" << MValue << L"]." << std::endl;

	if constexpr (sizeof...(TTypes)>0)
	{
		MValues.PrintInternal(Index+1,Stream);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
const TType& CPartialTemplateSpecializationVariadic<TType,TTypes...>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
const CPartialTemplateSpecializationVariadic<TTypes...>& CPartialTemplateSpecializationVariadic<TType,TTypes...>::GetValues(void) const noexcept
{
	return(MValues);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CString CPartialTemplateSpecializationVariadic<TType,TTypes...>::Print(const CString& Value) const
{
	std::wstringstream											Stream;

	Stream << Value << std::endl;

	PrintInternal(1,Stream);

	CString														Text(Stream.str());

	return(Text);
}
//----------------------------------------------------------------------------------------------------------------------