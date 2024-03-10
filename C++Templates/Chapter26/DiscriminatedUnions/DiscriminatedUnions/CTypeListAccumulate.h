//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTypeList.h"
#include "CTypeListIsEmpty.h"
#include "CTypeListFront.h"
#include "CTypeListPopFront.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! 1. TEMPLATE PARAMETER je TYPE LIST a 2. TEMPLATE PARAMETER OPERATION, ktora sa ma aplikovat na kazdu dvojicu TYPES v TYPE LIST a 3. TEMPLATE PARAMETER je INITIAL TYPE.
template<typename TTypeList, template<typename,typename> class TOperation, typename TType, bool EMPTY=CTypeListIsEmpty<TTypeList>>
class CTypeListAccumulateType;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OPERATION odstrani FRONT TYPE z TYPE LIST a aplikuje OPERATION na FRONT TYPE a INITIAL TYPE (ktory sa pri rekurzivnom prechode stale meni).
template<typename TTypeList, template<typename,typename> class TOperation, typename TType>
class CTypeListAccumulateType<TTypeList,TOperation,TType,false> : public CTypeListAccumulateType<CTypeListPopFront<TTypeList>,TOperation,typename TOperation<TType,CTypeListFront<TTypeList>>::TYPE>
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList, template<typename,typename> class TOperation, typename TType>
class CTypeListAccumulateType<TTypeList,TOperation,TType,true>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! Vracia INITIAL TYPE.
		using													TYPE=TType;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TTypeList, template<typename,typename> class TOperation, typename TType>
using															CTypeListAccumulate=typename CTypeListAccumulateType<TTypeList,TOperation,TType>::TYPE;
//----------------------------------------------------------------------------------------------------------------------