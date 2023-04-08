//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje COMPARATOR FUNCTOR, ktory je mozne pouzit v COLLECTIONS.
class CMyIntComparatorFunctor
{
	public:
		// !!! FUNCTOR musi mat pretazeny OPERATOR() s 2 PARAMETRAMI a BOOL ako RETURN VALUE.
		bool operator()(int Value1, int Value2);

	public:
		CMyIntComparatorFunctor(void);
		virtual ~CMyIntComparatorFunctor(void);
};
//-------------------------------------------------------------------------------------------------------