//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <codecvt>
//-----------------------------------------------------------------------------
// !!!!! Podla C++ DOCUMENTATION je NUTNE vykonat DERIVATION z CLASS [codecvt<TElement,TByte,TState>], pretoze ta definuje PROTECTED DESTRUCTOR.
template<class TElement, class TByte, class TState>
class CCustomCodeConverter : public std::codecvt<TElement,TByte,TState>
{
//-----------------------------------------------------------------------------
	public:
		virtual ~CCustomCodeConverter(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------