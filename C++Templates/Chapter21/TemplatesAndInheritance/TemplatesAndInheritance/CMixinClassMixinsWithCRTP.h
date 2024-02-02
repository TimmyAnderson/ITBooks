//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je MIXIN, ktory kombinuje MIXINS PATTERN a CURIOUSLY RECURRING TEMPLATE PATTERN.
// !!!!! MIXIN CLASS predstavuje v CURIOUSLY RECURRING TEMPLATE PATTERN DERIVED CLASS, ktora ma BASE CLASSES, pricom tieto BASE CLASSES obsahuju v TYPE TEMPLATE PARAMETER TYPE MIXIN CLASS.
// !!!!! Kedze BASE CLASSES musia obsahovat TYPE TEMPLATE PARAMETER pre MIXIN CLASS, tak TEMPLATE PARAMETER PACK v MIXIN CLASS je typu TEMPLATE TEMPLATE PARAMETER PACK.
template<template<typename> typename... TTypes>
// !!!!! MIXING CLASS musi dedit z BASE CLASSES a zaroven im posunut svoj TYPE ako TYPE TEMPLATE PARAMETER.
class CMixinClassMixinsWithCRTP final : public TTypes<CMixinClassMixinsWithCRTP<TTypes...>>...
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValueInt;

	public:
		int GetValueInt(void) const;
		void SetValueInt(int Value);

	public:
		CMixinClassMixinsWithCRTP(void);
		virtual ~CMixinClassMixinsWithCRTP(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<template<typename> typename... TTypes>
CMixinClassMixinsWithCRTP<TTypes...>::CMixinClassMixinsWithCRTP(void)
	: TTypes<CMixinClassMixinsWithCRTP<TTypes...>>()..., MValueInt()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<template<typename> typename... TTypes>
CMixinClassMixinsWithCRTP<TTypes...>::~CMixinClassMixinsWithCRTP(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<template<typename> typename... TTypes>
int CMixinClassMixinsWithCRTP<TTypes...>::GetValueInt(void) const
{
	return(MValueInt);
}
//----------------------------------------------------------------------------------------------------------------------
template<template<typename> typename... TTypes>
void CMixinClassMixinsWithCRTP<TTypes...>::SetValueInt(int Value)
{
	MValueInt=Value;
}
//----------------------------------------------------------------------------------------------------------------------