//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include "MyDebug.h"
#include "CException.h"
//-------------------------------------------------------------------------------------------------------
template<typename... TParameters>
class CTuple
{
//-------------------------------------------------------------------------------------------------------
	public:
		void PrintItems(void) const
		{
		}

		template<typename TType, int Index>
		const TType& GetItem(void) const
		{
			throw(CException(L"INDEX is OUT of BOUNDS !"));
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<size_t Index, typename... TParameters>
class CTupleElement
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TFirstParameter, typename... TOtherParameters>
class CTupleElement<0,TFirstParameter,TOtherParameters...>
{
//-------------------------------------------------------------------------------------------------------
	public:
		using													TYPE_TUPLE=CTuple<TFirstParameter,TOtherParameters...>;
		using													TYPE_VALUE=TFirstParameter;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<size_t Index, typename TFirstParameter, typename... TOtherParameters>
class CTupleElement<Index,TFirstParameter,TOtherParameters...> : public CTupleElement<Index-1,TOtherParameters...>
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TFirstParameter, typename... TOtherParameters>
class CTuple<TFirstParameter,TOtherParameters...> : private CTuple<TOtherParameters...>
{
//-------------------------------------------------------------------------------------------------------
	private:
		TFirstParameter											MValue;

	public:
		using													TYPE=TFirstParameter;

	public:
		const CTuple<TOtherParameters...>& GetBase(void) const
		{
			const CTuple<TOtherParameters...>&					Base=static_cast<const CTuple<TOtherParameters...>&>(*this);

			return(Base);
		}

	public:
		void PrintItems(void) const
		{
			std::wcout << " [" << MValue << "]";

			const CTuple<TOtherParameters...>&					Base=GetBase();

			Base.PrintItems();
		}

	public:
		void Print(const std::wstring& Prefix) const
		{
			std::wcout << Prefix;

			PrintItems();

			std::wcout << L" !" << std::endl;
		}

	public:
		const TFirstParameter& GetValue(void) const
		{
			return(MValue);
		}

	public:
		template<size_t Index>
		const typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TYPE_VALUE& GetItem(void) const
		{
			static_assert(Index>=0 && Index<(sizeof...(TOtherParameters)+1),"PARAMETER Index is OUT of BOUNDS !");

			using												TUPLE=typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TYPE_TUPLE;
			const TUPLE&										This=((TUPLE&)*this);

			return(This.GetValue());
		}

	public:
		CTuple(const TFirstParameter& Value, const TOtherParameters&... Values)
			: CTuple<TOtherParameters...>(Values...), MValue(Value)
		{
			std::wcout << L"CTuple CONSTRUCTOR CALLED for VALUE [" << MValue << L"] !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------