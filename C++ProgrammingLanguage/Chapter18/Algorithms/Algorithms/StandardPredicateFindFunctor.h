//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <functional>
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTOR CLASS zdedim zo STANDARDNEHO FUNCTOR CLASS.
// !!!!! Dedenie zo STANDARDNEHO BASE FUNCTOR velky zmysel NEMA.
class CStandardPredicateFindFunctor : std::unary_function<std::wstring,bool>
{
	private:
		std::wstring											MValueToCompare;

	public:
		bool operator()(std::wstring Param);

	public:
		CStandardPredicateFindFunctor(std::wstring ValueToCompare);
		virtual ~CStandardPredicateFindFunctor(void);
};
//-------------------------------------------------------------------------------------------------------