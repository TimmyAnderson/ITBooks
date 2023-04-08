//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
//-------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje TYPE FUNCTION, ktora vykonava jednoducho kalkulaciu, pricom vracia TYPE, ktory zabera v MEMORY viac BYTES.
template<typename TType1, typename TType2>
class CBiggerTypeTypeFunction
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! Je tu pouzita COMPILE TIME CONDITION.
		using													BiggerType=typename std::conditional<sizeof(TType1)>=sizeof(TType2),TType1,TType2>::type;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------