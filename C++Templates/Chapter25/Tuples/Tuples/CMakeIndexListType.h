//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CValueList.h"
#include "CCompileTimeValue.h"
#include "CTupleTypeListInterface.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t INDEX, typename TResult=CValueList<size_t>>
class CMakeIndexListType : public CMakeIndexListType<INDEX-1,typename CTupleTypeListPushFrontType<TResult,CCompileTimeValue<size_t,INDEX-1>>::TYPE>
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TResult>
class CMakeIndexListType<0,TResult>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=TResult;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t INDEX>
using															CMakeIndexList=typename CMakeIndexListType<INDEX>::TYPE;
//----------------------------------------------------------------------------------------------------------------------