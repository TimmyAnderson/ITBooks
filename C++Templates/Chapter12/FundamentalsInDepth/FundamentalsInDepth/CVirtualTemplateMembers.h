//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CVirtualTemplateMembers final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MField;

	public:
		// !!! NON-TEMPLATE METHOD MOZE byt VIRTUAL.
		virtual const TType& GetField(void) const noexcept;

	public:
		// !!! TEMPLATE METHOD MOZE NESMIE byt VIRTUAL.
		template<typename TInnerType>
		TInnerType ConvertToNonVirtual(void) const;

	/*
	public:
		// !!! TEMPLATE METHOD MOZE NESMIE byt VIRTUAL.
		template<typename TInnerType>
		virtual TInnerType ConvertToVirtual(void) const;
	*/

	public:
		CVirtualTemplateMembers(TType Field);
		// !!! DESTRUCTOR MOZE byt VIRTUAL, pretoze DESTRUCTOR je v skutocnosti NON-TEMPLATE METHOD TEMPLATE CLASS.
		~CVirtualTemplateMembers(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CVirtualTemplateMembers<TType>::CVirtualTemplateMembers(TType Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CVirtualTemplateMembers<TType>::~CVirtualTemplateMembers(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CVirtualTemplateMembers<TType>::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<typename TInnerType>
TInnerType CVirtualTemplateMembers<TType>::ConvertToNonVirtual(void) const
{
	TInnerType													ConvertedValue=static_cast<TInnerType>(MField);

	return(ConvertedValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
template<typename TType>
template<typename TInnerType>
TInnerType CVirtualTemplateMembers<TType>::ConvertToVirtual(void) const
{
	TInnerType													ConvertedValue=static_cast<TInnerType>(MField);

	return(ConvertedValue);
}
*/
//----------------------------------------------------------------------------------------------------------------------