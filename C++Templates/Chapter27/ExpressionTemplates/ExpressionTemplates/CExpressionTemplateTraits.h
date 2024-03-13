//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CExpressionTemplateScalar;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE CLASS pre NON-SCALAR TYPES vracia CONST REFERENCE.
template<typename TType>
class CExpressionTemplateTraits
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=const TType&;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION pre SCALAR TYPES vracia VALUE.
template<typename TType>
class CExpressionTemplateTraits<CExpressionTemplateScalar<TType>>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=CExpressionTemplateScalar<TType>;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------