//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
#include "CCRTPFacadePatternHiddenInterfaceInterface.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
class CCRTPFacadePatternHiddenInterfaceBase
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		const TDerivedObject& GetDerivedObject(void) const;

	private:
		TDerivedObject& GetDerivedObject(void);

	public:
		// !!!!! METHOD predstavuje PUBLIC INTERFACE, ktory vyuziva METHODS, ktore musi implementovat DERIVED CLASS [TDerivedObject].
		void Print(void) const;

	public:
		CCRTPFacadePatternHiddenInterfaceBase(void);
		virtual ~CCRTPFacadePatternHiddenInterfaceBase(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPFacadePatternHiddenInterfaceBase<TDerivedObject>::CCRTPFacadePatternHiddenInterfaceBase(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPFacadePatternHiddenInterfaceBase<TDerivedObject>::~CCRTPFacadePatternHiddenInterfaceBase(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
const TDerivedObject& CCRTPFacadePatternHiddenInterfaceBase<TDerivedObject>::GetDerivedObject(void) const
{
	// !!!!! Vrati REFERENCE na DERIVED OBJECT, ktory je TYPE DERIVED OBJECT.
	const TDerivedObject&										DerivedObject=*(static_cast<const TDerivedObject*>(this));

	return(DerivedObject);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
TDerivedObject& CCRTPFacadePatternHiddenInterfaceBase<TDerivedObject>::GetDerivedObject(void)
{
	// !!!!! Vrati REFERENCE na DERIVED OBJECT, ktory je TYPE DERIVED OBJECT.
	TDerivedObject&												DerivedObject=*(static_cast<TDerivedObject*>(this));

	return(DerivedObject);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
void CCRTPFacadePatternHiddenInterfaceBase<TDerivedObject>::Print(void) const
{
	const TDerivedObject&										DerivedObject=GetDerivedObject();

	// !!!!! Vola sa METHOD TYPE [TDerivedObject], ktoru musi implementovat DERIVED CLASS.
	CString														Prefix=CCRTPFacadePatternHiddenInterfaceInterface::GetPrefix(DerivedObject);

	// !!!!! Vola sa METHOD TYPE [TDerivedObject], ktoru musi implementovat DERIVED CLASS.
	CString														Value=CCRTPFacadePatternHiddenInterfaceInterface::GetValue(DerivedObject);

	std::wcout << L"PRINT - PREFIX [" << Prefix << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------