//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STraitsIfThenElse.h"
#include "STypeTraitIdentity.h"
#include "CTypeListIsEmpty.h"
#include "CTypeListFront.h"
#include "CTypeListPopFront.h"
#include "CTypeListPushFront.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je TYPE LIST, 2. TEMPLATE PARAMETER urcuje TYPE, ktory sa bude do TYPE LIST pridavat a 3. TEMPLATE PARAMETER urcuje COMPARE OPRATION.
template<typename TTypeList, typename TType, template<typename,typename> class TCompare, bool EMPTY=CTypeListIsEmpty<TTypeList>>
class CTypeListInsertionSortInternalType;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList, typename TType, template<typename,typename> class TCompare>
class CTypeListInsertionSortInternalType<TTypeList,TType,TCompare,false>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! Urci novy TAIL rekurzivnym aplikovanim OPERARATION [TCompare] na TYPE [TType] a FRONT TYPE z TYPE LIST. Pri rekurzii sa vzdy ostranuje FRONT TYPE a hlada sa TYPE, pre ktory splna OPERARATION [TCompare] vracia TRUE.
		using													NewTail=typename STraitsIfThenElseUsing<TCompare<TType,CTypeListFront<TTypeList>>::VALUE,STypeTraitIdentity<TTypeList>,CTypeListInsertionSortInternalType<CTypeListPopFront<TTypeList>,TType,TCompare>>::TYPE;

		// !!! Urci novy HEAD aplikovanim OPERARATION [TCompare] na TYPE [TType] a FRONT TYPE z TYPE LIST.
		using													NewHead=STraitsIfThenElseUsing<TCompare<TType,CTypeListFront<TTypeList>>::VALUE,TType,CTypeListFront<TTypeList>>;

	public:
		// !!! Prida novy HEAD na zaciatok noveho TAIL.
		using													TYPE=CTypeListPushFront<NewTail,NewHead>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList, typename TType, template<typename,typename> class TCompare>
class CTypeListInsertionSortInternalType<TTypeList,TType,TCompare,true> : public CTypeListPushFrontType<TTypeList,TType>
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList, typename TType, template<typename,typename> class TCompare>
using															CTypeListInsertionSortInternal=typename CTypeListInsertionSortInternalType<TTypeList,TType,TCompare>::TYPE;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je TYPE LIST a 2. TEMPLATE PARAMETER urcuje COMPARE OPRATION.
template<typename TTypeList, template<typename,typename> class TCompare, bool EMPTY=CTypeListIsEmpty<TTypeList>>
class CTypeListInsertionSortType;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION spusta rekurzivne volanie CLASS [CTypeListInsertionSortInternalType<>].
template<typename TTypeList, template<typename,typename> class TCompare>
class CTypeListInsertionSortType<TTypeList,TCompare,false> : public CTypeListInsertionSortInternalType<typename CTypeListInsertionSortType<CTypeListPopFront<TTypeList>,TCompare>::TYPE,CTypeListFront<TTypeList>,TCompare>
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList, template<typename,typename> class TCompare>
class CTypeListInsertionSortType<TTypeList,TCompare,true>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=TTypeList;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList, template<typename,typename> class TCompare>
using															CTypeListInsertionSort=typename CTypeListInsertionSortType<TTypeList,TCompare>::TYPE;
//----------------------------------------------------------------------------------------------------------------------