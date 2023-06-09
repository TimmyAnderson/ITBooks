//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateMethodsFriends1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:	
		// !!! CONVERSION OPERATOR, ktory ma zaroven vlastny TEMPLATE PARAMETER, nezavisly na TEMPLATE PARAMETER TEMPLATE CLASS.
		template<typename TOtherType>
		CTemplateMethodsFriends1<TType>& operator=(const CTemplateMethodsFriends1<TOtherType>& Other);

	public:
		const TType& Get(void) const noexcept;

	public:	
		CTemplateMethodsFriends1(const TType& Value);
		virtual ~CTemplateMethodsFriends1(void) noexcept;

	// !!!!! CODE oznaci vsetky TEMPLATE CLASSES TYPE [CTemplateMethodsFriends1<>]  ako FRIENDS.
	// !!!!! TEMPLATE PARAMETER nie je nutne pouzit a tym padom ani nie je nutne definovat jeho NAME.
	template<typename>
	friend class CTemplateMethodsFriends1;

	/*
	// !!!!! Pri tomto CODE COMPILER hodi ERROR, pretoze CODE [CTemplateMethodsFriends1<TOtherType>] povazuje COMPILER za TEMPLATE SPECIALIZATION.
	template<typename TOtherType>
	friend class CTemplateMethodsFriends1<TOtherType>;
	*/
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateMethodsFriends1<TType>::CTemplateMethodsFriends1(const TType& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateMethodsFriends1<TType>::~CTemplateMethodsFriends1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETERS TEMPLATE CLASS.
template<typename TType>
// !!! TEMPLATE PARAMETERS TEMPLATE METHOD (OPERATOR).
template<typename TOtherType>
CTemplateMethodsFriends1<TType>& CTemplateMethodsFriends1<TType>::operator=(const CTemplateMethodsFriends1<TOtherType>& Other)
{
	// !!!!! Kedze OPERATOR je FRIEND, tak je mozne pristupit k PRIVATE MEMBERS CLASS 'CTemplateMethodsFriends1<TOtherType>'.
	const TOtherType&											OriginalValue=Other.MValue;
	TType														ConvertedValue=static_cast<TType>(OriginalValue);

	MValue=ConvertedValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CTemplateMethodsFriends1<TType>::Get(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------