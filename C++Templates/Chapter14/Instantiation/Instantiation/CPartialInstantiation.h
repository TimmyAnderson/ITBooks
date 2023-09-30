//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType PartialInstantiationFunction(TType Value)
{
	TType														Result=(2*Value);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ VYKONA iba PARTIAL INSTANTIATION TEMPLATE FUNCTION [TType PartialInstantiationFunction(TType Value)], pretoze potrebuje zistit iba TYPE je RETURN VALUE.
decltype(PartialInstantiationFunction(2))						PartialInstantiationVariable1=2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CPartialInstantiation
{
	private:
		using													TLocalType=typename TType::Type;
};
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ VYKONA iba PARTIAL INSTANTIATION TEMPLATE CLASS [CPartialInstantiation<TType>], pretoze POINTER VARIABLE nepotrebuje DEFINITION TEMPLATE CLASS, ale staci jej iba DECLARATION TEMPLATE CLASS.
// !!!!! Ak by C++ vykonalo FULL INSTANTIATION, tak by COMPILER generoval ERROR, pretoze TYPE [int] NEMA SUBTYPE [Type].
CPartialInstantiation<int>*										PartialInstantiationVariable2=nullptr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType															PartialInstantiationVariableTemp=TType::default_value();
//----------------------------------------------------------------------------------------------------------------------
// !!!!! C++ VYKONA iba PARTIAL INSTANTIATION TEMPLATE VARIABLE [PartialInstantiationVariableTemp], pretoze VARIABLE potrebuje iba TYPE TEMPLATE VARIABLE [PartialInstantiationVariableTemp], a nie je VALUE.
// !!!!! Ak by C++ vykonalo FULL INSTANTIATION, tak by COMPILER generoval ERROR, pretoze TYPE [int] NEMA STATIC METHOD [default_value()].
decltype(PartialInstantiationVariableTemp<int>)					PartialInstantiationVariable3=100;
//----------------------------------------------------------------------------------------------------------------------