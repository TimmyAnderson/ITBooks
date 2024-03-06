//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STraitsIfThenElse.h"
#include "STypeTraitIdentity.h"
#include "CTupleTypeListInterface.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je TUPLE, 2. TEMPLATE PARAMETER urcuje TYPE, ktory sa bude do TUPLE pridavat a 3. TEMPLATE PARAMETER urcuje COMPARE OPRATION.
template<typename TTuple, typename TType, template<typename,typename> class TCompare, bool EMPTY=CTupleTypeListIsEmpty<TTuple>::VALUE>
class CTupleInsertionSortInternalType;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTuple, typename TType, template<typename,typename> class TCompare>
class CTupleInsertionSortInternalType<TTuple,TType,TCompare,false>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! Urci novy TAIL rekurzivnym aplikovanim OPERARATION [TCompare] na TYPE [TType] a FRONT TYPE z TUPLE. Pri rekurzii sa vzdy ostranuje FRONT TYPE a hlada sa TYPE, pre ktory splna OPERARATION [TCompare] vracia TRUE.
		using													NewTail=typename STraitsIfThenElseUsing<TCompare<TType,typename CTupleTypeListFrontType<TTuple>::TYPE>::VALUE,STypeTraitIdentity<TTuple>,CTupleInsertionSortInternalType<typename CTupleTypeListPopFrontType<TTuple>::TYPE,TType,TCompare>>::TYPE;

		// !!! Urci novy HEAD aplikovanim OPERARATION [TCompare] na TYPE [TType] a FRONT TYPE z TUPLE.
		using													NewHead=STraitsIfThenElseUsing<TCompare<TType,typename CTupleTypeListFrontType<TTuple>::TYPE>::VALUE,TType,typename CTupleTypeListFrontType<TTuple>::TYPE>;

	public:
		// !!! Prida novy HEAD na zaciatok noveho TAIL.
		using													TYPE=typename CTupleTypeListPushFrontType<NewTail,NewHead>::TYPE;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTuple, typename TType, template<typename,typename> class TCompare>
class CTupleInsertionSortInternalType<TTuple,TType,TCompare,true> : public CTupleTypeListPushFrontType<TTuple,TType>
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTuple, typename TType, template<typename,typename> class TCompare>
using															CTupleInsertionSortInternal=typename CTupleInsertionSortInternalType<TTuple,TType,TCompare>::TYPE;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je TUPLE a 2. TEMPLATE PARAMETER urcuje COMPARE OPRATION.
template<typename TTuple, template<typename,typename> class TCompare, bool EMPTY=CTupleTypeListIsEmpty<TTuple>::VALUE>
class CTupleInsertionSortType;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION spusta rekurzivne volanie CLASS [CTupleInsertionSortInternalType<>].
template<typename TTuple, template<typename,typename> class TCompare>
class CTupleInsertionSortType<TTuple,TCompare,false> : public CTupleInsertionSortInternalType<typename CTupleInsertionSortType<typename CTupleTypeListPopFrontType<TTuple>::TYPE,TCompare>::TYPE,typename CTupleTypeListFrontType<TTuple>::TYPE,TCompare>
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTuple, template<typename,typename> class TCompare>
class CTupleInsertionSortType<TTuple,TCompare,true>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=TTuple;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTuple, template<typename,typename> class TCompare>
using															CTupleInsertionSort=typename CTupleInsertionSortType<TTuple,TCompare>::TYPE;
//----------------------------------------------------------------------------------------------------------------------