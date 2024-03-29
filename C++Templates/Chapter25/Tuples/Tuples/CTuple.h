//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <utility>
#include <iostream>
#include "CTupleGet.h"
#include "CTupleOperatorPrint.h"
#include "CCompileTimeValue.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION TUPLE CLASS.
template<typename... TTypes>
class CTuple;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION TUPLE CLASS pre RECURSIVE CASE.
template<typename THead, typename... TTail>
class CTuple<THead,TTail...>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		THead													MHead;
		CTuple<TTail...>										MTail;

	public:
		template<typename TType, TType INDEX>
		auto& operator[](CCompileTimeValue<TType,INDEX>);

	private:
		template<size_t INDEX, typename... TTypes>
		const auto& InternalGet(const CTuple<TTypes...>& Tuple) const;

	public:
		THead& GetHead(void);
		const THead& GetHead(void) const;
		CTuple<TTail...>& GetTail(void);
		const CTuple<TTail...>& GetTail(void) const;

	public:
		template<size_t INDEX>
		const auto& Get(void) const;

	public:
		CTuple(void);
		CTuple(const THead& Head, const CTuple<TTail...>& Tail);
		CTuple(const THead& Head, const TTail&... Tail);

		// !!!!! ENABLE IF sposobi, ze nedojde ku konfliktu medzi tymto CONSTRUCTOR a CONSTRUCTOR [CTuple(const THead& Head, const CTuple<TTail...>& Tail)].
		CTuple(const CTuple<THead,TTail...>& Other);

		virtual ~CTuple(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
CTuple<THead,TTail...>::CTuple(void)
	: MHead(), MTail()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
CTuple<THead,TTail...>::CTuple(const THead& Head, const CTuple<TTail...>& Tail)
	: MHead(Head), MTail(Tail)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
CTuple<THead,TTail...>::CTuple(const THead& Head, const TTail&... Tail)
	: MHead(Head), MTail(Tail...)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
CTuple<THead,TTail...>::CTuple(const CTuple<THead,TTail...>& Other)
	: MHead(Other.GetHead()), MTail(Other.GetTail())
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
CTuple<THead,TTail...>::~CTuple(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
template<typename TType, TType INDEX>
auto& CTuple<THead,TTail...>::operator[](CCompileTimeValue<TType,INDEX>)
{
	auto&														Result=TupleGet<INDEX>(*this);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool operator==(const CTuple<>&, const CTuple<>&);
//----------------------------------------------------------------------------------------------------------------------
template<typename THead1, typename... TTail1, typename THead2, typename... TTail2, typename = std::enable_if_t<sizeof...(TTail1)==sizeof...(TTail2)>>
bool operator==(const CTuple<THead1,TTail1...>& Value1, const CTuple<THead2,TTail2...>& Value2)
{
	bool														Result=(Value1.GetHead()==Value2.GetHead() && Value1.GetTail()==Value2.GetTail());

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
std::wostream& operator<<(std::wostream& Stream, const CTuple<TTypes...>& Tuple)
{
	PrintTuple(Stream,Tuple,true);

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
template<size_t INDEX, typename... TTypes>
const auto& CTuple<THead,TTail...>::InternalGet(const CTuple<TTypes...>& Tuple) const
{
	if constexpr (INDEX>0)
	{
		const auto&												Value=Tuple.GetTail().template Get<INDEX-1>();

		return(Value);
	}
	else
	{
		const auto&												Value=Tuple.GetHead();

		return(Value);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
THead& CTuple<THead,TTail...>::GetHead(void)
{
	return(MHead);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
const THead& CTuple<THead,TTail...>::GetHead(void) const
{
	return(MHead);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
CTuple<TTail...>& CTuple<THead,TTail...>::GetTail(void)
{
	return(MTail);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
const CTuple<TTail...>& CTuple<THead,TTail...>::GetTail(void) const
{
	return(MTail);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename THead, typename... TTail>
template<size_t INDEX>
const auto& CTuple<THead,TTail...>::Get(void) const
{
	const auto&													Value=InternalGet<INDEX>(*this);

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION TUPLE CLASS pre TERMINAL CASE.
template<>
class CTuple<>
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
auto MakeTuple(TTypes&&... Elements)
{
	return(CTuple<std::decay_t<TTypes>...>(std::forward<TTypes>(Elements)...));
}
//----------------------------------------------------------------------------------------------------------------------