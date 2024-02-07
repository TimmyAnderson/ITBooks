//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <utility>
#include "CTypeErasureCallbackWrapperBridgeInterface.h"
#include "STypeErasureCallbackWrapperTryEquals.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS implementuje INTERFACE [CTypeErasureCallbackWrapperBridgeInterface<TReturnValue,TParameters>].
// !!!!! DERIVED CLASS je TEMPLATE CLASS, ktora uz OBSAHUJE ako TEMPLATE PARAMETER CALLBACK TYPE. To znamena, ze tato TEMPLATE CLASS je INSTANTIATED pre KAZDY CALLBACK TYPE.
// !!!!! Vyhodou pouzitia TYPE ERASURE PATTERN je, ze C++ vykonava TEMPLATE INSTANTIATION iba pre tieto MALE DERIVED CLASSES a nie pre daleko rozsiahlejsiu CLASS [CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>] co by viedlo ku generovaniu daleko vacsieho mnozstva BINARY CODE.
// !!!!! ALTERNATIVNOU IMPLEMENTACIOU by mohlo byt definovanie viacerych DERIVED CLASSES, kde kazda DERIVED CLASS by implementovala konkretny CALLBACK TYPE ako napriklad POINTER na FUNCTION, REFERENCE na FUNCTION, FUNCTION OBJECT ci TYPE LAMBDA EXPRESSION. To vsak nie je nutne, pretoze je v tomto pripade je mozne DERIVED CLASS pre VSETKY CALLBACK TYPES definovat ako TEMPLATE CLASS.
template<typename TFunctionObject, typename TReturnValue, typename... TParameters>
class CTypeErasureCallbackWrapperBridgeImplementation final : public CTypeErasureCallbackWrapperBridgeInterface<TReturnValue,TParameters...>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!!!! FIELD obsahuje konkretny CALLBACK TYPE. To znamena, ze tato TEMPLATE CLASS je INSTANTIATED pre KAZDY CALLBACK TYPE.
		TFunctionObject											MFunctionObject;

	public:
		virtual CTypeErasureCallbackWrapperBridgeImplementation* Clone(void) const override;
		virtual TReturnValue Invoke(TParameters... Parameters) const override;
		virtual bool Equals(const CTypeErasureCallbackWrapperBridgeInterface<TReturnValue,TParameters...>* Bridge) const override;

	public:
		template<typename TFunctionObjectForward>
		CTypeErasureCallbackWrapperBridgeImplementation(TFunctionObjectForward&& FunctionObject);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFunctionObject, typename TReturnValue, typename... TParameters>
template<typename TFunctionObjectForward>
CTypeErasureCallbackWrapperBridgeImplementation<TFunctionObject,TReturnValue,TParameters...>::CTypeErasureCallbackWrapperBridgeImplementation(TFunctionObjectForward&& FunctionObject)
	: MFunctionObject(std::forward<TFunctionObjectForward>(FunctionObject))
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFunctionObject, typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapperBridgeImplementation<TFunctionObject,TReturnValue,TParameters...>* CTypeErasureCallbackWrapperBridgeImplementation<TFunctionObject,TReturnValue,TParameters...>::Clone(void) const
{
	CTypeErasureCallbackWrapperBridgeImplementation*			Object=new CTypeErasureCallbackWrapperBridgeImplementation(MFunctionObject);

	return(Object);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TFunctionObject, typename TReturnValue, typename... TParameters>
TReturnValue CTypeErasureCallbackWrapperBridgeImplementation<TFunctionObject,TReturnValue,TParameters...>::Invoke(TParameters... Parameters) const
{
	return(MFunctionObject(std::forward<TParameters>(Parameters)...));
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TFunctionObject, typename TReturnValue, typename... TParameters>
bool CTypeErasureCallbackWrapperBridgeImplementation<TFunctionObject,TReturnValue,TParameters...>::Equals(const CTypeErasureCallbackWrapperBridgeInterface<TReturnValue,TParameters...>* Bridge) const
{
	auto														ConvertedBridge=dynamic_cast<const CTypeErasureCallbackWrapperBridgeImplementation*>(Bridge);

	if (ConvertedBridge!=nullptr)
	{
		bool													Result=STypeErasureCallbackWrapperTryEquals<TFunctionObject>::Equals(MFunctionObject,ConvertedBridge->MFunctionObject);

		return(Result);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------