//-------------------------------------------------------------------------------------------------------
#include "Template.h"
//-------------------------------------------------------------------------------------------------------
template<typename TClassType>
CTemplate<typename TClassType>::CTemplate(TClassType Value)
	: MValue(Value)
{
}
//-------------------------------------------------------------------------------------------------------
template<typename TClassType>
CTemplate<typename TClassType>::~CTemplate(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TClassType>
TClassType CTemplate<typename TClassType>::GetValue(void)
{
	return(MValue);
}
//-------------------------------------------------------------------------------------------------------
template<typename TClassType>
template<typename TFunctionType>
TFunctionType CTemplate<typename TClassType>::GetValues(TFunctionType InValue, TClassType* OutValue)
{
	*OutValue=MValue;

	return(InValue);
}
//-------------------------------------------------------------------------------------------------------