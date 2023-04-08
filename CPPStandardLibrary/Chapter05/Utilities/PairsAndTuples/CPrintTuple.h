//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <tuple>
//-------------------------------------------------------------------------------------------------------
// !!! VARIADIC TEMPLATE CLASS, ktora vykonava COMPILE-TIME RECURSION.
template<int INDEX, int MAX, typename... TParameters>
class CPrintTuple
{
//-------------------------------------------------------------------------------------------------------
	public:
		static void PrintItems(std::tuple<TParameters...> Tuple)
		{
			if (INDEX!=0)
			{
				std::wcout << ", ";
			}

			std::wcout << L"PARAMETER " << INDEX << " [";

			// Vypise 1. ITEM daneho TUPLE.
			std::wcout << std::get<INDEX>(Tuple);

			std::wcout << L"]";

			// !!!!! Rekurzivne vola VARIADIC TEMPLATE CLASS na vypisanie ostatnych ITEMS.
			CPrintTuple<INDEX+1,sizeof...(TParameters),TParameters...>::PrintItems(Tuple);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! VARIADIC TEMPLATE CLASS SPECIALIZATION, ktora UKONCUJE vykonavanie COMPILE-TIME RECURSION.
template<int MAX, typename... TParameters>
class CPrintTuple<MAX,MAX,TParameters...>
{
//-------------------------------------------------------------------------------------------------------
	public:
		static void PrintItems(std::tuple<TParameters...>)
		{
			// EMPTY.
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Pomocna FUNCTION, ktora vypise obsah TUPLE.
template<typename... TParameters>
void PrintTuple(std::wstring Prefix, std::tuple<TParameters...> Tuple)
{
	std::wcout << Prefix << L" [";

	CPrintTuple<0,sizeof...(TParameters),TParameters...>::PrintItems(Tuple);

	std::wcout << L"] !" << std::endl;
}
//-------------------------------------------------------------------------------------------------------