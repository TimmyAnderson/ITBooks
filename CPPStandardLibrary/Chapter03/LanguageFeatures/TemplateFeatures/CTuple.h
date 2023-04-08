//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CException.h"
//-------------------------------------------------------------------------------------------------------
// !!!!! Lepsia verzia TUPLE pre prakticke pouzitie je vo FILE [CVariadicTemplate.h]. Tato verzia je pre studijne ucely.
//-------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje VARIADIC TEMPLATE.
// !!!!! CLASS zaroven reprezentuje FINAL STEP rekurzie.
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
// !!! CLASS reprezentuje TUPLE FIELD s INDEXOM [Index].
// !!!!! PARAMETER [TParameters] reprezentuje TYPE PARAMETERS VARIADIC TEMPLATE [CTuple].
template<size_t Index, typename... TParameters>
class CTupleElement
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// CLASS je TEMPLATE CLASS SPECIALIZATION.
// !!! CLASS zaroven FINAL STEP rekurzie.
// !!!!! CLASS teda reprezentuje VYSLEDOK TYPE FUNCTION pouzitej vo FUNCTION CTuple::Get<Index>(), teda TYPE, ktory je asociovany s INDEXOM [Index].
template<typename TFirstParameter, typename... TOtherParameters>
class CTupleElement<0,TFirstParameter,TOtherParameters...>
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! ALIAS reprezentuje CTuple. Tento ALIAS urcuje TYPE na ktory TEMPLATE METHOD Get<Index>() pretypuje THIS POINTER, aby sa prepracovala k tej verzii BASE CLASS (CTuple<>), ktora v TYPE PARAMETER [TFirstParameter] obsahuje VALUE FIELD s INDEXOM [Index].
		using													TYPE_TUPLE=CTuple<TFirstParameter,TOtherParameters...>;
		// ALIAS reprezentuje VALUE TUPLE ELEMENT s INDEXOM [Index].
		using													TYPE_VALUE=TFirstParameter;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// CLASS je TEMPLATE CLASS SPECIALIZATION.
// !!! CLASS zaroven reprezentuje RECURSION STEP rekurzie.
// !!! Rekurzia je realizovana pomocou INHERITANCE, kde CLASS dedi z (Index-1) instancie samej seba.
// !!! Pocas REKURZIE implementovanej dedenim sa osupe (PEEL OFF) vzdy prvy TYPE PARAMETER [TFirstParameter].
template<size_t Index, typename TFirstParameter, typename... TOtherParameters>
class CTupleElement<Index,TFirstParameter,TOtherParameters...> : public CTupleElement<Index-1,TOtherParameters...>
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje VARIADIC TEMPLATE SPECIALIZATION.
// !!!!! CLASS zaroven reprezentuje RECURSION STEP rekurzie.
// !!! TYPE PARAMETER [TFirstParameter] reprezentuje 1. TYPE PARAMETER zo VSETKYCH TYPE PARAMETERS v TYPE PARAMETER PACK.
template<typename TFirstParameter, typename... TOtherParameters>
class CTuple<TFirstParameter,TOtherParameters...> : private CTuple<TOtherParameters...>
{
//-------------------------------------------------------------------------------------------------------
	private:
		TFirstParameter											MValue;

	public:
		using													TYPE=TFirstParameter;

	public:
		// !!! Tato FUNCTION by mala byt skor PRIVATE. Na ukazku jej pouzitia je definovana ako PUBLIC.
		const CTuple<TOtherParameters...>& GetBase(void) const
		{
			const CTuple<TOtherParameters...>&					Base=static_cast<const CTuple<TOtherParameters...>&>(*this);

			return(Base);
		}

	public:
		void PrintItems(void) const
		{
			std::wcout << " [" << MValue << "]";

			// !!! Rekurzivne sa vola ta ista FUNCTION pre BASE CLASS, cim dochadza k PEEL OFF TYPE ARGUMENTS.
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
		// STATIC METHOD.
		template<size_t Index, typename... TTypes>
		static typename CTupleElement<Index,TTypes...>::TYPE_VALUE StaticGetItem(CTuple<TTypes...>& Tuple)
		{
			using												TUPLE=typename CTupleElement<Index,TTypes...>::TYPE_TUPLE;

			return(((TUPLE&)Tuple).GetValue());
		}

		// !!! METHOD vrati ITEM s INDEXOM [Index].
		// !!!!! RETURN VALUE je ALIAS [TYPE_VALUE], ktory sa subsituuje za TYPE [TFirstParameter].
		/*
			METHOD GetItem<Index>() funguje nasledujucim sposobom.

			!!! 1. Na to, aby METHOD GetItem<Index>() mohla vratit FIELD s INDEXOM [Index] je nutne najst BASE CLASS CLASS [CTuple], ktorej TYPE PARAMETER [TFirstParameter] reprezentuje TYPE FIELD s INDEXOM [Index]. Zaroven METHOD GetValue() tejto BASE CLASS vracia hodnotu daneho FIELD.
			2. Na najdenie spravnej BASE CLASS sa definuje pomocna VARIADIC TEMPLATE [CTupleElement<Index,TParameters...>].
			3. VARIADIC TEMPLATE [CTupleElement<Index,TParameters...>] podobne ako TEMPLATE [CTuple] REKURZIVNE DEDI zo SAMEJ SEBA.
			!!! 4. VARIADIC TEMPLATE [CTupleElement<Index,TParameters...>] pri dedeni zaroven ZNIZUJE HODNOTU INDEXU [Index]. To znaci, ze CLASS [CTupleElement<Index,TParameters...>] je zdedena z CLASS [CTupleElement<Index-1,TParameters...>].
			!!!!! 5. Ak sa zavola METHOD GetItem<Index>() s INDEXOM [Index] C++ vygeneruje CLASS [CTupleElement<Index,TParameters...>], ktora dedi z CLASS [CTupleElement<Index-1,TParameters...>]. V procese dedenia sa vykonava PEEL OFF jednotlivych TYPE PARAMETERS, az kym nie je vytvorena CLASS [CTupleElement<0,TParameters...>]. To znaci, ze napriklad volanie METHOD GetItem<2>() pre [CTuple<bool,short,int,float,double>] C++ vygeneruje CLASS [CTupleElement<Index,TParameters...>] nasledujucim sposobom.
			   A. Vytvori sa CLASS [CTupleElement<3,bool,short,int,float,double>].
			   B. CLASS [CTupleElement<3,bool,short,int,float,double>] je zdedena z CLASS [CTupleElement<2,short,int,float,double>]. Ako je vidiet 1. TYPE PARAMETER z povodnej CLASS [bool] bol odstraneny.
			   C. BASE CLASS [CTupleElement<2,short,int,float,double>] je zdedena z CLASS [CTupleElement<1,int,float,double>]. Ako je vidiet 2. TYPE PARAMETER z povodnej CLASS [short] bol odstraneny.
			   D. BASE CLASS [CTupleElement<1,int,float,double>] je zdedena z CLASS [CTupleElement<0,float,double>]. Ako je vidiet 3. TYPE PARAMETER z povodnej CLASS [int] bol odstraneny.
			  !!!!! E. Pre BASE CLASS [CTupleElement<0,float,double>] C++ pouzije TEMPLATE CLASS SPECIALIZATION, ktora pre CLASS [CTupleElement] s INDEXOM [Index==0] bola definovana.
			!!!!! 6. CLASS SPECIALIZATION [CTupleElement<0,float,double>] obsahuje definiciu 2 ALIASES.
			   A. ALIAS [TYPE_TUPLE] reprezentuje CLASS [CTuple].
			   B. ALIAS [TYPE_VALUE] reprezentuje TYPE PARAMETER FIELD s INDEXOM [Index].
			!!! 7. METHOD GetItem<Index>() pouzije ALIAS [TYPE_VALUE] na definovanie svojej RETURN VALUE.
			!!! 8. METHOD GetItem<Index>() pouzije ALIAS [TYPE_VALUE] na najdenie BASE CLASS CLASS [CTuple], ktorej TYPE PARAMETER [TFirstParameter] reprezentuje TYPE FIELD s INDEXOM [Index] a METHOD GetValue() vracia VALUE tohto FIELD.
			9. Po pretypovani THIS PARAMETER na TYPE reprezentovany ALIAS [TYPE_VALUE] METHOD zavola METHOD GetValue(), ktorym ziska hodnotu FIELD s INDEXOM [Index], cim je pozadovana hodnota najdena.
		*/
		template<size_t Index>
		const typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TYPE_VALUE& GetItem(void) const
		{
			static_assert(Index>=0 && Index<(sizeof...(TOtherParameters)+1),"PARAMETER Index is OUT of BOUNDS !");

			// !!! TYPE [TUPLE] reprezentuje TYPE CTuple pre [INDEX=Index], ktory je ulozeny v ALIAS [TYPE_TUPLE].
			using												TUPLE=typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TYPE_TUPLE;
			// !!! Vykona sa konverzia THIS na BASE TYPE, ktoreho TYPE PARAMETER [TFirstParameter] zodpoveda INDEXU [Index].
			const TUPLE&										This=((TUPLE&)*this);

			return(This.GetValue());
		}

	public:
		CTuple(const TFirstParameter& Value, const TOtherParameters&... Values)
			: CTuple<TOtherParameters...>(Values...), MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------