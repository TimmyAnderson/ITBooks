//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
#include "CCRTPFacadePatternAdapterInterface.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
class CCRTPFacadePatternAdapterBase
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
		CCRTPFacadePatternAdapterBase(void);
		virtual ~CCRTPFacadePatternAdapterBase(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPFacadePatternAdapterBase<TDerivedObject>::CCRTPFacadePatternAdapterBase(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPFacadePatternAdapterBase<TDerivedObject>::~CCRTPFacadePatternAdapterBase(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
const TDerivedObject& CCRTPFacadePatternAdapterBase<TDerivedObject>::GetDerivedObject(void) const
{
	// !!!!! Vrati REFERENCE na DERIVED OBJECT, ktory je TYPE DERIVED OBJECT.
	const TDerivedObject&										DerivedObject=*(static_cast<const TDerivedObject*>(this));

	return(DerivedObject);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
TDerivedObject& CCRTPFacadePatternAdapterBase<TDerivedObject>::GetDerivedObject(void)
{
	// !!!!! Vrati REFERENCE na DERIVED OBJECT, ktory je TYPE DERIVED OBJECT.
	TDerivedObject&												DerivedObject=*(static_cast<TDerivedObject*>(this));

	return(DerivedObject);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
void CCRTPFacadePatternAdapterBase<TDerivedObject>::Print(void) const
{
	const TDerivedObject&										DerivedObject=GetDerivedObject();

	// !!!!! Vola sa METHOD TYPE [TDerivedObject], ktoru musi implementovat DERIVED CLASS.
	CString														Prefix=CCRTPFacadePatternAdapterInterface::GetPrefix(DerivedObject);

	// !!!!! Vola sa METHOD TYPE [TDerivedObject], ktoru musi implementovat DERIVED CLASS.
	CString														Value=CCRTPFacadePatternAdapterInterface::GetValue(DerivedObject);

	std::wcout << L"PRINT - PREFIX [" << Prefix << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------