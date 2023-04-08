//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// CLASS reprezentuje modelovu implementaciu VARIADIC TEMPLATE.
template<typename... TParameters>
class CVariadicTemplate
{
//-------------------------------------------------------------------------------------------------------
	public:
		template<typename TType, int Index>
		const TType& GetItem(void) const
		{
			// EMPTY.
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<size_t Index, typename... TParameters>
class CVariadicTemplateElement
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TFirstParameter, typename... TOtherParameters>
class CVariadicTemplateElement<0,TFirstParameter,TOtherParameters...>
{
//-------------------------------------------------------------------------------------------------------
	public:
		using													TYPE_VARIADIC_TEMPLATE=CVariadicTemplate<TFirstParameter,TOtherParameters...>;
		using													TYPE_VALUE=TFirstParameter;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<size_t Index, typename TFirstParameter, typename... TOtherParameters>
class CVariadicTemplateElement<Index,TFirstParameter,TOtherParameters...> : public CVariadicTemplateElement<Index-1,TOtherParameters...>
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TFirstParameter, typename... TOtherParameters>
class CVariadicTemplate<TFirstParameter,TOtherParameters...> : private CVariadicTemplate<TOtherParameters...>
{
//-------------------------------------------------------------------------------------------------------
	private:
		TFirstParameter											MValue;

	private:
		const CVariadicTemplate<TOtherParameters...>& GetBase(void) const
		{
			const CVariadicTemplate<TOtherParameters...>&		Base=static_cast<const CVariadicTemplate<TOtherParameters...>&>(*this);

			return(Base);
		}

	public:
		const TFirstParameter& GetValue(void) const
		{
			return(MValue);
		}

	public:
		template<size_t Index>
		const typename CVariadicTemplateElement<Index,TFirstParameter,TOtherParameters...>::TYPE_VALUE& GetItem(void) const
		{
			static_assert(Index>=0 && Index<(sizeof...(TOtherParameters)+1),"PARAMETER Index is OUT of BOUNDS !");

			using												ELEMENT=typename CVariadicTemplateElement<Index,TFirstParameter,TOtherParameters...>::TYPE_VARIADIC_TEMPLATE;
			const ELEMENT&										This=((ELEMENT&)*this);

			return(This.GetValue());
		}

	public:
		CVariadicTemplate(const TFirstParameter& Value, const TOtherParameters&... Values)
			: CVariadicTemplate<TOtherParameters...>(Values...), MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------