//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
class CParameterPacksTuple;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<>
class CParameterPacksTuple<> final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
class CParameterPacksTuple<TType,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
	template<typename... TLocalTypes>
	friend class CParameterPacksTuple;
#else
	template<typename... TLocalTypes>
	friend void CParameterPacksTuple<TLocalTypes...>::PrintInternal(size_t Index, std::wstringstream& Stream) const;
#endif

	private:
		TType													MValue;
		CParameterPacksTuple<TTypes...>							MValues;

	private:
		void PrintInternal(size_t Index, std::wstringstream& Stream) const;

	public:
		const TType& GetValue(void) const noexcept;
		const CParameterPacksTuple<TTypes...>& GetValues(void) const noexcept;

	public:
		std::wstring Print(void) const;

	public:
		CParameterPacksTuple(TType Value, TTypes... Values);
		virtual ~CParameterPacksTuple(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CParameterPacksTuple<TType,TTypes...>::CParameterPacksTuple(TType Value, TTypes... Values)
	: MValue(Value), MValues(Values...)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CParameterPacksTuple<TType,TTypes...>::~CParameterPacksTuple(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void CParameterPacksTuple<TType,TTypes...>::PrintInternal(size_t Index, std::wstringstream& Stream) const
{
	if (Index>1)
	{
		Stream << L" ";
	}

	Stream << L"PARAMETER [" << Index << L"] VALUE [" << MValue << L"]";

	if constexpr (sizeof...(TTypes)>0)
	{
		MValues.PrintInternal(Index+1,Stream);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
const TType& CParameterPacksTuple<TType,TTypes...>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
const CParameterPacksTuple<TTypes...>& CParameterPacksTuple<TType,TTypes...>::GetValues(void) const noexcept
{
	return(MValues);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
std::wstring CParameterPacksTuple<TType,TTypes...>::Print(void) const
{
	std::wstringstream											Stream;

	PrintInternal(1,Stream);

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------