//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!!!! INTERFACE CLASS obsahuje INTERFACE pre FUNCTION OBJECT.
// !!!!! Klucove je, ze INTERFACE CLASS NEOBSAHUJE ako TYPE PARAMETER CALLBACK TYPE. To znamena, ze COMPILER NEGENERUJE osobitnu TEMPLATE INSTANTIATION pre kazdy CALLBACK TYPY ako je POINTER na FUNCTION, REFERENCE na FUNCTION, pre kazdy TYPE FUNCTION OBJECT ci kazdy TYPE LAMBDA EXPRESSIONS.
// !!!!! Vdaka tomu, ze INTERFACE NEOBSAHUJE TYPE FUNCTION OBJECT, tak CLASS [CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>] je generovana IBA RAZ pre rozlicne CALLBACK TYPES, ako je napriklad POINTER na FUNCTION, REFERENCE na FUNCTION, FUNCTION OBJECTS ci LAMBDA EXPRESSIONS.
// !!!!! Vysledkom je, ze sa generuje KRATSI CODE, kedze TEMPLATE INSTANTIATION CLASS [CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>] sa pre rozlicne CALLBACK TYPES generuje IBA RAZ.
template<typename TReturnValue, typename... TParameters>
class CTypeErasureCallbackWrapperBridgeInterface
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		virtual CTypeErasureCallbackWrapperBridgeInterface* Clone(void) const=0;
		virtual TReturnValue Invoke(TParameters... Parameters) const=0;
		virtual bool Equals(const CTypeErasureCallbackWrapperBridgeInterface* Bridge) const=0;

	public:
		virtual ~CTypeErasureCallbackWrapperBridgeInterface(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapperBridgeInterface<TReturnValue,TParameters...>::~CTypeErasureCallbackWrapperBridgeInterface(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------