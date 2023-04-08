//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje EQUAL FUNCTOR (PREDICATE), ktory je mozne pouzit v COLLECTIONS.
class CIntEqualFunctor
{
	public:
		// !!! FUNCTOR musi mat pretazeny OPERATOR() s 1 PARAMETROM a BOOL ako RETURN VALUE.
		bool operator()(int Value);

	public:
		CIntEqualFunctor(void);
		virtual ~CIntEqualFunctor(void);
};
//-------------------------------------------------------------------------------------------------------