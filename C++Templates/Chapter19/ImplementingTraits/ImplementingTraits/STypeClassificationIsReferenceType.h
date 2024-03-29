//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STypeClassificationIsLReferenceType.h"
#include "STypeClassificationIsRReferenceType.h"
#include "SOtherTraitsIfThenElse.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class STypeClassificationIsReferenceType final : public SOtherTraitsIfThenElse<STypeClassificationIsLReferenceType<TType>::VALUE,STypeClassificationIsLReferenceType<TType>,STypeClassificationIsRReferenceType<TType>>::TYPE
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------