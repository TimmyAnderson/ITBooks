//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STraitsIfThenElse.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS demonstruje stary sposob VALUE METAPROGRAMMING, ked neexistovali CONSTEXPR FUNCTIONS.
// !!!!! Je to OPTIMALNEJSIA VERZIA ako STRUCT [SOldValueMetaprogrammingSquareRoot], pretoze pouziva TYPE TRAIT [STraitsIfThenElseType], ktory zabranuje TEMPLATE CLASS INSTANTIATION aj pre FALSE CASES ako je to v pripade STRUCT [SOldValueMetaprogrammingSquareRoot].
// !!! PRIMARY TEMPLATE CLASS pre RECURSIVE CASE.
template<int VALUE, int LOW=1, int HIGH=VALUE>
struct SOldValueMetaprogrammingOptimumSquareRoot final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		static constexpr int									Middle=((LOW+HIGH+1)/2);

	private:
		// !!!!! Pouzitie TYPE TRAIT [STraitsIfThenElseType] zabranuje zbytocnemu TEMPLATE CLASS INSTANTIATION pre FALSE CASES.
		using													ComputedType=STraitsIfThenElseUsing<(VALUE<(Middle*Middle)),SOldValueMetaprogrammingOptimumSquareRoot<VALUE,LOW,Middle-1>,SOldValueMetaprogrammingOptimumSquareRoot<VALUE,Middle,HIGH>>;

	public:
		static constexpr int									Value=ComputedType::Value;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION pre FINAL CASE, ked plati EXPRESSION [LOW==HIGH]. TEMPLATE CLASS SPECIALIZATION zastavuje RECURSION.
template<int VALUE, int EQUAL>
struct SOldValueMetaprogrammingOptimumSquareRoot<VALUE,EQUAL,EQUAL> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr int									Value=EQUAL;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------