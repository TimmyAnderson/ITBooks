//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateMethodsFriends2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:	
		// !!! CONVERSION OPERATOR, ktory ma zaroven vlastny TEMPLATE PARAMETER, nezavisly na TEMPLATE PARAMETER TEMPLATE CLASS.
		template<typename TOtherType1, typename TOtherType2>
		CTemplateMethodsFriends2<TType1,TType2>& operator=(const CTemplateMethodsFriends2<TOtherType1,TOtherType2>& Other);

	public:
		const TType1& Get1(void) const noexcept;
		const TType2& Get2(void) const noexcept;

	public:	
		CTemplateMethodsFriends2(const TType1& Value1, const TType2& Value2);
		virtual ~CTemplateMethodsFriends2(void) noexcept;

	// !!!!! CODE oznaci vsetky TEMPLATE CLASSES TYPE [CTemplateMethodsFriends2<>]  ako FRIENDS.
	// !!!!! TEMPLATE PARAMETER nie je nutne pouzit a tym padom ani nie je nutne definovat jeho NAME.
	template<typename,typename>
	friend class CTemplateMethodsFriends2;

	/*
	// !!!!! Pri tomto CODE COMPILER hodi ERROR, pretoze CODE [CTemplateMethodsFriends2<TOtherType1,TOtherType2>] povazuje COMPILER za TEMPLATE SPECIALIZATION.
	template<typename TOtherType1, typename TOtherType2>
	friend class CTemplateMethodsFriends2<TOtherType1,TOtherType2>;
	*/
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateMethodsFriends2<TType1,TType2>::CTemplateMethodsFriends2(const TType1& Value1, const TType2& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateMethodsFriends2<TType1,TType2>::~CTemplateMethodsFriends2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE PARAMETERS TEMPLATE CLASS.
template<typename TType1, typename TType2>
// !!! TEMPLATE PARAMETERS TEMPLATE METHOD (OPERATOR).
template<typename TOtherType1, typename TOtherType2>
CTemplateMethodsFriends2<TType1,TType2>& CTemplateMethodsFriends2<TType1,TType2>::operator=(const CTemplateMethodsFriends2<TOtherType1,TOtherType2>& Other)
{
	// !!!!! Kedze OPERATOR je FRIEND, tak je mozne pristupit k PRIVATE MEMBERS CLASS 'CTemplateMethodsFriends2<TOtherType1,TOtherType2>'.
	const TOtherType1&											OriginalValue1=Other.MValue1;
	const TOtherType2&											OriginalValue2=Other.MValue2;
	TType1														ConvertedValue1=static_cast<TType1>(OriginalValue1);
	TType2														ConvertedValue2=static_cast<TType2>(OriginalValue2);

	MValue1=ConvertedValue1;
	MValue2=ConvertedValue2;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateMethodsFriends2<TType1,TType2>::Get1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateMethodsFriends2<TType1,TType2>::Get2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------