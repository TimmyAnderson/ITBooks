//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!! ADDITIONAL CLASS sluziaca na rozsirenie MIXIN CLASS. CLASS NIE je DERIVED z MIXIN CLASS.
// !!!!! ADDITIONAL CLASS v MIXIN PATTERN predstavuje BASE CLASS, ktoru dedi MIXIN (DERIVED) CLASS.
// !!!!! Vdaka aplikovaniu CURIOUSLY RECURRING TEMPLATE PATTERN ma ADDITIONAL CLASS ako TYPE TEMPLATE PARAMETER TYPE MIXIN (DERIVED) CLASS. ADDITIONAL CLASS tak moze vo svojom CODE vyuzivat MIXIN (DERIVED) CLASS.
template<typename TDerivedObject>
class CMixinClassMixinsWithCRTPAdditionalData2
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		double													MValueDouble;

	public:
		double GetValueDouble(void) const;
		void SetValueDouble(double Value);

	public:
		int GetValueFromMixinViaCRTPData2(void) const;

	public:
		CMixinClassMixinsWithCRTPAdditionalData2(void);
		virtual ~CMixinClassMixinsWithCRTPAdditionalData2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CMixinClassMixinsWithCRTPAdditionalData2<TDerivedObject>::CMixinClassMixinsWithCRTPAdditionalData2(void)
	: MValueDouble()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CMixinClassMixinsWithCRTPAdditionalData2<TDerivedObject>::~CMixinClassMixinsWithCRTPAdditionalData2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
double CMixinClassMixinsWithCRTPAdditionalData2<TDerivedObject>::GetValueDouble(void) const
{
	return(MValueDouble);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
void CMixinClassMixinsWithCRTPAdditionalData2<TDerivedObject>::SetValueDouble(double Value)
{
	MValueDouble=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD demonstruje vyuzitie CRTP na ziskanie dat z DERIVED CLASS.
template<typename TDerivedObject>
int CMixinClassMixinsWithCRTPAdditionalData2<TDerivedObject>::GetValueFromMixinViaCRTPData2(void) const
{
	const TDerivedObject&										DerivedObject=(*static_cast<const TDerivedObject*>(this));
	int															ValueFromDerivedObject=DerivedObject.GetValueInt();

	return(ValueFromDerivedObject);
}
//----------------------------------------------------------------------------------------------------------------------