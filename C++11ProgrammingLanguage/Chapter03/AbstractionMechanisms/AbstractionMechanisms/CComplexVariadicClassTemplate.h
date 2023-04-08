//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
// !!! Definicia VARIADIC TEMPLATE CLASS.
template<typename... TItems>
class CComplexVariadicClassTemplate
{
//-------------------------------------------------------------------------------------------------------
	public:
		CComplexVariadicClassTemplate(void)
		{
			size_t												NumberOfItems=sizeof...(TItems);

			wcout << L"BASE CLASS - NumberOfItems [" << NumberOfItems << L"] !\n";
		}

		// !!! FUNCTION je NUTNA pre ukoncenie rekurzie.
		void DoRecursion(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! SPECIALIZATION VARIADIC TEMPLATE CLASS definovanej vyssie.
// !!!!! TYPE PARAMETER [TFirstItem] reprezentuje 1. TYPE PARAMETER CELEJ VARIADIC TEMPLATE [CComplexVariadicClassTemplate]. Vdaka nemu je mozne vykonat PEEL-OFF jednotlivych TYPE PARAMETERS a spracovat ich v COMPILE-TIME RECURSION.
template<typename TFirstItem, typename... TOtherItems>
class CComplexVariadicClassTemplate<TFirstItem,TOtherItems...> : private CComplexVariadicClassTemplate<TOtherItems...>
{
//-------------------------------------------------------------------------------------------------------
	private:
		TFirstItem												MFirstItem;

	public:
		CComplexVariadicClassTemplate<TOtherItems...>* GetBase(void)
		{
			CComplexVariadicClassTemplate<TOtherItems...>*		Base=static_cast<CComplexVariadicClassTemplate<TOtherItems...>*>(this);

			return(Base);
		}

		const TFirstItem& GetFirstItem(void)
		{
			return(MFirstItem);
		}

		void DoRecursion(void)
		{
			std::wcout << L"SIZEOF() [" << sizeof...(TOtherItems) << L"] VALUE [" << MFirstItem << "] !\n";

			CComplexVariadicClassTemplate<TOtherItems...>*		Base=static_cast<CComplexVariadicClassTemplate<TOtherItems...>*>(this);

			Base->DoRecursion();
		}

	public:
		CComplexVariadicClassTemplate(TFirstItem FirstItem, TOtherItems... OtherItems)
			: CComplexVariadicClassTemplate<TOtherItems...>(OtherItems...), MFirstItem(FirstItem)
		{
			size_t												NumberOfItems=sizeof...(TOtherItems);

			std::wcout << L"DERIVED CLASS - NumberOfItems [" << NumberOfItems << L"] !\n";
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------