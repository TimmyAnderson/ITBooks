//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <utility>
#include "CComputedResultType.h"
#include "CTypeList.h"
#include "CCommonType.h"
#include "CTypeListFront.h"
#include "CTypeListPopFront.h"
#include "CTypeListAccumulate.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename TVisitor, typename... TElementTypes>
class CVisitResultType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=TReturnValue;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TVisitor, typename TType>
using															VisitElementResult=decltype(std::declval<TVisitor>()(std::declval<TType>()));
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre SENTINEL TYPE [CComputedResultType].
template<typename TVisitor, typename... TElementTypes>
class CVisitResultType<CComputedResultType,TVisitor,TElementTypes...>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		using													ResultTypes=CTypeList<VisitElementResult<TVisitor,TElementTypes>...>;

	public:
		using													TYPE=CTypeListAccumulate<CTypeListPopFront<ResultTypes>,CCommonType,CTypeListFront<ResultTypes>>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename TVisitor, typename... TElementTypes>
using															CVisitResult=typename CVisitResultType<TReturnValue,TVisitor,TElementTypes...>::TYPE;
//----------------------------------------------------------------------------------------------------------------------