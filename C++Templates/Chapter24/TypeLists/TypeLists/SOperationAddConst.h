//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
struct SOperationAddConstType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=const TType;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
using															SOperationAddConst=typename SOperationAddConstType<TType>::TYPE;
//----------------------------------------------------------------------------------------------------------------------