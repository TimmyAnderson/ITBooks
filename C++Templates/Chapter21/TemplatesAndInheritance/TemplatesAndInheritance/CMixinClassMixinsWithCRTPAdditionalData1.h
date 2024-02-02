//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! ADDITIONAL CLASS sluziaca na rozsirenie MIXIN CLASS. CLASS NIE je DERIVED z MIXIN CLASS.
// !!!!! ADDITIONAL CLASS v MIXIN PATTERN predstavuje BASE CLASS, ktoru dedi MIXIN (DERIVED) CLASS.
// !!!!! Vdaka aplikovaniu CURIOUSLY RECURRING TEMPLATE PATTERN ma ADDITIONAL CLASS ako TYPE TEMPLATE PARAMETER TYPE MIXIN (DERIVED) CLASS. ADDITIONAL CLASS tak moze vo svojom CODE vyuzivat MIXIN (DERIVED) CLASS.
template<typename TDerivedObject>
class CMixinClassMixinsWithCRTPAdditionalData1
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CString													MValueString1;
		CString													MValueString2;

	public:
		const CString& GetValueString1(void) const;
		void SetValueString1(const CString& Value);
		const CString& GetValueString2(void) const;
		void SetValueString2(const CString& Value);

	public:
		int GetValueFromMixinViaCRTPData1(void) const;

	public:
		CMixinClassMixinsWithCRTPAdditionalData1(void);
		virtual ~CMixinClassMixinsWithCRTPAdditionalData1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CMixinClassMixinsWithCRTPAdditionalData1<TDerivedObject>::CMixinClassMixinsWithCRTPAdditionalData1(void)
	: MValueString1(), MValueString2()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CMixinClassMixinsWithCRTPAdditionalData1<TDerivedObject>::~CMixinClassMixinsWithCRTPAdditionalData1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
const CString& CMixinClassMixinsWithCRTPAdditionalData1<TDerivedObject>::GetValueString1(void) const
{
	return(MValueString1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
void CMixinClassMixinsWithCRTPAdditionalData1<TDerivedObject>::SetValueString1(const CString& Value)
{
	MValueString1=Value;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
const CString& CMixinClassMixinsWithCRTPAdditionalData1<TDerivedObject>::GetValueString2(void) const
{
	return(MValueString2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
void CMixinClassMixinsWithCRTPAdditionalData1<TDerivedObject>::SetValueString2(const CString& Value)
{
	MValueString2=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD demonstruje vyuzitie CRTP na ziskanie dat z DERIVED CLASS.
template<typename TDerivedObject>
int CMixinClassMixinsWithCRTPAdditionalData1<TDerivedObject>::GetValueFromMixinViaCRTPData1(void) const
{
	const TDerivedObject&										DerivedObject=(*static_cast<const TDerivedObject*>(this));
	int															ValueFromDerivedObject=DerivedObject.GetValueInt();

	return(ValueFromDerivedObject);
}
//----------------------------------------------------------------------------------------------------------------------