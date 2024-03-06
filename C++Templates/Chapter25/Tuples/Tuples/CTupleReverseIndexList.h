//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTuple.h"
#include "CMakeIndexListType.h"
#include "CTupleTypeListInterface.h"
#include "CValueList.h"
#include "CCompileTimeValue.h"
#include "CTupleReverseType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTupleElements, size_t... INDICES>
typename CTupleReverseType<CTuple<TTupleElements...>>::TYPE TupleReverseIndexListInternal(const CTuple<TTupleElements...>& Tuple,CValueList<size_t,INDICES...>)
{
	typename CTupleReverseType<CTuple<TTupleElements...>>::TYPE	Result=MakeTuple(TupleGet<INDICES>(Tuple)...);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTupleElements>
typename CTupleReverseType<CTuple<TTupleElements...>>::TYPE TupleReverseIndexList(const CTuple<TTupleElements...>& Tuple)
{
	typename CTupleReverseType<CTuple<TTupleElements...>>::TYPE	Result=TupleReverseIndexListInternal(Tuple,typename CTupleReverseType<CMakeIndexList<sizeof...(TTupleElements)>>::TYPE());

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------