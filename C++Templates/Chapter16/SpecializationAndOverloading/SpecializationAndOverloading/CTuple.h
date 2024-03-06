//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <sstream>
#include "MyDebug.h"
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
class CTuple;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<>
class CTuple<> final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
class CTuple<TType,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
	template<typename... TLocalTypes>
	friend class CTuple;
#else
	template<typename... TLocalTypes>
	friend void CTuple<TLocalTypes...>::PrintInternal(size_t Index, std::wstringstream& Stream) const;
#endif

	private:
		TType													MValue;
		CTuple<TTypes...>										MValues;

	private:
		void PrintInternal(size_t Index, std::wstringstream& Stream) const;

	public:
		const TType& GetValue(void) const noexcept;
		const CTuple<TTypes...>& GetValues(void) const noexcept;

	public:
		CString Print(const CString& Value) const;

	public:
		CTuple(TType Value, TTypes... Values);
		virtual ~CTuple(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CTuple<TType,TTypes...>::CTuple(TType Value, TTypes... Values)
	: MValue(Value), MValues(Values...)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CTuple<TType,TTypes...>::~CTuple(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void CTuple<TType,TTypes...>::PrintInternal(size_t Index, std::wstringstream& Stream) const
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
const TType& CTuple<TType,TTypes...>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
const CTuple<TTypes...>& CTuple<TType,TTypes...>::GetValues(void) const noexcept
{
	return(MValues);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CString CTuple<TType,TTypes...>::Print(const CString& Value) const
{
	std::wstringstream											Stream;

	Stream << Value << std::endl;

	PrintInternal(1,Stream);

	CString														Text(Stream.str());

	return(Text);
}
//----------------------------------------------------------------------------------------------------------------------