//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!!!! Deklaracia VARIADIC TEMPLATE.
template<typename... TItems>
class CMyTuple
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Deklaracia TEMPLATE, ktora nema ZIADNE TEMPLATE PARAMETERS.
template<>
class CMyTuple<>
{
//-------------------------------------------------------------------------------------------------------
	public:
		static const size_t										SIZE=0;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Deklaracia TEMPLATE, ktora sluzi na REKURZIVNE spracovanie TEMPLATE PARAMETERS.
// !!! TEMPLATE PARAMETER [TTail] obsahuje VSETKY TEMPLATE PARAMETERS, okrem 1. TEMPLATE PARAMETER, ktory je reprezenovany TEMPLATE PARAMETER [THead].
// !!!!! Je NEVYHNUTNE vykonat INHERITANCE, aby CLASS mohla vratit TEMPLATE s ostavajucimi TEMPLATE PARAMETERS.
template<typename THead, typename... TTail>
class CMyTuple<THead,TTail...> : private CMyTuple<TTail...>
{
//-------------------------------------------------------------------------------------------------------
	private:
		THead													MHead;

	public:
		// !!! OPERATOR [sizeof...() vracia pocet TEMPLATE PARAMETERS, ktore su ZABALENE vo VARIADIC TEMPLATES PARAMETER.
		static const size_t										SIZE=sizeof...(TTail)+1;

	public:
		const THead& GetHead(void) const
		{
			return(MHead);
		}

		// !!! FUNCTION vracia novu TEMPLATE, ktora ma VSETKY PARAMETERS OKREM PRVEHO.
		const CMyTuple<TTail...>& GetTail(void) const
		{
			return(*this);
		}

	public:
		// !!! CODE [CMyTuple<TTail...>(Tail...)] znamena, ze sa vola 
		CMyTuple<THead,TTail...>(const THead& Head, const TTail&... Tail)
			: CMyTuple<TTail...>(Tail...), MHead(Head)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------