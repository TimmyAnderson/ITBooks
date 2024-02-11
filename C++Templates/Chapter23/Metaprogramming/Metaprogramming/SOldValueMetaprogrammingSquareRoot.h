//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS demonstruje stary sposob VALUE METAPROGRAMMING, ked neexistovali CONSTEXPR FUNCTIONS.
// !!! PRIMARY TEMPLATE CLASS pre RECURSIVE CASE.
template<int VALUE, int LOW=1, int HIGH=VALUE>
struct SOldValueMetaprogrammingSquareRoot final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		static constexpr int								Middle=((LOW+HIGH+1)/2);

	public:
		static constexpr int								Value=((VALUE<(Middle*Middle)) ? SOldValueMetaprogrammingSquareRoot<VALUE,LOW,Middle-1>::Value : SOldValueMetaprogrammingSquareRoot<VALUE,Middle,HIGH>::Value);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION pre FINAL CASE, ked plati EXPRESSION [LOW==HIGH]. TEMPLATE CLASS SPECIALIZATION zastavuje RECURSION.
template<int VALUE, int EQUAL>
struct SOldValueMetaprogrammingSquareRoot<VALUE,EQUAL,EQUAL> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr int									Value=EQUAL;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------