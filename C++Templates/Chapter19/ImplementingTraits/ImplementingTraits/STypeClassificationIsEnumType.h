//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "STypeClassificationIsFundamentalType.h"
#include "STypeClassificationIsPointerType.h"
#include "STypeClassificationIsReferenceType.h"
#include "STypeClassificationIsArrayType.h"
#include "STypeClassificationIsMemberPointerType.h"
#include "STypeClassificationIsFunctionType.h"
#include "STypeClassificationIsClassType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
struct STypeClassificationIsEnumType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr bool									VALUE=STypeClassificationIsFundamentalType<TType>::VALUE==false && STypeClassificationIsPointerType<TType>::VALUE==false && STypeClassificationIsReferenceType<TType>::VALUE==false && STypeClassificationIsArrayType<TType>::VALUE==false && STypeClassificationIsMemberPointerType<TType>::VALUE==false && STypeClassificationIsFunctionType<TType>::VALUE==false && STypeClassificationIsClassType<TType>::VALUE==false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------