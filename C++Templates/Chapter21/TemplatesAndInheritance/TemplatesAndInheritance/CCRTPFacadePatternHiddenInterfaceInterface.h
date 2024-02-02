//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS predstavuje PRIVATE INTERFACE, ktory vyuziva CLASS [CCRTPFacadePatternHiddenInterfaceBase] na implementaciu PUBLIC INTERFACE.
class CCRTPFacadePatternHiddenInterfaceInterface final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS [CCRTPFacadePatternHiddenInterfaceBase<TDerivedObject>] sa oznaci ako FRIEND, aby mohla pristupovat k PRIVATE METHODS tejto CLASS.
	template<typename TDerivedObject>
	friend class CCRTPFacadePatternHiddenInterfaceBase;

	private:
		template<typename TDerivedObject>
		static CString GetPrefix(const TDerivedObject& DerivedObject);

		template<typename TDerivedObject>
		static CString GetValue(const TDerivedObject& DerivedObject);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CString CCRTPFacadePatternHiddenInterfaceInterface::GetPrefix(const TDerivedObject& DerivedObject)
{
	CString														Prefix=DerivedObject.GetPrefix();

	return(Prefix);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CString CCRTPFacadePatternHiddenInterfaceInterface::GetValue(const TDerivedObject& DerivedObject)
{
	CString														Value=DerivedObject.GetValue();

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------