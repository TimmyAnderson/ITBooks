//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
class CCRTPFacadePatternBase
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		const TDerivedObject& GetDerivedObject(void) const;

	private:
		TDerivedObject& GetDerivedObject(void);

	public:
		// !!!!! METHOD predstavuje PUBLIC INTERFACE, ktory vyuziva METHODS, ktore musi implementovat DERIVED CLASS [TDerivedObject].
		void PrintConst(void) const;

	public:
		// !!!!! METHOD predstavuje PUBLIC INTERFACE, ktory vyuziva METHODS, ktore musi implementovat DERIVED CLASS [TDerivedObject].
		void PrintNonConst(void);

	public:
		CCRTPFacadePatternBase(void);
		virtual ~CCRTPFacadePatternBase(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPFacadePatternBase<TDerivedObject>::CCRTPFacadePatternBase(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPFacadePatternBase<TDerivedObject>::~CCRTPFacadePatternBase(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
const TDerivedObject& CCRTPFacadePatternBase<TDerivedObject>::GetDerivedObject(void) const
{
	// !!!!! Vrati REFERENCE na DERIVED OBJECT, ktory je TYPE DERIVED OBJECT.
	const TDerivedObject&										DerivedObject=*(static_cast<const TDerivedObject*>(this));

	return(DerivedObject);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
TDerivedObject& CCRTPFacadePatternBase<TDerivedObject>::GetDerivedObject(void)
{
	// !!!!! Vrati REFERENCE na DERIVED OBJECT, ktory je TYPE DERIVED OBJECT.
	TDerivedObject&												DerivedObject=*(static_cast<TDerivedObject*>(this));

	return(DerivedObject);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
void CCRTPFacadePatternBase<TDerivedObject>::PrintConst(void) const
{
	const TDerivedObject&										DerivedObject=GetDerivedObject();

	// !!!!! Vola sa METHOD TYPE [TDerivedObject], ktoru musi implementovat DERIVED CLASS.
	CString														Prefix=DerivedObject.GetPrefix();

	// !!!!! Vola sa METHOD TYPE [TDerivedObject], ktoru musi implementovat DERIVED CLASS.
	CString														Value=DerivedObject.GetValue();

	std::wcout << L"PRINT CONST - PREFIX [" << Prefix << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
void CCRTPFacadePatternBase<TDerivedObject>::PrintNonConst(void)
{
	TDerivedObject&												DerivedObject=GetDerivedObject();

	// !!!!! Vola sa METHOD TYPE [TDerivedObject], ktoru musi implementovat DERIVED CLASS.
	CString														Prefix=DerivedObject.GetPrefix();

	// !!!!! Vola sa METHOD TYPE [TDerivedObject], ktoru musi implementovat DERIVED CLASS.
	CString														Value=DerivedObject.GetValue();

	std::wcout << L"PRINT NON CONST - PREFIX [" << Prefix << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------